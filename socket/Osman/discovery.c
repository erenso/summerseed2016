//#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h> 
#include <string.h> //for memset
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <pthread.h>
//for struct sockaddr_in and socket parameters

#ifndef DEBUG
#define DEBUG 0
#endif
#define REQUEST "172.16.5.187"
void* discovery(void *str1);

int main(int argc, char const *argv[])
{
	int i=1,t;
	char cons[1024] ="172.16.5.";
	char str[1024],str1[1024];
	char str2[1024];
	 pid_t  pid;
	pthread_t threads[255];

	char tab[5]="\t";
	while(i<255){
		strcpy(str2,"");
		strcpy(str2,cons);
		sprintf(str,"%d",i);
		strcat(str2,str );
		printf("%s\n",str2 );
		
		printf("length : %d \n",str2);
		pthread_create(&threads[i], NULL, &discovery, (void *)str2);
		usleep(100);
		
		i++;	
	}

	

	return 0;
}


void* discovery(void *str1){
	int listendfd=0,connfd=0;
	struct sockaddr_in server_addr;
	char recMessage[1024];
	char  sendMessage[1024] ;
	char str[1024] ;
	strcpy(str,(void *)str1);
	

  	strcpy(sendMessage,"172.16.5.187,Osman\t");

  	printf("discovery string:  %s\n",str);

	listendfd = socket(AF_INET,SOCK_STREAM,0);
	printf("Socket retrieve succes\n");
	
	memset(&server_addr,'0',sizeof(server_addr));
	//memset(sendMessage,'0',sizeof(sendMessage));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(str);
	server_addr.sin_port = htons(10000);
	
	if (DEBUG){
		printf("bind..\n");
	}
	
	bind(listendfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	
	if (DEBUG){
		printf("end bind\n");
	}
	
		
	printf("waiting for accept request...");

	if((connfd=connect(listendfd, (struct sockaddr *)&server_addr, sizeof(server_addr)))<0){
      printf("\n Error : Connect Failed \n");
      return;
  	}
	printf("\nAccept request\n");

	write(listendfd,&sendMessage,1024);
	printf("send : %s\n",sendMessage);

	close(connfd);
	printf("Terminated connection\n");	

}