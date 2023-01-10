/*************************************************************************
	> File Name: UserManager.cpp
	> Author: kwb
	> Mail: 
	> Created Time: Thu 24 Mar 2022 10:59:20 PM CST
 ************************************************************************/
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "common/ret_value.h"
 #include "UserManager.h"

int UserManager::Start(DbManager* db_svr, int usr_svr_id) {
    user_svr_id_ = usr_svr_id;
    db_svr_ = db_svr;
    //Get Current User ID from DB
    set_cur_user_id(db_svr_->GetCurUserId(usr_svr_id));
    printf("cur_user_id: %d\n",cur_user_id());
    //set_cur_user_id(10001);
    set_user_count(0);
    //Get users from DB
    int ret = db_svr_->GetUsersBegin(usr_svr_id);
    int user_i = 0;
    if (ret == SUCCESS) {
        //将数据库的数据读到 &users_[user_i] 里
        ret = db_svr_->GetUsersOneByOne(&users_[user_i]);
        if (ret == SUCCESS) {
            printf("%d %s %s\n",users_[user_i].user_id(),users_[user_i].user_name(),users_[user_i].password());
            user_i++;
        }
        while (ret != DB_NO_MORE_DATA) {
            ret = db_svr_->GetUsersOneByOne(&users_[user_i]);
            if (ret == SUCCESS) {
                printf("%d %s %s\n",users_[user_i].user_id(),users_[user_i].user_name(),users_[user_i].password());
                user_i++;
            }
        }
        ret = db_svr_->GetUsersEnd();
        set_user_count(user_i);
        printf("UserCount: %d\n", user_count_);
    } else {
        printf("UserManager Start Failure(Db Get User Failed: %d)\n", ret);
        return ret;
    }
    //read cur_user_id from DB
    printf("UserManager Start\n");
    return SUCCESS;
}

int UserManager::Proc() {
    return SUCCESS;

}

int UserManager::Restart() {
    return SUCCESS;

}

int UserManager::Shutdown() {
    return SUCCESS;

}

UserInfo* UserManager::GetUser(int user_id) {
    for (int i=0; i<user_count_; i++) {
        if (users_[i].user_id()==user_id) {
            return &users_[i];
        }
    }    
    return NULL;
}

int UserManager::CheckExist(int user_id) {
    for (int i=0; i<user_count_; i++) {
        if (users_[i].user_id()==user_id) {
            return USER_EXIST;
        }
    }    
    return USER_NOT_EXIST;
}

int UserManager::CreateUser(const char* user_name, const char* pswd, int from, int reg_time) {
    int user_index_saved = 1;
    /* for (int i = 0; i < user_count_; i++) {
        if (strcmp(users_[i].user_name(), user_name)==0) {
            return USER_EXIST;
        } 
    } */

    if (user_count_<10239) {
        users_[user_count_].set_user_id(cur_user_id()); // 因为需要落地(从文件或者数据库读取)，所以先空着
        users_[user_count_].set_user_name(user_name);
        users_[user_count_].set_password(pswd);
        users_[user_count_].set_from(from);
        users_[user_count_].set_reg_time(reg_time);
        users_[user_count_].set_db_flag(FLAG_INSERT);
        user_index_saved = user_count_;
        user_count_++;
    } else {
        return USER_TOO_MUCH;
    }
    int ret_user_id = cur_user_id();
    char key_str[20] = "user_id";
    set_cur_user_id(cur_user_id()+2); //设置 slot user_id
    db_svr_->ChangeCurId(user_svr_id_, cur_user_id(), key_str);
    printf("changed!cur_user_id: %d\n", cur_user_id());

    //InsertUser(),应该是要存进数据库里
    db_svr_->InsertUser(&users_[user_index_saved], user_svr_id_);
    return ret_user_id;
}

int UserManager::DeleteUser(int user_id) {
    for (int i=0; i<user_count_; i++) {
        if (users_[i].user_id()==user_id) {
            users_[i].set_db_flag(FLAG_DELETE);
            return SUCCESS;
        }
    }  
    return USER_NOT_EXIST;
}

int UserManager::SaveUser(int user_id) {
    return SUCCESS;    
}

int UserManager::LoginCheck(const char* user_name, const char* pswd) {
    for (int i = 0; i < user_count_; i++) {
        if (strcmp(users_[i].user_name(), user_name)==0) {
            if (strcmp(users_[i].password(), pswd)==0) {
                return users_[i].user_id();
            } else {
                return WRONG_PASSWORD;
            }
        } 
    }
    return USER_NOT_EXIST; 
}

int UserManager::UserLogout(int user_id, int time_now) {
    UserInfo* user = GetUser(user_id);
    if (user == NULL) {
        return USER_NOT_EXIST;
    }
    user->set_logout_time(time_now);
    user->set_db_flag(FLAG_UPDATE);
    return SUCCESS;
}

int UserManager::GetUserIdByUserName(const char* user_name) {
    for (int i = 0; i < user_count_; i++) {
        if (strcmp(users_[i].user_name(), user_name)==0) {
            return users_[i].user_id();
        } 
    }
    return USER_NOT_EXIST; 
}

const char* UserManager::GetUserNameByUserId(int user_id) {
    for (int i=0; i<user_count_; i++) {
        if (users_[i].user_id()==user_id) {
            return users_[i].user_name();
        }
    }  
    return "USER_NOT_EXIST"; 
}

int UserManager::UpdateUserLoginTime(int user_id, int time_now) {
    UserInfo* user = GetUser(user_id);
    if (user == NULL) {
        return USER_NOT_EXIST;
    }
    user->set_login_time(time_now);
    user->set_db_flag(FLAG_UPDATE);
    return SUCCESS;
    
}

int UserManager::UpdateUserLogoutTime(int user_id, int time_now) {
    UserInfo* user = GetUser(user_id);
    if (user == NULL) {
        return USER_NOT_EXIST;
    }
    user->set_logout_time(time_now);
    user->set_db_flag(FLAG_UPDATE);
    return SUCCESS;
    
}

int UserManager::UpdateUserFreshTime(int user_id, int time_now) {
    UserInfo* user = GetUser(user_id);
    if (user == NULL) {
        return USER_NOT_EXIST;
    }
    user->set_fresh_time(time_now);
    user->set_db_flag(FLAG_UPDATE);
    return SUCCESS;
}

