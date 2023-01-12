/*************************************************************************
	> File Name: BusBlock.h
	> Author: kwb
	> Mail: 
	> Created Time: Sat 30 Apr 2022 09:06:49 PM CST
 ************************************************************************/

#ifndef _BUSBLOCK_H
#define _BUSBLOCK_H

class BusBlock {
//要全部声明成指针
public:
	//数据在赋值置为0，赋值完成置为1.
	//因为在赋值的过程中，可能数据很大，分了好几次进行赋值
	char* used; //1表示有数据，0表示没有数据
	BusBlock *next;
	int* size; //读多少数据,并非一定是10240
	char* data; //存放共享内存
};

#endif
