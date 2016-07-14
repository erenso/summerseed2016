#include "include/workers.h"


void listen_port(int port, int qid){
  int sockfd, newsockfd, portno;
  socklen_t clilen;
  struct sockaddr_in serv_addr, cli_addr;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0){
    error("ERROR opening socket");
    return;
  }
  
  bzero((char *)&serv_addr, sizeof(serv_addr));
  portno = port;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
    error("ERROR on binding");
    return;
  }
  listen(sockfd, 5);
  clilen = sizeof(cli_addr);
  while ((newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen))) {
    if (newsockfd < 0) {
      error("ERROR on accept");
      return;
    }
    // Just in case
    //int org_newsocketfd = dup(newsockfd);

    // Treat package as a file, 'cause why not?
    FILE *socketf = fdopen(newsockfd, "r");
    char ch;
    int n = 0;

    /*
     * Messing with char * and <string.h> makes me wanna
     * LIE DOWN
     * TRY NOT TO CRY
     * CRY A LOT
     */
    sds message = sdsempty();

    while ('\t' != (ch = fgetc(socketf))) {
      // what if '\t' does not exist?
      message = sdscat(message, &ch);
      n++;
    }

    if (n < 0) {
      error("ERROR reading from socket");
      return;
    }

    Message response_message;
    int message_length = sizeof(Message)-sizeof(int);
    response_message.qid = qid;
    response_message.mtype = 1;
    response_message.response = sdsempty();
    response_message.response = sdscpy(response_message.response, message);
    printf("%s", message);
    if(msgsnd(response_message.qid, &response_message, message_length, IPC_NOWAIT) != 0){
      perror("failed to send");
    }
    //strcpy(response, message);

    //
    // n = write(org_newsocketfd, "I got your message", 18);
    //
    // if (n < 0) {
    //   error("ERROR writing to socket");
    //   return;
    // }

    //sdsfree(message);
    fclose(socketf);
    close(newsockfd);
  }
  close(sockfd);
  return;
}

void response_consumer(int qid){
  Message received;
  printf("%s\n","outside1" );
  while(1){
    if(msgrcv(qid, &received, sizeof(Message)-sizeof(int), 1,1) != -1){
      
      if(received.mtype == 1){
        printf("message : %s", received.response);
      }
    }
  }
}
void error(const char *msg) {
  perror(msg);
}
