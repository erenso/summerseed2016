
//source http://stackoverflow.com/questions/2283494/get-ip-address-of-an-interface-on-linux#2283541
//edited

#include <stdio.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h> /* for strncpy */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include "NetworkHeaders.h"

char * getIP()
{
    int fd;
    struct ifreq ifr;
    
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    
    /* I want to get an IPv4 IP address */
    ifr.ifr_addr.sa_family = AF_INET;
    
    strncpy(ifr.ifr_name, "en0", IFNAMSIZ-1);
    
    ioctl(fd, SIOCGIFADDR, &ifr);
    
    close(fd);
    
    /* display result */
    char * ip = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
    
    return ip;
}