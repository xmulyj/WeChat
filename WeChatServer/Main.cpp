/*
 * Main.cpp
 *
 *  Created on: $DATE$
 *      Author: $USER$
 *
 *  POWERED BY ENET
 *  E-MAIL: xmulyj@gmail.com
 */

#include "WeChatServer.h"

const char CONF_NAME[]="../conf/TCPServer.conf";

int main()
{
    INIT_LOGGER("../conf/log4cplus.conf");

    ConfReader conf;
    if(conf.Init(CONF_NAME) != 0)
    {
    	string ErrMsg = conf.GetErrMsg();
    	printf("Init conf=%s failed.ErrMsg=%s\n", CONF_NAME,  ErrMsg.c_str());
    	return -1;
    }

    WeChatServer server(&conf);
    if(server.Init() != 0)
        return -1;

    //Set yourself Packet class by server.SetInternalPacket() method if needed:
    //server.SetInternalPacket(other_packet);

    server.RunForever();
    return 0;
}


