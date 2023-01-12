/*************************************************************************
	> File Name: BusManager.cpp
	> Author: kwb
	> Mail: 
	> Created Time: Sat 30 Apr 2022 10:00:08 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
//#include <sys/time.h>
#include "BusManager.h"

int debug=1;
#define SIZE_BUS_FLAG 1
#define SIZE_CHANNEL sizeof(Channel)
#define SIZE_ALL_CHANNEL (4*sizeof(Channel))
#define SIZE_CHANNEL_NAME 256
#define SIZE_CHANNEL_FROM sizeof(int)
#define SIZE_CHANNEL_TO sizeof(int)
#define SIZE_BLOCK sizeof(BusBlock)
#define SIZE_BLOCK_NEXT sizeof(BusBlock*)
#define SIZE_BLOCK_USED 1
#define SIZE_BLOCK_SIZE sizeof(int)
#define SIZE_BLOCK_DATA 10240

#define OFFSET_BUS_FLAG 0
#define OFFSET_CHANNEL 0
#define OFFSET_CHANNEL_NAME OFFSET_CHANNEL
#define OFFSET_CHANNEL_FROM OFFSET_CHANNEL_NAME+SIZE_CHANNEL_NAME
#define OFFSET_CHANNEL_TO OFFSET_CHANNEL_FROM+SIZE_CHANNEL_FROM
#define OFFSET_CHANNEL_BLOCK OFFSET_CHANNEL_TO+SIZE_CHANNEL_TO
#define OFFSET_CHANNEL_BLOCK_USED OFFSET_CHANNEL_BLOCK+SIZE_BLOCK
#define OFFSET_CHANNEL_BLOCK_NEXT OFFSET_CHANNEL_BLOCK_USED+SIZE_BLOCK_USED
#define OFFSET_CHANNEL_BLOCK_SIZE OFFSET_CHANNEL_BLOCK_NEXT+SIZE_BLOCK_NEXT
#define OFFSET_CHANNEL_BLOCK_DATA OFFSET_CHANNEL_BLOCK_SIZE+SIZE_BLOCK_SIZE

#define UNIT_SIZE (OFFSET_CHANNEL_BLOCK_DATA+SIZE_BLOCK_DATA)

//debug宏
#define BUS_CLEAR_F

/* 对 Init() 函数的分析：
 * 首先，./server_ssp 和 ./user_svr 11、./user_svr 12 通过 shmat()获取到的 shmp 不同，它们分别是：
 * 0x7f33db0d7000、0x7ff9d1a82000、0x7f1797b1d000，它们分别是 ./server_ssp 和 ./user_svr 11、./user_svr 12 这三个进程
 * 中的某一块内存地址，用于绑定共享内存。如果 ./server_ssp 更改了 shmp 里存放的值，那么对应的其他2个的值都会改变
 * 接下来分析Init()函数在三个进程中实现的内容：
 * 1.运行 ./server_ssp:
 * 		BusInit(); 这个函数把 Channel 里每一个数据存放的地址分配好。为什么 Channel 里的存放的都是指针类型？因为如果存放的是值，
 * 				   如果我们想要得到这个值的地址，就获取不到了。
 * 		ChannelInit(); Channel里的地址分配好之后，就对值进行初始化。
 * 2.运行 ./user_svr 11 和 ./user_svr 12
 * 		./server_ssp 把地址分配好，也把值赋好了。那么 ./user_svr 11 和 ./user_svr 12 要读写 Channel 里的内容要怎么做？
 * 		首先通过 shmat，./user_svr 11 和 ./user_svr 12 分别得到了两个地址不同的 shmp。要读写值时，只需把 shmp 加上对应值的地址
 * 		偏移量即可，也就是 MutableChannelName(int i)、MutableChannelFrom(int i) 等函数。
 */

int BusManager::Init() {
	/* rela、photo和mess 的svr整合为一个svr，标记为21
	 * usr_svr 有2个，分别标记为 11，12  
	 */
	//shm Init
	printf("----  Init Shm  ----\n");

	shm_id = shmget((key_t)9998, 10240*8, IPC_CREAT | 0666);
	if (shm_id < 0) {
		printf("shmget failed: %d\n", shm_id);
		return -1;
	}
	printf("---- shm_id: %d ----\n", shm_id);

	/* shmat:
	 * 连接共享内存标识符为shmid的共享内存，连接成功后把共享内存区对象映射到调用进程的地址空间，
	 * 随后可像本地空间一样访问
	 * 
	 * 共享内存映射到了shmp ，bus.Init()和bus2.Init()之后，它们的 shmp 是一样的(注)
	 * 但它们都指向了同一块共享内存 	 
	 */
	shmp = (char*)shmat(shm_id, NULL, 0);
	if (*shmp < 0) {
		printf("shmat failed: %d\n", *shmp);
		return -2;
	}
	printf("---- shm_addr: %p ----\n", shmp);
	if (*shmp == 'Y') {
		//如果共享内存已经被初始化了，则执行这一步
		//把共享内存映射到 *shmp 地址空间，并且不能调用 ChannelInit()
		//否则共享内存原本的值都被初始化了
		//BusInit(); 
		//printf("shmp == yes\n");
	} else {
		*shmp = 'Y'; //这步要先执行
		//构造Bus和Channel的指向关系
		BusInit(); //按照之前的结构映射到共享内存
		ChannelInit(); //给Channel里面的值初始化
		//printf("shmp == no\n");
	}
	printf("----  Init Finish!  ----\n");

	pthread_mutex_init(&mutex, NULL);
	
	return 0;
}

int BusManager::BusInit() {
	printf("----  Init Bus  ----\n");
	char *curp = shmp + 1; //[0] -- 'Y'
		
	int size_channel = sizeof(Channel);
	int size_block = sizeof(BusBlock);
	printf("channel(%d) block(%d)\n", size_channel, size_block);

	if(debug)printf("cur_addr:%p\n",curp);
	channel_[0] = (Channel*)curp;
	curp += size_channel;
	if(debug)printf("channel_[0]:%p\n",channel_[0]);

	if(debug)printf("cur_addr:%p\n",curp);
	channel_[1] = (Channel*)curp;
	curp += size_channel;
	if(debug)printf("channel_[1]:%p\n",channel_[1]);

	if(debug)printf("cur_addr:%p\n",curp);
	channel_[2] = (Channel*)curp;
	curp += size_channel;
	if(debug)printf("channel_[2]:%p\n",channel_[2]);

	if(debug)printf("cur_addr:%p\n",curp);
	channel_[3] = (Channel*)curp;
	curp += size_channel;
	if(debug)printf("channel_[3]:%p\n",channel_[3]);

	if(debug)printf("cur_addr:%p\n",curp);
	channel_[0]->name = curp;
	curp += 256;
	if(debug)printf("channel_[0]->name:%p\n",channel_[0]->name);

	if(debug)printf("cur_addr:%p\n",curp);
	channel_[0]->from = (int*)curp;
	//在不同的系统上，int 的大小不同，可能为 32、64 甚至是 128 位
	curp += sizeof(int);
	if(debug)printf("channel_[0]->from:%p\n",channel_[0]->from);

	if(debug)printf("cur_addr:%p\n",curp);
	channel_[0]->to = (int*)curp;
	curp += sizeof(int);
	if(debug)printf("channel_[0]->to:%p\n",channel_[0]->to);

	if(debug)printf("cur_addr:%p\n",curp);
	channel_[0]->block = (BusBlock*)curp;
	curp += sizeof(BusBlock); // Not Star!!!
	if(debug)printf("channel_[0]->block:%p\n",channel_[0]->block);

	if(debug)printf("cur_addr:%p\n",curp);
	channel_[0]->block->used = curp;
	/* 从汇编的角度，会变成INC; cup++ 则是放到寄存器里 +1，所以会多一条指令 
	 * 但现阶段会被编译器优化啊，所 ++i 和 i++ 是一样的
	 */
	curp++;
	if(debug)printf("channel_[0]->block->used:%p\n",channel_[0]->block->used);

	if(debug)printf("cur_addr:%p\n",curp);
	channel_[0]->block->next = (BusBlock*)curp;
	curp += sizeof(BusBlock*); //因为这里分配的就是一个指针，所以不需要分配 sizeof(BusBlock)
	if(debug)printf("channel_[0]->block->next:%p\n",channel_[0]->block->next);

	if(debug)printf("cur_addr:%p\n",curp);
	channel_[0]->block->size = (int*)curp;
	curp += sizeof(int);
	if(debug)printf("channel_[0]->block->size:%p\n",channel_[0]->block->size);

	if(debug)printf("cur_addr:%p\n",curp);
	channel_[0]->block->data = curp;
	curp += 10240;
	if(debug)printf("channel_[0]->block->data:%p\n",channel_[0]->block->data);

	for (int i = 1; i < 4; i++) {
		if(debug)printf("cur_addr:%p\n",curp);
		channel_[i]->name = curp;
		curp += 256;
		if(debug)printf("channel_[%d]->name:%p\n",i,channel_[i]->name);

		if(debug)printf("cur_addr:%p\n",curp);
		channel_[i]->from = (int*)curp;
		curp += sizeof(int);
		if(debug)printf("channel_[%d]->from:%p\n",i,channel_[i]->from);

		if(debug)printf("cur_addr:%p\n",curp);
		channel_[i]->to = (int*)curp;
		curp += sizeof(int);
		if(debug)printf("channel_[%d]->to:%p\n",i,channel_[i]->to);

		if(debug)printf("cur_addr:%p\n",curp);
		channel_[i]->block = (BusBlock*)curp;
		curp += sizeof(BusBlock); // Not Star!!!
		if(debug)printf("channel_[%d]->block:%p\n",i,channel_[i]->block);

		if(debug)printf("cur_addr:%p\n",curp);
		channel_[i]->block->used = curp;
		curp++;
		if(debug)printf("channel_[%d]->block->used:%p\n",i,channel_[i]->block->used);

		if(debug)printf("cur_addr:%p\n",curp);
		channel_[i]->block->next = (BusBlock*)curp;
		curp += sizeof(BusBlock*); 
		if(debug)printf("channel_[%d]->block->next:%p\n",i,channel_[i]->block->next);

		if(debug)printf("cur_addr:%p\n",curp);
		channel_[i]->block->size = (int*)curp;
		curp += sizeof(int);
		if(debug)printf("channel_[%d]->block->size:%p\n",i,channel_[i]->block->size);

		if(debug)printf("cur_addr:%p\n",curp);
		channel_[i]->block->data = curp;
		curp += 10240;
		if(debug)printf("channel_[%d]->block->data:%p\n",i,channel_[i]->block->data);
	}
	return 0;
}

int BusManager::ChannelInit() {
	/* strncpy(channel_[0]->name, "User1 -> Server", 15);
	*(channel_[0]->from) = 11;
	*(channel_[0]->to) = 21;
	*(channel_[0]->block->used) = 'N';
	*(channel_[0]->block->size) = 0;
	memset(channel_[0]->block->data, 0, 10240);

	strncpy(channel_[1]->name, "User2 -> Server", 15);
	*(channel_[1]->from) = 12;
	*(channel_[1]->to) = 21;
	*(channel_[1]->block->used) = 'N';
	*(channel_[1]->block->size) = 0;
	memset(channel_[1]->block->data, 0, 10240);

	strncpy(channel_[2]->name, "Server -> User1", 15);
	*(channel_[2]->from) = 21;
	*(channel_[2]->to) = 11;
	*(channel_[2]->block->used) = 'N';
	*(channel_[2]->block->size) = 0;
	memset(channel_[2]->block->data, 0, 10240);

	strncpy(channel_[3]->name, "Server -> User2", 15);
	*(channel_[3]->from) = 21;
	*(channel_[3]->to) = 12;
	*(channel_[3]->block->used) = 'N';
	*(channel_[3]->block->size) = 0;
	memset(channel_[3]->block->data, 0, 10240); */

	printf("----  Channel Init ----\n");

	for(int i=0;i<4;i++){
		memset(MutableChannelName(i),0,SIZE_CHANNEL_NAME);
		*MutableChannelBlockUsed(i)='N';
		*MutableChannelBlockSize(i)=0;
		memset(MutableChannelBlockData(i),0,SIZE_BLOCK_DATA);
		
	}
	strncpy(MutableChannelName(0),"Usr1->Server",12);
	*MutableChannelFrom(0)=11;
	*MutableChannelTo(0)=21;

	strncpy(MutableChannelName(1),"Usr2->Server",12);
	*MutableChannelFrom(1)=12;
	*MutableChannelTo(1)=21;

	strncpy(MutableChannelName(2),"Server->Usr1",12);
	*MutableChannelFrom(2)=21;
	*MutableChannelTo(2)=11;

	strncpy(MutableChannelName(3),"Server->Usr2",12);
	*MutableChannelFrom(3)=21;
	*MutableChannelTo(3)=12;

	return 0;
}

int BusManager::ShmDetach() {
	int ret = shmdt(shmp); //解绑共享内存
	if (ret < 0) {
		printf("shmdt failed: %d\n", ret);
	}
	return ret;
}

int BusManager::ShmRemove() {
	int ret = shmctl(shm_id, IPC_RMID, 0); //删除共享内存
	if (ret < 0) {
		printf("shmctl failed: %d\n", ret);
	}
	return ret;
}


Channel* BusManager::GetChannel(int from, int to) {
	for (int i = 0; i < 4; i++) {
		//printf("from: %d\n", *(channel_[i]->from));
		if ((*MutableChannelFrom(i) == from) && (*MutableChannelTo(i) == to)) {	
			int offset_in = OFFSET_CHANNEL+SIZE_BUS_FLAG;
			int offset_out = i*(SIZE_CHANNEL);		
			return (Channel*)(shmp+offset_in+offset_out);
		}
	}
	return NULL;
}

int BusManager::GetChannelIndex(int from,int to) {
	for(int i=0;i<4;i++){
		if(*MutableChannelTo(i)==to){
			if(*MutableChannelFrom(i)==from){
				return i;
			}
		}
	}
	return -1;
}

char* BusManager::GetChannelName(int from,int to) {
	int idx=GetChannelIndex(from,to);
	if(idx!=-1){
		return MutableChannelName(idx);
	}
	return NULL;	
}

int BusManager::ChannelShow() {
	/* for(int i=0;i<4;i++){
		printf("Channel[%d] Name: %s\n",i,channel_[i]->name);
		printf("Channel[%d] From: %d\n",i,*(channel_[i]->from));
		printf("Channel[%d] To  : %d\n",i,*(channel_[i]->to));
		printf("Channel[%d] Used: %c\n",i,*(channel_[i]->block->used));
		printf("Channel[%d] Size: %d\n",i,*(channel_[i]->block->size));
		printf("Channel[%d] Data: %s\n",i,channel_[i]->block->data);
	} */
	printf("----  Channel Display  ----\n");
	for(int i=0;i<4;i++){
		printf("Channel[%d] Name: %s\n",i,MutableChannelName(i));
		printf("Channel[%d] From: %d\n",i,*MutableChannelFrom(i));
		printf("Channel[%d] To  : %d\n",i,*MutableChannelTo(i));
		printf("Channel[%d] Used: %c\n",i,*MutableChannelBlockUsed(i));
		printf("Channel[%d] Size: %d\n",i,*MutableChannelBlockSize(i));
		printf("Channel[%d] Data: %s\n",i,MutableChannelBlockData(i));
	}
	return 0;
}

int BusManager::ChannelTestShow() {
	printf("Channel[0] Name: %p\n", channel_[0]->name);
	printf("Channel[0] From: %p\n", channel_[0]->from);
	/* for(int i=0;i<4;i++){
		printf("Channel[%d] Name: %p\n",i,channel_[i]->name);
		printf("Channel[%d] From: %p\n",i,*(channel_[i]->from));
		printf("Channel[%d] To  : %p\n",i,*(channel_[i]->to));
		printf("Channel[%d] Used: %p\n",i,*(channel_[i]->block->used));
		printf("Channel[%d] Size: %p\n",i,*(channel_[i]->block->size));
		printf("Channel[%d] Data: %p\n",i,channel_[i]->block->data);
	} */
	return 0;
}

//检查这四个通道是否有数据
int BusManager::CheckRecv(int target_id) {
	for(int i=0;i<4;i++){
		if(*MutableChannelTo(i)==target_id){
			if(*MutableChannelBlockUsed(i)=='Y'){
				printf("----[debg]channel %s recv %d bytes.\n",MutableChannelName(i),*MutableChannelBlockSize(i));
				return *MutableChannelFrom(i);			
			}
		}
	}
	return -1;

	/* //printf("channel_[0]->block->used: %c\n", *(channel_[0]->block->used));
	for (int i = 0; i < 4; i++) {
		if (*(channel_[i]->to) == target_id) {
			if (*(channel_[i]->block->used) == 'Y') {
				//printf("channel_[%d]->block->used: %c\n", i, *(channel_[i]->block->used));
				return *(channel_[i]->from);
			}
		}
	}
	return -1; */
}

int BusManager::RecvSize(int from, int to) {
	int idx=GetChannelIndex(from,to);
	if(idx!=-1){
		return *MutableChannelBlockSize(idx);
	}
	return 0;
}

char* BusManager::Recv(int from, int to) {
	int idx=GetChannelIndex(from,to);
	if(idx!=-1){
		if(*MutableChannelBlockUsed(idx)=='Y'){
			*MutableChannelBlockUsed(idx)='N';
			return MutableChannelBlockData(idx);
		}
	}
	return NULL;
}

int BusManager::Send(int from, int to, char* data, int size) {
	pthread_mutex_lock(&mutex);
	int idx=GetChannelIndex(from,to);
	if(idx==-1){
		printf("----\033[31m[erro]Channel(%d,%d) Not Exist\033[0m\n",from,to);
		pthread_mutex_unlock(&mutex);
		return -2;
	}
	char* p_ch_used=MutableChannelBlockUsed(idx); //获取存储Used的地址
	int* p_ch_size=MutableChannelBlockSize(idx);

	printf("BlockUsed: %c\n", *p_ch_used);
	printf("BlockSize: %d\n", *p_ch_size);
	if(*p_ch_used!='N'){		
		printf("----[warn]Channel(%s) Is Busy\n",MutableChannelName(idx));
		pthread_mutex_unlock(&mutex);
		return -3;
	}
	if(idx!=-1&&*p_ch_used=='N'){
		strncpy(MutableChannelBlockData(idx),data,size);
		*p_ch_size=size;
		*p_ch_used='Y';
		pthread_mutex_unlock(&mutex);
		return 0;
	}
	pthread_mutex_unlock(&mutex);
	return -1;
}

int BusManager::Clear(int from, int to) {
	pthread_mutex_lock(&mutex);
	int idx=GetChannelIndex(from,to);
	if(idx!=-1){
		int size=*MutableChannelBlockSize(idx);
		*MutableChannelBlockUsed(idx)='N';
		*MutableChannelBlockSize(idx)=0;
		memset(MutableChannelBlockData(idx),0,size);
	}

	#ifdef BUS_CLEAR_F
	printf("from(%d) to(%d) idx(%d) cleard!\n", from, to, idx);
	if(idx == 1) {
		char *p_block_used = MutableChannelBlockUsed(idx);
		int *p_block_size = MutableChannelBlockSize(idx);
		char *p_block_data = MutableChannelBlockData(idx);
		printf("BlockUsed: %c, BlockSize: %d, BlockData: %s\n", *p_block_used, *p_block_size, p_block_data);
	}
	#endif

	pthread_mutex_unlock(&mutex);
	return 0;
}

int BusManager::ChannelsClear() {
	for(int i=0;i<4;i++){
		int size=*MutableChannelBlockSize(i);
		*MutableChannelBlockUsed(i)='N';
		*MutableChannelBlockSize(i)=0;
		memset(MutableChannelBlockData(i),0,size);
	}
	return 0;
}

char* BusManager::MutableChannelName(int i){
	int offset_in=OFFSET_CHANNEL_NAME;
	int offset_out=i*UNIT_SIZE;
	return (shmp+offset_in+offset_out+SIZE_BUS_FLAG+SIZE_ALL_CHANNEL);
}

int* BusManager::MutableChannelFrom(int i){
	int offset_in=OFFSET_CHANNEL_FROM;
	int offset_out=i*UNIT_SIZE;
	return (int*)(shmp+offset_in+offset_out+SIZE_BUS_FLAG+SIZE_ALL_CHANNEL);
}

int* BusManager::MutableChannelTo(int i){
	int offset_in=OFFSET_CHANNEL_TO;
	int offset_out=i*UNIT_SIZE;
	return (int*)(shmp+offset_in+offset_out+SIZE_BUS_FLAG+SIZE_ALL_CHANNEL);
}

int BusManager::MutableChannelBlock(int i){
	int offset_in=OFFSET_CHANNEL_BLOCK;
	int offset_out=i*UNIT_SIZE;
	return *((int*)shmp+offset_in+offset_out+SIZE_BUS_FLAG+SIZE_ALL_CHANNEL);
}

BusBlock* BusManager::MutableChannelBlockNext(int i){
	int offset_in=OFFSET_CHANNEL_BLOCK_NEXT;
	int offset_out=i*UNIT_SIZE;
	return (BusBlock*)(shmp+offset_in+offset_out+SIZE_BUS_FLAG+SIZE_ALL_CHANNEL);
}

char* BusManager::MutableChannelBlockUsed(int i){
	int offset_in=OFFSET_CHANNEL_BLOCK_USED;
	int offset_out=i*UNIT_SIZE;
	return (char*)(shmp+offset_in+offset_out+SIZE_BUS_FLAG+SIZE_ALL_CHANNEL);
}

int* BusManager::MutableChannelBlockSize(int i){
	int offset_in=OFFSET_CHANNEL_BLOCK_SIZE;
	int offset_out=i*UNIT_SIZE;
	return (int*)(shmp+offset_in+offset_out+SIZE_BUS_FLAG+SIZE_ALL_CHANNEL);
}

char* BusManager::MutableChannelBlockData(int i){
	int offset_in=OFFSET_CHANNEL_BLOCK_DATA;
	int offset_out=i*UNIT_SIZE;
	return (shmp+offset_in+offset_out+SIZE_BUS_FLAG+SIZE_ALL_CHANNEL);
}

