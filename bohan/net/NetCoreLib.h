/*
 * @Author: bohan.lj
 * @Date: 2022-11-20 18:36:34
 * @FilePath: /Bohan/bohan/net/NetCoreLib.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-12-11 20:09:02
 * @Description: srouce_code
 */


#ifndef BOHAN_NET_TCPSOCKETMANAGER_H
#define BOHAN_NET_TCPSOCKETMANAGER_H

#include "Connection.h"
#include "base/Copyable.h"
#include "BaseSocket.h"
#include <memory>

namespace bohan{
    class DLL_EXPORTS NetCoreLib : public Copyable
    {
    public:
       static NetCoreLib *Instance();
       bool startNetEvent();
       void stopNetEvent();
       socket_handle connect(std::string server_ip, uint32_t server_port);
       ConnectionPtr getConn(socket_handle handle);
       void registerCallback(socket_handle handle,TcpSocketCallback* callback);
       void unRegisterCallback(socket_handle handle);
    private:
        NetCoreLib(){};
        virtual ~NetCoreLib(){};
        void runEventLoop();
    private:
        ConnPtrMap_t m_ConnPtr_map;
        std::thread m_eventLoop_thread;
    }; 
}
#endif