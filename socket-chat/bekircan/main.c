#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <unistd.h>  
#include <sys/wait.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
#include "commons.h"
#include "listener.h"
#include "StringBuilder.h"

#ifndef THREADVECTOR_INITIAL_CAPACITY
#define THREADVECTOR_INITIAL_CAPACITY 10
#endif

#define NICK "bekircan"
#define REFRESH_FREQ 600 //sec

/* thread vector */
typedef struct{
	
	pthread_t *threads;
	int size;
	int capacity;
}threadvector_t;

void LLaddAdress(const address_t* address);
void LLclear();
const char* LLfindIP(const char* nick);
extern void send_msg(const char* ip, int port, const char* msg);
extern void discover();
void listUsers();
void signalHandler(int sig);
void* refresh(void* arg);

/* signal handler flag */
volatile sig_atomic_t interrupt = 0;
/* mutex lock for linked list */
pthread_mutex_t ll_mutex;
/* head of the linked list */
static address_ll* headLL = NULL;

int main(){
	
	int i, ports[]={REQ_PORT, RESP_PORT, MSG_PORT};
	pthread_t thread;
	StringBuilder nick, msg;
	char ch;
	const char* target_ip;
	struct sigaction act;
	
	threadvector_t threadArray={
		
		.threads = (pthread_t*)malloc(THREADVECTOR_INITIAL_CAPACITY*sizeof(pthread_t)),
		.size = 0,
		.capacity = THREADVECTOR_INITIAL_CAPACITY
	};
	
	/* set signal handler */
	act.sa_handler = signalHandler; 
	act.sa_flags = 0;
	if ((sigemptyset(&act.sa_mask) == -1) || 
		(sigaction(SIGINT, &act, NULL) == -1))
	{
		perror("Failed to set signal handler");
		exit(1);
	}
	
	/* create listener threads */
	
	pthread_create(&thread, NULL, listener, (void*)(ports)); //request
	threadArray.threads[(threadArray.size)++] = thread;
	 
	pthread_create(&thread, NULL, listener, (void*)(ports+1)); //response
	threadArray.threads[(threadArray.size)++] = thread;
	
	pthread_create(&thread, NULL, listener, (void*)(ports+2)); //message
	threadArray.threads[(threadArray.size)++] = thread;
	
	
	sleep(1); //wait for listener threads
	
	pthread_create(&thread, NULL, refresh, NULL);
	threadArray.threads[(threadArray.size)++] = thread;
		
	while(!interrupt){
	
		SBinitilize(&nick);
		
		puts("Enter target nick, -ls for list");
		
		while(scanf("%c", &ch) != EOF && ch != '\n')
			
			SBaddChar(&nick, ch);
		
		if(strcmp("-ls", nick.str) == 0){
			
			listUsers();
			SBclear(&nick);
			continue;
		}
			
		if((target_ip = LLfindIP(nick.str)) == NULL){
			
			fprintf(stderr, "user %s couldn't find\n", nick.str);
			SBclear(&nick);
			continue;
		}
		
		puts("Enter target msg");
		
		SBinitilize(&msg);
				
		SBaddString(&msg, NICK);
		SBaddChar(&msg, ',');
		
		while(scanf("%c", &ch) != EOF && ch != '\n')
			
			SBaddChar(&msg, ch);
		
		send_msg(target_ip, MSG_PORT, msg.str);
		
		SBclear(&nick);
		SBclear(&msg);
	}
	
	/* wait for threads */
	for(i=0; i<threadArray.size; ++i)
		
		pthread_join(threadArray.threads[i], NULL);
	
	/* free sources */
	
	pthread_mutex_destroy(&ll_mutex);
	free((void*)threadArray.threads);	
	
	return 0;
}

void* refresh(void* arg){
	
	while(!interrupt){
		
		discover();
		
		sleep(REFRESH_FREQ);
	}
	
	return NULL;
	
}

void LLaddAdress(const address_t* address){
	
	address_ll **temp = &headLL;
	
	pthread_mutex_lock(&ll_mutex);
	
	while(*temp)
		
		temp = &((*temp)->next);
		
	*temp = (address_ll*)malloc(sizeof(address_ll));
		
	strcpy(((*temp)->address).nick, address->nick);
	strcpy(((*temp)->address).ip, address->ip);
	(*temp)->next = NULL;	
		
	pthread_mutex_unlock(&ll_mutex);
}

const char* LLfindIP(const char* nick){
	
	address_ll* temp = headLL;
	
	pthread_mutex_lock(&ll_mutex);
		
	while(temp){
		
		if(strcmp(nick, temp->address.nick) == 0){
				
			pthread_mutex_unlock(&ll_mutex);
			
			return temp->address.ip;
		}
		
		temp = temp->next;
	}
	
	pthread_mutex_unlock(&ll_mutex);
	
	return NULL;
}

void LLclear(){
	
	address_ll* temp;
	
	pthread_mutex_lock(&ll_mutex);
	
	while(headLL){
		
		temp = headLL->next;
		
		free(headLL);
		
		headLL = temp;
	}		
	
	pthread_mutex_unlock(&ll_mutex);
}

void listUsers(){
	
	address_ll* temp = headLL;
	
	pthread_mutex_lock(&ll_mutex);
	
	for(;temp;temp=temp->next)
		
		puts(temp->address.nick);	

	pthread_mutex_unlock(&ll_mutex);
}

void signalHandler(int sig){
	
	exit(0);
	
	if(interrupt)
		
		return ;
	
	fprintf(stderr, "Interrupt signal received. Closing program\n");
		
	interrupt = 1;	
}
