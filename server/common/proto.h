/*************************************************************************
	> File Name: proto.h
	> Author: kwb
	> Mail: 
	> Created Time: Sun 03 Apr 2022 11:44:38 PM CST
 ************************************************************************/

#ifndef _PROTO_H
#define _PROTO_H

/* 对应操作的解析文件 */

#define REG_REQ 401
#define REG_RSP 402

#define LOGIN_REQ 101
#define LOGIN_RSP 102
#define LOGOUT_REQ 111
#define LOGOUT_RSP 112

#define ADD_FRIEND_REQ 201
#define ADD_FRIEND_RSP 202
#define DEL_FRIEND_REQ 211
#define DEL_FRIEND_RSP 212

#define GET_PHOTO_REQ 301 //拉取小红点
#define GET_PHOTO_RSP 302

#define GET_MESSAGE_LIST_REQ 501
#define GET_MESSAGE_LIST_RSP 502

#define PUBLISH_MESSAGE_REQ 601
#define PUBLISH_MESSAGE_RSP 602

#define SERVER_RESTART 701
#define SERVER_SHUTDOWN 702

#define TEST_TYPE_REQ 801
#define TEST_TYPE_RSP 802

//进程间通信以10开头
#define GET_USER_ID_REQ 1001
#define GET_USER_ID_RSP 1002
#define CREATE_USER_REQ 1003
#define CREATE_USER_RSP 1004
#define LOGIN_CHECK_REQ 1005
#define LOGIN_CHECK_RSP 1006
#define CHECK_EXIST_REQ 1007
#define CHECK_EXIST_RSP 1008
#define ADD_FRIEND_CHECK_USER_ID_EXIST_REQ 1009
#define ADD_FRIEND_CHECK_USER_ID_EXIST_RSP 1010
#define ADD_FRIEND_CHECK_OTHER_ID_EXIST_REQ 1011
#define ADD_FRIEND_CHECK_OTHER_ID_EXIST_RSP 1012
#define PUBLISH_MESSAGE_CHECK_ID_EXIST_REQ 1013
#define PUBLISH_MESSAGE_CHECK_ID_EXIST_RSP 1014
#define GET_PHOTO_CHECK_ID_EXIST_REQ 1015
#define GET_PHOTO_CHECK_ID_EXIST_RSP 1016
#define GET_MESSAGE_LIST_CHECK_ID_EXIST_REQ 1017
#define GET_MESSAGE_LIST_CHECK_ID_EXIST_RSP 1018
#define DEL_FRIEND_CHECK_USER_ID_EXIST_REQ 1019
#define DEL_FRIEND_CHECK_USER_ID_EXIST_RSP 1020
#define DEL_FRIEND_CHECK_OTHER_ID_EXIST_REQ 1021
#define DEL_FRIEND_CHECK_OTHER_ID_EXIST_RSP 1022
#define LOGOUT_CHECK_ID_EXIST_REQ 1023
#define LOGOUT_CHECK_ID_EXIST_RSP 1024


#endif