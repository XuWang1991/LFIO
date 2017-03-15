%option yylineno
%option noyywrap
%option never-interactive
%s PAREN
%s DEFINITION

%{
#include "function.h"
#include <limits.h>
#include <iostream>
#include <sstream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "parse.hh"
%}
IF		:-
CH		&&
IDENTIFIER [a-z][a-zA-Z0-9_']*
NUMBER [0-9][0-9]*
VARIABLE [A-Z][a-zA-Z0-9_']*
NOT [Nn][Oo][Tt]

%%
[ \t\n\r]+	{}		
[,]	{return ',';}
[{]	{return '{';}
[}]	{return '}';}
[(]	{return '(';}
[)]	{return ')';}
[.]	{return '.';}
{CH}	{return CH;}
{IF}	{return IF;}
{NOT}	{return NOT;}
[;]	{return ';';}
{NUMBER} {yylval.s = clone_string(yytext); return NUMBER;}
{IDENTIFIER} { yylval.s = clone_string(yytext); return IDENTIFIER;}
{VARIABLE} {yylval.s = clone_string(yytext); return VARIABLE;}
<<EOF>>  {yyterminate();}

