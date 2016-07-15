#include "get_send_mes.h"

int listenmes (int portno, int opt)
{
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }

    struct timeval timeout;
    timeout.tv_sec = 3;
    timeout.tv_usec = 0;


    if (setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
    {
        close(socket_desc);
        perror("setsockopt(SO_REUSEADDR) failed");
    }

    // if (setsockopt (sock_desc, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0){
    //     perror("setsockopt failed");
    //     close(sock);  
    //     return -1;
    // }

    // if (setsockopt (sock_desc, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0) 
    // {
    //     perror("setsockopt failed");
    //     close(sock); 
    //     return -1;
    // }

    //puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(portno);
     
    //Bind
    if(bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        close(socket_desc);
        return 1;
    }
    //puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        close(client_sock);
        close(socket_desc);
        return 1;
    }
    puts("Connection accepted");

    //Receive a message from client
    int i = 0;
    while(recv(client_sock , &client_message[i] , 1, 0)) 
    {
        if (client_message[i] == '\t')
        {
            client_message[i] == '\0';
            break;
        }
        i++;
    }

    char originalMes[MAXLEN];
    strcpy(originalMes, client_message);

    if (opt == 1) // If sending response option is selected
    {
        char smes[MAXLEN];
        char client_ip [20];
        strcpy(client_ip, strtok(client_message, ","));
        strcpy(smes, "172.16.5.194,hasan");
        sendmes(client_ip, 10001, smes, 2);
    }

    //show the new message
    //puts("+++++++++++++++++++++New Message+++++++++++++++++++");
    puts("+++++++++++++++++++++++++++++++++++++++++++++++++++");
    puts(originalMes);
    puts("+++++++++++++++++++++++++++++++++++++++++++++++++++");
    //Send recv message to the client
    //write(client_sock , "Got it (hasan)" , strlen("Got it (hasan)"));
    puts("\n");
     
    if(read_size == 0)
    {
        puts("Client disconnected\n");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }

    fflush(stdout);
    fflush(stdin);

    close(client_sock);
    close(socket_desc);

    return 0;
}

int sendmes (char ipaddr[], int portno, char mes[], int opt)
{
    int sock;
    struct sockaddr_in server;
    char server_reply[MAXLEN];
     
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    //puts("Socket created");

    struct timeval timeout;
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;

    if (setsockopt (sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0){
        perror("setsockopt failed");
        close(sock);  
        return -1;
    }

    if (setsockopt (sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0) 
    {
        perror("setsockopt failed");
        close(sock); 
        return -1;
    }

    server.sin_addr.s_addr = inet_addr(ipaddr);
    server.sin_family = AF_INET;
    server.sin_port = htons(portno);
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //perror("connect failed. Error");
        close(sock);
        return 0;
    }
     
    //puts("Connected\n");
    strcat(mes,"\t");
     
    //Send some data
    if(send(sock , mes , strlen(mes) , 0) < 0)
    {
        puts("Send failed");
        close(sock);
        return 1;
    }
    else 
    {
        if (opt == 1)
        {
            printf("Request sent to: %s\n", ipaddr);
        }
        else if (opt == 2)
        {
            printf("Response sent to: %s\n", ipaddr);
        }
    }

    close(sock);

    return 0;
}
