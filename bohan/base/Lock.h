/*
 * @Author: bohan.lj
 * @Date: 2022-10-07 09:56:23
 * @FilePath: /Bohan/bohan/base/Lock.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-07 23:47:49
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
    private:
    #ifdef __WIN32
        CRITICAL_SECTION m_critical_section;
    #else
        pthread_mutex_t m_lock;
    #endif        
};

//C++11 fengzhuang

//std::Gurad_lock
class GuardLock{
    public:
        GuardLock();
        virtual ~GuardLock();
        void lock();
    private:
        std::mutex m_mutex;
};

//std::unique_lock
class UniqueLock{
    public:
        UniqueLock();
        virtual ~UniqueLock();
        void lock();
        void unlock();
        bool haslock();
        std::unique_lock<std::mutex> &getlock();
    private:
        std::mutex mutex;
        std::unique_lock<std::mutex> m_unique_lock;
};
}
#endif