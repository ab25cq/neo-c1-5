%{
#include "parser.tab.h"
#include "common.h"
#include <string.h>
#include <limits.h>
%}

%%
[ \t]+
[=+\-\*\/;\(\)\{\},] { 
    return(yytext[0]); 
}
[0-9]+ { 
    sscanf(yytext, "%d", &yylval.ival);
    return(INTNUM); 
}
\n {
    gSLine++;
    return yytext[0];
}

void {
    strncpy(yylval.cval, yytext, 128);
    return(VOID); 
}

extern {
    strncpy(yylval.cval, yytext, 128);
    return(EXTERN); 
}

return {
    strncpy(yylval.cval, yytext, 128);
    return(RETURN);
}

[a-zA-Z_$]+ {
    strncpy(yylval.cval, yytext, 128);
    return(IDENTIFIER); 
}

. { 
    fprintf(stderr, "%s %d: Illegal charcter %c, ignored\n", gSName, gSLine, yytext[0]); 
}

%%
