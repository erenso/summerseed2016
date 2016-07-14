/* listens request port */

#include "commons.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

extern void LLaddAdress(const address_t* address);
extern const char* LLfindIP(const char* nick);
extern char* recv_msg(int port);
extern volatile sig_atomic_t interrupt;
extern void send_msg(const char* ip, int port, const char* msg);


void parser(address_t* address, char* str){
	
	int i, j;
	
	for(i=0; str[i] != ',' && str[i] != '\0'; ++i)
			
		(address->ip)[i] = str[i];
					
	for(i=i+1, j=0; str[i] != '\0' ; ++i, ++j)
			
		(address->nick)[j] = str[i];

}

void* listen_req(void* arg){
	
	char *str;
	address_t address;
	
	while(!interrupt){
	
		str = recv_msg(REQ_PORT);
		
		parser(&address, str);

		puts(address.ip);
		puts(address.nick);
		
		free(str);

		send_msg(address.ip, RESP_PORT, RESPONSE);
	
		if(LLfindIP(address.nick) == NULL) /* if not exist */
			LLaddAdress(&address);
	}
	
	return NULL;
}

void* listen_resp(void* arg){
	
	char *str;
	address_t address;
	
	while(!interrupt){
	
		str = recv_msg(RESP_PORT);
		
		parser(&address, str);
		
		
		puts(address.ip);
		puts(address.nick);
		
		free(str);
		
		if(LLfindIP(address.nick) == NULL) /* if not exist */
			LLaddAdress(&address);
	}
	
	return NULL;
}

void* listen_msg(void* arg){
	
	char *str;
// 	int i;
	
	while(!interrupt){
	
		str = recv_msg(MSG_PORT);
		
		//TODO formatted output
		puts(str);
				
		free(str);
	}
	
	return NULL;
}

