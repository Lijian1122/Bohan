/*
 * @Author: bohan.lj
 * @Date: 2022-12-04 11:57:25
 * @FilePath: /Bohan/bohan/base/PackageBase.cc
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-12-04 22:25:48
 * @Description: srouce_code
 */
#include "PackageBase.h"
#include "BaseDefine.pb.h"

using namespace Bohan::BaseDefine;
namespace bohan
{
PackageBase::PackageBase()
{
    m_header.version = PACKAGE_VERSION;
    m_header.flag = 0;
    m_header.service_id = ServiceID::SID_OTHER;
    m_header.command_id = 0; 
    m_header.seq_num = 0;
    m_header.reversed = 0; 
}

uchar_t* PackageBase::GetBuffer()
{
    return m_simpleBuf.GetBuffer();
}
uint32_t PackageBase::GetLength()
{
    return m_simpleBuf.GetWriteOffset();
}
uchar_t* PackageBase::GetBodyData()
{
   return m_simpleBuf.GetBuffer() +  sizeof(PackageHeader);
}
uint32_t PackageBase::GetBodyLength()
{
   uint32_t bodyLen = 0;
   bodyLen = m_simpleBuf.GetWriteOffset() - sizeof(PackageHeader);
   return bodyLen;
}

void PackageBase::SetVersion(uint16_t version)
{
    uchar_t* buf = GetBuffer();
    PackageByteStream::WriteUint16(buf + 4, version);
}
void PackageBase::SetFlag(uint16_t flag)
{
    uchar_t* buf = GetBuffer();
    PackageByteStream::WriteUint16(buf + 6, flag);
}
void PackageBase::SetServiceId(uint16_t service_id)
{
    uchar_t* buf = GetBuffer();
    PackageByteStream::WriteUint16(buf + 8, service_id);
}
void PackageBase::SetCommandId(uint16_t command_id)
{
    uchar_t* buf = GetBuffer();
    PackageByteStream::WriteUint16(buf + 10, command_id);
}
void PackageBase::SetError(uint16_t error)
{
    uchar_t* buf = GetBuffer();
    PackageByteStream::WriteUint16(buf + 12, error);
}
void PackageBase::SetSeqNum(uint16_t seq_num)
{
    uchar_t* buf = GetBuffer();
    PackageByteStream::WriteUint16(buf + 12, seq_num);
}
void PackageBase::SetReversed(uint32_t reversed)
{
    uchar_t* buf = GetBuffer();
    PackageByteStream::WriteUint16(buf + 14, reversed);
}
void PackageBase::WriteHeader()
{
   uchar_t* buf = GetBuffer();
   PackageByteStream::WriteInt32(buf, GetLength());
   PackageByteStream::WriteUint16(buf + 4, m_header.version);
   PackageByteStream::WriteUint16(buf + 6, m_header.flag);
   PackageByteStream::WriteUint16(buf + 8, m_header.service_id);
   PackageByteStream::WriteUint16(buf + 10, m_header.command_id);
   PackageByteStream::WriteUint16(buf + 12, m_header.seq_num);
   PackageByteStream::WriteUint16(buf + 14, m_header.reversed);
}

bool PackageBase::IsPackageAvailable(uchar_t* buf, uint32_t len, uint32_t& pdu_len)
{
   if (len < PACKAGE_HEADER_LEN)
	return false;

   pdu_len = PackageByteStream::ReadUint32(buf);
   if(pdu_len > len)
   {
      return false;
   }
    
   if(0 == pdu_len)
   {
      throw PackageException(PackageErrorCode::PARSE_ERROR, "pdu_len is 0");
   }
  return true;
}

PackageBase* PackageBase::ReadPackage(uchar_t* buf, uint32_t len)
{
   uint32_t pdu_len = 0;
   if (!IsPackageAvailable(buf, len, pdu_len))
	return nullptr;

   PackageBase* package = new PackageBase();
   package->Write(buf, pdu_len);
   package->ReadHeader(buf, PACKAGE_HEADER_LEN);
   return package;
}
int PackageBase::ReadHeader(uchar_t* buf, uint32_t len)
{
   int ret = -1;
   if (len >= PACKAGE_HEADER_LEN && buf) 
   {
	PackageByteStream stream(buf, len);
	stream >> m_header.length;
	stream >> m_header.version;
	stream >> m_header.flag;
          stream >> m_header.service_id;
	stream >> m_header.command_id;
	stream >> m_header.seq_num;
          stream >> m_header.reversed;
          ret = 0;
    }
    return ret;
}
void PackageBase::SetPackage(const google::protobuf::MessageLite* msg)
{
    m_simpleBuf.Read(NULL, m_simpleBuf.GetWriteOffset());
    m_simpleBuf.Write(NULL, sizeof(PackageHeader));
    uint32_t size = msg->ByteSize();
    uchar_t* data = new uchar_t[size];
    if(!msg->SerializeToArray(data, size))
    {
        printf("pb msg miss required fields.");
        return;
    }
    m_simpleBuf.Write(data, size);
    delete []data;
    WriteHeader();
}
}