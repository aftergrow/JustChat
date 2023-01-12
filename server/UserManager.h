/*************************************************************************
	> File Name: UserManager.h
	> Author: kwb
	> Mail: 
	> Created Time: Thu 24 Mar 2022 10:19:41 PM CST
 ************************************************************************/

#ifndef _USERMANAGER_H
#define _USERMANAGER_H

#include "common/macro.h"
#include "UserInfo.h"
#include "DbManager.h"

class UserManager {
private:
    UserInfo users_[10240];
    GETSETVAR(int, user_count)
    GETSETVAR(int, cur_user_id)
private:
    DbManager* db_svr_;
    int user_svr_id_;
public:
    //对于一个通用的进程应该提供的四个方法
    int Start(DbManager* db_svr, int usr_svr_id);
    int Proc();
    int Restart();
    int Shutdown();

public:
    UserInfo* GetUser(int user_id);
    int CheckExist(int user_id);
    //reg_time 为什么用传变量的方式？
    //用中断获取会影响性能；从内存读取也会会稍快一些，但传变量的方式是最快的
    int CreateUser(const char* user_name, const char* pswd, int from, int reg_time);
    int DeleteUser(int user_id);
    int SaveUser(int user_id);//todo
    int LoginCheck(const char* user_name, const char* pswd);
    int UserLogout(int user_id, int time_now);
    int GetUserIdByUserName(const char* user_name);
    const char* GetUserNameByUserId(int user_id);
    int UpdateUserLoginTime(int user_id, int time_now);
    int UpdateUserLogoutTime(int user_id, int time_now);
    int UpdateUserFreshTime(int user_id, int time_now);
};

#endif
