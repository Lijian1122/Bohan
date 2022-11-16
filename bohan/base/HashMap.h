/*
 * @Author: bohan.lj
 * @Date: 2022-10-16 10:07:41
 * @FilePath: /Bohan/bohan/base/HashMap.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-11-11 09:03:58
 * @Description: 线程安全的hash_map封装
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
    Hash_Map(bool threadsafe = false)
    {
        m_threadsafe = threadsafe;
    }
    ~Hash_Map()
    {
        if(m_threadsafe)
        {
            std::unique_lock<std::mutex> lock(m_mutex);
        }
        m_map.clear();
    }
    void emplace(const K& key, const V& v)
    {
        if(m_threadsafe)
        {
            std::unique_lock<std::mutex> lock(m_mutex);
        }
        m_map[key] = v;
    }
    void emplace(const K& key, const V&& v) //右值引用
    {
        if(m_threadsafe)
        {
            std::unique_lock<std::mutex> lock(m_mutex);
        }
        m_map[key] = std::move(v);
    }
    void erase(const K& key)
    {
        if(m_threadsafe)
        {
            std::unique_lock<std::mutex> lock(m_mutex);
        }
        if (m_map.find(key) != m_map.end())
        {
            m_map.erase(key);
        }
    }
    size_t size()
    {
        if(m_threadsafe)
        {
            std::unique_lock<std::mutex> lock(m_mutex);
        }
        return m_map.size();
    }
    bool getvalue(const K& key, V& value)
    {
        if(m_threadsafe)
        {
            std::unique_lock<std::mutex> lock(m_mutex);
        }
        if (m_map.find(key) != m_map.end()) 
        {
            value = m_map[key];
            return true;
        }
        return false;
    }
    bool haskey(const K& key)
    {
        if(m_threadsafe)
        {
            std::unique_lock<std::mutex> lock(m_mutex);
        }
        return m_map.find(key) != m_map.end();
    }
private:
    bool m_threadsafe = false;
    std::unordered_map<K,V>  m_map;
    std::mutex m_mutex;
};
}
#endif