#include <pthread.h>
#include "get_send_mes.h"

void* send_req (void* req_ip)
{
	char new_ip [30];
	strcpy(new_ip, (char*) req_ip); // getting the ip address
	char mes[20] = "172.16.5.194,hasan";

	sendmes(new_ip, 10000, mes, 1); // sending the request

	return NULL;
}

int main()
{
	pthread_t thr[255];

	char IP [30] = "172.16.5.";
	char IPS [255][30]; // the list of all IPs

	for(int i = 0; i < 255; i++) // appending last digits
		sprintf(IPS[i], "%s%d", IP, i);

	for (int j = 0; j <= 254; j++) // creating threads
		pthread_create(&thr[j], NULL, send_req, (void*)&IPS[j]);

	for (int k = 0; k < 255; k++) // joining all threads
		pthread_join(thr[k], NULL);


	return 0;
}