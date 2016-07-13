#include "netcat.h"

int main(){
	char ip[50] = "172.16.5.";
	int i;
	for(i = 0; i < 256; i++){
		char command[50];
		sprintf(command, "echo \"172.16.5.179,ali\t\" | ./nc %s%d 10000 &", ip, i);
		//printf("%s\n", command);
		//static char *argv[]={NULL};
		system(command);
	}
	sleep(1);
	system("killall nc");
}
