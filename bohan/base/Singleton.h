/*
 * @Author: bohan.lj
 * @Date: 2022-10-16 21:52:04
 * @FilePath: /Bohan/bohan/base/Singleton.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-16 22:33:59
 * @Description: srouce_code
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
    //禁用拷贝构造函数
    Singleton(const Singleton&) = delete;
    //禁用赋值函数
    Singleton& operator=(const Singleton&) = delete;

    Class *Instance();
    static void  Destroy();
private:
    static std::mutex m_mutex;
    static Class *m_singleton;
};
} 
#endif
