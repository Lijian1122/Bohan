/*
 * @Author: bohan.lj
 * @Date: 2022-12-11 21:37:01
 * @FilePath: /Bohan/bohan/MsgServer/ServerDefine.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2023-03-12 12:48:56
 * @Description: srouce_code
 */
#ifndef SERVER_DEFINE_H
#define SERVER_DEFINE_H

#include <iostream>
#include <set>
#include "pb/protocol/BaseDefine.pb.h"
#include "os_type.h"

using namespace std;



#define CLIENT_TYPE_FLAG_NONE    0x00
#define CLIENT_TYPE_FLAG_PC      0x01
#define CLIENT_TYPE_FLAG_MOBILE  0x02
#define CLIENT_TYPE_FLAG_BOTH    0x03

#define CHECK_CLIENT_TYPE_PC(type) \
({\
bool bRet = false;\
if ((type & 0x10) == 0x00)\
{\
bRet = true;\
}\
bRet;\
})

#define CHECK_CLIENT_TYPE_MOBILE(type) \
({\
bool bRet = false;\
if ((type & 0x10) == 0x10)\
{\
bRet = true;\
}\
bRet;\
})


namespace bohan
{
enum ClientType{
    WINDOWS  = 0x00,
    MAC      = 0x01,
    IOS      = 0x11,
    ANDROID  = 0x12,
    BOTH     = 0x13
};

struct UserStat{
    uint32_t user_id;
    uint32_t status;
    uint32_t client_type;
};


struct UserConn{
    uint32_t user_id;
    uint32_t conn_cnt;
};
}
#endif