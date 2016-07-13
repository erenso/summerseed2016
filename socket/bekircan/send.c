#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

int main(){
	
	struct sockaddr_in server_addr;
	int fdSocket;
	
    /* Create socket */
	
	if((fdSocket = socket(AF_INET , SOCK_STREAM , 0)) == -1){
		 
		perror("Socket couldn't create");
		exit(1);
	}
	
	
	memset(&server_addr, 0, sizeof(server_addr));
    
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(888);
  
	
	 if (connect(fdSocket , (struct sockaddr*)&server_addr , sizeof(server_addr)) < 0){
         
		 perror("Couldn't connect server");
		 close(fdSocket);
         exit(1);
     }
	
	send(fdSocket, "hello\n", 6, 0);
	
	close(fdSocket);
		
	return 0;
}
