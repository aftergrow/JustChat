#include "PhotoInfo.h"

int PhotoInfo::FromPb(ssp::PhotoInfoBase &photo) {
    set_user_id(photo.user_id());
    set_last_publisher_id(photo.last_publisher());
    set_last_publisher_time(photo.last_publisher_time());
    set_last_user_get_time(photo.last_user_get_time());
    return 0;
}

int PhotoInfo::ToPb(ssp::PhotoInfoBase &photo) {
    photo.set_user_id(user_id());
    photo.set_last_publisher(last_publisher_id());
    photo.set_last_publisher_time(last_publisher_time());
    photo.set_last_user_get_time(last_user_get_time());
    return 0;
}