#ifndef NETCAT_H
#define NETCAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_PACKET_LENGTH 1024

int netlisten(int port, int sendResponse, int whatToListen);
int netsend(char *ip, int port, char *mesaj);
int isValidIpAddress(char *ipAddress);
#endif /* NETCAT_H */
