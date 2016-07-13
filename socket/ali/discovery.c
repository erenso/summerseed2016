#include "netcat.h"

int main(){
	char ip[50] = "172.16.5.";
	int i = 0;
	for(i = 0; i < 256; i++){
		char newip[50];
		sprintf(newip, "%s%d", ip, i);
		printf("%s", newip);
		/*static char *argv[]={"172.16.5.61","10000",NULL};
		execv("./nc &", argv);*/
	}
}
