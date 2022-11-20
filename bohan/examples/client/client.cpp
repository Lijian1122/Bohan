/*
 * @Author: bohan.lj
 * @Date: 2022-11-17 08:14:43
 * @FilePath: /Bohan/bohan/examples/client/client.cpp
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-11-20 20:00:55
 * @Description: srouce_code
 */
#include "net/Connection.h"
#include "net/NetOperation.h"
#include "net/NetCoreLib.h"
#include <stdio.h>
#include <iostream>
#include <memory>
#include <thread>

using namespace bohan;

int main()
{

    if(!NetCoreLib::Instance()->startNetEvent())
    {
        printf("run net event error...");
        return -1;
    }

    socket_handle handle =  NetCoreLib::Instance()->connect("127.0.0.1",10086);
    if(handle == INVALID_SOCKET_HANDLE)
    {
        printf("connect server error...");
        return -2;
    }

    int i = 0;
    scanf("%d",&i);
    return 0;
}