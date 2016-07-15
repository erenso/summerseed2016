#ifndef GET_SEND_MES_H
#define GET_SEND_MES_H

#include <stdio.h> 
#include <string.h>    
#include <sys/socket.h>   
#include <arpa/inet.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MAXLEN 2000

int sendmes(char ipaddr[], int portno, char mes[], int opt);
int listenmes(int portno, int opt);

#endif
