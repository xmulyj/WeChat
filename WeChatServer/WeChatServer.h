/*
 * WeChatServer.h
 *
 *  Created on: 2015-02-18 16:16
 *      Author: young
 *
 *  POWERED BY ENET
 *  E-MAIL: xmulyj@gmail.com
 */

#ifndef _WECHATSERVER_H_
#define _WECHATSERVER_H_

#include "enet/ENet.h"
using namespace enet;

#define SHOW_EXAMPLE 0

/* 1: 10000以内的CmdID内部占用,请从10001开始定义自己的CmdID;
 * 2: 建议将cmd ID移到统一的文件中进行定义;
 */

#if SHOW_EXAMPLE == 1
#define CMD_EXAMPLE_REQ  9998
#define CMD_EXAMPLE_RSP  9999
#endif


#include "CommonSend.h"
#include "UserInfo.h"
#include "../proto/WeChat.pb.h"

class WeChatServer:public TCPServer, public TCPServerRoute, public CommonSend
{
public:
    WeChatServer(ConfReader *conf):TCPServer(conf){}
protected:
    // @override
    int OnInit(ConfReader *config);

    // @override
    bool OnPacket(TCPSession *session, uint32_t cmd, const char *packet_data, uint32_t head_size, uint32_t body_size, uint64_t tid);

    // @override
    IOStatus OnError(TCPSession *session, uint64_t now_ms);

    /* 需要处理自己的监听,请去掉注释
    // @override
    // 创建listen成功后调用
    void OnListenSucc(ListenInfo &listen_info, const ConfSessionParam &session_param);
    */

    /* 需要处理每秒检查任务,请去掉注释
    // @override
    // 每秒定时器触发
    void OnCheckPerSec(uint64_t now_ms);
    */
private:
    // CmdID的处理方法类型定义
    //   session: 请求的会话信息(即代表一个连接)
    //      data: 完整的请求数据,包含协议头和协议体;协议头主要用来分包的,协议体则包含应用层自定义的协议数据(参考Packet类的定义)
    // head_size: 协议头长度
    // body_size: 协议头体长度
    //       tid: 事务id(代表每个请求的唯一id号)
    // handler类型定义
    typedef int (HANDLER)(TCPSession *session, const char *data, uint32_t head_size, uint32_t body_size, uint64_t tid);
    // handler指针类型定义
    typedef int (WeChatServer::*HANLDER_PTR)(TCPSession *session, const char *data, uint32_t head_size, uint32_t body_size, uint64_t tid);
    // 声明handler方法
#if SHOW_EXAMPLE == 1
    HANDLER OnExample;
#endif
    HANDLER OnPingReq;
    HANDLER OnRegReq;
    HANDLER OnLoginReq;
    HANDLER OnLogoutReq;
    HANDLER OnSendMsgReq;

    HANDLE_REG(WeChatServer, uint32_t, HANLDER_PTR)
#if SHOW_EXAMPLE == 1
    HANDLE_CMD(CMD_EXAMPLE_REQ, OnExample)
#endif
    HANDLE_CMD(CMD_PING_REQ, OnPingReq)
    HANDLE_CMD(CMD_REG_REQ, OnRegReq)
    HANDLE_CMD(CMD_LOGIN_REQ, OnLoginReq)
    HANDLE_CMD(CMD_LOGOUT_REQ, OnLogoutReq)
    HANDLE_CMD(CMD_SEND_MSG_REQ, OnSendMsgReq)

    HANDLE_REG_END
private:
    typedef map<uint32_t, UserInfo> UserInfoMap;
    typedef map<TCPSession*, UserInfo*> SessionUserInfoMap;
    UserInfoMap m_UserInfoMap;
    SessionUserInfoMap m_SessionUserInfoMap;

    void BroadcastMsg(Msg &msg);
    UserInfo* SaveNewUser(RegReq &req);
    uint32_t GenID(){return m_UserInfoMap.size()+10000;}

    UserInfo* LoginCheck(LoginReq &req);
    void FillMemberList(uint32_t id, MemberList &member_list);
private:
    DECL_LOGGER(logger);
};

#endif /* _WECHATSERVER_H_ */

