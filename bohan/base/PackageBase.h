/*
 * @Author: bohan.lj
 * @Date: 2022-12-04 11:56:38
 * @FilePath: /Bohan/bohan/base/PackageBase.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-12-04 22:24:52
 * @Description: srouce_code
 */


#ifndef BOHAN_BASE_PACKAGEBASE_H
#define BOHAN_BASE_PACKAGEBASE_H
#include "PackageUtil.h"
#include "SimpleBuffer.h"
#include "pb/google/protobuf/message_lite.h"

#define PACKAGE_VERSION 1
#define PACKAGE_HEADER_LEN 16

namespace bohan
{

typedef struct PackageHeader
{
    uint32_t   length;     //the package length
    uint16_t   version;    // version 
    uint16_t   flag;       //flag
    uint16_t   service_id; //service id  
    uint16_t   command_id; //command id	  
    uint16_t   seq_num;    //seq num
    uint16_t   reversed;   //reversed
};

class PackageBase
{
public:
   PackageBase();
   virtual ~PackageBase(){}

   uchar_t* GetBuffer();
   uint32_t GetLength();
   uchar_t* GetBodyData();
   uint32_t GetBodyLength();
    
   uint16_t GetVersion() { return m_header.version; }
   uint16_t GetFlag() { return m_header.flag; }
   uint16_t GetServiceId() { return m_header.service_id; }
   uint16_t GetCommandId() { return m_header.command_id; }
   uint16_t GetSeqNum() { return m_header.seq_num; }
   uint32_t GetReversed() { return m_header.reversed; }
    
   void SetVersion(uint16_t version);
   void SetFlag(uint16_t flag);
   void SetServiceId(uint16_t service_id);
   void SetCommandId(uint16_t command_id);
   void SetError(uint16_t error);
   void SetSeqNum(uint16_t seq_num);
   void SetReversed(uint32_t reversed);
   void WriteHeader();
    
   static bool IsPackageAvailable(uchar_t* buf, uint32_t len, uint32_t& pdu_len);
   static PackageBase* ReadPackage(uchar_t* buf, uint32_t len);
   void Write(uchar_t* buf, uint32_t len) { m_simpleBuf.Write((void*)buf, len);}
   int  ReadHeader(uchar_t* buf, uint32_t len);
   void SetPackage(const google::protobuf::MessageLite* msg);

private:
   SimpleBuffer m_simpleBuf;
   PackageHeader m_header;
};
}


#endif