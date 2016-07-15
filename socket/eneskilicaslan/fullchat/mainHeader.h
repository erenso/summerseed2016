//
// Created by parallels on 7/14/16.
//

#ifndef CHAT_MAINHEADER_H
#define CHAT_MAINHEADER_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <wait.h>
#include <pthread.h>
#include "discovery.h"
#include "listenRequest.h"
#include "listenResponce.h"


#define MESSAGE "172.16.5.244,enes\0"
#define MESSAGE_LEN 18
#define PORT0    "10000"
#define PORT1    "10001"
#define PORT2    "10002"

#define FILE_NAME "addressBook.txt"

#define BACKLOG 10     // how many pending connections queue will hold


//for test
#define LAN_IP  "172.16.5."
#define LAN_IP_SIZE 14

void sigchld_handler(int s);
void *get_in_addr(struct sockaddr *sa);


int listenMessage();
void * listenMessageThread( void *ptr );
int responceMessage();
void * listenResponceThread( void *ptr );
void * listenMessageThread( void *ptr );

#endif //CHAT_MAINHEADER_H
