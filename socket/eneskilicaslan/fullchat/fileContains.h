#ifndef CHAT_FILECONTAINS_H
#define CHAT_FILECONTAINS_H


#define BUFF_SIZE 25 // buffer size and it specifies max number of character in targer



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>




int search(char theFileName[], char theTarget[]);//searchs target keyword in the file
bool find(char theBuffer[], int theBufferSize, char theTheTarget[], int theTargetSize);
char* intToString(int variable); //converts integer to string
int numberOfPlaces(int value);


#endif //CHAT_FILECONTAINS_H
