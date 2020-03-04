#include<stdio.h>

int main()
 {
 int n;
 int x=2;
 int y=3;
     
 int *d=&x;
 int *s=&y;
     
 for(int i=0; i<n && (*d++ = *s++); ++i)
  {
  printf("i=%d,    Változó értéke=%d,  Változó címe/%d\n", i, *d, *s);
  }
 return 0;
 }
