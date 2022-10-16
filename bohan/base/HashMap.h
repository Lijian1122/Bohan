/*
 * @Author: bohan.lj
 * @Date: 2022-10-16 10:07:41
 * @FilePath: /Bohan/bohan/base/HashMap.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-16 10:48:38
 * @Description: 线程安全的hash_map 封装
 */
#ifndef BOHAN_BASE_HASHMAP_H
#define BOHAN_BASE_HASHMAP_H
#include <unordered_map>
#include <thread>
#include <mutex>

using namespace std;
namespace bohan
{
template<typename K,typename V>
class Hash_Map
{
public:
    Hash_Map(bool threadsafe = true);
    ~Hash_Map();
    void emplace(const K& key, const V& v);
    void emplace(const K& key, const V&& v);  //右值引用
    void erase(const K& key);
    size_t size();
    bool getvalue(const K& key, V& value);
    bool haskey(const K& key);
private:
    bool m_threadsafe;
    std::unordered_map<K,V>  m_map;
    std::mutex m_mutex;
};
}
#endif