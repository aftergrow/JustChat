#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <string>>
#include <QMessageBox>
#include <QStringListModel>
#include <QStandardItemModel>
#include "D:\Haizei\ssp\ssp_client\common\proto.h"
#include "D:\Haizei\ssp\ssp_client\common\ret_value.h"

#include<bits/stdc++.h>

//debug 宏
//#define ADD_FRIEND_M
//#define DEL_FRIEND_M
#define SOCKET_M
#define LOGIN_M
#define GET_MESSAGE_M
#define GET_PHOTO_M

#define WAIT_NONE 0
#define WAIT_SEND 1
#define WAIT_RECV 2

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    is_connected = false;
    is_logined = false; 
    send_or_recv = WAIT_NONE;


}

MainWindow::~MainWindow()
{
    delete ui;
}

QString getRetString(int ret_value){
    switch(ret_value){
    case USER_EXIST:
        return "用户已存在";
    case USER_NOT_EXIST:
        return "用户不存在";
    case WRONG_PASSWORD:
        return "密码错误";
    case NOT_FRIEND:
        return "不是好友关系";
    case ALREADY_FRIEND:
        return "已经是好友了";
    case FRIEND_TOO_MUCH:
        return "好友列表已满";
    case RELATION_NOT_EXIST:
        return "好友服务器异常，请重新拉取";
    case MESSAGE_NOT_EXIST:
        return "消息已过期或被删除";
    case PHOTO_NOT_EXIST:
        return "消息已过期或被删除";
    default:
        return QString::number(ret_value);
    }
    return QString::number(ret_value);
}

//return: <0，失败，=0成功
int MainWindow::SocketInit()
{
    #ifdef _WIN32
        //启动windows socket 2,x环境 windows特有
        ver = MAKEWORD(2,2);//WinSock库版本号
        if(0 != WSAStartup(ver,&dat))
        {
            char ret_str[256];
            //sprintf(ret_str,"connect_ret:%d\n",conn_ret);
            sprintf(ret_str,"WSAStartup failed!");

            QMessageBox msg;
            msg.setText(ret_str);
            msg.exec();
            return -1;
        }
    #endif
    sock_client=socket(AF_INET, SOCK_STREAM, 0);
    if(INVALID_SOCKET == sock_client)//建立失败
    {
        char ret_str[256];
        //sprintf(ret_str,"connect_ret:%d\n",conn_ret);
        sprintf(ret_str,"socket create failed!");

        QMessageBox msg;
        msg.setText(ret_str);
        msg.exec();
        return -1;
    }
    struct sockaddr_in server_addr;
    memset(&server_addr, 0 ,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    #ifdef _WIN32
        server_addr.sin_addr.S_un.S_addr =  inet_addr("118.31.74.118");//想要连接的IP
    #else
        server_addr.sin_addr.s_addr =  inet_addr("127.0.0.1");//想要连接的IP
    #endif
    //server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8999);
    int conn_ret=::connect(sock_client, (struct sockaddr*)&server_addr, sizeof(server_addr));

    if(conn_ret<0){
        char ret_str[256];
        //sprintf(ret_str,"connect_ret:%d\n",conn_ret);
        sprintf(ret_str,"未检测到服务器");

        QMessageBox msg;
        msg.setText(ret_str);
        msg.exec();
    }
    return conn_ret;
}

int MainWindow::SocketSend(int size){
    if(send_or_recv == WAIT_RECV){
        return -1;
    }
    int ret = ::send(sock_client,send_buffer,size,0);
    return ret;
}

int MainWindow::SocketRecv()
{
    //QMessageBox msg;
    QString ret_qs;
    QString login_user_id_qs;
    QString publish_id_qs;
    QString last_publish_time_qs;
    QString last_user_get_time_qs;
    int rsp_ret;
    int ret=::recv(sock_client,recv_buffer,10240,0);

    #ifdef SOCKET_M
    ret_qs = QString::number(ret);
    ui->EditLog->append("recv_size: 10240, recv() success: "+ret_qs);
    #endif

    if(ret>0){
        clinetRsp.ParseFromArray(recv_buffer,10240);
        int recv_cmd_type = clinetRsp.header().cmd_type();
        QString recv_cmd_type_qs=QString::number(recv_cmd_type);
        ui->EditLog->append("recv_cmd_type:"+recv_cmd_type_qs);
        switch(clinetRsp.header().cmd_type()){
            case REG_RSP:
                ui->EditLog->append("收到注册回包");
                rsp_ret=clinetRsp.reg_rsp().ret();
                if(rsp_ret!=SUCCESS){
                    ret_qs=getRetString(rsp_ret);//QString::number(rsp_ret);
                    ui->EditLog->append("ret:"+ret_qs);
                }else{
                    ret_qs=QString::number(clinetRsp.reg_rsp().ret());
                    ui->EditLog->append("ret:{user_id:"+ret_qs+"}");
                }
                break;
            case LOGIN_RSP:
                //msg.setText("收到登录回包");
                //msg.exec();
                ui->EditLog->append("收到登录回包");
                rsp_ret=clinetRsp.login_rsp().ret();
                if(rsp_ret!=SUCCESS){
                    ret_qs=getRetString(rsp_ret);//ret_qs=QString::number(rsp_ret);
                    ui->EditLog->append("ret:"+ret_qs);
                    is_logined=false;
                }else{
                    login_user_id = clinetRsp.login_rsp().user_id();
                    ret_qs=QString::number(clinetRsp.login_rsp().user_id());
                    ui->EditLog->append("ret:{user_id:"+ret_qs+"}");
                }
                break;
            case ADD_FRIEND_RSP:
                ui->EditLog->append("收到添加好友回包");

                rsp_ret=clinetRsp.add_friend_rsp().ret();

                #ifdef ADD_FRIEND_M
                ret_qs=QString::number(rsp_ret);
                ui->EditLog->append("ret:"+ret_qs);
                #endif

                if(rsp_ret!=SUCCESS){
                    ret_qs=getRetString(rsp_ret);//ret_qs=QString::number(rsp_ret);
                    ui->EditLog->append("ret:"+ret_qs);
                }else{
                    ret_qs=QString::number(clinetRsp.add_friend_rsp().ret());
                    ui->EditLog->append("ret:"+ret_qs+"--成功");
                }
                break;
            case DEL_FRIEND_RSP:
                ui->EditLog->append("收到删除好友回包");

                rsp_ret=clinetRsp.del_friend_rsp().ret();

                #ifdef DEL_FRIEND_M
                ret_qs=QString::number(rsp_ret);
                ui->EditLog->append("ret:"+ret_qs);
                #endif

                if(rsp_ret!=SUCCESS){
                    ret_qs=getRetString(rsp_ret);//ret_qs=QString::number(rsp_ret);
                    ui->EditLog->append("ret:"+ret_qs);
                }else{
                    ret_qs=QString::number(clinetRsp.del_friend_rsp().ret());
                    ui->EditLog->append("ret:"+ret_qs+"--成功");
                }
                break;
            case LOGOUT_RSP:
                //msg.setText("收到登出回包");
                //msg.exec();
                ui->EditLog->append("收到登出回包");
                rsp_ret=clinetRsp.logout_rsp().ret();
                if(rsp_ret!=SUCCESS){
                    ret_qs=getRetString(rsp_ret);//ret_qs=QString::number(rsp_ret);
                    ui->EditLog->append("ret:"+ret_qs);
                }else{
                    ret_qs=getRetString(rsp_ret);//=QString::number(loginRsp.user_id());
                    ui->EditLog->append("ret:"+ret_qs+"}");
                    is_logined=false;
                    is_connected=false;
                    closesocket(sock_client);
                }
                break;
            case PUBLISH_MESSAGE_RSP:
                //msg.setText("收到发布回包");
                //msg.exec();
                ui->EditLog->append("收到发布回包");
                rsp_ret=clinetRsp.publish_message_rsp().ret();
                if(rsp_ret!=SUCCESS){
                    ret_qs=getRetString(rsp_ret);//ret_qs=QString::number(rsp_ret);
                    ui->EditLog->append("ret:"+ret_qs);
                }else{
                    ret_qs=getRetString(rsp_ret);//=QString::number(loginRsp.user_id());
                    ui->EditLog->append("ret:{"+ret_qs+"}");
                }
                break;
             case GET_MESSAGE_LIST_RSP:
                {
                    //msg.setText("收到刷新回包");
                    //msg.exec();
                    ui->EditLog->append("收到刷新回包");
                    rsp_ret=clinetRsp.get_message_list_rsp().ret();
                    if(rsp_ret!=SUCCESS){
                        ret_qs=getRetString(rsp_ret);//ret_qs=QString::number(rsp_ret);
                        ui->EditLog->append("ret:"+ret_qs);
                    } else {
                        int list_size = clinetRsp.get_message_list_rsp().message_list_size();
                        ui->tblMessageList->setRowCount(list_size);
                        ui->tblMessageList->setColumnCount(3);
                        for(int i=0;i<list_size;i++){
                            std::string s1 = std::to_string(clinetRsp.get_message_list_rsp().message_list(i).publisher_id());
                            std::string s2 = std::to_string(clinetRsp.get_message_list_rsp().message_list(i).publish_time());
                            ui->tblMessageList->setItem(i,0,new QTableWidgetItem(s1.c_str()));
                            ui->tblMessageList->setItem(i,1,new QTableWidgetItem(s2.c_str()));
                            ui->tblMessageList->setItem(i,2,new QTableWidgetItem(clinetRsp.get_message_list_rsp().message_list(i).content().c_str()));
                        }

                        ret_qs=getRetString(rsp_ret);//=QString::number(loginRsp.user_id());
                        ui->EditLog->append("ret:{"+ret_qs+"}");

                        #ifdef GET_MESSAGE_M
                        QMessageBox msg;
                        ret_qs = QString::number(list_size);
                        ui->EditLog->append("message_list_size:"+ret_qs);
                        for(int i=0;i<list_size;i++){
                            QString ret_qs1, ret_qs2, ret_qs3;
                            ret_qs1 = QString::number(clinetRsp.get_message_list_rsp().message_list(i).publisher_id());
                            ret_qs2 = QString::number(clinetRsp.get_message_list_rsp().message_list(i).publish_time());
                            ret_qs3 = (clinetRsp.get_message_list_rsp().message_list(i).content().c_str());
                            ui->EditLog->append("publisher_id:{"+ret_qs1+"}, publish_time:{"+ret_qs2+"}, content:{"+ret_qs3+"}");
                        }
                        #endif

                    }

                }
                break;
            case GET_PHOTO_RSP:
                ui->EditLog->append("收到快照回包");
                uint32_t last_publish_time;
                int publish_id;

                #ifdef GET_PHOTO_M
                ui->EditLog->append("last_user_get_time: "+QString::number(clinetRsp.get_photo_rsp().last_user_get_time()));
                #endif

                last_publish_time = clinetRsp.get_photo_rsp().last_publisher_time();
                //第一次登录时的情况;有新消息来的情况
                if(get_photo_flag == 0) {
                    last_user_get_time = clinetRsp.get_photo_rsp().last_user_get_time();
                } else if(get_photo_flag == 1){ //publish message

                } else if(get_photo_flag == 2) { //get message
                    last_user_get_time = clinetRsp.get_photo_rsp().last_user_get_time();
                } else {

                }
                if(last_user_get_time > last_publish_time) {
                    ui->EditPhoto->appendPlainText("没有新消息！");
                } else {
                    publish_id = clinetRsp.get_photo_rsp().last_publisher_id();
                    publish_id_qs = QString::number(publish_id);
                    ui->EditPhoto->appendPlainText("user: "+publish_id_qs+" 有新消息！");
                }

                #ifdef GET_PHOTO_M
                rsp_ret=clinetRsp.get_photo_rsp().ret();
                ret_qs = QString::number(rsp_ret);
                publish_id = clinetRsp.get_photo_rsp().last_publisher_id();
                publish_id_qs = QString::number(publish_id);
                login_user_id_qs = QString::number(login_user_id);
                last_publish_time_qs = QString::number(last_publish_time);
                last_user_get_time_qs = QString::number(last_user_get_time);
                ui->EditLog->append("ret: "+ret_qs+", user_id:"+login_user_id_qs+", publish_id:"+publish_id_qs+", last_user_publish_time:"+last_publish_time_qs+", last_get_time:"+last_user_get_time_qs);
                #endif

                rsp_ret=clinetRsp.get_photo_rsp().ret();
                if(rsp_ret!=SUCCESS){
                    ret_qs=getRetString(rsp_ret);//ret_qs=QString::number(rsp_ret);
                    ui->EditLog->append("ret:"+ret_qs);
                }else{
                    ret_qs=getRetString(rsp_ret);//=QString::number(loginRsp.user_id());
                    ui->EditLog->append("ret:{"+ret_qs+"}");
                }
                break;
            default:
                break;
        }

        return ret;
    }
    return 0;
}

int MainWindow::SocketClose()
{
    #ifdef _WIN32
        //关闭socket
        closesocket(sock_client);
    #else
        //关闭socket/LINUX
        close(_mysocket);
    #endif
    #ifdef _WIN32
        //清除windows socket 环境
        WSACleanup();
    #endif
    return 0;
}

int MainWindow::WaitRsp(){
    send_or_recv = WAIT_RECV;
    int times=10;
    while(times--){
        int ret=SocketRecv();
        if(ret>0){
            send_or_recv = WAIT_NONE;
            break;
        }
        //sleep(1);
    }
    return 0;
}

void MainWindow::on_Reg_clicked()
{
    int ret=0;
    //网络链接判断
    if(!is_connected){
        ret=SocketInit();
    }
    if(ret==0){
        is_connected=true;
        clientReq.Clear();
        //Register
        QString username_text=ui->EditUsername->toPlainText();
        QByteArray username_qba_u8 = username_text.toUtf8();
        char* username_cstr=username_qba_u8.data();
        QString password_text=ui->EditPassword->toPlainText();
        QByteArray password_qba_u8 = password_text.toUtf8();
        char* password_cstr=password_qba_u8.data();
        clientReq.mutable_header()->set_ver(1);
        clientReq.mutable_header()->set_cmd_type(REG_REQ);
        clientReq.mutable_reg_req()->set_user_name(username_cstr);
        clientReq.mutable_reg_req()->set_password(password_cstr);
        clientReq.mutable_reg_req()->set_from(23);
        clientReq.SerializeToArray(send_buffer,10240);
        int req_size=clientReq.ByteSize();
        SocketSend(req_size);
        WaitRsp();
    }
}

void MainWindow::on_Login_clicked()
{
    if(is_logined){
        QMessageBox msg;
        msg.setText("你已经登录了");
        msg.exec();
        return;
    }
    int ret=0;
    if(!is_connected){
        ret=SocketInit();
    }
    if(ret==0){
        is_connected=true;
        clientReq.Clear();
        //LoginReq
        QString username_text=ui->EditUsername->toPlainText();
        QByteArray username_qba_u8 = username_text.toUtf8();
        char* username_cstr=username_qba_u8.data();
        QString password_text=ui->EditPassword->toPlainText();
        QByteArray password_qba_u8 = password_text.toUtf8();
        char* password_cstr=password_qba_u8.data();

        clientReq.mutable_header()->set_ver(1);
        clientReq.mutable_header()->set_cmd_type(LOGIN_REQ);
        clientReq.mutable_login_req()->set_user_name(username_cstr);
        clientReq.mutable_login_req()->set_password(password_cstr);
        clientReq.SerializeToArray(send_buffer,10240);
        int req_size=clientReq.ByteSize();
        SocketSend(req_size);
        is_logined=true;
        WaitRsp();

        //get login user photo info
/*
        get_photo_flag = 0;
        clientReq.Clear();
        clientReq.mutable_header()->set_ver(1);
        clientReq.mutable_header()->set_cmd_type(GET_PHOTO_REQ);
        clientReq.mutable_get_photo_req()->set_user_id(login_user_id);
        clientReq.SerializeToArray(send_buffer,10240);
        req_size=clientReq.ByteSize();
        SocketSend(req_size);
        WaitRsp();
*/
    }
}




void MainWindow::on_AddFriend_clicked()
{

    #ifdef ADD_FRIEND_M
    QMessageBox msg1;
    msg1.setText("添加好友！");
    msg1.exec();
    #endif

    if(!is_logined){
        QMessageBox msg;
        msg.setText("请先登录");
        msg.exec();
        return;
    }
    int ret=0;
    if(!is_connected){
        ret=SocketInit();
    }
    if(ret==0){
        is_connected=true;
        clientReq.Clear();
        //LoginReq
        QString friendid_text=ui->EditFriendName->toPlainText();
        QByteArray friendid_qba_u8 = friendid_text.toUtf8();
        char* friendid_cstr=friendid_qba_u8.data();
        int friendid_i = atoi(friendid_cstr);
        clientReq.mutable_header()->set_ver(1);
        clientReq.mutable_header()->set_cmd_type(ADD_FRIEND_REQ);
        clientReq.mutable_add_friend_req()->set_user_id(login_user_id);
        clientReq.mutable_add_friend_req()->set_other_id(friendid_i);
        clientReq.SerializeToArray(send_buffer,10240);
        int req_size=clientReq.ByteSize();
        SocketSend(req_size);
        WaitRsp();
    }
}


void MainWindow::on_DeleteFriend_clicked()
{

    #ifdef DEL_FRIEND_M
    QMessageBox msg1;
    msg1.setText("删除好友！");
    msg1.exec();
    #endif

    if(!is_logined){
        QMessageBox msg;
        msg.setText("请先登录");
        msg.exec();
        return;
    }
    int ret=0;
    if(!is_connected){
        ret=SocketInit();
    }
    if(ret==0){
        is_connected=true;
        clientReq.Clear();
        //LoginReq
        QString friendid_text=ui->EditFriendName_2->toPlainText();
        QByteArray friendid_qba_u8 = friendid_text.toUtf8();
        char* friendid_cstr=friendid_qba_u8.data();
        int friendid_i = atoi(friendid_cstr);
        clientReq.mutable_header()->set_ver(1);
        clientReq.mutable_header()->set_cmd_type(DEL_FRIEND_REQ);
        clientReq.mutable_del_friend_req()->set_user_id(login_user_id);
        clientReq.mutable_del_friend_req()->set_other_id(friendid_i);
        clientReq.SerializeToArray(send_buffer,10240);
        int req_size=clientReq.ByteSize();
        SocketSend(req_size);
        WaitRsp();
    }
}


void MainWindow::on_SendMessage_clicked()
{
    if(!is_logined){
        QMessageBox msg;
        msg.setText("请先登录");
        msg.exec();
        return;
    }
    int ret=0;
    if(!is_connected){
        ret=SocketInit();
    }
    if(ret==0){
        is_connected=true;
        clientReq.Clear();
        //SendMessage
        QString message_text=ui->EditPublishMessage->toPlainText();
        QByteArray message_qba_u8 = message_text.toUtf8();
        char* message_cstr=message_qba_u8.data();
        clientReq.mutable_header()->set_ver(1);
        clientReq.mutable_header()->set_cmd_type(PUBLISH_MESSAGE_REQ);
        clientReq.mutable_publish_message_req()->set_user_id(login_user_id);
        clientReq.mutable_publish_message_req()->set_content(message_cstr);
        clientReq.SerializeToArray(send_buffer,10240);
        int req_size=clientReq.ByteSize();
        SocketSend(req_size);
        ui->EditPublishMessage->clear();
        WaitRsp();

        /*
        get_photo_flag = 1;
        clientReq.Clear();
        clientReq.mutable_header()->set_ver(1);
        clientReq.mutable_header()->set_cmd_type(GET_PHOTO_REQ);
        clientReq.mutable_get_photo_req()->set_user_id(login_user_id);
        clientReq.SerializeToArray(send_buffer,10240);
        req_size=clientReq.ByteSize();
        SocketSend(req_size);
        WaitRsp();
        */
    }
}


void MainWindow::on_GetMessage_clicked()
{
    if(!is_logined){
        QMessageBox msg;
        msg.setText("请先登录");
        msg.exec();
        return;
    }
    int ret=0;
    if(!is_connected){
        ret=SocketInit();
    }
    if(ret==0){
        is_connected=true;
        clientReq.Clear();
        ui->tblMessageList->clear();
        //GetMessage
        clientReq.mutable_header()->set_ver(1);
        clientReq.mutable_header()->set_cmd_type(GET_MESSAGE_LIST_REQ);
        clientReq.mutable_get_message_list_req()->set_user_id(login_user_id);
        clientReq.SerializeToArray(send_buffer,10240);
        int req_size=clientReq.ByteSize();
        SocketSend(req_size);
        WaitRsp();

        /*
        get_photo_flag = 2;
        clientReq.Clear();
        clientReq.mutable_header()->set_ver(1);
        clientReq.mutable_header()->set_cmd_type(GET_PHOTO_REQ);
        clientReq.mutable_get_photo_req()->set_user_id(login_user_id);
        clientReq.SerializeToArray(send_buffer,10240);
        req_size=clientReq.ByteSize();
        SocketSend(req_size);
        WaitRsp();
        */
    }
}


void MainWindow::on_Logout_clicked()
{
    if(!is_logined){
        QMessageBox msg;
        msg.setText("您没有登录！");
        msg.exec();
        return;
    }
    int ret=0;
    if(!is_connected){
        ret=SocketInit();
    }
    if(ret==0){
        is_connected=true;
        clientReq.Clear();
        ui->tblMessageList->clear();
        clientReq.mutable_header()->set_ver(1);
        clientReq.mutable_header()->set_cmd_type(LOGOUT_REQ);
        clientReq.mutable_logout_req()->set_user_id(login_user_id);
        clientReq.SerializeToArray(send_buffer,10240);
        int req_size=clientReq.ByteSize();
        SocketSend(req_size);
        WaitRsp();
    }
}


void MainWindow::on_Test_clicked()
{
    if(is_logined){
        QMessageBox msg;
        msg.setText("你已经登录了");
        msg.exec();
        return;
    }
    int ret=0;
    if(!is_connected){
        ret=SocketInit();
    }
    if(ret==0){
        is_connected=true;
        clientReq.Clear();
        //LoginReq
        QString username_text=ui->EditUsername->toPlainText();
        QByteArray username_qba_u8 = username_text.toUtf8();
        char* username_cstr=username_qba_u8.data();
        QString password_text=ui->EditPassword->toPlainText();
        QByteArray password_qba_u8 = password_text.toUtf8();
        char* password_cstr=password_qba_u8.data();

        clientReq.mutable_header()->set_ver(1);
        clientReq.mutable_header()->set_cmd_type(LOGIN_REQ);
        clientReq.mutable_login_req()->set_user_name(username_cstr);
        clientReq.mutable_login_req()->set_password(password_cstr);
        clientReq.SerializeToArray(send_buffer,10240);
        int req_size=clientReq.ByteSize();
        SocketSend(req_size);
        is_logined=true;
        WaitRsp();

        //get login user photo info

        get_photo_flag = 0;
        clientReq.Clear();
        clientReq.mutable_header()->set_ver(1);
        clientReq.mutable_header()->set_cmd_type(GET_PHOTO_REQ);
        clientReq.mutable_get_photo_req()->set_user_id(login_user_id);
        clientReq.SerializeToArray(send_buffer,10240);
        req_size=clientReq.ByteSize();
        SocketSend(req_size);
        WaitRsp();

    }
}

