#include "broadcastModule.h"
#include "usrModule.h"
#include "soc.h"
#define NUM_THREADS 254

void *FUNC_THREAD(void *threadid)
{
	FILE *dosya;
	dosya = fopen("usrtable.txt","w");
	long tid;
	tid = (long)threadid;
	char str[20];
	sprintf(str,"172.16.5.%ld",(tid+1));
	int conn;
	conn = connect_socket(10000,str);
	char *message;
	message = (char *)malloc(30);
	memset(message, 0, 30);
	if (conn != -1)
        {
                send(conn, "172.16.5.76,elif", 16, 0);
                receive_message(conn, message);
                fprintf(dosya,"%s %s\n", str, findName(str));
		printf("%s -> %s\n",str, message);
        }
	close(conn);
	fclose(dosya);
	pthread_exit(NULL);
}

void broadcast()
{
	pthread_t threads[NUM_THREADS];
	int rc;
	int i;
	for( i=0; i < NUM_THREADS; i++ )
	{
		rc = pthread_create(&threads[i], NULL,FUNC_THREAD,(void *)i);
		if (rc)
		{
			printf("Broadcast: unable to create thread, %d\n",rc);
			exit(1);
		}
	}
}
