/*
 * @Author: bohan.lj
 * @Date: 2022-12-04 12:02:36
 * @FilePath: /Bohan/bohan/base/PackageUtil.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-12-04 22:21:23
 * @Description: package_utils
 */

#ifndef BOHAN_BASE_PACKAGEUTIL_H
#define BOHAN_BASE_PACKAGEUTIL_H

#include <os_type.h>
#include <string>
#include "SimpleBuffer.h"

namespace bohan
{

enum PackageErrorCode{
     PARSE_ERROR  = 0,
     SERVICE_ID_ERROR,
     COMMAND_ID_ERROR,
     ALLOC_ERROR
};

class PackageException {
public:
          PackageException(uint32_t service_id, uint32_t command_id, uint32_t error_code, const char* error_msg)
	{
		m_service_id = service_id;
		m_command_id = command_id;
		m_error_code = error_code;
		m_error_msg = error_msg;
	}

	PackageException(uint32_t error_code, const char* error_msg)
	{
		m_service_id = 0;
		m_command_id = 0;
		m_error_code = error_code;
		m_error_msg = error_msg;
	}

	virtual ~PackageException() {}

	uint32_t GetServiceId() { return m_service_id; }
	uint32_t GetCommandId() { return m_command_id; }
	uint32_t GetErrorCode() { return m_error_code; }
          const char* GetErrorMsg() { return m_error_msg.c_str();}
private:
	uint32_t	m_service_id;
	uint32_t	m_command_id;
	uint32_t	m_error_code;
	std::string m_error_msg;
};

class PackageByteStream
{
public:
     PackageByteStream(u_char *buf, uint32_t len);
     PackageByteStream(SimpleBuffer *buf, uint32_t len);
     virtual ~PackageByteStream();
   
     unsigned char* GetBuf() { return m_simpbuf ? m_simpbuf->GetBuffer() : m_buf;}
     uint32_t GetPos() { return m_pos;}
     uint32_t GetLen() { return m_len;}
     void Skip(uint32_t len)
     {
	m_pos += len;
	if(m_pos > m_len)
	{
              throw PackageException(PackageErrorCode::PARSE_ERROR, "parase packet failed!");
	}
    }

    static int16_t ReadInt16(uchar_t* buf);
    static uint16_t ReadUint16(uchar_t* buf);
    static int32_t ReadInt32(uchar_t* buf);
    static uint32_t ReadUint32(uchar_t* buf);
    static void WriteInt16(uchar_t* buf, int16_t data);
    static void WriteUint16(uchar_t* buf, uint16_t data);
    static void WriteInt32(uchar_t* buf, int32_t data);  
    static void WriteUint32(uchar_t* buf, uint32_t data);

    void operator << (int8_t data);
    void operator << (uint8_t data);
    void operator << (int16_t data);
    void operator << (uint16_t data);
    void operator << (int32_t data);
    void operator << (uint32_t data);

    void operator >> (int8_t& data);
    void operator >> (uint8_t& data);
    void operator >> (int16_t& data);
    void operator >> (uint16_t& data);
    void operator >> (int32_t& data);
    void operator >> (uint32_t& data);

    void WriteString(const char* str);
    void WriteString(const char* str, uint32_t len);
    const char* ReadString(uint32_t& len);

    void WriteData(uchar_t* data, uint32_t len);
    const uchar_t* ReadData(uint32_t& len);

private:
   void  WriteByte(void* buf, uint32_t len);
   void  ReadByte(void* buf, uint32_t len);

private:
   SimpleBuffer*	m_simpbuf;
   uchar_t*	m_buf;
   uint32_t	m_len;
   uint32_t	m_pos;
};
}
#endif