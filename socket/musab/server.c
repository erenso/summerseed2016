#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> /* for strncpy */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <pthread.h> //for threading , link with lpthread
#include <fcntl.h>
 
void *connection_handler(void *);

//char *client_ip = inet_ntoa(client.sin_addr);
//int client_port = ntohs(client.sin_port);

int main(int argc , char *argv[])
{
    int socket_desc , new_socket , c, *new_sock;
    struct sockaddr_in server , client;
    char *message , server_reply[2000];
    int port_number=10000;
    
    struct timeval timeout;      
	timeout.tv_sec = 0;
	timeout.tv_usec = 3; 
    
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    
    setsockopt(socket_desc,SOL_SOCKET,SO_REUSEADDR,
	       (char *)&timeout, sizeof(timeout));
    
    memset(&server,'0',sizeof(server));

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port_number);
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("bind failed");
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
    
    
     
    //Accept and incoming connection
    
    //printf("Server ip: %s\n", server_ip);
    //printf("Server port: %d\n", server_port);
    puts("Waiting for incoming connections...");
    
    c = sizeof(struct sockaddr_in);
    while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Connection accepted");
        char *client_ip = inet_ntoa(client.sin_addr);
        printf("-----------\nConnected IP: %s\n", client_ip);
        
        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = new_socket;
         
        if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }
         
        //Now join the thread , so that we dont terminate before the thread
        pthread_join( sniffer_thread , NULL);
        puts("Handler assigned");
    }
    return 0;
}


void *connection_handler(void *socket_desc)
{
    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    int read_size;
    char *message , client_message[2000];
    char line[1024], word[50] ;
    FILE *inp, *outp;
    inp = fopen("adressbook.txt", "a+");
    outp = fopen("addressbook.txt", "r");
    
    message = "172.16.5.145,musab\t"; 
    //Send some messages to the client
    
    write(sock , message , strlen(message));
    
     
    //Receive a message from client
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
    {
        //Send the message back to client
        printf("client_message: %s\n-------------\n", client_message);
        fprintf(inp, "%s\n", client_message);
        strcpy(word,strtok(client_message, ","));
        //printf("word: %s\n", word);
        write(sock , message , strlen(message));
        
    }
     
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
         
    //Free the socket pointer
    free(socket_desc);
    fclose(inp); 
    return 0;
}
