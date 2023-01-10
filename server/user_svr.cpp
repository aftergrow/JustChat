/*************************************************************************
	> File Name: user_svr.cpp
	> Author: kwb
	> Mail: 
	> Created Time: Wed 04 May 2022 12:18:14 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include "BusManager.h"
#include "common/ret_value.h"
#include "common/proto.h"
#include "proto/message_define.pb.h"
#include "UserManager.h"
#include "DbManager.h"

#define SEND_CHECK_USER_EXIST {\
	MAKE_RSP_HEAD(cmd_id);\
	int user_id = inner_req.check_user_exist().user_id();\
	int ret = user_svr.CheckExist(user_id);\
	inner_rsp.mutable_check_user_exist()->set_ret(ret); \
	BUS_SEND_RSP(user_svr_id,check_bus);\
}

BusManager bus;
UserManager user_svr;
DbManager db_svr;
int user_svr_id = 0;
ssp::ServerToUserReq inner_req;
ssp::UserToServerRsp inner_rsp;

void MAKE_RSP_HEAD(int cmd_id){
	inner_rsp.Clear();
	inner_rsp.mutable_header()->set_ver(1);
	inner_rsp.mutable_header()->set_cmd_type(cmd_id+1);
	memset(bus.send_buffer, 0, 10240);
}

void BUS_SEND_RSP(int from,int to){
	inner_rsp.SerializeToArray(bus.send_buffer,inner_rsp.ByteSize());
	printf("----[debug]bus send message:\n");
	std::string debug_message=inner_rsp.Utf8DebugString();
	printf("%s\n",debug_message.c_str());
	int ret=bus.Send(from,to,bus.send_buffer,inner_rsp.ByteSize());
	//bus.ChannelShow();
	printf("send_ret:%d\n",ret);
}

/* void BUS_SEND_RSP_C(int from,int to){
	inner_rsp.SerializeToArray(bus.send_buffer,10240);
	printf("----[debug]bus send message:\n");
	std::string debug_message=inner_rsp.Utf8DebugString();
	printf("%s\n",debug_message.c_str());
	int ret=bus.Send(from,to,bus.send_buffer,10240);
	bus.ChannelShow();
	printf("send_ret:%d\n",ret);
} */

/* void BUS_SEND_CREATE_RSP(int from,int to){
	inner_rsp.SerializeToArray(bus.send_buffer,10240);
		
	inner_rsp.Clear();
	inner_rsp.ParseFromArray(bus.send_buffer, 10240);
	printf("send_buff: %s", bus.send_buffer);
	
	int user_id = inner_rsp.create_user().user_id();
	inner_rsp.mutable_header()->set_ver(1);
	inner_rsp.mutable_header()->set_cmd_type(CREATE_USER_RSP);
	inner_rsp.mutable_create_user()->set_ret(SUCCESS);
	inner_rsp.mutable_create_user()->set_user_id(user_id);
	printf("after parse: %d\n", inner_rsp.create_user().user_id());
	memset(bus.send_buffer, 0, 10240);
	inner_rsp.SerializeToArray(bus.send_buffer,10240);
	printf("send_buff: %s", bus.send_buffer);

	printf("----[debug]bus send message:\n");
	std::string debug_message=inner_rsp.Utf8DebugString();
	printf("%s\n",debug_message.c_str());
	int ret=bus.Send(from,to,bus.send_buffer,10240);
	bus.ChannelShow();
	printf("send_ret:%d\n",ret);

	inner_rsp.ParseFromArray(bus.Recv(11,21),10240);
	printf("create_user_id from bus: %d\n", inner_rsp.create_user().user_id());
	bus.ChannelShow();

} */

int main(int argc, char* argv[]) {
	//printf("begin\n");
	//sleep(10);
	if (argc < 2) {
		printf("Usage: user_svr <svr_id>");
		return 0;
	}
	sscanf(argv[1], "%d", &user_svr_id);
	bus.Init();	
	/* printf("bus.Init()\n");
	sleep(10); */
	db_svr.Init();	
	/* printf("db_svr.Init()\n");
	sleep(10); */
	user_svr.Start(&db_svr, user_svr_id); 
	int server_on = 1;	
	int time_now;
	int check_bus;
	//int check_bus = -1;
	//bus.ChannelShow();
	while(server_on){								
		time_now=time(NULL);
		check_bus=bus.CheckRecv(user_svr_id);			
		if(check_bus!=-1){
			// ---- bus check recv; after recv clear bus
			inner_req.ParseFromArray(bus.Recv(check_bus,user_svr_id),bus.RecvSize(check_bus,user_svr_id));
			printf("----[debug]bus recv message:\n");
			std::string debug_message=inner_req.Utf8DebugString();
			printf("%s\n",debug_message.c_str());
			bus.Clear(check_bus,user_svr_id);

			int cmd_id=inner_req.header().cmd_type();
			switch(cmd_id) {
				case GET_USER_ID_REQ:
				{
					MAKE_RSP_HEAD(cmd_id);
					int user_id = user_svr.GetUserIdByUserName(inner_req.get_user_id().user_name().c_str());
					if(user_id==USER_NOT_EXIST){
						inner_rsp.mutable_get_user_id()->set_ret(USER_NOT_EXIST);
						inner_rsp.mutable_get_user_id()->set_user_id(user_svr.cur_user_id());						
					}else{
						inner_rsp.mutable_get_user_id()->set_ret(USER_EXIST);
						inner_rsp.mutable_get_user_id()->set_user_id(user_id);
					}
					BUS_SEND_RSP(user_svr_id, check_bus);
					//printf("deal GET_USER_ID_REQ\n\n");
				}
				break;
				case CREATE_USER_REQ:
				{
					MAKE_RSP_HEAD(cmd_id);
					int user_id=user_svr.CreateUser(inner_req.create_user().user_name().c_str(), 
								 				inner_req.create_user().password().c_str(), 
								 				inner_req.create_user().from(), time_now);

					if(user_id==USER_TOO_MUCH){
						inner_rsp.mutable_create_user()->set_ret(USER_TOO_MUCH);
						//inner_rsp.mutable_create_user()->set_user_id(user_id);
					}else{
						inner_rsp.mutable_create_user()->set_ret(SUCCESS);
						inner_rsp.mutable_create_user()->set_user_id(user_id);	
						//printf("create_user_id: %d\n", inner_rsp.create_user().user_id());					
					}
					BUS_SEND_RSP(user_svr_id, check_bus);
					//printf("deal CREATE_USER_REQ\n\n");
				}
				break;
				case LOGIN_CHECK_REQ:
				{
					MAKE_RSP_HEAD(cmd_id);
					// ---- add code here ----
					int user_id = user_svr.LoginCheck(inner_req.login_check().user_name().c_str(), inner_req.login_check().password().c_str());
					if (user_id == WRONG_PASSWORD || user_id == USER_NOT_EXIST) {
						inner_rsp.mutable_login_check()->set_ret(user_id);
					} else {
						inner_rsp.mutable_login_check()->set_ret(SUCCESS);
						inner_rsp.mutable_login_check()->set_user_id(user_id);
					}										
					BUS_SEND_RSP(user_svr_id,check_bus);
				}
				break;
				case ADD_FRIEND_CHECK_USER_ID_EXIST_REQ:
				{
					SEND_CHECK_USER_EXIST
				}
				break;
				case ADD_FRIEND_CHECK_OTHER_ID_EXIST_REQ:
				{
					SEND_CHECK_USER_EXIST
				}
				break;
				case PUBLISH_MESSAGE_CHECK_ID_EXIST_REQ:
				{
					SEND_CHECK_USER_EXIST
				}
				break;
				case GET_PHOTO_CHECK_ID_EXIST_REQ:
				{
					SEND_CHECK_USER_EXIST
				}
				break;
				case GET_MESSAGE_LIST_CHECK_ID_EXIST_REQ:
				{
					SEND_CHECK_USER_EXIST
				}
				break;
				case DEL_FRIEND_CHECK_USER_ID_EXIST_REQ:
				{
					SEND_CHECK_USER_EXIST
				}
				break;
				case DEL_FRIEND_CHECK_OTHER_ID_EXIST_REQ:
				{
					SEND_CHECK_USER_EXIST
				}
				break;
				case LOGOUT_CHECK_ID_EXIST_REQ:
				{
					SEND_CHECK_USER_EXIST
				}
				break;
				default:				
				break;	
			}
		} else {
			usleep(500);
		} 		
	}
	bus.ShmDetach();
	return 0;
}

