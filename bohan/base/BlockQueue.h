/*
 * @Author: bohan.lj
 * @Date: 2022-10-10 22:48:44
 * @FilePath: /Bohan/bohan/base/BlockQueue.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-10 22:55:01
 * @Description: srouce_code
 */

#ifndef BOHAN_BASE_BLOCK_QUEUE_H
#define BOHAN_BASE_BLOCK_QUEUE_H

#include <deque>
#include <mutex>
#include <iostream>
#include <thread>
#include <condition_variable>
#include "os_type.h"
#include "Copyable.h"

using namespace std;

namespace bohan{

template<typename T>
class BlockQueue : Copyable
{
public:
    BlockQueue();
    ~BlockQueue();
    void push(const T &value);
    void push(T &&value);
    T pop();
    bool isEmpty();
    size_t size();
private:
    std::deque<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_condition;
};
}
#endif
