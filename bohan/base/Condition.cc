/*
 * @Author: bohan.lj
 * @Date: 2022-10-07 12:00:28
 * @FilePath: /Bohan/bohan/base/Condition.cc
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-16 17:42:34
 * @Description: srouce_code
 */
#include "Condition.h"
#include <assert.h>

namespace bohan{

Condition::Condition(CLock *lock)
{
#ifdef _MSC_VER
#else
    if(!lock)
    {
        assert(false);
    }
    m_pLock = lock;
    pthread_cond_init(&m_cond, NULL);
#endif
}

void Condition::wait()
{
#ifdef _MSC_VER
#else
     pthread_cond_wait(&m_cond, &m_pLock->getMutex());
#endif
}

bool Condition::waitTime(uint64_t nWaitTime)
{
#ifdef _MSC_VER
#else
    uint64_t nTime = nWaitTime * 1000000;
    struct timespec sTime;
    uint64_t nSec = nTime / (1000000000);
    uint64_t nNsec = nTime % (1000000000);
    sTime.tv_sec = time(NULL) + (uint32_t)nSec;
    sTime.tv_nsec = (uint32_t)nNsec;
    if(ETIMEDOUT == pthread_cond_timedwait(&m_cond, &m_pLock->getMutex(), &sTime))
    {
        return false;
    }
    return true;
#endif
}
void Condition::notify()
{
#ifdef _MSC_VER
#else
    pthread_cond_signal(&m_cond);
#endif
}
void Condition::notifyAll()
{
#ifdef _MSC_VER
#else
   pthread_cond_broadcast(&m_cond);
#endif
}
Condition::~Condition()
{
#ifdef _MSC_VER
#else
    pthread_cond_destroy(&m_cond);
#endif
}    
}