#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netdb.h>
#include <sys/sendfile.h>
#include <pthread.h>


int new_sock[10];
int new1_sock[10];
int new1sockets=0;
int sockets=0;
int numberClient;
int client_arr[10];

int establish (unsigned short portnum);

int main(){

	int socket_desc;
    char message[128];
    int counter=0;
    char *savedEndd1;

    socket_desc=establish(10002);

    if (socket_desc == -1){
        fprintf(stderr, "Bind Failed try again with new port\n" );
        exit(0);
    }
    else{
        fprintf(stderr, "Socket is opened\n" );
    }

    while (1){

        new1_sock[new1sockets++] = accept(socket_desc, NULL, NULL);
        
        new_sock[sockets++] = new1_sock[new1sockets-1];
        ++numberClient;
        client_arr[numberClient-1]=new_sock[sockets-1];
        
        fprintf(stderr, "Message is coming...\n" );
        
        while (read(new_sock[sockets-1],&message[counter],sizeof(char)) > 0){
            if ( message[counter] == '\t')
                break;
            ++counter;
            fprintf(stderr, "%c",message[counter-1] );
        }
        message[counter]='\0';
        fprintf(stderr, "\n" );
    }

     close(socket_desc);

}


int establish (unsigned short portnum) {
    char myname[HOST_NAME_MAX+1]; 
    int s;
    struct sockaddr_in sa; 
    struct hostent *hp;
    memset(&sa, 0, sizeof(struct sockaddr_in)); 
    
    gethostname(myname, HOST_NAME_MAX);
    hp= gethostbyname(myname);

    if (hp == NULL) /* we don't exist !? */ 
        return(-1);
    
    sa.sin_family= hp->h_addrtype; 
    sa.sin_port= htons(portnum);

    if ( ( s = socket(AF_INET, SOCK_STREAM, 0) ) < 0) 
        return(-1);

    if ( bind( s, (struct sockaddr *)&sa,sizeof(struct sockaddr_in) ) < 0 ) {
        close(s);
        return -1;
    }

    listen(s, 10);
    
    return(s);

}