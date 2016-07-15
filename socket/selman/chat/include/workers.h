#ifndef WORKERS_H
#define WORKERS_H

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdbool.h>
#include "../sds/sds.h"
#include "utils.h"
#include "message_queue.h"

void listen_port(int, int, int, int, int);
void send_response(sds, int, sds);
void error(const char*);

#endif
