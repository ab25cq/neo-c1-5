%{
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "common.h"

unsigned int it;
unsigned int prev_block[BLOCK_NEST_MAX];
int num_prev_block = 0;
unsigned int block;
BOOL var_arg;
unsigned int func_params;
unsigned int params;
extern int yyerror(char *msg);
extern int yylex();
sCompileInfo cinfo;
unsigned int elif_exps[ELIF_NUM_MAX];
unsigned int elif_blocks[ELIF_NUM_MAX];
int elif_num;
unsigned int fields;
char variable_names[VAR_NAME_MAX][128];
int num_variable_names = 0;
char variable_name[VAR_NAME_MAX];
char type_params[VAR_NAME_MAX];
int num_struct_generics_types = 0;
char struct_generics_types[GENERICS_TYPES_MAX][VAR_NAME_MAX];
int num_function_generics_types = 0;
char function_generics_types[GENERICS_TYPES_MAX][VAR_NAME_MAX];
int num_method_generics_types = 0;
char method_generics_types[GENERICS_TYPES_MAX][VAR_NAME_MAX];
unsigned int object;
BOOL inline_ = FALSE;
BOOL static_ = FALSE;
BOOL inherit_ = FALSE;
int enum_number = 0;
int array_index_num_dimention = 0;
unsigned int array_index_index_node[ARRAY_DIMENTION_MAX];
int num_array_value;
unsigned int array_values[INIT_ARRAY_MAX];
unsigned int num_switch_expression;
unsigned int switch_expression[SWITCH_STASTMENT_NODE_MAX];
unsigned int fun_node;
sVarTable* gLVTable;
%}

%union {
    int ival;
    char char_val;
    unsigned int node;
    char cval[128];
    char sval[512];
    int rval;
}

%token <ival> INTNUM 
%token <char_val> CHARNUM 
%token <cval> IDENTIFIER
%token <cval> TYPE_NAME
%token <cval> LONG
%token <cval> SHORT
%token <sval> CSTRING
%token <cval> VOID
%token <cval> IF
%token <cval> ELSE
%token <cval> EXTERN
%token <cval> RETURN
%token <cval> TYPEDEF
%token <cval> TOKEN_TRUE
%token <cval> TOKEN_FALSE
%token <cval> CONST
%token <cval> UNSIGNED
%token <cval> SIGNED
%token <cval> REGISTER
%token <cval> VOLATILE
%token <cval> STATIC
%token <cval> NEW
%token <cval> CLONE
%token <cval> INLINE
%token <cval> STRUCT
%token <cval> UNION
%token <cval> EQEQ
%token <cval> NOT_EQ
%token <cval> ANDAND
%token <cval> OROR
%token <cval> LAMBDA
%token <cval> TEMPLATE
%token <cval> ENUM
%token <cval> INHERIT
%token <cval> METHOD_MARK
%token <cval> PLUS_PLUS
%token <cval> PLUS_EQ
%token <cval> MINUS_MINUS
%token <cval> MINUS_EQ
%token <cval> MULT_EQ
%token <cval> DIV_EQ
%token <cval> MOD_EQ
%token <cval> AND_EQ
%token <cval> XOR_EQ
%token <cval> OR_EQ
%token <cval> LSHIFT_EQ
%token <cval> RSHIFT_EQ
%token <cval> FUNCTION_POINTER
%token <cval> FOR
%token <cval> WHILE
%token <cval> DO
%token <cval> SWITCH
%token <cval> CASE
%token <cval> BREAK
%token <cval> CONTINUE
%token <cval> DEFAULT
%token <cval> SIZEOF
%type <cval> type 
%type <cval> type_name
%type <cval> type_attribute
%type <cval> type_and_variable_name
%type <cval> type_params
%type <cval> generics_types 
%type <cval> function_generics_types 
%type <cval> function_struct_type_name 
%type <cval> pointer
%type <cval> array_type
%type <cval> const_array_type
%type <node> program function block function_block block_end statment node function_params exp comma_exp params elif_statment prepare_elif_statment struct_ fields union_ method_generics_types global_variable enum_ enum_fields array_index array_value switch_block case_statment after_return_case_statment cstring_array_value2 sub_array sub_array_init source_point_macro typedef_ function_params_end;

%left OROR
%left ANDAND
%left '|'
%left '^'
%left '&'
%left EQEQ NOT_EQ 
%left '<' '>' GTEQ LTEQ
%left LSHIFT RSHIFT
%left '+' '-'
%left '*' '/' '%'
%left '!' '~'

%start program

%%

source_point_macro: '#' INTNUM CSTRING {
        xstrncpy(gSName, $3, PATH_MAX);
        gSLine = $2;
        }
        | '#' INTNUM CSTRING INTNUM {
        xstrncpy(gSName, $3, PATH_MAX);
        gSLine = $2;
        }
        | '#' INTNUM CSTRING INTNUM INTNUM INTNUM {
        xstrncpy(gSName, $3, PATH_MAX);
        gSLine = $2;
        }
        | '#' INTNUM CSTRING INTNUM INTNUM {
        xstrncpy(gSName, $3, PATH_MAX);
        gSLine = $2;
        }
        ;

program:
        source_point_macro {
        }
        |
        function {
            $$ = compile($1, &cinfo);
        }
        | global_variable {
            $$ = compile($1, &cinfo);
        }
        | typedef_ {
            $$ = compile($1, &cinfo);
        }
        | struct_ {
            $$ = compile($1, &cinfo);
        }
        | union_ {
            $$ = compile($1, &cinfo);
        }
        | enum_ {
        }
        | program source_point_macro {
        }
        | program function {
            $$ = compile($2, &cinfo);
        }
        | program global_variable {
            $$ = compile($2, &cinfo);
        }
        | program struct_ {
            $$ = compile($2, &cinfo);
        }
        | program union_ {
            $$ = compile($2, &cinfo);
        }
        | program enum_ {
        }
        | program typedef_ {
            $$ = compile($2, &cinfo);
        }
        ;

type:
    type_attribute {
        if(strcmp($1, "long ") == 0) {
            xstrncpy($$, "long", VAR_NAME_MAX);
        }
        else if(strcmp($1, "shor ") == 0) {
            xstrncpy($$, "short", VAR_NAME_MAX);
        }
        else if(strcmp($1, "unsigned ") == 0) {
            xstrncpy($$, "unsigned int", VAR_NAME_MAX);
        }
        else if(strcmp($1, "singed ") == 0) {
            xstrncpy($$, "singed int", VAR_NAME_MAX);
        }
        else {
            fprintf(stderr, "invalid type name (%s)\n", $1);
            exit(1);
        }
    }
    | type_attribute pointer {
        if(strcmp($1, "long ") == 0) {
            xstrncpy($$, "long", VAR_NAME_MAX);
            xstrncat($$, $2, VAR_NAME_MAX);
        }
        else if(strcmp($1, "shor ") == 0) {
            xstrncpy($$, "short", VAR_NAME_MAX);
            xstrncat($$, $2, VAR_NAME_MAX);
        }
        else if(strcmp($1, "unsigned ") == 0) {
            xstrncpy($$, "unsigned int", VAR_NAME_MAX);
            xstrncat($$, $2, VAR_NAME_MAX);
        }
        else if(strcmp($1, "singed ") == 0) {
            xstrncpy($$, "singed int", VAR_NAME_MAX);
            xstrncat($$, $2, VAR_NAME_MAX);
        }
        else {
            fprintf(stderr, "invalid type name (%s)\n", $1);
            exit(1);
        }
    }
    | type_attribute pointer '%' {
        if(strcmp($1, "long ") == 0) {
            xstrncpy($$, "long", VAR_NAME_MAX);
            xstrncat($$, $2, VAR_NAME_MAX);
            xstrncat($$, "%", VAR_NAME_MAX);
        }
        else if(strcmp($1, "shor ") == 0) {
            xstrncpy($$, "short", VAR_NAME_MAX);
            xstrncat($$, $2, VAR_NAME_MAX);
            xstrncat($$, "%", VAR_NAME_MAX);
        }
        else if(strcmp($1, "unsigned ") == 0) {
            xstrncpy($$, "unsigned int", VAR_NAME_MAX);
            xstrncat($$, $2, VAR_NAME_MAX);
            xstrncat($$, "%", VAR_NAME_MAX);
        }
        else if(strcmp($1, "singed ") == 0) {
            xstrncpy($$, "singed int", VAR_NAME_MAX);
            xstrncat($$, $2, VAR_NAME_MAX);
            xstrncat($$, "%", VAR_NAME_MAX);
        }
        else {
            fprintf(stderr, "invalid type name (%s)\n", $1);
            exit(1);
        }
    }
    | type_attribute type_name {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncat($$, $2, VAR_NAME_MAX);
    }
    | type_attribute type_name pointer {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncat($$, $2, VAR_NAME_MAX);
        xstrncat($$, $3, VAR_NAME_MAX);
    }
    | type_attribute type_name pointer '%' {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncat($$, $2, VAR_NAME_MAX);
        xstrncat($$, $3, VAR_NAME_MAX);
        xstrncat($$, "%", VAR_NAME_MAX);
    }
    | type_name {
        xstrncpy($$, $1, VAR_NAME_MAX);
    }
    | type_name pointer {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncat($$, $2, VAR_NAME_MAX);
    }
    | type_name pointer '%' {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncat($$, $2, VAR_NAME_MAX);
        xstrncat($$, "%", VAR_NAME_MAX);
    }
    | STRUCT '{' fields '}' {
            static int anonyomous_struct_num = 0;
            char buf[VAR_NAME_MAX];
            snprintf(buf, VAR_NAME_MAX, "anonmous_struct%d", anonyomous_struct_num);
            anonyomous_struct_num++;
            char* struct_name = buf;
            unsigned int fields = $3;
            BOOL anonymous = TRUE;
            BOOL generics = FALSE;

            unsigned int node = sNodeTree_create_struct(struct_name, fields, generics, anonymous, gSName, gSLine);

            compile(node, &cinfo);

            xstrncpy($$, buf, VAR_NAME_MAX);
    }
    | UNION '{' fields '}' {
            static int anonyomous_union_num = 0;
            char buf[VAR_NAME_MAX];
           
            snprintf(buf, VAR_NAME_MAX, "anonmous_union%d", anonyomous_union_num);
            anonyomous_union_num++;
            char* union_name = buf;
            unsigned int fields = $3;
            BOOL anonymous = TRUE;

            unsigned int node = sNodeTree_create_union(union_name, fields, anonymous, gSName, gSLine);

            compile(node, &cinfo);

            xstrncpy($$, buf, VAR_NAME_MAX);
    }
    ;

pointer: 
    '*' {
        xstrncpy($$, "*", VAR_NAME_MAX);
    }
    | pointer '*' {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncat($$, "*", VAR_NAME_MAX);
    }
    ;

type_attribute: 
    LONG {
        xstrncpy($$, "long ", VAR_NAME_MAX); 
        inline_ = FALSE;
        static_ = FALSE;
        inherit_ = FALSE;
    }
    | SHORT {
        xstrncpy($$, "short ", VAR_NAME_MAX); 
        inline_ = FALSE;
        static_ = FALSE;
        inherit_ = FALSE;
    }
    | CONST {
        xstrncpy($$, "const ", VAR_NAME_MAX); 
        inline_ = FALSE;
        static_ = FALSE;
        inherit_ = FALSE;
    }
    | UNSIGNED {
        xstrncpy($$, "unsigned ", VAR_NAME_MAX); 
        inline_ = FALSE;
        static_ = FALSE;
        inherit_ = FALSE;
    }
    | SIGNED {
        xstrncpy($$, "signed ", VAR_NAME_MAX); 
        inline_ = FALSE;
        static_ = FALSE;
        inherit_ = FALSE;
    }
    | REGISTER {
        xstrncpy($$, "regisster ", VAR_NAME_MAX); 
        inline_ = FALSE;
        static_ = FALSE;
        inherit_ = FALSE;
    }
    | STATIC {
        xstrncpy($$, "static ", VAR_NAME_MAX); 
        static_ = TRUE;
        inline_ = FALSE;
        static_ = FALSE;
        inherit_ = FALSE;
    }
    | INLINE {
        xstrncpy($$, "", VAR_NAME_MAX); 
        inline_ = TRUE;
        static_ = FALSE;
        inherit_ = FALSE;
    }
    | INHERIT {
        xstrncpy($$, "", VAR_NAME_MAX); 
        inherit_ = TRUE;
        inline_ = FALSE;
        static_ = FALSE;
    }
    | type_attribute LONG {
        xstrncpy($$, $1, VAR_NAME_MAX); 
        xstrncat($$, "long ", VAR_NAME_MAX); 
    }
    | type_attribute SHORT {
        xstrncpy($$, $1, VAR_NAME_MAX); 
        xstrncat($$, "short ", VAR_NAME_MAX); 
    }
    | type_attribute CONST {
        xstrncpy($$, $1, VAR_NAME_MAX); 
        xstrncat($$, "const ", VAR_NAME_MAX); 
    }
    | type_attribute UNSIGNED {
        xstrncpy($$, $1, VAR_NAME_MAX); 
        xstrncat($$, "unsigned ", VAR_NAME_MAX); 
    }
    | type_attribute SIGNED {
        xstrncpy($$, $1, VAR_NAME_MAX); 
        xstrncat($$, "signed ", VAR_NAME_MAX); 
    }
    | type_attribute REGISTER {
        xstrncpy($$, $1, VAR_NAME_MAX); 
        xstrncat($$, "regisster ", VAR_NAME_MAX); 
    }
    | type_attribute STATIC {
        xstrncpy($$, $1, VAR_NAME_MAX); 
        xstrncat($$, "static ", VAR_NAME_MAX); 
        static_ = TRUE;
    }
    | type_attribute INLINE {
        xstrncpy($$, $1, VAR_NAME_MAX); 
        inline_ = TRUE;
    }
    | type_attribute INHERIT {
        xstrncpy($$, $1, VAR_NAME_MAX); 
        inherit_ = TRUE;
    }
    ;

type_name: 
    TYPE_NAME {
        char type_name[VAR_NAME_MAX];
        get_typedef($1, type_name);

        int i;
        for(i=0; i<num_function_generics_types; i++) {
            if(strcmp(type_name, function_generics_types[i]) == 0) {
                char buf[VAR_NAME_MAX];
                snprintf(buf, VAR_NAME_MAX, "generics%d", i);
                xstrncpy(type_name, buf, VAR_NAME_MAX);
            }
        }
        for(i=0; i<num_struct_generics_types; i++) {
            if(strcmp(type_name, struct_generics_types[i]) == 0) {
                char buf[VAR_NAME_MAX];
                snprintf(buf, VAR_NAME_MAX, "generics%d", i);
                xstrncpy(type_name, buf, VAR_NAME_MAX);
            }
        }
        for(i=0; i<num_method_generics_types; i++) {
            if(strcmp(type_name, method_generics_types[i]) == 0) {
                char buf[VAR_NAME_MAX];
                snprintf(buf, VAR_NAME_MAX, "mgenerics%d", i);
                xstrncpy(type_name, buf, VAR_NAME_MAX);
            }
        }

        xstrncpy($$, type_name, VAR_NAME_MAX);
    }
    | TYPE_NAME '!' '<' generics_types '>' {
        char type_name[VAR_NAME_MAX];
        get_typedef($1, type_name);

        int i;
        for(i=0; i<num_function_generics_types; i++) {
            if(strcmp(type_name, function_generics_types[i]) == 0) {
                char buf[VAR_NAME_MAX];
                snprintf(buf, VAR_NAME_MAX, "generics%d", i);
                xstrncpy(type_name, buf, VAR_NAME_MAX);
            }
        }
        for(i=0; i<num_struct_generics_types; i++) {
            if(strcmp(type_name, struct_generics_types[i]) == 0) {
                char buf[VAR_NAME_MAX];
                snprintf(buf, VAR_NAME_MAX, "generics%d", i);
                xstrncpy(type_name, buf, VAR_NAME_MAX);
            }
        }
        for(i=0; i<num_method_generics_types; i++) {
            if(strcmp(type_name, method_generics_types[i]) == 0) {
                char buf[VAR_NAME_MAX];
                snprintf(buf, VAR_NAME_MAX, "mgenerics%d", i);
                xstrncpy(type_name, buf, VAR_NAME_MAX);
            }
        }

        xstrncat(type_name, "<", VAR_NAME_MAX);
        xstrncat(type_name, $4, VAR_NAME_MAX);
        xstrncat(type_name, ">", VAR_NAME_MAX);

        xstrncpy($$, type_name, VAR_NAME_MAX);
    }
/*
    | LONG {
        xstrncpy($$, "long",  VAR_NAME_MAX);
    }
    | SHORT {
        xstrncpy($$, "short",  VAR_NAME_MAX);
    }
*/
    | VOID {
        xstrncpy($$, "void",  VAR_NAME_MAX);
    }
    ;

typedef_: TYPEDEF type IDENTIFIER ';' {
        char* name = $3;
        char* type_name = $2;
        $$ = sNodeTree_create_typedef(name, type_name, gSName, gSLine);
    }
    | TYPEDEF type TYPE_NAME ';' {
        char* name = $3;
        char* type_name = $2;
        $$ = sNodeTree_create_typedef(name, type_name, gSName, gSLine);
    }
    ;

generics_types: type {
        char type_name[VAR_NAME_MAX];
        get_typedef($1, type_name);

        xstrncpy($$, type_name, VAR_NAME_MAX);
    }
    | generics_types type {
        char type_name[VAR_NAME_MAX];
        get_typedef($2, type_name);

        xstrncpy($$, ",", VAR_NAME_MAX);
        xstrncpy($$, type_name, VAR_NAME_MAX);
    }
    ;

type_and_variable_name: 
    type IDENTIFIER {
        char type_name[VAR_NAME_MAX];

        xstrncpy(type_name, $1, VAR_NAME_MAX);
    
        xstrncpy($$, type_name, VAR_NAME_MAX);
        xstrncpy(variable_names[num_variable_names++], $2, VAR_NAME_MAX);
    }
    | type IDENTIFIER array_type {
        char type_name[VAR_NAME_MAX];

        xstrncpy(type_name, $1, VAR_NAME_MAX);
        xstrncat(type_name, $3, VAR_NAME_MAX);
    
        xstrncpy($$, type_name, VAR_NAME_MAX);
        xstrncpy(variable_names[num_variable_names++], $2, VAR_NAME_MAX);
    }
    | type IDENTIFIER const_array_type {
        char type_name[VAR_NAME_MAX];

        xstrncpy(type_name, $1, VAR_NAME_MAX);
        xstrncat(type_name, $3, VAR_NAME_MAX);

        xstrncpy($$, type_name, VAR_NAME_MAX);
        xstrncpy(variable_names[num_variable_names++], $2, VAR_NAME_MAX);
    }
    | type IDENTIFIER ':' INTNUM {
        char type_name[VAR_NAME_MAX];

        xstrncpy(type_name, $1, VAR_NAME_MAX);
        xstrncat(type_name, ":", VAR_NAME_MAX);

        char buf[128];
        snprintf(buf, 128, "%d", $4);

        xstrncat(type_name, buf, VAR_NAME_MAX);
    
        xstrncpy($$, type_name, VAR_NAME_MAX);
        xstrncpy(variable_names[num_variable_names++], $2, VAR_NAME_MAX);
    }
    | type FUNCTION_POINTER IDENTIFIER ')' '(' type_params ')' {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncat($$, " lambda(", VAR_NAME_MAX);
        xstrncat($$, $6, VAR_NAME_MAX);
        xstrncat($$, ")", VAR_NAME_MAX);

        xstrncpy(variable_names[num_variable_names++], $3, VAR_NAME_MAX);

        xstrncpy(type_params, "", VAR_NAME_MAX);
    }
    ;

array_type: '[' exp ']' {
        snprintf($$, VAR_NAME_MAX, "[!%d]", $2);
    }
    | array_type '[' exp ']' {
        char buf[VAR_NAME_MAX];
        snprintf(buf, VAR_NAME_MAX, "[!%d]", $3);

        xstrncat($$, buf, VAR_NAME_MAX);
    }
    ;

const_array_type: '[' INTNUM ']' {
        snprintf($$, VAR_NAME_MAX, "[%d]", $2);
    }
    | const_array_type '[' INTNUM ']' {
        char buf[VAR_NAME_MAX];
        snprintf(buf, VAR_NAME_MAX, "[%d]", $3);

        xstrncat($$, buf, VAR_NAME_MAX);
    }
    ;

type_params: {
        xstrncpy(type_params, "", VAR_NAME_MAX);
        xstrncpy($$, type_params, VAR_NAME_MAX);
    }
    | type {
        xstrncpy(type_params, $1, VAR_NAME_MAX);
        xstrncpy($$, type_params, VAR_NAME_MAX);
    }
    | type_params ',' type {
        xstrncat(type_params, ",", VAR_NAME_MAX);
        xstrncat(type_params, $3, VAR_NAME_MAX);
        xstrncpy($$, type_params, VAR_NAME_MAX);
    };

union_: UNION IDENTIFIER '{' fields '}' ';' { char* union_name = $2;
            unsigned int fields = $4;
            BOOL anonymous = FALSE;

            $$ = sNodeTree_create_union(union_name, fields, anonymous, gSName, gSLine);
        }
        ;

struct_: 
        STRUCT IDENTIFIER '!' '<' struct_generics_types '>' '{' fields '}' ';' {
            char* struct_name = $2;
            unsigned int fields = $8;
            BOOL anonymous = FALSE;
            BOOL generics = num_struct_generics_types > 0;

            $$ = sNodeTree_create_struct(struct_name, fields, generics, anonymous, gSName, gSLine);
        }
        | STRUCT IDENTIFIER '{' fields '}' ';' {
            char* struct_name = $2;
            unsigned int fields = $4;
            BOOL anonymous = FALSE;
            BOOL generics = FALSE;

            $$ = sNodeTree_create_struct(struct_name, fields, generics, anonymous, gSName, gSLine);
        }
        ;

struct_generics_types: {
        num_struct_generics_types = 0;
    }
    | struct_generics_types IDENTIFIER {
        xstrncpy(struct_generics_types[num_struct_generics_types], $2, VAR_NAME_MAX);

        num_struct_generics_types++;

        if(num_struct_generics_types >= GENERICS_TYPES_MAX) {
            fprintf(stderr, "overflow method generics types number\n");
            exit(2);
        }
    }
    ;

fields:  { 
            fields = sNodeTree_create_struct_fields(gSName, gSLine); $$ = fields; 
        }
        | fields type_and_variable_name ';' { 
            $$ = fields; append_field_to_fields(fields, variable_names[--num_variable_names], $2); 
        }
        ;

enum_: ENUM '{' enum_fields '}' ';' {
    }
    ;

enum_fields: {
        enum_number = 0;
    }
    | IDENTIFIER {
        enum_number = 0;

        BOOL alloc = TRUE;
        BOOL global = TRUE;
        char* var_name = $1;
        unsigned int exp = sNodeTree_create_int_value(enum_number, gSName, gSLine);

        char* type_name = "int";

        unsigned int node = sNodeTree_create_store_variable(var_name, type_name, exp, alloc, global, gSName, gSLine); 

        compile(node, &cinfo);

        enum_number++;
    }
    | IDENTIFIER '=' INTNUM {
        enum_number = $3;

        BOOL alloc = TRUE;
        BOOL global = TRUE;
        char* var_name = $1;
        unsigned int exp = sNodeTree_create_int_value(enum_number, gSName, gSLine);

        char* type_name = "int";

        unsigned int node = sNodeTree_create_store_variable(var_name, type_name, exp, alloc, global, gSName, gSLine); 

        compile(node, &cinfo);

        enum_number++;
    }
    | enum_fields ',' IDENTIFIER {
        BOOL alloc = TRUE;
        BOOL global = TRUE;
        char* var_name = $3;
        unsigned int exp = sNodeTree_create_int_value(enum_number, gSName, gSLine);

        char* type_name = "int";

        unsigned int node = sNodeTree_create_store_variable(var_name, type_name, exp, alloc, global, gSName, gSLine); 

        compile(node, &cinfo);

        enum_number++;
    }
    | enum_fields ',' IDENTIFIER '=' INTNUM {
        enum_number = $5;

        BOOL alloc = TRUE;
        BOOL global = TRUE;
        char* var_name = $3;
        unsigned int exp = sNodeTree_create_int_value(enum_number, gSName, gSLine);

        char* type_name = "int";

        unsigned int node = sNodeTree_create_store_variable(var_name, type_name, exp, alloc, global, gSName, gSLine); 

        compile(node, &cinfo);

        enum_number++;
    }
    ;

global_variable:
        type_and_variable_name ';' {
            char* type_name = $1;
            char* var_name = variable_names[--num_variable_names];
            BOOL global = TRUE;
            BOOL extern_ = FALSE;

            $$ = sNodeTree_create_define_variable(type_name, var_name, global, extern_, gSName, gSLine);
        }

        | type IDENTIFIER const_array_type '=' '{' array_value '}' ';' { 
            char type_name[VAR_NAME_MAX];
            xstrncpy(type_name, $1, VAR_NAME_MAX);
            xstrncat(type_name, $3, VAR_NAME_MAX);

            char* var_name = $2;

            BOOL global = TRUE;
            BOOL extern_ = FALSE;

            $$ = sNodeTree_create_define_variable(type_name, var_name, global, extern_, gSName, gSLine);

            $$ = sNodeTree_create_array_initializer($$, var_name, num_array_value, array_values, global, gSName, gSLine);
        }
        | type IDENTIFIER '[' ']' '=' '{' array_value '}' ';' { 
            char type_name[VAR_NAME_MAX];
            xstrncpy(type_name, $1, VAR_NAME_MAX);

            char buf[128];
            snprintf(buf, 128, "[%d]", num_array_value);
            xstrncat(type_name, buf, VAR_NAME_MAX);

            char* var_name = $2;

            BOOL global = TRUE;
            BOOL extern_ = FALSE;

            $$ = sNodeTree_create_define_variable(type_name, var_name, global, extern_, gSName, gSLine);

            $$ = sNodeTree_create_array_initializer($$, var_name, num_array_value, array_values, global, gSName, gSLine);
        }
        | type IDENTIFIER const_array_type '=' CSTRING ';' { 
            char type_name[VAR_NAME_MAX];
            xstrncpy(type_name, $1, VAR_NAME_MAX);
            xstrncat(type_name, $3, VAR_NAME_MAX);

            char* var_name = $2;

            BOOL global = TRUE;
            BOOL extern_ = FALSE;

            $$ = sNodeTree_create_define_variable(type_name, var_name, global, extern_, gSName, gSLine);

            unsigned int array_values[512];

            if(strlen($5) >= 512) {
                fprintf(stderr, "overflow c string length\n");
                exit(2);
            }

            int i;
            for(i=0; i<strlen($5); i++) {
                array_values[i] = sNodeTree_create_char_value($5[i], gSName, gSLine);
            }
            array_values[i] = sNodeTree_create_char_value('\0', gSName, gSLine);

            int num_array_value = strlen($5) + 1;

            $$ = sNodeTree_create_array_initializer($$, var_name, num_array_value, array_values, global, gSName, gSLine);
        }

        | type_and_variable_name '=' exp ';'  { 
            BOOL alloc = TRUE;
            BOOL global = TRUE;

            $$ = sNodeTree_create_store_variable(variable_names[--num_variable_names], $1, $3, alloc, global, gSName, gSLine); 
        }
        ;

sub_array: 
    exp {
        array_values[num_array_value++] = $1;

        if(num_array_value >= INIT_ARRAY_MAX) {
            fprintf(stderr, "overflow array element numver\n");
            exit(1);
        }

        $$ = $1;
    }
    | sub_array ',' exp {
        array_values[num_array_value++] = $3;

        if(num_array_value >= INIT_ARRAY_MAX) {
            fprintf(stderr, "overflow array element numver\n");
            exit(1);
        }

        $$ = $3;
    }
    ;

sub_array_init: {
    num_array_value = 0;
    }
    ;

array_value: 
    exp {
        num_array_value = 0;
        array_values[num_array_value++] = $1;

        if(num_array_value >= INIT_ARRAY_MAX) {
            fprintf(stderr, "overflow array element numver\n");
            exit(1);
        }

        $$ = $1;
    }
    | '{' sub_array_init sub_array '}' {
        $$ = $2;
    }
    | array_value ',' exp {
        array_values[num_array_value++] = $3;

        if(num_array_value >= INIT_ARRAY_MAX) {
            fprintf(stderr, "overflow array element numver\n");
            exit(1);
        }

        $$ = $3;
    }
    | array_value ',' '{' sub_array '}' {
        $$ = $4;
    }
    ;

function: 
        type IDENTIFIER '(' function_params ')' ';' {
            char* result_type = $1;
            char* fun_name = $2;
            unsigned int function_params = $4;
            $$ = it = sNodeTree_create_external_function(fun_name, function_params, result_type, var_arg, inherit_, gSName, gSLine);

            num_function_generics_types = 0;
            num_method_generics_types = 0;
            inline_ = FALSE;
            static_ = FALSE;
            inherit_ = FALSE;
        }
        | EXTERN type IDENTIFIER '(' function_params ')' ';' {
            char* result_type = $2;
            char* fun_name = $3;
            unsigned int function_params = $5;
            $$ = it = sNodeTree_create_external_function(fun_name, function_params, result_type, var_arg, inherit_, gSName, gSLine);

            num_function_generics_types = 0;
            num_method_generics_types = 0;
            inline_ = FALSE;
            static_ = FALSE;
            inherit_ = FALSE;
        }
        | type IDENTIFIER '(' function_params ')' function_params_end '{' function_block '}' block_end {
            char* result_type = $1;
            char* fun_name = $2;
            unsigned int function_params = $4;
            unsigned int node_block = $8;
            BOOL generics = FALSE;
            BOOL method_generics = FALSE;

            $$ = it = sNodeTree_create_function(fun_node, fun_name, fun_name, function_params, result_type, node_block, var_arg, inline_, static_, inherit_, generics, num_method_generics_types, gSName, gSLine);

            num_function_generics_types = 0;
            num_method_generics_types = 0;
            inline_ = FALSE;
            static_ = FALSE;
            inherit_ = FALSE;
        }
        | type function_struct_type_name METHOD_MARK IDENTIFIER '(' function_params ')' function_params_end '{' function_block '}' block_end 
        {
            char* result_type = $1;

            char fun_name[VAR_NAME_MAX];

            char* struct_name = $2;

            char* p = strstr(struct_name, "<");

            char struct_name2[VAR_NAME_MAX];

            if(p) {
                memcpy(struct_name2, struct_name, p - struct_name);
                struct_name2[p-struct_name] = '\0';
            }
            else {
                xstrncpy(struct_name2, struct_name, VAR_NAME_MAX);
            }

            xstrncpy(fun_name, struct_name2, VAR_NAME_MAX);
            xstrncat(fun_name, "_", VAR_NAME_MAX);
            xstrncat(fun_name, $4, VAR_NAME_MAX);

            char fun_base_name[VAR_NAME_MAX];

            xstrncpy(fun_base_name, $4, VAR_NAME_MAX);

            unsigned int function_params = $6;
            unsigned int node_block = $10;
            BOOL generics = num_function_generics_types > 0;
            BOOL method_generics = num_method_generics_types > 0;

            $$ = it = sNodeTree_create_function(fun_node, fun_name, fun_base_name, function_params, result_type, node_block, var_arg, inline_, static_, inherit_, generics, method_generics, gSName, gSLine);

            num_function_generics_types = 0;
            num_method_generics_types = 0;
            inline_ = FALSE;
            static_ = FALSE;
            inherit_ = FALSE;
        }
        | TEMPLATE '!' '<' method_generics_types '>' type IDENTIFIER '(' function_params ')' function_params_end '{' function_block '}' block_end {
            char* result_type = $6;
            char* fun_name = $7;
            unsigned int function_params = $9;
            unsigned int node_block = $13;
            BOOL generics = FALSE;
            BOOL method_generics = num_method_generics_types > 0;

            $$ = it = sNodeTree_create_function(fun_node, fun_name, fun_name, function_params, result_type, node_block, var_arg, inline_, static_, inherit_, generics, num_method_generics_types, gSName, gSLine);

            num_function_generics_types = 0;
            num_method_generics_types = 0;
            inline_ = FALSE;
            static_ = FALSE;
            inherit_ = FALSE;
        }
        | TEMPLATE '!' '<' method_generics_types '>' type function_struct_type_name METHOD_MARK IDENTIFIER '(' function_params ')' function_params_end '{' function_block '}' block_end 
        {
            char* result_type = $6;

            char fun_name[VAR_NAME_MAX];

            char* struct_name = $7;

            char* p = strstr(struct_name, "<");

            char struct_name2[VAR_NAME_MAX];

            if(p) {
                memcpy(struct_name2, struct_name, p - struct_name);
                struct_name2[p-struct_name] = '\0';
            }
            else {
                xstrncpy(struct_name2, struct_name, VAR_NAME_MAX);
            }

            xstrncpy(fun_name, struct_name2, VAR_NAME_MAX);
            xstrncat(fun_name, "_", VAR_NAME_MAX);
            xstrncat(fun_name, $9, VAR_NAME_MAX);

            char fun_base_name[VAR_NAME_MAX];

            xstrncpy(fun_base_name, $8, VAR_NAME_MAX);

            unsigned int function_params = $11;
            unsigned int node_block = $15;
            BOOL generics = num_function_generics_types > 0;
            BOOL method_generics = num_method_generics_types > 0;

            $$ = it = sNodeTree_create_function(fun_node, fun_name, fun_base_name, function_params, result_type, node_block, var_arg, inline_, static_, inherit_, generics, method_generics, gSName, gSLine);

            num_function_generics_types = 0;
            num_method_generics_types = 0;
            inline_ = FALSE;
            static_ = FALSE;
            inherit_ = FALSE;
        }
        ;

function_params: { 
            func_params = sNodeTree_create_function_params(gSName, gSLine); $$ = func_params; var_arg = FALSE; 
        }
        | VOID { 
            func_params = sNodeTree_create_function_params(gSName, gSLine); $$ = func_params; 
        }
        | type_and_variable_name {
            func_params = sNodeTree_create_function_params(gSName, gSLine);
            $$ = func_params; 
            var_arg = FALSE; 
            append_param_to_function_params(func_params, $1, variable_names[--num_variable_names]);
        }
        | function_params ',' type_and_variable_name { 
            $$ = func_params; 
            append_param_to_function_params(func_params, $3, variable_names[--num_variable_names]); 
        }
        | function_params ',' '.' '.' '.' {
            var_arg = TRUE;
        }
        ;

function_params_end: {
        $$ = fun_node = sNodeTree_pre_create_function(func_params, gSName, gSLine);
        }
        ;


method_generics_types: {
        num_method_generics_types = 0;
    }
    | method_generics_types IDENTIFIER {
        xstrncpy(method_generics_types[num_method_generics_types], $2, VAR_NAME_MAX);

        num_method_generics_types++;

        if(num_method_generics_types >= GENERICS_TYPES_MAX) {
            fprintf(stderr, "overflow method generics types number\n");
            exit(2);
        }
    }
    ;

function_struct_type_name: TYPE_NAME {
        char type_name[VAR_NAME_MAX];
        get_typedef($1, type_name);

        xstrncpy($$, type_name, VAR_NAME_MAX);
        num_function_generics_types = 0;
    }
    | TYPE_NAME '!' '<' function_generics_types '>' {
        char type_name[VAR_NAME_MAX];
        get_typedef($1, type_name);

        xstrncat(type_name, "<", VAR_NAME_MAX);
        xstrncat(type_name, $4, VAR_NAME_MAX);
        xstrncat(type_name, ">", VAR_NAME_MAX);

        xstrncpy($$, type_name, VAR_NAME_MAX);
    }
    ;


function_generics_types: {
        num_function_generics_types = 0;
    }
    | function_generics_types type {
        char type_name[VAR_NAME_MAX];
        get_typedef($2, type_name);

        xstrncpy($$, ",", VAR_NAME_MAX);
        xstrncpy($$, type_name, VAR_NAME_MAX);

        xstrncpy(function_generics_types[num_function_generics_types], type_name, VAR_NAME_MAX);
        num_function_generics_types++;

        if(num_function_generics_types >= GENERICS_TYPES_MAX) {
            fprintf(stderr, "overflow generics type number\n");
            exit(2);
        }
    }
    ;


block:  statment                  { 
            prev_block[num_prev_block] = block;
            num_prev_block++;

            if(num_prev_block >= BLOCK_NEST_MAX) {
                fprintf(stderr, "overflow nest block\n");
                exit(2);
            }

            BOOL create_lv_table = TRUE;

            block = sNodeTree_create_block(create_lv_table, gSName, gSLine); append_node_to_node_block(block, $1); $$ = block; 
        } 
        | block statment          { 
            $$ = block; append_node_to_node_block(block, $2); 
        }
        ;

function_block:  statment                  { 
            prev_block[num_prev_block] = block;
            num_prev_block++;

            if(num_prev_block >= BLOCK_NEST_MAX) {
                fprintf(stderr, "overflow nest block\n");
                exit(2);
            }

            BOOL create_lv_table = FALSE;

            block = sNodeTree_create_block(create_lv_table, gSName, gSLine); append_node_to_node_block(block, $1); $$ = block; 
        } 
        | function_block statment          { 
            $$ = block; append_node_to_node_block(block, $2); 
        }
        ;

block_end: {
        block = prev_block[num_prev_block-1];

        num_prev_block--;
        if(num_prev_block < 0) {
            fprintf(stderr, "overflow nest block\n");
            exit(2);
        }
        $$ = block;
        };

statment: comma_exp ';'              { $$ = $1; }
    | RETURN ';'               { $$ = sNodeTree_create_return(0, 0, gSName, gSLine); }
    | RETURN '(' comma_exp ')' ';'   { $$ = sNodeTree_create_return($3, 0, gSName, gSLine); }
    | RETURN comma_exp ';'  { $$ = sNodeTree_create_return($2, 0, gSName, gSLine); }
    | RETURN ';' after_return_case_statment { $$ = sNodeTree_create_return(0, $3, gSName, gSLine); }
    | RETURN '(' comma_exp ')' ';' after_return_case_statment   { $$ = sNodeTree_create_return($3, $6, gSName, gSLine); }
    | RETURN comma_exp ';' after_return_case_statment  { $$ = sNodeTree_create_return($2, $4, gSName, gSLine); }
    | IF '(' comma_exp ')' '{' block '}' block_end {
        unsigned int if_exp = $3;
        unsigned int if_block = $6;
        int elif_num = 0;
        unsigned int elif_exps[ELIF_NUM_MAX];
        unsigned int elif_blocks[ELIF_NUM_MAX];
        unsigned else_block = 0;
        
        $$ = sNodeTree_create_if(if_exp, if_block, elif_num, elif_exps, elif_blocks, else_block, gSName, gSLine);
    }
    | IF '(' comma_exp ')' '{' block '}' block_end ELSE '{' block '}' block_end 
    {
        unsigned int if_exp = $3;
        unsigned int if_block = $6;
        int elif_num = 0;
        unsigned int elif_exps[ELIF_NUM_MAX];
        unsigned int elif_blocks[ELIF_NUM_MAX];
        unsigned int else_block = $11;
        
        $$ = sNodeTree_create_if(if_exp, if_block, elif_num, elif_exps, elif_blocks, else_block, gSName, gSLine);
    }
    | IF '(' comma_exp ')' '{' block '}' block_end ELSE IF prepare_elif_statment elif_statment ELSE '{' block '}' block_end 
    {
        unsigned int if_exp = $3;
        unsigned int if_block = $6;
        unsigned int else_block = $15;
        
        $$ = sNodeTree_create_if(if_exp, if_block, elif_num, elif_exps, elif_blocks, else_block, gSName, gSLine);
    }
    | IF '(' comma_exp ')' '{' block '}' block_end ELSE IF prepare_elif_statment elif_statment {
        unsigned int if_exp = $3;
        unsigned int if_block = $6;
        unsigned else_block = 0;
        
        $$ = sNodeTree_create_if(if_exp, if_block, elif_num, elif_exps, elif_blocks, else_block, gSName, gSLine);
    }
    | FOR '(' comma_exp ';' comma_exp ';' comma_exp ')' '{' block '}' block_end {
        unsigned int expression_node1 = $3;
        unsigned int expression_node2 = $5;
        unsigned int expression_node3 = $7;

        unsigned int for_node_block = $10;

        $$ = sNodeTree_for_statment(expression_node1, expression_node2, expression_node3, for_node_block, gSName, gSLine);
    }
    | WHILE '(' comma_exp ')' '{' block '}' block_end {
        unsigned int expression_node1 = $3;

        unsigned int while_node_block = $6;

        $$ = sNodeTree_while_statment(expression_node1, while_node_block, gSName, gSLine);
    }
    | SWITCH '(' comma_exp ')' '{' switch_block '}' {
        unsigned int expression_node = $3;

        $$ = sNodeTree_switch_statment(expression_node, num_switch_expression, switch_expression, gSName, gSLine);
    }
    | case_statment  {
        $$ = $1;
    }
    | DEFAULT ':' {
        BOOL first_case = TRUE;
        BOOL last_case = TRUE;
        BOOL case_after_return = FALSE;
        unsigned int first_statment = 0;
        unsigned int last_statment = 0;

        $$ = sNodeTree_case_expression(0, first_case, last_case, case_after_return, first_statment, last_statment, gSName, gSLine);
    }
    | BREAK ';' {
        $$ = sNodeTree_create_break_expression(gSName, gSLine);
    }
    | CONTINUE ';' {
        $$ = sNodeTree_create_continue_expression(gSName, gSLine);
    }
    | DO '{' block '}' block_end WHILE '(' comma_exp ')' ';' {
        unsigned int expression_node1 = $8;

        unsigned int while_node_block = $3;

        $$ = sNodeTree_do_while_expression(expression_node1, while_node_block, gSName, gSLine);
    }
    | type_and_variable_name ';' {
        char* type_name = $1;
        char* var_name = variable_names[--num_variable_names];
        BOOL global = FALSE;
        BOOL extern_ = FALSE;

        $$ = sNodeTree_create_define_variable(type_name, var_name, global, extern_, gSName, gSLine);
    }
    ;

case_statment: CASE exp ':' {
        BOOL first_case = TRUE;
        BOOL last_case = TRUE;
        BOOL case_after_return = FALSE;

        unsigned int expression_node = $2;

        unsigned int first_statment = 0;
        unsigned int last_statment = 0;

        $$ = sNodeTree_case_expression(expression_node, first_case, last_case, case_after_return, first_statment, last_statment, gSName, gSLine);
    }
    | case_statment CASE exp ':' {
        BOOL first_case = FALSE;
        BOOL last_case = TRUE;
        BOOL case_after_return = FALSE;

        unsigned int first_statment = 0;
        unsigned int last_statment = $1;
        unsigned int expression_node = $3;

        gNodes[last_statment].uValue.sCase.mLastCase = FALSE;

        $$ = sNodeTree_case_expression(expression_node, first_case, last_case, case_after_return, first_statment, last_statment, gSName, gSLine);
    }
    ;

after_return_case_statment: CASE exp ':' {
        BOOL first_case = TRUE;
        BOOL last_case = TRUE;
        BOOL case_after_return = TRUE;

        unsigned int expression_node = $2;

        unsigned int first_statment = 0;
        unsigned int last_statment = 0;

        $$ = sNodeTree_case_expression(expression_node, first_case, last_case, case_after_return, first_statment, last_statment, gSName, gSLine);
    }
    | after_return_case_statment CASE exp ':' {
        BOOL first_case = FALSE;
        BOOL last_case = TRUE;
        BOOL case_after_return = FALSE;

        unsigned int first_statment = 0;
        unsigned int last_statment = $1;
        unsigned int expression_node = $3;

        gNodes[last_statment].uValue.sCase.mLastCase = FALSE;

        $$ = sNodeTree_case_expression(expression_node, first_case, last_case, case_after_return, first_statment, last_statment, gSName, gSLine);
    }
    ;

switch_block: statment {
        num_switch_expression = 0;

        switch_expression[num_switch_expression] = $1;

        num_switch_expression++;

        if(num_switch_expression >= SWITCH_STASTMENT_NODE_MAX) {
            fprintf(stderr, "overflow switch expression\n");
            exit(2);
        }
    }
    | switch_block statment {
        switch_expression[num_switch_expression] = $2;

        num_switch_expression++;

        if(num_switch_expression >= SWITCH_STASTMENT_NODE_MAX) {
            fprintf(stderr, "overflow switch expression\n");
            exit(2);
        }
    }
    ;


prepare_elif_statment: '(' comma_exp ')' '{' block '}' block_end {
    elif_num = 0;
    elif_exps[elif_num] = $2;
    elif_blocks[elif_num] = $5;
    elif_num++;

    if(elif_num >= ELIF_NUM_MAX) {
        fprintf(stderr, "overflow else if number\n");
        exit(2);
    }

    $$ = 0;
    }
    ;

elif_statment:
    ELSE IF '(' comma_exp ')' '{' block '}' block_end {
        elif_exps[elif_num] = $4;
        elif_blocks[elif_num] = $7;
        elif_num++;

        if(elif_num >= ELIF_NUM_MAX) {
            fprintf(stderr, "overflow else if number\n");
            exit(2);
        }
    }
    | elif_statment ELSE IF '(' comma_exp ')' '{' block '}' block_end {
        elif_exps[elif_num] = $5;
        elif_blocks[elif_num] = $8;
        elif_num++;

        if(elif_num >= ELIF_NUM_MAX) {
            fprintf(stderr, "overflow else if number\n");
            exit(2);
        }
    }
    ;

comma_exp: exp {
         $$ = $1;
         }
         | comma_exp ',' comma_exp {
            compile($1, &cinfo); $$ = $3;
         }
         ;

exp: node {
        $$ = $1;
    }
    | exp '+' exp    { $$ = sNodeTree_create_add($1, $3, gSName, gSLine); }
    | exp '-' exp    { $$ = sNodeTree_create_sub($1, $3, gSName, gSLine); }
    | exp '*' exp   { $$ = sNodeTree_create_mult($1, $3,  gSName, gSLine); }
    | exp '/' exp    { $$ = sNodeTree_create_div($1, $3, gSName, gSLine); }
    | exp '%' exp    { $$ = sNodeTree_create_mod($1, $3, gSName, gSLine); }
    | exp EQEQ exp   { $$ = sNodeTree_create_equals($1, $3, gSName, gSLine); }
    | exp '>' exp    { $$ = sNodeTree_create_gt($1, $3, gSName, gSLine); }
    | exp '<' exp    { $$ = sNodeTree_create_lt($1, $3, gSName, gSLine); }
    | exp GTEQ exp   { $$ = sNodeTree_create_ge($1, $3, gSName, gSLine); }
    | exp LTEQ exp   { $$ = sNodeTree_create_le($1, $3, gSName, gSLine); }
    | exp ANDAND exp { $$ = sNodeTree_create_and_and($1, $3, gSName, gSLine); }
    | exp OROR exp   { $$ = sNodeTree_create_or_or($1, $3, gSName, gSLine); }
    | exp LSHIFT exp { $$ = sNodeTree_create_lshift($1, $3, gSName, gSLine); }
    | exp RSHIFT exp { $$ = sNodeTree_create_rshift($1, $3, gSName, gSLine); }
    | exp '|' exp    { $$ = sNodeTree_create_or($1, $3, gSName, gSLine); }
    | exp '^' exp    { $$ = sNodeTree_create_xor($1, $3, gSName, gSLine); }
    | exp '&' exp    { $$ = sNodeTree_create_and($1, $3, gSName, gSLine); }
    | '(' comma_exp ')'    { $$ = $2; }
    | '!' exp        { $$ = sNodeTree_create_logical_denial($2, gSName, gSLine); }
    | '~' exp        { $$ = sNodeTree_create_complement($2, gSName, gSLine); }
    | '&' node       { $$ = sNodeTree_create_refference($2, gSName, gSLine); }
    ;

cstring_array_value2: CSTRING {
        $$ = sNodeTree_create_c_string($1, gSName, gSLine);

        num_array_value = 0;
        array_values[num_array_value++] = $$;
    }
    | cstring_array_value2 ',' CSTRING {
        $$ = sNodeTree_create_c_string($3, gSName, gSLine);

        array_values[num_array_value++] = $$;
    };

node: source_point_macro exp {
            $$ = $2;
            }
        | INTNUM                { $$ = it = sNodeTree_create_int_value($1, gSName, gSLine); }
        | CHARNUM                { $$ = it = sNodeTree_create_char_value($1, gSName, gSLine); }
        | CSTRING {
            $$ = it = sNodeTree_create_c_string($1, gSName, gSLine);
        }
        | TOKEN_TRUE {
            $$ = sNodeTree_create_true(gSName, gSLine);
        }
        | TOKEN_FALSE {
            $$ = sNodeTree_create_false(gSName, gSLine);
        }
        | IDENTIFIER {
            $$ = sNodeTree_create_load_variable($1, gSName, gSLine);
        }
        | type_and_variable_name '=' comma_exp  { 
            BOOL alloc = TRUE;
            BOOL global = FALSE;

            $$ = sNodeTree_create_store_variable(variable_names[--num_variable_names], $1, $3, alloc, global, gSName, gSLine); 
        }
        | type IDENTIFIER const_array_type '=' '{' cstring_array_value2 '}' { 
            char type_name[VAR_NAME_MAX];
            xstrncpy(type_name, $1, VAR_NAME_MAX);
            xstrncat(type_name, $3, VAR_NAME_MAX);

            char* var_name = $2;

            BOOL global = FALSE;
            BOOL extern_ = FALSE;

            $$ = sNodeTree_create_define_variable(type_name, var_name, global, extern_, gSName, gSLine);

            $$ = sNodeTree_create_array_initializer($$, var_name, num_array_value, array_values, global, gSName, gSLine);
        }
        | type IDENTIFIER const_array_type '=' '{' array_value '}' { 
            char type_name[VAR_NAME_MAX];
            xstrncpy(type_name, $1, VAR_NAME_MAX);
            xstrncat(type_name, $3, VAR_NAME_MAX);

            char* var_name = $2;

            BOOL global = FALSE;
            BOOL extern_ = FALSE;

            $$ = sNodeTree_create_define_variable(type_name, var_name, global, extern_, gSName, gSLine);

            $$ = sNodeTree_create_array_initializer($$, var_name, num_array_value, array_values, global, gSName, gSLine);
        }
        | type IDENTIFIER '[' ']' '=' '{' array_value '}' { 
            char type_name[VAR_NAME_MAX];
            xstrncpy(type_name, $1, VAR_NAME_MAX);

            char buf[128];
            snprintf(buf, 128, "[%d]", num_array_value);

            xstrncat(type_name, buf, VAR_NAME_MAX);

            char* var_name = $2;

            BOOL global = FALSE;
            BOOL extern_ = FALSE;

            $$ = sNodeTree_create_define_variable(type_name, var_name, global, extern_, gSName, gSLine);

            $$ = sNodeTree_create_array_initializer($$, var_name, num_array_value, array_values, global, gSName, gSLine);
        }
        | type IDENTIFIER const_array_type '=' CSTRING { 
            char type_name[VAR_NAME_MAX];
            xstrncpy(type_name, $1, VAR_NAME_MAX);
            xstrncat(type_name, $3, VAR_NAME_MAX);

            char* var_name = $2;

            BOOL global = FALSE;
            BOOL extern_ = FALSE;

            $$ = sNodeTree_create_define_variable(type_name, var_name, global, extern_, gSName, gSLine);

            unsigned int array_values[512];

            if(strlen($5) >= 512) {
                fprintf(stderr, "overflow c string length\n");
                exit(2);
            }

            int i;
            for(i=0; i<strlen($5); i++) {
                array_values[i] = sNodeTree_create_char_value($5[i], gSName, gSLine);
            }
            array_values[i] = sNodeTree_create_char_value('\0', gSName, gSLine);

            int num_array_value = strlen($5) + 1;

            $$ = sNodeTree_create_array_initializer($$, var_name, num_array_value, array_values, global, gSName, gSLine);
        }
        | IDENTIFIER '=' comma_exp { 
            BOOL alloc = FALSE;
            BOOL global = FALSE;

            $$ = sNodeTree_create_store_variable($1, "", $3, alloc, global, gSName, gSLine); 
        }

        | IDENTIFIER array_index {
            unsigned int array = sNodeTree_create_load_variable($1, gSName, gSLine);

            unsigned int* index_node = array_index_index_node;
            int num_dimention = array_index_num_dimention;

            $$ = sNodeTree_create_load_array_element(array, index_node, num_dimention, gSName, gSLine);
        }
        | IDENTIFIER array_index '=' comma_exp {
            unsigned int array = sNodeTree_create_load_variable($1, gSName, gSLine);

            unsigned int* index_node = array_index_index_node;
            int num_dimention = array_index_num_dimention;

            unsigned int right_node = $4;

            $$ = sNodeTree_create_store_element(array, index_node, num_dimention, right_node, gSName, gSLine);
        }

        | IDENTIFIER '(' ')' {
            BOOL existance = function_existance($1);

            if(existance) {
                $$ = sNodeTree_create_function_call($1, 0, FALSE, FALSE, gSName, gSLine);
            }
            else {
                unsigned int node = sNodeTree_create_load_variable($1, gSName, gSLine);
                $$ = sNodeTree_create_lambda_call(node, 0, gSName, gSLine);
            }
        }
        | IDENTIFIER '(' params ')' {
            BOOL existance = function_existance($1);

            if(existance) {
                $$ = sNodeTree_create_function_call($1, $3, FALSE, FALSE, gSName, gSLine);
            }
            else {
                unsigned int node = sNodeTree_create_load_variable($1, gSName, gSLine);
                $$ = sNodeTree_create_lambda_call(node, $3, gSName, gSLine);
            }
        }
        | exp '.' IDENTIFIER '(' ')' {
            params = sNodeTree_create_params(gSName, gSLine); 
            append_param_to_params(params, $1);

            $$ = sNodeTree_create_function_call($3, params, TRUE, FALSE, gSName, gSLine);
        }
        | exp '.' IDENTIFIER '(' params ')' {
            append_param_to_params($5, $1);
            $$ = sNodeTree_create_function_call($3, $5, TRUE, FALSE, gSName, gSLine);
        }
        | INHERIT '(' ')' {
            $$ = sNodeTree_create_function_call("inherit", 0, FALSE, TRUE, gSName, gSLine);
        }
        | INHERIT '(' params ')' {
            $$ = sNodeTree_create_function_call("inherit", $3, FALSE, TRUE, gSName, gSLine);
        }
        | exp '.' INHERIT '(' ')' {
            params = sNodeTree_create_params(gSName, gSLine); 
            append_param_to_params(params, $1);

            $$ = sNodeTree_create_function_call("inherit", params, TRUE, TRUE, gSName, gSLine);
        }
        | exp '.' INHERIT '(' params ')' {
            append_param_to_params($5, $1);
            $$ = sNodeTree_create_function_call("inherit", $5, TRUE, TRUE, gSName, gSLine);
        }
        | exp '.' IDENTIFIER {
            $$ = sNodeTree_create_load_field($3, $1, gSName, gSLine);
        }
        | exp '-' '>' IDENTIFIER {
            $$ = sNodeTree_create_load_field($4, $1, gSName, gSLine);
        }
        | exp '.' IDENTIFIER '=' comma_exp  { 
            $$ = sNodeTree_create_store_field($3, $1, $5, gSName, gSLine); 
        }
        | exp '-' '>' IDENTIFIER '=' comma_exp  { 
            $$ = sNodeTree_create_store_field($4, $1, $6, gSName, gSLine); 
        }
        | NEW type {
            char* type_name = $2;
            unsigned int object_num = 0;

            $$ = sNodeTree_create_object(type_name, object_num, gSName, gSLine);
        }
        | NEW type '[' comma_exp ']'  {
            char* type_name = $2;
            unsigned int object_num = $4;

            $$ = sNodeTree_create_object(type_name, object_num, gSName, gSLine);
        }
        | CLONE exp {
            unsigned int exp = $2;

            $$ = sNodeTree_create_clone(exp, gSName, gSLine);
        }
        | type LAMBDA '(' function_params ')' '{' function_block '}' block_end 
        {
            char* result_type_name = $1;
            unsigned int function_params = $4;
            unsigned int node_block = $7;

            $$ = sNodeTree_create_coroutine(function_params, result_type_name, node_block, var_arg, gSName, gSLine);
        }
        | exp '(' params ')' {
            $$ = sNodeTree_create_lambda_call($1, $3, gSName, gSLine);
        }
        | pointer '(' exp ')'     { 
            $$ = sNodeTree_create_derefference($3, gSName, gSLine); 

            int i;
            for(i=0; i<strlen($1)-1; i++) {
                $$ = sNodeTree_create_derefference($$, gSName, gSLine); 
            }
        }
        | pointer IDENTIFIER     { 
            $$ = sNodeTree_create_load_variable($2, gSName, gSLine);
            int i;
            for(i=0; i<strlen($1); i++) {
                $$ = sNodeTree_create_derefference($$, gSName, gSLine); 
            }
        }
        | IDENTIFIER PLUS_PLUS { 
            $$ = sNodeTree_create_load_variable($1, gSName, gSLine);

            unsigned int int_value = sNodeTree_create_int_value(1, gSName, gSLine);

            $$ = sNodeTree_create_add($$, int_value, gSName, gSLine);

            BOOL alloc = FALSE;
            BOOL global = FALSE;

            $$ = sNodeTree_create_store_variable($1, "", $$, alloc, global, gSName, gSLine); 

            $$ = sNodeTree_create_sub($$, int_value, gSName, gSLine);
        }
        | '(' comma_exp ')' PLUS_PLUS { 
            unsigned int left = $2;
            unsigned int right = sNodeTree_create_int_value(1, gSName, gSLine);

            $$ = sNodeTree_create_plus_eq(left, right, gSName, gSLine);
        }
        | PLUS_PLUS IDENTIFIER { 
            $$ = sNodeTree_create_load_variable($2, gSName, gSLine);

            unsigned int int_value = sNodeTree_create_int_value(1, gSName, gSLine);

            $$ = sNodeTree_create_add($$, int_value, gSName, gSLine);

            BOOL alloc = FALSE;
            BOOL global = FALSE;

            $$ = sNodeTree_create_store_variable($2, "", $$, alloc, global, gSName, gSLine); 
        }
        | FUNCTION_POINTER IDENTIFIER ')' PLUS_PLUS {
            unsigned int left = sNodeTree_create_load_variable($2, gSName, gSLine);
            left = sNodeTree_create_derefference(left, gSName, gSLine); 

            unsigned int right = sNodeTree_create_int_value(1, gSName, gSLine);

            $$ = sNodeTree_create_plus_eq(left, right, gSName, gSLine);
        }
        | IDENTIFIER MINUS_MINUS { 
            $$ = sNodeTree_create_load_variable($1, gSName, gSLine);

            unsigned int int_value = sNodeTree_create_int_value(1, gSName, gSLine); 

            $$ = sNodeTree_create_sub($$, int_value, gSName, gSLine);

            BOOL alloc = FALSE;
            BOOL global = FALSE;

            $$ = sNodeTree_create_store_variable($1, "", $$, alloc, global, gSName, gSLine); 

            $$ = sNodeTree_create_add($$, int_value, gSName, gSLine);
        }
        | MINUS_MINUS IDENTIFIER { 
            $$ = sNodeTree_create_load_variable($2, gSName, gSLine);

            unsigned int int_value = sNodeTree_create_int_value(1, gSName, gSLine); 

            $$ = sNodeTree_create_sub($$, int_value, gSName, gSLine);

            BOOL alloc = FALSE;
            BOOL global = FALSE;

            $$ = sNodeTree_create_store_variable($2, "", $$, alloc, global, gSName, gSLine); 
        }
        | FUNCTION_POINTER IDENTIFIER ')' MINUS_MINUS {
            unsigned int left = sNodeTree_create_load_variable($2, gSName, gSLine);
            left = sNodeTree_create_derefference(left, gSName, gSLine); 

            unsigned int right = sNodeTree_create_int_value(1, gSName, gSLine);

            $$ = sNodeTree_create_minus_eq(left, right, gSName, gSLine);
        }
        | '(' comma_exp ')' MINUS_MINUS { 
            unsigned int left = $2;
            unsigned int right = sNodeTree_create_int_value(1, gSName, gSLine);

            $$ = sNodeTree_create_minus_eq(left, right, gSName, gSLine);
        }
        | IDENTIFIER PLUS_EQ comma_exp { 
            $$ = sNodeTree_create_load_variable($1, gSName, gSLine);

            unsigned int int_value = $3;

            $$ = sNodeTree_create_add($$, int_value, gSName, gSLine);

            BOOL alloc = FALSE;
            BOOL global = FALSE;

            $$ = sNodeTree_create_store_variable($1, "", $$, alloc, global, gSName, gSLine); 

            $$ = sNodeTree_create_sub($$, int_value, gSName, gSLine);
        }
        | '(' comma_exp ')' PLUS_EQ comma_exp { 
            unsigned int left = $2;
            unsigned int right = $5;

            $$ = sNodeTree_create_plus_eq(left, right, gSName, gSLine);
        }
        | FUNCTION_POINTER IDENTIFIER ')' PLUS_EQ comma_exp {
            unsigned int left = sNodeTree_create_load_variable($2, gSName, gSLine);
            left = sNodeTree_create_derefference(left, gSName, gSLine); 
            unsigned int right = $5;

            $$ = sNodeTree_create_plus_eq(left, right, gSName, gSLine);
        }
        | IDENTIFIER MINUS_EQ comma_exp { 
            $$ = sNodeTree_create_load_variable($1, gSName, gSLine);

            unsigned int int_value = $3;

            $$ = sNodeTree_create_sub($$, int_value, gSName, gSLine);

            BOOL alloc = FALSE;
            BOOL global = FALSE;

            $$ = sNodeTree_create_store_variable($1, "", $$, alloc, global, gSName, gSLine); 

            $$ = sNodeTree_create_add($$, int_value, gSName, gSLine);
        }
        | '(' comma_exp ')' MINUS_EQ exp { 
            unsigned int left = $2;
            unsigned int right = $5;

            $$ = sNodeTree_create_minus_eq(left, right, gSName, gSLine);
        }
        | FUNCTION_POINTER IDENTIFIER ')' MINUS_EQ comma_exp {
            unsigned int left = sNodeTree_create_load_variable($2, gSName, gSLine);
            left = sNodeTree_create_derefference(left, gSName, gSLine); 
            unsigned int right = $5;

            $$ = sNodeTree_create_minus_eq(left, right, gSName, gSLine);
        }
        | IDENTIFIER MULT_EQ comma_exp { 
            $$ = sNodeTree_create_load_variable($1, gSName, gSLine);

            unsigned int int_value = $3;

            $$ = sNodeTree_create_mult($$, int_value, gSName, gSLine);

            BOOL alloc = FALSE;
            BOOL global = FALSE;

            $$ = sNodeTree_create_store_variable($1, "", $$, alloc, global, gSName, gSLine); 
        }
        | '(' comma_exp ')' MULT_EQ exp { 
            unsigned int left = $2;
            unsigned int right = $5;

            $$ = sNodeTree_create_mult_eq(left, right, gSName, gSLine);
        }
        | FUNCTION_POINTER IDENTIFIER ')' MULT_EQ comma_exp {
            unsigned int left = sNodeTree_create_load_variable($2, gSName, gSLine);
            left = sNodeTree_create_derefference(left, gSName, gSLine); 
            unsigned int right = $5;

            $$ = sNodeTree_create_mult_eq(left, right, gSName, gSLine);
        }
        | IDENTIFIER DIV_EQ comma_exp {
            $$ = sNodeTree_create_load_variable($1, gSName, gSLine);

            unsigned int int_value = $3;

            $$ = sNodeTree_create_div($$, int_value, gSName, gSLine);

            BOOL alloc = FALSE;
            BOOL global = FALSE;

            $$ = sNodeTree_create_store_variable($1, "", $$, alloc, global, gSName, gSLine); 
        }
        | '(' comma_exp ')' DIV_EQ exp { 
            unsigned int left = $2;
            unsigned int right = $5;

            $$ = sNodeTree_create_div_eq(left, right, gSName, gSLine);
        }
        | FUNCTION_POINTER IDENTIFIER ')' DIV_EQ comma_exp {
            unsigned int left = sNodeTree_create_load_variable($2, gSName, gSLine);
            left = sNodeTree_create_derefference(left, gSName, gSLine); 
            unsigned int right = $5;

            $$ = sNodeTree_create_div_eq(left, right, gSName, gSLine);
        }
        | IDENTIFIER MOD_EQ comma_exp {
            $$ = sNodeTree_create_load_variable($1, gSName, gSLine);

            unsigned int int_value = $3;

            $$ = sNodeTree_create_mod($$, int_value, gSName, gSLine);

            BOOL alloc = FALSE;
            BOOL global = FALSE;

            $$ = sNodeTree_create_store_variable($1, "", $$, alloc, global, gSName, gSLine); 
        }
        | '(' comma_exp ')' MOD_EQ exp { 
            unsigned int left = $2;
            unsigned int right = $5;

            $$ = sNodeTree_create_mod_eq(left, right, gSName, gSLine);
        }
        | FUNCTION_POINTER IDENTIFIER ')' MOD_EQ comma_exp {
            unsigned int left = sNodeTree_create_load_variable($2, gSName, gSLine);
            left = sNodeTree_create_derefference(left, gSName, gSLine); 
            unsigned int right = $5;

            $$ = sNodeTree_create_mod_eq(left, right, gSName, gSLine);
        }

        | IDENTIFIER AND_EQ comma_exp {
            $$ = sNodeTree_create_load_variable($1, gSName, gSLine);

            unsigned int int_value = $3;

            $$ = sNodeTree_create_and($$, int_value, gSName, gSLine);

            BOOL alloc = FALSE;
            BOOL global = FALSE;

            $$ = sNodeTree_create_store_variable($1, "", $$, alloc, global, gSName, gSLine); 
        }
        | '(' comma_exp ')' AND_EQ exp { 
            unsigned int left = $2;
            unsigned int right = $5;

            $$ = sNodeTree_create_and_eq(left, right, gSName, gSLine);
        }
        | FUNCTION_POINTER IDENTIFIER ')' AND_EQ comma_exp {
            unsigned int left = sNodeTree_create_load_variable($2, gSName, gSLine);
            left = sNodeTree_create_derefference(left, gSName, gSLine); 
            unsigned int right = $5;

            $$ = sNodeTree_create_and_eq(left, right, gSName, gSLine);
        }

        | IDENTIFIER XOR_EQ comma_exp {
            $$ = sNodeTree_create_load_variable($1, gSName, gSLine);

            unsigned int int_value = $3;

            $$ = sNodeTree_create_xor($$, int_value, gSName, gSLine);

            BOOL alloc = FALSE;
            BOOL global = FALSE;

            $$ = sNodeTree_create_store_variable($1, "", $$, alloc, global, gSName, gSLine); 
        }
        | '(' comma_exp ')' XOR_EQ exp { 
            unsigned int left = $2;
            unsigned int right = $5;

            $$ = sNodeTree_create_xor_eq(left, right, gSName, gSLine);
        }
        | FUNCTION_POINTER IDENTIFIER ')' XOR_EQ comma_exp {
            unsigned int left = sNodeTree_create_load_variable($2, gSName, gSLine);
            left = sNodeTree_create_derefference(left, gSName, gSLine); 
            unsigned int right = $5;

            $$ = sNodeTree_create_xor_eq(left, right, gSName, gSLine);
        }

        | IDENTIFIER OR_EQ comma_exp {
            $$ = sNodeTree_create_load_variable($1, gSName, gSLine);

            unsigned int int_value = $3;

            $$ = sNodeTree_create_or($$, int_value, gSName, gSLine);

            BOOL alloc = FALSE;
            BOOL global = FALSE;

            $$ = sNodeTree_create_store_variable($1, "", $$, alloc, global, gSName, gSLine); 
        }
        | '(' comma_exp ')' OR_EQ exp { 
            unsigned int left = $2;
            unsigned int right = $5;

            $$ = sNodeTree_create_or_eq(left, right, gSName, gSLine);
        }
        | FUNCTION_POINTER IDENTIFIER ')' OR_EQ comma_exp {
            unsigned int left = sNodeTree_create_load_variable($2, gSName, gSLine);
            left = sNodeTree_create_derefference(left, gSName, gSLine); 
            unsigned int right = $5;

            $$ = sNodeTree_create_or_eq(left, right, gSName, gSLine);
        }

        | IDENTIFIER LSHIFT_EQ comma_exp {
            $$ = sNodeTree_create_load_variable($1, gSName, gSLine);

            unsigned int int_value = $3;

            $$ = sNodeTree_create_lshift($$, int_value, gSName, gSLine);

            BOOL alloc = FALSE;
            BOOL global = FALSE;

            $$ = sNodeTree_create_store_variable($1, "", $$, alloc, global, gSName, gSLine); 
        }
        | '(' comma_exp ')' LSHIFT_EQ exp { 
            unsigned int left = $2;
            unsigned int right = $5;

            $$ = sNodeTree_create_lshift_eq(left, right, gSName, gSLine);
        }
        | FUNCTION_POINTER IDENTIFIER ')' LSHIFT_EQ comma_exp {
            unsigned int left = sNodeTree_create_load_variable($2, gSName, gSLine);
            left = sNodeTree_create_derefference(left, gSName, gSLine); 
            unsigned int right = $5;

            $$ = sNodeTree_create_lshift_eq(left, right, gSName, gSLine);
        }

        | IDENTIFIER RSHIFT_EQ comma_exp {
            $$ = sNodeTree_create_load_variable($1, gSName, gSLine);

            unsigned int int_value = $3;

            $$ = sNodeTree_create_rshift($$, int_value, gSName, gSLine);

            BOOL alloc = FALSE;
            BOOL global = FALSE;

            $$ = sNodeTree_create_store_variable($1, "", $$, alloc, global, gSName, gSLine); 
        }
        | '(' comma_exp ')' RSHIFT_EQ exp { 
            unsigned int left = $2;
            unsigned int right = $5;

            $$ = sNodeTree_create_rshift_eq(left, right, gSName, gSLine);
        }
        | FUNCTION_POINTER IDENTIFIER ')' RSHIFT_EQ comma_exp {
            unsigned int left = sNodeTree_create_load_variable($2, gSName, gSLine);
            left = sNodeTree_create_derefference(left, gSName, gSLine); 
            unsigned int right = $5;

            $$ = sNodeTree_create_rshift_eq(left, right, gSName, gSLine);
        }

        | '(' type ')' exp {
            char type_name[VAR_NAME_MAX];

            xstrncpy(type_name, $2, VAR_NAME_MAX);

            unsigned int lnode = $4;

            $$ = sNodeTree_create_cast(type_name, lnode, gSName, gSLine);
        }
        | SIZEOF '(' IDENTIFIER ')' {
            char* var_name = $3;

            $$ = sNodeTree_create_sizeof2(var_name, gSName, gSLine);
        }
        | SIZEOF '(' type ')' {
            char* type_name = $3;

            $$ = sNodeTree_create_sizeof1(type_name, gSName, gSLine);
        }
        ;

array_index: '[' exp ']' {
        array_index_num_dimention = 0;
        array_index_index_node[array_index_num_dimention] = $2;
        array_index_num_dimention++;

        if(array_index_num_dimention >= ARRAY_DIMENTION_MAX) {
            fprintf(stderr, "overflow array dimention number\n");
            exit(2);
        }
    }
    | '[' exp ']' array_index {
        array_index_index_node[array_index_num_dimention] = $2;
        array_index_num_dimention++;

        if(array_index_num_dimention >= ARRAY_DIMENTION_MAX) {
            fprintf(stderr, "overflow array dimention number\n");
            exit(2);
        }
    }
    ;

params: { 
        params = sNodeTree_create_params(gSName, gSLine); 
        $$ = params; 
    }
    | exp { 
        params = sNodeTree_create_params(gSName, gSLine); 
        append_param_to_params(params, $1); 
        $$ = params; 
    }
    | exp ',' params { 
        append_param_to_params(params, $1); 
        $$ = params; 
    }
    ;

%%
int yyerror(char *msg)
{
    fprintf(stderr, "%s %d: %s\n", gSName, gSLine, msg);
    return 0;
}
