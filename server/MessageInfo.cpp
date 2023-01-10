/*************************************************************************
	> File Name: MessageInfo.cpp
	> Author: kwb
	> Mail: 
	> Created Time: Wed 24 Aug 2022 06:51:39 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "MessageInfo.h"

int MessageInfo::FromPb(ssp::MessageInfoBase &pb_mess) {
	set_user_id(pb_mess.user_id());
	set_message_id(pb_mess.publisher_id());
	set_publish_time(pb_mess.publisher_time());
	set_content(pb_mess.content().c_str());
	return 0;
}

int MessageInfo::ToPb(ssp::MessageInfoBase &pb_mess) {
	pb_mess.set_user_id(user_id());
	pb_mess.set_publisher_id(message_id());
	pb_mess.set_publisher_time(publish_time());
	pb_mess.set_content(content());
	return 0;
}

