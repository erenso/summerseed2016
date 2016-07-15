#include <pthread.h>
#include "get_send_mes.h"

char new_mes[MAXLEN] = "Hasan: ";

void* send_mes (void* req_ip)
{
	char new_ip [30];
	strcpy(new_ip, (char*) req_ip); // getting the ip address

	sendmes(new_ip, 10002, new_mes, 3);

	return NULL;
}

int main()
{
	pthread_t thr[255];

	char IP [30] = "172.16.5.";
	char IPS [255][30];

	for(int i = 0; i < 255; i++)
		sprintf(IPS[i], "%s%d", IP, i);

	char actual_mes[MAXLEN];
	puts("Enter your message");
	fgets(actual_mes, MAXLEN, stdin); // getting the message
	strcat(new_mes,actual_mes);

	for (int j = 0; j <= 254; j++) // creating threads
		pthread_create(&thr[j], NULL, send_mes, (void*)&IPS[j]);

	for (int k = 0; k < 255; k++) // joining all threads
		pthread_join(thr[k], NULL);

	return 0;
}