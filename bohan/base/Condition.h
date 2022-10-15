/*
 * @Author: bohan.lj
 * @Date: 2022-10-07 12:00:10
 * @FilePath: /Bohan/bohan/base/Condition.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-07 22:13:09
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
    Condition();
    void wait(UniqueLock &lock);
    void notify();
    void notifyAll();
    void waitTime(UniqueLock &lock,uint64_t nWaitTime); //毫秒
    ~Condition();
private:
    std::condition_variable m_condition;
}; 
}

#endif
