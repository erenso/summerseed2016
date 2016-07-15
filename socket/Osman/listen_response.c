//#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h> 
#include <string.h> //for memset
#include <unistd.h>
#include <arpa/inet.h>
//for struct sockaddr_in and socket parameters


#ifndef DEBUG
#define DEBUG 0
#endif


int main(int argc, char const *argv[])
{
	int listendfd=0,connfd=0;
	struct sockaddr_in server_addr;
	char recMessage[1024];
	int option = 1 ;
	char  sendMessage[1024] ;
	char temp[20],*temp2;


	/*------initiliaze timeout for socket ---------*/
	struct timeval timeout;      
    timeout.tv_sec = 0;
    timeout.tv_usec = 3;
    /*--------------------*/


  	/*------create socket --------*/
	listendfd = socket(AF_INET,SOCK_STREAM,0);
	if(listendfd<0)
		perror("dont create socket\n");
	else if (DEBUG)
	{
		printf("Socket create succes\n");
	}
		

	/*------assign socket for timeout------*/
	setsockopt(listendfd,SOL_SOCKET,SO_REUSEADDR,
       &option, sizeof(option));
	
	//set server address initiliaze '0'
	memset(&server_addr,'0',sizeof(server_addr));
	
	/*------------server address  set ------*/
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(10001);
	
	if (DEBUG){
		printf("bind..\n");
	}
	
	//Server address bind socket
	bind(listendfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	
	if (DEBUG){
		printf("end bind\n");
	}

	//listen socket
	if (listen(listendfd,10)==-1)
	{
		printf("failed listen\n");
		return -1;
	}

	
	while(1){
		if (DEBUG)
		{
			printf("-----------------START------------------\n");
			printf("waiting for accept request...\n");
		}
		
		printf("-------------------------------\n");
		printf("Waiting port 10001 for response...\n");
		//if come a request to socket ,accept
		if((connfd = accept(listendfd,(struct sockaddr *)NULL,NULL))<0){
	      perror("Error  \n");
	      return -1;
	  	}else{
	  		printf("Accept request\n");
			
			//read message the socket
			if(read(connfd,&recMessage,1024)>-1){
				strcpy(temp,strtok(recMessage,","));
				printf("Request Ip address : %s\n",temp );
				while(temp2=strtok(NULL,",")){
					printf("Nick : %s\n",temp2);
				}

				if(DEBUG)
					printf("ip : %s len : %d\n",temp,(int)strlen(temp));
	
			}
			printf("-----------------------------------------------------\n");

		}

		

		/*-----close connection-----*/
		close(connfd);
		//close(listendfd);

		if (DEBUG)
		{
			printf("Terminated connection\n");
			printf("-----------------END------------------\n\n");
		}
			
		 
	}

	return 0;
}