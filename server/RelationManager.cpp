/*************************************************************************
	> File Name: RelationManager.cpp
	> Author: kwb
	> Mail: 
	> Created Time: Sun 27 Mar 2022 01:31:36 AM CST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "common/ret_value.h"
#include "RelationManager.h"
#include "DbManager.h"

int RelationManager::Start(DbManager *db_svr){
    pthread_mutex_init(&mutex, NULL);
    db_svr_ = db_svr;
    set_relation_count(0);

    int ret = db_svr_->GetDataBegin("select * from tb_rela;");
    int user_i = 0;
    if (ret == SUCCESS) {
        //将数据库的数据读到 &users_[user_i] 里
        ret = db_svr_->GetDataOneByOne(&relations_[user_i]);
        if (ret == SUCCESS) {
            printf("user_id = %d, friend_count = %d\n",
                   relations_[user_i].user_id(),relations_[user_i].friend_count());
            user_i++;
        }
        while (ret != DB_NO_MORE_DATA) {
            ret = db_svr_->GetDataOneByOne(&relations_[user_i]);
            if (ret == SUCCESS) {
                printf("user_id = %d, friend_count = %d\n",
                   relations_[user_i].user_id(),relations_[user_i].friend_count());
                user_i++;
            }
        }
        ret = db_svr_->GetDataEnd();
        set_relation_count(user_i);
        printf("RelationCount: %d\n", relation_count_);
    } else {
        printf("RelationManager Start Failure(Db Get Relation Failed: %d)\n", ret);
        return ret;
    }
    //read cur_user_id from DB
    printf("RelationManager Start\n");
    return SUCCESS;
	//printf("[  INFO  ]Relation Manager Start\n");
}
int RelationManager::Proc(){
	//printf("Relation Manager Proc\n");
	return 0;
}

int RelationManager::Shutdown(){
	//printf("[  INFO  ]Relation Manager Shutdown\n");
	return 0;
}

int RelationManager::Restart(){
//	printf("[  INFO  ]Relation Manager Restart\n");
	return 0;
}

/* @details: 如果数据库没有该User的relation信息，需要进行初始化
 */
int RelationManager::UserRelationInit(int user_id) {
    pthread_mutex_lock(&mutex);
    for(int i=0;i<relation_count_;i++){
		if(relations_[i].user_id()==user_id){
            pthread_mutex_unlock(&mutex);
			return RELATION_EXIST;
		}
	}
    if (relation_count_<10239) {
        relations_[relation_count_].set_user_id(user_id);
        relation_count_++;
        pthread_mutex_unlock(&mutex);
        return SUCCESS;
    } else {
        pthread_mutex_unlock(&mutex);
        return RELATION_TOO_MUCH;
    }
}

RelationInfo* RelationManager::GetRelation(int user_id) {
    for (int i=0; i<relation_count_; i++) {
        if (relations_[i].user_id()==user_id) {
            return &relations_[i];
        }
    }
    return NULL;
}

int RelationManager::AddFriend(int user_id, int other_id) {
    pthread_mutex_lock(&mutex);
    RelationInfo* relation = GetRelation(user_id);
    if (relation==NULL) {
        pthread_mutex_unlock(&mutex);
        return RELATION_NOT_EXIST;
    }
    int ret = relation->AddFriend(other_id);
    if(ret == SUCCESS) {
        db_svr_->InsertData(relation);
    }
    pthread_mutex_unlock(&mutex);
    return ret;
}

int RelationManager::DeleteFriend(int user_id, int other_id) {
    pthread_mutex_lock(&mutex);
    RelationInfo* relation = GetRelation(user_id);
    if (relation==NULL) {
        pthread_mutex_unlock(&mutex);
        return RELATION_NOT_EXIST;
    }
    int ret = relation->DeleteFriend(other_id);
    if(ret == SUCCESS) {
        db_svr_->InsertData(relation);
    }
    pthread_mutex_unlock(&mutex);
    return ret;
}

int RelationManager::AddBlack(int user_id, int other_id) {
    RelationInfo* relation = GetRelation(user_id);
    if (relation==NULL) {
        return RELATION_NOT_EXIST;
    }
    int ret = relation->AddBlack(other_id);
    if(ret == SUCCESS) {
        db_svr_->InsertData(relation);
    }
    return ret;
}

int RelationManager::DeleteBlack(int user_id, int other_id) {
    RelationInfo* relation = GetRelation(user_id);
    if (relation==NULL) {
        return RELATION_NOT_EXIST;
    }
    int ret = relation->DeleteBlack(other_id);
    if(ret == SUCCESS) {
        db_svr_->InsertData(relation);
    }
    return ret;
}
