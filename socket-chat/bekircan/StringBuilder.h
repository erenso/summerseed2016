#ifndef __STRINGBUILDER_H__
#define __STRINGBUILDER_H__

typedef struct {
	
	int size;
	int capacity;
	char *str;
	
}StringBuilder;

extern int SBinitilize(StringBuilder *s);
extern void SBaddChar(StringBuilder *s, char ch);
extern void SBclear(StringBuilder *s);
extern void SBaddString(StringBuilder *s, const char* str);

#endif
