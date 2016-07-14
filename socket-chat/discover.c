#include "commons.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#define NUM_IP 254

extern void send_msg(const char* ip, int port, const char* msg);

void* sendRequest(void* arg){
	
	char ip[IP_MAX]="172.16.5.";
	sprintf(ip+strlen(ip), "%d", *((int*)arg));
	send_msg(ip, REQ_PORT, RESPONSE);
	
//    	fprintf(stderr, "%s\n",ip);
	
// 	pthread_detach(pthread_self());
	return NULL;	
}

void discover(){
	
	int i, arr[NUM_IP];
	pthread_t threads[NUM_IP];
	fprintf(stderr, "discover start\n");
// 	pthread_attr_t attr;
// 	
// 	pthread_attr_init(&attr);
// 	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
// 	
	for(i=0; i<NUM_IP; ++i){
		
		arr[i] = i+1; 
		pthread_create(threads+i, NULL, sendRequest, (void*)(arr+i));
	}
/*	TODO böyle çok bekliyo. detachable?*/
 	for(i=0; i<NUM_IP; ++i)
 		
 		pthread_join(threads[i], NULL);	
	
	fprintf(stderr, "discover done\n");
}
