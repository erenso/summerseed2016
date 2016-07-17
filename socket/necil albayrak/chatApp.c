#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}


char* getIpString(char *ipPart, int i){
	char *temp,*result;
	int size = 0;
	sprintf(temp,"%d",i);
	size = strlen(temp)+strlen(ipPart);
	result = malloc(size*sizeof(char));
	for(int i = 0; i < strlen(ipPart); i++){
		result[i]=ipPart[i];	
	}
	for(int i = strlen(ipPart); i < size; i++){
		result[i]=temp[i];	
	}
	return result;
}



char* getIpFromString(char *str){
	int count = 0, i=0;
	char *ip;
	while(str[i] != ',' && str[i] != '\t'){
		i++;
	}
	count = i;
	i = 0;
	ip = malloc(count*sizeof(char));
	while(i < count){
		ip[i]=str[i];
		i++;
	}
	return ip;
}

char* getNickFromString(char *str, int size){
	int count = 0, i=0, start;
	char *nick;
	while(str[i] != '\t'){
		if(str[i] == ','){
			start = i+1;
			break;
		}
		i++;
	}
	nick = malloc((size-start)*sizeof(char));
	i = 0;
	while(start < size){
		nick[i] = str[start];
		start++;
		i++;
	}
	return nick;
}

char* getNickFromIp(char *clientIp){
	size_t len;
	ssize_t read;
	char *line,*nick;
	int stopFlag = 1;
	FILE *file1 = fopen("addresses.txt","r");
	if (file1 != NULL){
		while ((read = getline(&line, &len, file1)) != -1) {
			stopFlag = strcmp(clientIp,getIpFromString(line));
			if(stopFlag == 0){
				nick = getNickFromString(line,strlen(line));
				fclose(file1);
				if(nick[strlen(nick)-1] == '\n')
					nick[strlen(nick)-1]= ' ';
				return nick;
			}				
		}	
		fclose(file1);
		return NULL;
	}
}

char* getIpAddress(){
	FILE *f;
	char line[100] , *p , *c;

	f = fopen("/proc/net/route" , "r");

	while(fgets(line , 100 , f))
	{
		p = strtok(line , " \t");
		c = strtok(NULL , " \t");

		if(p!=NULL && c!=NULL)
		{
			if(strcmp(c , "00000000") == 0)
			{
				break;
			}
		}
	}

	//which family do we require , AF_INET or AF_INET6
	int fm = AF_INET;
	struct ifaddrs *ifaddr, *ifa;
	int family , s;
	char *host = malloc(NI_MAXHOST*sizeof(char));

	if (getifaddrs(&ifaddr) == -1) 
	{
		perror("getifaddrs");
		exit(EXIT_FAILURE);
	}

//Walk through linked list, maintaining head pointer so we can free list later
	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) 
	{
		if (ifa->ifa_addr == NULL)
		{
			continue;
		}

		family = ifa->ifa_addr->sa_family;

		if(strcmp( ifa->ifa_name , p) == 0)
		{
			if (family == fm) 
			{
				s = getnameinfo( ifa->ifa_addr, (family == AF_INET) ? 					sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6) , host , NI_MAXHOST , NULL , 0 , NI_NUMERICHOST);

			if (s != 0) 
			{
				printf("getnameinfo() failed: %s\n", gai_strerror(s));
				exit(EXIT_FAILURE);
			}

			return host;
		}
	}
}

freeifaddrs(ifaddr);
}

void *sendMessage(char *to, int port, char *message){
	struct timeval timeout;      
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    int sockfd, portno, n;
    int ret;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    

    char buffer[256];
    portno = port;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(to);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    ret = connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if(ret == -1)
	return NULL;
	if (setsockopt (sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,sizeof(timeout)) < 0)
       error("setsockopt failed\n");


    n = write(sockfd,message,strlen(message));
    if (n < 0) 
         error("ERROR writing to socket");
    close(sockfd);
    return NULL;
}


void *listenMessages(){
	struct sockaddr_in serv_addr, cli_addr;
	int sockfd, newsockfd, clilen;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(10002);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		error("ERROR on binding");
	listen(sockfd,5);
	clilen = sizeof(cli_addr);

	while (newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen)) {
		if (newsockfd < 0)
			error("ERROR on accept");
		int i = 0;
		char temp,n;
		char *message = malloc(sizeof(char));
		while(n = recv(newsockfd, &temp, 1,0)){
			if(temp == '\t')
				break;
			if(message = realloc(message,sizeof(char))){
				message[i] = temp;
				i++;		    
			}
		}
		if (n < 0){ 
			error("ERROR reading from socket");
		}
		size_t len;
		ssize_t read;
		char *line;
		int stopFlag = 1;
		
		char *clientIp = malloc(sizeof(char)*15);
		sprintf(clientIp,"%d.%d.%d.%d",
			(int)(cli_addr.sin_addr.s_addr&0xFF),
			(int)((cli_addr.sin_addr.s_addr&0xFF00)>>8),
			(int)((cli_addr.sin_addr.s_addr&0xFF0000)>>16),
			(int)((cli_addr.sin_addr.s_addr&0xFF000000)>>24));
		char *nick = getNickFromIp(clientIp);
		
		char *fileName = nick;
		if(nick != NULL){FILE *file;
			file = fopen(fileName, "a");
			if (file == NULL)
				error("ERROR opening file!");
			fprintf(file,"%s\n",message);
			fclose(file);
		}else{
			printf("%s tried to send message before discovery\n", clientIp);
		}
		
		
		free(fileName);
		free(message);
		free(clientIp);
		free(nick);
		close(newsockfd);
	}
	close(sockfd);
}

void *listenDiscoveryResponse(){
	struct sockaddr_in serv_addr, cli_addr;
	int sockfd, newsockfd, clilen;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(10001);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		error("ERROR on binding");
	listen(sockfd,5);
	clilen = sizeof(cli_addr);

	while (newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen)) {
		if (newsockfd < 0)
			error("ERROR on accept");
		int i = 0;
		char temp,n;
		char *message = malloc(sizeof(char));
		while(n = recv(newsockfd, &temp, 1,0)){
			if(temp == '\t'){
				break;
			}
			if(message = realloc(message,sizeof(char))){
				message[i] = temp;
				i++;		    
			}
		}
		if (n < 0){ 
			error("ERROR reading from socket");
		}
		char *ip = getIpFromString(message);
		char *nick = getNickFromString(message, (int)strlen(message));
		size_t len;
		ssize_t read;
		char *line;
		int stopFlag = 1;
		FILE *file1 = fopen("addresses.txt","r");
		if (file1 != NULL){
			while ((read = getline(&line, &len, file1)) != -1) {
				stopFlag = strcmp(nick,getNickFromString(line,len));
				if(stopFlag == 0){
					break;			
				}				
			}	
			
			fclose(file1);
		}
		FILE *file;
		
		char *clientIp = malloc(sizeof(char)*15);
		sprintf(clientIp,"%d.%d.%d.%d",
			(int)(cli_addr.sin_addr.s_addr&0xFF),
			(int)((cli_addr.sin_addr.s_addr&0xFF00)>>8),
			(int)((cli_addr.sin_addr.s_addr&0xFF0000)>>16),
			(int)((cli_addr.sin_addr.s_addr&0xFF000000)>>24));
		
		if(stopFlag != 0){
			file = fopen("addresses.txt", "a");
			if (file == NULL)
				error("ERROR opening file!");
			fprintf(file,"%s",message);
			if(message[strlen(message)-1] != '\n');
				fprintf(file, "\n");
			fclose(file);
		}
		free(message);
		free(ip);
		free(nick);
		close(newsockfd);
	}
	close(sockfd);
}

void *listenDiscovery(){
	struct sockaddr_in serv_addr, cli_addr;
	int sockfd, newsockfd, clilen;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(10000);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		error("ERROR on binding");
	listen(sockfd,5);
	clilen = sizeof(cli_addr);

	while (newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen)) {
		if (newsockfd < 0)
			error("ERROR on accept");
		int i = 0;
		char temp,n;
		char *message = malloc(sizeof(char));
		while(n = recv(newsockfd, &temp, 1,0)){
			if(temp == '\t')
				break;
			if(message = realloc(message,sizeof(char))){
				message[i] = temp;
				i++;		    
			}
		}
		if (n < 0){ 
			error("ERROR reading from socket");
		}
		char *ip = getIpFromString(message);
		char *nick = getNickFromString(message, (int)strlen(message));
		size_t len;
		ssize_t read;
		char *line;
		int stopFlag = 1;
		FILE *file1 = fopen("addresses.txt","r");
		if (file1 != NULL){
			while ((read = getline(&line, &len, file1)) != -1) {
				stopFlag = strcmp(nick,getNickFromString(line,len));
				if(stopFlag == 0){
					break;			
				}				
			}	
			
			fclose(file1);
		}
		FILE *file;
		if(stopFlag != 0){
			file = fopen("addresses.txt", "a");
			if (file == NULL)
				error("ERROR opening file!");
			fprintf(file,"%s",message);
			if(message[strlen(message)-1] != '\n');
				fprintf(file, "\n");
			fclose(file);
		}
		char *myIp = getIpAddress(),*messageToSend,*myNick = ",TomatoSlicer\t";
		int ipSize = strlen(myIp);
		messageToSend = malloc((14+ipSize)*sizeof(char));
		for(int k=0; k<ipSize; k++){
			messageToSend[k] = myIp[k];
		}
		for(int j=ipSize; j<(ipSize+14); j++){
			messageToSend[j] = myNick[j-ipSize];
		}
		char *clientIp = malloc(sizeof(char)*15);
		sprintf(clientIp,"%d.%d.%d.%d",
			(int)(cli_addr.sin_addr.s_addr&0xFF),
			(int)((cli_addr.sin_addr.s_addr&0xFF00)>>8),
			(int)((cli_addr.sin_addr.s_addr&0xFF0000)>>16),
			(int)((cli_addr.sin_addr.s_addr&0xFF000000)>>24));
		sendMessage(clientIp, 10001, messageToSend);
		free(messageToSend);
		free(message);
		free(ip);
		free(nick);
		close(newsockfd);
	}
	close(sockfd);
}



void *discover(void *str){
	char *myIp = getIpAddress(),*messageToSend,*myNick = ",TomatoSlicer\t";
	//TODO: malloc pointers or use array
	int ipSize = strlen(myIp);
	messageToSend = malloc((14+ipSize)*sizeof(char));
	for(int k=0; k<ipSize; k++){
		messageToSend[k] = myIp[k];
	}
	for(int j=ipSize; j<(ipSize+14); j++){
		messageToSend[j] = myNick[j-ipSize];
	}
	int flag = strcmp((char*)str,myIp);
	if(flag != 0)
		sendMessage((char*)str,10000,messageToSend);
	return NULL;
}


void sendMessageToUser(){
   char *nick=malloc(sizeof(char)*1024), *message=malloc(sizeof(char)*1024);

   printf("to whom :\n");
   scanf("%s",nick);
   printf("message :\n");
   scanf("%s",message);
	char *ip;
	char *line=malloc(sizeof(char)*1024);
	int stopFlag = 1;
	size_t len;
	ssize_t read;
	FILE *file1 = fopen("addresses.txt","r");
	if (file1 != NULL){
		while ((read = getline(&line, &len, file1)) != -1) {
			stopFlag = strcmp(nick,getNickFromString(line,len));
			if(stopFlag == 0){
				ip = getIpFromString(line);
				break;			
			}				
		}	
	
		fclose(file1);
	}
	sendMessage(ip, 10002, message);
	FILE *file = fopen(nick, "a");
	if (file == NULL)
		error("ERROR opening file!");
	fprintf(file,"TomatoSlicer: %s\n",message);
	fclose(file);
}

int main(int argc, char *argv[])
{		
	pthread_t pth1, pth2, pth3, pth4;
//	pthread_create(&pth1, NULL, &listenDiscovery,"discovering...");
	//pthread_create(&pth2, NULL, &listenDiscoveryResponse,"listenResponse");
	pthread_create(&pth3, NULL, &listenMessages,"listenMessage");
	
	int i=1;
	char ipPart[1024] ="172.16.5.";
	char str[1024],str1[1024],str2[1024];
	pid_t  pid;
	pthread_t threads[255];
	char strArray[255][1024];

	while(i<256){
		strcpy(str2,"");
		strcpy(str2,ipPart);
		sprintf(str,"%d",i);
		strcat(str2,str );
		strcpy(strArray[i],str2);
		pthread_create(&threads[i], NULL, &discover, (void *)strArray[i]);
		usleep(100);
		i++;	
	}
	while(1){
		printf("1: send message\n2:exit\n");
		char tmp = '3';
		scanf("%c",&tmp);
		if(tmp == '2')
			exit(0);
		sendMessageToUser();
	}
	for(int k = 0; k < 256; k++){
		printf("%d joined", k);
		pthread_join(threads[k], NULL);
	}
	
//	pthread_join(pth1, NULL);
//	pthread_join(pth2, NULL);
	pthread_join(pth3, NULL);
	return 0;
}
