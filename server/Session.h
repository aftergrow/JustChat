/*************************************************************************
	> File Name: Session.h
	> Author: kwb
	> Mail: 
	> Created Time: Mon 02 May 2022 12:23:22 AM CST
 ************************************************************************/

#ifndef _SESSION_H
#define _SESSION_H

class Session {
public:
    char user_name[256];
    char password[256];
    int ret;
    int user_id;
    int other_id;
    int from;
    int cur_user_id;
    int collect_count;
};

#endif
