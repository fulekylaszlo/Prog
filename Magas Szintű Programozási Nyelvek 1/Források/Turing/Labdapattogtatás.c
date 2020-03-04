#include <stdio.h>
#include <curses.h>
#include <unistd.h>

int
main ( void )
  {
   WINDOW *ablak;
   ablak = initscr ();
   int x = 0;
   int y = 0;
   int xnov = 1;
   int ynov = 1;
   int mx;
   int my;

  for ( ; ; )
    {
     getmaxyx ( ablak, my , mx );
     mvprintw ( y, x, "O" );
     refresh ();
     usleep ( 100000 );
     x = x + xnov;
     y = y + ynov;

     if ( x>=mx-1 )
       { 
        xnov = xnov * -1;
        }
        if ( x<=0 )
	{
	xnov = xnov * -1;
        }
        if ( y<=0 )
	{
	xnov = ynov * -1;
        }
        if ( y>=my-1 )
	{
	ynov = ynov * -1;
        }
    } 
    return 0;
  }
