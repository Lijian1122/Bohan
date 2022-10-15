/*
 * @Author: bohan.lj
 * @Date: 2022-10-10 22:49:20
 * @FilePath: /Bohan/bohan/base/BlockQueue.cc
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-15 22:41:48
 * @Description: srouce_code
 */

#include "BlockQueue.h"
#include <mutex>

namespace bohan{
template<typename T>
BlockQueue<T>::BlockQueue()
{

}
template<typename T>
void BlockQueue<T>::push(const T &value)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_queue.push_back(value);
    m_condition.notify_one();
}

template<typename T>
void BlockQueue<T>::push(T &&value)
{
     std::unique_lock<std::mutex> lock(m_mutex);
     m_queue.push_back(std::move(value));
     m_condition.notify_one();
}

template<typename T>
T BlockQueue<T>::pop()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    while(m_queue.empty())
    {
        m_condition.wait(lock);
    }
    assert(!m_queue.empty());
    T value = std::move(m_queue.front());
    m_queue.pop_front();
    return value;
}

template<typename T>
bool BlockQueue<T>::isEmpty()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_queue.empty();
}

template<typename T>
size_t BlockQueue<T>::size()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_queue.size();
}

template<typename T> 
BlockQueue<T>::~BlockQueue()
{
    if(!m_queue.empty())
    {
        m_queue.clear();
    }
}
}