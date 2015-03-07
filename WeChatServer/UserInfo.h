/*
 * UserInfo.h
 *
 *  Created on: Feb 18, 2015
 *      Author: young
 */

#ifndef WECHATSERVER_USERINFO_H_
#define WECHATSERVER_USERINFO_H_
#include <string>
using std::string;

class UserInfo
{
public:
    uint32_t id;
    string name;
    string passwd;
};



#endif /* WECHATSERVER_USERINFO_H_ */
