#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>   
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/sendfile.h>
#include <pthread.h>

int sock;
unsigned short portnum;
void* callSocket(void *str1);


int main(int argc , char *argv[]){

	char ipp_[256][256];
	pthread_t *threadArr;
	char message[128];
	char response[128];
	int counter=0,counter1=0;
	int ip_=1,i;
	int *sockk;
	int iNumberofThread=0;
	unsigned short portnum;

	sockk=malloc(sizeof(int));
	
	portnum=atoi(argv[1]);
	
	threadArr=(pthread_t*)malloc(sizeof(pthread_t)*255);

	for ( ip_= 1; ip_ <= 254; ++ip_){ 
		sprintf(ipp_[ip_], "172.16.5.%d", ip_);

		++iNumberofThread;
		if( pthread_create( &threadArr[iNumberofThread-1], NULL, (void*) callSocket, &ipp_[ip_]) < 0){
	        fprintf(stderr,"could not create thread");
	        return 1;
	    }
	}


	for(i=0;i<iNumberofThread;++i){    
        pthread_join(threadArr[i],(void**)&sockk);
        if ( *sockk != -1){
	        while ( message[counter++] != '\t'){
	        	fprintf(stderr, "ASDADASAAAAAAAAAAAAAAAAAA\n" );
		    	write(*sockk,&message[counter-1],sizeof(char));
		    }
		}
       
    }

}

void* callSocket(void *str1){
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


  	strcpy(sendMessage,"172.16.5.61,Caner Bakar\t");

  	printf("Discovering  %s\n",str);

  	/*------create socket --------*/
	listendfd = socket(AF_INET,SOCK_STREAM,0);
	if(listendfd<0)
		perror("Error  ");
	else
		printf("Socket create succes\n");
	
	/*------assign socket for timeout------*/
	setsockopt(listendfd,SOL_SOCKET,SO_REUSEADDR,(char *)&timeout, sizeof(timeout));

	
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
