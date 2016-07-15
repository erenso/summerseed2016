#include "netcat.h"
#include <pthread.h>

// BEWARE, this file has threads

char ip[50] = "172.16.5.";	// first three numbers of the ip address
char message[MAX_PACKET_LENGTH];

// this function is passed into pthread_create function in order to create a thread
// this has to be type of void* and its argument should be void* as well
void *send_msg(void *ip){
    char *ipp = (char*)ip;
    ncsend(ipp, 10002, message);		// send our message
    return NULL;
}

int main(){
    int i = 0; 		// last digit of IP
    pthread_t pth[256];	// thread identifier
    char ips[256][50];
    for(i = 0; i < 256; i++){
        //ips[i][0] = '\0';
        sprintf(ips[i], "%s%d", ip, i);
    }

    char messageContent[MAX_PACKET_LENGTH-3];
    fgets(messageContent, MAX_PACKET_LENGTH, stdin);
    sprintf(message, "ali,%s", messageContent);

    i = 0;
    while(i < 255){
        int err = pthread_create(&pth[i],NULL,send_msg,(void*)&ips[i]);	// start creating some threads
        usleep(300);
        if(err == -1){	// if thread creation fails print error and exit
            perror("thread creation");
            exit(-1);
        }
        i++;
    }

    for(i = 0; i < 256; i++) {
        pthread_join(pth[i], NULL);
    }
    return 0;
}