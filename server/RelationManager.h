/*************************************************************************
	> File Name: RelationManager.h
	> Author: kwb
	> Mail: 
	> Created Time: Sat 26 Mar 2022 11:18:01 PM CST
 ************************************************************************/

#ifndef _RELATIONMANAGER_H
#define _RELATIONMANAGER_H

#include <pthread.h>
#include "RelationInfo.h"
#include "common/macro.h"


class DbManager;
class RelationManager {
private:
    RelationInfo relations_[10240];
    GETSETVAR(int, relation_count)
    
private:
    pthread_mutex_t mutex;
    DbManager* db_svr_;

public:
    int Start(DbManager *db_svr);
    int Proc();
    int Restart();
    int Shutdown();

public:
    //RelationManager 的主键还是 user_id
    int UserRelationInit(int user_id);
    RelationInfo* GetRelation(int user_id);
    int AddFriend(int user_id, int other_id);
    int DeleteFriend(int user_id, int other_id);
    int AddBlack(int user_id, int other_id);
    int DeleteBlack(int user_id, int other_id);
};


#endif
