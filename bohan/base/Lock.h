/*
 * @Author: bohan.lj
 * @Date: 2022-10-07 09:56:23
 * @FilePath: /Bohan/bohan/base/Lock.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-16 17:45:56
 * @Description: lock
 */


#ifndef BOHAN_BASE_LOCK_H
#define BOHAN_BASE_LOCK_H

#include "os_type.h"
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

namespace bohan{
class CLock{
    public:
        CLock();
        virtual ~CLock();
        void lock();
        void unlock();
    #ifndef _WIN32
        pthread_mutex_t& getMutex() { return m_lock;}
        bool try_lock();
    #endif
    private:
    #ifdef __WIN32
        CRITICAL_SECTION m_critical_section;
    #else
        pthread_mutex_t m_lock;
    #endif        
};
class AutoLock
{
public:
    AutoLock(CLock* pLock);
    virtual ~AutoLock();
private:
    CLock* m_pLock;
};



}
#endif