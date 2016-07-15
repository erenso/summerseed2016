#include "responseModule.h"
#include "soc.h"
void send_response()
{
	int s, c ,a, length, msgLength;
	char response[] = "172.16.5.76,elif";
	struct sockaddr_in client_address;
	//char *message;
	char message[25];
	length = sizeof(client_address);
	memset(&client_address, 0, length);
	//message = (char *)malloc(25);
	//memset(message, 0, 25);
	s = listen_socket(10000);
	while(1)
	{
		c = accept(s, (struct sockaddr *) &client_address,&length);
		if(c != -1)
		{
			msgLength = recv(c, &message, 25, 0);
			printf("Message length: %d", msgLength);
			if(msgLength > 0)
			{
				a = connect_socket(10001, inet_ntoa(client_address.sin_addr));
				send(a, response, strlen(response)+1, 0);
				FILE *dosya;
				dosya = fopen("usrtable.txt", "a");
				fprintf(dosya, "%s\n", message);
				fclose(dosya);
				close(c);
			}
		}
		close(c);
	}
	close(s);
}
