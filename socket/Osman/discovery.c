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

int receive_port(int portX);

int send_message(){}

int receive_message(){}
/*----------------------------------------*/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


int main(int argc, char const *argv[])
{
	//char Myip[1024] = "172.16.5.187";
	discoveryMain();
	
	return 0;
}

int discoveryMain(){
	int i=1;
	char cons[1024] ="172.16.5."; ///subnet hosts
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
	for (i = 1; i <255; ++i)
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
		perror("Error  socket");
	else if (DEBUG)
	{
		printf("Socket create succes\n");
	}
		
	
	/*------assign socket for timeout------*/
	setsockopt(listendfd,SOL_SOCKET,SO_REUSEADDR,
       (char *)&timeout, sizeof(timeout));

	
	/*------------server address  set ------*/
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(str);
	server_addr.sin_port = htons(10000);
	
		
	if (DEBUG)
	{
		printf("-----------------START------------------\n");
		printf("waiting for accept request...\n");
	}
		
	/*------connect address the socket--------*/
	if((connfd=connect(listendfd, (struct sockaddr *)&server_addr, sizeof(server_addr)))<0){
      printf("ip : %s connect fault\n",str);  	
  	}else{
		
		if (DEBUG){
			printf("\nConnect host\n");
		}


		write(listendfd,&sendMessage,sizeof(sendMessage));
		printf("-----------------------------\n");
		printf("Discovered  : %s\n",str);
		printf("-----------------------------\n");
		
		
		
  	}

  	/*-----close connect and socket -----*/

	close(connfd);
	close(listendfd);
	
	if (DEBUG){
		printf("Terminated connection ip %s\n",str);	
	}

}


int receive_port(int portX){
	int listendfd=0,connfd=0;
	struct sockaddr_in server_addr;
	char recMessage[1024];
	int option = 1 ;
	int byte=0;
	char  sendMessage[1024] ;
	char temp[20],*temp2;

	FILE *inp = fopen("discovery.txt","a");
	if(inp==NULL){
		perror("Error file");
		exit(1);
	}



  	/*------create socket --------*/
	listendfd = socket(AF_INET,SOCK_STREAM,0);
	if(listendfd<0)
		perror("dont create socket\n");
	else if(DEBUG)
		printf("Socket create succes\n");


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
		perror("Error listen ");
		return -1;
	}

	
		
	
	//if come a request to socket ,accept
	if((connfd = accept(listendfd,(struct sockaddr *)NULL,NULL))<0){
	  perror("Accept Failed \n");
	  return -1;
	}
	
	if(DEBUG){
		printf("\nAccept request\n");
	}

	byte=(int)read(connfd,&recMessage,1024);
	if (DEBUG)
	{
		printf("recByte : %d \nmessage%s\n",byte,recMessage);
	}

	/*
	pthread_mutex_lock(&mutex);
	pthread_mutex_unlock(&mutex);
	*/	
	

	if(strstr(recMessage,",") == NULL) {
    	fprintf(inp,"%s\n",recMessage );
	
	}
	printf("--------------------------------------------\n");
	fprintf(inp,"%s : ",strcpy(temp,strtok(recMessage,",")));
	printf("discovered\n");
	printf("IP : %s\n",temp);
	printf("--------------------------------------------\n");
	while((temp2=strtok(NULL,","))!=NULL){
		fprintf(inp,",%s\n",temp2);
	}
	printf("Nick : %s\n",temp2);

	fclose(inp);
	printf("discovered end\n");
	/*-----close connection-----*/
	close(connfd);
	close(listendfd);
}