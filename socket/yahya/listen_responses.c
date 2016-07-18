#include "netcat.h"

int main(){
    while(1){
        netlisten(10001, 0, 2); // nclisten listens on port 10001
    }
}