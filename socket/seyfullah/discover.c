#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <math.h>
#include <stdlib.h>

void *yaz(void *data)
{
    system(data);
    return NULL;
}

int main(int argc, char *argv[])
{  
	system("gnome-terminal -e ./listen_message");
	system("rm kisiler.txt");;
	pthread_t th1;
	char gonder[100];
	char i2[10];

	for(int i=1;i<255;i++)
	{

		printf("%d\n",i);
		strcat(gonder,"./send 10.38.66.");
		snprintf(i2,10,"%d", i);
		strcat(gonder,i2);
		strcpy(i2,"");
		strcat(gonder," 10000 172.16.5.203,seyfullah/t");
    	pthread_create(&th1, NULL, yaz, gonder);
		sleep(1);
		pthread_cancel(th1);
		strcpy(gonder,"");

	}
	system("exit");
	exit(1);

}
