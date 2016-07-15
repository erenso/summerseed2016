#include "responseModule.h"
void make_response()
{
	int s, c, a, l, msgLen;
	char responsePacket[] = "172.16.5.103,ahmet";
	struct sockaddr_in client_address;
	char *message;
	l = sizeof(client_address);
	memset(&client_address, 0, l);
	s = listen_socket(10000);
	while(1){
		c = accept(s, (struct sockaddr *) &client_address,&l);
		if(c != -1){
			msgLen = receive_message(c,message);
			if (msgLen > 0){
				a = connect_socket(10001, inet_ntoa(client_address.sin_addr));
				send(c, responsePacket, strlen(responsePacket)+1, 0);
				FILE *dosya;
				dosya = fopen("userList.txt","a");
				fprintf(dosya, "%s\n", message);
				fclose(dosya);
				close(c);
			}
		}

		close(c);
	}
	close(s);
}
