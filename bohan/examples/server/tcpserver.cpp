/*
 * @Author: bohan.lj
 * @Date: 2022-11-06 10:53:07
 * @FilePath: /Bohan/bohan/examples/server/tcpserver.cpp
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-12-10 21:32:04
 * @Description: srouce_code
 */
#include "net/Connection.h"
#include "net/NetOperation.h"
#include <memory>

using namespace bohan;

void serv_callback(void* callback_data, NetEvent msg, socket_handle handle, void* pParam)
{
	printf("serv_callback msgType:%d\n",msg);
	if (msg == NetEvent::NET_CONNECT)
	{
		printf("new connection comming...\n");
		Connection *conn = new Connection();
		conn->OnNewConn(handle);
	}
}

int main()
{
    NetOptErrorCode ret = net_init();
    if (ret == NetOptErrorCode::NET_OPT_ERROR)
		return (int)ret;

    ret = net_listen("127.0.0.1", 10086, serv_callback, NULL);
    if (ret == NetOptErrorCode::NET_OPT_ERROR)
    {
        return ret;
    }
    printf("now enter the event loop...\n");
    net_eventloop();
    return 0;
}