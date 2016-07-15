#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <unistd.h>

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[1024];
    strcpy(buffer,argv[3]);

    //enter host address and port no as arguments
    if (argc < 4) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    portno = atoi(argv[2]);
    server = gethostbyname(argv[1]);

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
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(portno);

    //connect to the desired address
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0){
        error("ERROR connecting");
    } 
        
    //write buffer to the connected address and port
    write(sockfd,&buffer,1024);
    printf("Message sent: %s\n",buffer);

    close(sockfd);

    printf("Closed socket\n");
    
    return 0;
}