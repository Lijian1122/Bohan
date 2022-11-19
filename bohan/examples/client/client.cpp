/*
 * @Author: bohan.lj
 * @Date: 2022-11-17 08:14:43
 * @FilePath: /Bohan/bohan/examples/client/client.cpp
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-11-19 12:29:31
 * @Description: srouce_code
 */
#include "net/Connection.h"
#include "net/NetOperation.h"
#include <stdio.h>
#include <iostream>
#include <memory>

using namespace bohan;

ConnMap_t m_conn_map;

void callback(void* data, uint8_t msg, uint32_t handle, void* param)
{
	printf("!!!error msg: %d ", msg);
}

int main()
{
    NetOptErrorCode ret = net_init();
    if (ret == NetOptErrorCode::NET_OPT_ERROR)
		return (int)ret;

    ConnectionPtr conn = make_shared<Connection>();
    socket_handle handle = conn->Connect("127.0.0.1",10086,callback,NULL);
    if(handle == INVALID_SOCKET_HANDLE)
    {
        printf("connect server error...");
        return -1;
    }

    m_conn_map[handle] = conn;

    std::string data = "Hello sever,I m client";
    int retCode = conn->Send((void*)data.c_str(),data.size());
    printf("ret:%d",retCode);
    return 0;
}