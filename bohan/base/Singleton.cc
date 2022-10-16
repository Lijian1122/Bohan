/*
 * @Author: bohan.lj
 * @Date: 2022-10-16 21:52:11
 * @FilePath: /Bohan/bohan/base/Singleton.cc
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-16 22:34:49
 * @Description: srouce_code
 */
#include "Singleton.h"

namespace bohan{
template<typename Class>
Class *Singleton<Class>::m_singleton = nullptr;
template<typename Class>
std::mutex Singleton<Class>::m_mutex;

template<typename Class>
Class *Singleton<Class>::Instance()
{
    if(!m_singleton)
    {
        m_mutex.lock();
        if(!m_singleton)
        {
            m_singleton = new Class;       
        }
        m_mutex.unlock();
    }
    return m_singleton;
}

template<typename Class>
void Singleton<Class>::Destroy()
{
     m_mutex.lock();
     if(m_singleton)
     {
        delete m_singleton;
        m_singleton = nullptr; 
     }
     m_mutex.unlock();
}
}

