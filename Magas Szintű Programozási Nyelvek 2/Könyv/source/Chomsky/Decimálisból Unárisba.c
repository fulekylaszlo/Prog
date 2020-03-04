#include <stdio.h>

int main(void)
 {
 int a=20;
 int i=0;
 for (i=0 ; i < a; ++i)
  {
	(i % 5) ? printf("|") : printf(" |");
	}
 printf("\n");
 return 0;
 }
