#include "netcat.h"
#include <pthread.h>

// BEWARE, this file has threads

char ip[50] = "10.38.65.";	// first three numbers of the ip address

// this function is passed into pthread_create function in order to create a thread
// this has to be type of void* and its argument should be void* as well
void *sendRequest(void *i_ptr){
	int *i = (int*)i_ptr;	// cast i to int*
	if(!(*i >= 0 && *i <= 255)){
		return NULL;
	}
	char newip[50];			// holds new ip value
	sprintf(newip, "%s%d", ip, *i); // new ip in the form of ip.i, basically concats i to ip creating an ip address
	char message[MAX_PACKET_LENGTH];	// our message, which is "10.38.65.183,ali"
	strcpy(message, "10.38.65.183,ali");	// copy our message to the variable
	ncsend(newip, 10000, message);		// send our message
	
	return NULL;
}

int main(){
	int i = 0; 		// last digit of IP
	pthread_t pth;	// thread identifier
	
	while(i < 255){
		int err = pthread_create(&pth,NULL,sendRequest,(void*)&i);	// start creating some threads
		if(err == -1){	// if thread creation fails print error and exit
			perror("thread creation");
			exit(-1);
		}
		i++;
	}
	
	return 0;
}
