/*************************************************************************
	> File Name: Config.cpp
	> Author: kwb
	> Mail: 
	> Created Time: Tue 29 Mar 2022 10:01:09 PM CST
 ************************************************************************/

#include "Config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Config::ReadConfig() {
    FILE* f = fopen("config.ini", "r");
	if (f == NULL) {
		return -1;
	}
	while(1) {
		char config_line[256];
		if (fscanf(f, "%s", config_line) == EOF) {
			break;
		}
		char config_addr[256];
		if (strstr(config_line, "socket_addr=") != NULL) {
			sscanf(config_line, "socket_addr=%s", config_addr);
			printf("addr:%s\n", config_addr);
			set_socket_addr(config_addr);
		}
		int config_port;
		if (strstr(config_line, "socket_port=") != NULL) {
			sscanf(config_line, "socket_port=%d", &config_port);
			printf("port:%d\n", config_port);
			set_socket_port(config_port);
		}
	}
	fclose(f);
	return 0;
}
