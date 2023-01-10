#include "Socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#define SOCKET_M

int SspSocket::Init() {
    //accept_flag=0;
	printf("SocketInit\n");
    return config.ReadConfig();
}

int SspSocket::SocketInit() {
    /* 这里的 ip 和 port 是硬编码，移到其他服务器就用不了了，可移植性差，所以需要写配置文件 */
    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(config.socket_port());
    //如果这里监听的是 127.0.0.1，意味着客户端也需要部署在本机上
    server_addr.sin_addr.s_addr = inet_addr(config.socket_addr());
    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_socket, 10000);
    return 0;
}

int SspSocket::ClientSocketInit() {
    //第三个参数：IPPROTO_TCP 为TCP；0 为自动
    client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(config.socket_addr());
	server_addr.sin_port = htons(config.socket_port());
    int conn_ret = connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (conn_ret < 0) {
        return conn_ret;
    }
    //accept_flag = 1;
    return 0;
}

int SspSocket::SocketAccept() {
    /* if (accept_flag == 1) {
        return 0;
    } */
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    client_socket = accept(server_socket, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    //accept_flag = 1;
    return 0;
}

int SspSocket::SocketCheckRecv() {
    /* if (accept_flag == 0) {
        return -1;
    } */
    int ret = recv(client_socket, recv_buffer, 10240, 0);
    if (ret > 0) {
        return ret;
    } else {
        return -1;
    }
    return 0;
}

int SspSocket::SocketSend(int send_size) {
    int ret = send(client_socket, send_buffer, send_size, 0);

    #ifdef SOCKET_M
    printf("send_size: %d, send() success: %d\n", send_size, ret);
    #endif

    memset(send_buffer, 0, send_size); //下次发送的时候就不会有脏数据了
;    if (ret < 0) {
        return -1;
    }
    return 0;
}

int SspSocket::ClientClose() {
    close(client_socket);
    //accept_flag = 0;
    return 0;
}

int SspSocket::ServerClose() {
    close(server_socket);
    return 0;
}

int SspSocket::show_send_buffer(int size) {
    for (int i = 0; i < size; i++) {
        int l4 = send_buffer[i] & 0x000f;
        int h4 = (send_buffer[i]>>4) & 0x000f;
        int l0 = l4 & 0x0001;
        l4 = l4 >> 1;
        int l1 = l4 & 0x0001;
        l4 = l4 >> 1;
        int l2 = l4 & 0x0001;
        l4 = l4 >> 1;
        int l3 = l4 & 0x0001;

        int h0 = h4 & 0x0001;
        h4 = h4 >> 1;
        int h1 = h4 & 0x0001;
        h4 = h4 >> 1;
        int h2 = h4 & 0x0001;
        h4 = h4 >> 1;
        int h3 = h4 & 0x0001;

        printf("%02x %d%d%d%d %d%d%d%d %3d", send_buffer[i], h3, h2, h1, h0, l3, l2, l1, l0, send_buffer[i]);
        if('0'<=send_buffer[i]&&send_buffer[i]<='9')printf("'%c'",send_buffer[i]);
		if('A'<=send_buffer[i]&&send_buffer[i]<='Z')printf("'%c'",send_buffer[i]);
		if('a'<=send_buffer[i]&&send_buffer[i]<='z')printf("'%c'",send_buffer[i]);
		printf("\n");
    }
    return 0;
}

int SspSocket::show_recv_buffer(int size) {
    for (int i=0;i<size;i++){
		int l4=recv_buffer[i]&0x000f;
		int h4=(recv_buffer[i]>>4)&0x000f;
		int l0=l4&0x0001;
		l4=l4>>1;
		int l1=l4&0x0001;
		l4=l4>>1;
		int l2=l4&0x0001;
		l4=l4>>1;
		int l3=l4&0x0001;
		int h0=h4&0x0001;
		h4=h4>>1;
		int h1=h4&0x0001;
		h4=h4>>1;
		int h2=h4&0x0001;
		h4=h4>>1;
		int h3=h4&0x0001;
		printf("%02x %d%d%d%d %d%d%d%d %3d ",recv_buffer[i],h3,h2,h1,h0,l3,l2,l1,l0,recv_buffer[i]);
		if('0'<=recv_buffer[i]&&recv_buffer[i]<='9')printf("'%c'",recv_buffer[i]);
		if('A'<=recv_buffer[i]&&recv_buffer[i]<='Z')printf("'%c'",recv_buffer[i]);
		if('a'<=recv_buffer[i]&&recv_buffer[i]<='z')printf("'%c'",recv_buffer[i]);
		printf("\n");
	}
    return 0;
}