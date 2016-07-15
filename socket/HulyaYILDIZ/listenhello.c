#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <signal.h>
#include <netinet/in.h>

#define MAXSIZE 10000
#define MYINFO "172.16.5.86,HLYYLDZ"


/*Ctr-C yakalama*/
void catchCtrlC(int signal);
int sending(char ip[20],char port[20],char mymessage[9995]);
void * sendIP(void * i);
char *listenfunc(char argv[MAXSIZE]);
int discovery();
void * listenHello();
void * recMessage();
int sendMessage();


char IP[20]="172.16.5";
char AllIP[255][20];  
pthread_t pth[255],dis,lisHello,recM,sendM;	
int sockfd = 0,numOfPerson=0;
char AllUserIP[255][50];
char AllUserNICK[255][50];


int main(){

    // pthread_create(&dis,NULL,(void *)discovery,NULL);sleep(1);
    pthread_create(&lisHello,NULL,(void *)listenHello,NULL);
    pthread_create(&recM,NULL,(void *)recMessage,NULL);
     //pthread_create(&sendM,NULL,(void *)sendMessage,NULL);
    
    while(1){    
      sendMessage();
    }   
    
    pthread_join(recM,NULL);
    pthread_join(lisHello,NULL);    
    //pthread_join(dis,NULL);
    
return 0;    
}

int sendMessage(){
    char nick[50];
    char message[MAXSIZE],sender[MAXSIZE];
    int i,person=-1;
    
    printf("\n\nEnter Nick (enter QUIT for exit) : ");
    scanf("%s",nick);
    //printf("%s",nick);
    if(strcmp(nick,"QUIT")==0){
        printf("\nChat closed..\n");
        exit(0);
    }   
    for(i=0;i<numOfPerson;i++){
        if(strcmp(AllUserNICK[i],nick)==0){
            person=i;        
        }    
    }
    if(person==-1){
        printf("\n\n%s isimli kullanici bulunamadi.\n",nick);
        return;
    }
    printf("\nEnter Message : ");
    fgets(message,10000,stdin);
    sprintf(sender,"%s: %s%s","HLYYLDZ",message,"\0");
    sending(AllUserIP[person],"10002", sender);
    //printf("**%s**",sender);
    sleep(1);
}


void * recMessage(){
    char receiver[MAXSIZE];
    while(1){ 
    
        fflush(stdin);
        fflush(stdout);        
        memset(receiver, ' ', sizeof(receiver));
        strcpy(receiver,listenfunc("10002"));
        //sprintf(receiver,"%s",strtok(receiver,"           "));
        //sleep(1);
        printf("\n***********************************************************************\n");        
        printf("\nNew Message : ");
        strcat(receiver,"\0");
        printf("\n%s\n",receiver);
        printf("\n***********************************************************************\n");  
 
    }
}

void * listenHello(){
    char receiver[MAXSIZE];
    char *IPADDR,*nick;
    int i=0,k,flag=0;
    while(1){
        memset(receiver, ' ', sizeof(receiver)); 
        flag=1;
        strcpy(receiver,listenfunc("10000"));
        IPADDR=strtok(receiver,",");
        nick=strtok(NULL,"\n");
        //printf("\n#############################################33\n");
        //printf("\n%s\n",IPADDR);
        //printf("%s\n",nick);
        sending(IPADDR,"10001", MYINFO);
      
        if(i==0){
            strcat(AllUserIP[numOfPerson],IPADDR);
            strcat(AllUserNICK[numOfPerson],nick);
            // printf("\n%d) %s\n",numOfPerson,AllUserIP[numOfPerson]);
            // printf("%s\n",AllUserNICK[numOfPerson]);
            numOfPerson++;
        }
        else 
            for(k=0;k<numOfPerson;k++){
                if(strncmp(AllUserIP[k],IPADDR,16)==0)
                    {flag=1; //printf("%d ***************\n",k);
                }
            }  

        if(flag!=1){
            strcat(AllUserIP[numOfPerson],IPADDR);
            strcat(AllUserNICK[numOfPerson],nick);      
            //printf("\n%d) %s ",numOfPerson,AllUserIP[numOfPerson]);
            //printf("%s\n",AllUserNICK[numOfPerson]);
            numOfPerson++;
            flag=1;
        }
              
        i++;   
    }
}




// argv Portunu dinleyen fonksiyon
char *listenfunc(char argv[MAXSIZE]){
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;    
    struct timeval timeout;
    int i=1;
	
    char sendBuff[MAXSIZE];
    static char send[MAXSIZE];

    memset(&serv_addr, ' ', sizeof(serv_addr));
    memset(sendBuff, ' ', sizeof(sendBuff)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv)); 

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
/*
    timeout.tv_sec = 3;
    timeout.tv_usec = 0;

    if (setsockopt (listenfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
         if (setsockopt (listenfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,sizeof(timeout)) < 0)
            if(-1 == sockfd){
                close(connfd);	// close connection socket
                close(listenfd);	// close the socket we listened to
                exit(1);
            }
*/   
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i)) == -1) {
        close(listenfd);
        exit(1);
    }
    if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))<0){
        fprintf(stderr, "BINDIIING\n");
        close(listenfd);
        exit(1);     
    }

    listen(listenfd, 10); 
	//fprintf(stderr, "Server was started\n");   
    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
 
    memset(send, '\0', sizeof(send)); 
 
    //scanf("%s",sendBuff);
    while( read(connfd, sendBuff, sizeof(sendBuff))<0); 
  
    
    for (i=0;i<MAXSIZE;i++){
        if(sendBuff[i]=='\t'){
            //printf("**********************************************");
            //printf( "okunan :%s\n",send);
            close(connfd);
            close(listenfd);
            return send;
        }
         else
            send[i] = sendBuff[i];
    }
    //printf("**********************************************");   
    //printf( "okunan: %s\n",send);
    close(connfd);
    close(listenfd);
return send;    
}

int discovery(){

    int i =0,err;
    char newip[20]; 	
	
	// CTRL^C.nin yakalanmasi 
	signal(SIGINT,catchCtrlC);
	
	for(i=0;i<255;i++){
		sprintf(newip, "%s.%d", IP, i);     
	    strcat(AllIP[i],newip);
	}

    for(i=0;i<255;i++){
	    err=pthread_create(&pth[i],NULL,(void *)sendIP,(void*)AllIP[i]);	
	    if(err == -1){
		    perror("thread creation");
		    exit(-1);
	    } 
    }

    for (i = 0; i < 255; i++) 
        if ( pthread_join(pth[i], NULL)) {
            fprintf(stderr, "Failed to join thread ");
            return 1;
        }
    // printf("--------------------------------");
     
return 0;    
}

int sending(char ip[20],char port[20],char mymessage[9995])
{
    int sockfd = 0, n = 0;
    char recvBuff[9995];
    struct sockaddr_in serv_addr; 

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("\n Error : Could not create socket \n");
        return 1;
    } 
    
    memset(recvBuff, '0',sizeof(recvBuff));
    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(port)); 

	/*Verilen stringi (IP adresini) network adresine kopyalar*/
    if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0){
        //printf("\n inet_pton error occured\n");
        return 1;
    } 
	/*Client server a baglanti yapar. Server kabul edene kadar bekler*/
    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        //printf("\n Error : Connect Failed \n");
        return 1;
    }  
    //else printf("\n baglndı" );

    snprintf(recvBuff, sizeof(recvBuff), "%s\t%s",mymessage,"\0");
    //printf("\n%s\n", recvBuff);
    
    n = write(sockfd, recvBuff, strlen(recvBuff));
    printf("\nyazılan:%s\n", recvBuff);
    close(sockfd);
    return 0;
}


void * sendIP(void * i){
	sending(i,"10000", MYINFO);		
	// printf("gonderildi");
}


void catchCtrlC(int signal){
    int i=0;
    printf("\nCTRL-C sinyali yakalandi. Programdan cikiliyor..\n\n");    
/*    for (i = 0; i < 255; i++)    
        close(sockfd);
        if ( pthread_cancel(pth[i])) {
            fprintf(stderr, "Failed to join thread ");
            exit(0);
    }
    pthread_cancel(tid);*/
close(sockfd);
exit(0);
}

