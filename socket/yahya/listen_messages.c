#include "netcat.h"

int main(){
    while(1){
        netlisten(10002, 0, 3); // nclisten listens on port 10002
    }
}