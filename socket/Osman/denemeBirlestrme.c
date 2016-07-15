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
#define REQUEST "172.16.5.187"
void* discovery(void *str1);

/*----------------------------------------*/
int discoveryMain();

int listen_request(int portX);
void* discovery(void *str1);

int send_port(char *temp,int portX);

int send_message(){}

int receive_message(){}
/*----------------------------------------*/



int main(int argc, char const *argv[])
{
	char ip[1024] = "172.16.5.179";
	//discoveryMain();
	//send_port(ip,10002);
	//listen_request(10000);
	//listen_response();
	listen_request(10000);
	return 0;
}

int discoveryMain(){
	int i=1;
	char cons[1024] ="172.16.5.";
	char str[1024],str1[1024];
	char str2[1024];
	pid_t  pid;
	pthread_t threads[255];
	char strArray[255][1024];

	char tab[5]="\t";


	while(i<255){
		/*-------calculate ip address-------*/
		strcpy(str2,"");
		strcpy(str2,cons);
		sprintf(str,"%d",i);
		strcat(str2,str );
		strcpy(strArray[i],str2);
		/*---------------------------*/

		pthread_create(&threads[i], NULL, &discovery, (void *)strArray[i]);
		usleep(100);
		
		i++;	
	}


	/*-------Wait for connection's finish---------*/
	for (i = 0; i <255; ++i)
	{
		pthread_join(threads[i],NULL);
		printf("joined thread : %d\n",i);
	}


}

void* discovery(void *str1){
	int listendfd=0,connfd=0,option=1;
	struct sockaddr_in server_addr;
	char recMessage[1024];
	char  sendMessage[1024] ;
	char str[1024] ;
	strcpy(str,(void *)str1);
	int bindErr=0;

	/*------initiliaze timeout for socket ---------*/
	struct timeval timeout;      
    timeout.tv_sec = 0;
    timeout.tv_usec = 3;
    /*--------------------*/


  	strcpy(sendMessage,"172.16.5.187,Osman\t");

  	printf("Discovering  %s\n",str);

  	/*------create socket --------*/
	listendfd = socket(AF_INET,SOCK_STREAM,0);
	if(listendfd<0)
		perror("Error  ");
	else
		printf("Socket create succes\n");
	
	/*------assign socket for timeout------*/
	setsockopt(listendfd,SOL_SOCKET,SO_REUSEADDR,
       (char *)&timeout, sizeof(timeout));

	
	/*------------server address  set ------*/
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(str);
	server_addr.sin_port = htons(10000);
	
		
	printf("waiting for accept request...\n");

	/*------connect address the socket--------*/
	if((connfd=connect(listendfd, (struct sockaddr *)&server_addr, sizeof(server_addr)))<0){
      printf("ip : %s\n",str);
      perror("Error  ");
  	}else{
		printf("\nAccept request\n");
		printf("Discovered  %s\n",str);
		write(listendfd,&sendMessage,sizeof(sendMessage));
		printf("send : %s\n",sendMessage);
  	}

  	/*-----close connect and socket -----*/
	close(connfd);
	close(listendfd);
	printf("Terminated connection\n");	

}


int listen_request(int portX){
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
	server_addr.sin_port = htons(portX);
	
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

		if(portX==10002){
			printf("%s\n",recMessage );
		}else{
			strcpy(temp,strtok(recMessage,","));
			printf("Ip address : %s\n",temp );
			while(temp2=strtok(NULL,",")){
				printf("Nick : %s\n",temp2);
			}
		}
		
		
		
		/*-----close connection-----*/
		close(connfd);
		close(listendfd);
		if(portX==10000)
			send_port(temp,10001);
		else if(portX == 10002){
			send_port(temp,10002);
		}

		printf("Terminated connection\n");
		printf("-----------------END------------------\n\n");
		 
	}
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
	if(portX==10002)
	{
		printf("Please enter message>>");
		scanf("%s",mess);
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

