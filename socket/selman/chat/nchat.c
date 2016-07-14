#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include "include/workers.h"
//#include "../ncclone/nc/include/nc.h"


struct listen_args {
  int port;
  char *response;
  int qid;
};

// http://stackoverflow.com/questions/6621785/posix-pthread-programming
void sigint(int signo) {
  puts("\nsignal arrived");
  exit(1);
  (void)signo;
}

void *listen_worker(void *passed_arg){
  struct listen_args *args;
  args = (struct listen_args*)passed_arg;
  
  listen_port(args->port, args->qid);
  return NULL;
}

void *print_message_worker(void *passed_arg){
  int* qid = (int *)passed_arg;
  Message response_message;
  int message_length = sizeof(Message)-sizeof(int);
  while(1){
    int r = (msgrcv(*qid,&response_message,message_length,1, IPC_NOWAIT));
    if( r != -1 ){
      printf("%s \n", response_message.response);
    }
    //printf("%d", r);
  }
  return NULL;
}


int main(int argc, char const *argv[]) {

  // Response message queue
  key_t msgkey;
  int response_qid;
  msgkey = ftok("./",'m');
  response_qid = msgget(msgkey, IPC_CREAT | 0660);


  pthread_t t1;
  pthread_t t2;
  struct listen_args *listen_args  = malloc(sizeof(struct listen_args));
  listen_args->port = 10000;
  listen_args->response = "";
  listen_args->qid = response_qid;
  
  pthread_create(&t1, NULL, listen_worker, (void *)listen_args);
  pthread_create(&t2, NULL, print_message_worker, (void *)&response_qid);

  printf("%s\n", "before" );
  pthread_join(t2, NULL);
  pthread_join(t1, NULL);
  printf("%s\n", "after" );
  

  
  msgctl(response_qid, IPC_RMID, 0);
  return 0;
}
