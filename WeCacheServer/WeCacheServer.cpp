/*
 * WeCacheServer.cpp
 *
 *  Created on: 2015-06-11 21:00
 *      Author: young
 *
 *  POWERED BY ENET
 *  E-MAIL: xmulyj@gmail.com
 */
#include "WeCacheServer.h"

/* 1: 10000以内的CmdID内部占用,请从10001开始定义自己的CmdID;
 * 2: 建议将cmd ID移到统一的文件中进行定义;
 */

IMPL_LOGGER(WeCacheServer, logger);

int WeCacheServer::OnInit(ConfReader *config)
{
    //注册Cmd处理方法
    CALL_HANDLE_REG();

    //添加其他初始化内容

    return 0;
}

bool WeCacheServer::OnPacket(TCPSession *session, uint32_t cmd, const char *packet_data, uint32_t head_size, uint32_t body_size, uint64_t tid)
{
    if(!HAS_HANDLE(cmd))
    {
        LOG_DEBUG(logger, "can't find handler for cmd="<<cmd<<".fd="<<session->GetFD());
        //由父类来处理
        return TCPServer::OnPacket(session, cmd, packet_data, head_size, body_size, tid);
    }

    HANDLER_PTR handler = GET_HANDLE(cmd);
    int ret = (this->*handler)(session, packet_data, head_size, body_size, tid);
    return ret==0?true:false;
}

// 需要处理错误的话,请打开开关
#if USE_ERROR
IOStatus WeCacheServer::OnError(TCPSession *session, uint64_t now_ms)
{
    //处理错误

    return TCPServer::OnError(session, now_ms);
}
#endif

// 需要处理自己的监听的话,请打开开关
#if USE_LISTEN
//创建listen成功后调用,需要处理listen_fd的连接事件
bool WeCacheServer::OnListenSucc(uint32_t index, uint32_t listen_fd, const ConfSessionParam &session_param)
{
    LOG_DEBUG(logger, "OnListenSucc|index="<<index);
    switch(index)
    {
    case 0:  //默认是服务器间的通信
        return TCPServer::OnListenSucc(index, listen_fd, session_param);
        break;
//    case 1:
//        InitSessionMgr(&m_listen_session_mgr_1, session_param);  //初始化listen session mgr
//        m_listen_session_mgr_1.Init(GetIOServer(), m_packet_1, listen_fd);
//        break;
    default:
        return false;
    }

    return true;
}
#endif

// 需要处理每秒检查任务的话,请打开开关
#if USE_CHECK_TIMER
void WeCacheServer::OnCheckPerSec(uint64_t now_ms)
{

    return ;
}
#endif

// 需要按cmd/svr_id做路由选择的话,请打开开关
#if USE_CMD_ROUTE
Session* WeCacheServer::SererGroup_GetSession(uint32_t cmd, uint32_t svr_id, vector<ServerInfo>&svr_group)
{
    if(svr_group.size()>0 && svr_group[0].svr_valid)
    {
        LOG_DEBUG(logger, "WeCacheServer|SererGroup_GetSession|use first svr_info by default.cmd="<<cmd
                    <<",svr_id="<<svr_group[0].svr_id
                    <<",svr_num="<<svr_group[0].svr_num
                    <<",svr_inde="<<svr_group[0].svr_index
                    <<",svr_session"<<svr_group[0].svr_session);
        return svr_group[0].svr_session;
    }

    LOG_ERROR(logger, "WeCacheServer|SererGroup_GetSession|no valid session.cmd="<<cmd
                    <<",svr_id="<<svr_id
                    <<",svr_group size="<<svr_group.size());
    return NULL;
}
#endif


#if USE_EXAMPLE == 1
int WeCacheServer::OnExample(TCPSession *session, const char *data, uint32_t head_size, uint32_t body_size, uint64_t tid)
{
    string req_str;
    req_str.assign(data+head_size, body_size);
    LOG_INFO(logger, "OnExample|Req="<<req_str);

    string rsp_str = "TestExample is ok!";
    char buffer[1024];
    uint32_t rsp_size = 0;

    Packet *packet = GetInternalPacket();
    int header_size = packet->SetHead(buffer, sizeof(buffer), rsp_str.size(), CMD_EXAMPLE_RSP);
    assert(header_size > 0);

    memcpy(buffer+header_size, rsp_str.c_str(), rsp_str.size());
    rsp_size = header_size+rsp_str.size();

    if(session->AsyncSend(buffer, rsp_size) == true)
    {
        LOG_INFO(logger, "OnExample|send OnExampleRsp succ.fd="<<session->GetFD()<<".rsp_size="<<rsp_size);
    }
    else
    {
        LOG_WARN(logger, "OnExample|send OnExampleRsp failed.fd="<<session->GetFD()<<".rsp_size="<<rsp_size);
    }

    return 0;
}
#endif
