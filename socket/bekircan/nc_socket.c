#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StringBuilder.h"

#ifndef BUF_SIZE
#define BUF_SIZE 65000
#endif

extern void recv_msg(int port);
extern void send_msg(const char* ip, int port, const char* msg);

int main(int argc, char **argv){
	
	char buf[1];
	StringBuilder str;
	
	/*	listen */
	if(strcmp(argv[1], "-l") == 0){
		
		recv_msg(atoi(argv[2]));
		
	}else{ /*send*/
	
		SBinitilize(&str);
		
		while(scanf("%c", buf) != EOF)
			
			SBaddChar(&str, *buf);
		
		if(str.str[str.size-1] == '\n')
			
			str.str[str.size-1] = '\0';
		
		str.size--;
		
		send_msg(argv[1], atoi(argv[2]), str.str);
		
		SBclear(&str);
	}
	
	
	
	return 0;
}

