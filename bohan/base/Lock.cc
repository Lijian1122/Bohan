/*
 * @Author: bohan.lj
 * @Date: 2022-10-07 09:56:55
 * @FilePath: /Bohan/bohan/base/Loch.cc
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-07 11:58:16
 * @Description: srouce_code
 */
#include "Lock.h"

namespace bohan
{
CLock::CLock()
{
#ifdef __WIN32
    InitializeCriticalSection(&m_critical_section);
#else
    pthread_mutex_init(&m_lock,NULL);
#endif
}
CLock::~CLock()
{
#ifdef _WIN32
    DeleteCriticalSection(&m_critical_section);
#else
    pthread_mutex_destroy(&m_lock);
#endif

}
void CLock::lock()
{
#ifdef _WIN32
    EnterCriticalSection(&m_critical_section);
#else
    pthread_mutex_lock(&m_lock);
#endif
}
void CLock::unlock()
{
#ifdef _WIN32
    LeaveCriticalSection(&m_critical_section);
#else
    pthread_mutex_unlock(&m_lock);
#endif
}


GuardLock::GuardLock()
{

}
GuardLock::~GuardLock()
{

}
void GuardLock::lock()
{
    std::lock_guard<std::mutex> lock(m_mutex);
}


UniqueLock::UniqueLock()
{
    m_unique_lock = std::unique_lock<std::mutex>(mutex);
}
UniqueLock::~UniqueLock()
{

}
void UniqueLock::lock()
{
    m_unique_lock.lock();
}
void UniqueLock::unlock()
{
    m_unique_lock.unlock();
} 

bool UniqueLock::haslock()
{
    return m_unique_lock.owns_lock();
}

 std::unique_lock<std::mutex> &UniqueLock::getlock()
 {
    return m_unique_lock;
 }
}