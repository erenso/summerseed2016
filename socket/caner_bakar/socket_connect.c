#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>   
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/sendfile.h>
#include <pthread.h>

int sock;
int callSocket(char *hostname, unsigned short portnum,char ip[128]);

int main(int argc , char *argv[]){

	char ip[128];
	char myname[HOST_NAME_MAX+1];
	char message[128];
	int counter=0;


	gethostname(myname, HOST_NAME_MAX);
    sock=callSocket(myname,atoi(argv[2]),argv[1]);

    if ( sock == -1){
        fprintf(stderr, "There is no server! \n" );
        exit(0);
    }

    fprintf(stderr, "Enter the message\n" );
    scanf("%s",message);

    message[strlen(message)]='\t';


    while ( message[counter++] != '\t'){
    	write(sock,&message[counter-1],sizeof(char));
    	fprintf(stderr, "%d\n",message[counter-1] );
    }

    write(sock,&message[counter-1],sizeof(char)*(counter-1));
    fprintf(stderr, "%d\n",counter );
    

    close(sock);
}






int callSocket(char *hostname, unsigned short portnum,char ip[128]) {
    struct sockaddr_in sa;
    struct hostent *hp;
    int a, s;

    if ((hp= gethostbyname(hostname)) == NULL) { 
        return(-1);
    } 
    
    memset(&sa,0,sizeof(sa));
    sa.sin_family= hp->h_addrtype; 
    sa.sin_port= htons((u_short)portnum);
    inet_pton(AF_INET, ip, &(sa.sin_addr.s_addr));
    
    if ((s= socket(hp->h_addrtype,SOCK_STREAM,0)) < 0) 
        return(-1);

    if (connect(s,(struct sockaddr *)&sa,sizeof sa) < 0) { 
        close(s);
        return(-1);
    }
    return(s); 
}