

#include "NetworkHeaders.h"

int main()
{
    char input[2048];
    input[0] = '\0';
    
    printf("Welcome to simple chat engine\nInitialising...\n");
    discover();
    pthread_t listeners[2];
    int error = pthread_create(&listeners[0], NULL, listenREQ, input);
    if (error == -1)
    {
        char err[30];
        sprintf(err, "Cannot listen port %d",PRT_REQ);
        perror(err);
        return -1;
    }
    
    error = pthread_create(&listeners[1], NULL, listenMSG, input);
    
    if (error == -1)
    {
        char err[30];
        sprintf(err, "Cannot listen port %d",PRT_MSG);
        perror(err);
        return -1;
    }
    
    void* listenMSG(void* input);
    
    printf("Use QUIT to exit\nSEND to messege send mode\n\n");
    
    while (exitCon(input) != -1)
    {
        scanf("%s", input);
        if(sendCon(input) == 1)
        {
            printf("To: ");
            scanf("%s", input);
            char IPtoSend[30];
            strcpy(IPtoSend, findIP(input));
            if (isSame(IPtoSend, "NOTFOUND") == 0)
            { continue;}             
            printf("Messege: ");
            scanf("%s", input);
            send_MSG(PRT_MSG, IPtoSend, input, 10);
        }
        if(isSame(input, "FIX") == 0)
        {
            fix_add();
        }
    }
    
    usleep(1000);
    pthread_cancel(listeners[0]);
    pthread_cancel(listeners[1]);

    
    return 0;
}
