#include "include/workers.h"


void listen_port(int port, int response_qid, int hosts_qid, int reply, int reply_port){
  int sockfd, newsockfd, portno;
  socklen_t clilen;
  struct sockaddr_in serv_addr, cli_addr;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0){
    error("ERROR opening socket");
    return;
  }
  int option = 1;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
  
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
    int screwed = 0;
    while ('\t' != (ch = fgetc(socketf))) {
      // what if '\t' does not exist?
      if(n > 2048){
        screwed = 1;
        break;
      }
      //printf("%c\n", ch);
      message = sdscat(message, &ch);
      n++;
    }
    
    if(screwed){
      fclose(socketf);
      close(newsockfd);
      continue;
    }

    if (n < 0) {
      error("ERROR reading from socket");
      return;
    }

    Response response_message;
    // Just in case
    bzero((char *)&response_message, sizeof(response_message));
    int message_length = sizeof(Response)-sizeof(int);
    //response_message.qid = response_qid;
    response_message.mtype = 1;
    response_message.response_message = sdsempty();
    response_message.response_message = sdscpy(response_message.response_message, message);

    // block 'em all
    if(msgsnd(response_qid, &response_message, message_length, 0) != 0){
      perror("failed to send response");
    }
    
    sds *tokens;
    int count;
    
    // 0 => IP addr, 1 => nickname
    tokens = sdssplitlen(message, sdslen(message), ",", 1, &count);
    
    // screwed
    if(count != 2){
      fclose(socketf);
      close(newsockfd);
      continue;
    }
    
    Host host_info;
    // Just in case
    bzero((char *)&host_info, sizeof(host_info));
    int host_info_length = sizeof(Host)-sizeof(int);
    host_info.mtype = 1;
    host_info.IP = sdsempty();
    host_info.IP = sdscpy(host_info.IP, tokens[0]);
    host_info.nickname = sdsempty();
    host_info.nickname = sdscpy(host_info.nickname, tokens[1]);
    
    // block 'em again
    if(msgsnd(hosts_qid, &host_info, host_info_length, 0) != 0){
      perror("failed to send host info");
    }
    sds reply_message = sdsnew(sdscat(sdscat(get_iface_ipaddr("wlan0"), ","), getenv("USER")));
    printf("reply :%d\n", reply);
    if(reply){
      printf("%s\n",host_info.IP);
      send_response(host_info.IP, reply_port, reply_message);
    }

    sdsfree(message);
    fclose(socketf);
    close(newsockfd);
  }
  close(sockfd);
  return;
}

void send_response(sds hostname, int port, sds message){
  printf("inside send_response --%s--\n", hostname);
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  portno = port;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0){
    error("ERROR opening socket");
    return;
  }
  server = gethostbyname(hostname);
  if (server == NULL) {
    error("ERROR, no such host");
    //return;
  }
  
  struct timeval timeout;
	timeout.tv_sec = 1;
  
  setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR, (char *)&timeout, sizeof(timeout));
  
  bzero((char *)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
  serv_addr.sin_port = htons(portno);
  serv_addr.sin_addr.s_addr = inet_addr(hostname);
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
    error("ERROR connecting");
    return;
  }
  
  // How to get hostname
  // printf("%s", inet_ntoa(serv_addr.sin_addr));
  
  n = write(sockfd, message, sdslen(message));
  if (n < 0) {
      error("ERROR writing to socket");
      return;
  }

  free(message);
  close(sockfd);
}

void error(const char *msg) {
  perror(msg);
}
