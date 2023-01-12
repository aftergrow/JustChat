/*************************************************************************
	> File Name: UserInfo.cpp
	> Author: kwb
	> Mail: 
	> Created Time: Thu 21 Apr 2022 05:41:06 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UserInfo.h"

int UserInfo::FromPb(ssp::UserInfoBase &pb_user) {
	set_user_id(pb_user.user_id());
	//string类型不能直接转化为 char* 类型
	set_user_name(pb_user.user_name().c_str());
	set_nick_name(pb_user.nick_name().c_str());
	set_reg_time(pb_user.reg_time());
	set_password(pb_user.password().c_str());
	set_from(pb_user.from());
	set_login_time(pb_user.login_time());
	set_last_login_time(pb_user.last_login_time());
	set_logout_time(pb_user.logout_time());
	set_fresh_time(pb_user.fresh_time());
	set_db_flag(pb_user.db_flag());
	return 0;
}

int UserInfo::ToPb(ssp::UserInfoBase &pb_user) {
	pb_user.set_user_id(user_id());
	//这里可以直接传 char* 类型。c++兼容c
	pb_user.set_user_name(user_name());
	pb_user.set_nick_name(nick_name());
	pb_user.set_reg_time(reg_time());
	pb_user.set_password(password());
	pb_user.set_from(from());
	pb_user.set_login_time(login_time());
	pb_user.set_last_login_time(last_login_time());
	pb_user.set_logout_time(logout_time());
	pb_user.set_fresh_time(fresh_time());
	pb_user.set_db_flag(db_flag());
	return 0;
}
