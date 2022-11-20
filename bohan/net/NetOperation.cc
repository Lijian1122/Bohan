/*
 * @Author: bohan.lj
 * @Date: 2022-10-30 21:57:00
 * @FilePath: /Bohan/bohan/net/NetOperation.cc
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-11-10 08:51:23
 * @Description: srouce_code
 */
#include "NetOperation.h"
namespace bohan
{
NetOptErrorCode net_init()
{
    NetOptErrorCode ret = NetOptErrorCode::NET_OPT_OK;
#ifdef _WIN32
	WSADATA wsaData;
	WORD wReqest = MAKEWORD(1, 1);
	if (WSAStartup(wReqest, &wsaData) != 0)
	{
		ret = NetOptErrorCode::NET_OPT_ERROR;
	}
#endif
	return ret;
}

NetOptErrorCode net_destroy()
{
    NetOptErrorCode ret = NetOptErrorCode::NET_OPT_OK;
#ifdef _WIN32
	if (WSACleanup() != 0)
	{
		ret = NetOptErrorCode::NET_OPT_ERROR;
	}
#endif
	return ret;
}

NetOptErrorCode net_listen(const char *server_ip, uint32_t	port, callback_fun callback, void*	callback_data)
{
    BaseSocket* socket = new BaseSocket();
	if (!socket)
		return NetOptErrorCode::NET_OPT_ERROR;

	SocketError ret =  socket->Listen(server_ip, port, callback, callback_data);
	if (ret != SocketError::NO_ERROR)
    {
        delete socket;
        socket = nullptr;
		return NetOptErrorCode::NET_OPT_ERROR;
    }
	return NetOptErrorCode::NET_OPT_OK;
}

socket_handle net_connect(const char*server_ip,uint16_t port,callback_fun callback,void *callback_data)
{
    BaseSocket* socket = new BaseSocket();
	if (!socket)
		return INVALID_SOCKET_HANDLE;
	socket_handle handle = socket->Connect(server_ip, port, callback, callback_data);
	if (handle == INVALID_SOCKET_HANDLE)
    {
        delete socket;
        socket = nullptr;
    }
	return handle;
}

int net_send(socket_handle handle, void* buf, int len)
{
    BaseSocket* socket = FindBaseSocket(handle);
	if (!socket)
	{
		return NetOptErrorCode::NET_OPT_ERROR;
	}
	int ret = socket->Send(buf, len);
	return ret;
}

int net_recv(socket_handle handle, void* buf, int len)
{
    BaseSocket* socket = FindBaseSocket(handle);
	if (!socket)
		return NetOptErrorCode::NET_OPT_ERROR;
	int ret = socket->Recv(buf, len);
	return ret;
}

int net_close(socket_handle handle)
{
    BaseSocket* socket = FindBaseSocket(handle);
	if (!socket)
	{
		return NetOptErrorCode::NET_OPT_ERROR;
	}
	int ret = socket->Close();
	return ret;
}

int net_option(socket_handle handle, NetOptType opt, void* optval)
{
    BaseSocket* socket = FindBaseSocket(handle);
	if (!socket)
	{
		return NetOptErrorCode::NET_OPT_ERROR;
	}
	switch (opt)
	{
	case OPT_SET_CALLBACK_FUN:
		 socket->SetCallback((callback_fun)optval);
		 break;
	case OPT_SET_CALLBACK_DATA:
		 socket->SetCallbackData(optval);
		 break;
	case OPT_GET_REMOTE_IP:
		*(string*)optval = socket->GetRemoteIP();
		break;
	case OPT_GET_REMOTE_PORT:
		*(uint16_t*)optval = socket->GetRemotePort();
		break;
	case OPT_GET_LOCAL_IP:
		*(string*)optval = socket->GetLocalIP();
		break;
	case OPT_GET_LOCAL_PORT:
		*(uint16_t*)optval = socket->GetLocalPort();
		break;
	case OPT_SET_SEND_BUF_SIZE:
		socket->SetSendBufSize(*(uint32_t*)optval);
		break;
	case OPT_SET_RECV_BUF_SIZE:
		socket->SetRecvBufSize(*(uint32_t*)optval);
		break;
	}
	return NetOptErrorCode::NET_OPT_OK;
}

int net_register_timer(callback_fun callback, void* user_data, uint64_t interval)
{
    EventDispatchMgr::Instance()->AddTimer(callback, user_data, interval);
	return NetOptErrorCode::NET_OPT_OK;
}

int net_delete_timer(callback_fun callback, void* user_data)
{
    EventDispatchMgr::Instance()->RemoveTimer(callback, user_data);
	return NetOptErrorCode::NET_OPT_OK;
}

int net_add_loop(callback_fun callback, void* user_data)
{
    EventDispatchMgr::Instance()->AddLoop(callback, user_data);
	return NetOptErrorCode::NET_OPT_OK;
}

void net_eventloop(uint32_t timeout)
{
    EventDispatchMgr::Instance()->StartDispatch(timeout);
}

void net_stop_event()
{
    EventDispatchMgr::Instance()->StopDispatch();
}

bool net_is_running()
{
    return EventDispatchMgr::Instance()->IsRunning();
}

void net_set_running()
{
    EventDispatchMgr::Instance()->SetRunning();
}
}