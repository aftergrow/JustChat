#ifndef _RELATION_INFO_H_
#define _RELATION_INFO_H_

#include "common/macro.h"
#include <string.h>
#include "proto/relation_info_base.pb.h"

class RelationInfo {
private:
    GETSETVAR(int, user_id)
    GETSETVAR(int, friend_count) //DB初始化读进来的
    int friend_list_[10240]; //存储好友的 user_id
    GETSETVAR(int, black_count)
    int black_list_[10240];
public:
    int FromPb(ssp::RelationInfoBase &pb_rela);
    int ToPb(ssp::RelationInfoBase &pb_rela);

    int CheckFriend(int other_id);
    int CheckBlack(int other_id);
    int AddFriend(int other_id);
    int AddBlack(int other_id);
    int DeleteFriend(int other_id);
    int DeleteBlack(int other_id);
    int GetFriendByIndex(int index);
    int GetBlackByIndex(int index);
};

#endif