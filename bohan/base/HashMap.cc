/*
 * @Author: bohan.lj
 * @Date: 2022-10-16 10:15:37
 * @FilePath: /Bohan/bohan/base/HashMap.cc
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-16 10:50:17
 * @Description: srouce_code
 */
#include "HashMap.h"

namespace bohan{
template<typename K,typename V>
Hash_Map<K,V>::Hash_Map(bool threadsafe)
    :m_threadsafe(threadsafe)
{
}

template<typename K,typename V>
void Hash_Map<K,V>::emplace(const K& key, const V& v)
{
    if(m_threadsafe)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
    }
    m_map[key] = v;
}

template<typename K,typename V>
void Hash_Map<K,V>::emplace(const K& key, const V&& v)
{
    if(m_threadsafe)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
    }
    m_map[key] = std::move(v);
}
template<typename K,typename V>
void Hash_Map<K,V>::erase(const K& key)
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

template<typename K,typename V>
size_t Hash_Map<K,V>::size()
{
    if(m_threadsafe)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
    }
    return m_map.size();
}

template<typename K,typename V>
bool Hash_Map<K,V>::getvalue(const K& key, V& value)
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

template<typename K,typename V>
bool Hash_Map<K,V>::haskey(const K& key)
{
    if(m_threadsafe)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
    }
    return m_map.find(key) != m_map.end();
}

template<typename K,typename V>
Hash_Map<K,V>::~Hash_Map()
{
    if(m_threadsafe)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
    }
    m_map.clear();
}
}