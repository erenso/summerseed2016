//#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h> 
#include <string.h> //for memset
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
//for struct sockaddr_in and socket parameters


#ifndef DEBUG
#define DEBUG 0
#endif


int main(int argc, char const *argv[])
{
	int listendfd=0,connfd=0;
	struct sockaddr_in server_addr;
	char recMessage[1024];
	int len = 0,option=1;
	char  sendMessage[1024] ;
	char temp[20],*temp2;
	int count=0;

	/*------create socket --------*/
	if((listendfd = socket(AF_INET, SOCK_STREAM, 0))< 0){
		perror("Error create socket  ");
		return -1;
	}else if (DEBUG){
		printf("Socket create succes (receive message)\n");
	}

		/*------assign socket for timeout------*/
	setsockopt(listendfd,SOL_SOCKET,SO_REUSEADDR,
       &option, sizeof(option));

	//set server address initiliaze '0'
	memset(&server_addr,'0',sizeof(server_addr));
	
	/*------------server address  set ------*/
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(10002);
	
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

	count=1;
	while(1){
		
	
		
		//if come a request to socket ,accept
		if((connfd = accept(listendfd,(struct sockaddr *)NULL,NULL))<0){
	      perror("Accept Failed \n");
	  	}
	  	if(DEBUG){
			printf("\nAccept request\n");
		}
		printf("connect %d\n",count++);
		memset(&recMessage,' ',1024);
		//read message the socket
		len = (int)read(connfd,&recMessage,1024);
		if (DEBUG)
		{
			printf("receive byte : %d ",len);
		}

		if(strstr(recMessage,",") == NULL) {
    		
    		printf("%s(wrong format!!)\n",recMessage );
		}else{
			printf("%s  ",strcpy(temp,strtok(recMessage,",")));

			while((temp2=strtok(NULL,","))!=NULL){
				printf(": %s\n",temp2);
			}
		}
		fflush(stdin);
		fflush(stdout);
		/*-----close connection-----*/
		close(connfd);
	}
	return 0;
}