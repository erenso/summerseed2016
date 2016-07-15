#include "requestModule.h"
void make_request()
{
        int s, c, l;
        char responsePacket[] = "172.16.5.103,ahmet";
        struct sockaddr_in client_address;
        l = sizeof(client_address);
        memset(&client_address, 0, sizeof(client_address));
        s = listen_socket(10001);
        while(1){
                c = accept(s, (struct sockaddr *) &client_address,&l);
                send(c, responsePacket, strlen(responsePacket)+1, 0);
                //FILE *dosya;
                //dosya = fopen("userList.txt","a");
                //fprintf(dosya, "%s\n", message);
                //fclose(dosya);
		close(c);
        }
        close(s);
}

