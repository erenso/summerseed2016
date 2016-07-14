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


int send_port(char *ip,int portX);

int main(int argc, char const *argv[])
{
	int listendfd=0,connfd=0;
	struct sockaddr_in server_addr;
	char recMessage[1024];
	int option = 1 ;
	char  sendMessage[1024] ;
	char temp[20],*temp2;
  	/*------create socket --------*/
	listendfd = socket(AF_INET,SOCK_STREAM,0);
	if(listendfd<0)
		perror("dont create socket\n");
	else
		printf("Socket create succes\n");

	/*------assign socket for timeout------*/
	setsockopt(listendfd,SOL_SOCKET,SO_REUSEADDR,
       &option, sizeof(option));
	
	//set server address initiliaze '0'
	memset(&server_addr,'0',sizeof(server_addr));
	
	/*------------server address  set ------*/
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(10000);
	
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
		
		printf("-----------------START------------------\n");
		printf("waiting for accept request...\n");
		
		//if come a request to socket ,accept
		if((connfd = accept(listendfd,(struct sockaddr *)NULL,NULL))<0){
	      perror("Accept Failed \n");
	  	}else{
			printf("\nAccept request\n");
		}

		//read message the socket
		read(connfd,&recMessage,1024);
		strcpy(temp,strtok(recMessage,","));
		printf("Ip address : %s\n",temp );
		while(temp2=strtok(NULL,",")){
			printf("Nick : %s\n",temp2);
		}
		
		//for respond
		//send_port(temp,10001);

		/*-----close connection-----*/
		close(connfd);

		printf("Terminated connection\n");
		printf("-----------------END------------------\n\n");
		 
	}

	return 0;
}


int send_port(char *ip,int portX){
	int sockfd = 0;
	char recvBuff[1024],sendBuff[1026];
	struct sockaddr_in serv_addr;
	char  mess[1024] ;
	int connfd;

	strcpy(mess,"172.16.5.187,Osman\t");

	/*------initiliaze timeout for socket ---------*/
	struct timeval timeout;      
	timeout.tv_sec = 0;
	timeout.tv_usec = 3;
	/*--------------------*/


	/*------create socket --------*/
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
		perror("Error create socket  ");
	else
	printf("Socket create succes\n");

	/*------assign socket for timeout------*/
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,
	       (char *)&timeout, sizeof(timeout));

	/*------------server address  set ------*/
  	serv_addr.sin_family = AF_INET;
  	serv_addr.sin_port = htons(portX);
  	serv_addr.sin_addr.s_addr = inet_addr(ip);


		
	printf("-----------------START------------------\n");
	printf("waiting for incoming message...\n");
		
	//if come a request to socket ,accept
	if((connfd=connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)))<0){
	  perror("Error connecting socket ");
	}else{
		printf("Accept socket\n");
	}

	printf("%s\n",mess );
	//send message the socket
	write(sockfd,&mess,1024);
	printf("send message\n");
		
	/*-----close connection-----*/
	close(connfd);
	close(sockfd);

	printf("Terminated connection\n");
	printf("-----------------END------------------\n\n");
}
