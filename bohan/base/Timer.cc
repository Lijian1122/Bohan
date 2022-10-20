/*
 * @Author: bohan.lj
 * @Date: 2022-10-16 22:55:31
 * @FilePath: /Bohan/bohan/base/Timer.cc
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-20 22:20:28
 * @Description: srouce_code
 */
#include "Timer.h"

namespace bohan
{
Timer::Timer(int threadnum)
{
    m_thread_pool = new ThreadPool(threadnum);
    m_tm_id.store(0);
    is_running.store(true);
}

Timer::~Timer()
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

void Timer::StartLoop()
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
                m_thread_pool->addTask(move(task.callback));
            }
        }
    });
}

void Timer::Cancel(TimerId timerId)
{
    if(m_state_map.haskey(timerId))
    {
        m_state_map.erase(timerId);
    }
}

template <typename F, typename... Args>
TimerId Timer::AddPeriodTimer(int ms_time, F&& f, Args&&... args)
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
TimerId Timer::AddRepeatedTimer(int ms_time, int repeated_num, F&& f, Args&&... args)
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
} // namespace bohan
