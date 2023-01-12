/*************************************************************************
	> File Name: common/ret_value.h
	> Author: kwb
	> Mail: 
	> Created Time: Tue 22 Mar 2022 11:12:57 PM CST
 ************************************************************************/

#ifndef RET_VALUE_H
#define RET_VALUE_H

#define SUCCESS 1

#define USER_NOT_EXIST 100
#define USER_EXIST 101
#define WRONG_PASSWORD 102
#define USER_TOO_MUCH 103

#define NOT_FRIEND 200
#define ALREADY_FRIEND 201
#define FRIEND_TOO_MUCH 202
#define FRIEND_INDEX_WRONG 203

#define NOT_BLACK 210
#define ALREADY_BLACK 211
#define BLACK_TOO_MUCH 212
#define BLACK_INDEX_WRONG 213

#define RELATION_TOO_MUCH 220
#define RELATION_NOT_EXIST 221
#define RELATION_EXIST 222

#define MESSAGE_NOT_EXIST 300
#define MESSAGE_TOO_MUCH 301

#define PHOTO_NOT_EXIST 400
#define PHOTO_TOO_MUCH 401
#define PHOTO_EXIST 402

#define FLAG_INSERT 500
#define FLAG_DELETE 501
#define FLAG_UPDATE 502

#define DB_CONN_INIT_FAIL 601
#define DB_CONN_CONNECT_FAIL 602
#define DB_QUREY_FAIL 603
#define DB_BUSY 604
#define DB_NO_MORE_DATA 605
#define DB_DATA_TYPE_ERRO 606

#define FILE_CAN_NOT_OPEN 701

#endif
