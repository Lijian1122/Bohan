/*
 * @Author: bohan.lj
 * @Date: 2022-10-30 23:12:56
 * @FilePath: /Bohan/bohan/net/Connection.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-12-11 20:08:42
 * @Description: srouce_code
 */

#ifndef BOHAN_NET_CONNECTION_H
#define BOHAN_NET_CONNECTION_H

#include "BaseSocket.h"
#include "SimpleBuffer.h"
#include "EventDispatch.h"
#include "PackageBase.h"
#include "Util.h"
#include <memory>
#include <iostream>
#include <hash_map>
#include <map>

#define READ_BUF_SIZE	2048

#define IS_DEBUG_MODE  1

namespace bohan{


class TcpSocketCallback
{
    public:
      virtual void onConnected() = 0;
      virtual void onClose()  =0;
      virtual void onReceiveData(const char *data, int32_t size) = 0;
      virtual void onReceiveError() = 0;
};

class DLL_EXPORTS Connection
{
public:
    Connection();
    virtual ~Connection();
    virtual socket_handle Connect(const char* server_ip, uint16_t server_port); 
    virtual int SendPackage(PackageBase *package){return Send((void*)package->GetBuffer(),(int)package->GetLength());}
    virtual int Send(void *data ,int size);
    virtual void Close();
    //sever new client
    virtual void OnNewConn(socket_handle handle);
    //client connected
    virtual void OnConnected(); 
    virtual void OnRead();
    virtual void OnWrite();
    virtual void OnClose();
    virtual void OnTimer(uint64_t curTime);
    virtual void OnRevice(void *data ,int size);

    virtual void HandlePackage(const PackageBase* package) {}

    void RegisterCallback(TcpSocketCallback* callback);
	void UnRegisterCallback();
private:
    socket_handle m_handle;

    std::string m_remote_ip;
    uint32_t m_remote_port;

    SimpleBuffer	m_recv_buf;
	SimpleBuffer	m_send_buf;
    uint32_t        m_reve_size;

    uint64_t		m_last_send_tick;
	uint64_t		m_last_recv_tick;
    bool            is_sending;
    TcpSocketCallback *m_tcpcallback;
};

typedef std::shared_ptr<Connection> ConnectionPtr;
typedef hash_map<socket_handle, Connection*> ConnMap_t;
typedef hash_map<socket_handle, ConnectionPtr> ConnPtrMap_t;


void conn_callback(void* callback_data, NetEvent event, socket_handle handle, void* pParam);

Connection *FindImConn(ConnMap_t* imconn_map, socket_handle handle);
}
#endif