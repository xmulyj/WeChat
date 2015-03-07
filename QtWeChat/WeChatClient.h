/*
 * WeChatClient.h
 *
 *  Created on: Feb 19, 2015
 *      Author: young
 */

#ifndef WECHATCLIENT_WECHATCLIENT_H_
#define WECHATCLIENT_WECHATCLIENT_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <string>
using std::string;
#include <google/protobuf/message.h>
using namespace ::google::protobuf;
#include "WeChat.pb.h"
#include "enet/ENet.h"

class WeChatMainDialog;

class CWeChatClient:public IOHandler, public Thread
{
public:
    CWeChatClient():m_Fd(-1), m_ChatDialog(NULL){}
    static int SendAndRecvMsg(int fd, int cmd, Message *req, Message *rsp);

    int Init(int32_t fd, uint32_t id, const string &name, WeChatMainDialog *chat_dialog);


    void UnInit();

    int SendLogout();
    int SendMsg(const char *msg);
    int SendMsg(const string &msg);

    int DoPing();
protected:
    void DoRun();
private:
    IOStatus OnRead(int fd, uint64_t now_ms);
    IOStatus OnWrite(int fd, uint64_t now_ms);
    IOStatus OnError(int fd, uint64_t now_ms);  //请不要close掉fd,框架会close的.切记切记!!!
private:
    int32_t m_Fd;
    uint32_t m_ID;
    string m_Name;

    int32_t m_Pipe[2];
    IOServerEpoll m_IOServer;

    char m_SendBuffer[1024];
    char m_RecvBuffer[1024];

    int PacketMsg(uint32_t cmd, Message *msg);
    int OnSendMsg();
    int OnRecvMsg();

    WeChatMainDialog *m_ChatDialog;
    void InitUI(LoginRsp &rsp);
};



#endif /* WECHATCLIENT_WECHATCLIENT_H_ */
