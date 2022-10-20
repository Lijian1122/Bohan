/*
 * @Author: bohan.lj
 * @Date: 2022-10-20 22:34:54
 * @FilePath: /Bohan/bohan/base/ThreadPoolTaskSize.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-20 23:34:59
 * @Description: 线程池设置最大任务数
 */


#ifndef BOHAN_BASE_THREADPOOL_TASKSIZE_H
#define BOHAN_BASE_THREADPOOL_TASKSIZE_H

#include "os_type.h"
#include "Copyable.h"
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>

#define DEFAULT_THREAD_NUM 1

namespace bohan{

typedef std::function<void()> Task;

class ThreadPoolTaskSize
{

public:
    explicit ThreadPoolTaskSize(uint32_t threadNum = DEFAULT_THREAD_NUM ,const std::string& name = "Thread");
    ~ThreadPoolTaskSize();

    void Start();
    void Stop();

    void SetMaxTaskSize(uint32_t maxSize){m_maxTask_size = maxSize;}
    size_t GetTaskSize();
    void Push(Task task);

private:
    bool IsFull();
    void Run();
    Task Pop();

private:
    std::string m_thread_name;
    uint32_t m_thread_num;
    uint32_t m_maxTask_size;
    std::mutex m_mutex;
    std::condition_variable m_notEmpty_con;
    std::condition_variable m_notFull_con;
    std::vector<std::thread> m_threads;
    std::deque<Task> m_tasks;
    bool is_running;
};
}
#endif