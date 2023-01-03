/*************************************************************************
	> File Name: getter.cpp
	> Author: kwb
	> Mail: 
	> Created Time: Fri 29 Apr 2022 06:11:27 PM CST
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
	char* shmaddr = (char*)shmat(shm_id, NULL, 0); 
	if (*shmaddr < 0) {
		printf("shmat failed: %d\n", *shmaddr);
		return 0;
	}
	printf("shmaddr = %p\n", shmaddr);

	while (1) {
		if (strcmp(shmaddr, "quit")==0) {
			break;
		}

		if (*shmaddr == 0) {
			//printf("null string\n"); //shmaddr用memset设置为0后，就会一直进入这个if里
			continue;
		}
		printf("get %s\n", shmaddr);
		memset(shmaddr, 0, 10240);
		sleep(1);
	}
	shmdt(shmaddr);

	return 0;
}