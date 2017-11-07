#include <pthread.h>
#include "dn_queue.h"
#include <WinSock2.h>
#include <Windows.h>

#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

char *obj_to_json() {}

void create_json(dn_object_t *o, char *buffer, int size);

void * collect_in_thread(void *p) {

	/* fuck me */
    SOCKET socketC;

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

    struct sockaddr_in serverInfo;
    int len = sizeof(serverInfo);

    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port = htons(1234);
    //serverInfo.sin_addr.s_addr = inet_addr("127.0.0.1");
    //serverInfo.sin_addr.s_addr = inet_addr("10.0.4.21");
	inet_pton(AF_INET, "10.0.4.21", &(serverInfo.sin_addr));

    socketC = socket(AF_INET,SOCK_DGRAM,0);

    while (1) {
	    char buffer[1024];
        dn_object_t *o;

	    ZeroMemory(buffer, sizeof(buffer));

		// Read from queue
		while (!dn_queue_empty()) {
			dn_object_t *o = dn_pop();
			create_json(o, buffer, sizeof(buffer));
		}
        //strcpy(buffer, "{ msg : \"hello world\" }");

	    //sendto(socketC, buffer, sizeof(buffer), 0, (sockaddr*)&serverInfo, len);
		sendto(socketC, buffer, strlen(buffer), 0, &serverInfo, len);
        // sleep(1);
    }
    closesocket(socketC);
}

void create_json(dn_object_t *o, char *buffer, int size) {

	char *res = "[{ \"name\": \"%s\", \"prob\": %3.2f, \"ix\": %d, \"iy\": %d,\"x\": %d, \"y\": %d, \"width\": %d, \"height\": %d, \"color\": \"%2.2X%2.2X%2.2X%2.2XFF\" }]";
	sprintf(buffer, res, 
		o->name,
		o->prob,
		o->x_size,
		o->y_size,
		o->x_box,
		o->y_box,
		o->w_box,
		o->h_box,
		o->box_red,
		o->box_green,
		o->box_blue);
}
