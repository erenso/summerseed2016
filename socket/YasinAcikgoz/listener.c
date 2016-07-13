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

int establish (unsigned short portnum);

void printTime();

void err_sys(const char *x){ 
	perror(x);
	exit(-1);
}
int main(int argc, char *argv[]){
	char command[30], c, *sIp, IP[30];
	int port = atoi(argv[1]);
	int listenfd, socketFD, i=0;
	if((listenfd = establish(port))<0)
		err_sys("socket");

	if(argc != 2)
		printf("1 arguman girmelisiniz\t./listener <port_number>\n");
	else{
		system("clear");
		if((socketFD = accept(listenfd, NULL, NULL))<0)
			err_sys("accept");
		read(socketFD, &IP, sizeof(IP));
		while(1){
			while(1){
				if(read(socketFD, &c, sizeof(char))<0)
					err_sys("read");
				if(i==0){
					printTime();
					fprintf(stderr, "<%s>: ", IP);
				}
				if(c!='\t')
					fprintf(stderr, "%c", c);
				else
					break;
				++i;
			}
			i=0;
		}
	}
	return 0;
}
int establish (unsigned short portnum){
	char myname[30];
	int s;
	struct sockaddr_in serverAdress;
	struct hostent *hp;

	memset(&serverAdress, 0, sizeof(struct sockaddr_in));
	gethostname(myname,30);

	serverAdress.sin_family= AF_INET;
	serverAdress.sin_port= htons(portnum);
	serverAdress.sin_addr.s_addr=htonl(INADDR_ANY);
 	
	if ((s= socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return -1;
	if (bind(s,(struct sockaddr *)&serverAdress,sizeof(struct sockaddr_in)) < 0){
		close(s);
		return -1;
	}
	listen(s, 10);
	return s;
}
void printTime(){
	char sBuffer[26];
	time_t timer;
	struct tm* tm_info;
	time(&timer);
	tm_info = localtime(&timer);
	//strftime(sBuffer, 26, "%d.%m.%Y, saat %H:%M:%S", tm_info);
	strftime(sBuffer, 26, "[%H:%M:%S]", tm_info);
	fprintf(stderr, "%s  ", sBuffer);
}