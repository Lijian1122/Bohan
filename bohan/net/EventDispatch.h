/*
 * @Author: bohan.lj
 * @Date: 2022-10-29 20:11:36
 * @FilePath: /Bohan/bohan/net/EventDispatch.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-11-20 10:53:32
 * @Description: socket event dispatch
 */

#ifndef BOHAN_EVENT_DISPATCH_H
#define BOHAN_EVENT_DISPATCH_H

#include "Singleton.h"
#include <list>
#include <mutex>
#include <thread>
#include "BaseSocket.h"
#include "Util.h"

enum SocketEvent{
	SOCKET_READ		= 0x1,
	SOCKET_WRITE	= 0x2,
	SOCKET_EXCEP	= 0x4,
	SOCKET_ALL		= 0x7
};

struct NetEventItem{
	callback_fun callback;
	void*		user_data;
	uint64_t	interval;
	uint64_t	next_tick;
	NetEvent    event_type;
};

namespace bohan{

class EventDispatch : Copyable
{
public:
    void AddEvent(socket_handle fd, uint8_t socket_event);
	void RemoveEvent(socket_handle fd, uint8_t socket_event);

	void AddTimer(callback_fun callback, void* user_data, uint64_t interval);
	void RemoveTimer(callback_fun callback, void* user_data);
    
    void AddLoop(callback_fun callback, void* user_data);

	void StartDispatch(uint32_t wait_timeout = 100);
    void StopDispatch();
    
    bool IsRunning() {return is_running;}
	void SetRunning() { is_running = true;}
    ~EventDispatch();
    EventDispatch();
    void CheckTimer();
    void CheckLoop();
private:
#ifdef _WIN32
	fd_set	m_read_set;
	fd_set	m_write_set;
	fd_set	m_excep_set;
#elif __APPLE__
	int 	m_kqfd;
#else
	int		m_epfd;
#endif
	std::mutex			m_mutex;
	std::list<NetEventItem*>	m_timer_list;
	std::list<NetEventItem*>	m_loop_list;
    bool is_running;
};

typedef bohan::Singleton<EventDispatch> EventDispatchMgr;
}

#endif