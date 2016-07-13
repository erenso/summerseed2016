#include <stdio.h> //printf
#include <string.h>    //strlen
#include <sys/socket.h>    //socket
#include <arpa/inet.h> //inet_addr
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MAXLEN 2000
 
int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char server_reply[MAXLEN];
     
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    int portno = atoi(argv[2]);

    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons(portno);
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
     
    puts("Connected\n");

    char* mes = argv[3];
    strcat(mes,"\t");
     
    //Send some data
    if(send(sock , mes , strlen(mes) , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
     
    //Receive a reply from the server
    if(recv(sock , server_reply , MAXLEN , 0) < 0)
    {
        puts("recv failed");
        return 1;
    }
     
    puts("Server reply :");
    puts(server_reply);
    puts("\n");
    
     
    close(sock);
    return 0;
}
