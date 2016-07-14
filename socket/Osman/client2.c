//#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h> 
#include <string.h> //for memset
#include <unistd.h>
#include <arpa/inet.h>
//for struct sockaddr_in and socket parameters

#ifndef DEBUG
#define DEBUG 0
#endif

#define REQUEST "172.16.5.61"


int main(void)
{
  int sockfd = 0,n = 0;
  char recvBuff[1024],sendBuff[1026];
  struct sockaddr_in serv_addr;
  char  mess[1024] ;

  strcpy(mess,"172.16.5.187,Osman\t");

  /*------initiliaze timeout for socket ---------*/
  struct timeval timeout;      
  timeout.tv_sec = 0;
  timeout.tv_usec = 3;
    /*--------------------*/



  /*------create socket --------*/
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    perror("Error   ");
  else
    printf("Socket create succes\n");

  /*------assign socket for timeout------*/
  setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,
       (char *)&timeout, sizeof(timeout));

  /*------------server address  set ------*/
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(10001);
  serv_addr.sin_addr.s_addr = inet_addr(REQUEST);

  //Server address bind socket
  bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

 
  printf("Connect ip address : %s\n",REQUEST);


  n = read(sockfd,&recvBuff, 1023);
  printf("Read information : %s\n",recvBuff);


  write(sockfd,mess,sizeof(mess));
  printf("Sent my information : %s\n",mess );
 
  
 
  close(sockfd);
  
 
  return 0;
}