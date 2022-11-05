/*
 * @Author: bohan.lj
 * @Date: 2022-10-30 23:12:56
 * @FilePath: /Bohan/bohan/net/Connection.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-11-05 22:58:25
 * @Description: srouce_code
 */

#ifndef BOHAN_NET_CONNECTION_H
#define BOHAN_NET_CONNECTION_H

#include "BaseSocket.h"
#include "SimpleBuffer.h"
#include "EventDispatch.h"
#include "Util.h"
#include <memory>
#include <iostream>
#include <hash_map>
#include <map>

#define READ_BUF_SIZE	2048

namespace bohan{

class Connection
{
public:
    Connection();
    virtual ~Connection();

    virtual int Send(void *data ,int size);
    virtual void OnConnect(socket_handle handle){m_handle = handle;}
    virtual void OnRead();
    virtual void OnWrite();
    virtual void OnClose();
    virtual void OnTimer(uint64_t curTime);
    virtual void OnRevice(void *data ,int size);
private:
    socket_handle m_handle;

    SimpleBuffer	m_recv_buf;
	SimpleBuffer	m_send_buf;
    uint32_t        m_reve_size;

    uint64_t		m_last_send_tick;
	uint64_t		m_last_recv_tick;
    bool            is_sending;
};

typedef std::shared_ptr<Connection> ConnectionPtr;
typedef hash_map<socket_handle, ConnectionPtr> ConnMap_t;

void conn_callback(void* callback_data, NetEvent event, socket_handle handle, void* pParam);
}
#endif