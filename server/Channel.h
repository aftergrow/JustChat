/*************************************************************************
	> File Name: Channel.h
	> Author: kwb
	> Mail: 
	> Created Time: Sat 30 Apr 2022 08:58:50 PM CST
 ************************************************************************/

#ifndef _CHANNEL_H
#define _CHANNEL_H

#include "common/macro.h"
#include "BusBlock.h"

class Channel {
public:
	char* name;
	int* from;
	int* to;
	BusBlock* block;

};

#endif
