/*
 * @Author: bohan.lj
 * @Date: 2022-12-04 12:02:49
 * @FilePath: /Bohan/bohan/base/PackageUtil.cc
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-12-04 22:30:02
 * @Description: srouce_code
 */
#include "PackageUtil.h"
#include <string.h>

namespace bohan
{
PackageByteStream::PackageByteStream(u_char *buf, uint32_t len)
{
   m_buf = buf;
   m_len = len;
   m_simpbuf = nullptr;
   m_pos = 0;
}
PackageByteStream::PackageByteStream(SimpleBuffer *buf, uint32_t len)
{
   m_buf = nullptr;
   m_len = len;
   m_simpbuf = buf;
   m_pos = 0;
}
PackageByteStream::~PackageByteStream()
{

}

int16_t PackageByteStream::ReadInt16(uchar_t* buf)
{
    int16_t data = (buf[0] << 8) | buf[1];
    return data;
}
uint16_t PackageByteStream::ReadUint16(uchar_t* buf)
{
    uint16_t data = (buf[0] << 8) | buf[1];
    return data;
}
int32_t PackageByteStream::ReadInt32(uchar_t* buf)
{
    int32_t data = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
    return data;
}
uint32_t PackageByteStream::ReadUint32(uchar_t* buf)
{
    uint32_t data = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
    return data;
}
void PackageByteStream::WriteInt16(uchar_t* buf, int16_t data)
{
    buf[0] = static_cast<uchar_t>(data >> 8);
    buf[1] = static_cast<uchar_t>(data & 0xFF);
}
void PackageByteStream::WriteUint16(uchar_t* buf, uint16_t data)
{
    buf[0] = static_cast<uchar_t>(data >> 8);
    buf[1] = static_cast<uchar_t>(data & 0xFF);
}
void PackageByteStream::WriteInt32(uchar_t* buf, int32_t data)
{
    buf[0] = static_cast<uchar_t>(data >> 24);
    buf[1] = static_cast<uchar_t>((data >> 16) & 0xFF);
    buf[2] = static_cast<uchar_t>((data >> 8) & 0xFF);
    buf[3] = static_cast<uchar_t>(data & 0xFF);
}
void PackageByteStream::WriteUint32(uchar_t* buf, uint32_t data)
{
    buf[0] = static_cast<uchar_t>(data >> 24);
    buf[1] = static_cast<uchar_t>((data >> 16) & 0xFF);
    buf[2] = static_cast<uchar_t>((data >> 8) & 0xFF);
    buf[3] = static_cast<uchar_t>(data & 0xFF);    
}

void PackageByteStream::operator << (int8_t data)
{
     WriteByte(&data, 1);
}
void PackageByteStream::operator << (uint8_t data)
{
     WriteByte(&data, 1);
}
void PackageByteStream::operator << (int16_t data)
{
    unsigned char buf[2];
    buf[0] = static_cast<uchar_t>(data >> 8);
    buf[1] = static_cast<uchar_t>(data & 0xFF);
    WriteByte(buf, 2);
}
void PackageByteStream::operator << (uint16_t data)
{
    unsigned char buf[2];
    buf[0] = static_cast<uchar_t>(data >> 8);
    buf[1] = static_cast<uchar_t>(data & 0xFF);
    WriteByte(buf, 2);
}
void PackageByteStream::operator << (int32_t data)
{
    unsigned char buf[4];
	buf[0] = static_cast<uchar_t>(data >> 24);
	buf[1] = static_cast<uchar_t>((data >> 16) & 0xFF);
	buf[2] = static_cast<uchar_t>((data >> 8) & 0xFF);
	buf[3] = static_cast<uchar_t>(data & 0xFF);
	WriteByte(buf, 4);
}
void PackageByteStream::operator << (uint32_t data)
{
    unsigned char buf[4];
	buf[0] = static_cast<uchar_t>(data >> 24);
	buf[1] = static_cast<uchar_t>((data >> 16) & 0xFF);
	buf[2] = static_cast<uchar_t>((data >> 8) & 0xFF);
	buf[3] = static_cast<uchar_t>(data & 0xFF);
	WriteByte(buf, 4);
}
void PackageByteStream::operator >> (int8_t& data)
{
    ReadByte(&data, 1);
}
void PackageByteStream::operator >> (uint8_t& data)
{
    ReadByte(&data, 1);
}
void PackageByteStream::operator >> (int16_t& data)
{
    unsigned char buf[2];
    ReadByte(buf, 2);
	data = (buf[0] << 8) | buf[1];
}
void PackageByteStream::operator >> (uint16_t& data)
{
    unsigned char buf[2];
    ReadByte(buf, 2);
	data = (buf[0] << 8) | buf[1];
}
void PackageByteStream::operator >> (int32_t& data)
{
    unsigned char buf[4];
	ReadByte(buf, 4);
	data = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
}
void PackageByteStream::operator >> (uint32_t& data)
{
    unsigned char buf[4];
	ReadByte(buf, 4);
	data = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
}

void PackageByteStream::WriteString(const char* str)
{
    uint32_t size = str? (uint32_t)strlen(str) : 0;
    *this << size;
    WriteByte((void*)str,size);
}
void PackageByteStream::WriteString(const char* str, uint32_t len)
{
    *this << len;
    WriteByte((void*)str,len);
}
const char* PackageByteStream::ReadString(uint32_t& len)
{
    *this >> len;
	char* str = (char*)GetBuf() + GetPos();
	Skip(len);
	return str;
}

void PackageByteStream::WriteData(uchar_t* data, uint32_t len)
{
    *this << len;
    WriteByte(data, len);
}
const uchar_t* PackageByteStream::ReadData(uint32_t& len)
{
    *this >> len;
	uchar_t* data = (uchar_t*)GetBuf() + GetPos();
	Skip(len);
	return data;
}

void  PackageByteStream::WriteByte(void* buf, uint32_t len)
{
    if (m_buf && (m_pos + len > m_len))
		return;

	if (m_simpbuf)
		m_simpbuf->Write((char*)buf, len);
	else
		memcpy(m_buf + m_pos, buf, len);
	m_pos += len;
}
void  PackageByteStream::ReadByte(void* buf, uint32_t len)
{
    if(m_pos + len > m_len)
	{
		throw PackageException(PackageErrorCode::PARSE_ERROR, "parase packet failed!");
	}

	if (m_simpbuf)
		m_simpbuf->Read((char*)buf, len);
	else
		memcpy(buf, m_buf + m_pos, len);
	m_pos += len;
}

}