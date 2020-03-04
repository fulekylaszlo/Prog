#include <cstdlib>

int main()
 {
 
 int a;
  //1.Egy egészet vezet be.
 int *b;
  //2.Egy egészre mutató mutatót vezet be.
 int *c = &a;
  //3.Egy egésznek a referenciáját vezeti be.
 int d[5];
  //4.Ez egy egésznek a tömbjét vezeti be.
 int (&e)[5] = d;
  //5.Ez pedig egy egészek tömbjének a referenciáját.
 int **f[5];
  //6.Egy egésznek a tömbjére mutató mutatót vezet be.
 int *g(void);
  //7.Ez egy egészre mutató mutatót visszadó függvényt vezet be.
 int *(*(*h)(void)) = h;
  //8.Ez egy egésznek a muatatójára mutató mutatót visszadó függvényt vezet be.
 int (*(*i)(int))(int, int);
  //9.Ez két egészet kapva, majd egy egészre mutató mutatót visszaadó függvényt vezet be.
 int (*(*j)(int))(int, int) = i;
  //10.Két egészet kapó és egy egészet visszadó függvényre való mutató mutatót vezet be.

 return 0;
 }
