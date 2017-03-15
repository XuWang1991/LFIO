%{
#include <vector>
#include "function.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
extern int yylineno;

extern int yyparse(void);
extern int yylex(void);
extern char *yytext;

void yyerror(const char* const message)
{
fprintf(stderr,"Line: %d AT %c\nERROR: %s\n",yylineno,yytext[0],message);
printf("Parse error:%s\n", message);
    exit(1);
}

Program lfio;
extern Str_list *termlist;
extern Str_list *predicatelist;
%}

%union{
char* 			s;
class Program           *pro;
class ParseNode		*p;
}

%type <p>	head body sigle_input sigle_output atom sigle_head rule rules input output argulist tail examples example
%token <s>	IDENTIFIER NUMBER IF CH VARIABLE NOT
%type <s>   argument
%type <pro>	program statements

%right '(' '[' '{'
%left  ')' ']' '}'

%%

program :
        statements
        { $$ = $1;}
        ;

statements :
	  statements CH
        { }
        | statements rule '.'
        {  $$ = $1; lfio.add($2); }
        | statements example '.'
        {  $$ = $1; lfio.add($2); }
        |
        { $$ = NULL; }
        ;

example : '{' input ';' output '}'
        {$$=new ParseNode(exam,NULL,$2,$4);
        }
     ;

input   : input ',' sigle_input {$$=new ParseNode(in,NULL,$1,$3);}
        | sigle_input {$$=new ParseNode(in,NULL,NULL,$1);}
        ;

output  : output ',' sigle_output {$$=new ParseNode(out,NULL,$1,$3);
	}
        | sigle_output {$$=new ParseNode(out,NULL,NULL,$1);
	}
        ;

sigle_input : atom 
	{$1->neg=0;$$=$1;}
	| NOT atom 
	{$2->neg=1;$$=$2;}
        ;

sigle_output : atom 
	{$1->neg=0;$$=$1;}
	| NOT atom 
	{$2->neg=1;$$=$2;}
	;



rule :
        head
     {$$=new ParseNode(rule,NULL,$1,NULL);
     }
     | head IF tail
     {$$=new ParseNode(rule,NULL,$1,$3);
     }
     ;




tail :
        tail ',' body
        {$$=new ParseNode(tail,NULL,$1,$3);
	}
        | body
        {$$=new ParseNode(tail,NULL,NULL,$1);
	}
        ;

head :
        atom
     { $$ = $1; }
     ;

body    : atom 
	{$1->neg=0;$$=$1;}
	| NOT atom 
	{$2->neg=1;$$=$2;}
        ;

atom    :  IDENTIFIER '(' argulist ')'
        {$$=new ParseNode(atom,$1,NULL,$3);
        }
        | IDENTIFIER {
	 $$=new ParseNode(atom,$1,NULL,NULL);
	}
        ;


argulist:
         argulist ',' argument
		{$$ = new ParseNode(argu,$3,$1,NULL);
         }
         | argument
         {$$ = new ParseNode(argu,$1,NULL,NULL);
         }
         ;

argument:
	 IDENTIFIER
	{$$=$1;ch *temp=new ch($1);if(termlist->is_subset(temp)==0)termlist->Append(temp);}
	| NUMBER
	{$$=$1;ch *temp=new ch($1);if(termlist->is_subset(temp)==0)termlist->Append(temp);}
        | VARIABLE
        {$$=$1;ch *temp=new ch($1);if(predicatelist->is_subset(temp)==0)predicatelist->Append(temp);}
	;
