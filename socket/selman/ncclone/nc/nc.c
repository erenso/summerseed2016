#include "include/nc.h"

/*
 *  TODO: Seperate Makefile for "nc"
 */

int listen_port(int port){
  int sockfd, newsockfd, portno;
  socklen_t clilen;
  struct sockaddr_in serv_addr, cli_addr;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0){
    //error("ERROR opening socket");
    return -1;
  }
  
  bzero((char *)&serv_addr, sizeof(serv_addr));
  portno = port;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
    //error("ERROR on binding");
    return -1;
  }
  listen(sockfd, 5);
  clilen = sizeof(cli_addr);
  while ((newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen))) {
    if (newsockfd < 0) {
      //error("ERROR on accept");
      return -1;
    }
    // Just in case
    int org_newsocketfd = dup(newsockfd);

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
      if(n > 2048){
        break;
      }
      message = sdscat(message, &ch);
      n++;
    }

    if (n < 0) {
      //error("ERROR reading from socket");
      return -1;
    }

    printf("%s\n", message);

    n = write(org_newsocketfd, "I got your message", 18);

    if (n < 0) {
      //error("ERROR writing to socket");
      return -1;
    }

    sdsfree(message);
    fclose(socketf);
    close(newsockfd);
  }
  close(sockfd);
  return 0;
}

int write_to(const char *hostname, int port){
  size_t buffer_size = 2048;
  char *message = calloc(sizeof(char),  (buffer_size + 1));
  getline(&message, &buffer_size, stdin);
  //sds message = sdstrim(sdsnew(message_h), " ");
  message[strlen(message)] = '\t';
  message[strlen(message)+1] = '\0';
  

  
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  portno = port;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0){
    error("ERROR opening socket");
    return -1;
  }
  server = gethostbyname(hostname);
  if (server == NULL) {
      fprintf(stderr, "ERROR, no such host\n");
      exit(0);
  }
  bzero((char *)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
    error("ERROR connecting");
  }
  
  // How to get hostname
  // printf("%s", inet_ntoa(serv_addr.sin_addr));
  
  n = write(sockfd, message, strlen(message));
  if (n < 0) {
      error("ERROR writing to socket");
  }
  
  /*
   * Should w8 for response?
   */
  
  //printf("%s\n",message);
  free(message);
  close(sockfd);
  return 0;
  
  

}

void error(const char *msg) {
  perror(msg);
  exit(1);
}
