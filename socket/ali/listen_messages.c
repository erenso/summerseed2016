#include "netcat.h"

int main(){
    while(1){
        nclisten(10002, 0, 3); // nclisten listens on port 10002
    }
}