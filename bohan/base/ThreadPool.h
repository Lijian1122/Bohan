/*
 * @Author: bohan.lj
 * @Date: 2022-10-07 22:16:16
 * @FilePath: /Bohan/bohan/base/ThreadPool.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-15 22:46:29
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
#include "Lock.h"
#include "Copyable.h"
#include "assert.h"

#define THREADPOOL_MAX_NUM 64;
typedef std::function<void()>  ThreadTask;

namespace bohan{
class ThreadPool : Copyable
{

public:
    ThreadPool(uint64_t threadNum = 4);
    ~ThreadPool();
    void stop();

    template<class F, class... Args>
	void addTask(F&& f, Args&&... args);
private:
    void addThread(uint64_t threadNum);
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