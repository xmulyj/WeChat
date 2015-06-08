/*
 * CommonSend.h
 *
 *  Created on: Nov 22, 2014
 *      Author: young
 */

#ifndef COMMONSEND_H_
#define COMMONSEND_H_

#include "enet/ENet.h"
using namespace enet;

#include <google/protobuf/message.h>
using namespace ::google::protobuf;

class CommonSend
{
public:
    CommonSend():m_tcp_svr(NULL){}
    void SetServer(TCPServer *tcp_svr)
    {
        m_tcp_svr = tcp_svr;
    }
    
    //发送数据到svr.根据session发送
    int SendToSvr(Session *session, uint32_t cmd, Message *msg, uint64_t tid);
    //发送数据到svr.指定svr_id和路由方式选择对应的session
    int SendToSvr(uint32_t cmd, Message *msg, uint32_t svr_id, uint64_t tid);

    //发送请求.直接按cmd路由;
    //如果req_session非空的话将tid和req_session作映射(事务处理,需要检查该session发送的请求是否超时)
    int ReqSvr(uint32_t cmd, Message *msg, uint64_t tid, Session *req_session=NULL, uint32_t req_timeout=5);
    //发送回复.往session发送回复包
    int RspSvr(Session *session, uint32_t cmd, Message *msg, uint64_t tid);
    //发送回复到tid映射的session,如果找不到session返回失败
    int RspSvr(uint32_t cmd, Message *msg, uint64_t tid);
private:
    TCPServer *m_tcp_svr;
};

inline
int CommonSend::SendToSvr(Session *session, uint32_t cmd, Message *msg, uint64_t tid)
{
    if(session == NULL)
        return -1;
    TCPSession *tcp_session = dynamic_cast<TCPSession*>(session);

    Packet* packet = tcp_session->GetPacket(); assert(packet != NULL);
    ByteBuffer& send_byte_buffer = tcp_session->GetSendBuffer();
    //序列化
    int body_size = msg->ByteSize();
    char* buffer = send_byte_buffer.RemainBuffer(body_size+100);
    if(buffer == NULL)
    {
        return -2;
    }
    int head_size = packet->SetHead(buffer, 100, body_size, cmd, tid);
    if(head_size <= 0)
        return -3;
    msg->SerializePartialToArray(buffer+head_size, body_size);
    send_byte_buffer.AddSize(head_size+body_size);
    //异步发送
    return tcp_session->AsyncSend()?0:-4;
}

inline
int CommonSend::SendToSvr(uint32_t cmd, Message *msg, uint32_t svr_id, uint64_t tid)
{
    //获取会话和byte buffer
    TCPSession *session = dynamic_cast<TCPSession*>(m_tcp_svr->ServerGroup_GetSession(cmd));
    return SendToSvr(session, cmd, msg, tid);
}

inline
int CommonSend::ReqSvr(uint32_t cmd, Message *msg, uint64_t tid, Session *req_session/*=NULL*/, uint32_t req_timeout/*=5*/)  //直接按cmd路由
{
    if(req_session != NULL)
    {
        if(m_tcp_svr->SaveTraction(tid, req_session, req_timeout))
        {
            return -99999;
        }
    }
    Session *session = m_tcp_svr->ServerGroup_GetSession(cmd);
    return SendToSvr(session, cmd, msg, tid);
}

inline
int CommonSend::RspSvr(Session *session, uint32_t cmd, Message *msg, uint64_t tid)
{
    return SendToSvr(session, cmd, msg, tid);
}

inline
int CommonSend::RspSvr(uint32_t cmd, Message *msg, uint64_t tid)
{
    SessionDefault* session = dynamic_cast<SessionDefault*>(m_tcp_svr->GetTraction(tid, true));
    if(session == NULL)
    {
        return -99999;
    }
    return SendToSvr(session, cmd, msg, tid);
}
#endif /* COMMONSEND_H_ */
