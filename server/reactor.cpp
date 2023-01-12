/*************************************************************************
	> File Name: main.cpp
	> Author: kwb
	> Mail: 
	> Created Time: Sun 27 Mar 2022 05:05:52 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <vector>
#include <sys/epoll.h>
#include <pthread.h>
#include "UserManager.h"
#include "RelationManager.h"
#include "MessageManager.h"
#include "PhotoManager.h"
#include "Socket.h"
#include "common/proto.h"
#include "common/ret_value.h"
#include "proto/message_define.pb.h"
#include "BusManager.h"
#include "DbManager.h"
#include "reactor.h"
#include "Session.h"
#include "common.h"

//#define ADD_FRIEND_F
//#define DEL_FRIEND_F
#define FRIEND_F
#define GET_MESSAGE_F
#define PHOTO_F

extern RelationManager rela_svr;
extern MessageManager mess_svr;
extern PhotoManager photo_svr;
extern DbManager db_svr;
extern BusManager bus;

//最好是通过配置文件读出来
int server_id = 21;
int user_svr_count = 2; //总共2个 user_svr
int user_svr_id[2] = {11, 12};

/* void heart_beat(int signum) {
    struct wechat_msg msg;
    msg.type = WECHAT_HEART;
    DBG(GREEN"SIGALRM\n"NONE);
    //给每个 在线的 用户发送心跳包
    for (int i = 0; i < MAXUSERS; i++) {
        if (users[i].isOnline) {
            send(users[i].fd, (void *)&msg, sizeof(msg), 0);
            users[i].isOnline--; //在下面的 sub_reactor() 中，isOnline 置为5
            if (users[i].isOnline == 0) {
                int tmp_fd = users[i].sex ? subefd1 : subefd2; 
                epoll_ctl(tmp_fd, EPOLL_CTL_DEL, users[i].fd, NULL);
                close(users[i].fd);
                DBG(RED"<Heart Beat Err>"NONE" %s is removed because of heart beat error.\n", users[i].name);
            }
        }
    }
} */

int add_to_reactor(int epollfd, int fd){
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN | EPOLLET; //边缘触发
    make_nonblock(fd); //非阻塞

    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev) < 0) {
        return -1;
    }
    return 0;
}

void work(SspSocket& sock, int subfd) {
    Session reg_session; //用来标识发包和回包的是谁
    Session login_session;
    Session add_friend_session;
    Session del_friend_session;
    Session pulish_mess_session;
    Session get_mess_session;
    Session get_photo_session;
    Session logout_session;
    Session session;

    //客户端和服务端的请求与应答
    ssp::CommonReq common_req;
    ssp::CommonRsp common_rsp;
    //内部请求和内部应答
    ssp::ServerToUserReq inner_req;
    ssp::UserToServerRsp inner_rsp;

    int inner_req_num = 0;
    int common_req_num = 1;

    int server_on=1;
    while(common_req_num || inner_req_num) { 
        int check_bus;
        if (inner_req_num) {
            #ifdef ADD_FRIEND_F
            printf("before while\n");
            #endif

            check_bus = bus.CheckRecv(server_id);
            while (check_bus == -1) {
                check_bus=bus.CheckRecv(server_id);
                if (check_bus != -1) break;   
            }        

            #ifdef ADD_FRIEND_F
            printf("after while\n");
            #endif
        } 
		int check_sock=-1;
		int cmd_id=-1;
        
        //user_svr.Proc(); //watch memory info，信息监控
        rela_svr.Proc();
		mess_svr.Proc();
		photo_svr.Proc();

        //这个时间每次循环只写一次，当下面的内容需要用的时候就取这个时间就行了
        time_t time_now = time(NULL); //time(NULL): 获取当前时间

        int ret = 0;
        //register request
        //get value from recv_buffer  获取客户端的值
        //int cmd_id = sock.GetCmdId();

        if(common_req_num == 1){         
            printf("\n\n\ncheck_sock ok\n");
            common_req.ParseFromArray(sock.recv_buffer,10240);
            memset(sock.recv_buffer,0,common_req.ByteSize());
            cmd_id=common_req.header().cmd_type();

            common_rsp.Clear();//todo 比较放在这里和放在分支下的效率
            common_rsp.mutable_header()->set_ver(1);
            common_rsp.mutable_header()->set_cmd_type(cmd_id+1);               
            common_req_num = 0;
		}else{
			printf("check_bus ok\n");
            //inner_rsp.ParseFromArray(bus.Recv(check_bus,server_id),10240);
			inner_rsp.ParseFromArray(bus.Recv(check_bus,server_id),bus.RecvSize(check_bus,server_id));
            //printf("create_user_id: %d\n", inner_rsp.create_user().user_id());   
            //printf("data addr: %p\n", bus.MutableChannelBlockData(bus.GetChannelIndex(check_bus, server_id)));
            //bus.ChannelShow();      
			bus.Clear(check_bus,server_id);
			cmd_id=inner_rsp.header().cmd_type();
                            
            inner_req_num--;
		}       

        if(cmd_id<=0){
			usleep(5000);
			continue;
		}

        printf("----[debug]cmd_id:%d\n",cmd_id);
        switch(cmd_id) {
            case REG_REQ:
            {
                
                //解析方法，用什么样的方法解析。从哪开始解析；解码的长度。一条命令就可以把 user_name、password 等都拿到了
                //RegReq.ParseFromArray(sock.recv_buffer+3, 10240); //直接引用 sock.recv_buffer+3
                //memset(sock.recv_buffer, 0, RegReq.ByteSize()+3); //解析后需要清0避免脏数据
                //char* user_name = sock.GetRegUserName();
                //char* password = sock.GetRegPassword();

                //在case里定义变量，需要指定作用域
                
                common_rsp.mutable_reg_rsp()->Clear(); //清空避免脏数据
                /* 
                int user_id = user_svr.GetUserIdByUserName(common_req.reg_req().user_name().c_str()); //GetUserIdByUserName()的参数是 char*，所以这里需要转换成c风格的参数               
                int ret_value = 0;
                if (user_id == USER_NOT_EXIST) {
                    user_id = user_svr.CreateUser(common_req.reg_req().user_name().c_str(), common_req.reg_req().password().c_str(), common_req.reg_req().from(), time_now);                    
                } else {
                    ret_value = USER_EXIST;
                }
                common_rsp.mutable_reg_rsp()->set_ret(ret_value);
                common_rsp.mutable_reg_rsp()->set_user_id(user_id);
                common_rsp.SerializeToArray(sock.send_buffer, 10240); 
                sock.SocketSend(common_rsp.ByteSize()); //ByteSize()：序列化后 array 的长度 */

                //Send request to UserX
                memset(reg_session.user_name, 0, 256);
                memset(reg_session.user_name, 0, 256);
                strcpy(reg_session.user_name, common_req.reg_req().user_name().c_str());
                strcpy(reg_session.password, common_req.reg_req().password().c_str());
                inner_req.mutable_get_user_id()->Clear();
                inner_req.mutable_header()->set_ver(1);
                inner_req.mutable_header()->set_cmd_type(GET_USER_ID_REQ);
                inner_req.mutable_get_user_id()->set_user_name(common_req.reg_req().user_name());                
                char data[10240] = {0};
                inner_req.SerializeToArray(data, inner_req.ByteSize());
                for (int i = 0; i < user_svr_count; i++) {
                    bus.Send(server_id, user_svr_id[i], data, inner_req.ByteSize());
                    inner_req_num++;
                }
                reg_session.collect_count = 0;
                reg_session.cur_user_id = 0x3fffffff;
                reg_session.from = common_req.reg_req().from(); //这个目前是随便编的数字       

                //printf("deal REG_REQ\n\n");                         
            }
            break;
            case GET_USER_ID_RSP:
            {
                if (reg_session.collect_count == user_svr_count) {
                    //drop 当有了预期结果，后面就不用等了;即便来了，也不处理
                    break;
                }
                //collect_count: 目前遍历了几个 user_svr
                reg_session.collect_count++;
                if (inner_rsp.get_user_id().ret() == USER_EXIST) {
                    common_rsp.mutable_reg_rsp()->set_ret(USER_EXIST);
                    common_rsp.mutable_reg_rsp()->set_user_id(inner_rsp.get_user_id().user_id());
                    common_rsp.SerializeToArray(sock.send_buffer, 10240);
                    sock.SocketSend(common_rsp.ByteSize());
                    reg_session.collect_count = user_svr_count;
                    continue;
                } else {
                    if (reg_session.cur_user_id > inner_rsp.get_user_id().user_id()) {
                        reg_session.cur_user_id = inner_rsp.get_user_id().user_id();
                    }
                }
                if (reg_session.collect_count == user_svr_count) {
                    //user_svr.CreateUser
                    int user_idx = reg_session.cur_user_id % 2;
                    int cur_user_svr_id;
                    if (user_idx == 1) {
                        //user_svr_id[0] 存奇数ID
                        cur_user_svr_id = user_svr_id[0];
                    } else {
                        //user_svr_id[1] 存偶数ID
                        cur_user_svr_id = user_svr_id[1];
                    }
                    //send user_svr UserCreate
                    inner_req.mutable_create_user()->Clear();
                    inner_req.mutable_header()->set_cmd_type(CREATE_USER_REQ);
                    inner_req.mutable_create_user()->set_user_name(reg_session.user_name);
                    inner_req.mutable_create_user()->set_password(reg_session.password);
                    inner_req.mutable_create_user()->set_from(reg_session.from);
                    char data[10240] = {0};
                    inner_req.SerializeToArray(data, inner_req.ByteSize());
                    bus.Send(server_id, cur_user_svr_id, data, inner_req.ByteSize());
                    inner_req_num++;
                }
                //printf("deal GET_USER_ID_RSP\n\n");
            }
            break;
            case CREATE_USER_RSP:
            {
                /* common_rsp.Clear();
                common_rsp.mutable_header()->set_ver(1);
				common_rsp.mutable_header()->set_cmd_type(REG_RSP); */
                common_rsp.mutable_reg_rsp()->set_ret(inner_rsp.create_user().ret());
                common_rsp.mutable_reg_rsp()->set_user_id(inner_rsp.create_user().user_id());
                common_rsp.SerializeToArray(sock.send_buffer, 10240);
                sock.SocketSend(common_rsp.ByteSize());
                //printf("deal CREATE_USER_RSP\n\n");
            }
            break;
            case LOGIN_REQ:
            {
                common_rsp.mutable_login_rsp()->Clear();
                //strcpy(login_session.user_name, common_req.login_req().user_name().c_str());
                //strcpy(login_session.password, common_req.login_req().password().c_str());
                inner_req.mutable_login_check()->Clear();
                inner_req.mutable_header()->set_ver(1);
                inner_req.mutable_header()->set_cmd_type(LOGIN_CHECK_REQ);
                inner_req.mutable_login_check()->set_user_name(common_req.login_req().user_name()); 
                inner_req.mutable_login_check()->set_password(common_req.login_req().password());               
                char data[10240] = {0};
                inner_req.SerializeToArray(data, inner_req.ByteSize());
                for (int i = 0; i < user_svr_count; i++) {
                    bus.Send(server_id, user_svr_id[i], data, inner_req.ByteSize());
                    inner_req_num++;
                }
                login_session.collect_count = 0;
                                            
            }
            break;
            case LOGIN_CHECK_RSP:
            {
                //login_session.collect_count:判断已经收到几个 user_svr 的message
                if (login_session.collect_count == user_svr_count) {                
                    break;
                }
                login_session.collect_count++;               
                ret = inner_rsp.login_check().ret();                
                if (ret == SUCCESS) {
                    int ret1, ret2;
                    int user_id = inner_rsp.login_check().user_id();
                    common_rsp.mutable_login_rsp()->set_user_id(user_id);
                    ret1 = rela_svr.UserRelationInit(user_id);
                    ret2 = photo_svr.CreatePhoto(user_id);
                    printf("logincheck=%d rela_create=%d photo_create=%d\n",ret,ret1,ret2);
                    common_rsp.mutable_login_rsp()->set_ret(ret);
                    common_rsp.SerializeToArray(sock.send_buffer, 10240);
                    sock.SocketSend(common_rsp.ByteSize());
                    login_session.collect_count = user_svr_count;
                    continue;
                } else if (ret == WRONG_PASSWORD) {
                    common_rsp.mutable_login_rsp()->set_ret(ret);
                    common_rsp.SerializeToArray(sock.send_buffer, 10240);
                    sock.SocketSend(common_rsp.ByteSize());
                    login_session.collect_count = user_svr_count;
                    continue;
                } else {

                }
                if (login_session.collect_count == user_svr_count) {
                    common_rsp.mutable_login_rsp()->set_ret(ret);
                    common_rsp.SerializeToArray(sock.send_buffer, 10240);
                    sock.SocketSend(common_rsp.ByteSize());
                }                
            }
            break;
            case ADD_FRIEND_REQ:
            {
                add_friend_session.user_id = common_req.add_friend_req().user_id();
                add_friend_session.other_id = common_req.add_friend_req().other_id();

                common_rsp.mutable_add_friend_rsp()->Clear();
                inner_req.mutable_check_user_exist()->Clear();
                inner_req.mutable_header()->set_ver(1);
                inner_req.mutable_header()->set_cmd_type(ADD_FRIEND_CHECK_USER_ID_EXIST_REQ);
                inner_req.mutable_check_user_exist()->set_user_id(add_friend_session.user_id);
                char data[10240] = {0};
                inner_req.SerializeToArray(data, inner_req.ByteSize());
                for (int i = 0; i < user_svr_count; i++) {
                    bus.Send(server_id, user_svr_id[i], data, inner_req.ByteSize());
                    inner_req_num++;
                }
                add_friend_session.collect_count = 0;
                add_friend_session.ret = USER_NOT_EXIST;     
                                          
            }
            break;
            case ADD_FRIEND_CHECK_USER_ID_EXIST_RSP:
            {
                if (add_friend_session.collect_count == user_svr_count) {                
                    break;
                }
                add_friend_session.collect_count++;               
                ret = inner_rsp.check_user_exist().ret();
                if(add_friend_session.ret != USER_EXIST && ret == USER_EXIST) {
                    add_friend_session.ret = USER_EXIST;
                }                
                if (add_friend_session.ret == USER_EXIST && add_friend_session.collect_count == user_svr_count) {
                    inner_req.mutable_check_user_exist()->Clear();
                    inner_req.mutable_header()->set_ver(1);
                    inner_req.mutable_header()->set_cmd_type(ADD_FRIEND_CHECK_OTHER_ID_EXIST_REQ);                                        
                    inner_req.mutable_check_user_exist()->set_user_id(add_friend_session.other_id);
                    char data[10240] = {0};                                                            
                    inner_req.SerializeToArray(data, 10240);
                    for (int i = 0; i < user_svr_count; i++) {
                        bus.Send(server_id, user_svr_id[i], data, inner_req.ByteSize());
                        inner_req_num++;
                    }                    
                    continue;
                } else {
                    
                } 
                if (add_friend_session.collect_count == user_svr_count) {
                    #ifdef ADD_FRIEND_F
                        printf("ADD_FRIEND_CHECK_USER_ID_EXIST_RSP: send to client\n");
                    #endif

                    common_rsp.mutable_add_friend_rsp()->set_ret(ret);
                    common_rsp.SerializeToArray(sock.send_buffer, 10240);
                    sock.SocketSend(common_rsp.ByteSize());
                }                
            }
            break;
            case ADD_FRIEND_CHECK_OTHER_ID_EXIST_RSP:
            {
                #ifdef ADD_FRIEND_F
                    if(add_friend_session.collect_count < 2) {
                        printf("add_friend_session.collect_count < 2");
                        sleep(500);
                    }
                #endif

                if (add_friend_session.collect_count >= 2*user_svr_count) {                
                    break;
                }

                add_friend_session.collect_count++;              
                ret = inner_rsp.check_user_exist().ret();

                #ifdef ADD_FRIEND_F
                printf("inner_rsp.check_user_exist().ret(): %d\n", ret);
                #endif

                if (ret == USER_EXIST) {
                    ret = rela_svr.AddFriend(add_friend_session.user_id, add_friend_session.other_id);
                    common_rsp.mutable_add_friend_rsp()->set_ret(ret);
                    common_rsp.SerializeToArray(sock.send_buffer, 10240);
                    sock.SocketSend(common_rsp.ByteSize());   
                    add_friend_session.collect_count++;  

                    #ifdef ADD_FRIEND_F
                    printf("Server AddFriend Ret: %d\n", ret);
                    #endif

                    continue;
                } else {
                    
                } 
                if (add_friend_session.collect_count == 2*user_svr_count) {

                    #ifdef ADD_FRIEND_F
                    printf("add_friend_session.collect_count: %d\n", add_friend_session.collect_count);
                    #endif

                    common_rsp.mutable_add_friend_rsp()->set_ret(ret);
                    common_rsp.SerializeToArray(sock.send_buffer, 10240);
                    sock.SocketSend(common_rsp.ByteSize());
                }                
            }
            break;
            case PUBLISH_MESSAGE_REQ:
            {
                common_rsp.mutable_get_photo_rsp()->Clear();
                inner_req.mutable_check_user_exist()->Clear();
                pulish_mess_session.user_id = common_req.publish_message_req().user_id();
                inner_req.mutable_header()->set_ver(1);
                inner_req.mutable_header()->set_cmd_type(PUBLISH_MESSAGE_CHECK_ID_EXIST_REQ);
                inner_req.mutable_check_user_exist()->set_user_id(pulish_mess_session.user_id);
                char data[10240] = {0};
                inner_req.SerializeToArray(data, inner_req.ByteSize());
                for (int i = 0; i < user_svr_count; i++) {
                    bus.Send(server_id, user_svr_id[i], data, inner_req.ByteSize());
                    inner_req_num++;
                }
                pulish_mess_session.collect_count = 0;
                
            }
            break;
            case PUBLISH_MESSAGE_CHECK_ID_EXIST_RSP:
            {
                if (pulish_mess_session.collect_count == user_svr_count) {                
                    break;
                }
                pulish_mess_session.collect_count++;               
                ret = inner_rsp.check_user_exist().ret();                
                if (ret == USER_EXIST) {
                    int mess_id_ret = 0;
                    MessageInfo message;
                    message.set_user_id(pulish_mess_session.user_id);
                    message.set_content(common_req.publish_message_req().content().c_str());
                    uint32_t time_n = time_now;
                    message.set_publish_time(time_n);
                    mess_id_ret = mess_svr.PublishMessage(message);                   
                    ret = mess_id_ret;

                    if (mess_id_ret != MESSAGE_TOO_MUCH) {
                        /* 更新 user_id 自己的消息和快照 */
                        mess_svr.PushUserMessageId(pulish_mess_session.user_id, mess_id_ret);
                        //更新快照
                        photo_svr.UpdatePhoto(pulish_mess_session.user_id, pulish_mess_session.user_id, time_now, true);

                        RelationInfo* rela_info = rela_svr.GetRelation(pulish_mess_session.user_id);
                        if (rela_info) {
                            for (int i = 0; i < rela_info->friend_count(); i++) {
                                int friend_id = rela_info->GetFriendByIndex(i);
                                photo_svr.UpdatePhoto(friend_id, pulish_mess_session.user_id, time_now, true);
                                mess_svr.PushUserMessageId(friend_id, mess_id_ret);
                            }
                        }
                        ret = SUCCESS;
                    }
                    common_rsp.mutable_publish_message_rsp()->set_ret(ret);
                    common_rsp.SerializeToArray(sock.send_buffer, 10240);
                    sock.SocketSend(common_rsp.ByteSize());  
                    pulish_mess_session.collect_count = user_svr_count;
                    continue;
                } else {
                    
                } 
                if (pulish_mess_session.collect_count == user_svr_count) {
                    common_rsp.mutable_publish_message_rsp()->set_ret(ret);
                    common_rsp.SerializeToArray(sock.send_buffer, 10240);
                    sock.SocketSend(common_rsp.ByteSize());
                }
            }
            break;
            case GET_PHOTO_REQ:
            {
                common_rsp.mutable_get_photo_rsp()->Clear();
                get_photo_session.user_id = common_req.get_photo_req().user_id();
                inner_req.mutable_check_user_exist()->Clear();                
                inner_req.mutable_header()->set_ver(1);
                inner_req.mutable_header()->set_cmd_type(GET_PHOTO_CHECK_ID_EXIST_REQ);
                inner_req.mutable_check_user_exist()->set_user_id(get_photo_session.user_id);
                char data[10240] = {0};
                inner_req.SerializeToArray(data, inner_req.ByteSize());
                for (int i = 0; i < user_svr_count; i++) {
                    bus.Send(server_id, user_svr_id[i], data, inner_req.ByteSize());
                    inner_req_num++;
                }
                get_photo_session.collect_count = 0;  
                              
            }
            break;
            case GET_PHOTO_CHECK_ID_EXIST_RSP:
            {
                if (get_photo_session.collect_count == user_svr_count) {                
                    break;
                }
                get_photo_session.collect_count++;               
                ret = inner_rsp.check_user_exist().ret();                
                if (ret == USER_EXIST) {
                    PhotoInfo* photo = photo_svr.GetPhoto(get_photo_session.user_id);
                    if(photo != nullptr){						
                        int publisher_id = photo->last_publisher_id();
                        uint32_t last_publisher_time = photo->last_publisher_time();
                        uint32_t last_user_get_time = photo->last_user_get_time();
						//common_rsp.mutable_get_photo_rsp()->set_last_publisher_id(publisher_id);
                        //common_rsp.mutable_get_photo_rsp()->set_last_publisher_time(last_publisher_time);
                        //common_rsp.mutable_get_photo_rsp()->set_last_user_get_time(last_user_get_time);

                        #ifdef PHOTO_F
                        common_rsp.mutable_get_photo_rsp()->set_last_publisher_id(10002);
                        common_rsp.mutable_get_photo_rsp()->set_last_publisher_time(5);
                        common_rsp.mutable_get_photo_rsp()->set_last_user_get_time(10);
                        #endif

                        #ifdef PHOTO_F
                        printf("last_publisher_id: %d\n",common_rsp.get_photo_rsp().last_publisher_id());
                        printf("last_publisher_time: %d\n",common_rsp.get_photo_rsp().last_publisher_time());
                        printf("last_user_get_time: %d\n",common_rsp.get_photo_rsp().last_user_get_time());
                        #endif
                        //common_rsp.mutable_get_photo_rsp()->set_last_publish_name(user_svr.GetUserNameByUserId(publisher_id));                        
					}else{
						printf("photo info is null\n");
					}
                    ret = SUCCESS;
                    common_rsp.mutable_get_photo_rsp()->set_ret(ret);
                    printf("before SerializeToArray\n");
                    common_rsp.SerializeToArray(sock.send_buffer, 10240);
                    printf("after SerializeToArray\n");
                    sock.SocketSend(common_rsp.ByteSize());
                    get_photo_session.collect_count = user_svr_count;
                    continue;
                } else {
                    
                } 
                if (get_photo_session.collect_count == user_svr_count) {
                    common_rsp.mutable_get_photo_rsp()->set_ret(ret);
                    common_rsp.SerializeToArray(sock.send_buffer, 10240);
                    sock.SocketSend(common_rsp.ByteSize());
                }
            }
            break;
            case GET_MESSAGE_LIST_REQ:
            //服务器将用户的一部分message返回给Client，用于给用户看
            {
                get_mess_session.user_id = common_req.get_message_list_req().user_id();
                common_rsp.mutable_get_message_list_rsp()->Clear();
                inner_req.mutable_check_user_exist()->Clear();
                inner_req.mutable_header()->set_ver(1);
                inner_req.mutable_header()->set_cmd_type(GET_MESSAGE_LIST_CHECK_ID_EXIST_REQ);
                inner_req.mutable_check_user_exist()->set_user_id(get_mess_session.user_id);
                char data[10240] = {0};
                inner_req.SerializeToArray(data, inner_req.ByteSize());
                for (int i = 0; i < user_svr_count; i++) {
                    bus.Send(server_id, user_svr_id[i], data, inner_req.ByteSize());
                    inner_req_num++;
                }
                get_mess_session.collect_count = 0;
                            
            }
            break;
            case GET_MESSAGE_LIST_CHECK_ID_EXIST_RSP:
            {
                if (get_mess_session.collect_count == user_svr_count) {                
                    break;
                }
                get_mess_session.collect_count++;               
                ret = inner_rsp.check_user_exist().ret();                
                if (ret == USER_EXIST) {
                    std::vector<int> ids = mess_svr.GetMessageIds(get_mess_session.user_id);                    
                    for (int i = 0; i<ids.size() && i<10; i++) {
                        MessageInfo* message = mess_svr.GetMessage(ids[i]);
                        //add    repeated MessageItem message_list = 3; 
                        ssp::MessageItem* item=common_rsp.mutable_get_message_list_rsp()->add_message_list();
                        item->set_publisher_id(message->user_id());
                        item->set_publish_time(message->publish_time());                       
                        item->set_content(message->content());

                        #ifdef GET_MESSAGE_F
                        printf("get message. publish_id: %d, publish_time: %d, content: %s\n",
                               item->publisher_id(),
                               item->publish_time(),
                               item->content().c_str());
                        #endif
                    }
                    PhotoInfo *photo = photo_svr.GetPhoto(get_mess_session.user_id);
                    photo_svr.UpdatePhoto(get_mess_session.user_id, photo->last_publisher_id(), time_now, false);
                    ret = SUCCESS;
                    common_rsp.mutable_get_message_list_rsp()->set_ret(ret);
                    common_rsp.SerializeToArray(sock.send_buffer, 10240);
                    sock.SocketSend(common_rsp.ByteSize());
                    get_mess_session.collect_count = user_svr_count;
                    /*
                    #ifdef GET_MESSAGE_F
                    int list_size = common_rsp.get_message_list_rsp().message_list_size();
                    printf("message_list_size(): %d\n", list_size);
                    for(int i=0;i<list_size;i++){
                        printf("publish_id: %d, publish_time: %ld, content: %s\n",
                               common_rsp.get_message_list_rsp().message_list(i).publisher_id(),
                               common_rsp.get_message_list_rsp().message_list(i).publish_time(),
                               common_rsp.get_message_list_rsp().message_list(i).content().c_str());
                    }
                    #endif
                    */
                    continue;
                } else {
                    
                } 
                if (get_mess_session.collect_count == user_svr_count) {
                    common_rsp.mutable_get_message_list_rsp()->set_ret(ret);
                    common_rsp.SerializeToArray(sock.send_buffer, 10240);
                    sock.SocketSend(common_rsp.ByteSize());
                }
            }
            break;
            case DEL_FRIEND_REQ:
            {
                del_friend_session.user_id = common_req.del_friend_req().user_id();
                del_friend_session.other_id = common_req.del_friend_req().other_id();

                #ifdef DEL_FRIEND_F
                printf("user_id: %d, other_id: %d\n", del_friend_session.user_id, del_friend_session.other_id);
                #endif

                common_rsp.mutable_del_friend_rsp()->Clear();
                inner_req.mutable_check_user_exist()->Clear();
                inner_req.mutable_header()->set_ver(1);
                inner_req.mutable_header()->set_cmd_type(DEL_FRIEND_CHECK_USER_ID_EXIST_REQ);
                inner_req.mutable_check_user_exist()->set_user_id(del_friend_session.user_id);
                char data[10240] = {0};
                inner_req.SerializeToArray(data, inner_req.ByteSize());
                for (int i = 0; i < user_svr_count; i++) {
                    bus.Send(server_id, user_svr_id[i], data, inner_req.ByteSize());
                    inner_req_num++;
                }
                del_friend_session.collect_count = 0;   
                del_friend_session.ret = USER_NOT_EXIST;             
            }
            break;
            case DEL_FRIEND_CHECK_USER_ID_EXIST_RSP:
            {
                if (del_friend_session.collect_count == user_svr_count) {                
                    break;
                }
                del_friend_session.collect_count++;               
                ret = inner_rsp.check_user_exist().ret();
                if(del_friend_session.ret != USER_EXIST && ret == USER_EXIST) {
                    del_friend_session.ret = USER_EXIST;
                }                
                if (del_friend_session.ret == USER_EXIST && del_friend_session.collect_count == user_svr_count) {
                    inner_req.mutable_check_user_exist()->Clear();
                    inner_req.mutable_header()->set_ver(1);
                    inner_req.mutable_header()->set_cmd_type(DEL_FRIEND_CHECK_OTHER_ID_EXIST_REQ);                                        
                    inner_req.mutable_check_user_exist()->set_user_id(del_friend_session.other_id);
                    char data[10240] = {0};                                                            
                    inner_req.SerializeToArray(data, 10240);
                    for (int i = 0; i < user_svr_count; i++) {
                        bus.Send(server_id, user_svr_id[i], data, inner_req.ByteSize());
                        inner_req_num++;
                    }
                    continue;
                } else {
                    
                } 
                if (del_friend_session.collect_count == user_svr_count) {
                    common_rsp.mutable_del_friend_rsp()->set_ret(ret);
                    common_rsp.SerializeToArray(sock.send_buffer, 10240);
                    sock.SocketSend(common_rsp.ByteSize());
                }
            }
            break;
            case DEL_FRIEND_CHECK_OTHER_ID_EXIST_RSP:
            {
                if (del_friend_session.collect_count >= 2*user_svr_count) {                
                    break;
                }
                del_friend_session.collect_count++;               
                ret = inner_rsp.check_user_exist().ret();

                #ifdef DEL_FRIEND_F
                printf("other ID check_user_exist: %d\n", ret);
                #endif

                if (ret == USER_EXIST) {
                    ret = rela_svr.DeleteFriend(del_friend_session.user_id, del_friend_session.other_id);

                    #ifdef DEL_FRIEND_F
                    printf("DeleteFriend return: %d\n", ret);
                    #endif

                    common_rsp.mutable_del_friend_rsp()->set_ret(ret);
                    common_rsp.SerializeToArray(sock.send_buffer, common_rsp.ByteSize());
                    sock.SocketSend(common_rsp.ByteSize());     
                    del_friend_session.collect_count++;                                                       
                    continue;
                } else {
                    
                }

                #ifdef DEL_FRIEND_F
                printf("front del_friend_session.collect_count: %d\n", del_friend_session.collect_count);
                #endif

                if (del_friend_session.collect_count == 2*user_svr_count) {

                    #ifdef DEL_FRIEND_F
                    printf("del_friend_session.collect_count: %d\n", del_friend_session.collect_count);
                    #endif

                    common_rsp.mutable_del_friend_rsp()->set_ret(ret);
                    common_rsp.SerializeToArray(sock.send_buffer, common_rsp.ByteSize());
                    sock.SocketSend(common_rsp.ByteSize());

                    #ifdef DEL_FRIEND_F
                    printf("send to client finished\n");
                    #endif
                }
            }
            break;
            case LOGOUT_REQ:
			{		
                logout_session.user_id = common_req.logout_req().user_id();
                common_rsp.mutable_logout_rsp()->Clear();
                inner_req.mutable_check_user_exist()->Clear();
                inner_req.mutable_header()->set_ver(1);
                inner_req.mutable_header()->set_cmd_type(LOGOUT_CHECK_ID_EXIST_REQ);
                inner_req.mutable_check_user_exist()->set_user_id(logout_session.user_id);
                char data[10240] = {0};
                inner_req.SerializeToArray(data, inner_req.ByteSize());
                for (int i = 0; i < user_svr_count; i++) {
                    bus.Send(server_id, user_svr_id[i], data, inner_req.ByteSize());
                    inner_req_num++;
                }
                logout_session.collect_count = 0;

			}
            break;
            case LOGOUT_CHECK_ID_EXIST_RSP:
            {
                if (logout_session.collect_count == user_svr_count) {                
                    break;
                }
                logout_session.collect_count++;               
                ret = inner_rsp.check_user_exist().ret();                
                if (ret == USER_EXIST) {
                    //ret = photo_svr.StorageDb(logout_session.user_id);
                    ret = SUCCESS;
                    common_rsp.mutable_logout_rsp()->set_ret(ret);
                    common_rsp.SerializeToArray(sock.send_buffer,10240);
                    sock.SocketSend(common_rsp.ByteSize());
                    epoll_ctl(subfd, EPOLL_CTL_DEL, sock.client_socket, NULL);
                    sock.ClientClose();
                    logout_session.collect_count = user_svr_count;
                    continue;
                } else {
                    
                } 
                if (logout_session.collect_count == user_svr_count) {
                    common_rsp.mutable_get_photo_rsp()->set_ret(ret);
                    common_rsp.SerializeToArray(sock.send_buffer, 10240);
                    sock.SocketSend(common_rsp.ByteSize());
                }
            }
            break;
            case TEST_TYPE_REQ:
            {

            }
            break;
            case SERVER_SHUTDOWN:
            {
                server_on = 0;
            }
            break;
            default:
            break;
        }
    }
}

void* sub_reactor(void *arg) {
    int subfd = *(int *)arg;
    REACTOR(L_RED "<Sub Reactor>" NONE" : in sub reactor %d.\n", subfd);
    
    struct epoll_event ev, events[MAXEVENTS];
    //for 是 epoll 的标准使用方式
    for (;;) {
        REACTOR(YELLOW "<in sub reactor loop: start>\n" NONE);
        // sigset_t sigset;
        // sigemptyset(&sigset);
        // sigaddset(&sigset, SIGALRM);
        int nfds = epoll_pwait(subfd, events, MAXEVENTS, -1, nullptr);
        if (nfds < 0) {
            REACTOR(L_RED "<Sub Reactor Err> : sub reactor error %d.\n" NONE, subfd);
            continue;
        }
        for (int i = 0; i < nfds; i++) {
            REACTOR(YELLOW "<in sub reactor loop: for each event>\n" NONE);
            int fd = events[i].data.fd;
            SspSocket sock;
            //REACTOR(YELLOW"<in sub reactor loop: event before recv> : <%d, %d>\n"NONE, i, fd);
            int ret = recv(fd, sock.recv_buffer, 10240, 0);
            //REACTOR(YELLOW"<in sub reactor loop: event after recv>\n"NONE);
            //考虑 fd 是非阻塞的情况
            if (ret < 0 &&  !(errno & EAGAIN)) {
                close(fd);
                epoll_ctl(subfd, EPOLL_CTL_DEL, fd, NULL);
                REACTOR(L_RED "<Sub Reactor Err> : connecttion of %d on %d is closed.\n" NONE, fd, subfd);
                continue;  
            }       
            sock.client_socket = fd;
            work(sock, subfd); 
        }
    }
}


