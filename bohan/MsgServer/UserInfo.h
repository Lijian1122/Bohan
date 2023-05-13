

#ifndef USER_INFO_H
#define USER_INFO_H

#include "ServerDefine.h"
#include "net/Connection.h"
#include "pb/protocol/BaseDefine.pb.h"
#include "pb/protocol/Login.pb.h"
#include "MsgConn.h"
#include "PackageBase.h"
#include <list>

#define MAX_ONLINE_FRIEND_CNT		100	//通知好友状态通知的最多个数

namespace bohan
{
class UserInfo
{
public:
    UserInfo(string user_id);
    UserInfo(Bohan::Login::LoginReq msg);
    ~UserInfo();
    
    void SetUserId(std::string user_id) { m_user_id = user_id; }
    std::string GetUserId() { return m_user_id; }
    void SetNickName(string nick_name) { m_nick_name = nick_name; }
    string GetNickName() { return m_nick_name; }
    bool IsValidate() { return m_bValidate; }
    void SetValidated() { m_bValidate = true; }
    uint32_t GetPCLoginStatus() { return m_pc_login_status; }
    void SetPCLoginStatus(uint32_t pc_login_status) { m_pc_login_status = pc_login_status; }
	
    string GetUserHead(){return m_user_head; }	  
    Bohan::BaseDefine::RoleType  GetRoleType(){ return  m_role_type;}   
	
	bool  GetSendFlag(){return m_sendFlag;}
	void  SetSendFlag(bool flag){ m_sendFlag = flag; }
	
    UserConn GetUserConn();
    
    bool IsMsgConnEmpty() { return m_conn_map.empty(); }
    void AddMsgConn(uint32_t handle, MsgConn* pMsgConn) { m_conn_map[handle] = pMsgConn; }
    void DelMsgConn(uint32_t handle) { m_conn_map.erase(handle); }
    MsgConn* GetMsgConn(uint32_t handle);
    void ValidateMsgConn(uint32_t handle, MsgConn* pMsgConn);
    
    void AddUnValidateMsgConn(MsgConn* pMsgConn) { m_unvalidate_conn_set.insert(pMsgConn); }
    void DelUnValidateMsgConn(MsgConn* pMsgConn) { m_unvalidate_conn_set.erase(pMsgConn); }
    MsgConn* GetUnValidateMsgConn(uint32_t handle);
    
    map<uint32_t, MsgConn*>& GetMsgConnMap() { return m_conn_map; }

    void BroadcastPdu(PackageBase* pack, MsgConn* pFromConn = NULL);
    void BroadcastPduWithOutMobile(PackageBase* pack, MsgConn* pFromConn = NULL);
    void BroadcastPduToMobile(PackageBase* pack, MsgConn* pFromConn = NULL);
    void BroadcastClientMsgData(PackageBase* pack, uint32_t msg_id, MsgConn* pFromConn = NULL, uint32_t from_id = 0);
    void BroadcastData(void* buff, uint32_t len, MsgConn* pFromConn = NULL);
        
    void HandleKickUser(MsgConn* pConn, uint32_t reason);
    
    bool KickOutSameClientType(uint32_t client_type, uint32_t reason, MsgConn* pFromConn = NULL);
    
    uint32_t GetClientTypeFlag();
private:
    string		    m_user_id;           /*userId*/
    string          m_nick_name;         /* 登录名 */
    string          m_user_head;         /*头像地址*/
    Bohan::BaseDefine::RoleType       m_role_type;      //用户类别
	
    bool            m_sendFlag;          /*是否禁言*/
	
    bool 			m_user_updated;
    uint32_t        m_pc_login_status;  // pc client login状态，1: on 0: off
    
    bool 			m_bValidate;
	
    map<uint32_t, MsgConn*>	m_conn_map;
    set<MsgConn*> m_unvalidate_conn_set;
};

typedef map<string, UserInfo*> UserInfoMap_t;
typedef map<string, UserInfo*> UserInfoMapByName_t;
typedef list<UserStat> UserStatList_t;

class UserInfoManager
{
public:
    UserInfoManager() {}
    ~UserInfoManager();
    
    static UserInfoManager* GetInstance();
    UserInfo* GetImUserById(string user_id);
    UserInfo* GetImUserByLoginName(string login_name);
    
    MsgConn* GetMsgConnByHandle(string user_id, uint32_t handle);
    bool AddImUserByLoginName(string login_name, UserInfo* pUser);
    void RemoveImUserByLoginName(string login_name);
    
    bool AddImUserById(string user_id, UserInfo* pUser);
    void RemoveImUserById(string user_id);
    
    void RemoveImUser(UserInfo* pUser);
    
    void RemoveAll();
    void GetOnlineUserInfo(UserStatList_t *userStatList);
    void GetUserConnCnt(list<UserConn>* user_conn_list, uint32_t& total_conn_cnt);
    
    void BroadcastPdu(PackageBase* pdu, uint32_t client_type_flag);
private:
    UserInfoMap_t m_im_user_map;
    UserInfoMapByName_t m_im_user_map_by_name;
};

void get_online_user_info(list<UserStat>* online_user_info);
}
#endif
