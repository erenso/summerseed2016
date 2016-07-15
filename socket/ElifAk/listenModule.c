#include "listenModule.h"
#include "usrModule.h"
void listener()
{
	int s, c, l, r;
	struct sockaddr_in client_address;
	l = sizeof(client_address);
	memset(&client_address, 0, sizeof(client_address));
	s = listen_socket(10002);
	char *message;
	char * name;
	while(1)
	{
		//memset(inbuffer, 0, 512);
		c = accept(s, (struct sockaddr *) &client_address, &l);
		//r = receive_message(c, message);
		name = findName(inet_ntoa(client_address.sin_addr));
		r = receive_message(c, name);
		if(r == -1){
			perror("receive");
			close(c);
			return;
		}
		//name = findName(inet_ntoa(client_address.sin_addr));
		//if(name != NULL)
		//	printf("%s: %s>",name, message);
		//else
		//	printf(">Unknown user: %s>", message);
		fflush(stdout);
		close(c);
	}
	close(s);
}
