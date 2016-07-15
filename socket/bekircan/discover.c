#include "commons.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#define NUM_IP 254

extern void send_msg(const char* ip, int port, const char* msg);
extern volatile sig_atomic_t interrupt;
extern const char*  RESPONSE;
extern void LLclear();
extern void LLfixDuplicateIPs();

extern pthread_mutex_t ll_mutex;

void* sendRequest(void* arg){
	
	char ip[IP_MAX]="172.16.5.";
	sprintf(ip+strlen(ip), "%d", *((int*)arg));
	send_msg(ip, REQ_PORT, RESPONSE);
	
	return NULL;	
}

void discover(){
	
	int i, j, arr[NUM_IP];
	pthread_t threads[NUM_IP];

	fprintf(stderr, "discover start\n");
	
	pthread_mutex_lock(&ll_mutex);
	LLclear();
	pthread_mutex_unlock(&ll_mutex);
	
	for(i=0; i<NUM_IP && !interrupt; ++i){
		
		arr[i] = i+1; 
		pthread_create(threads+i, NULL, sendRequest, (void*)(arr+i));
	}

 	for(j=0; j<i; ++j)
 		
 		pthread_join(threads[j], NULL);	

	pthread_mutex_lock(&ll_mutex);
	LLfixDuplicateIPs();
	pthread_mutex_unlock(&ll_mutex);
	
	fprintf(stderr, "discover done\n");
}
