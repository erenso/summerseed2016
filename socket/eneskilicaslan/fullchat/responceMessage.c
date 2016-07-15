//
// Created by parallels on 7/14/16.
//

#include "mainHeader.h"
int responceMessage();


//discover function takes one argument which is i, last part of ip address
int responceMessage()
{
    int sockfd, numbytes;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    while(1)
    {   
        /*we will ask for input here*/
        const char enes[] = "172.16.5.53";

        const char mess[] = "sana mesaj";

        if((rv = getaddrinfo(enes, PORT2, &hints, &servinfo)) != 0) {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
            return 1;
        }

        // loop through all the results and connect to the first we can
        for(p = servinfo; p != NULL; p = p->ai_next) {
            if ((sockfd = socket(p->ai_family, p->ai_socktype,
                                 p->ai_protocol)) == -1) {
                //perror("client: socket");
                continue;
            }

            if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
                close(sockfd);
                //perror("client: connect");
                continue;
            }

            break;
        }

        if (p == NULL) {
            //fprintf(stderr, "discover: failed to connect\n");
            return 2;
        }

        //printf("%s\n", ip );

        inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
                  s, sizeof s);

        freeaddrinfo(servinfo); // all done with this structure

    
        if(send(sockfd, mess, MESSAGE_LEN , 0) == -1)
            perror("send");

    }

    close(sockfd);

    return 0;
}
