#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

void* discovery(void *str1);

void error(char *msg)
{
    perror(msg);
}

int main(int argc, char *argv[])
{
    int portno, i, k;
    char *iplist[258];
    pthread_t threads[255];
    
    //constructor for ips
    char singleip[20] = "172.16.5.";

    //creates iplist array of all ip's ranging from 0 to 254
    for (k=0; k<255; k=k+1){
        strcpy(singleip,"172.16.5.");
        char str[50];
        sprintf(str, "%d", k);
        strcat(singleip, str);
        iplist[k] = malloc(strlen(singleip) + 1);
        strcpy(iplist[k], singleip);
        printf("%s\n",iplist[k]);

        //creates a thread of function discovery
        pthread_create(&threads[k], NULL, &discovery, (void *)iplist[k]);
        usleep(100);
    }

    //------Wait for connection's finish---------
    for (i = 1; i <255; ++i)
    {
        pthread_join(threads[i],NULL);
        printf("joined thread : %d\n",i);
    }

    return 0;
}

void* discovery(void *str1){
int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;
    char ipstr[1024];
    strcpy(ipstr,str1);
    char buffer[1024];
    strcpy(buffer,"172.16.5.108,berke");
    portno = 10000;
    server = gethostbyname(ipstr);

    //creates the socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    /*------initiliaze timeout for socket ---------*/
    struct timeval timeout;      
    timeout.tv_sec = 0;
    timeout.tv_usec = 3;
    /*------assign socket for timeout------*/
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,
            (char *)&timeout, sizeof(timeout));
    /*--------------------*/

    //set server address properties
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ipstr);
    serv_addr.sin_port = htons(portno);

    //connect to the desired address
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0){
        //error("ERROR connecting");
    }else{
        //write buffer to the connected address and port
        write(sockfd,&buffer,1024);
        printf("Message sent: %s  %s\n",buffer, ipstr);
    }
        
    
    close(sockfd);

    //printf("Closed socket\n");
}




    
