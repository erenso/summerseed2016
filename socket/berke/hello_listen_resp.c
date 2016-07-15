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

     //acquire and set server address properties to serv_addr struct
     portno = 10001;
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
        //accept incoming request
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) {
            error("ERROR on accept");
        }
        else{
            //printf("Request accepted\n");
        }

        //read the message in the incoming request
        //write it to buffer char array
        bzero(buffer,1024);
        n = read(newsockfd,buffer,1024);
        if (n < 0){
            error("ERROR reading from socket");
        }

        //print the incoming message to stdout 
        printf("---%s----\n",buffer);

        close(newsockfd);
        FILE *f = fopen("addressbook.txt", "a");
            if (f == NULL)
            {
                printf("Error opening file!\n");
                exit(1);
            }

        /* print some text */
        fprintf(f, "%s\n", buffer);
        
        fclose(f);
     }
    
     return 0; 
}