/*************************************************************************
	> File Name: Socket.h
	> Author: kwb
	> Mail: 
	> Created Time: Mon 28 Mar 2022 12:39:31 AM CST
 ************************************************************************/

#ifndef _SOCKET_H
#define _SOCKET_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // read、write、getpid 等函数
#include <vector>
#include "Config.h"

class SspSocket {
public:
    int server_socket; //监听 socket
    struct sockaddr_in server_addr;
    int client_socket;
    struct sockaddr_in client_addr;
    int accept_flag = 0; // 标志位。有client连接时 > 0

    char recv_buffer[10240];
    char send_buffer[10240];
    Config config;
    int Init();
    int SocketInit();
    int ClientSocketInit();
    int SocketAccept();
    int SocketCheckRecv();
    int SocketSend(int send_size);
    int ClientClose();
    int ServerClose();
    int show_send_buffer(int size);
    int show_recv_buffer(int size);
};   

#endif
