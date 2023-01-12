#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "Socket.h"
#include "proto/message_define.pb.h"
#include "common/proto.h"

#define GOTO_NEXT if(ret==0) {phase++;}
#define GOTO_LOGIN if(ret==0){phase=5;}
#define GET_OUT if(ret==0){phase=999;}
#define CHECK_SERVER_ON if(ret<0) {\
									printf("Server Not Ready\n"); \
									return 0;}
#define WAIT_RSP_GO_NEXT ret=RecvRsp(); 
#define WAIT_RSP_GO_LOGIN ret=RecvRsp();GOTO_LOGIN
#define WAIT_RSP_GET_OUT ret=RecvRsp();GET_OUT
#define SEND common_req.SerializeToArray(sock.send_buffer, common_req.ByteSize());\
	int ret = sock.SocketSend(common_req.ByteSize());\
	send_count++;\
	return ret;
#define CHECK_SEND need_send=check_need_send(time0_now, time0_last);\
				   if(need_send==0) {break;} 

int send_count=0;
int recv_count=0;

ssp::CommonReq common_req;
ssp::CommonRsp common_rsp;

SspSocket sock;

int SendRegReq(const char* user_name, const char* password) {
	common_req.Clear();
	common_req.mutable_header()->set_ver(1);
	common_req.mutable_header()->set_cmd_type(REG_REQ);
	common_req.mutable_reg_req()->set_user_name(user_name);
	common_req.mutable_reg_req()->set_password(password);
	common_req.mutable_reg_req()->set_from(1);
	SEND
}

int SendLoginReq(const char* user_name, const char* password) {
	common_req.Clear();
	//common_req.mutable_header()->set_ver(1);
	common_req.mutable_header()->set_cmd_type(LOGIN_REQ);
	common_req.mutable_login_req()->set_user_name(user_name);
	common_req.mutable_login_req()->set_password(password);
	SEND
}

int SendAddFriendReq(int user_id, int other_id) {
	common_req.Clear();
	common_req.mutable_header()->set_cmd_type(ADD_FRIEND_REQ);
	common_req.mutable_add_friend_req()->set_user_id(user_id);
	common_req.mutable_add_friend_req()->set_other_id(other_id);
	SEND
}

int SendDelFriendReq(int user_id, int other_id) {
	common_req.Clear();
	common_req.mutable_header()->set_cmd_type(DEL_FRIEND_REQ);
	common_req.mutable_del_friend_req()->set_user_id(user_id);
	common_req.mutable_del_friend_req()->set_other_id(other_id);
	SEND
}

int SendPublishMessageReq(int user_id, const char* content) {
	common_req.Clear();
	common_req.mutable_header()->set_cmd_type(PUBLISH_MESSAGE_REQ);
	common_req.mutable_publish_message_req()->set_user_id(user_id);
	common_req.mutable_publish_message_req()->set_content(content);
	SEND
} 

int SendGetPhotoReq(int user_id) {
	common_req.Clear();
	common_req.mutable_header()->set_cmd_type(GET_PHOTO_REQ);
	common_req.mutable_get_photo_req()->set_user_id(user_id);
	SEND
}

int SendGetMessageReq(int user_id) {
	common_req.Clear();
	common_req.mutable_header()->set_cmd_type(GET_MESSAGE_LIST_REQ);
	common_req.mutable_get_message_list_req()->set_user_id(user_id);
	SEND
}

int SendLogout(int user_id) {
    common_req.Clear();
	common_req.mutable_header()->set_cmd_type(LOGOUT_REQ);
	common_req.mutable_logout_req()->set_user_id(user_id);
    SEND
}

int SendShutDown() {
	common_req.Clear();
	common_req.mutable_header()->set_cmd_type(SERVER_SHUTDOWN);
	SEND
}

int saved_user_id1 = 0;
int saved_user_id2 = 0;

int RecvRsp() {
	int ret = sock.SocketCheckRecv();
	if (ret > 0) {
		common_rsp.ParseFromArray(sock.recv_buffer, 10240);
		int cmd_type = common_rsp.header().cmd_type();
		//recv_count++;
		//if(recv_count>0)return 0;
		switch(cmd_type) {
			case REG_RSP:
				printf("Receive Reg Rsp\n");
				printf("ret     : %d\n", common_rsp.reg_rsp().ret());
				printf("user_id : %d\n", common_rsp.reg_rsp().user_id());
				break;
			case LOGIN_RSP:
				printf("Receive Login Rsp\n");
				printf("ret     : %d\n", common_rsp.login_rsp().ret());
				printf("user_id : %d\n", common_rsp.login_rsp().user_id());
				if(saved_user_id1==0){
					saved_user_id1=common_rsp.login_rsp().user_id();
				}else{
					if(saved_user_id2==0){
						saved_user_id2=common_rsp.login_rsp().user_id();
					}
				}
				break;
			case ADD_FRIEND_RSP:
				printf("Receive AddFriend Rsp\n");
				printf("ret    : %d\n",common_rsp.add_friend_rsp().ret());
				break;
			case DEL_FRIEND_RSP:
				printf("Receive DelFriend Rsp\n");
				printf("ret    : %d\n",common_rsp.del_friend_rsp().ret());
				break;
			case PUBLISH_MESSAGE_RSP:
				printf("Receive PublishMessage Rsp\n");
				printf("ret    : %d\n",common_rsp.publish_message_rsp().ret());
				break;
			case GET_PHOTO_RSP:
				printf("Receive GetPhoto Rsp\n");
				printf("ret    : %d\n",common_rsp.get_photo_rsp().ret());
				printf("update : %d\n",common_rsp.get_photo_rsp().last_publisher_id());
				break;
			case GET_MESSAGE_LIST_RSP:
				{
					printf("Receive GetMessageList Rsp\n");
					printf("ret    : %d\n",common_rsp.get_message_list_rsp().ret());
					int message_count=common_rsp.get_message_list_rsp().message_list_size();
					printf("count  : %d\n",common_rsp.get_message_list_rsp().message_list_size());
					for(int i=0;i<message_count;i++){
						printf("%6d : %s\n",common_rsp.get_message_list_rsp().message_list(i).publisher_id(),
											common_rsp.get_message_list_rsp().message_list(i).content().c_str());
					}
				}	
				break;
            case LOGOUT_RSP:
                printf("Receive Logout Rsp\n");
				printf("ret    : %d\n",common_rsp.logout_rsp().ret());
				break;
			default:
				break;
		}

	} else {
		return -1;
	}
	return 0;
}

/* 多个用户登录、使用软件测试
 */

int main() {
    int ret;
	ret = sock.Init();
	ret = sock.ClientSocketInit();
	CHECK_SERVER_ON

    int client_on = 1;
    int phase;

    while (client_on) {
        int need_send = 0;
        printf("please input function number: ");
        scanf("%d", &phase);
		switch(phase) {
			case 1:
				ret = SendRegReq("hank14567", "123456");
				GOTO_NEXT
                WAIT_RSP_GO_NEXT
				break;
			case 2:
				ret = SendLoginReq("hank14567", "123456");
				GOTO_NEXT
                WAIT_RSP_GO_NEXT
				break;
			case 3:
                printf("please input add friend_id: ");
                scanf("%d", &saved_user_id2);
				ret = SendAddFriendReq(saved_user_id1, saved_user_id2);
				GOTO_NEXT;
                WAIT_RSP_GO_NEXT
				break;
			case 4:
				ret = SendPublishMessageReq(saved_user_id1, "circle");
				GOTO_NEXT;
                WAIT_RSP_GO_NEXT
				break;
			case 5:
				ret = SendGetMessageReq(saved_user_id1);
				GOTO_NEXT;
                WAIT_RSP_GO_NEXT
				break;
			case 6:
                printf("please input delete friend_id: ");
                scanf("%d", &saved_user_id2);
				ret = SendDelFriendReq(saved_user_id1, saved_user_id2);
				GOTO_NEXT;
                WAIT_RSP_GO_NEXT
				break;
            case 7:
                ret = SendLogout(saved_user_id1);
                GOTO_NEXT;
                WAIT_RSP_GO_NEXT
                sock.ClientClose();
				break;
			default:
                client_on = 0;
				break;
		}
		
	}

    sock.ClientClose();

    return 0;
}