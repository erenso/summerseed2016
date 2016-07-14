#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include "../sds/sds.h"

typedef struct response_buffer {
  int mtype;
  sds response_message;
//  int qid;
} Response;


typedef struct host_buffer {
  int mtype;
  sds nickname;
  sds IP;
} Host;
#endif
