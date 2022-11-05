/*
 * @Author: bohan.lj
 * @Date: 2022-11-05 21:10:35
 * @FilePath: /Bohan/bohan/base/SimpleBuffer.cc
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-11-05 21:44:28
 * @Description: srouce_code
 */
#include "SimpleBuffer.h"
#include <string.h>

namespace bohan{
SimpleBuffer::SimpleBuffer()
{
    m_buffer = nullptr;
    m_alloc_size = 0;
    m_write_offset = 0;

}
SimpleBuffer::~SimpleBuffer()
{
    if(m_buffer)
    {
        free(m_buffer);
        m_buffer = nullptr;
    }
    m_alloc_size = 0;
    m_write_offset = 0;
}

void SimpleBuffer::ReSizeBuffer(uint32_t len)
{
    m_alloc_size = m_write_offset + len;
    m_alloc_size += m_alloc_size;	//模仿std::vector扩容规则 重新申请2倍大的空间
    uchar_t* new_buf = (uchar_t*)realloc(m_buffer, m_alloc_size);
	m_buffer = new_buf;
}
uint32_t SimpleBuffer::Write(void* buf, uint32_t len)
{
    if(m_write_offset + len > m_alloc_size)
    {
        ReSizeBuffer(len);
    }
    if(buf)
    {
        memcpy(m_buffer + m_write_offset,buf, len);
    }
    m_write_offset += len;
    return len;
}
uint32_t SimpleBuffer::Read(void* buf, uint32_t len)
{
    if(len > m_write_offset)
    {
        len = m_write_offset;
    }
    if(buf)
    {
        memcpy(buf,m_buffer,len);
    }
    m_write_offset -= len;
    memmove(m_buffer, m_buffer + len, m_write_offset); //剩余的内存拷贝到m_buffer位置
    return len;
}
}