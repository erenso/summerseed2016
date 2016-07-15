#include "include/utils.h"

// http://stackoverflow.com/questions/2283494/get-ip-address-of-an-interface-on-linux
sds get_iface_ipaddr(sds iface){
  int fd;
  struct ifreq ifr;
  
  fd = socket(AF_INET, SOCK_DGRAM, 0);
  
  /* I want to get an IPv4 IP address */
  ifr.ifr_addr.sa_family = AF_INET;
  
  /* I want IP address attached to "eth0" */
  strncpy(ifr.ifr_name, iface , IFNAMSIZ-1);
  
  ioctl(fd, SIOCGIFADDR, &ifr);
  
  close(fd);
  
  return sdsnew(inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
  
}
