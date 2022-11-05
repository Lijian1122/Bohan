/*
 * @Author: bohan.lj
 * @Date: 2022-10-29 18:24:21
 * @FilePath: /Bohan/bohan/net/BaseSocket.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-11-05 22:48:32
 * @Description: base socket
 */

#ifndef BOHAN_NET_BASE_SOCKET_H
#define BOHAN_NET_BASE_SOCKET_H
#include "os_type.h"
#include "HashMap.h"

#define SOCKET_MAX_BUF_SIZE		(128 * 1024)

typedef int socket_handle;

enum SocketState{
    IDLE = 0,
    LISTENING,
    CONNECTING,
    CONNECTED,
    CLOSING
};

enum SocketShutdown{
    RECIVE = 0,
    SEND,
    RECIVE_SNED
};

enum SocketError{
	NO_ERROR		= 0,
	CREAET_ERROR	= 1,
    BIND_ERROR	= 2,
    LISTEN_ERROR = 3,
    SEND_ERROR
};

typedef void (*callback_fun)(void* data, uint8_t msg, uint32_t handle, void* param);

namespace bohan
{
class BaseSocket
{
public:
    BaseSocket();
    virtual ~BaseSocket();

    socket_handle GetSocketHandle() { return m_socket; }
	void SetSocketHandle(socket_handle hd) { m_socket = hd; }
	void SetState(SocketState state) { m_state = state; }

	void SetCallback(callback_fun callback) { m_callback = callback; }
	void SetCallbackData(void* data) { m_callback_data = data; }
	void SetRemoteIP(const char* ip) { m_remote_ip = ip; }
	void SetRemotePort(uint32_t port) { m_remote_port = port; }
	void SetSendBufSize(uint32_t send_size);
	void SetRecvBufSize(uint32_t recv_size);

	const char*	GetRemoteIP() { return m_remote_ip.c_str(); }
	uint32_t	GetRemotePort() { return m_remote_port; }
	const char*	GetLocalIP() { return m_local_ip.c_str(); }
	uint32_t	GetLocalPort() { return m_local_port; }
    
public:
    SocketError Listen(const char*	server_ip, uint32_t port, callback_fun callback,void *callback_data);
	socket_handle Connect(const char *server_ip, uint32_t port,callback_fun	callback,void *callback_data);
    int Send(void* buf, int len);
	int Recv(void* buf, int len);
	int Close();

    void OnRead();
	void OnWrite();
	void OnClose();
	bool Shutdown(SocketShutdown type);

private:
    int  GetErrorCode();
	bool IsBlock(int error_code);
	void SetNonblock(socket_handle fd);
	void SetReuseAddr(socket_handle fd);
	void SetNoDelay(socket_handle fd);
	void SetAddr(const char* ip, const uint32_t port, sockaddr_in* pAddr);
	void AcceptNewSocket();

private:
    std::string m_remote_ip;
    uint32_t m_remote_port;
    std::string m_local_ip;
    uint32_t m_local_port;
   
    callback_fun m_callback;
    void *m_callback_data;

    socket_handle m_socket;
    SocketState m_state;
};

BaseSocket* FindBaseSocket(socket_handle sh);
}
#endif
