#include "../sds/sds.h"

typedef struct mymsgbuf
{
  int mtype;
  sds response;
  int qid;
} Message;
