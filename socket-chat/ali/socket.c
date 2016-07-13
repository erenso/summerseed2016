#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#define LISTENPORT 10001
#define AZAMIUZUNLUK 1024

int main(){  
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
    serverAddr.sin_port = htons(LISTENPORT);
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

    gelenBayt = recv(newfd, &str, AZAMIUZUNLUK-1, 0);
    if(-1 == gelenBayt){  
        perror("recv");
    }
    else if(0 == gelenBayt){  
        printf("Bağlantı kapalı.\n");
    }
    printf("%d bayt aldım:\t%s\n", gelenBayt, str);

    gidenBayt = send(newfd, gonder, strlen(gonder), 0);
    if(-1 == gidenBayt){  
        perror("send");
    }
    else if(strlen(gonder) != gidenBayt){
        printf("Gönderilen: %d\tGiden: %d\n", strlen(gonder), gidenBayt);
    }
    printf("%d bayt gönderdim:\t%s\n", gidenBayt, gonder);

    close(newfd);
    close(sockfd);
}
