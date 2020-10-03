%{
#include "parser.tab.h"
#include "common.h"
#include <string.h>
#include <limits.h>


char buf[512];
char* p;
%}

%x str
%x comment
%x comment2

%%

\"  p = buf; BEGIN(str);

<str>\" {
    BEGIN(INITIAL);
    *p = '\0';

    strncpy(yylval.sval, buf, 512);
    return(CSTRING); 
}

<str>\n {
    fprintf(stderr, "invalid line field in string");
    exit(1);
}

<str>\\[0-7]{1,3} {
    int result;

    (void)sscanf(yytext + 1, "%o", &result);

    if(result > 0xff) {
        fprintf(stderr, "invalid octal escape sequence\n");
        exit(1);
    }

    *p++ = result;

    if(p - buf >= 512) {
        fprintf(stderr, "overflow c string\n");
        exit(2);
    }
}

<str>\\[0-9]+ {
    fprintf(stderr, "invalid escape sequence\n");
    exit(1);
}

<str>\\n {
    *p++ = '\n';

    if(p - buf >= 512) {
        fprintf(stderr, "overflow c string\n");
        exit(2);
    }
}
<str>\\t {
    *p++ = '\t';

    if(p - buf >= 512) {
        fprintf(stderr, "overflow c string\n");
        exit(2);
    }
}
<str>\\r {
    *p++ = '\r';

    if(p - buf >= 512) {
        fprintf(stderr, "overflow c string\n");
        exit(2);
    }
}
<str>\\b {
    *p++ = '\b';

    if(p - buf >= 512) {
        fprintf(stderr, "overflow c string\n");
        exit(2);
    }
}
<str>\\f {
    *p++ = '\f';

    if(p - buf >= 512) {
        fprintf(stderr, "overflow c string\n");
        exit(2);
    }
}

<str>\\(.|\n) {
    *p++ = yytext[1];

    if(p - buf >= 512) {
        fprintf(stderr, "overflow c string\n");
        exit(2);
    }
}

<str>[^\\\n\"]+ {
    char* yp = yytext;

    while(*yp) {
        *p++ = *yp++;

        if(p - buf >= 512) {
            fprintf(stderr, "overflow c string\n");
            exit(2);
        }
    }
}

"/*"   BEGIN(comment);

<comment>[^*\n]*
<comment>"*"+[^*/\n]*
<comment>\n  gSLine++;
<comment>"*"+"/"    BEGIN(INITIAL);

"//" BEGIN(comment2);

<comment2>[^\n]*
<comment2>\n { gSLine++; BEGIN(INITIAL); }

[ \t\n]+ {
    char* p = yytext;
    while(*p) {
        if(*p == '\n') {
            gSLine++;
        }
        p++;
    }
}
[\*]+ {
    strncpy(yylval.cval, yytext, 128);
    return(POINTER); 
}

[%] {
    strncpy(yylval.cval, yytext, 128);
    return(HEAP); 
}
[=+\-\*\/;\(\)\{\},\.:] { 
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

if {
    strncpy(yylval.cval, yytext, 128);
    return(IF); 
}

else {
    strncpy(yylval.cval, yytext, 128);
    return(ELSE); 
}

true {
    strncpy(yylval.cval, yytext, 128);
    return(TOKEN_TRUE); 
}

false {
    strncpy(yylval.cval, yytext, 128);
    return(TOKEN_FALSE); 
}

extern {
    strncpy(yylval.cval, yytext, 128);
    return(EXTERN); 
}

const {
    strncpy(yylval.cval, yytext, 128);
    return(CONST); 
}

return {
    strncpy(yylval.cval, yytext, 128);
    return(RETURN);
}

[a-zA-_$][a-zA-Z0-9$_]* {
    strncpy(yylval.cval, yytext, 128);
    return(IDENTIFIER); 
}

. { 
    fprintf(stderr, "%s %d: Illegal charcter %c, ignored\n", gSName, gSLine, yytext[0]); 
}

%%
