#include "userModule.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
char * findUser(char * name){
	FILE * dosya;
	dosya = fopen("userList.txt", "r");
	User temp;
	while((fscanf(dosya, "%s", temp.IP) != EOF ) && (fscanf(dosya, "%s", temp.name) != EOF)){
		if(strcmp(temp.name, name) == 0){
			char * returnIP =(char *)
			malloc((strlen(temp.IP)+1) * sizeof(char));
			strcpy(returnIP, temp.IP);
			return returnIP;
		}
	}
	fclose(dosya);
	return NULL;
}

char * findName(char * IP){
	FILE * dosya;
	dosya = fopen("userList.txt", "r");
	User temp;
	while((fscanf(dosya, "%s", temp.IP) != EOF ) && (fscanf(dosya, "%s", temp.name) != EOF)){
		if(strcmp(temp.IP, IP) == 0){
			char *returnName =(char *)
			malloc((strlen(temp.name)+1) * sizeof(char));
			strcpy(returnName, temp.name);
			return returnName;
		}
	}
	fclose(dosya);
	return NULL;
}

void printAll(){
	FILE * dosya;
	dosya = fopen("userList.txt", "r");
	User temp;
	int i=0;
	while((fscanf(dosya, "%s", temp.IP) != EOF ) && (fscanf(dosya, "%s", temp.name) != EOF)){
		printf("%d %s\n",++i, temp.name);
	}
	fclose(dosya);
}
