#include <stdio.h>
#include "mainHeader.h"
#include <fcntl.h>


int main() {

    int fd;

    if(( fd = open(FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC)) == -1 ) 
    {
        perror("Failed to open input file");
        return 1;
    }

    close(fd);

    
    int i=1;
    int childpid;

    printf("%s\n", "enes" );

    for(i=1; i < 259; i++)
    {
        if ((childpid = fork()) == 0 && (i < 255) )
        {
            char des[LAN_IP_SIZE];
            snprintf(des, LAN_IP_SIZE, "%s%d",LAN_IP,i);

            const char *destination = des;
            discover(destination, PORT0);

            break;
        }
        else if(childpid == -1)
        {
            perror("FORK NOT OPERATED");
            exit(1);
        }

        if((childpid == 0) && (i == 255) )
            listenRequest();
        
        else if((childpid == 0) && (i == 256))
            listenResponce();
        else if((childpid == 0) && (i == 257))
            listenMessage();
        else if((childpid == 0) && (i == 258))
            responceMessage();


    }

    while(childpid = wait(NULL) )
        if ((childpid == -1) && (errno != EINTR))
            break;

        return 0;
}
