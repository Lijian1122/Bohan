/*
 * @Author: bohan.lj
 * @Date: 2022-10-10 22:01:25
 * @FilePath: /Bohan/bohan/base/Queue.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-12-11 20:05:10
 * @Description: srouce_code
 */

#ifndef BOHAN_BASE_QUEUE_H
#define BOHAN_BASE_QUEUE_H

#include <deque>
#include <mutex>
#include <iostream>
#include <thread>
#include "os_type.h"
#include "Copyable.h"

using namespace std;

namespace bohan{

template<typename T>
class DLL_EXPORTS Queue : Copyable
{
public:
    Queue();
    ~Queue();
    void push(const T &value);
    void push(T &&value);
    T pop();
    bool isEmpty();
    size_t size();
private:
    std::deque<T> m_queue;
    std::mutex m_mutex;
};
}
#endif
