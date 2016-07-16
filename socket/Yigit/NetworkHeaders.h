

#ifndef NetworkHeaders_h
#define NetworkHeaders_h

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


#define ADRSBK "Address_Book"
#define PRT_MSG 10002
#define PRT_RIS 10001
#define PRT_REQ 10000
#define MSG_LIMIT 2048
#define IP_LIMIT 20
#define MAX_MSG 2000
#define NICK_LIMIT 48
#define jiFIX 0
#define ABSIZE 500

char * getIP();
void fix_add();
int listen_nw(int port);
int send_MSG(int port, char * IP, const char * MSG, int timeoutSec);
void discover();
int exitCon(char * input);
void* listenMSG(void* input);
char * findIP(char * nick);
void* listenREQ(void* input);
void cpySTR(char * des, const char * sor);
int isSame(char * str1, char * str2);


#endif /* NetworkHeaders_h */
