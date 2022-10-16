/*
 * @Author: bohan.lj
 * @Date: 2022-10-16 22:54:36
 * @FilePath: /Bohan/bohan/base/Timer.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-17 00:09:15
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
#include "HashMap.h"

#define DEFAULT_TIMER_THREAD_POOL_SIZE 1

namespace bohan{
typedef struct TimerEntity
{
    chrono::time_point<chrono::high_resolution_clock> tm_point;
    std::function<void()> callback;
    int repeated_id{0}; 
    int timer_id{0};   //定时器ID
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
    Timer(int threadnumn = DEFAULT_TIMER_THREAD_POOL_SIZE);
    ~Timer();
    void StartLoop();
    void Cancel(int timerId);

    template <typename F, typename... Args>
    int AddPeriodTimer(int ms_time, F&& f, Args&&... args);

    template <typename F, typename... Args>
    int AddRepeatedTimer(int ms_time, int repeated_num, F&& f, Args&&... args);

private:
    std::priority_queue<TimerEntity> m_timer_queue;
    std::atomic<bool> is_running;
    std::mutex m_mutex;
    std::condition_variable m_cond;
    std::thread m_timer_thread;

    ThreadPool *m_thread_pool;
    std::atomic<int> m_tm_id;
    Hash_Map<int, TimerState> m_state_map;
};
}

#endif