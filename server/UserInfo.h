#ifndef _USER_INFO_H_
#define _USER_INFO_H_

#include "common/macro.h"
#include <string.h>
#include "proto/user_info_base.pb.h"

class UserInfo {
    public:
        //传地址。传值的话会发生对象拷贝
        int FromPb(ssp::UserInfoBase &pb_user);
        int ToPb(ssp::UserInfoBase &pb_user);
    private:
        GETSETVAR(int, user_id)
        GETSETSTR(256, user_name)
        GETSETSTR(256, nick_name) //昵称
        GETSETVAR(int, reg_time) //注册时间
        GETSETVAR(int, from) //登录渠道
        GETSETVAR(int, login_time) //登录时间 
        GETSETVAR(int, last_login_time)
        GETSETVAR(int, fresh_time)
        GETSETSTR(256, password)
        GETSETVAR(int, logout_time)
        //这个人有没有更新过信息，有没有回写DB
        GETSETVAR(int, db_flag)
};

#endif