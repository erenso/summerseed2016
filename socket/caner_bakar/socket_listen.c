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

#define MAXCLIENT 254


int new_sock[10];
int new1_sock[10];
int new1sockets=0;
int sockets=0;
int numberClient;
int client_arr[10];
int establish (unsigned short portnum);
int response(char *str);


int main(int argc , char *argv[]){

    int socket_desc;
    char message[128];
    int counter=0;
    char *savedEndd1;

    socket_desc=establish(atoi(argv[1]));

    if (socket_desc == -1){
        fprintf(stderr, "Bind Failed try again with new port\n" );
        exit(0);
    }
    else{
        fprintf(stderr, "Socket is opened\n" );
    }

    while (1){

        fprintf(stderr, "Client will be connected...\n" );
        new1_sock[new1sockets++] = accept(socket_desc, NULL, NULL);
        
        fprintf(stderr,"Client is connected !!\n" );
        
        if ( new1_sock[sockets-1]  < 0){
            fprintf(stderr,"accept failed\n");
            return 1;
        }
        
        new_sock[sockets++] = new1_sock[new1sockets-1];
        ++numberClient;
        client_arr[numberClient-1]=new_sock[sockets-1];
        
        
        while (read(new_sock[sockets-1],&message[counter],sizeof(char)) > 0){
            if ( message[counter] == '\t')
                break;
            ++counter;
        }

        message[counter]='\0';
        fprintf(stderr, "%s\n",message );
    
        
        strtok_r(message, ",",&savedEndd1);
        response(message);
  
        message[0]='\0';
        counter=0;

    }

    close(socket_desc);

}

int response(char *str){

    
    int listendfd=0,connfd=0,option=1;
    struct sockaddr_in server_addr;
    char response1[100]="192.168.2.1,Caner Bakar\t";
    int bindErr=0;
    int counter=0;

    while ( response1[counter] != '\0' ){
        ++counter;
    }


    /*------initiliaze timeout for socket ---------*/
    struct timeval timeout;      
    timeout.tv_sec = 0;
    timeout.tv_usec = 3;
    /*--------------------*/

    printf("Repsonsing... \n");

    /*------create socket --------*/
    listendfd = socket(AF_INET,SOCK_STREAM,0);
    if(listendfd<0)
        perror("Error  ");
    else
        printf("Socket create succes\n");
    
    /*------assign socket for timeout------*/
    setsockopt(listendfd,SOL_SOCKET,SO_REUSEADDR,(char *)&timeout, sizeof(timeout));

    
    /*------------server address  set ------*/
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(str);
    server_addr.sin_port = htons(10001);

    /*------connect address the socket--------*/
    
    if((connfd=connect(listendfd, (struct sockaddr *)&server_addr, sizeof(server_addr)))<0){
      printf("ip : %s\n",str);
      perror("Error  ");
    }

    else{
        write(listendfd,response1,sizeof(response1));
    }

    /*-----close connect and socket -----*/
    close(connfd);
    close(listendfd);
    printf("Terminated connection\n");  
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

    listen(s, MAXCLIENT);
    
    return(s);

}



