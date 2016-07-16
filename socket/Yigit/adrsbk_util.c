

#include "NetworkHeaders.h"

int exitCon(char * input)
{
    if(input[0] == 'Q')
        if(input[1] == 'U')
            if(input[2] == 'I')
                if(input[3] == 'T')
                    return -1;
    
    return 0;
}

int sendCon(char * input)
{
    if(input[0] == 'S')
        if(input[1] == 'E')
            if(input[2] == 'N')
                if(input[3] == 'D')
                    return 1;
    
    return 0;
}

void cpySTR(char * des, const char * sor)
{

    if (strlen(des) > strlen(sor))
    {
        unsigned long k = strlen(des);
        unsigned long i = strlen(sor);
        int j;
        for (j = 0; j < i; j++)
        {
            des[j] = sor[j];
        }
        for (; j < k; j++)
        {
            des[j] = '\0';
        }
    }
    else
    {
        unsigned long i = strlen(des);
        for (int j = 0; j < i; j++)
        {
            des[j] = sor[j];
        }
    }
}

int isSame(char * str1, char * str2) //-1 diff, 0 same
{
    if(strlen(str1) != strlen(str2))
    {
        return -1;
    }
    unsigned long lmt = strlen(str1);
    for (int j = 0; j < lmt; j++)
    {
        if(str1[j] != str2[j])
        {
            return -1;
        }
    }
    return 0;
}

void swap(char * str1, char * str2)
{
    char temp[78];
    cpySTR(temp, str1);
    cpySTR(str1, str2);
    cpySTR(str2, temp);
}

int whichFirst(char * str1, char * str2)
{
    unsigned long size = strlen(str1);
    for(int j = 0; j < size; j++)
    {
        if(str1[j] > str2[j])
            return 1;
        else if(str2[j] > str1[j])
            return 2;
    }
    return 0;
}

char * giveNick(char * data)
{
    int j;
    char data_nick[48];
    
    for (j = 0; j < 48; j++)
    {
        if(data[j] == ',')
        {
            for (int i = j; i < 49; i++)
            {
                data_nick[i] = '\0';
            }
            break;
        }
        if(j == 47)
        {
            printf("Unvalid format found at Address book use please fix it");
            continue;
        }
        data_nick[j] = data[j];
    }
    return data_nick;
}

void fix_add()
{
    FILE * ab;
    ab = fopen(ADRSBK, "r");
    rewind(ab);
    char ab_hold[ABSIZE][78];
    char rd[78];
    int ad_count = 0;
    for(int j = 0; 1; j++)
    {
        if(feof(ab) != 0)
        {
            break;
        }
        fscanf(ab, "%s", rd);
        *ab_hold[j] = *rd;
        ad_count++;
    }
    fclose(ab);
    int change = 1;
    for(int j = 0; j < ad_count; j++)
    {
        if (change == 0)
        {
            break;
        }
        else
        {
            change = 0;
        }
        for(int i = 0; i < (ad_count - 1); i++)
        {
            if (whichFirst(ab_hold[i+1], ab_hold[i]) == 1)
                {
                    swap(ab_hold[i+1], ab_hold[i]);
                    change = 1;
                }
        }
    }
    char writeEN[ABSIZE];
    writeEN[0] = '1';
    int j;
    for(j = 1; j < ad_count; j++)
    {
        /*if(IPcheck(ab_hold[j] == -1))
        {
             writeEN[j] = '0';
             continue;
        }*/
        if(isSame(giveNick(ab_hold[j]), giveNick(ab_hold[j-1])) == 0)
        {
            writeEN[j] = '0';
        }
        else
            writeEN[j] = '1';
    }
    for(; j < ABSIZE; j++)
    {
        writeEN[j] = '0';
    }
    
    ab = fopen(ADRSBK, "w");
    
    for(int k = 0; k < ad_count; k++)
    {
        if(writeEN[k] == 1)
        {
            fprintf(ab, "%s", ab_hold[k]);
        }
    }
    
    fclose(ab);
}

char * findIP(char * nick)
{
    char * IP[30];
    FILE * ab;
    ab = fopen(ADRSBK, "r");
    rewind(ab);
    
    char * data[78];
    
    while(1)
    {
        if(feof(ab) != 0)
        {
            printf("%s cannot found", nick);
            char * hold = "NOTFOUND\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
            strcpy(*IP, hold);
            break;
        }
        fscanf(ab, "%s", *data);
        char data_nick[48];
        int j;
        for (j = 0; j < 48; j++)
        {
            if(*data[j] == ',')
            {
                for (int i = j; i < 49; i++)
                {
                    data_nick[i] = '\0';
                }
                break;
            }
            if(j == 47)
            {
                printf("Unvalid format found at Address book use please fix it");
                continue;
            }
            data_nick[j] = *data[j];
        }
        if(isSame(data_nick, nick) == -1)
        {
            continue;
        }
        for(int k = 0; k < 30; k++)
        {
            j++;
            if(*data[j] == '\0')
            {
                for (int i = k; i < 30; i++)
                {
                    IP[i] = '\0';
                }
                break;
            }
            if(j == 29)
            {
                printf("Unvalid format found at Address book use please fix it");
                continue;
            }
            IP[k] = data[j];
        }
    }
    
    fclose(ab);
    return *IP;
}