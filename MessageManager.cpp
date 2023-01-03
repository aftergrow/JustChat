/*************************************************************************
	> File Name: MessageMenager.cpp
	> Author: kwb
	> Mail: 
	> Created Time: Sun 27 Mar 2022 04:16:03 PM CST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "common/ret_value.h"
#include "MessageManager.h"
#include "RelationManager.h"
#include "RelationInfo.h"
#include "DbManager.h"

#define PUBLISH_MESSAGE_M

int MessageManager::Start(DbManager *db_svr, RelationManager *rela_svr){
    pthread_mutex_init(&mutex, NULL);

    db_svr_ = db_svr;
    rela_svr_ = rela_svr;
    set_cur_message_id(db_svr_->GetCurMessId());
    printf("cur_mess_id: %d\n",cur_message_id());
    //Get Message ID from DB
	set_message_count(0);
    int ret = db_svr_->GetDataBegin("select * from tb_mess;");
    int mess_i = 0;
    RelationInfo* rela_info = nullptr;
    if (ret == SUCCESS) {
        //将数据库的数据读到 &users_[user_i] 里
        ret = db_svr_->GetDataOneByOne(&messages_[mess_i]);
        PushUserMessageId(messages_[mess_i].user_id(), messages_[mess_i].message_id());
        rela_info = rela_svr_->GetRelation(messages_[mess_i].user_id());
        if (rela_info) {
            for (int i = 0; i < rela_info->friend_count(); i++) {
                int friend_id = rela_info->GetFriendByIndex(i);
                PushUserMessageId(friend_id, messages_[mess_i].message_id());
            }
        }
        if (ret == SUCCESS) {
            printf("%d %d %s\n",messages_[mess_i].user_id(),messages_[mess_i].message_id(),messages_[mess_i].content());
            mess_i++;
        }
        while (ret != DB_NO_MORE_DATA) {
            ret = db_svr_->GetDataOneByOne(&messages_[mess_i]);
            PushUserMessageId(messages_[mess_i].user_id(), messages_[mess_i].message_id());
            rela_info = rela_svr_->GetRelation(messages_[mess_i].user_id());
            if (rela_info) {
                for (int i = 0; i < rela_info->friend_count(); i++) {
                    int friend_id = rela_info->GetFriendByIndex(i);
                    PushUserMessageId(friend_id, messages_[mess_i].message_id());
                }
            }
            if (ret == SUCCESS) {
                printf("%d %d %s\n",messages_[mess_i].user_id(),messages_[mess_i].message_id(),messages_[mess_i].content());
                mess_i++;
            }
        }
        ret = db_svr_->GetDataEnd();
        set_message_count(mess_i);
        printf("MessageCount: %d\n", message_count_);
    } else {
        printf("MessageManager Start Failure(Db Get Message Failed: %d)\n", ret);
        return ret;
    }
    printf("MessageManager Start!\n");
    return SUCCESS;
}
void MessageManager::Proc(){

}
void MessageManager::Shutdown(){

}
void MessageManager::Restart(){

}

MessageInfo* MessageManager::GetMessage(int user_id,int message_id){
	for(int i=0;i<message_count_;i++){
		if(messages_[i].user_id()==user_id && messages_[i].message_id()==message_id){
			return &messages_[i];
		}
	}
	return NULL;
}

MessageInfo* MessageManager::GetMessage(int message_id){
	for(int i=0;i<message_count_;i++){
		if(messages_[i].message_id()==message_id){
			return &messages_[i];
		}
	}	
	return NULL;
}

int MessageManager::PublishMessage(MessageInfo& message){
	if(message_count_==10239){
		return MESSAGE_TOO_MUCH;
	}
    int ret_mess_id=cur_message_id();
	messages_[message_count_].set_message_id(cur_message_id());
	messages_[message_count_].set_user_id(message.user_id());
	messages_[message_count_].set_publish_time(message.publish_time());
	messages_[message_count_].set_content(message.content());

	db_svr_->InsertData(&messages_[message_count_]);

    #ifdef PUBLISH_MESSAGE_M
    printf("publish message.\n");
    printf("message_id: %d, user_id: %d, publish_time: %d, content: %s\n",
            messages_[message_count_].message_id(),
            messages_[message_count_].user_id(), 
            messages_[message_count_].publish_time(),
            messages_[message_count_].content());
    #endif

    cur_message_id_++;
	message_count_++;

    db_svr_->ChangeCurId(cur_message_id(), "mess_id"); 
	return ret_mess_id;
}

int MessageManager::DeleteMessage(int message_id) {
    for (int i=0; i<message_count_; i++) {
        if (messages_[i].message_id()==message_id) {
            messages_[i].set_user_id(messages_[message_count_-1].user_id());
            messages_[i].set_message_id(messages_[message_count_-1].message_id());
            messages_[i].set_publish_time(messages_[message_count_-1].publish_time());
            messages_[i].set_content(messages_[message_count_-1].content());
            message_count_--;
            return SUCCESS;
        }
    }
    return MESSAGE_NOT_EXIST;
}

int MessageManager::PushUserMessageId(int user_id, int message_id) {
    std::map<int, std::vector<int> >::iterator iter;
    pthread_mutex_lock(&mutex);
    iter = user_messages_.find(user_id);
    if (iter==user_messages_.end()) {
        std::vector<int> mess_ids;
        mess_ids.push_back(message_id);
        user_messages_.insert(std::pair<int, std::vector<int> >(user_id, mess_ids));
        pthread_mutex_unlock(&mutex);
        return 1;
    }
    iter->second.push_back(message_id);
    pthread_mutex_unlock(&mutex);
    return 0;
}

int MessageManager::PopUserMessageId(int user_id, int message_id) {
    /* std::vector<int> v_mess_id = GetMessageIds(user_id);
    if (v_mess_id == std::vector<int>()) {
        return -1;
    }
    iter->second.push_back(message_id);
    return 0; */
    return 0;
}

std::vector<int> MessageManager::GetMessageIds(int user_id) {
    std::map<int, std::vector<int> >::iterator iter;
    iter = user_messages_.find(user_id);
    if (iter == user_messages_.end()) {
        return std::vector<int>();
    }
    return iter->second;
}