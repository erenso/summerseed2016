#include <stdio.h>
#include <stdlib.h>
#include "StringBuilder.h"

#define INITIAL_CAPACITY 10

int resize(StringBuilder *s){
		
	if((s->str = (char*)realloc((void*)s->str, s->capacity*2)) == NULL){
		
		perror("StringBuilder(resize): Memory allocation error");
		return -1;		
	}
	
	s->capacity *= 2;
	
	return 0;
}

int SBinitilize(StringBuilder *s){
	
	s->str = (char*)malloc(sizeof(char)*INITIAL_CAPACITY);
	
	if(s->str == NULL){
		
		perror("StringBuilder(initilize): Memory allocation error");
		return -1;		
	}
	
	s->size=0;
	s->capacity=INITIAL_CAPACITY;
	
	return 0;
}

void SBaddChar(StringBuilder *s, char ch){
	
	if(s->size>=s->capacity-1)
		
		resize(s);
	
	s->str[s->size++] = ch;
	s->str[s->size] = '\0';
}

void SBclear(StringBuilder *s){
	
	if(s->str){
		
		free((void*)s->str);	
		s->str = NULL;
	}
	
	s->size=0;
	s->capacity=0;
}

void SBaddString(StringBuilder *s, const char* str){
	
	int i;
	
	if(str==NULL)
	
		return ;
	
	for(i=0; str[i] != '\0'; ++i)
		
		SBaddChar(s, str[i]);
}

