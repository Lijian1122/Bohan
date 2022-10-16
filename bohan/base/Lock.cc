/*
 * @Author: bohan.lj
 * @Date: 2022-10-07 09:56:55
 * @FilePath: /Bohan/bohan/base/Lock.cc
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-16 21:51:35
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

#ifndef _WIN32
bool CLock::try_lock()
{
     return pthread_mutex_trylock(&m_lock) == 0;
}
#endif
AutoLock::AutoLock(CLock* pLock)
{
    m_pLock = pLock;
    if(!m_pLock)
        m_pLock->lock();
}

AutoLock::~AutoLock()
{
    if(!m_pLock)
        m_pLock->unlock();
}
}
