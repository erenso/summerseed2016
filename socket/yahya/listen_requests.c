#include "netcat.h"

int main(){
	while(1){
		netlisten(10000, 1, 1); // nclisten listens on port 10000
	}
}
