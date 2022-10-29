/*
 * @Author: bohan.lj
 * @Date: 2022-10-29 20:12:10
 * @FilePath: /Bohan/bohan/net/EventDispatch.cc
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-29 22:58:58
 * @Description: srouce_code
 */
#include "BEventDispatch.h"

#define TIMER_DURATION	100	// 100 miliseconds

uint64_t get_current_tick()
{
#ifdef _MSC_VER
	LARGE_INTEGER liCounter; 
	LARGE_INTEGER liCurrent;
	if (!QueryPerformanceFrequency(&liCounter))
		return GetTickCount();

	QueryPerformanceCounter(&liCurrent);
	return (uint64_t)(liCurrent.QuadPart * 1000 / liCounter.QuadPart);
#else
	struct timeval tval;
	uint64_t current_tick;

	gettimeofday(&tval, NULL);

	current_tick = tval.tv_sec * 1000L + tval.tv_usec / 1000L;
	return current_tick;
#endif
}

namespace bohan{
EventDispatch::EventDispatch()
{
    is_running = false;
#ifdef _WIN32
	FD_ZERO(&m_read_set);
	FD_ZERO(&m_write_set);
	FD_ZERO(&m_excep_set);
#elif __APPLE__
	m_kqfd = kqueue();
	if (m_kqfd == -1)
	{
		printf("kqueue failed");
	}
#else
	m_epfd = epoll_create(1024);
	if (m_epfd == -1)
	{
		printf("epoll_create failed");
	}
#endif
}

EventDispatch::~EventDispatch()
{
#ifdef _WIN32
#elif __APPLE__
	close(m_kqfd);
#else
	close(m_epfd);
#endif
}
void EventDispatch::AddEvent(socket_handle fd, uint8_t socket_event)
{
    std::lock_guard<mutex> lock{m_mutex};
#ifdef _WIN32
    if ((socket_event & SOCKET_READ) != 0)
	{
		FD_SET(fd, &m_read_set);
	}
	if ((socket_event & SOCKET_WRITE) != 0)
	{
		FD_SET(fd, &m_write_set);
	}
	if ((socket_event & SOCKET_EXCEP) != 0)
	{
		FD_SET(fd, &m_excep_set);
	}
#elif __APPLE__
    struct kevent ke;
	if ((socket_event & SOCKET_READ) != 0)
	{
		EV_SET(&ke, fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
		kevent(m_kqfd, &ke, 1, NULL, 0, NULL);
	}

	if ((socket_event & SOCKET_WRITE) != 0)
	{
		EV_SET(&ke, fd, EVFILT_WRITE, EV_ADD, 0, 0, NULL);
		kevent(m_kqfd, &ke, 1, NULL, 0, NULL);
	}
#else
    struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLOUT | EPOLLET | EPOLLPRI | EPOLLERR | EPOLLHUP;
	ev.data.fd = fd;
	if (epoll_ctl(m_epfd, EPOLL_CTL_ADD, fd, &ev) != 0)
	{
		printf("epoll_ctl() failed, errno=%d", errno);
	}
#endif
}
void EventDispatch::RemoveEvent(socket_handle fd, uint8_t socket_event)
{
    std::lock_guard<mutex> lock{m_mutex};
#ifdef _WIN32
    if ((socket_event & SOCKET_READ) != 0)
	{
		FD_CLR(fd, &m_read_set);
	}

	if ((socket_event & SOCKET_WRITE) != 0)
	{
		FD_CLR(fd, &m_write_set);
	}

	if ((socket_event & SOCKET_EXCEP) != 0)
	{
		FD_CLR(fd, &m_excep_set);
	}
#elif __APPLE__
    struct kevent ke;
	if ((socket_event & SOCKET_READ) != 0)
	{
		EV_SET(&ke, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
		kevent(m_kqfd, &ke, 1, NULL, 0, NULL);
	}
	if ((socket_event & SOCKET_WRITE) != 0)
	{
		EV_SET(&ke, fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
		kevent(m_kqfd, &ke, 1, NULL, 0, NULL);
	}
#else
    if (epoll_ctl(m_epfd, EPOLL_CTL_DEL, fd, NULL) != 0)
	{
		printf("epoll_ctl failed, errno=%d", errno);
	}
#endif
}

void EventDispatch::AddTimer(callback_fun callback, void* user_data, uint64_t interval)
{
    for(auto &item : m_timer_list)
    {
        if(item->callback == callback && item->user_data == user_data)
        {
            item->interval = interval;
            item->next_tick = get_current_tick() + interval;
            return;
        }
    }

    NetEventItem *event = new NetEventItem;
    event->callback = callback;
	event->user_data = user_data;
	event->interval = interval;
	event->next_tick = get_current_tick() + interval;
    event->event_type = NetEvent::NET_TIMER;
	m_timer_list.push_back(event);

}
void EventDispatch::RemoveTimer(callback_fun callback, void* user_data)
{
    for(auto &item : m_timer_list)
    {
        if(item->callback == callback && item->user_data == user_data)
        {
            m_timer_list.erase(item);
            break;
        }
    }
}
    
void EventDispatch::AddLoop(callback_fun callback, void* user_data)
{
    NetEventItem* event = new NetEventItem;
    event->callback = callback;
    event->user_data = user_data;
    event->event_type = NetEvent::NET_LOOP;
    m_loop_list.push_back(event);
}


void EventDispatch::CheckTimer()
{
    uint64_t curr_tick = get_current_tick();
	for (auto &item : m_timer_list)
	{
		if (curr_tick >= item->next_tick)
		{
			item->next_tick += item->interval;
			item->callback(item->user_data, item->event_type, 0, NULL);
		}
	}
}
void EventDispatch::CheckLoop()
{
    for(auto &item : m_loop_list)
	{
		item->callback(item->user_data, item->event_type, 0, NULL);
	}
}
void EventDispatch::StartDispatch(uint32_t wait_timeout)
{
#ifdef _WIN32
    fd_set read_set, write_set, excep_set;
	timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = wait_timeout * 1000;	// 10 millisecond

    if(is_running)
        return;
    is_running = true;
    
    while (is_running)
	{
		CheckTimer();
        CheckLoop();

		if (!m_read_set.fd_count && !m_write_set.fd_count && !m_excep_set.fd_count)
		{
			Sleep(TIMER_DURATION);
			continue;
		}

		m_mutex.lock();
		memcpy(&read_set, &m_read_set, sizeof(fd_set));
		memcpy(&write_set, &m_write_set, sizeof(fd_set));
		memcpy(&excep_set, &m_excep_set, sizeof(fd_set));
		m_mutex.unlock();

		int nfds = select(0, &read_set, &write_set, &excep_set, &timeout);

		if (nfds == SOCKET_ERROR)
		{
			printf("select failed, error code: %d", GetLastError());
			Sleep(TIMER_DURATION);
			continue;
		}

		if (nfds == 0)
		{
			continue;
		}

		for (u_int i = 0; i < read_set.fd_count; i++)
		{
			socket_handle fd = read_set.fd_array[i];
			BaseSocket* socket = FindBaseSocket(socket_handle);
			if (socket)
			{
				socket->OnRead();
			}
		}

		for (u_int i = 0; i < write_set.fd_count; i++)
		{
			socket_handle fd = write_set.fd_array[i];
			BaseSocket* socket = FindBaseSocket(fd);
			if (socket)
			{
				socket->OnWrite();
			}
		}

		for (u_int i = 0; i < excep_set.fd_count; i++)
		{
			socket_handle fd = excep_set.fd_array[i];
			CBaseSocket* socket = FindBaseSocket(fd);
			if (socket)
			{
				socket->OnClose();
			}
		}
	}
#elif __APPLE__
    struct kevent events[1024];
	int nfds = 0;
	struct timespec timeout;
	timeout.tv_sec = 0;
	timeout.tv_nsec = wait_timeout * 1000000;

    if(is_running)
        return;
    is_running = true;
    
    while (running)
	{
		nfds = kevent(m_kqfd, NULL, 0, events, 1024, &timeout);
		for (int i = 0; i < nfds; i++)
		{
			socket_handle ev_fd = events[i].ident;
			BaseSocket* socket = FindBaseSocket(ev_fd);
			if (!socket)
				continue;

			if (events[i].filter == EVFILT_READ)
			{
				socket->OnRead();
			}

			if (events[i].filter == EVFILT_WRITE)
			{
				socket->OnWrite();
			}
		}
		CheckTimer();
        CheckLoop();
	}
#else
    struct epoll_event events[1024];
	int nfds = 0;

    if(is_running)
        return;
    is_running = true;
    
	while (running)
	{
		nfds = epoll_wait(m_epfd, events, 1024, wait_timeout);
		for (int i = 0; i < nfds; i++)
		{
			socket_handle ev_fd = events[i].data.fd;
			BaseSocket* socket = FindBaseSocket(ev_fd);
			if (!socket)
				continue;
            
            #ifdef EPOLLRDHUP
            if (events[i].events & EPOLLRDHUP)
            {
                socket->OnClose();
            }
            #endif

			if (events[i].events & EPOLLIN)
			{
				socket->OnRead();
			}

			if (events[i].events & EPOLLOUT)
			{
				socket->OnWrite();
			}

			if (events[i].events & (EPOLLPRI | EPOLLERR | EPOLLHUP))
			{
				socket->OnClose();
			}
		}
		CheckTimer();
        CheckLoop();
	}
#endif
}
void EventDispatch::StopDispatch()
{
    is_running = false;
} 
}