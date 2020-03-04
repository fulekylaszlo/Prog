#include<stdio.h>

int main()
 {
 int tomb[5];
 
 for(int i=0; i<5; tomb[i] = i++)
  {
   printf("%d %d\n", i, tomb[i]);
  }
 return 0;
 }
