#ifndef _PHOTO_INFO_H
#define _PHOTO_INFO_H

#include "common/macro.h"
#include "proto/photo_info_base.pb.h"

class PhotoInfo {
private:
    GETSETVAR(int, user_id) //作为主键
    GETSETVAR(int, last_publisher_id) //最新发布新消息的用户ID
    GETSETVAR(time_t, last_publisher_time)
    GETSETVAR(time_t, last_user_get_time)

public:
    int FromPb(ssp::PhotoInfoBase &photo);
    int ToPb(ssp::PhotoInfoBase &photo);
};

#endif