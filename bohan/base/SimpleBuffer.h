/*
 * @Author: bohan.lj
 * @Date: 2022-11-05 21:10:23
 * @FilePath: /Bohan/bohan/base/SimpleBuffer.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-11-05 22:46:45
 * @Description: srouce_code
 */

#ifndef BOHAN_BASE_SIMPLE_BUFFER_H
#define BOHAN_BASE_SIMPLE_BUFFER_H

#include "os_type.h"

namespace bohan{
class SimpleBuffer
{
public:
    SimpleBuffer();
    virtual ~SimpleBuffer();
    uchar_t *GetBuffer(){return m_buffer;}
    uint32_t GetAllocSize() { return m_alloc_size; }
	uint32_t GetWriteOffset() { return m_write_offset; }
	void IncWriteOffset(uint32_t len) { m_write_offset += len; }

	void ReSizeBuffer(uint32_t len);
	uint32_t Write(void* buf, uint32_t len);
	uint32_t Read(void* buf, uint32_t len);
private:
    uchar_t*	m_buffer;
	uint32_t	m_alloc_size;
	uint32_t	m_write_offset;
};
}
#endif
