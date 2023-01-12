#ifndef _MESSAGE_INFO_H
#define _MESSAGE_INFO_H

#include <string.h>
#include "common/macro.h"
#include "proto/message_info_base.pb.h"

class MessageInfo {
    GETSETVAR(int, user_id)
    GETSETVAR(int, message_id)
    GETSETVAR(uint32_t, publish_time)
    GETSETSTR(1024, content) //消息内容，如文字，图片链接，表情链接等等

public:
    int FromPb(ssp::MessageInfoBase &pb_mess);
    int ToPb(ssp::MessageInfoBase &pb_mess);
};

#endif