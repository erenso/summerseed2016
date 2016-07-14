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

struct packet {
    char area1[50];
    char area2[MAX_PACKET_LENGTH - 20];
};

int nclisten(int port, int sendResponse);
int ncsend(char *ip, int port, char *mesaj);
int isValidIpAddress(char *ipAddress);
struct packet parsePacket(int packetType, char *packet);
#endif /* NETCAT_H */
