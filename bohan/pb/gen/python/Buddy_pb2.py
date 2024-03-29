# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: Buddy.proto
"""Generated protocol buffer code."""
from google.protobuf.internal import builder as _builder
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import BaseDefine_pb2 as BaseDefine__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x0b\x42uddy.proto\x12\x0b\x42ohan.Buddy\x1a\x10\x42\x61seDefine.proto\"[\n\x17RecentContactSessionReq\x12\x0f\n\x07user_id\x18\x01 \x02(\x0c\x12\x1a\n\x12latest_update_time\x18\x02 \x02(\r\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"\x83\x01\n\x17RecentContactSessionRsp\x12\x0f\n\x07user_id\x18\x01 \x02(\x0c\x12\x42\n\x14\x63ontact_session_list\x18\x02 \x03(\x0b\x32$.Bohan.BaseDefine.ContactSessionInfo\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"?\n\x0eUserStatNotify\x12-\n\tuser_stat\x18\x01 \x02(\x0b\x32\x1a.Bohan.BaseDefine.UserStat\"J\n\x0cUsersInfoReq\x12\x0f\n\x07user_id\x18\x01 \x02(\x0c\x12\x14\n\x0cuser_id_list\x18\x02 \x03(\x0c\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"h\n\x0cUsersInfoRsp\x12\x0f\n\x07user_id\x18\x01 \x02(\x0c\x12\x32\n\x0euser_info_list\x18\x02 \x03(\x0b\x32\x1a.Bohan.BaseDefine.UserInfo\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"\x81\x01\n\x10RemoveSessionReq\x12\x0f\n\x07user_id\x18\x01 \x02(\x0c\x12\x33\n\x0csession_type\x18\x02 \x02(\x0e\x32\x1d.Bohan.BaseDefine.SessionType\x12\x12\n\nsession_id\x18\x03 \x02(\x0c\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"\x96\x01\n\x10RemoveSessionRsp\x12\x0f\n\x07user_id\x18\x01 \x02(\x0c\x12\x13\n\x0bresult_code\x18\x02 \x02(\r\x12\x33\n\x0csession_type\x18\x03 \x02(\x0e\x32\x1d.Bohan.BaseDefine.SessionType\x12\x12\n\nsession_id\x18\x04 \x02(\r\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"N\n\nAllUserReq\x12\x0f\n\x07user_id\x18\x01 \x02(\x0c\x12\x1a\n\x12latest_update_time\x18\x02 \x02(\r\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"}\n\nAllUserRsp\x12\x0f\n\x07user_id\x18\x01 \x02(\x0c\x12\x1a\n\x12latest_update_time\x18\x02 \x02(\r\x12-\n\tuser_list\x18\x03 \x03(\x0b\x32\x1a.Bohan.BaseDefine.UserInfo\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"J\n\x0cUsersStatReq\x12\x0f\n\x07user_id\x18\x01 \x02(\x0c\x12\x14\n\x0cuser_id_list\x18\x02 \x03(\x0c\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"h\n\x0cUsersStatRsp\x12\x0f\n\x07user_id\x18\x01 \x02(\x0c\x12\x32\n\x0euser_stat_list\x18\x02 \x03(\x0b\x32\x1a.Bohan.BaseDefine.UserStat\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"K\n\x0f\x43hangeAvatarReq\x12\x0f\n\x07user_id\x18\x01 \x02(\x0c\x12\x12\n\navatar_url\x18\x02 \x02(\t\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"L\n\x0f\x43hangeAvatarRsp\x12\x0f\n\x07user_id\x18\x01 \x02(\x0c\x12\x13\n\x0bresult_code\x18\x02 \x02(\r\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"Z\n\x13PCLoginStatusNotify\x12\x0f\n\x07user_id\x18\x01 \x02(\x0c\x12\x32\n\nlogin_stat\x18\x02 \x02(\x0e\x32\x1e.Bohan.BaseDefine.UserStatType\"o\n\x13RemoveSessionNotify\x12\x0f\n\x07user_id\x18\x01 \x02(\x0c\x12\x33\n\x0csession_type\x18\x02 \x02(\x0e\x32\x1d.Bohan.BaseDefine.SessionType\x12\x12\n\nsession_id\x18\x03 \x02(\r\"Q\n\rDepartmentReq\x12\x0f\n\x07user_id\x18\x01 \x02(\x0c\x12\x1a\n\x12latest_update_time\x18\x02 \x02(\r\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"\x82\x01\n\rDepartmentRsp\x12\x0f\n\x07user_id\x18\x01 \x02(\x0c\x12\x1a\n\x12latest_update_time\x18\x02 \x02(\r\x12/\n\tdept_list\x18\x03 \x03(\x0b\x32\x1c.Bohan.BaseDefine.DepartInfo\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\x42\x16\n\x12\x63om.bohan.protobufH\x03')

_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, globals())
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'Buddy_pb2', globals())
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\022com.bohan.protobufH\003'
  _RECENTCONTACTSESSIONREQ._serialized_start=46
  _RECENTCONTACTSESSIONREQ._serialized_end=137
  _RECENTCONTACTSESSIONRSP._serialized_start=140
  _RECENTCONTACTSESSIONRSP._serialized_end=271
  _USERSTATNOTIFY._serialized_start=273
  _USERSTATNOTIFY._serialized_end=336
  _USERSINFOREQ._serialized_start=338
  _USERSINFOREQ._serialized_end=412
  _USERSINFORSP._serialized_start=414
  _USERSINFORSP._serialized_end=518
  _REMOVESESSIONREQ._serialized_start=521
  _REMOVESESSIONREQ._serialized_end=650
  _REMOVESESSIONRSP._serialized_start=653
  _REMOVESESSIONRSP._serialized_end=803
  _ALLUSERREQ._serialized_start=805
  _ALLUSERREQ._serialized_end=883
  _ALLUSERRSP._serialized_start=885
  _ALLUSERRSP._serialized_end=1010
  _USERSSTATREQ._serialized_start=1012
  _USERSSTATREQ._serialized_end=1086
  _USERSSTATRSP._serialized_start=1088
  _USERSSTATRSP._serialized_end=1192
  _CHANGEAVATARREQ._serialized_start=1194
  _CHANGEAVATARREQ._serialized_end=1269
  _CHANGEAVATARRSP._serialized_start=1271
  _CHANGEAVATARRSP._serialized_end=1347
  _PCLOGINSTATUSNOTIFY._serialized_start=1349
  _PCLOGINSTATUSNOTIFY._serialized_end=1439
  _REMOVESESSIONNOTIFY._serialized_start=1441
  _REMOVESESSIONNOTIFY._serialized_end=1552
  _DEPARTMENTREQ._serialized_start=1554
  _DEPARTMENTREQ._serialized_end=1635
  _DEPARTMENTRSP._serialized_start=1638
  _DEPARTMENTRSP._serialized_end=1768
# @@protoc_insertion_point(module_scope)
