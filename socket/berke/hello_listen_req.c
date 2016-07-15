/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}


void sendBackInfo(void *str1){
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char ipstr[1024];
    strcpy(ipstr,str1);
    char buffer[1024];
    strcpy(buffer,"172.16.5.108,berke");
    portno = 10001;
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
        printf("Info sent: %s , to: %s\n",buffer, ipstr);
    }
        
    
    close(sockfd);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen;
     int option = 1;
     char buffer[1024];
     struct sockaddr_in serv_addr, cli_addr;
     int n;

     //creates the socket, generates and error if could not
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");

     //initialize server address
     bzero((char *) &serv_addr, sizeof(serv_addr));

     //set server address properties to serv_addr struct
     portno = 10000;
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
    
     //make sockets reusable at each iteration 
     setsockopt(newsockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
     setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
     

     //bind address to the socket
     if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
      {
        error("ERROR on binding");
     }

     //listen to socket
     listen(sockfd,10);
     clilen = sizeof(cli_addr);

     while(1){
        //printf("Started listening for incoming requests succesfully...\n");

        //accept incoming request
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) {
            error("ERROR on accept");
        }
        else{
           // printf("Request accepted\n");
        }

        //read the message in the incoming request
        //write it to buffer char array
        bzero(buffer,1024);
        n = read(newsockfd,buffer,1024);
        if (n < 0){
            error("ERROR reading from socket");
        }

        //print the incoming message to stdout 
        printf("Received request: %s\n",buffer);

        //takes ip of the sender from string
        //sends own info back to port 10001
        char * pch;
        pch = strtok(buffer, ",");
        sendBackInfo(pch);

        close(newsockfd);

        //printf("Socket closed succesfully\n");
     }

     return 0; 
}