#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_PACKET_LENGTH 512

extern int sender(char* ip, int port, char* msg);

void* sendRequest(void* ip){
	char message[MAX_PACKET_LENGTH+1];
	char *ip2 = (char*)ip;
	sprintf(message, "172.16.5.140,ozgun");
	sender(ip2, 10000, message);
	return NULL;	
}

char ip[40]="172.16.5.";

int main(){
	int i = 0;
	pthread_t pth[256];
	char totalip[256][40];
	for(i = 0; i < 256; i++){
		sprintf(totalip[i], "%s%d", ip, i);
	}
	i = 0;
	while(i < 255){
		pthread_create(&pth[i],NULL,&sendRequest,(void*)&totalip[i]);
		usleep(300);
		i++;
	}
	for(i = 0; i < 255; i++) {
		pthread_join(pth[i], NULL);
	}
	return 0;
}
