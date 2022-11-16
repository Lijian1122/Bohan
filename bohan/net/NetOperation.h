/*
 * @Author: bohan.lj
 * @Date: 2022-10-30 21:56:49
 * @FilePath: /Bohan/bohan/net/NetOperation.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-11-10 08:53:01
 * @Description: net operation
 */

#ifndef BOHAN_NET_NET_OPERATION_H
#define BOHAN_NET_NET_OPERATION_H

#include "BaseSocket.h"
#include "EventDispatch.h"

enum NetOptErrorCode{
	NET_OPT_OK		= 0,
	NET_OPT_ERROR	= -1
};

enum NetOptType{
	OPT_SET_CALLBACK_FUN = 0,
	OPT_SET_CALLBACK_DATA,
    OPT_GET_REMOTE_IP,
    OPT_GET_REMOTE_PORT,
    OPT_GET_LOCAL_IP,
    OPT_GET_LOCAL_PORT,
    OPT_SET_SEND_BUF_SIZE,
    OPT_SET_RECV_BUF_SIZE
};

namespace bohan
{
#ifdef __cplusplus
extern "C" {
#endif

NetOptErrorCode net_init();

NetOptErrorCode net_destroy();

NetOptErrorCode net_listen(const char *server_ip, uint32_t	port, callback_fun	callback, void*	callback_data);

socket_handle net_connect(const char*	server_ip,uint16_t port,callback_fun callback,void *callback_data);

int net_send(socket_handle handle, void* buf, int len);

int net_recv(socket_handle handle, void* buf, int len);

int net_close(socket_handle handle);

int net_option(socket_handle handle, NetOptType opt, void* optval);

int net_register_timer(callback_fun callback, void* user_data, uint64_t interval);

int net_delete_timer(callback_fun callback, void* user_data);

int net_add_loop(callback_fun callback, void* user_data);

void net_eventloop(uint32_t timeout = 100);

void net_stop_event();

bool net_is_running();

void net_set_running();

#ifdef __cplusplus
}
#endif
}

#endif