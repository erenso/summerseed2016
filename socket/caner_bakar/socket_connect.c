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
void *takeResponse();
int sendMessage1(char *str,char *ip);

char IP[30];
char str2[100];

#define MAXCLIENT 254


int main(int argc , char *argv[]){

	char ipp_[256][256];
	char str[100];
	pthread_t *threadArr;
	pthread_t thread_response;
	char message[128];
	char response[128];
	int counter=0,counter1=0;
	int ip_=1,i;
	int *sockk;
	int iNumberofThread=0;
	int numberip=0;
	unsigned short portnum;

	sockk=malloc(sizeof(int));
	
	portnum=atoi(argv[1]);
	
	threadArr=(pthread_t*)malloc(sizeof(pthread_t)*255);

	
    fprintf(stderr, "Sending message.. Enter message\n" );
	fgets(str,sizeof(str),stdin);
	str[strlen(str)]='\t';
	strcpy(str2,str);

	for ( ip_= 1; ip_ <= 254; ++ip_){ 
		sprintf(ipp_[ip_], "172.16.5.%d", ip_);

		++iNumberofThread;
		if( pthread_create( &threadArr[iNumberofThread-1], NULL, (void*) callSocket, &ipp_[ip_]) < 0){
	        fprintf(stderr,"could not create thread");
	        return 1;
	    }
	}
	takeResponse();
	sendMessage1(str2,IP);

}

void *takeResponse(){
	int sockfd, newfd;
	struct sockaddr_in serverAddr;	// server addresses
    struct sockaddr_in clientAddr;
    char str[120]="172.16.5.61,Caner Bakar\t";
    int option;
    str[0] = '\0';
    int structSize;
    int counter=0;
    char *savedEndd1;
    
    option=1;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
																			
    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    if (setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
                    sizeof(timeout)) < 0)

    if (setsockopt (sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,
                    sizeof(timeout)) < 0)

    if(-1 == sockfd){
        close(newfd);
        close(sockfd);	
        return ;
    }
    
    serverAddr.sin_family = AF_INET;		
    serverAddr.sin_port = htons(10001);		
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    memset(&(serverAddr.sin_zero), '\0', 8);


    if(-1 == bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr))){
        close(newfd);	
        close(sockfd);
        return ;
	}
	if(-1 == listen(sockfd, 20)){
        close(newfd);	
        close(sockfd);
        return ;
    }

    structSize = sizeof(clientAddr);	
    
   
    newfd = accept(sockfd, (struct sockaddr *)&clientAddr, (socklen_t*)&structSize);
    if(-1 == newfd){
     
        close(newfd);
        close(sockfd);
        return ;
    }
  
    int index = 0;	

    fprintf(stderr, "Respond Taken: \n" );
	while(1){
		read(newfd, &str[index], 1);	
		if(str[index] == '\t'){			
			index++;					
			break;					
		}
		fprintf(stderr, "%c",str[index] );
		index++;					
	}
	strtok_r(str, ",",&savedEndd1);
	strcpy(IP,str);
	fprintf(stderr, "\n" );
	str[index] = '\0';					
}

void* callSocket(void *str1){
	int listendfd=0,connfd=0,option=1;
	struct sockaddr_in server_addr;
	char recMessage[1024];
	char  sendMessage[1024] ;
	char str[1024] ;
	strcpy(str,(void *)str1);
	int bindErr=0;
	int counter1=0;

	/*------initiliaze timeout for socket ---------*/
	struct timeval timeout;      
    timeout.tv_sec = 0;
    timeout.tv_usec = 3;
    /*--------------------*/

  	strcpy(sendMessage,"172.16.5.61,Caner Bakar\t");


  	/*------create socket --------*/
	listendfd = socket(AF_INET,SOCK_STREAM,0);
	if(listendfd<0)
		perror("Error  ");
	
	/*------assign socket for timeout------*/
	setsockopt(listendfd,SOL_SOCKET,SO_REUSEADDR,(char *)&timeout, sizeof(timeout));

	/*------------server address  set ------*/
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(str);
	server_addr.sin_port = htons(10000);
	


	/*------connect address the socket--------*/
	if((connfd=connect(listendfd, (struct sockaddr *)&server_addr, sizeof(server_addr)))<0){

  	}
  	else{
	
	
		while ( sendMessage[counter1] != '\t'){
			write(listendfd,&sendMessage[counter1++],sizeof(char));
		}
		write(listendfd,&sendMessage[counter1],sizeof(char));
  	}

  	/*-----close connect and socket -----*/

	close(connfd);
	close(listendfd);	

}  


int sendMessage1(char *str,char *ip){

	int listendfd=0,connfd=0,option=1;
	struct sockaddr_in server_addr;
	int bindErr=0;
	int counter1=0;

	/*------initiliaze timeout for socket ---------*/
	struct timeval timeout;      
    timeout.tv_sec = 0;
    timeout.tv_usec = 3;
    /*--------------------*/

  	/*------create socket --------*/
	listendfd = socket(AF_INET,SOCK_STREAM,0);
	if(listendfd<0)
		perror("Error  ");
	
	/*------assign socket for timeout------*/
	setsockopt(listendfd,SOL_SOCKET,SO_REUSEADDR,(char *)&timeout, sizeof(timeout));

	
	/*------------server address  set ------*/
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(ip);
	server_addr.sin_port = htons(10002);
	

	/*------connect address the socket--------*/
	if((connfd=connect(listendfd, (struct sockaddr *)&server_addr, sizeof(server_addr)))<0){

  	}
  	else{
		while ( str[counter1] != '\t'){
			write(listendfd,&str[counter1++],sizeof(char));
		}
		write(listendfd,&str[counter1],sizeof(char));
  	}

  	/*-----close connect and socket -----*/
	close(connfd);
	close(listendfd);	



}
