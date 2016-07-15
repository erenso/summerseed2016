#ifndef NC_H
#define NC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include "../../sds/sds.h"


int listen_port(int, char*);
int write_to(const char *, int);
void error(const char*);

#endif
