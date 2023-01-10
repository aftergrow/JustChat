/*************************************************************************
	> File Name: PhotoManager.h
	> Author: kwb
	> Mail: 
	> Created Time: Sun 27 Mar 2022 10:56:53 PM CST
 ************************************************************************/

#ifndef _PHOTOMANAGER_H
#define _PHOTOMANAGER_H

#include "PhotoInfo.h"
#include "common/macro.h"

class DbManager;
class PhotoManager {
private:
	PhotoInfo photos_[10240];
	GETSETVAR(int, photo_count)

private:
	DbManager* db_svr_;

public:
	int Start(DbManager *db_svr);
	void Proc();
	void Restart();
	void Shutdown();

public:
	int CreatePhoto(int user_id);
	PhotoInfo* GetPhoto(int user_id);
	int UpdatePhoto(int user_id,int publisher_id,time_t update_time, bool publish_or_get);
	int StorageDb(int user_id);
};

#endif
