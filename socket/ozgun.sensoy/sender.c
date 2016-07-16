#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  
#include <netdb.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_PACKET_LENGTH 512

int sender(char *ip , int port , char *msg) {
	char message[MAX_PACKET_LENGTH];
    	strcpy(message, msg);
	if(strlen(message)>MAX_PACKET_LENGTH) {
		printf("Message is too long.");
		return -1;
	}
	int sock;
        struct sockaddr_in serverAddress;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sock){
        	printf("Socket could not created in this ip: %s\n", ip);
        	close(sock);
        	return -1;
        }
	struct timeval timeout;
        timeout.tv_sec = 2;
        timeout.tv_usec = 0;

        if (setsockopt (sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0){
		printf("Timeout settings has failed.\n");
        	close(sock);
        	return -1;
        }
	if (setsockopt (sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0) {
        	printf("Timeout settings has failed.\n");
        	close(sock);
        return -1;
        }
	serverAddress.sin_addr.s_addr = inet_addr(ip);
        serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	memset(&(serverAddress.sin_zero), '\0', 8);
	if(-1 == connect(sock, (struct sockaddr *) &serverAddress, sizeof(struct sockaddr))){
        	close(sock);
        	return -1;
        }
	ssize_t sendCheck = send(sock, message, strlen(message), 0);
	if(-1 == sendCheck){
        	close(sock);
        	return -1;
        } else {
		printf("Message sent to %s\n", ip);
	}	
	close(sock);
	return 0;
}
