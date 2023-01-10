/*************************************************************************
	> File Name: DbManager.h
	> Author: kwb
	> Mail: 
	> Created Time: Tue 19 Apr 2022 09:04:48 PM CST
 ************************************************************************/

#ifndef _DBMANAGER_H
#define _DBMANAGER_H

#include <string>
#include "mysql/mysql.h"
#include <iostream>
#include "common/macro.h"
#include "proto/message_info_base.pb.h"
#include "proto/relation_info_base.pb.h"
#include "proto/photo_info_base.pb.h"
#include "common/ret_value.h"

class UserInfo;
class RelationInfo;
class MessageInfo;
class PhotoInfo;
class DbManager {
private:
    //transection：切断,截断，防止被别人打断
    GETSETVAR(int, transection); //1表示忙，0表示空闲
private:
    MYSQL *conn;
    MYSQL_RES *result;
    MYSQL_ROW row;
private:
    int db_svr_id;
public:
    int Init();
    int execSql(std::string sql);
    int GetDataBegin(std::string sql);
    //begin和end用于设置 GetUsersOneByOne() 这个事务
    int GetUsersBegin(int usr_svr_id);
    int GetDataOneByOne(RelationInfo* t);
    int GetDataOneByOne(MessageInfo* t);
    int GetDataOneByOne(PhotoInfo* t);    
    int GetUsersOneByOne(UserInfo* user); //做成一个事务
    int GetDataEnd();
    int GetUsersEnd();
    int GetCurUserId(int usr_svr_id);
    int GetCurMessId();
    int InsertUser(UserInfo* user, int usr_svr_id);

    //insert or delete
    int ChangeData(std::string sql);

    int tb_rela_query(const char* user_id);
    int InsertData(RelationInfo* t);

    int InsertData(MessageInfo* t);
    int UpdateData(PhotoInfo* t);

    //更改user CurId
    int ChangeCurId(int user_svr_id, int cur_id, char* key_str);
    //更改其他的 CurId
    int ChangeCurId(int cur_mess_id, const char *key_str);

    template<typename T>
    int GetDataOneByOne(T* t) {
        if (result) {
            row = mysql_fetch_row(result);
            if (row == NULL) {
                return DB_NO_MORE_DATA;
            }
            return DB_DATA_TYPE_ERRO;
        } else {		
            return DB_NO_MORE_DATA;
        }
        return SUCCESS;
    }

    template<typename T>
    int InsertData(T* t) {
        return DB_DATA_TYPE_ERRO;
    }
};

#endif
