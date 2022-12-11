/*
 * @Author: bohan.lj
 * @Date: 2022-10-07 22:16:16
 * @FilePath: /Bohan/bohan/base/ThreadPool.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-12-11 20:05:27
 * @Description: 有关线程池实现
 */

#ifndef BOHAN_BASE_THREADPOOL_H
#define BOHAN_BASE_THREADPOOL_H

#include "os_type.h"
#include <thread>
#include <functional>
#include <atomic>
#include <list>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include "Lock.h"
#include "Copyable.h"
#include "assert.h"

#define THREADPOOL_MAX_NUM 64;
typedef std::function<void()>  ThreadTask;

namespace bohan{
class DLL_EXPORTS ThreadPool : Copyable
{

public:
    ThreadPool(uint64_t threadNum = 4)
    {
        m_stop = false;
        addThread(threadNum); 
    }
    ~ThreadPool()
    {
        stop();
    }
    void stop()
    {
        m_stop=true;
	    m_condition.notify_all();
	    for (thread& thread : m_threads) 
        {
		    if(thread.joinable())
			    thread.join(); 
	    };
    }

    template<class F, class... Args>
	void addTask(F&& f, Args&&... args)
    {
        if (m_stop)
	    {
		    return;
	    }
	    using return_type = typename std::result_of_t<F(Args...)>;
	    auto task = make_shared<packaged_task<return_type()>>(
			bind(forward<F>(f), forward<Args>(args)...)
		);
	    std::lock_guard<mutex> lock{m_mutex};
	    m_tasks.emplace(task);
	    m_condition.notify_one(); 
    }
private:
    void addThread(uint64_t threadNum)
    {
        for (uint64_t i = 0; i < threadNum; i++)
	    {
			m_threads.emplace_back([this]{
				while (!m_stop)
				{
					ThreadTask task;
					{
						std::unique_lock<mutex> lock(m_mutex);
						//队列不为空或者销毁线程
                        m_condition.wait(lock, [this]{
								return m_stop || !m_tasks.empty();
						});
						if (m_stop && m_tasks.empty())
							break;
						task = move(m_tasks.front());
						m_tasks.pop();
					}
					task();
				}
			});
	    };
    }
private:
    uint64_t m_threadNum;
    std::list<std::thread> m_threads;
    std::queue<ThreadTask> m_tasks;
    std::condition_variable  m_condition;
    std::mutex m_mutex;
    std::atomic<bool> m_stop;
};
}

#endif