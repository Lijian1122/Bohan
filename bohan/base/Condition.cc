/*
 * @Author: bohan.lj
 * @Date: 2022-10-07 12:00:28
 * @FilePath: /Bohan/bohan/base/Condition.cc
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-07 21:48:14
 * @Description: srouce_code
 */
#include "Condition.h"

namespace bohan{

Condition::Condition()
{
}

void Condition::wait(UniqueLock &lock)
{
    m_condition.wait(lock.getlock());
}

void Condition::waitTime(UniqueLock &lock,uint64_t nWaitTime)
{
    m_condition.wait_for(lock.getlock(),std::chrono::seconds(nWaitTime));
}
void Condition::notify()
{
    m_condition.notify_one();
}
void Condition::notifyAll()
{
    m_condition.notify_all();
}
Condition::~Condition()
{
}    
}