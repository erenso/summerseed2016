#include "requestModule.h"
void make_request()
{
        int s, c , length;
	//int a;
        char request[] = "172.16.5.76,elif";
        struct sockaddr_in client_address;
        length = sizeof(client_address);
        memset(&client_address, 0, length);
        s = listen_socket(10001);
        while(1)
        {
                c = accept(s, (struct sockaddr *) &client_address,&length);
                send(c, request, strlen(request)+1, 0);
                close(c);
        }
        close(s);
}
