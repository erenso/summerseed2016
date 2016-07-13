#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/msg.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
#include <limits.h>
#include <sys/ipc.h>
#include <string.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <net/if.h>

int callSocket(char *hostname, unsigned short portnum);

void err_sys(const char *x){ 
	perror(x);
	exit(-1);
}
int main(int argc, char *argv[]){
	char *sIp, command[30], *sPort, c, IP[30];
	if(argc != 2)
		printf("2 arguman girmelisiniz\t./listener <IP>:<port_number>\n");
	else{
		system("clear");
		sIp=strtok(argv[1], ":");
		sPort=strtok(NULL, ":");
		int port=atoi(sPort);
		int	socketFD = callSocket(sIp, port);
		if(socketFD==-1)
			err_sys("connection error");
		sprintf(IP, "%s", sIp);
		write(socketFD, &IP, sizeof(IP));
		while(1){
			do{
				scanf("%c", &c);
				write(socketFD, &c, sizeof(c));
				//fprintf(stderr, "%c", c);
			}while(c!='\n');
			c='\t';
			write(socketFD, &c, sizeof(c));
		}
	}
	return 0;
}
int callSocket(char *hostname, unsigned short portnum){
	struct sockaddr_in sa;
	struct hostent *hp;
	int a, s;
	
	if ((hp= gethostbyname(hostname)) == NULL)
		err_sys("gethostbyname");

	memset(&sa,0,sizeof(sa));
	sa.sin_family= AF_INET;
	sa.sin_port= htons((u_short)portnum);
	inet_pton(AF_INET, hostname, &sa.sin_addr.s_addr);
	
	if ((s = socket(AF_INET,SOCK_STREAM,0)) < 0)
		return -1;

	if (connect(s, (struct sockaddr *)&sa,sizeof sa) < 0){
		close(s);
		return -1;
	}
	return(s);
}