/*
 * @Author: bohan.lj
 * @Date: 2022-12-11 21:00:08
 * @FilePath: /Bohan/bohan/MsgServer/MsgConn.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2023-03-12 12:05:41
 * @Description: srouce_code
 */
#ifndef MSG_CONN_H
#define MSG_CONN_H
#include "os_type.h"
#include "HashMap.h"
#include "net/Connection.h"

namespace bohan
{
class MsgConn : public Connection
{

public:
    MsgConn(/* args */);
    ~MsgConn();
private:
          /* data */
};
}
#endif