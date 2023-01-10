/*************************************************************************
	> File Name: MessageMenager.h
	> Author: kwb
	> Mail: 
	> Created Time: Sun 27 Mar 2022 04:18:08 PM CST
 ************************************************************************/

#ifndef _MESSAGEMENAGER_H
#define _MESSAGEMENAGER_H

#include <vector>
#include <map>
#include <pthread.h>
#include "MessageInfo.h"
#include "common/macro.h"

class DbManager;
class RelationManager;
class MessageManager {
private:
    MessageInfo messages_[10240];
    GETSETVAR(int, message_count)
    GETSETVAR(int, cur_message_id) //当前最新加入的message的 message_id
    std::map<int, std::vector<int> > user_messages_;

private:
    DbManager* db_svr_;
    RelationManager* rela_svr_;
    pthread_mutex_t mutex;

public:
    int Start(DbManager *db_svr, RelationManager *rela_svr);
    void Proc();
    void Restart();
    void Shutdown();

public:

    MessageInfo* GetMessage(int user_id,int message_id);
	MessageInfo* GetMessage(int message_id);
    int PublishMessage(MessageInfo& message);
    int DeleteMessage(int message_id);
    int PushUserMessageId(int user_id, int message_id);
    int PopUserMessageId(int user_id, int message_id);
    std::vector<int> GetMessageIds(int user_id);
};

#endif
