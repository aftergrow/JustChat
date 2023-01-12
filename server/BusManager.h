/*************************************************************************
	> File Name: BusManager.h
	> Author: kwb
	> Mail: 
	> Created Time: Sat 30 Apr 2022 01:21:32 PM CST
 ************************************************************************/

#ifndef _BUSMANAGER_H
#define _BUSMANAGER_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include "Channel.h"

class BusManager {
private:
    int shm_id;
    char* shmp;
    //将要分配的指针，不再是已分配的内存
    Channel* channel_[4];

private:
    pthread_mutex_t mutex;

public:
    char send_buffer[10240]; //不在共享内存，只是作为临时存储
public:
    int Init();
    int BusInit();
    int ChannelInit();
    int ShmDetach();
    int ShmRemove();

    Channel* GetChannel(int from, int to);
    int GetChannelIndex(int from,int to);
    char* GetChannelName(int from,int to);
    int ChannelShow();
    int ChannelTestShow();
    int CheckRecv(int target_id);
    int RecvSize(int from, int to);
    char* Recv(int from, int to);
    int Send(int from, int to, char* data, int size);
    int Clear(int from, int to);
    int ChannelsClear();

	char* MutableChannelName(int i);
	int* MutableChannelFrom(int i);
	int* MutableChannelTo(int i);
	int MutableChannelBlock(int i);
	BusBlock* MutableChannelBlockNext(int i);
	char* MutableChannelBlockUsed(int i);
	int* MutableChannelBlockSize(int i);
	char* MutableChannelBlockData(int i);     

    

};


#endif
