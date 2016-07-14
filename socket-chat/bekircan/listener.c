/* listens request port */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <errno.h>  
#include <unistd.h>  
#include <netdb.h>
#include <netinet/in.h>
#include <dirent.h>
#include "StringBuilder.h"
#include "commons.h"

#ifndef MAXHOSTNAME
#define MAXHOSTNAME 256
#endif

extern void LLaddAdress(const address_t* address);
extern const char* LLfindIP(const char* nick);
extern char* recv_msg(int port);
extern volatile sig_atomic_t interrupt;
extern void send_msg(const char* ip, int port, const char* msg);

const char terminate_char = '\t';

void parser(address_t* address, char* str){
	
	int i, j;
	
	for(i=0; str[i] != ',' && str[i] != '\0'; ++i)
			
		(address->ip)[i] = str[i];
					
	for(i=i+1, j=0; str[i] != '\0' ; ++i, ++j)
			
		(address->nick)[j] = str[i];
	
	(address->nick)[j] = '\0';
}

int open_socket(short port){
	
	int socketServer;
    struct sockaddr_in serverAddr;
	struct hostent *hp;
	char myname[MAXHOSTNAME+1];
	struct timeval timeout;      
    		
 	timeout.tv_sec = 0;
 	timeout.tv_usec = 0;
	
	 /* create socket */
    if((socketServer = socket(AF_INET , SOCK_STREAM , 0)) == -1){
        
 		perror("Couldn't create a socket.");
		return -1;
    }
    
    if (setsockopt (socketServer, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(timeout)) < 0)
 		
		perror("set timeout failed\n");
    
    memset(&serverAddr, 0, sizeof(struct sockaddr_in));
    
	gethostname(myname, MAXHOSTNAME);
	
	if((hp = gethostbyname(myname)) == NULL){
		
 		perror("Couldn't get hostname");
		close(socketServer);
		return -1;
	}
	
	serverAddr.sin_family= hp->h_addrtype;
	serverAddr.sin_port= htons(port);
     
    /* bind */
    if(bind(socketServer, (struct sockaddr *)&serverAddr , sizeof(serverAddr)) == -1){
		
        perror("Couldn't bind socket");
		close(socketServer);
        return -1;
    }
	
	listen(socketServer, 3);
	
	return socketServer;	
}

void* listener(void* arg){
	
	int lenght, socketClient, socketServer, *port = (int*)arg, i;
	StringBuilder str;
	address_t address;
	struct sockaddr_in clientAddr;
	char buf[1];
	
	socketServer = open_socket((short)(*port));
	
	lenght = sizeof(clientAddr);
		
	while(!interrupt){
	
		if((socketClient = accept(socketServer, (struct sockaddr *)&clientAddr, (socklen_t *)&lenght)) < 0){
	
			perror("Client couldn't accept");
			close(socketServer);
			
			if(interrupt)
				
				break;
			
			exit(1);
		}
	
		SBinitilize(&str);
		
		while(!interrupt && recv(socketClient, buf, 1, 0)){
						
			if(*buf == terminate_char)
				
				break;
				
			SBaddChar(&str, *buf);		
		}
					
		if(*port == MSG_PORT){
			
			for(i=0; i<str.size; ++i){
				
				if((str.str)[i] == ','){
					
					(str.str)[i] = ']';
					break;
				}
			}
			
			printf("[%s\n", str.str);
			
			SBclear(&str);
			continue;
		}
		
		parser(&address, str.str);

		SBclear(&str);
		/*
		puts(address.ip);
		puts(address.nick);
		*/
		
		if(*port == REQ_PORT && !interrupt)
				
			send_msg(address.ip, RESP_PORT, RESPONSE);
	
		if(LLfindIP(address.nick) == NULL) /* if not exist */
			
			LLaddAdress(&address);
		
	}
	
	close(socketServer);
	close(socketClient);
	
	return NULL;
}

