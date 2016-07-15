#include "fileContains.h"

int search(char fileName[], char target[])
{
   int fd;
   int i, bytesRead , row = 1 ,  column = 1 , counter = 0;
   int targetLengt = strlen(target); 
   char theChar;

   char* buf = (char *) malloc(BUFF_SIZE + targetLengt - 1 );

   if( (fd = open(fileName, O_RDONLY)) < 0 )
   {        
      perror("Open Failed");
      exit(EXIT_FAILURE);
   }
 
   
   bytesRead = read(fd, buf , BUFF_SIZE);
       
   while( bytesRead > 0)
   {
      for( i=0 ; i< bytesRead; ++i )
      {
         if(buf[i] == '\n')
         {
            ++row;
            column = 0;
         }

         if( find( buf + i , strlen(buf), target, strlen(target) ) )
         {
            ++counter;          
         }

         ++column;
      }     
      
      for(i=0; i<targetLengt - 1; ++i)
         buf[i] = buf[ bytesRead - targetLengt + 1 + i]; 
         
      for(i=0; i<targetLengt - 1; ++i)
      {
         if(buf[i] == '\n')
            --row;
         else
            --column;
      }
     
      bytesRead = read(fd, buf + targetLengt - 1 , BUFF_SIZE); 
      
      if(bytesRead != 0 )
        bytesRead =  bytesRead + targetLengt - 1;
         
   }
   
   free(buf);
   close(fd);
   
   return counter;
}


bool find(char theBuffer[], int theBufferSize, char theTarget[], int targetSize)
{
   int i;
   
   if(targetSize > theBufferSize)
      return false;

   else
      for( i=0; i < targetSize; i++)
         if(theBuffer[i] != theTarget[i])
            return false;

   return true;
}


int numberOfPlaces(int value)
{
   int i= 0;
   
   while(true)
   {
      value = value / 10;
      ++i;
      
      if(value == 0 )
         break;
   }

   return i;
}

char* intToString(int var)
{
   int places = numberOfPlaces(var);
   char* temp = (char *) malloc( places + 1 );
    
   sprintf(temp, "%d", var );
   temp[places] = '\0';
   
   return temp; 
}