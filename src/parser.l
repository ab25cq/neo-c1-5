%{
#include "parser.tab.h"
#include "common.h"
#include <string.h>
#include <limits.h>
%}

%%
[ \t]+
\n {
    gSLine++;
    return yytext[0];
}
[\*]+ {
    strncpy(yylval.cval, yytext, 128);
    return(POINTER); 
}

[%] {
    strncpy(yylval.cval, yytext, 128);
    return(HEAP); 
}
[=+\-\*\/;\(\)\{\},] { 
    return(yytext[0]); 
}
[0-9]+ { 
    sscanf(yytext, "%d", &yylval.ival);
    return(INTNUM); 
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

[a-zA-_$][a-zA-Z0-9$]* {
    strncpy(yylval.cval, yytext, 128);
    return(IDENTIFIER); 
}

. { 
    fprintf(stderr, "%s %d: Illegal charcter %c, ignored\n", gSName, gSLine, yytext[0]); 
}

%%
