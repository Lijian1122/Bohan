/*
 * @Author: bohan.lj
 * @Date: 2022-10-07 22:18:12
 * @FilePath: /Bohan/bohan/base/ThreadPool.cc
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-15 22:48:48
 * @Description: srouce_code
 */
#include "ThreadPool.h"
#include <future>

namespace bohan{
ThreadPool::ThreadPool(uint64_t threadNum)
{
	m_stop = false;
    addThread(threadNum); 
}
ThreadPool::~ThreadPool()
{
	stop();
}
void ThreadPool::stop()
{
    m_stop=true;
	m_condition.notify_all();
	for (thread& thread : m_threads) 
    {
		if(thread.joinable())
			thread.join(); 
	}
}

template<class F, class... Args>
void ThreadPool::addTask(F&& f, Args&&... args)
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

void ThreadPool::addThread(uint64_t threadNum)
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
	}
}
}