/*************************************************************************
	> File Name: RelationInfo.cpp
	> Author: kwb
	> Mail: 
	> Created Time: Tue 22 Mar 2022 11:02:49 PM CST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RelationInfo.h"
#include "common/ret_value.h"

int RelationInfo::FromPb(ssp::RelationInfoBase &pb_rela) {
    set_user_id(pb_rela.user_id());
    set_friend_count(pb_rela.friend_count());
    set_black_count(pb_rela.black_count());
    for(int i = 0; i < friend_count(); i++) {
        friend_list_[i] = pb_rela.friend_list(i);
    }
    for(int i = 0; i < black_count(); i++) {
        black_list_[i] = pb_rela.black_list(i);
    }
    return 0;
}

int RelationInfo::ToPb(ssp::RelationInfoBase &pb_rela) {
    pb_rela.set_user_id(user_id());
    pb_rela.set_friend_count(friend_count());
    pb_rela.set_black_count(black_count());
    for(int i = 0; i < friend_count(); i++) {
        pb_rela.add_friend_list(friend_list_[i]);
    }
    for(int i = 0; i < black_count(); i++) {
        pb_rela.add_black_list(black_list_[i]);
    }
    return 0;
}

int RelationInfo::CheckFriend(int other_id) {
    for (int i=0; i<friend_count_; i++) {
        if (friend_list_[i] == other_id) {
            return SUCCESS;
        }
    }
    return NOT_FRIEND;
}

int RelationInfo::CheckBlack(int other_id) {
    for (int i=0; i<black_count_; i++) {
        if (black_list_[i] == other_id) {
            return SUCCESS;
        }
    }
    return NOT_BLACK;
}
   
int RelationInfo::AddFriend(int other_id){
    if (CheckFriend(other_id) == SUCCESS) {
        return ALREADY_FRIEND;
    }
    if (friend_count_<10239) {
        friend_list_[friend_count_] = other_id;
        friend_count_++;
    } else {
        return FRIEND_TOO_MUCH;
    }
    return SUCCESS;
}

int RelationInfo::AddBlack(int other_id){
    if (CheckBlack(other_id) == SUCCESS) {
        return ALREADY_BLACK;
    }
    if (black_count_<10239) {
        black_list_[black_count_] = other_id;
        black_count_++;
    } else {
        return BLACK_TOO_MUCH;
    }
    return SUCCESS;
    
}

int RelationInfo::DeleteFriend(int other_id){
    if (CheckFriend(other_id) == SUCCESS) {
        for (int i=0; i<friend_count_; i++) {
            if (friend_list_[i] == other_id) {
                friend_list_[i] = -1;
                for (int j=i; j<friend_count_-1; j++) {
                    friend_list_[j] = friend_list_[j+1];
                }
                break;
            }
        }
        friend_count_--;
    } else {
        return NOT_FRIEND;
    }
    return SUCCESS;
}

int RelationInfo::DeleteBlack(int other_id){
    if (CheckBlack(other_id) == SUCCESS) {
        for (int i=0; i<black_count_; i++) {
            if (black_list_[i] == other_id) {
                black_list_[i] = -1;
                for (int j=i; j<black_count_-1; j++) {
                    black_list_[j] = black_list_[j+1];
                }
                break;
            }
        }
        black_count_--;
    } else {
        return NOT_BLACK;
    }
    return SUCCESS;
}

int RelationInfo::GetFriendByIndex(int index){
    if (index<0 || index>=friend_count_) {
        return FRIEND_INDEX_WRONG;
    }
    return friend_list_[index];
}

int RelationInfo::GetBlackByIndex(int index){
    if (index<0 || index>=black_count_) {
        return BLACK_INDEX_WRONG;
    }
    return black_list_[index];
}

