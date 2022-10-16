/*
 * @Author: bohan.lj
 * @Date: 2022-10-07 12:00:10
 * @FilePath: /Bohan/bohan/base/Condition.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-16 17:44:41
 * @Description: condition
 */

#ifndef BOHAN_BASE_CONDITION_H
#define BOHAN_BASE_CONDITION_H
#include "os_type.h"
#include <thread>
#include <condition_variable>
#include <chrono>
#include "Lock.h"

using namespace std;

namespace bohan
{
class Condition
{
public:
    Condition(CLock *lock);
    void wait();
    void notify();
    void notifyAll();
    bool waitTime(uint64_t nWaitTime); //毫秒
    ~Condition();
private:
    CLock* m_pLock;
    #ifdef _MSC_VER
    #else
    pthread_cond_t m_cond;
    #endif 
}; 
}

#endif
