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
		perror("didnt create socket\n");
	else if (DEBUG)
	{
		printf("Socket created succesfully\n");
	}
		


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
		if (DEBUG)
		{
			printf("-----------------START------------------\n");
			printf("waiting for accept request...\n");
		}
		
		printf("Waiting request port 10000...\n");
		//if come a request to socket ,accept
		if((connfd = accept(listendfd,(struct sockaddr *)NULL,NULL))<0){
	      perror("Accept Failed \n");
	      printf("Accept Failed\n");
	      return -1;
	  	}else{
	  		printf("Accept request\n");
			if (DEBUG)
			{
				printf("\nAccept request\n");
			}
			printf("-------------------------------\n");
			/*fflush(stdin);
			fflush(stdout);*/
			//read message the socket
			recMessage[0]='\0';
			if(read(connfd,&recMessage,1024)>-1){
				temp[0] = '\0';
				printf("%s\n",recMessage );
				strcpy(temp,strtok(recMessage,","));
				printf("Request Ip address : %s\n",temp );
				while(temp2=strtok(NULL,"	")){
					printf("Nick : %s\n",temp2);
				}

				if(DEBUG)
					printf("ip : %s len : %d\n",temp,(int)strlen(temp));

				send_port(temp,10001);	
			}
			/*-----close connection-----*/
			close(connfd);
			printf("-----------------------------------------------------\n");

		}

		
		
		//for respond
		

		/*-----close connection-----*/
		close(connfd);

		if (DEBUG)
		{
			printf("Terminated connection\n");
			printf("-----------------END------------------\n\n");
		}
			
		 
	}

	return 0;
}


int send_port(char *ip,int portX){
	int sockfd = 0;
	char recvBuff[1024],sendBuff[1026];
	struct sockaddr_in serv_addr;
	char  mess[1024] ;
	int connfd;

	memset(&mess,' ',1024);
	strcpy(mess,"192.168.182.187,Osman\t");

	/*------initiliaze timeout for socket ---------*/
	struct timeval timeout;      
	timeout.tv_sec = 0;
	timeout.tv_usec = 3;
	/*--------------------*/


	/*------create socket --------*/
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0){
		perror("Error create socket  ");
		return -1;
	}else if (DEBUG){
		printf("Socket create succes (send response)\n");
	}
	


	/*------assign socket for timeout------*/
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,
	       (char *)&timeout, sizeof(timeout));
	/*if (setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
                    sizeof(timeout)) < 0)*/
        //perror("setsockopt failed");

	/*------------server address  set ------*/
  	serv_addr.sin_family = AF_INET;
  	serv_addr.sin_port = htons(portX);
  	serv_addr.sin_addr.s_addr = inet_addr(ip);


		
	if (DEBUG){
		printf("-----------------START------------------\n");
		printf("waiting for send port 10001...\n");		
	}
	printf("response 10001\n");
	

	//if come a request to socket ,accept
	if((connfd=connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)))<0){
	  perror("Error connecting socket ");
	  return -1;
	}else{
		printf("Response host\n");
	}

	

	//send message the socket
	write(sockfd,&mess,1024);
	printf("Response message : %s\n\n",mess );
		
	/*-----close connection-----*/
	close(connfd);
	close(sockfd);
	if (DEBUG){
		printf("Terminated connection send_port\n");
		printf("-----------------END------------------\n\n");	
	}
	
}
