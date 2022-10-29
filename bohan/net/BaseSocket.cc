/*
 * @Author: bohan.lj
 * @Date: 2022-10-29 18:25:22
 * @FilePath: /Bohan/bohan/net/BaseSocket.cc
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-29 21:40:56
 * @Description: srouce_code
 */
#include "BaseSocket.h"
#include "assert.h"
#include "BEventDispatch.h"

namespace bohan
{

typedef Hash_Map<socket_handle,BaseSocket*> socket_map;
socket_map g_socket_map;

void AddBaseSocket(BaseSocket* socket)
{
    assert(!socket);
	g_socket_map.emplace(socket->GetSocketHandle(),socket);
}

void RemoveBaseSocket(BaseSocket* socket)
{
    assert(!socket);
	g_socket_map.erase(socket->GetSocketHandle());
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
	//CEventDispatch::Instance()->AddEvent(m_socket, SOCKET_READ | SOCKET_EXCEP);
    EventDispatchMgr->Instance()->AddEvent(m_socket, SOCKET_READ | SOCKET_EXCEP);
	return SocketError::NO_ERROR;
}
socket_handle BaseSocket::Connect(const char *server_ip, uint32_t port,callback_fun	callback,void *callback_data)
{

}
int BaseSocket::Send(void* buf, int len)
{

}
int BaseSocket::Recv(void* buf, int len)
{

}
int BaseSocket::Close()
{

}

void BaseSocket::OnRead()
{

}
void BaseSocket::OnWrite()
{

}

void BaseSocket::OnClose()
{

}

bool BaseSocket::Shutdown(SOCKET_SHUTDOWN type)
{
    
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

}
}