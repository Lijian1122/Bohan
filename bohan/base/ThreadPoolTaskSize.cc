/*
 * @Author: bohan.lj
 * @Date: 2022-10-20 22:35:00
 * @FilePath: /Bohan/bohan/base/ThreadPoolTaskSize.cc
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-21 08:34:00
 * @Description: srouce_code
 */
#include "ThreadPoolTaskSize.h"
#include <assert.h>
#include <stdio.h>

namespace bohan
{

ThreadPoolTaskSize::ThreadPoolTaskSize(uint32_t threadNum,const std::string& name)
        :m_thread_num(threadNum),
        m_thread_name(name),
        m_tasks(0),
        is_running(false)
{
}

ThreadPoolTaskSize::~ThreadPoolTaskSize()
{
    if(is_running)
    {
        Stop();
    }
}

void ThreadPoolTaskSize::Start()
{
    assert(m_threads.empty());
    is_running = true;
    m_threads.reserve(m_thread_num);
    for(int i  = 0; i < m_thread_num ; i++)
    {
        // char id[32];
        // snprintf(id, sizeof(id), "_%d", i+1);
        m_threads.emplace_back(std::thread(&ThreadPoolTaskSize::Run, this));
    }
}
void ThreadPoolTaskSize::Stop()
{
    is_running = false;
    m_notEmpty_con.notify_all();
    m_notFull_con.notify_all();
    for(auto &thread : m_threads)
    {
        thread.join();
    }
}

bool ThreadPoolTaskSize::IsFull()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_tasks.empty();
}

size_t ThreadPoolTaskSize::GetTaskSize()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_tasks.size();
}
void ThreadPoolTaskSize::Push(Task task)
{
    if(m_threads.empty())
    {
        task();
    }else
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        while(m_tasks.size() == m_maxTask_size && is_running)
        {
            m_notFull_con.wait(lock);
        }
        assert(!IsFull());
        m_tasks.push_back(std::move(task));
        m_notEmpty_con.notify_one();
    }
}
void ThreadPoolTaskSize::Run()
{
    while (is_running)
    {
        Task task = std::move(Pop());
        if(task)
        {
            task();
        }
    } 
}
Task ThreadPoolTaskSize::Pop()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    while(m_tasks.empty() && is_running)
    {
        m_notEmpty_con.wait(lock);
    }
    Task task;
    if(!m_tasks.empty())
    {
        task = m_tasks.front();
        m_tasks.pop_front();
        m_notFull_con.notify_one();
    }
    return task; 
}
}