#ifndef USRMOD_H
#define USRMOD_H
typedef struct Users{
	char IP[20];
	char name[20];
} User;
char * findUser(char * name);
char * findName(char * IP);
void printAll();
#endif
