#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  
#include <netdb.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_PACKET_LENGTH 512

extern int sender(char *ip , int port , char *msg);

int main(){
	char name[50];
	char ip[15];
	char message[MAX_PACKET_LENGTH];
	char *nick;
	
	printf("Enter the name of the person you want to send the message or write quit to close: ");
	fgets(name, 50, stdin);
        while(strcmp(name, "quit\n") != 0){
		FILE *stream;		
		char *line = NULL;
        	size_t len = 0;
        	ssize_t read;
		stream = fopen("address.txt", "r");
		if (!stream){
			return -1;
		}
		int i;
		while((read = getline(&line, &len, stream)) != -1) {
			if(strstr(line, name) != NULL){
				strtok_r(line, ",", &nick);
				i = 0;
			}else{
				i = 1;
			}
		}
		if(i != 1){
			strcpy(ip,line);
			printf("Enter your message like this: nick,message\n");
			printf("Enter the message you want to send or write quit to choose another person: ");
			fgets(message, 1024, stdin);
			while(strcmp(message, "quit\n") != 0){
				sender(ip, 10002, message);
				printf("Enter the message you want to send or write quit to choose another person: ");
				fgets(message, 1024, stdin);
			}
		}else{
			printf("There is no such user.\n");
		}
		printf("Enter the name of the person you want to send the message or write quit to close: ");
		fgets(name, 50, stdin);
		fclose(stream);
	}
}
