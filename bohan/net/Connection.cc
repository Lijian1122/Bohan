/*
 * @Author: bohan.lj
 * @Date: 2022-11-05 20:32:00
 * @FilePath: /Bohan/bohan/net/Connection.cc
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-11-19 12:21:36
 * @Description: srouce_code
 */
#include "Connection.h"
#include "NetOperation.h"

namespace bohan
{

static ConnectionPtr FindImConn(ConnMap_t* imconn_map, socket_handle handle)
{
	ConnectionPtr conn;
	ConnMap_t::iterator iter = imconn_map->find(handle);
	if (iter != imconn_map->end())
	{
		conn = iter->second;
	}
	return conn;
}


void conn_callback(void* callback_data, NetEvent event, socket_handle handle, void* pParam)
{
    if (!callback_data)
    {
        return;
    }
	ConnMap_t* conn_map = (ConnMap_t*)callback_data;
	ConnectionPtr conn = FindImConn(conn_map, handle);
	if (!conn.get())
    {
        return;
    }
	switch (event)
	{
	case NetEvent::NET_CONFIRM:
		 //pConn->OnConfirm();
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
}


socket_handle Connection::Connect(const char* server_ip, uint16_t server_port,callback_fun callback,void *callback_data)
{
	m_handle = net_connect(server_ip, server_port,callback,callback_data);
	return m_handle;
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
    // else
    // {
    //     OnWriteCompelete();
    // }
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

		m_reve_size += ret;
		m_recv_buf.IncWriteOffset(ret);
		m_last_recv_tick = get_current_tick();
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