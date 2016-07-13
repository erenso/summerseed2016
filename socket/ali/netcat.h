#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>

#define AZAMIUZUNLUK 1024

void nclisten(int port);
void ncsend(char *ip, int port, char *mesaj);
