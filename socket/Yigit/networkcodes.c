

#include "NetworkHeaders.h"

int findTrdDot(const char * str)
{
    int dotcount = 0;
    for(int j = 0; j < strlen(str); j++)
    {
        if(str[j] == '.')
        {
            dotcount++;
        }
        if(dotcount == 3)
        {
            return j;
        }
        
    }
    return -1;
}

void* sendReq(void* ip)
{
    char MSG[50];
    
    strcpy(MSG, getIP());
    unsigned long ji = strlen(MSG) + jiFIX;
    MSG[ji] = ',';
    MSG[ji+1] = 'y';
    MSG[ji+2] = 's';
    send_MSG(PRT_REQ, ip, MSG, 1);
    return NULL;
}

void* listenRespons(void* input)
{
    while(exitCon(input) != -1)
    {
    int port = PRT_RIS;
    listen_nw(port);
    }
    return NULL;
}

void discover()
{
    char myIP[30];
    strcpy(myIP, getIP());
    char cmmIP[30];
    strcpy(cmmIP, getIP());
    int locDot = 1 + findTrdDot(cmmIP);
    for(int j = locDot; j < 30; j++)
    {
        cmmIP[j] = '\0';
    }
    
    char hold[4];
    
    cpySTR(hold, "CONT");
    pthread_t listn;
    int error = pthread_create(&listn,NULL,listenRespons,(void*)&hold);
    if(error == -1)
    {
        perror("Cannot listen discovery");
        return;
    }
    
    char sndIP[256][30];
    
    for(int i = 2; i < 256; i++)
    {
        sprintf(sndIP[i], "%s%d", cmmIP, i);
    }
    
    pthread_t sendDis[256];
    
    for(int j = 2; j < 256; j++)
    {
        error = pthread_create(&sendDis[j],NULL,sendReq,(void*)&sndIP[j]);
        if(error == -1)
        {
            printf("Request to %s wont send due to thread error",sndIP[j]);
        }
        
    }
    for (int i = 0; i < 256; i++)
    {
       // pthread_join(sendDis[i], NULL);
        pthread_cancel(sendDis[i]);
    }
    
    usleep(500);
    char * temp = "QUIT";
 
    
    cpySTR(hold, temp);
    usleep(500);
    pthread_cancel(listn);
    fix_add();
}

void* listenMSG(void* input)
{
    while (exitCon(input) != -1)
    {
        listen_nw(PRT_MSG);
    }
    
    return NULL;
}

void* listenREQ(void* input)
{
    while (exitCon(input) != -1)
    {
        listen_nw(PRT_REQ);
        fix_add();
    }
    
    return NULL;
}