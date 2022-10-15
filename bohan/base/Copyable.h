/*
 * @Author: bohan.lj
 * @Date: 2022-10-07 21:53:36
 * @FilePath: /Bohan/bohan/base/Copyable.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-07 22:07:22
 * @Description: 不可拷贝对象封装  对象无法拷贝,赋值
 */

#ifndef BOHAN_BASE_COPYABLE_H
#define BOHAN_BASE_COPYABLE_H
namespace bohan
{
class Copyable
{
public:
    Copyable() = default;  //默认
    ~Copyable() = default; //默认

    //禁用拷贝构造函数
    Copyable(const Copyable&) = delete;

    //禁用赋值函数
    Copyable& operator=(const Copyable&) = delete;
};
}

#endif