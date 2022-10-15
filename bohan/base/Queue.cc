/*
 * @Author: bohan.lj
 * @Date: 2022-10-10 22:01:36
 * @FilePath: /Bohan/bohan/base/Queue.cc
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-15 22:44:22
 * @Description: srouce_code
 */

#include "Queue.h"
#include <mutex>

namespace bohan{
template<typename T>
Queue<T>::Queue()
{

}
template<typename T>
void Queue<T>::push(const T &value)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_queue.push_back(value);
}

template<typename T>
void Queue<T>::push(T &&value)
{
     std::unique_lock<std::mutex> lock(m_mutex);
     m_queue.push_back(std::move(value));
}

template<typename T>
T Queue<T>::pop()
{
    if(isEmpty())
    {
        return nullptr;
    }
    std::unique_lock<std::mutex> lock(m_mutex);
    T value = std::move(m_queue.front());
    m_queue.pop_front();
    return value;
}

template<typename T>
bool Queue<T>::isEmpty()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_queue.empty();
}

template<typename T>
size_t Queue<T>::size()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_queue.size();
}

template<typename T> 
Queue<T>::~Queue()
{
    if(!m_queue.empty())
    {
        m_queue.clear();
    }
}
}