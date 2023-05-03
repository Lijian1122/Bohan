#include "UserInfo.h"
//#include "RouteServConn.h"
//#include "pb/protocol/Se"Bohan.Server.pb.h"
#include "pb/protocol/Login.pb.h"
using namespace ::Bohan::BaseDefine;


namespace bohan
{
UserInfo::UserInfo(string user_name)
{
	//初始化为不禁言
	m_sendFlag = false; 
	
    m_login_name = user_name;
    m_bValidate = false;
    m_user_id = 0;
    m_user_updated = false;
    m_pc_login_status = Bohan::BaseDefine::USER_STATUS_OFFLINE;
}

UserInfo::UserInfo(Bohan::Login::LoginReq msg)
{
	//初始化为不禁言
	m_sendFlag = false; 
	
	//设置字段
    // m_login_name = msg.user_id();
    // m_nick_name = msg.user_name();
    // m_group_Id = msg.group_id();
    // m_user_group = msg.user_group();      
	// m_user_head = msg.user_head();      
	//m_role_type = msg.role_type();   
	
    m_bValidate = false;
    m_user_id = 0;
    m_user_updated = false;
    m_pc_login_status = Bohan::BaseDefine::USER_STATUS_OFFLINE;
}

UserInfo::~UserInfo()
{
    //log("~ImUser, userId=%u\n", m_user_id);
}

MsgConn* UserInfo::GetUnValidateMsgConn(uint32_t handle)
{
    for (set<MsgConn*>::iterator it = m_unvalidate_conn_set.begin(); it != m_unvalidate_conn_set.end(); it++)
    {
        MsgConn* pConn = *it;
        // if (pConn->GetHandle() == handle) {
        //     return pConn;
        // }
    }
    
    return NULL;
}

MsgConn* UserInfo::GetMsgConn(uint32_t handle)
{
    MsgConn* pMsgConn = NULL;
    map<uint32_t, MsgConn*>::iterator it = m_conn_map.find(handle);
    if (it != m_conn_map.end()) {
        pMsgConn = it->second;
    }
    return pMsgConn;
}

void UserInfo::ValidateMsgConn(uint32_t handle, MsgConn* pMsgConn)
{
    AddMsgConn(handle, pMsgConn);
    DelUnValidateMsgConn(pMsgConn);
}


UserConn UserInfo::GetUserConn()
{
    uint32_t conn_cnt = 0;
    for (map<uint32_t, MsgConn*>::iterator it = m_conn_map.begin(); it != m_conn_map.end(); it++)
    {
        MsgConn* pConn = it->second;
        // if (pConn->IsOpen()) {
        //     conn_cnt++;
        // }
    }
    
    UserConn user_cnt = {m_user_id, conn_cnt};
    return user_cnt;
}

void UserInfo::BroadcastPdu(PackageBase* pPdu, MsgConn* pFromConn)
{
    for (map<uint32_t, MsgConn*>::iterator it = m_conn_map.begin(); it != m_conn_map.end(); it++)
    {
        MsgConn* pConn = it->second;
        if (pConn != pFromConn) {
            //pConn->SendPdu(pPdu);
        }
    }
}

void UserInfo::BroadcastPduWithOutMobile(PackageBase *pPdu, MsgConn* pFromConn)
{
    for (auto &it  : m_conn_map)
    {
        MsgConn* pConn = it.second;
        // if (pConn != pFromConn && CHECK_CLIENT_TYPE_PC(pConn->GetClientType())) {
        //     //pConn->SendPdu(pPdu);
        // }
    }
}

void UserInfo::BroadcastPduToMobile(PackageBase* pPdu, MsgConn* pFromConn)
{
    for (map<uint32_t, MsgConn*>::iterator it = m_conn_map.begin(); it != m_conn_map.end(); it++)
    {
        MsgConn* pConn = it->second;
        // if (pConn != pFromConn && CHECK_CLIENT_TYPE_MOBILE(pConn->GetClientType())) {
        //     //pConn->SendPdu(pPdu);
        // }
    }
}


void UserInfo::BroadcastClientMsgData(PackageBase* pPdu, uint32_t msg_id, MsgConn* pFromConn, uint32_t from_id)
{
    for (map<uint32_t, MsgConn*>::iterator it = m_conn_map.begin(); it != m_conn_map.end(); it++)
    {
        MsgConn* pConn = it->second;
        if (pConn != pFromConn) {
            //pConn->SendPdu(pPdu);
            //pConn->AddToSendList(msg_id, from_id);
        }
    }
}

void UserInfo::BroadcastData(void *buff, uint32_t len, MsgConn* pFromConn)
{
    if(!buff)
        return;
    for (map<uint32_t, MsgConn*>::iterator it = m_conn_map.begin(); it != m_conn_map.end(); it++)
    {
        MsgConn* pConn = it->second;
        
        if(pConn == NULL)
            continue;
        
        if (pConn != pFromConn) {
            pConn->Send(buff, len);
        }
    }
}

void UserInfo::HandleKickUser(MsgConn* pConn, uint32_t reason)
{
    //pConn->GetHandle()
    map<uint32_t, MsgConn*>::iterator it = m_conn_map.find(12);
    if (it != m_conn_map.end()) {
        MsgConn* pConn = it->second;
        if(pConn) {
            //log("kick service user, user_id=%u.", m_user_id);
            Bohan::Login::KickUser msg;
            msg.set_user_id(m_user_id);
            //msg.set_kick_reason((::IM::BaseDefine::KickReasonType)reason);
            PackageBase pdu;
            //pdu.SetPBMsg(&msg);
            pdu.SetServiceId(SID_LOGIN);
            pdu.SetCommandId(CID_LOGIN_KICK_USER);
            //pConn->SendPdu(&pdu);
            //pConn->SetKickOff();
            //pConn->Close();
        }
    }
}

// 只支持一个WINDOWS/MAC客户端登陆,或者一个ios/android登录
bool UserInfo::KickOutSameClientType(uint32_t client_type, uint32_t reason, MsgConn* pFromConn)
{
    for (map<uint32_t, MsgConn*>::iterator it = m_conn_map.begin(); it != m_conn_map.end(); it++)
    {
        MsgConn* pMsgConn = it->second;
        
        //16进制位移计算
        // if ((((pMsgConn->GetClientType() ^ client_type) >> 4) == 0) && (pMsgConn != pFromConn)) {
        //     HandleKickUser(pMsgConn, reason);
        //     break;
        // }
    }
    return true;
}

uint32_t UserInfo::GetClientTypeFlag()
{
    uint32_t client_type_flag = 0x00;
    map<uint32_t, MsgConn*>::iterator it = m_conn_map.begin();
    for (; it != m_conn_map.end(); it++)
    {
        MsgConn* pConn = it->second;
        //uint32_t client_type = pConn->GetClientType();
        uint32_t client_type = 0;
        if (CHECK_CLIENT_TYPE_PC(client_type))
        {
            client_type_flag |= CLIENT_TYPE_FLAG_PC;
        }
        else if (CHECK_CLIENT_TYPE_MOBILE(client_type))
        {
            client_type_flag |= CLIENT_TYPE_FLAG_MOBILE;
        }
    }
    return client_type_flag;
}


UserInfoManager::~UserInfoManager()
{
    RemoveAll();
}

UserInfoManager* UserInfoManager::GetInstance()
{
    static UserInfoManager s_manager;
    return &s_manager;
}


UserInfo* UserInfoManager::GetImUserByLoginName(string login_name)
{
    UserInfo* pUser = NULL;
    UserInfoMapByName_t::iterator it = m_im_user_map_by_name.find(login_name);
    if (it != m_im_user_map_by_name.end()) {
        pUser = it->second;
    }
    return pUser;
}

UserInfo* UserInfoManager::GetImUserById(uint32_t user_id)
{
    UserInfo* pUser = NULL;
    UserInfoMap_t::iterator it = m_im_user_map.find(user_id);
    if (it != m_im_user_map.end()) {
        pUser = it->second;
    }
    return pUser;
}

MsgConn* UserInfoManager::GetMsgConnByHandle(uint32_t user_id, uint32_t handle)
{
    MsgConn* pMsgConn = NULL;
    UserInfo* pImUser = GetImUserById(user_id);
    if (pImUser) {
        pMsgConn = pImUser->GetMsgConn(handle);
    }
    return pMsgConn;
}

bool UserInfoManager::AddImUserByLoginName(string login_name, UserInfo *pUser)
{
    bool bRet = false;
    if (GetImUserByLoginName(login_name) == NULL) {
        m_im_user_map_by_name[login_name] = pUser;
        bRet = true;
    }
    return bRet;
}

void UserInfoManager::RemoveImUserByLoginName(string login_name)
{
    m_im_user_map_by_name.erase(login_name);
}

bool UserInfoManager::AddImUserById(uint32_t user_id, UserInfo *pUser)
{
    bool bRet = false;
    if (GetImUserById(user_id) == NULL) {
        m_im_user_map[user_id] = pUser;
        bRet = true;
    }
    return bRet;
}

void UserInfoManager::RemoveImUserById(uint32_t user_id)
{
    m_im_user_map.erase(user_id);
}

void UserInfoManager::RemoveImUser(UserInfo *pUser)
{
    if (pUser != NULL) {
        RemoveImUserById(pUser->GetUserId());
        RemoveImUserByLoginName(pUser->GetLoginName());
        delete pUser;
        pUser = NULL;
    }
}

void UserInfoManager::RemoveAll()
{
    for(auto &it : m_im_user_map_by_name)
    {
        UserInfo* pUser = it.second;
        if (pUser != NULL) {
            delete pUser;
            pUser = NULL;
        }
    }
    m_im_user_map_by_name.clear();
    m_im_user_map.clear();
}

void UserInfoManager::GetOnlineUserInfo(UserStatList_t *userStatList)
{
    UserStat status;
    UserInfo* pImUser = NULL;
    for (auto &it : m_im_user_map) {
        pImUser = it.second;
        if (pImUser->IsValidate()) {
            map<uint32_t, MsgConn*>& ConnMap = pImUser->GetMsgConnMap();
            for (map<uint32_t, MsgConn*>::iterator it = ConnMap.begin(); it != ConnMap.end(); it++)
            {
                MsgConn* pConn = it->second;
                // if (pConn->IsOpen())
                // {
                //     status.user_id = pImUser->GetUserId();
                //     status.client_type = pConn->GetClientType();
                //     status.status = pConn->GetOnlineStatus();
                //     userStatList->push_back(status);
                // }
            }
        }
    }
}

void UserInfoManager::GetUserConnCnt(list<UserConn>* user_conn_list, uint32_t& total_conn_cnt)
{
    total_conn_cnt = 0;
    UserInfo* pImUser = NULL;
    for (auto &it : m_im_user_map)
    {
        pImUser = it.second;
        if (pImUser->IsValidate())
        {
            UserConn user_conn_cnt = pImUser->GetUserConn();
            user_conn_list->push_back(user_conn_cnt);
            total_conn_cnt += user_conn_cnt.conn_cnt;
        }
    }
}

void UserInfoManager::BroadcastPdu(PackageBase* pdu, uint32_t client_type_flag)
{
    UserInfo* pImUser = NULL;
    for (auto &it : m_im_user_map)
    {
        pImUser = it.second;;
        if (pImUser->IsValidate())
        {
            switch (client_type_flag) {
                case WINDOWS:
                    pImUser->BroadcastPduWithOutMobile(pdu);
                    break;
                case IOS:
                    pImUser->BroadcastPduToMobile(pdu);
                    break;
                 case ANDROID:
                    pImUser->BroadcastPduToMobile(pdu);
                    break;
                case BOTH:
                    pImUser->BroadcastPdu(pdu);
                    break;
                default:
                    break;
            }
        }
    }
}
}