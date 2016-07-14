//#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h> 
#include <string.h> //for memset
#include <unistd.h>
//for struct sockaddr_in and socket parameters

#ifndef DEBUG
#define DEBUG 0
#endif
/*----------------------------------------*/
int discovery(){}

int listen_hello_request(){}

int listen_hello_response(){}

int send_message(){}

int receive_message(){}
/*----------------------------------------*/

int main(int argc, char const *argv[])
{
	int listendfd=0,connfd=0;
	struct sockaddr_in server_addr;
	char recMessage[1024];
	int option = 1 ;
	char  sendMessage[1024] ;

  	strcpy(sendMessage,"172.16.5.187,Osman");



	listendfd = socket(AF_INET,SOCK_STREAM,0);
	 setsockopt(listendfd,SOL_SOCKET,SO_REUSEADDR,
       &option, sizeof(option));
	printf("Socket retrieve succes\n");
	
	memset(&server_addr,'0',sizeof(server_addr));
	//memset(sendMessage,'0',sizeof(sendMessage));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(10000);
	
	if (DEBUG){
		printf("bind..\n");
	}
	
	bind(listendfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	
	if (DEBUG){
		printf("end bind\n");
	}

	if (listen(listendfd,10)==-1)
	{
		printf("failed listen\n");
		return -1;
	}

	
	while(1){
		
		printf("-----------------START------------------\n");
		printf("waiting for accept request...\n");
		
		

		connfd = accept(listendfd,(struct sockaddr *)NULL,NULL);
		printf("\nAccept request\n");
		
		read(connfd,&recMessage,1024);
		printf("Request : %s\n",recMessage);

		

/*
		write(connfd,sendMessage,strlen(sendMessage));
		printf("Response : %s\n",sendMessage);*/
		close(connfd);
		printf("Terminated connection\n");
		printf("-----------------END------------------\n\n");
		 
	}

	return 0;
}