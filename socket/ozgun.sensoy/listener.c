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

int listener(int port) {
	usleep(100);
	int sock, new;
	int timeoutoption = 1;
	struct sockaddr_in serverAddress;
        struct sockaddr_in clientAddress;
	char buffer[MAX_PACKET_LENGTH];

	sock = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &timeoutoption, sizeof(timeoutoption));

    	if(-1 == sock){
        	printf("Socket could not created.\n");
        	close(sock);
        return -1;
        }
	struct timeval timeout;
        timeout.tv_sec = 3;
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
	serverAddress.sin_family = AF_INET;
    	serverAddress.sin_port = htons(port);
    	serverAddress.sin_addr.s_addr = INADDR_ANY;
    	memset(&(serverAddress.sin_zero), '\0', 8);

	if(-1 == bind(sock, (struct sockaddr *) &serverAddress, sizeof(struct sockaddr))){
        	close(new);
        	close(sock);
        	return -1;
        }
	if(-1 == listen(sock, 20)){
		printf("Error in listening.\n");
	}
	int structSize;
	structSize = sizeof(clientAddress);
	new = accept(sock, (struct sockaddr *) &clientAddress, (socklen_t*)&structSize);
	if(-1 == new){
        	close(new);
        	close(sock);
        	return -1;
        }
	bzero(buffer, MAX_PACKET_LENGTH);
	read(new, buffer, 511);
	if(port != 10002){
		char ip[15];
		FILE *ptr_file;
		ptr_file =fopen("address.txt", "a+");
		char *line = NULL;
        	size_t len = 0;
        	ssize_t read;
		int i = 0;
		while((read = getline(&line, &len, ptr_file)) != -1) {
			if(strstr(line, buffer) != NULL){
				printf("Message: %s\n", buffer);
				i++;
				break;
			}
		}
		if(i == 0){
			fprintf(ptr_file, "%s\n", buffer);
			printf("Message: %s\n", buffer);
		}
		fclose(ptr_file);
		if( port == 10000 ){
			char *nick;
			strtok_r(buffer, ",", &nick);
			strcpy(ip, buffer);
			sender(ip, 10001, "172.16.5.140,ozgun");
		}
	}else{
		char *message;
		strtok_r(buffer, ",", &message);
		printf("%s: %s", buffer, message);
	}
	close(new);
	close(sock);
	fflush(stdout);
	return 0;
}
