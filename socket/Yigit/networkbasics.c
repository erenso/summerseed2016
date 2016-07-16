//
//
//
//

#include "NetworkHeaders.h"

/*int IPcheck(char * IP) // -1 for not valid
{
    char myIP = *getIP();
    int lenIP = strlen(&myIP);
    
    
    
    return 0;
}*/

int listen_nw(int port)
{
    char msg[MSG_LIMIT];
    int listener, feed, opt = 1;
    
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
   
    struct sockaddr_in listenAddr;
    struct sockaddr_in feedAddr;
    
    listener = socket(AF_INET, SOCK_STREAM, 0);
    
    setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    setsockopt (listener, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
    setsockopt (listener, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout));
    
    if(listener == -1)
    {
        perror("Cannot open listening socket");
        return -1;
    }
    
    listenAddr.sin_family = AF_INET;
    listenAddr.sin_port = htons((uint16_t)port);
    listenAddr.sin_addr.s_addr = INADDR_ANY;
    memset(&(listenAddr.sin_zero), '\0', 8);
    
    if(bind(listener, (struct sockaddr *)&listenAddr, sizeof(struct sockaddr)) == -1)
    {
        perror("Cannot bind listenin socket");
        close(listener);	// close the socket we listened to
        return -1;
    }
    
    if(listen(listener, 5) == -1)
    {
        perror("Cannot listen from port");
        close(listener);
        return -1;
    }
        
    
    feed = accept(listener, (struct sockaddr *)&feedAddr, (socklen_t*)&feedAddr);
    
    if(feed == -1)
    {
        perror("Cannot accept connetion");
        close(feed);
        close(listener);
        return -1;
    }
    
    int index = 0;
    
    while(index != MSG_LIMIT)
    {
        read(feed, &msg[index], 1);
        
        if(msg[index] == '\t')
        {
            for(int j = index; j < MSG_LIMIT; j++)
            {
                msg[j] = '\0';
            }
            break;
        }

        index++;
    }
    
    if (index == MSG_LIMIT)
    {
        printf("Messege is longer then expected. Abandoning...\n");
        return -1;
    }
    
    shutdown(listener, SHUT_RDWR);
    shutdown(feed, SHUT_RDWR);
    close(listener);
    close(feed);

    if (port == PRT_MSG)
    {
        char Nick[NICK_LIMIT];
        char msg_toshow[MAX_MSG];
        int j, k;
        for(j = 0; j < (NICK_LIMIT); j++)
        {
            if(msg[j] == ',')
            {
                for(int i = j; i < (MSG_LIMIT - MAX_MSG); i++)
                {
                    Nick[i] = '\0';
                }
                j++;
                break;
            }
            Nick[j] = msg[j];
        }
        for(k = 0; k < MAX_MSG; k++)
        {
            if(msg[j] == '\0')
            {
                for(int i = k; i < (MAX_MSG); i++)
                {
                    msg_toshow[i] = '\0';
                }
                break;
            }
            msg_toshow[k] = msg[j];
            j++;
        }
        printf("%s: %s\n", Nick, msg_toshow);
    }
    else if(port == PRT_RIS)
    {
        char IP[IP_LIMIT];
        char Nick[NICK_LIMIT];
        int j, k;
        for(j = 0; j < IP_LIMIT; j++)
        {
            if(msg[j] == ',')
            {
                for(int i = j; i < IP_LIMIT; i++)
                {
                    IP[i] = '\0';
                }
                j++;
                break;
            }
            IP[j] = msg[j];
        }
        
    /*    if(IPcheck(IP) == -1)
        {
            printf("Incomming IP address is not valid");
            return -1;
        } */
        
        for(k = 0; k < NICK_LIMIT; k++)
        {
            if(msg[j] == '\0')
            {
                for(int i = k; i < (NICK_LIMIT); i++)
                {
                    Nick[i] = '\0';
                }
                break;
            }
            Nick[k] = msg[j];
            j++;
        }
        FILE * adbk;
        adbk = fopen(ADRSBK, "a");
        fprintf(adbk, "%s,%s\n", Nick, IP);
        fclose(adbk);
    }
    else if(port == PRT_REQ)
    {
        char IP[IP_LIMIT];
        char Nick[NICK_LIMIT];
        int j, k;
        for(j = 0; j < IP_LIMIT; j++)
        {
            if(msg[j] == ',')
            {
                for(int i = j; i < IP_LIMIT; i++)
                {
                    IP[i] = '\0';
                }
                j++;
                break;
            }
            IP[j] = msg[j];
        }
    /*    if(IPcheck(IP) == -1)
        {
            return -1;
        } */
        for(k = 0; k < NICK_LIMIT; k++)
        {
            if(msg[j] == '\0')
            {
                for(int i = k; i < (NICK_LIMIT); i++)
                {
                    Nick[i] = '\0';
                }
                break;
            }
            Nick[k] = msg[j];
            j++;
        }
        
        
        FILE * adbk;
        adbk = fopen(ADRSBK, "a");
        fprintf(adbk, "%s,%s\n", Nick, IP);
        fclose(adbk);
        
        char rtrnmsg[30];
        strcpy(rtrnmsg, getIP());
        unsigned long ji = strlen(rtrnmsg) + jiFIX;
        rtrnmsg[ji] = ',';
        rtrnmsg[ji+1] = 'y';
        rtrnmsg[ji+2] = 's';
        
        send_MSG(PRT_RIS, IP, rtrnmsg, 2);
    }
    
    
    return 0;
}

int send_MSG(int port, char * IP, const char * MSG, int timeoutSec)
{
    
    struct timeval timeout;
    timeout.tv_sec = timeoutSec;
    timeout.tv_usec = 0;
    
    unsigned long msglght = strlen(MSG);
    char sndMSG[msglght + 1];
    strcpy(sndMSG, MSG);
    sndMSG[msglght] = '\t';
    
    int sender;
    
    struct sockaddr_in sendAddr;
    
    
    sender = socket(AF_INET, SOCK_STREAM, 0);
    if(sender == -1)
    {
        perror("Cannot create socket to send");
        return -1;
    }
    
    
    setsockopt (sender, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
    setsockopt (sender, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout));
    
    sendAddr.sin_family = AF_INET;
    sendAddr.sin_port = htons((uint16_t)port);
    sendAddr.sin_addr.s_addr = inet_addr(IP);
    memset(&(sendAddr.sin_zero), '\0', 8);
    
    if(connect(sender, (struct sockaddr *)&sendAddr, sizeof(struct sockaddr)) == -1)
    {
        
        printf("Cannot connect to %s\n", IP);
        perror("Error");
        close(sender);
        return -1;
    }
    
    if(send(sender, sndMSG, strlen(sndMSG), 0) == -1)
    {
        perror("Cannot send messege");
    }
    
    shutdown(sender, SHUT_RDWR);
    close(sender);
    
    return 0;
}