/*
 * @Author: bohan.lj
 * @Date: 2022-11-17 08:14:43
 * @FilePath: /Bohan/bohan/examples/client/client.cpp
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-11-20 13:33:51
 * @Description: srouce_code
 */
#include "net/Connection.h"
#include "net/NetOperation.h"
#include <stdio.h>
#include <iostream>
#include <memory>
#include <thread>

using namespace bohan;

int main()
{
    NetOptErrorCode ret = net_init();
    if (ret == NetOptErrorCode::NET_OPT_ERROR)
		return (int)ret;

	std::thread run_thread = std::thread([](){
        net_eventloop();
    });

    ConnectionPtr conn = make_shared<Connection>();
    socket_handle handle = conn->Connect("127.0.0.1",10086);
    if(handle == INVALID_SOCKET_HANDLE)
    {
        printf("connect server error...");
        return -1;
    }

    int i = 0;
    scanf("%d",&i);
    return 0;
}