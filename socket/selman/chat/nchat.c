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
  int *test = (int *)passed_arg;
  //printf("test %d", *test);
  return NULL;
}


int main(int argc, char const *argv[]) {
  sigset_t sigset, oldset;
  sigemptyset(&sigset);
  sigaddset(&sigset, SIGINT);
  pthread_sigmask(SIG_BLOCK, &sigset, &oldset);
  
  
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
  
  if (pthread_create(&t1, NULL, listen_worker, (void *)listen_args) != 0) {
      printf("Uh-oh!\n");
      return -1;
  }
  

  if (pthread_create(&t2, NULL, print_message_worker, (void *)&response_qid) != 0) {
      printf("Uh-oh!\n");
      return -1;
  }

    
  
  struct sigaction s;
  s.sa_handler = sigint;
  sigemptyset(&s.sa_mask);
  s.sa_flags = 0;
  sigaction(SIGINT, &s, NULL);

  // Restore the old signal mask only for this thread.
  pthread_sigmask(SIG_SETMASK, &oldset, NULL);


  // Wait for SIGINT to arrive.
  pause();

  pthread_cancel(t1);
  pthread_cancel(t2);
  
  sigsuspend(&oldset);
  
  printf("%s\n", "before" );
  pthread_join(t2, NULL);
  pthread_join(t1, NULL);
  printf("%s\n", "after" );
  
  // cancel thread

  msgctl(response_qid, IPC_RMID, 0);
  return 0;
}
