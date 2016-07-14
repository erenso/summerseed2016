#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  
#include <netdb.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>

extern volatile sig_atomic_t interrupt;

void send_msg(const char* ip, int port, const char* msg){
	
	struct sockaddr_in server_addr;
	int fdSocket;
 	struct timeval timeout;      
    		
 	timeout.tv_sec = 10;
 	timeout.tv_usec = 0;
    
	/* Create socket */
	
	if((fdSocket = socket(AF_INET , SOCK_STREAM , 0)) == -1){
		 
 		perror("Socket couldn't create");
		return ;
	}
	
 	if (setsockopt(fdSocket, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,sizeof(timeout)) < 0)
 		
		perror("set timeout failed\n");
	
	memset(&server_addr, 0, sizeof(server_addr));
    
	server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
  
	
	if(connect(fdSocket , (struct sockaddr*)&server_addr , sizeof(server_addr)) < 0){
         
// 		 perror("Couldn't connect server");
		 close(fdSocket);
         return ;
     }
		
	send(fdSocket, msg, strlen(msg), 0);
	send(fdSocket, "\t", 1, 0);
		
	shutdown(fdSocket, SHUT_RDWR);
	close(fdSocket);
}
