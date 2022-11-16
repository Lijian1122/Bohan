/*
 * @Author: bohan.lj
 * @Date: 2022-10-16 21:52:04
 * @FilePath: /Bohan/bohan/base/Singleton.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-11-11 09:13:29
 * @Description: 线程安全的单例模式设置
 */
#include "os_type.h"
#include "Copyable.h"
#include <mutex>

#ifndef BOHAN_BASE_SINGLETON_H
#define BOHAN_BASE_SINGLETON_H
namespace bohan
{
template<typename Class>
class Singleton : Copyable
{
public:
   Singleton() = delete;
   ~Singleton() = delete;

    static Class *Instance()
    {
        if(!m_singleton)
        {
            m_mutex.lock();
            if(!m_singleton)
            {
                m_singleton = new Class();       
            }
            m_mutex.unlock();
        }
        return m_singleton;
    }
    static void  Destroy()
    {
        m_mutex.lock();
        if(m_singleton)
        {
            delete m_singleton;
            m_singleton = nullptr; 
        }
        m_mutex.unlock();
    }
private:
    static std::mutex m_mutex;
    static Class *m_singleton;
};
template<typename Class>
Class *Singleton<Class>::m_singleton = nullptr;
template<typename Class>
std::mutex Singleton<Class>::m_mutex;
} 
#endif
