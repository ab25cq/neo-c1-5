%{
#include "mini-lang.tab.h"
#include <string.h>
%}

white       [ \t]
floating    [0-9]+\.[0-9]+
integer     [0-9]+
symbol      [=+\-\^*/();\n]
letter      [a-zA-Z]
other       .

%%
{white}+
{symbol}                { return(yytext[0]); }
{integer}               { sscanf(yytext, "%d", &yylval.ival);
                          return(INTNUM); }
{floating}              { sscanf(yytext, "%lf", &yylval.dval);
                          return(DOUBLENUM); }
{letter}                { yylval.cval = yytext[0];
                          return(IDENTIFIER); }
for                     { return(FOR); }
in                      { return(IN); }
to                      { return(TO); }
step                    { return(STEP); }
if                      { return(IF); }
then                    { return(THEN); }
else                    { return(ELSE); }
end                     { return(END); }
exit                    { return(EXIT); }                     
{other}                 { fprintf(stderr, "Illegal charcter %c, ignored\n", yytext[0]); }

%%
