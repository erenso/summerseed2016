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

#define REQUEST "172.16.5.187"


int main(void)
{
  int sockfd = 0,n = 0;
  char recvBuff[1024],sendBuff[1026];
  struct sockaddr_in serv_addr;
  char  mess[1024] ;

  strcpy(mess,"172.16.5.187,Osman\t");

  memset(sendBuff, '0' ,sizeof(recvBuff));

  if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
  {
      printf("\n Error : Could not create socket \n");
      return 1;
  }
  printf("Socket retrieve succes\n");

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(10000);
  serv_addr.sin_addr.s_addr = inet_addr(REQUEST);
 
  if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
      printf("\n Error : Connect Failed \n");
      return 1;
  }
  printf("Connect ip address : %s\n",REQUEST);

  write(sockfd,mess,sizeof(mess));
  printf("Sent my information : %s\n",mess );
 
  
  n = read(sockfd,&recvBuff, 1023);
  printf("Read information : %s\n",recvBuff);

 
  if( n < 0)
  {
    printf("\n Read Error \n");
  }

  close(sockfd);
  
 
  return 0;
}