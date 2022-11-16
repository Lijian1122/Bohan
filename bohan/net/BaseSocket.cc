/*
 * @Author: bohan.lj
 * @Date: 2022-10-29 18:25:22
 * @FilePath: /Bohan/bohan/net/BaseSocket.cc
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-11-16 22:48:21
 * @Description: srouce_code
 */
#include "BaseSocket.h"
#include "assert.h"
#include "EventDispatch.h"
#include <memory.h>
#include "HashMap.h"

namespace bohan
{
	
Hash_Map<socket_handle,BaseSocket*> g_socket_map;

void AddBaseSocket(BaseSocket* socket)
{
	if(socket)
	{
		g_socket_map.emplace(socket->GetSocketHandle(),socket);
	}
}

void RemoveBaseSocket(BaseSocket* socket)
{
    if(socket)
	{
		g_socket_map.erase(socket->GetSocketHandle());
	}	
}

BaseSocket* FindBaseSocket(socket_handle sh)
{
	BaseSocket* socket = nullptr;
    g_socket_map.getvalue(sh,socket);
    return socket;
}

//base socket
BaseSocket::BaseSocket()
   :m_socket(INVALID_SOCKET),
    m_state(SocketState::IDLE)
{

}
BaseSocket::~BaseSocket()
{
    
}

SocketError BaseSocket::Listen(const char*	server_ip, uint32_t port, callback_fun callback,void *callback_data)
{
    m_local_ip = server_ip;
	m_local_port = port;
	m_callback = callback;
	m_callback_data = callback_data;

	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
		printf("socket create failed, err_code=%d\n", GetErrorCode());
		return SocketError::CREAET_ERROR;
	}

	SetReuseAddr(m_socket);
	SetNonblock(m_socket);

	sockaddr_in serv_addr;
	SetAddr(server_ip, port, &serv_addr);
    int ret = ::bind(m_socket, (sockaddr*)&serv_addr, sizeof(serv_addr));
	if (ret == SOCKET_ERROR)
	{
        printf("bind failed, err_code=%d\n", GetErrorCode());
		closesocket(m_socket);
		return SocketError::BIND_ERROR;
	}

	ret = listen(m_socket, 64);
	if (ret == SOCKET_ERROR)
	{
        printf("listen failed, err_code=%d\n",GetErrorCode());
		closesocket(m_socket);
		return SocketError::LISTEN_ERROR;
	}

	m_state = SocketState::LISTENING;

	AddBaseSocket(this);
    EventDispatchMgr::Instance()->AddEvent(m_socket, SocketEvent::SOCKET_READ | SocketEvent::SOCKET_EXCEP);
	return SocketError::NO_ERROR;
}
socket_handle BaseSocket::Connect(const char *server_ip, uint32_t port,callback_fun	callback,void *callback_data)
{
    printf("CBaseSocket::Connect, server_ip=%s, port=%d", server_ip, port);
	m_remote_ip = server_ip;
	m_remote_port = port;
	m_callback = callback;
	m_callback_data = callback_data;

	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
		printf("socket failed, err_code=%d", GetErrorCode());
		return INVALID_SOCKET_HANDLE;
	}

	SetNonblock(m_socket);
	SetNoDelay(m_socket);
	sockaddr_in serv_addr;
	SetAddr(server_ip, port, &serv_addr);
	int ret = connect(m_socket, (sockaddr*)&serv_addr, sizeof(serv_addr));
	if ((ret == SOCKET_ERROR) && (!IsBlock(GetErrorCode())))
	{	
		printf("connect failed, err_code=%d", GetErrorCode());
		closesocket(m_socket);
		return INVALID_SOCKET_HANDLE;
	}
	m_state = SocketState::CONNECTING;
	AddBaseSocket(this);
	EventDispatchMgr::Instance()->AddEvent(m_socket, SocketEvent::SOCKET_ALL);
	return m_socket;
}
int BaseSocket::Send(void* buf, int len)
{
    if (m_state != SocketState::CONNECTED)
		return SocketError::SEND_ERROR;

	int ret = send(m_socket, (char*)buf, len, 0);
	if (ret == SOCKET_ERROR)
	{
		int err_code = GetErrorCode();
		if (IsBlock(err_code))
		{
#if ((defined _WIN32) || (defined __APPLE__))
			EventDispatchMgr::Instance()->AddEvent(m_socket, SocketEvent::SOCKET_WRITE);
#endif
			ret = 0;
		}
		else
		{
			printf("!!!send failed, error code: %d", err_code);
		}
	}
	return ret;
}
int BaseSocket::Recv(void* buf, int len)
{
    return recv(m_socket, (char*)buf, len, 0);
}

int BaseSocket::Close()
{
    EventDispatchMgr::Instance()->RemoveEvent(m_socket, SocketEvent::SOCKET_ALL);
	RemoveBaseSocket(this);
	closesocket(m_socket);
	return 0;
}

void BaseSocket::OnRead()
{
    if (m_state == SocketState::LISTENING)
	{
        AcceptNewSocket();
	}
	else
	{
		u_long avail = 0;
		if ((ioctlsocket(m_socket, FIONREAD, &avail) == SOCKET_ERROR) || (avail == 0) )
		{
			m_callback(m_callback_data, NetEvent::NET_CLOSE, m_socket, NULL);
		}
		else
		{
			m_callback(m_callback_data, NetEvent::NET_READ, m_socket, NULL);
		}
	}
}
void BaseSocket::OnWrite()
{
#if ((defined _MSC_VER) || (defined __APPLE__))
	EventDispatchMgr::Instance()->RemoveEvent(m_socket, SOCKET_WRITE);
#endif
	if (m_state == SocketState::CONNECTING)
	{
		int error = 0;
		socklen_t len = sizeof(error);
#ifdef _MSC_VER
		getsockopt(m_socket, SOL_SOCKET, SO_ERROR, (char*)&error, &len);
#else
		getsockopt(m_socket, SOL_SOCKET, SO_ERROR, (void*)&error, &len);
#endif
		if (error) 
        {
			m_callback(m_callback_data, NetEvent::NET_CLOSE, m_socket, NULL);

		}else 
        {
			m_state = SocketState::CONNECTED;
			m_callback(m_callback_data, NetEvent::NET_CONFIRM, m_socket, NULL);
		}
	}
	else
	{
		m_callback(m_callback_data, NetEvent::NET_WRITE, m_socket, NULL);
	}
}

void BaseSocket::OnClose()
{
    m_state = SocketState::CLOSING;
	m_callback(m_callback_data, NetEvent::NET_CLOSE, m_socket, NULL);
}

bool BaseSocket::Shutdown(SocketShutdown type)
{
    return (0 == shutdown(m_socket, (int)type));
}
void BaseSocket::SetSendBufSize(uint32_t send_size)
{
    int ret = setsockopt(m_socket, SOL_SOCKET, SO_SNDBUF, &send_size, 4);
	if (ret == SOCKET_ERROR) 
    {
		printf("set SO_SNDBUF failed for fd=%d", m_socket);
	}
	socklen_t len = 4;
	int size = 0;
	getsockopt(m_socket, SOL_SOCKET, SO_SNDBUF, &size, &len);
	printf("socket=%d send_buf_size=%d", m_socket, size);
}
void BaseSocket::SetRecvBufSize(uint32_t recv_size)
{
    int ret = setsockopt(m_socket, SOL_SOCKET, SO_RCVBUF, &recv_size, 4);
	if (ret == SOCKET_ERROR) 
    {
		printf("set SO_RCVBUF failed for fd=%d", m_socket);
	}
	socklen_t len = 4;
	int size = 0;
	getsockopt(m_socket, SOL_SOCKET, SO_RCVBUF, &size, &len);
	printf("socket=%d recv_buf_size=%d", m_socket, size);
}

int  BaseSocket::GetErrorCode()
{
#ifdef _WIN32
	return WSAGetLastError();
#else
	return errno;
#endif
}
bool BaseSocket::IsBlock(int error_code)
{
#ifdef _WIN32
	return ((error_code == WSAEINPROGRESS) || (error_code == WSAEWOULDBLOCK) );
#else
	return ((error_code == EINPROGRESS) || (error_code == EWOULDBLOCK));
#endif
}
void BaseSocket::SetNonblock(socket_handle sh)
{
#ifdef _WIN32
	u_long nonblock = 1;
	int ret = ioctlsocket(sh, FIONBIO, &nonblock);
#else
	int ret = fcntl(sh, F_SETFL, O_NONBLOCK | fcntl(sh, F_GETFL));
#endif
	if (ret == SOCKET_ERROR)
	{
		printf("_SetNonblock failed, err_code=%d", GetErrorCode());
	}
}
void BaseSocket::SetReuseAddr(socket_handle sh)
{
    int reuse = 1;
	int ret = setsockopt(sh, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(reuse));
	if (ret == SOCKET_ERROR)
	{
        printf("SetReuseAddr failed,err_code=%d\n",GetErrorCode());
	}
}
void BaseSocket::SetNoDelay(socket_handle sh)
{
    int nodelay = 1;
	int ret = setsockopt(sh, IPPROTO_TCP, TCP_NODELAY, (char*)&nodelay, sizeof(nodelay));
	if (ret == SOCKET_ERROR)
	{
		printf("SetNoDelay failed,err_code=%d\n",GetErrorCode());
	}
}

void BaseSocket::SetAddr(const char* ip, const uint32_t port, sockaddr_in* pAddr)
{
    memset(pAddr, 0, sizeof(sockaddr_in));
	pAddr->sin_family = AF_INET;
	pAddr->sin_port = htons(port);
	pAddr->sin_addr.s_addr = inet_addr(ip);
	if (pAddr->sin_addr.s_addr == INADDR_NONE)
	{
		hostent* host = gethostbyname(ip);
		if (!host)
		{
			printf("gethostbyname failed, ip=%s", ip);
			return;
		}
		pAddr->sin_addr.s_addr = *(uint32_t*)host->h_addr;
	}
}
void BaseSocket::AcceptNewSocket()
{
    printf("BaseSocket::AcceptNewSocket: %s", "OnRead New");
	socket_handle fd = 0;
	sockaddr_in peer_addr;
	socklen_t addr_len = sizeof(sockaddr_in);
	char ip_str[64];
    fd = accept(m_socket, (sockaddr*)&peer_addr, &addr_len);
	while((fd = accept(m_socket, (sockaddr*)&peer_addr, &addr_len)) != INVALID_SOCKET)
	{
		BaseSocket* socket = new BaseSocket();

		uint32_t ip = ntohl(peer_addr.sin_addr.s_addr);
		uint32_t port = ntohs(peer_addr.sin_port);

		snprintf(ip_str, sizeof(ip_str), "%d.%d.%d.%d", ip >> 24, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);

		printf("Accept fd=%d from %s:%d\n", fd, ip_str, port);

		socket->SetSocketHandle(fd);
		socket->SetCallback(m_callback);
		socket->SetCallbackData(m_callback_data);
		socket->SetState(SocketState::CONNECTED);
		socket->SetRemoteIP(ip_str);
		socket->SetRemotePort(port);

		SetNoDelay(fd);
		SetNonblock(fd);
		AddBaseSocket(socket);
		EventDispatchMgr::Instance()->AddEvent(fd, SocketEvent::SOCKET_READ | SocketEvent::SOCKET_EXCEP);
		m_callback(m_callback_data, NetEvent::NET_CONNECT, fd, NULL);       
	}
}
}