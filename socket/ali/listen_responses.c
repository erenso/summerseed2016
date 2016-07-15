#include "netcat.h"

int main(){
    while(1){
        nclisten(10001, 0, 2); // nclisten listens on port 10001
    }
}