%{
#include <stdio.h>
int valos=0;
%}
%option noyywrap
%% 
	
[:digit:]+  { valos++; }
[A-Za-z][A-Za-z0-9]*

%%
int main()
 {
 yylex();
 printf("%d A lexer általi találat: \n",valos);
 return 0;
 } 
