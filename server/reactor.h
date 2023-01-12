/*************************************************************************
	> File Name: reactor.h
	> Author: kwb
	> Mail: 
	> Created Time: Wed 31 Aug 2022 12:03:21 PM CST
 ************************************************************************/

#ifndef _REACTOR_H
#define _REACTOR_H

#define MAXEVENTS 10

int add_to_reactor(int epollfd, int fd);
void* sub_reactor(void *arg);

#endif
