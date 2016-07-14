#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nc/include/nc.h"

int main(int argc, char *argv[]) {
  
  if(argv[1] && !strcmp(argv[1], "-l")){
    /*
     * Listen port @argv[1]
     */
     
     
    // blocking call
    int r = listen_port(atoi(argv[2]));
    
      if(r == -1){
        exit(1);
      }
  
  }else {
  
    /*
     * Read from stdin and write to @argv[1] : @argv[2]
     */
     //printf("%s", "t");
     if (argc < 3) {
         fprintf(stderr, "usage %s hostname port\n", argv[0]);
         exit(0);
     }
     int r = write_to(argv[1], atoi(argv[2]));
     if(r == -1){
       exit(1);
     }
 
  
  }
  return 0;
}
