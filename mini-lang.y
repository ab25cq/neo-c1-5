%{
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define outofrange(n) fprintf(stderr, "memory #%d out of range\n", (n));
#define IDENTSIZE 16
typedef struct _identmap{
    char name;
    double value;
} identmap;
identmap imap[IDENTSIZE];
double getvalue(char name);
int identregister(char name,double value);
double it;
%}

%union {
    int ival;
    double dval;
    char cval;
}

%token <ival> INTNUM MEMLOAD MEMSTORE FOR IN TO STEP IF THEN ELSE END EXIT
%token <dval> DOUBLENUM
%token <cval> IDENTIFIER
%type <dval> program block expr term factor ifstmt

%start program

%%
program :                       { $$ = it; }
        | block ';'             { $$ = it = $1; printf("program return = %lf\n", it); }
        | block '\n'            { $$ = it = $1; printf("program return = %lf\n", it); }
        | program block '\n'    { $$ = it = $2; printf("program return = %lf\n", it); }
        | program EXIT '\n'     { $$ = it; printf("program return = %lf\n", it); return 0; }
        ;

block   : expr                  { $$ = $1; }
        | ifstmt                { $$ = $1; }

ifstmt  : IF expr THEN expr END { if ( $2 == 1.0) $$ = $4;
                                  else $$ = -1; }
        ;   

expr    : term                  { $$ = $1; }
        | IDENTIFIER '=' expr   { identregister($1, $3);
                                  $$ = $3; }
        | expr '+' term         { $$ = $1 + $3; }
        | expr '-' term         { $$ = $1 - $3; }
        ;

term    : factor                { $$ = $1; }
        | term '*' factor       { $$ = $1 * $3; }
        | term '/' factor       { $$ = $1 / $3; }
        ;

factor  : INTNUM                { $$ = (double) $1; }
        | DOUBLENUM             { $$ = $1; }
        | IDENTIFIER            { $$ = getvalue($1); }
        | factor IDENTIFIER     { $$ = (double) $1 * getvalue($2); }
        | '(' expr ')'          { $$ = $2; }
        ;

%%
int main(void)
{
    yyparse();
    printf("See you!!");
    return 0;
}

int yyerror(char *msg)
{
    fprintf(stderr, "mini-lang: %s\n", msg);
    return 0;
}

int indexident(char name){
    int i;
    for( i = 0; i < IDENTSIZE; i++){
        if( imap[i].name == name )
            return i;
    }
    return -1;
}

int identregister(char name,double value){
    int i = indexident(name);
    if ( i == -1){
        static int usedi = 0;
        imap[usedi].name = name;
        imap[usedi].value = value;
        usedi++;
    }else{
        imap[i].value = value;
    }
    return 0;
}

double getvalue(char name){
    int i = indexident(name);
    if (i != -1)
        return imap[i].value;
    else
        printf("mini-lang: \'%c\' is not defined\n",name);
    return 0.0;
}
