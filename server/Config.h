/*************************************************************************
	> File Name: Config.h
	> Author: kwb
	> Mail: 
	> Created Time: Tue 29 Mar 2022 09:59:16 PM CST
 ************************************************************************/

#ifndef _CONFIG_H
#define _CONFIG_H

#include "common/macro.h"
#include <cstring>

class Config {
    GETSETVAR(int, socket_port)
    GETSETSTR(256, socket_addr)
public:
    int ReadConfig();
};


#endif
