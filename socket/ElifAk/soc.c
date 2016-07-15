#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include "soc.h"
int connect_socket(int portNo, char *ip)
{
	struct sockaddr_in a;
	int s;
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		close(s);
		return -1;
	}

	memset(&a, 0, sizeof(a));
	a.sin_port = htons(portNo);
	a.sin_family = AF_INET;
	if (!inet_aton(ip, (struct in_addr *) &a.sin_addr.s_addr))
	{
		perror("bad IP address format");
		close(s);
		return -1;
	}
	if (connect(s, (struct sockaddr *) &a, sizeof(a)) == -1)
	{
		close(s);
		return -1;
	}
	return s;
}
int listen_socket(int portNo)
{
	struct sockaddr_in a;
	int s;
	int yes;
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket kurulamadi");
		return -1;
	}
	yes = 1;
	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR,&yes, sizeof(yes)) == -1) 
	{
		perror("setsockopt");
		close(s);
		return -1;
	}
	memset(&a, 0, sizeof(a));
	a.sin_port = htons(portNo);
	a.sin_family = AF_INET;
	if (bind(s, (struct sockaddr *) &a, sizeof(a)) == -1)
	{
		perror("binding yapilamadi");
		close(s);
		return -1;
	}
	printf("accepting connections on port %d\n", portNo);
	listen(s, 10);
	return s;
}

int receive_message(int socket, char *message)
{
	int strLength = 0;
	char buffer;
	char *temp;
	temp = (char *) malloc(1025);
	memset(temp, 0, 1025);
	if(temp == NULL) return -1;
	//if(strLength == -1) return -1;
	while(recv(socket, &buffer, 1, 0) > 0 && buffer != 0 && strLength < 1024 && buffer != '\t')
	{
		temp[strLength] = buffer;
		strLength++;
	}
	//message = (char *) malloc(strLength + 1);
	//strcpy(message, temp);
	//message[strLength + 1] = '\0';
	temp[strLength + 1] = '\0';
	printf("%s:  %s \n", message, temp);
	return strLength;
}
