#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>

int
main (void)
 {
 int xj = 0; 
 int xk = 0; 
 int yj = 0; 
 int yk = 0;
 int mx, my;

 WINDOW *ablak;
 ablak = initscr ();
 noecho ();
 cbreak ();
 nodelay (ablak, true);

 for ( ; ; )
  {
	getmaxyx(ablak, my, mx);
  xj = (xj - 1) % mx;
  xk = (xk + 1) % mx;
  yj = (yj - 1) % my;
  yk = (yk + 1) % my;

  mvprintw (abs (yj + (my - yk)),
  abs (xj + (mx - xk)), "O");

  refresh ();
  usleep (160000);

  } 
 return 0;
}
