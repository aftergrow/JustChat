/*************************************************************************
	> File Name: setter.cpp
	> Author: kwb
	> Mail: 
	> Created Time: Fri 29 Apr 2022 05:26:57 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
	int shm_id = shmget((key_t)8998, 10240, IPC_CREAT | 0666);
	if (shm_id < 0) {
		printf("shmget failed: %d\n", shm_id);
		return 0;
	}
	printf("shmget id = %d\n", shm_id);
	//shaddr的地址与程序有关。同样的程序每次执行，shmaddr的地址一般都不同 
	char* shmaddr = (char*)shmat(shm_id, NULL, 0); 
	if (*shmaddr < 0) {
		printf("shmat failed: %d\n", *shmaddr);
		return 0;
	}
	printf("shmaddr = %p\n", shmaddr);

	while (1) {
		scanf("%s", shmaddr);
		if (strcmp(shmaddr, "quit")==0) {
			break;
		}
	}
	shmdt(shmaddr);

	return 0;
}

