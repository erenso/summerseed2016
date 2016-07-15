//
// Created by parallels on 7/14/16.
//

#include "mainHeader.h"
#include "fileContains.h"

typedef struct {

    int socketFd;

} threadArgument;


int listenResponce()
{
    int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    pthread_t requestThread;
    int iret;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    //here we are listening port 10000 (nc -l 10000)
    if ((rv = getaddrinfo(NULL, PORT1, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                       sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if(p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if(listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size);
        threadArgument *args = malloc(sizeof *args);
        args->socketFd = new_fd;

        pthread_t myThread;

        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
                  get_in_addr((struct sockaddr *) &their_addr),
                  s, sizeof s);

        printf("server: got connection from %s-----\n", s);

        //thread part starts here
        iret = pthread_create(&myThread, NULL, listenResponceThread, args);

        if (iret) {
            fprintf(stderr, "Error - pthread_create() return code: %d\n", iret);
            exit(EXIT_FAILURE);
        }

        pthread_join(myThread, NULL);
        close(new_fd);  // parent doesn't need this
    }

    return 0;
}


void * listenResponceThread( void *ptr )
{
    threadArgument *actual_args = ptr;
    char readed;
    char gotMessage[3200];
    int new_fd = actual_args->socketFd;
    int counter = 0;

    //printf("%s\n", );
    recv(new_fd, &readed, 1, 0);

    /*receive part */
    while(readed != '\n')
    {
        gotMessage[counter] = readed;
        counter++;

        if((recv(new_fd, &readed, 1, 0)) == -1) {
            perror("recv");
            exit(1);
        }
    }

    gotMessage[counter] = '\0';
   // printf("%s\n", gotMessage);

    const char s[2] = ",";
    char *ip;
    char *nick;

    /* get the first token */
    ip   = strtok(gotMessage, s);
    nick = strtok(NULL, s);
    printf("%s\n", "YAZDIMM" );
    if(search(FILE_NAME, ip) == 0  && search(FILE_NAME, nick) == 0)
    {
    	int fd;

    	printf("%s(%s) is ready to chat\n",nick ,ip);

    	if(( fd = open(FILE_NAME, O_WRONLY |  O_APPEND )) == -1 ) 
    	{
	        perror("Failed to open input file");	       
	    }

	    write(fd, ip, strlen(ip));
	    write(fd, ",", 1);
	   	write(fd, nick, strlen(nick));
	   	write(fd, "\n",1);
    }


    free(actual_args);
    return 0;
}