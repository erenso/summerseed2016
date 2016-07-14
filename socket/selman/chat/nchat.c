#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include "include/workers.h"
#include "include/utils.h"
//#include "../ncclone/nc/include/nc.h"


struct listen_args {
  int port;
  int reply;
  int reply_port;
  int response_qid;
  int hosts_qid;
};

// http://stackoverflow.com/questions/6621785/posix-pthread-programming
void sigint(int signo) {
    (void)signo;
}


void *listen_requests(void *passed_arg){
  struct listen_args *args;
  args = (struct listen_args*)passed_arg;
  
  listen_port(args->port, args->response_qid, args->hosts_qid, args->reply, 0);
  return NULL;
}

void *listen_responses(void *passed_arg){
  struct listen_args *args;
  args = (struct listen_args*)passed_arg;
  
  listen_port(args->port, args->response_qid, args->hosts_qid, args->reply, args->reply_port);
  return NULL;
}

void *print_message_worker(void *passed_arg){
  int* qid = (int *)passed_arg;
  Response response_message;
  int response_length = sizeof(Response) - sizeof(int);
  while(1){
     msgrcv(*qid,&response_message,response_length,1, 0);
    // if( r != -1 ){   // in case of fails
      printf("got request/response from : %s \n", response_message.response_message);
    // }
    //printf("%d", r);
  }
  return NULL;
}

void *print_hosts_worker(void *passed_arg){
  int *qid = (int *)passed_arg;
  Host host_info;
  int host_info_length = sizeof(Host) - sizeof(int);
  while(1){
     msgrcv(*qid,&host_info,host_info_length,1, 0);
    // if( r != -1 ){   // in case of fails
      printf("got hostname : %s \n", host_info.IP);
    // }
    //printf("%d", r);
  }
  
  return NULL;
}

// TODO: Clean up main function.

int main(int argc, char const *argv[]) {
  sigset_t sigset, oldset;
  sigemptyset(&sigset);
  sigaddset(&sigset, SIGINT);
  pthread_sigmask(SIG_BLOCK, &sigset, &oldset);

  // Response message queue
  key_t msgkey;
  int response_qid;
  msgkey = ftok(".",1);
  response_qid = msgget(msgkey, IPC_CREAT | 0660);
  
  // Hosts message queue
  int hosts_qid;
  key_t other;
  other = ftok(".",2);
  hosts_qid = msgget(other, IPC_CREAT | 0660);


  pthread_t t1, t2, t3, t4;

  struct listen_args *listen_requests_args  = malloc(sizeof(struct listen_args));
  listen_requests_args->port = 10000;
  listen_requests_args->response_qid = response_qid;
  listen_requests_args->hosts_qid = hosts_qid;
  listen_requests_args->reply = 1;
  listen_requests_args->reply_port = 10001;
  
  struct listen_args *listen_responses_args  = malloc(sizeof(struct listen_args));
  listen_responses_args->port = 10001;
  listen_responses_args->response_qid = response_qid;
  listen_responses_args->hosts_qid = hosts_qid;
  listen_responses_args->reply = 0;


  
  
  pthread_create(&t3, NULL, print_hosts_worker, (void *)&hosts_qid);
  pthread_create(&t2, NULL, print_message_worker, (void *)&response_qid);
  pthread_create(&t1, NULL, listen_requests, (void *)listen_requests_args);
  pthread_create(&t4, NULL, listen_responses, (void *)listen_responses_args);

  
  struct sigaction s;
  s.sa_handler = sigint;
  sigemptyset(&s.sa_mask);
  s.sa_flags = 0;
  sigaction(SIGINT, &s, NULL);

  // Restore the old signal mask only for this thread.
  pthread_sigmask(SIG_SETMASK, &oldset, NULL);

  // Wait for SIGINT to arrive.
  pause();

  // Cancel both threads.
  pthread_cancel(t1);
  pthread_cancel(t2);
  pthread_cancel(t3);
  pthread_cancel(t4);



  pthread_join(t3, NULL);
  pthread_join(t2, NULL);
  pthread_join(t1, NULL);
  

  
  msgctl(response_qid, IPC_RMID, 0);
  msgctl(hosts_qid, IPC_RMID, 0);
  printf("%s\n", "cleaned up");
  return 0;
}
