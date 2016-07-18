#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>


#define AZAMIUZUNLUK 1024

int main(int argc, char *argv[])
{  
    
  int sockfd, newfd; 
  struct sockaddr_in serverAddr;    
  struct sockaddr_in clientAddr;
  char str[AZAMIUZUNLUK];
  int gelenBayt, gidenBayt, structSize;
  sockfd = socket(AF_INET, SOCK_STREAM, 0); 
  if(-1 == sockfd)
  {
    perror("socket");
  }

  char a;

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(10000);
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  memset(&(clientAddr.sin_zero), '\0', 0);

   
  if(-1 == bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr)))
  {
    perror("bind");
  }

  if(-1 == listen(sockfd, 1))
  {
     perror("listen");
  }

  int i=0;
  char ara;
  char cevap[50];

  while(1)
  {
    memset(&(serverAddr.sin_zero), '\0', 0);
    str[0]=NULL;
    structSize = sizeof(clientAddr);
    newfd = accept(sockfd, (struct sockaddr *)&clientAddr, &structSize);
    if(-1 == newfd)
    {
      perror("accept");
    }


    i=0;
    while(1)
    { 
      gelenBayt = recv(newfd, &a, 1, 0);
      if(-1 == gelenBayt)
      {  
        perror("recv");
        break;
       }
      if(a=='/')
      {
        ara=a;  
        gelenBayt = recv(newfd, &a, 1, 0);
        if(a=='t')
        {
          break;
        }
        else
        {
          printf("%c",ara);//str[i]=ara;
          printf("%c",a);//str[i+1]=a;
          i++;
          continue;
        } 
      }   

    printf("%c",a);//str[i]=a;
    i++;
  
    }
    printf("\n");
    strcpy(cevap,"");
    strcat(cevap,"./send ");
    strcat(cevap,inet_ntoa(clientAddr.sin_addr));
    strcat(cevap," 10001 ");
    strcat(cevap,inet_ntoa(clientAddr.sin_addr));
    strcat(cevap,",seyfullah/t");
    printf("Cevap Gönderildi..");
    system(cevap);

    if(-1 == gelenBayt)
    {  
        perror("recv");
    }

    else if(0 == gelenBayt)
    {  
        printf("Bağlantı kapalı.\n");
    }


    printf("\n-------------------------------------------------------------\n\n");


    close(newfd);
  }
  close(sockfd);

}
