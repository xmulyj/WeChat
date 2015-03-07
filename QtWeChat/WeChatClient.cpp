/*
 * WeChatClient.cpp
 *
 *  Created on: Feb 19, 2015
 *      Author: young
 */

#include "WeChatClient.h"
#include <unistd.h>
#include "wechatmaindialog.h"


class PingTimer:public TimerHandler
{
public:
    PingTimer():m_WeChatClient(NULL){}
    ~PingTimer(){}

    void Set(IOServer *io_server, CWeChatClient *app)
    {
        TimerHandler::Init(io_server, 20000, true);
        m_WeChatClient = app;
    }

    bool OnTimeOut(uint64_t now_ms)
    {
        m_WeChatClient->DoPing();
        return true;
    }
private:
    CWeChatClient *m_WeChatClient;
};
PingTimer g_PingTimer;

//static
int CWeChatClient::SendAndRecvMsg(int fd, int cmd, Message *req, Message *rsp)
{
    Packet packet;
    //序列化
    uint32_t body_size = req->ByteSize();
    if(body_size > 960)
    {
        return -1;
    }
    char DataBuffer[960];
    uint32_t head_size = packet.SetHead(DataBuffer, 100, body_size, cmd, 0);
    if(head_size <= 0)
    {
        return -2;
    }
    req->SerializePartialToArray(DataBuffer+head_size, body_size);

    int total_size = head_size+body_size;
    int ret = TcpSocket::SendAll(fd, DataBuffer, total_size);
    if(ret != total_size)
    {
        return -3;
    }

    //接收登录回包
    uint32_t data_size = sizeof(StDefaultPacket);
    ret = TcpSocket::RecvAll(fd, DataBuffer, data_size);
    if(ret != data_size)
    {
        return -4;
    }

    if(packet.IsValid(DataBuffer, data_size, head_size, body_size) != PACKET_OK)
    {
        return -5;
    }
    ret = TcpSocket::RecvAll(fd, DataBuffer+head_size, body_size);
    if(ret != body_size)
    {
        return -6;
    }

    if(rsp->ParseFromArray(DataBuffer+head_size, body_size) == false)
    {
        return -7;
    }

    return 0;
}


int CWeChatClient::Init(int32_t fd, uint32_t id, const string &name, WeChatMainDialog *chat_dialog)
{
    m_ID = id;
    m_Name = name;
    m_Fd = fd;
    m_ChatDialog = chat_dialog;

    if(pipe(m_Pipe) != 0)
    {
        //printf("create pipe failed. error=%d\n", errno);
        return -2;
    }
    //printf("WeChatClient Init:fd=%d,pipe_read=%d\n", fd, m_Pipe[0]);

    m_IOServer.Init(10);
    IOHandler::Init(&m_IOServer, -1);
    m_IOServer.AddEvent(m_Fd, EVENT_READ, this);
    m_IOServer.AddEvent(m_Pipe[0], EVENT_READ, this);

    g_PingTimer.Set(&m_IOServer, this);
    m_IOServer.AddTimer(&g_PingTimer);

    StartThread();
    return 0;
}

void CWeChatClient::InitUI(LoginRsp &rsp)
{

}

void CWeChatClient::UnInit()
{
    //这边有个小问题:发送了LOGOUT后进入到这边,IOServer的stop先生效退出导致LOGOUT命令没有发送出去
    sleep(3);
    m_IOServer.Stop();
    WaitTerminate();
}

int CWeChatClient::SendLogout()
{
    printf("[id=%d name=%s] Logout...\n", m_ID, m_Name.c_str());
    LogoutReq req;
    req.set_id(m_ID);

    PacketMsg(CMD_LOGOUT_REQ, &req);
    return 0;
}

int CWeChatClient::SendMsg(const char *msg)
{
    //printf("id=%d name=%s:\n\t%s\n", m_ID, m_Name.c_str(), msg);
    SendMsgReq req;
    req.set_msg(msg);

    PacketMsg(CMD_SEND_MSG_REQ, &req);
    return 0;
}

int CWeChatClient::SendMsg(const string &msg)
{
    //printf("id=%d name=%s:\n\t%s\n", m_ID, m_Name.c_str(), msg);
    SendMsgReq req;
    req.set_msg(msg);

    PacketMsg(CMD_SEND_MSG_REQ, &req);
    return 0;
}

void CWeChatClient::DoRun()
{
    printf("WeChatClient running...\n");
    m_IOServer.RunForever();
}


IOStatus CWeChatClient::OnRead(int fd, uint64_t now_ms)
{
    //printf("OnRead:fd=%d\n", fd);
    if(fd == m_Pipe[0])
    {
        OnSendMsg();
    }
    else
    {
        if(OnRecvMsg() != 0)
        {
            return IO_ERROR;
        }
    }
    return IO_CONTINUE;
}

IOStatus CWeChatClient::OnWrite(int fd, uint64_t now_ms)
{
    return IO_SUCC;
}

IOStatus CWeChatClient::OnError(int fd, uint64_t now_ms)
{
    m_Fd = -1;
    return IO_SUCC;
}


int CWeChatClient::OnSendMsg()
{
    uint32_t size = 0;
    read(m_Pipe[0], &size, sizeof(uint32_t));
    read(m_Pipe[0], m_SendBuffer, size);

    if(m_Fd <= 0)
    {
        m_ChatDialog->AppendMsg("connect is closed");
        return -1;
    }

    int ret = TcpSocket::SendAll(m_Fd, m_SendBuffer, size);
    if(ret != size)
    {
        m_ChatDialog->AppendMsg("send failed.");
        return ret;
    }

    return 0;
}

int CWeChatClient::OnRecvMsg()
{
    uint32_t data_size = sizeof(StDefaultPacket);
    int ret = TcpSocket::RecvAll(m_Fd, m_RecvBuffer, data_size);
    if(ret != data_size)
    {
        printf("recv head failed, head_size=%d, ret=%d.\n", data_size, ret);
        return -1;
    }

    Packet packet;

    uint32_t head_size, body_size;
    if(packet.IsValid(m_RecvBuffer, data_size, head_size, body_size) != PACKET_OK)
    {
        printf("packet data is invalid.\n");
        return -2;
    }
    ret = TcpSocket::RecvAll(m_Fd, m_RecvBuffer+head_size, body_size);
    if(ret != body_size)
    {
        printf("recv body data failed.body_size=%d, ret=%d\n", body_size, ret);
        return -3;
    }
    Msg msg;
    if(msg.ParseFromArray(m_RecvBuffer+head_size, body_size) == false)
    {
        printf("parse msg failed.\n");
        return -4;
    }

    m_ChatDialog->AppendMsg(msg);
    return 0;
}

int CWeChatClient::PacketMsg(uint32_t cmd, Message *msg)
{
    Packet packet;
    //序列化
    int body_size = msg->ByteSize();
    if(body_size > 960)
    {
        printf("msg size too big(limit=960\n");
        return -1;
    }
    int head_size = packet.SetHead(m_SendBuffer, 100, body_size, cmd, 0);
    if(head_size <= 0)
    {
        printf("packet head failed.\n");
        return -2;
    }
    msg->SerializePartialToArray(m_SendBuffer+head_size, body_size);

    //send to pipe
    uint32_t total_size = head_size+body_size;
    write(m_Pipe[1], &total_size, sizeof(uint32_t));
    write(m_Pipe[1], m_SendBuffer, total_size);
    return total_size;
}

int CWeChatClient::DoPing()
{
    if(m_Fd <= 0)
    {
        printf("DoPing:connect is closed.\n");
        return -1;
    }

    PingReq req;
    req.set_id(m_ID);

    Packet packet;
    //序列化
    int body_size = req.ByteSize();
    int head_size = packet.SetHead(m_SendBuffer, 100, body_size, CMD_PING_REQ, 0);
    if(head_size <= 0)
    {
        printf("packet head failed.\n");
        return -1;
    }
    req.SerializePartialToArray(m_SendBuffer+head_size, body_size);

    uint32_t size = head_size+body_size;
    int ret = TcpSocket::SendAll(m_Fd, m_SendBuffer, size);
    if(ret != size)
    {
        printf("send failed. size=%d, ret=%d", size, ret);
        return ret;
    }

    return 0;
}
