#include "netcat.h"

int main(int argc, char *argv[] ){
	// parse arguments
	if(strcmp(argv[1], "-l") == 0){
		nclisten(atoi(argv[2]));
	}else{
		char mesaj[AZAMIUZUNLUK];
		scanf("%s", mesaj);
		strcat(mesaj, "\t");
		ncsend(argv[1], atoi(argv[2]), mesaj);
	}
}
