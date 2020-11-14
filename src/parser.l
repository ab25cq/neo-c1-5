%{
#include "parser.tab.h"
#include "common.h"
#include <string.h>
#include <limits.h>

char buf[512];
char* p;

extern int num_struct_generics_types;
char struct_generics_types[GENERICS_TYPES_MAX][VAR_NAME_MAX];
extern int num_function_generics_types;
char function_generics_types[GENERICS_TYPES_MAX][VAR_NAME_MAX];
extern int num_method_generics_types;
char method_generics_types[GENERICS_TYPES_MAX][VAR_NAME_MAX];

BOOL is_type_name(char* name)
{
    char name2[VAR_NAME_MAX];

    get_typedef(name, name2);

    int i;
    for(i=0; i<num_function_generics_types; i++) {
        if(strcmp(name, function_generics_types[i]) == 0) {
            return TRUE;
        }
    }
    for(i=0; i<num_struct_generics_types; i++) {
        if(strcmp(name, struct_generics_types[i]) == 0) {
            return TRUE;
        }
    }
    for(i=0; i<num_method_generics_types; i++) {
        if(strcmp(name, method_generics_types[i]) == 0) {
            return TRUE;
        }
    }

    sNodeType* node_type = create_node_type_with_class_name(name2);

    return node_type != NULL;
}
%}

%option yylineno

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
<comment>\n  
<comment>"*"+"/"    BEGIN(INITIAL);

"//" BEGIN(comment2);

<comment2>[^\n]*
<comment2>\n { BEGIN(INITIAL); }

[ \t]+ {
}

\n {
}

== {
    strncpy(yylval.cval, yytext, 128);
    return(EQEQ); 
}

!= {
    strncpy(yylval.cval, yytext, 128);
    return(NOT_EQ); 
}

"&&" {
    strncpy(yylval.cval, yytext, 128);
    return(ANDAND); 
}

"||" {
    strncpy(yylval.cval, yytext, 128);
    return(OROR); 
}

__attribute__ {
    strncpy(yylval.cval, yytext, 128);
    return(__ATTRIBUTE__); 
}
__nothrow__ {
    strncpy(yylval.cval, yytext, 128);
    return(__NOTHROW__); 
}

__leaf__ {
    strncpy(yylval.cval, yytext, 128);
    return(__LEAF__); 
}

__malloc__ {
    strncpy(yylval.cval, yytext, 128);
    return(__MALLOC__); 
}

__printf__ {
    strncpy(yylval.cval, yytext, 128);
    return(__PRINTF__); 
}

__asm__ {
    strncpy(yylval.cval, yytext, 128);
    return(__ASM__); 
}

__scanf__ {
    strncpy(yylval.cval, yytext, 128);
    return(__SCANF__); 
}


__format__ {
    strncpy(yylval.cval, yytext, 128);
    return(__FORMAT__); 
}

__restrict {
    strncpy(yylval.cval, yytext, 128);
    return(__RESTRICT); 
}

restrict {
    strncpy(yylval.cval, yytext, 128);
    return(__RESTRICT); 
}

\([ \t]*\*  {
    strncpy(yylval.cval, yytext, 128);
    return(FUNCTION_POINTER); 
}

">=" {
    strncpy(yylval.cval, yytext, 128);
    return(GTEQ); 
}

"<=" {
    strncpy(yylval.cval, yytext, 128);
    return(LTEQ); 
}

"::" {
    strncpy(yylval.cval, yytext, 128);
    return(METHOD_MARK); 
}

"<<" {
    strncpy(yylval.cval, yytext, 128);
    return(LSHIFT); 
}

">>" {
    strncpy(yylval.cval, yytext, 128);
    return(RSHIFT); 
}

"++" {
    strncpy(yylval.cval, yytext, 128);
    return(PLUS_PLUS); 
}

"+=" {
    strncpy(yylval.cval, yytext, 128);
    return(PLUS_EQ); 
}

"--" {
    strncpy(yylval.cval, yytext, 128);
    return(MINUS_MINUS); 
}

"-=" {
    strncpy(yylval.cval, yytext, 128);
    return(MINUS_EQ); 
}

"*=" {
    strncpy(yylval.cval, yytext, 128);
    return(MULT_EQ); 
}

"/=" {
    strncpy(yylval.cval, yytext, 128);
    return(DIV_EQ); 
}

"%=" {
    strncpy(yylval.cval, yytext, 128);
    return(MOD_EQ); 
}

"&=" {
    strncpy(yylval.cval, yytext, 128);
    return(AND_EQ); 
}

"^=" {
    strncpy(yylval.cval, yytext, 128);
    return(XOR_EQ); 
}

"|=" {
    strncpy(yylval.cval, yytext, 128);
    return(OR_EQ); 
}

"<<=" {
    strncpy(yylval.cval, yytext, 128);
    return(LSHIFT_EQ); 
}

">>=" {
    strncpy(yylval.cval, yytext, 128);
    return(LSHIFT_EQ); 
}

#[ \t]*error.* {
    strncpy(yylval.cval, yytext, 128);

    return(ERROR);
}

[=+\-\*\/;\(\)\{\},\.:%\[\]\!<>\&\^\|\~\#\?] { 
    return(yytext[0]); 
}


0[0-9]+ {
    long value = strtol(yytext, NULL, 8);
    yylval.ival = value;
    return(INTNUM);
}

0[0-9]+u {
    unsigned long value = strtol(yytext, NULL, 8);
    yylval.ival = value;
    return(INTNUM);
}

0[0-9]+l {
    long value = strtol(yytext, NULL, 8);
    yylval.ival = value;
    return(INTNUM);
}

0[0-9]+ll {
    long long value = strtol(yytext, NULL, 8);
    yylval.ival = value;
    return(INTNUM);
}

0[0-9]+ull {
    unsigned long long value = strtol(yytext, NULL, 8);
    yylval.ival = value;
    return(INTNUM);
}

0x[0-9abcdefABCDEF]+ {
    long value = strtol(yytext, NULL, 16);
    yylval.ival = value;
    return(INTNUM);
}

0x[0-9abcdefABCDEF]+u {
    unsigned long value = strtol(yytext, NULL, 16);
    yylval.ival = value;
    return(INTNUM);
}

0x[0-9abcdefABCDEF]+l {
    long value = strtol(yytext, NULL, 16);
    yylval.ival = value;
    return(INTNUM);
}

0x[0-9abcdefABCDEF]+ll {
    long long value = strtol(yytext, NULL, 16);
    yylval.ival = value;
    return(INTNUM);
}

0x[0-9abcdefABCDEF]+ull {
    unsigned long long value = strtol(yytext, NULL, 16);
    yylval.ival = value;
    return(INTNUM);
}

[0-9]* { 
    sscanf(yytext, "%ld", &yylval.ival);
    return(INTNUM); 
}

[0-9]*u { 
    sscanf(yytext, "%lu", &yylval.ival);
    return(INTNUM); 
}

[0-9]*l { 
    sscanf(yytext, "%ld", &yylval.ival);
    return(INTNUM); 
}

[0-9]*ll { 
    sscanf(yytext, "%ld", &yylval.ival);
    return(INTNUM); 
}

[0-9]*ull { 
    sscanf(yytext, "%lu", &yylval.ival);
    return(INTNUM); 
}

\'.\' {
    sscanf(yytext, "'%c'", &yylval.char_val);
    return(CHARNUM); 
}

\'\\\\' {
    yylval.char_val = '\\';
    return(CHARNUM); 
}

\'\\0' {
    yylval.char_val = 0;
    return(CHARNUM); 
}

\'\\n\' {
    yylval.char_val = '\n';
    return(CHARNUM); 
}

\'\\t\' {
    yylval.char_val = '\t';
    return(CHARNUM); 
}

\'\\r\' {
    yylval.char_val = '\r';
    return(CHARNUM); 
}

\'\\b\' {
    yylval.char_val = '\b';
    return(CHARNUM); 
}

\'\\f\' {
    yylval.char_val = '\f';
    return(CHARNUM); 
}

void {
    strncpy(yylval.cval, yytext, 128);
    return(VOID); 
}

inherit {
    strncpy(yylval.cval, yytext, 128);
    return(INHERIT); 
}

template {
    strncpy(yylval.cval, yytext, 128);
    return(TEMPLATE); 
}

enum {
    strncpy(yylval.cval, yytext, 128);
    return(ENUM); 
}

if {
    strncpy(yylval.cval, yytext, 128);
    return(IF); 
}

else {
    strncpy(yylval.cval, yytext, 128);
    return(ELSE); 
}

lambda {
    strncpy(yylval.cval, yytext, 128);
    return(LAMBDA); 
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

unsigned {
    strncpy(yylval.cval, yytext, 128);
    return(UNSIGNED); 
}

signed {
    strncpy(yylval.cval, yytext, 128);
    return(SIGNED); 
}

register {
    strncpy(yylval.cval, yytext, 128);
    return(REGISTER); 
}

volatile {
    strncpy(yylval.cval, yytext, 128);
    return(VOLATILE); 
}

clone {
    strncpy(yylval.cval, yytext, 128);
    return(CLONE); 
}

static {
    strncpy(yylval.cval, yytext, 128);
    return(STATIC); 
}

inline {
    strncpy(yylval.cval, yytext, 128);
    return(INLINE); 
}
struct {
    strncpy(yylval.cval, yytext, 128);
    return(STRUCT); 
}

union {
    strncpy(yylval.cval, yytext, 128);
    return(UNION); 
}

return {
    strncpy(yylval.cval, yytext, 128);
    return(RETURN);
}

typedef {
    strncpy(yylval.cval, yytext, 128);
    return(TYPEDEF);
}

new {
    strncpy(yylval.cval, yytext, 128);
    return(NEW);
}

for {
    strncpy(yylval.cval, yytext, 128);
    return(FOR);
}

while {
    strncpy(yylval.cval, yytext, 128);
    return(WHILE);
}

do {
    strncpy(yylval.cval, yytext, 128);
    return(DO);
}

switch {
    strncpy(yylval.cval, yytext, 128);
    return(SWITCH);
}

case {
    strncpy(yylval.cval, yytext, 128);
    return(CASE);
}

default {
    strncpy(yylval.cval, yytext, 128);
    return(DEFAULT);
}

break {
    strncpy(yylval.cval, yytext, 128);
    return(BREAK);
}

continue {
    strncpy(yylval.cval, yytext, 128);
    return(CONTINUE);
}

sizeof {
    strncpy(yylval.cval, yytext, 128);
    return(SIZEOF);
}

__extension__ {
}

__pure__ {
    strncpy(yylval.cval, yytext, 128);
    return(__PURE__);
}

__nonnull__ {
    strncpy(yylval.cval, yytext, 128);
    return(__NONNULL__);
}

__mode__ {
    strncpy(yylval.cval, yytext, 128);
    return(__MODE__);
}
__QI__ {
    strncpy(yylval.cval, yytext, 128);
    return(__QI__);
}
__HI__ {
    strncpy(yylval.cval, yytext, 128);
    return(__HI__);
}
__SI__ {
    strncpy(yylval.cval, yytext, 128);
    return(__SI__);
}
__DI__ {
    strncpy(yylval.cval, yytext, 128);
    return(__DI__);
}
__word__ {
    strncpy(yylval.cval, yytext, 128);
    return(__WORD__);
}
__pure__ {
    strncpy(yylval.cval, yytext, 128);
    return(__PURE__);
}

__inline {
    strncpy(yylval.cval, yytext, 128);
    return(INLINE);
}

__inline__ {
    strncpy(yylval.cval, yytext, 128);
    return(INLINE);
}

inline {
    strncpy(yylval.cval, yytext, 128);
    return(INLINE);
}

annotate {
    strncpy(yylval.cval, yytext, 128);
    return(ANNOTATE);
}

__aligned__ {
    strncpy(yylval.cval, yytext, 128);
    return(__ALIGNED__);
}

__alignof__ {
    strncpy(yylval.cval, yytext, 128);
    return(__ALIGNOF__);
}

__signed__ {
    strncpy(yylval.cval, yytext, 128);
    return(SIGNED); 
}

__always_inline__ {
    strncpy(yylval.cval, yytext, 128);
    return(__ALWAYS_INLINE__); 
}

dummy_heap {
    strncpy(yylval.cval, yytext, 128);
    return(DUMMY_HEAP);
}

managed {
    strncpy(yylval.cval, yytext, 128);
    return(MANAGED_TOKEN);
}

[a-zA-Z_][a-zA-Z0-9_]* {
    strncpy(yylval.cval, yytext, 128);

    if(strcmp(yytext, "long") == 0) {
        return(LONG); 
    }
    else if(strcmp(yytext, "short") == 0) {
        return(SHORT); 
    }
    else if(is_type_name(yytext)) {
        return(TYPE_NAME); 
    }
    else {
        return(IDENTIFIER); 
    }
}

. { 
    fprintf(stderr, "%s %d: Illegal charcter %c, ignored\n", gSName, yylineno, yytext[0]); 
}

%%
