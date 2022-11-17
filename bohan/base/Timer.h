/*
 * @Author: bohan.lj
 * @Date: 2022-10-16 22:54:36
 * @FilePath: /Bohan/bohan/base/Timer.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-11-17 08:33:20
 * @Description: srouce_code
 */
#ifndef BOHAN_BASE_TIMER_H
#define BOHAN_BASE_TIMER_H

#include "os_type.h"
#include "ThreadPool.h"
#include <atomic>
#include <chrono>
#include <future>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <atomic>
#include <thread>
#include <utility>
#include "HashMap.h"

#define DEFAULT_TIMER_THREAD_POOL_SIZE 1
typedef uint32_t TimerId;

namespace bohan{
typedef struct TimerEntity
{
    chrono::time_point<chrono::high_resolution_clock> tm_point;
    std::function<void()> callback;
    int repeated_id{0}; 
    TimerId timer_id{0};   //定时器ID
    int repeated_num{0}; //重复次数
    bool is_period{false};
    bool is_repeated{false};
    chrono::milliseconds tm_period; //时间间隔
    bool operator<(const TimerEntity& b) const { return tm_point > b.tm_point;}
};

enum TimerState{ 
    Running = 0 
};

class Timer
{
public:
    Timer(int threadnumn = DEFAULT_TIMER_THREAD_POOL_SIZE)
    {
        m_thread_pool = new ThreadPool(threadnum);
        m_tm_id.store(0);
        is_running.store(true);
    }
    ~Timer()
    {
        is_running.store(false);
        m_cond.notify_all();
        if(m_timer_thread.joinable())
        {
            m_timer_thread.join();
        }   
        if(m_thread_pool)
        {
            delete m_thread_pool;
            m_thread_pool = nullptr;
        }
    }
    void StartLoop()
    {
        m_timer_thread = std::thread([this](){
        while (is_running.load()) {
            std::unique_lock<std::mutex> lock(m_mutex);
            if (m_timer_queue.empty()) {
                m_cond.wait(lock);
                continue;
            }
            auto task = m_timer_queue.top();
            auto diff = task.tm_point - chrono::high_resolution_clock::now();
            if (chrono::duration_cast<chrono::milliseconds>(diff).count() > 0) {
                m_cond.wait_for(lock, diff);
                continue;
            } else {
                m_timer_queue.pop();
                if(!m_state_map.haskey(task.timer_id))
                {
                    continue;
                }
                if(task.is_period)
                {   task.tm_point = chrono::high_resolution_clock::now() + task.tm_period;
                    m_timer_queue.push(task);
                }
                else if(task.is_repeated && task.repeated_num>0)
                {
                    task.tm_point = chrono::high_resolution_clock::now() + task.tm_period;
                    task.repeated_num--;
                    m_timer_queue.push(task);
                }
                lock.unlock();
                m_thread_pool->addTask(std::move(task.callback));
             }
            }
        });
    }
    void Cancel(TimerId timerId)
    {
        if(m_state_map.haskey(timerId))
        {
            m_state_map.erase(timerId);
        }
    }

    template <typename F, typename... Args>
    TimerId AddPeriodTimer(int ms_time, F&& f, Args&&... args)
    {
        TimerEntity timer;
        timer.timer_id = m_tm_id.fetch_add(1);
        m_state_map.emplace(timer.timer_id,TimerState::Running);
        timer.is_period = true;
        timer.tm_period =  chrono::milliseconds(ms_time);
        timer.tm_point = chrono::high_resolution_clock::now();
        timer.callback = std::bind(forward<F>(f), forward<Args>(args)...);
        std::unique_lock<std::mutex> lock(m_mutex);
        m_timer_queue.push(timer);
        m_cond.notify_all();
        return timer.timer_id;
    }

    template <typename F, typename... Args>
    TimerId AddRepeatedTimer(int ms_time, int repeated_num, F&& f, Args&&... args)
    {
        TimerEntity timer;
        timer.timer_id = m_tm_id.fetch_add(1);
        m_state_map.emplace(timer.timer_id,TimerState::Running);
        timer.is_repeated = true;
        timer.tm_period =  chrono::milliseconds(ms_time);
        timer.repeated_num = repeated_num;
        timer.tm_point = chrono::high_resolution_clock::now();
        timer.callback = std::bind(forward<F>(f), forward<Args>(args)...);
        std::unique_lock<std::mutex> lock(m_mutex);
        m_timer_queue.push(timer);
        m_cond.notify_all();
        return timer.timer_id;
    }

private:
    std::priority_queue<TimerEntity> m_timer_queue;
    std::atomic<bool> is_running;
    std::mutex m_mutex;
    std::condition_variable m_cond;
    std::thread m_timer_thread;

    ThreadPool *m_thread_pool;
    std::atomic<uint32_t> m_tm_id;
    Hash_Map<TimerId, TimerState> m_state_map;
};
}

#endif