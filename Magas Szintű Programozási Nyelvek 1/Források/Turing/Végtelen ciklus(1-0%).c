#include <stdio.h>
#include <unistd.h>

int main ()
 {
 for ( ; ; )
  {
  sleep (1);
  printf("Végtelen ciklus.\n");
  }
 return 0; 
 }
 
