#include "discoverModule.h"
#include "userModule.h"
#include "nc.h"
#define NUM_THREADS 254
void *FUNC_THREAD(void *threadid){
	FILE *dosya_yaz;
	dosya_yaz = fopen("userList.txt","w");
	long tid;
	tid = (long)threadid;
	char str[20];
	int conn;
	sprintf(str,"172.16.5.%ld",(tid+1));
	char *message;
	message= (char *)malloc(30);
	memset(message, 0, 30);
	conn = connect_socket(10000,str);
	if (conn != -1){
		send(conn, "172.16.5.103,ahmet", 18, 0);
		receive_message(conn, message);
		fprintf(dosya_yaz,"%s %s\n",str, message);
	}
	close(conn);
	fclose(dosya_yaz);
	pthread_exit(NULL);
}

void discover(){
	pthread_t threads[NUM_THREADS];
	int rc;
	int i;
	for( i=0; i < NUM_THREADS; i++ ){
		rc = pthread_create(&threads[i], NULL,FUNC_THREAD,(void *)i);
		if (rc){
			printf("Error:unable to create thread, %d\n",rc);
			exit(1);
		}
	}
}
