/*************************************************************************
	> File Name: qt_connect_test.cpp
	> Author: kwb
	> Mail: 
	> Created Time: Fri 27 May 2022 11:31:27 PM CST
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Socket.h"
#include <bits/stdc++.h>
SspSocket sock;

int main() {
	sock.Init();
    sock.SocketInit();
	int server_on = 1;
	
	while (server_on) {
		int check_sock = -1;
		sock.SocketAccept();
		printf("sock.accept_flag: %d", sock.accept_flag);
		//check_sock=sock.SocketCheckRecv();
		if (sock.accept_flag == 1) {
			if (sock.client_socket < 0) {
				printf("SocketAccept failed: %d\n", sock.client_socket);
				continue;
			} 
			printf("SocketAccept success: %d\n", sock.client_socket);
		}		
		check_sock=sock.SocketCheckRecv();
		if(check_sock>0){
			printf("check_sock ok\n");
			printf("recv: %s\n", sock.recv_buffer);			
			memset(sock.recv_buffer,0,strlen(sock.recv_buffer));			
		} else {
			continue;
		}
	}
	sock.ServerClose();
	return 0;
}

