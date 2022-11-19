/*
 * @Author: bohan.lj
 * @Date: 2022-11-06 10:53:07
 * @FilePath: /Bohan/bohan/examples/server/tcpserver.cpp
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-11-19 12:30:15
 * @Description: srouce_code
 */
#include "net/Connection.h"
#include "net/NetOperation.h"

using namespace bohan;

void serv_callback(void* callback_data, uint8_t msg, uint32_t handle, void* pParam)
{
	if (msg == NetEvent::NET_CONNECT)
	{
		printf("new connection comming...\n");
		Connection* pConn = new Connection();
		pConn->OnConnect(handle);
	}
	else
	{
		printf("!!!error msg: %d ", msg);
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
    
    //writePid();

	net_eventloop();

    return 0;
}