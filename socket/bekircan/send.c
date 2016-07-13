#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <unistd.h>  
#include <netdb.h>
#include <netinet/in.h>
#include <dirent.h>

#ifndef MAXHOSTNAME
#define MAXHOSTNAME 256
#endif

int main(){
	
	int socketServer, socketClient, i, numClients = 0, clientLen;
    struct sockaddr_in serverAddr, clientAddr;
	struct hostent *hp;
	char myname[MAXHOSTNAME+1];

	 /* create socket */
    if((socketServer = socket(AF_INET , SOCK_STREAM , 0)) == -1){
        
		perror("Couldn't create a socket.");
		exit(1);
    }
    
    memset(&serverAddr, 0, sizeof(struct sockaddr_in));
    
	gethostname(myname, MAXHOSTNAME);
	
	if((hp = gethostbyname(myname)) == NULL){
		
		perror("Couldn't get hostname");
		close(socketServer);
		exit(1);
	}
	
	serverAddr.sin_family= hp->h_addrtype;
	serverAddr.sin_port= htons(1234);
     
    /* bind */
    if(bind(socketServer, (struct sockaddr *)&serverAddr , sizeof(serverAddr)) == -1){
		
        perror("Couldn't bind socket");
		close(socketServer);
        exit(1);
    }
 
	listen(socketServer , 3);
	
	clientLen = sizeof(clientAddr);
			
	/* accept calls */
		
	if((socketClient = accept(socketServer, (struct sockaddr *)&clientAddr, (socklen_t *)&clientLen)) < 0){
	
		perror("Client couldn't accept");

		exit(1);
	}
	
	send(socketClient, "hello\n", 6, 0);
	
	close(socketServer);
	close(socketClient);
	
	return 0;
}
