/*************************************************************************
	> File Name: server.cpp
	> Author: kwb
	> Mail: 
	> Created Time: Tue 30 Aug 2022 06:07:39 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <pthread.h>
#include "common/macro.h"
#include "Socket.h"
#include "UserManager.h"
#include "RelationManager.h"
#include "MessageManager.h"
#include "PhotoManager.h"
#include "BusManager.h"
#include "DbManager.h"
#include "reactor.h"


#define SERVER_M

/* 单进程包含四个 server*/
/* 下面这几个 class 不能放在主函数里，因为占用空间太大，栈放不下，只能放在堆里 */
//UserSvr
//RelationSvr
//MessageSvr
//PhotoSvr
//UserManager user_svr;
RelationManager rela_svr;
MessageManager mess_svr;
PhotoManager photo_svr;
DbManager db_svr;
BusManager bus;

SspSocket sock;

int epollfd, subefd1, subefd2;

int main() {
	bus.Init();
    bus.ChannelsClear();

	db_svr.Init();
    //printf("dv_svr ret value: %d\n", ret);
    //user_svr.Start(&db_svr);//Init 
	rela_svr.Start(&db_svr);
	mess_svr.Start(&db_svr, &rela_svr);
	photo_svr.Start(&db_svr);

	sock.Init();
    sock.SocketInit();

    #ifdef SERVER_M
    printf("before epoll_create\n");
    #endif

	if ((epollfd = epoll_create(1)) < 0) {
        perror("epoll_create");
        exit(1);
    }
    if ((subefd1 = epoll_create(1)) < 0) {
        perror("epoll_create");
        exit(1);
    }
    if ((subefd2 = epoll_create(1)) < 0) {
        perror("epoll_create");
        exit(1);
    }
	SERVER(YELLOW "<D>" NONE" : Main reactor and two sub reactors created.\n");

	pthread_t tid1, tid2;
	SERVER(YELLOW "<D>" NONE" : two sub reactor threads created.\n");

	pthread_create(&tid1, NULL, sub_reactor, (void *)&subefd1);
    pthread_create(&tid2, NULL, sub_reactor, (void *)&subefd2);

	struct epoll_event events[MAXEVENTS], ev;
    ev.data.fd = sock.server_socket;
    ev.events = EPOLLIN;

    #ifdef SERVER_M
    printf("before for\n");
    #endif

    epoll_ctl(epollfd, EPOLL_CTL_ADD, sock.server_socket, &ev);

	for (;;) {
        // sigset_t sigset; //创建信号量集
        // sigemptyset(&sigset); //清空信号量集
        // sigaddset(&sigset, SIGALRM); //向信号量集中添加信号量
        //epoll_pwait() 多了一个信号参数
        SERVER(GREEN "<before epoll_pwait>\n" NONE);
        int nfds = epoll_pwait(epollfd, events, MAXEVENTS, -1, nullptr);
        SERVER(GREEN "<listen a socket>\n" NONE);
        if (nfds < 0) {
            perror("epoll_wait");
            exit(1);
        }
        for (int i = 0; i < nfds; i++) {
            int fd = events[i].data.fd;
            //监听新的连接，把新的sockfd加epollfd            
            if (fd == sock.server_socket && events[i].events & EPOLLIN) {
                int ret = sock.SocketAccept();
                if (sock.client_socket < 0) {
                    perror("accept");
                    exit(1);
                }
                ev.data.fd = sock.client_socket;
                ev.events = EPOLLIN;
                if(epoll_ctl(epollfd, EPOLL_CTL_ADD, sock.client_socket, &ev) < 0) {
                    perror("epoll_ctl");
                    exit(1);
                }
                SERVER(GREEN "<add a socket epollfd>\n" NONE);
            } else {                  
                int which = fd/2? subefd1 : subefd2;
                //在把 fd 加入到 从反应堆 之前应把它从主反应堆删除
                epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
                add_to_reactor(which, fd); 
                SERVER(GREEN "<add a socket to subepollfd>\n" NONE);
            }
        }
    }

    rela_svr.Shutdown();
	mess_svr.Shutdown();
	photo_svr.Shutdown();
    bus.ShmDetach();

	return 0;
}