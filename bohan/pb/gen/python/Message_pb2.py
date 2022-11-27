# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: Message.proto
"""Generated protocol buffer code."""
from google.protobuf.internal import builder as _builder
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import BaseDefine_pb2 as BaseDefine__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\rMessage.proto\x12\rBohan.Message\x1a\x10\x42\x61seDefine.proto\"\xaf\x01\n\x07MsgData\x12\x14\n\x0c\x66rom_user_id\x18\x01 \x02(\r\x12\x15\n\rto_session_id\x18\x02 \x02(\r\x12\x0e\n\x06msg_id\x18\x03 \x02(\r\x12\x13\n\x0b\x63reate_time\x18\x04 \x02(\r\x12+\n\x08msg_type\x18\x05 \x02(\x0e\x32\x19.Bohan.BaseDefine.MsgType\x12\x10\n\x08msg_data\x18\x06 \x02(\x0c\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"v\n\nMsgDataAck\x12\x0f\n\x07user_id\x18\x01 \x02(\r\x12\x12\n\nsession_id\x18\x02 \x02(\r\x12\x0e\n\x06msg_id\x18\x03 \x02(\r\x12\x33\n\x0csession_type\x18\x04 \x02(\x0e\x32\x1d.Bohan.BaseDefine.SessionType\"z\n\x0eMsgDataReadAck\x12\x0f\n\x07user_id\x18\x01 \x02(\r\x12\x12\n\nsession_id\x18\x02 \x02(\r\x12\x0e\n\x06msg_id\x18\x03 \x02(\r\x12\x33\n\x0csession_type\x18\x04 \x02(\x0e\x32\x1d.Bohan.BaseDefine.SessionType\"}\n\x11MsgDataReadNotify\x12\x0f\n\x07user_id\x18\x01 \x02(\r\x12\x12\n\nsession_id\x18\x02 \x02(\r\x12\x0e\n\x06msg_id\x18\x03 \x02(\r\x12\x33\n\x0csession_type\x18\x04 \x02(\x0e\x32\x1d.Bohan.BaseDefine.SessionType\"\x0f\n\rClientTimeReq\"$\n\rClientTimeRsp\x12\x13\n\x0bserver_time\x18\x01 \x02(\r\"7\n\x0fUnreadMsgCntReq\x12\x0f\n\x07user_id\x18\x01 \x02(\r\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"\x81\x01\n\x0fUnreadMsgCntRsp\x12\x0f\n\x07user_id\x18\x01 \x02(\r\x12\x11\n\ttotal_cnt\x18\x02 \x02(\r\x12\x35\n\x0funreadinfo_list\x18\x03 \x03(\x0b\x32\x1c.Bohan.BaseDefine.UnreadInfo\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"\xa5\x01\n\rGetMsgListReq\x12\x0f\n\x07user_id\x18\x01 \x02(\r\x12\x33\n\x0csession_type\x18\x02 \x02(\x0e\x32\x1d.Bohan.BaseDefine.SessionType\x12\x12\n\nsession_id\x18\x03 \x02(\r\x12\x14\n\x0cmsg_id_begin\x18\x04 \x02(\r\x12\x0f\n\x07msg_cnt\x18\x05 \x02(\r\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"\xc1\x01\n\rGetMsgListRsp\x12\x0f\n\x07user_id\x18\x01 \x02(\r\x12\x33\n\x0csession_type\x18\x02 \x02(\x0e\x32\x1d.Bohan.BaseDefine.SessionType\x12\x12\n\nsession_id\x18\x03 \x02(\r\x12\x14\n\x0cmsg_id_begin\x18\x04 \x02(\r\x12+\n\x08msg_list\x18\x05 \x03(\x0b\x32\x19.Bohan.BaseDefine.MsgInfo\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"\x82\x01\n\x11GetLatestMsgIdReq\x12\x0f\n\x07user_id\x18\x01 \x02(\r\x12\x33\n\x0csession_type\x18\x02 \x02(\x0e\x32\x1d.Bohan.BaseDefine.SessionType\x12\x12\n\nsession_id\x18\x03 \x02(\r\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"\x99\x01\n\x11GetLatestMsgIdRsp\x12\x0f\n\x07user_id\x18\x01 \x02(\r\x12\x33\n\x0csession_type\x18\x02 \x02(\x0e\x32\x1d.Bohan.BaseDefine.SessionType\x12\x12\n\nsession_id\x18\x03 \x02(\r\x12\x15\n\rlatest_msg_id\x18\x04 \x02(\r\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"\x93\x01\n\rGetMsgByIdReq\x12\x0f\n\x07user_id\x18\x01 \x02(\r\x12\x33\n\x0csession_type\x18\x02 \x02(\x0e\x32\x1d.Bohan.BaseDefine.SessionType\x12\x12\n\nsession_id\x18\x03 \x02(\r\x12\x13\n\x0bmsg_id_list\x18\x04 \x03(\r\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"\xad\x01\n\x0fIMGetMsgByIdRsp\x12\x0f\n\x07user_id\x18\x01 \x02(\r\x12\x33\n\x0csession_type\x18\x02 \x02(\x0e\x32\x1d.Bohan.BaseDefine.SessionType\x12\x12\n\nsession_id\x18\x03 \x02(\r\x12+\n\x08msg_list\x18\x04 \x03(\x0b\x32\x19.Bohan.BaseDefine.MsgInfo\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\x42\x16\n\x12\x63om.bohan.protobufH\x03')

_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, globals())
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'Message_pb2', globals())
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\022com.bohan.protobufH\003'
  _MSGDATA._serialized_start=51
  _MSGDATA._serialized_end=226
  _MSGDATAACK._serialized_start=228
  _MSGDATAACK._serialized_end=346
  _MSGDATAREADACK._serialized_start=348
  _MSGDATAREADACK._serialized_end=470
  _MSGDATAREADNOTIFY._serialized_start=472
  _MSGDATAREADNOTIFY._serialized_end=597
  _CLIENTTIMEREQ._serialized_start=599
  _CLIENTTIMEREQ._serialized_end=614
  _CLIENTTIMERSP._serialized_start=616
  _CLIENTTIMERSP._serialized_end=652
  _UNREADMSGCNTREQ._serialized_start=654
  _UNREADMSGCNTREQ._serialized_end=709
  _UNREADMSGCNTRSP._serialized_start=712
  _UNREADMSGCNTRSP._serialized_end=841
  _GETMSGLISTREQ._serialized_start=844
  _GETMSGLISTREQ._serialized_end=1009
  _GETMSGLISTRSP._serialized_start=1012
  _GETMSGLISTRSP._serialized_end=1205
  _GETLATESTMSGIDREQ._serialized_start=1208
  _GETLATESTMSGIDREQ._serialized_end=1338
  _GETLATESTMSGIDRSP._serialized_start=1341
  _GETLATESTMSGIDRSP._serialized_end=1494
  _GETMSGBYIDREQ._serialized_start=1497
  _GETMSGBYIDREQ._serialized_end=1644
  _IMGETMSGBYIDRSP._serialized_start=1647
  _IMGETMSGBYIDRSP._serialized_end=1820
# @@protoc_insertion_point(module_scope)
