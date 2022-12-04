/*
 * @Author: bohan.lj
 * @Date: 2022-11-05 20:32:00
 * @FilePath: /Bohan/bohan/net/Connection.cc
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-12-04 22:42:59
 * @Description: srouce_code
 */
#include "Connection.h"
#include "NetOperation.h"

namespace bohan
{

static ConnMap_t g_conn_map;

Connection *FindImConn(ConnMap_t* imconn_map, socket_handle handle)
{
	Connection *conn;
	ConnMap_t::iterator iter = imconn_map->find(handle);
	if (iter != imconn_map->end())
	{
		conn = iter->second;
	}
	return conn;
}

bool send = true;
bool is_server  =true;
void conn_callback(void* callback_data, NetEvent event, socket_handle handle, void* pParam)
{
    if (!callback_data)
    {
        return;
    }
	ConnMap_t* conn_map = (ConnMap_t*)callback_data;
	Connection *conn = FindImConn(conn_map, handle);

	printf("msg=%d, handle=%d\n", event, handle);
	std::string data;

	if (!conn)
    {
        return;
    }
	switch (event)
	{
	case NetEvent::NET_CONFIRM:
		 conn->OnConnected();
		 break;
	case NetEvent::NET_READ:
		 conn->OnRead();
		 break;
	case NetEvent::NET_WRITE:
		 conn->OnWrite();
		 break;
	case NetEvent::NET_CLOSE:
		 conn->OnClose();
		 break;
	default:
		break;
	}
}

Connection::Connection()
{
    m_handle = INVALID_SOCKET;
    m_reve_size = 0;
    is_sending = false;
    m_last_send_tick = m_last_recv_tick = get_current_tick();
	m_tcpcallback = nullptr;
}


socket_handle Connection::Connect(const char* server_ip, uint16_t server_port)
{
	is_server = false;
	m_handle = net_connect(server_ip, server_port,conn_callback,(void*)&g_conn_map);
	g_conn_map.insert(make_pair(m_handle, this));
	net_option(m_handle, OPT_GET_REMOTE_IP, (void*)&m_remote_ip);
	net_option(m_handle, OPT_GET_REMOTE_PORT, (void*)&m_remote_port);
	return m_handle;
}
void Connection::OnNewConn(socket_handle handle)
{
	m_handle = handle;
	g_conn_map.insert(make_pair(handle, this));
    
	net_option(handle, OPT_SET_CALLBACK_FUN, (void*)conn_callback);
	net_option(handle, OPT_SET_CALLBACK_DATA, (void*)&g_conn_map);
	net_option(handle, OPT_GET_REMOTE_IP, (void*)&m_remote_ip);
	net_option(handle, OPT_GET_REMOTE_PORT, (void*)&m_remote_port);
	printf("connect from %s:%d, handle=%d\n", m_remote_ip.c_str(), m_remote_port, m_handle);
}

void Connection::OnConnected()
{
    printf("connect to login server success handle=%d\n",  m_handle);
	if(m_tcpcallback)
	{
		m_tcpcallback->onConnected();
	}
	//test
	if(IS_DEBUG_MODE)
	{
		if(send && !is_server)
		{
			std::string data = "Hello server, I m client!!!";
		    Send((void*)data.c_str(),data.size());
			send = false;
		}
	}
}

void Connection::Close()
{
	if (m_handle != INVALID_SOCKET) {
		net_close(m_handle);
		g_conn_map.erase(m_handle);
		m_handle = INVALID_SOCKET;
	}
	if (m_tcpcallback)
		m_tcpcallback->onClose();
}

int Connection::Send(void *data ,int size)
{
    m_last_send_tick = get_current_tick();
	if (is_sending)
	{
		m_send_buf.Write(data, size);
		return size;
	}

	int offset = 0;
	int remain = size;
	while (remain > 0) 
    {
		int send_size = remain;
		if (send_size > SOCKET_MAX_BUF_SIZE) 
        {
			send_size = SOCKET_MAX_BUF_SIZE;
		}

		int ret = net_send(m_handle, (char*)data + offset , send_size);
		if (ret <= 0) 
        {
			ret = 0;
			break;
		}

		offset += ret;
		remain -= ret;
	}

	if (remain > 0)
	{
		m_send_buf.Write((char*)data + offset, remain);
		is_sending = true;
	}
	return size;
}
void Connection::OnRead()
{
    for (;;)
    {
          uint32_t free_buf_len = m_recv_buf.GetAllocSize() - m_recv_buf.GetWriteOffset();
	if (free_buf_len < READ_BUF_SIZE)
          {
              m_recv_buf.ReSizeBuffer(READ_BUF_SIZE);
          }
	int ret = net_recv(m_handle, m_recv_buf.GetBuffer() + m_recv_buf.GetWriteOffset(), READ_BUF_SIZE);
	if (ret <= 0)
	    break;

	m_recv_buf.IncWriteOffset(ret);
	m_last_recv_tick = get_current_tick();
	// std::string data((char*)m_recv_buf.GetBuffer());
	// printf("OnRead ReciveData=%s\n", data.c_str());
	// if(m_tcpcallback)
	// 	m_tcpcallback->onReceiveData((const char*)m_recv_buf.GetBuffer(),ret);

	// m_recv_buf.Read(NULL, ret);

          //test
	// if(IS_DEBUG_MODE)
	// {
	// 	if(send && is_server)
	// 	{
	// 	   data = "Hello clent, I m server!!!";
	// 	   Send((void*)data.c_str(),data.size());
	// 	   send = false;
	// 	}
	// }	
   }
   
   PackageBase *package = nullptr;
   try
   {
	while((package = PackageBase::ReadPackage(m_recv_buf.GetBuffer(), m_recv_buf.GetWriteOffset())))
	{
             uint32_t len = package->GetLength();
	   //处理业务逻辑
             HandlePackage(package);
             m_recv_buf.Read(NULL, len);
	   delete package;
             package = nullptr;
	}
   }
   catch(PackageException &ex)
   {
        printf("OnRead catch exception, sid=%u, cid=%u, err_code=%u, err_msg=%s, close the connection ", ex.GetServiceId(), ex.GetCommandId(), ex.GetErrorCode(), ex.GetErrorMsg());
        if (package) 
        {
            delete package;
            package = NULL;
        }
        OnClose();
   }
}
void Connection::OnWrite()
{
    if (!is_sending)
		return;

	while (m_send_buf.GetWriteOffset() > 0) 
    {
		int send_size = m_send_buf.GetWriteOffset();
		if (send_size > SOCKET_MAX_BUF_SIZE)
        {
			send_size = SOCKET_MAX_BUF_SIZE;
		}

		int ret = net_send(m_handle, m_send_buf.GetBuffer(), send_size);
		if (ret <= 0) 
        {
			ret = 0;
			break;
		}
		m_send_buf.Read(NULL, ret);
	}

	if (m_send_buf.GetWriteOffset() == 0) 
    {
		is_sending = false;
	}
}

void Connection::OnClose()
{
	printf("close connction handle=%d\n",  m_handle);
	if (m_handle != INVALID_SOCKET) {
		net_close(m_handle);
		g_conn_map.erase(m_handle);
		m_handle = INVALID_SOCKET;
		printf("close connction success\n");
	}
}

void Connection::RegisterCallback(TcpSocketCallback* callback)
{
	m_tcpcallback = callback;
}
void Connection::UnRegisterCallback()
{
	m_tcpcallback = nullptr;
}

void Connection::OnTimer(uint64_t curTime)
{

}
void Connection::OnRevice(void *data ,int size)
{

}
Connection::~Connection()
{

}
}