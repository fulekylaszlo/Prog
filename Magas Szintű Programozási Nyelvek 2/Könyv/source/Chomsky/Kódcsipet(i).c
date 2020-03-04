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
  if(signal(SIGINT, SIG_IGN)!=SIG_IGN)
  signal(SIGINT, jelkezelo);
  }
 printf("\nNem működik\n");
 return 0;
 }
