/*
 * WeStatusServer.h
 *
 *  Created on: 2015-06-11 11:49
 *      Author: young
 *
 *  POWERED BY ENET
 *  E-MAIL: xmulyj@gmail.com
 */

#ifndef _WESTATUSSERVER_H_
#define _WESTATUSSERVER_H_

#include "enet/ENet.h"
using namespace enet;

#include "MacroDefine.h"


/* 1: 10000以内的CmdID内部占用,请从10001开始定义自己的CmdID;
 * 2: 建议将cmd ID移到统一的文件中进行定义;
 */

#if USE_EXAMPLE == 1
#define CMD_EXAMPLE_REQ  9998
#define CMD_EXAMPLE_RSP  9999
#endif


#include "../proto/WeCmdID.pb.h"
#include "../proto/WeStatus.pb.h"

#include "../DBWrap/DBWrap.h"
#include "CommonSend.h"

class WeStatusServer:public TCPServer, public CommonSend
{
public:
    WeStatusServer(ConfReader *conf):TCPServer(conf), m_DBWrap(NULL){}
protected:
    // @override
    int OnInit(ConfReader *config);

    // @override
    bool OnPacket(TCPSession *session, uint32_t cmd, const char *packet_data, uint32_t head_size, uint32_t body_size, uint64_t tid);

    // 需要处理自己的错误的话,请打开开关
#if USE_ERROR
    // @override
    // 会话结束调用,回收相关资源
    IOStatus OnError(TCPSession *session, uint64_t now_ms);
#endif

    // 需要处理自己的错误的话,请打开开关
#if USE_LISTEN
    // @override
    // 创建listen成功后调用,需要处理listen_fd的连接事件
    bool OnListenSucc(uint32_t index, uint32_t listen_fd, const ConfSessionParam &session_param)
#endif

    // 需要处理每秒检查任务的话,请打开开关
#if USE_CHECK_TIMER
    // @override
    // 每秒定时器触发
    void OnCheckPerSec(uint64_t now_ms);
#endif

    // 需要按cmd/svr_id做路由选择的话,请打开开关
#if USE_CMD_ROUTE
    // @override
    // 根据cmd获取服务器组中的一个session(默认返回第一个有效的session).子类可以根据自己的路由规则需求重写本方法
    virtual Session* SererGroup_GetSession(uint32_t cmd, uint32_t svr_id, vector<ServerInfo>&svr_group);
#endif

private:
    /***********************************
     **********  定义 handler  **********
    /***********************************/
    // CmdID的处理方法类型定义
    //   session: 请求的会话信息(即代表一个连接)
    //      data: 完整的请求数据,包含协议头和协议体;协议头主要用来分包的,协议体则包含应用层自定义的协议数据(参考Packet类的定义)
    // head_size: 协议头长度
    // body_size: 协议头体长度
    //       tid: 事务id(代表每个请求的唯一id号)
    // handler类型定义
    typedef int (HANDLER)(TCPSession *session, const char *data, uint32_t head_size, uint32_t body_size, uint64_t tid);
    // handler指针类型定义
    typedef int (WeStatusServer::*HANDLER_PTR)(TCPSession *session, const char *data, uint32_t head_size, uint32_t body_size, uint64_t tid);

    // 声明handler方法
#if USE_EXAMPLE == 1
    HANDLER OnExample;
#endif

    HANDLER OnNotifyUserStatusReq;
    HANDLER OnGetUserStatusReq;

    /***********************************
     **********  注册 handler  **********
    /***********************************/
    HANDLE_REG(WeStatusServer, uint32_t, HANDLER_PTR)
#if USE_EXAMPLE == 1
    HANDLE_CMD(CMD_EXAMPLE_REQ, OnExample)
#endif

    HANDLE_CMD(CMD_NOTIFY_USERSTATUS_REQ, OnNotifyUserStatusReq);   //通知用户状态
    HANDLE_CMD(CMD_GET_USERSTATUS_REQ, OnGetUserStatusReq); //获取用户状态

    HANDLE_REG_END
private:
    DBWrap *m_DBWrap;
private:
    DECL_LOGGER(logger);
};

#endif /* _WESTATUSSERVER_H_ */

