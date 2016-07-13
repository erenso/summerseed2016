#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>

#define AZAMIUZUNLUK 1024

void nclisten(int port){
	int sockfd, newfd; 
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    char *gonder = "blablabla";
    char str[AZAMIUZUNLUK];
    int gelenBayt, gidenBayt, structSize;
    
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if(-1 == sockfd){
        perror("socket");
    }
	
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    memset(&(serverAddr.sin_zero), '\0', 8);

    if(-1 == bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr))){
        perror("bind");
    }

    if(-1 == listen(sockfd, 20)){
        perror("listen");
    }

    structSize = sizeof(clientAddr);
    newfd = accept(sockfd, (struct sockaddr *)&clientAddr, &structSize);
    if(-1 == newfd){
        perror("accept");
    }
    
    int index = 0;

	while(1){
		read(newfd, &str[index], 1);
		if(str[index] == '\t'){
			index++;
			break;
		}
		index++;
	}
	
	str[index] = '\0';
	
    
    printf("%d bayt aldım:\t%s\n", (int)strlen(str), str);

    close(newfd);
    close(sockfd);
}

void ncsend(char *ip, int port, char *mesaj){
	int sockfd; 
    struct sockaddr_in serverAddr;
    char str[AZAMIUZUNLUK];
    int gelenBayt, gidenBayt, structSize;

    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if(-1 == sockfd){
        perror("socket");
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    memset(&(serverAddr.sin_zero), '\0', 8);

    if(-1 == connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr))){
        perror("connect");
    }

    gidenBayt = send(sockfd, mesaj, strlen(mesaj), 0);
    if(-1 == gidenBayt){  
        perror("send");
    }
    else if(strlen(mesaj) != gidenBayt){
        printf("Gönderilen: %d\tGiden: %d\n", (int)strlen(mesaj), gidenBayt);
    }
    printf("%d bayt gönderdim:\t%s\n", gidenBayt, mesaj);

    close(sockfd);
}

int main(int argc, char *argv[] ){
	// parse arguments
	if(strcmp(argv[1], "-l") == 0){
		nclisten(atoi(argv[2]));
	}else{
		char mesaj[AZAMIUZUNLUK];
		scanf("%s", mesaj);
		strcat(mesaj, "\t");
		ncsend(argv[1], atoi(argv[2]), mesaj);
	}
}
