#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <math.h>
#include <stdlib.h>


#define AZAMIUZUNLUK 1024

int main(int argc, char *argv[]){  
    int sockfd; 
    struct sockaddr_in serverAddr;
    char str[AZAMIUZUNLUK];
    int gelenBayt, gidenBayt, structSize;

	
	char mesaj[1000];
	for(int i=3;i<argc;i++)
	{

		
		strcat(mesaj,argv[i]);
		strcat(mesaj," ");


	}



    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if(-1 == sockfd){
        perror("socket");
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2])); //port
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);//ip
    memset(&(serverAddr.sin_zero), '\0', 8);

    if(-1 == connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr))){
        perror("connect");
    }

    gidenBayt = send(sockfd, mesaj, strlen(mesaj), 0);
    if(-1 == gidenBayt){  
        perror("send");
    }


    gelenBayt = recv(sockfd, &str, AZAMIUZUNLUK-1, 0);
     if(0 == gelenBayt){  
        printf("Bağlantı kapalı.\n");
    }



    close(sockfd);
}
