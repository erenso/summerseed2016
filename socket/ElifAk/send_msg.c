#include "requestModule.h"
#include "responseModule.h"
#include "broadcastModule.h"
#include "listenModule.h"
#include "senderModule.h"
#include "usrModule.h"
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

char * getFullLine(void)
{
	char * line = malloc(100), * linep = line;
	size_t lenmax = 100, len = lenmax;
	int c;
	if(line == NULL)
		return NULL;
	for(;;)
	{
		c = fgetc(stdin);
		if(c == EOF)
			break;
		if(--len == 0)
		{
			len = lenmax;
			char * linen = realloc(linep, lenmax *= 2);
			if(linen == NULL)
			{
				free(linep);
				return NULL;
			}
			line = linen + (line - linep);
			linep = linen;
		}
		if((*line++ = c) == '\n')
			break;
	}
	*line = '\0';
	return linep;
}

int main( int argc, const char* argv[] )
{
	pthread_t tID;

	//process the knocking listener
	pthread_create(&tID,NULL,(void *)send_response,NULL);
	pthread_create(&tID,NULL,(void *)listener,NULL);
	pthread_create(&tID,NULL,(void *)make_request, NULL);

	//process scaning
	//broadcast();

	char command[50];
	printf("Welcome\n>");
	scanf("%s",command);
	while(strcmp(command,"QUIT") != 0)
	{
		if(strcmp(command, "SCAN") == 0)
		{
			broadcast(); //Scan
		}
		else if(strcmp(command, "LIST") == 0)
		{
			printAll();
		}
		else if(strcmp(command, "HELP") == 0)
		{
			printf("\nSCAN:\n\tscan all network to get online users.\n\n");
			printf("\nLIST:\n\tprint all recorded users on the LAN.\n\n");
			printf("\n<username> <message>: send one line message to recorded username.");
			printf("QUIT:\n\tterminate the program.\n");
		}
		else
		{
			if(findUser(command) != NULL)
			{
				char IP[20];
				strcpy(IP, findUser(command));
				char * msg = getFullLine();
				if(msg != NULL)
					sender(IP, msg);
			}
			else
				printf("ERROR! You can use HELP command\n");
		}
		printf(">");
		scanf("%s",command);
	};
	return 0;
}
