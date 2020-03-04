#include<stdio.h>
#include<signal.h>

void jelkezelo(int signo)
 {
 if (signo == SIGINT)
 printf("Működik\n");
 }

int main(void)
 {
 for ( ; ; )
  {
  if(signal(SIGINT, jelkezelo)==SIG_IGN)
  signal(SIGINT, SIG_IGN);
	}
 printf("\nNem működik\n");
 return 0;
 }
