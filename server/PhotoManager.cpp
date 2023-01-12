/*************************************************************************
	> File Name: PhotoManager.cpp
	> Author: kwb
	> Mail: 
	> Created Time: Sun 27 Mar 2022 04:37:44 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include "PhotoManager.h"
#include "DbManager.h"
#include "common/ret_value.h"

int PhotoManager::Start(DbManager *db_svr){
	db_svr_ = db_svr;
	set_photo_count(0);

    int ret = db_svr_->GetDataBegin("select * from tb_photo;");
    int photo_i = 0;
    if (ret == SUCCESS) {
        //将数据库的数据读到 &photos_[photo_i] 里
        ret = db_svr_->GetDataOneByOne(&photos_[photo_i]);
        if (ret == SUCCESS) {
            printf("user_id = %d, last_publisher_id = %d, last_publisher_time = %ld, last_user_get_time = %ld\n",
                   photos_[photo_i].user_id(),photos_[photo_i].last_publisher_id(),
				   photos_[photo_i].last_publisher_time(), photos_[photo_i].last_user_get_time());
            photo_i++;
        }
        while (ret != DB_NO_MORE_DATA) {
            ret = db_svr_->GetDataOneByOne(&photos_[photo_i]);
            if (ret == SUCCESS) {
				printf("user_id = %d, last_publisher_id = %d, last_publisher_time = %ld, last_user_get_time = %ld\n",
					photos_[photo_i].user_id(),photos_[photo_i].last_publisher_id(),
					photos_[photo_i].last_publisher_time(), photos_[photo_i].last_user_get_time());
				photo_i++;
			}
        }
        ret = db_svr_->GetDataEnd();
        set_photo_count(photo_i);
        printf("PhotoCount: %d\n", photo_count());
    } else {
        printf("PhotoManager Start Failure(Db Get Photo Failed: %d)\n", ret);
        return ret;
    }
    printf("PhotoManager Start\n");
    return SUCCESS;
}

void PhotoManager::Proc(){}
void PhotoManager::Shutdown(){}
void PhotoManager::Restart(){}

int PhotoManager::CreatePhoto(int user_id){
	for(int i=0;i<photo_count_;i++){
		if(photos_[i].user_id()==user_id){
			return PHOTO_EXIST;
		}
	}
	if(photo_count_==10239){
		return PHOTO_TOO_MUCH;
	}
	photos_[photo_count_].set_user_id(user_id);
	photos_[photo_count_].set_last_publisher_id(0);
	photos_[photo_count_].set_last_publisher_time(0);
	photos_[photo_count_].set_last_user_get_time(1);
	photo_count_++;
	return SUCCESS;
}

PhotoInfo* PhotoManager::GetPhoto(int user_id) {
	for (int i=0; i<photo_count_; i++) {
		if (photos_[i].user_id()==user_id) {
			return &photos_[i];
		}
	}
	return NULL;
}

//publish_or_get:true,publish messaage; false,get message
int PhotoManager::UpdatePhoto(int user_id,int publisher_id,time_t update_time, bool publish_or_get){
	PhotoInfo* photo=GetPhoto(user_id);
	if(photo==NULL){
		return PHOTO_NOT_EXIST;
	}
	photo->set_user_id(user_id);
	photo->set_last_publisher_id(publisher_id);
	if(publish_or_get) {
		photo->set_last_publisher_time(update_time);
	} else {
		photo->set_last_user_get_time(update_time);
	}
	
	return SUCCESS;
}

int PhotoManager::StorageDb(int user_id) {
	PhotoInfo* photo=GetPhoto(user_id);
	if(photo==NULL){
		return PHOTO_NOT_EXIST;
	}
	int ret = db_svr_->UpdateData(photo);
	if(ret != SUCCESS) {
		return ret;
	}
	return SUCCESS;
}