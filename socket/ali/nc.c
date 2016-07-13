#include "netcat.h"

int main(int argc, char *argv[] ){
	// parse arguments
	if(strcmp(argv[1], "-l") == 0){	// if second argument is -l, then listen port, which is third argument
 		nclisten(atoi(argv[2]));
	}else{
		char message[MAX_PACKET_LENGTH+1];	// if not, create a new message
		fgets(message, MAX_PACKET_LENGTH, stdin);	// I use fgets to get message here, scanf doesn't work
		ncsend(argv[1], atoi(argv[2]), message);	// send the message to desired IP
	}
}
