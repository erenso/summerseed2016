#include "listenModule.h"
#include "userModule.h"
void listener(){
	int s, c, l, r;
	struct sockaddr_in client_address;
	l = sizeof(client_address);
	memset(&client_address, 0, sizeof(client_address));
	s = listen_socket(10002);
	char *message;
	char * name;
	while(1){
		//memset(inbuffer, 0, 512);
		c = accept(s, (struct sockaddr *) &client_address, &l);
		receive_message(c, message);
		name = findName(inet_ntoa(client_address.sin_addr));
		if (r != -1){
			perror("receive");
			close(c);
			return;
		}
		if(name != NULL)
			printf(">%s: %s>",name, message);
		else
			printf(">unknown user: %s>", message);
		fflush(stdout);
		close(c);
	}
	close(s);
}
