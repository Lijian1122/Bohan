# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: Group.proto
"""Generated protocol buffer code."""
from google.protobuf.internal import builder as _builder
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import BaseDefine_pb2 as BaseDefine__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x0bGroup.proto\x12\x0b\x42ohan.Group\x1a\x10\x42\x61seDefine.proto\":\n\x12NormalGroupListReq\x12\x0f\n\x07user_id\x18\x01 \x02(\r\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"z\n\x12NormalGroupListRsp\x12\x0f\n\x07user_id\x18\x01 \x02(\r\x12>\n\x12group_version_list\x18\x02 \x03(\x0b\x32\".Bohan.BaseDefine.GroupVersionInfo\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"x\n\x10GroupInfoListReq\x12\x0f\n\x07user_id\x18\x01 \x02(\r\x12>\n\x12group_version_list\x18\x02 \x03(\x0b\x32\".Bohan.BaseDefine.GroupVersionInfo\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"n\n\x10GroupInfoListRsp\x12\x0f\n\x07user_id\x18\x01 \x02(\r\x12\x34\n\x0fgroup_info_list\x18\x02 \x03(\x0b\x32\x1b.Bohan.BaseDefine.GroupInfo\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"\xb9\x01\n\x0eGroupCreateReq\x12\x0f\n\x07user_id\x18\x01 \x02(\r\x12?\n\ngroup_type\x18\x02 \x02(\x0e\x32\x1b.Bohan.BaseDefine.GroupType:\x0eGROUP_TYPE_TMP\x12\x12\n\ngroup_name\x18\x03 \x02(\t\x12\x14\n\x0cgroup_avatar\x18\x04 \x02(\t\x12\x16\n\x0emember_id_list\x18\x05 \x03(\r\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"\x87\x01\n\x0eGroupCreateRsp\x12\x0f\n\x07user_id\x18\x01 \x02(\r\x12\x13\n\x0bresult_code\x18\x02 \x02(\r\x12\x10\n\x08group_id\x18\x03 \x01(\r\x12\x12\n\ngroup_name\x18\x04 \x02(\t\x12\x14\n\x0cuser_id_list\x18\x05 \x03(\r\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"\x9e\x01\n\x14GroupChangeMemberReq\x12\x0f\n\x07user_id\x18\x01 \x02(\r\x12\x36\n\x0b\x63hange_type\x18\x02 \x02(\x0e\x32!.Bohan.BaseDefine.GroupModifyType\x12\x10\n\x08group_id\x18\x03 \x02(\r\x12\x16\n\x0emember_id_list\x18\x04 \x03(\r\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"\xcf\x01\n\x14GroupChangeMemberRsp\x12\x0f\n\x07user_id\x18\x01 \x02(\r\x12\x36\n\x0b\x63hange_type\x18\x02 \x02(\x0e\x32!.Bohan.BaseDefine.GroupModifyType\x12\x13\n\x0bresult_code\x18\x03 \x02(\r\x12\x10\n\x08group_id\x18\x04 \x02(\r\x12\x18\n\x10\x63ur_user_id_list\x18\x05 \x03(\r\x12\x18\n\x10\x63hg_user_id_list\x18\x06 \x03(\r\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"_\n\x0eGroupShieldReq\x12\x0f\n\x07user_id\x18\x01 \x02(\r\x12\x10\n\x08group_id\x18\x02 \x02(\r\x12\x15\n\rshield_status\x18\x03 \x02(\r\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"]\n\x0eGroupShieldRsp\x12\x0f\n\x07user_id\x18\x01 \x02(\r\x12\x10\n\x08group_id\x18\x02 \x02(\r\x12\x13\n\x0bresult_code\x18\x03 \x02(\r\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"\xa8\x01\n\x17GroupChangeMemberNotify\x12\x0f\n\x07user_id\x18\x01 \x02(\r\x12\x36\n\x0b\x63hange_type\x18\x02 \x02(\x0e\x32!.Bohan.BaseDefine.GroupModifyType\x12\x10\n\x08group_id\x18\x03 \x02(\r\x12\x18\n\x10\x63ur_user_id_list\x18\x04 \x03(\r\x12\x18\n\x10\x63hg_user_id_list\x18\x05 \x03(\rB\x16\n\x12\x63om.bohan.protobufH\x03')

_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, globals())
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'Group_pb2', globals())
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\022com.bohan.protobufH\003'
  _NORMALGROUPLISTREQ._serialized_start=46
  _NORMALGROUPLISTREQ._serialized_end=104
  _NORMALGROUPLISTRSP._serialized_start=106
  _NORMALGROUPLISTRSP._serialized_end=228
  _GROUPINFOLISTREQ._serialized_start=230
  _GROUPINFOLISTREQ._serialized_end=350
  _GROUPINFOLISTRSP._serialized_start=352
  _GROUPINFOLISTRSP._serialized_end=462
  _GROUPCREATEREQ._serialized_start=465
  _GROUPCREATEREQ._serialized_end=650
  _GROUPCREATERSP._serialized_start=653
  _GROUPCREATERSP._serialized_end=788
  _GROUPCHANGEMEMBERREQ._serialized_start=791
  _GROUPCHANGEMEMBERREQ._serialized_end=949
  _GROUPCHANGEMEMBERRSP._serialized_start=952
  _GROUPCHANGEMEMBERRSP._serialized_end=1159
  _GROUPSHIELDREQ._serialized_start=1161
  _GROUPSHIELDREQ._serialized_end=1256
  _GROUPSHIELDRSP._serialized_start=1258
  _GROUPSHIELDRSP._serialized_end=1351
  _GROUPCHANGEMEMBERNOTIFY._serialized_start=1354
  _GROUPCHANGEMEMBERNOTIFY._serialized_end=1522
# @@protoc_insertion_point(module_scope)