/*************************************************************************
	> File Name: bus_test.cpp
	> Author: kwb
	> Mail: 
	> Created Time: Tue 03 May 2022 07:47:39 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include "BusManager.h"

BusManager bus, bus2;

int main() {
	bus.Init();
	/* printf("bus addr:\n");
	bus.ChannelTestShow(); */
	bus2.Init();
	/* printf("bus2 addr:\n");
	bus2.ChannelTestShow(); */
	
	int from, to;
	char message[256];
	int bus_on = 1;

	do {
		scanf("%d %d %s", &from, &to, message);
		if (strcmp(message, "quit") == 0) {
			bus_on = 0;
		}
		bus.Send(from, to, message, strlen(message));

		int ret11 = bus2.CheckRecv(11);
		int ret12 = bus2.CheckRecv(12);
		int ret21 = bus2.CheckRecv(21);
		bus2.ChannelShow();

		if (ret11) {
			//printf("from %d to 11\n", ret11);
			printf("[user1 recv]: %s\n", bus2.Recv(ret11, 11));
			bus2.Clear(ret11, 11);
		}
		if (ret12) {
			//printf("from %d to 12\n", ret12);
			printf("[user2 recv]: %s\n", bus2.Recv(ret12, 12));
			bus2.Clear(ret12, 12);
		}
		if (ret21) {
			//printf("from %d to 21\n", ret21);
			printf("[server recv]: %s\n", bus2.Recv(ret21, 21));
			bus2.Clear(ret21, 21);
		}
	} while(bus_on);
	bus2.ShmDetach();
	bus.ShmDetach();
	bus.ShmRemove();

	return 0;
}

