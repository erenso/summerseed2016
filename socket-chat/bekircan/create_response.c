#include <stdio.h>
#include <unistd.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include "commons.h"

#define INTERFACE "wlp4s0"
#define RESPONSE_MAX 100

const char* create_response(){
	
	int fd;
	struct ifreq ifr;
	static char response[RESPONSE_MAX]={0};
	
	fd = socket(AF_INET, SOCK_DGRAM, 0);
 
	/* I want to get an IPv4 IP address */
	ifr.ifr_addr.sa_family = AF_INET;

	/* I want IP address attached to "eth0" */
	strncpy(ifr.ifr_name, INTERFACE, IFNAMSIZ-1);

	ioctl(fd, SIOCGIFADDR, &ifr);

	close(fd);

	strcat(response, inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
	strcat(response, ",");
	strcat(response, NICK);
	
	return response;
}
