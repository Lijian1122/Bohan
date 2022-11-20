/*
 * @Author: bohan.lj
 * @Date: 2022-11-20 18:40:08
 * @FilePath: /Bohan/bohan/net/NetCoreLib.cpp
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-11-20 20:12:56
 * @Description: srouce_code
 */
#include "NetCoreLib.h"
#include "NetOperation.h"

namespace bohan{
NetCoreLib *NetCoreLib::Instance()
{
    static NetCoreLib  instance;
    return &instance;
}

bool NetCoreLib::startNetEvent()
{
    //启动任务队列线程
    //....

    //启动io复用监听循环
    if(!net_is_running())
    { 
      m_eventLoop_thread = std::thread(&NetCoreLib::runEventLoop, this);
      m_eventLoop_thread.detach();
    }
    return true;
}

void NetCoreLib::stopNetEvent()
{
    if(net_is_running())
    {
        net_stop_event();
        if(m_eventLoop_thread.joinable())
             m_eventLoop_thread.join(); 
        net_destroy();
    }
  
}

void NetCoreLib::runEventLoop()
{
    net_init();
	net_eventloop();
}

socket_handle NetCoreLib::connect(std::string server_ip, uint32_t server_port)
{
    ConnectionPtr conn = std::make_shared<Connection>();
    socket_handle handle = conn->Connect(server_ip.c_str(), server_port);
	if (handle != INVALID_SOCKET_HANDLE)
	{
		m_ConnPtr_map[handle] = conn;
	}
	return handle;
}
ConnectionPtr NetCoreLib::getConn(socket_handle handle)
{
    for(auto &it : m_ConnPtr_map)
    {
        if(it.first == handle)
        {
            return it.second;
        }
    } 
    return nullptr;
}
void NetCoreLib::unRegisterCallback(socket_handle handle)
{
    ConnectionPtr conn = getConn(handle);
    if(conn.get())
    {
        conn->UnRegisterCallback();

        m_ConnPtr_map.erase(handle);
    }
    
}
void NetCoreLib::registerCallback(socket_handle handle,TcpSocketCallback* callback)
{
    ConnectionPtr conn = getConn(handle);
    if(conn.get())
    {
        conn->RegisterCallback(callback);
    }
}
}