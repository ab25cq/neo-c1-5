%{
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "common.h"

unsigned int it;
unsigned int prev_block;
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
char variable_name[VAR_NAME_MAX];
char type_params[VAR_NAME_MAX];
int num_struct_generics_types;
char struct_generics_types[GENERICS_TYPES_MAX][VAR_NAME_MAX];
int num_function_generics_types;
char function_generics_types[GENERICS_TYPES_MAX][VAR_NAME_MAX];
int num_method_generics_types;
char method_generics_types[GENERICS_TYPES_MAX][VAR_NAME_MAX];
unsigned int object;
BOOL inline_;
BOOL static_;
BOOL inherit_;
%}

%union {
    int ival;
    unsigned int node;
    char cval[128];
    char sval[512];
    int rval;
}

%token <ival> INTNUM 
%token <cval> IDENTIFIER
%token <sval> CSTRING
%token <cval> VOID
%token <cval> IF
%token <cval> ELSE
%token <cval> EXTERN
%token <cval> RETURN
%token <cval> STAR
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
%token <cval> FUNCTION_POINTER
%token <cval> INHERIT
%type <rval> program 
%type <cval> type 
%type <cval> type_name
%type <cval> type_attribute
%type <cval> function_result_type_attribute
%type <cval> type_and_variable_name
%type <cval> type_params_start
%type <cval> type_params
%type <cval> generics_types 
%type <cval> function_struct_type_name 
%type <cval> function_generics_types 
%type <cval> function_struct_type 
%type <cval> function_result_type 
%type <node> function block block_end statment node func_params func_params_start exp params elif_statment prepare_elif_statment method_params struct_ fields union_ function_generics_types_start method_generics_types_start method_generics_type method_generics_types;

%left ANDAND OROR
%left EQEQ NOT_EQ
%left '+' '-'
%left '*' '/'

%start program

%%
program: function {
            $$ = compile($1, &cinfo);
        }
        | struct_ {
            $$ = compile($1, &cinfo);
        }
        | union_ {
            $$ = compile($1, &cinfo);
        }
        | program function {
            $$ = compile($2, &cinfo);
        }
        | program struct_ {
            $$ = compile($2, &cinfo);
        }
        | program union_ {
            $$ = compile($2, &cinfo);
        }
        ;

type_and_variable_name: type IDENTIFIER {
        char type_name[VAR_NAME_MAX];

        xstrncpy(type_name, $1, VAR_NAME_MAX);
    
        xstrncpy($$, type_name, VAR_NAME_MAX);
        xstrncpy(variable_name, $2, VAR_NAME_MAX);
    }
    | type FUNCTION_POINTER IDENTIFIER ')' '(' type_params_start type_params ')' {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncat($$, " lambda(", VAR_NAME_MAX);
        xstrncat($$, $7, VAR_NAME_MAX);
        xstrncat($$, ")", VAR_NAME_MAX);

        xstrncpy(variable_name, $3, VAR_NAME_MAX);
    }
    ;

type_params_start: {
    xstrncpy(type_params, "", VAR_NAME_MAX);
    xstrncpy($$, type_params, VAR_NAME_MAX);
    }
    ;

type_params: {
        xstrncpy($$, type_params, VAR_NAME_MAX);
    }
    | type {
        xstrncat(type_params, $1, VAR_NAME_MAX);
        xstrncpy($$, type_params, VAR_NAME_MAX);
    }
    | type_params ',' type {
        xstrncat(type_params, ",", VAR_NAME_MAX);
        xstrncat(type_params, $3, VAR_NAME_MAX);
        xstrncpy($$, type_params, VAR_NAME_MAX);
    };

function_struct_type:
    function_struct_type_name {
        xstrncpy($$, $1, VAR_NAME_MAX);
    }
    | function_struct_type_name STAR {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncat($$, $2, VAR_NAME_MAX);
    }
    | function_struct_type_name STAR '%' {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncat($$, $2, VAR_NAME_MAX);
        xstrncat($$, "%", VAR_NAME_MAX);
    }
    | type_attribute function_struct_type_name {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncpy($$, $2, VAR_NAME_MAX);
    }
    | type_attribute function_struct_type_name STAR {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncat($$, $2, VAR_NAME_MAX);
        xstrncat($$, $3, VAR_NAME_MAX);
    }
    | type_attribute function_struct_type_name STAR '%' {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncat($$, $2, VAR_NAME_MAX);
        xstrncat($$, $3, VAR_NAME_MAX);
        xstrncat($$, "%", VAR_NAME_MAX);
    }
    ;

type:
    type_name {
        xstrncpy($$, $1, VAR_NAME_MAX);
    }
    | type_name STAR {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncat($$, $2, VAR_NAME_MAX);
    }
    | type_name STAR '%' {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncat($$, $2, VAR_NAME_MAX);
        xstrncat($$, "%", VAR_NAME_MAX);
    }
    | type_attribute type_name {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncpy($$, $2, VAR_NAME_MAX);
    }
    | type_attribute type_name STAR {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncat($$, $2, VAR_NAME_MAX);
        xstrncat($$, $3, VAR_NAME_MAX);
    }
    | type_attribute type_name STAR '%' {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncat($$, $2, VAR_NAME_MAX);
        xstrncat($$, $3, VAR_NAME_MAX);
        xstrncat($$, "%", VAR_NAME_MAX);
    }
    ;

function_result_type:
    method_generics_types_start method_generics_type type_name {
        inline_ = FALSE;
        static_ = FALSE;
        inherit_ = FALSE;
        xstrncpy($$, $3, VAR_NAME_MAX);
    }
    | method_generics_types_start method_generics_type type_name STAR {
        inline_ = FALSE;
        static_ = FALSE;
        inherit_ = FALSE;
        xstrncpy($$, $3, VAR_NAME_MAX);
        xstrncat($$, $4, VAR_NAME_MAX);
    }
    | method_generics_types_start method_generics_type type_name STAR '%' {
        inline_ = FALSE;
        static_ = FALSE;
        inherit_ = FALSE;
        xstrncpy($$, $3, VAR_NAME_MAX);
        xstrncat($$, $4, VAR_NAME_MAX);
        xstrncat($$, "%", VAR_NAME_MAX);
    }
    | method_generics_types_start method_generics_type function_result_type_attribute type_name {
        xstrncpy($$, $3, VAR_NAME_MAX);
        xstrncpy($$, $4, VAR_NAME_MAX);
    }
    | method_generics_types_start method_generics_type function_result_type_attribute type_name STAR {
        xstrncpy($$, $3, VAR_NAME_MAX);
        xstrncat($$, $4, VAR_NAME_MAX);
        xstrncat($$, $5, VAR_NAME_MAX);
    }
    | method_generics_types_start method_generics_type function_result_type_attribute type_name STAR '%' {
        xstrncpy($$, $3, VAR_NAME_MAX);
        xstrncat($$, $4, VAR_NAME_MAX);
        xstrncat($$, $5, VAR_NAME_MAX);
        xstrncat($$, "%", VAR_NAME_MAX);
    }
    ;

method_generics_type: {
    }
    | TEMPLATE '<' method_generics_types '>' {
    }
    ;

method_generics_types_start: {
    num_method_generics_types = 0;
    }
    ;

method_generics_types: IDENTIFIER {
        xstrncpy(method_generics_types[0], $1, VAR_NAME_MAX);

        num_method_generics_types = 1;
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

type_attribute: { 
        xstrncpy($$, "", VAR_NAME_MAX); 
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
    }
    ;

function_result_type_attribute: { 
        inline_ = FALSE;
        static_ = FALSE;
        inherit_ = FALSE;
        xstrncpy($$, "", VAR_NAME_MAX); 
    }
    | function_result_type_attribute CONST {
        xstrncpy($$, $1, VAR_NAME_MAX); 
        xstrncat($$, "const ", VAR_NAME_MAX); 
    }
    | function_result_type_attribute UNSIGNED {
        xstrncpy($$, $1, VAR_NAME_MAX); 
        xstrncat($$, "unsigned ", VAR_NAME_MAX); 
    }
    | function_result_type_attribute SIGNED {
        xstrncpy($$, $1, VAR_NAME_MAX); 
        xstrncat($$, "signed ", VAR_NAME_MAX); 
    }
    | function_result_type_attribute STATIC {
        xstrncpy($$, $1, VAR_NAME_MAX); 
        static_ = TRUE;
    }
    | function_result_type_attribute INLINE {
        xstrncpy($$, $1, VAR_NAME_MAX); 
        inline_ = TRUE;
    }
    | function_result_type_attribute INHERIT {
        xstrncpy($$, $1, VAR_NAME_MAX); 
        inherit_ = TRUE;
    }
    ;

type_name: IDENTIFIER {
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
    | IDENTIFIER '<' generics_types '>' {
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
        xstrncat(type_name, $3, VAR_NAME_MAX);
        xstrncat(type_name, ">", VAR_NAME_MAX);

        xstrncpy($$, type_name, VAR_NAME_MAX);
    }
    | VOID {
        xstrncpy($$, "void",  VAR_NAME_MAX);
    }
    ;

function_struct_type_name: IDENTIFIER function_generics_types_start {
        char type_name[VAR_NAME_MAX];
        get_typedef($1, type_name);

        xstrncpy($$, type_name, VAR_NAME_MAX);
    }
    | IDENTIFIER '<' function_generics_types_start function_generics_types '>' {
        char type_name[VAR_NAME_MAX];
        get_typedef($1, type_name);

        xstrncat(type_name, "<", VAR_NAME_MAX);
        xstrncat(type_name, $4, VAR_NAME_MAX);
        xstrncat(type_name, ">", VAR_NAME_MAX);

        xstrncpy($$, type_name, VAR_NAME_MAX);
    }
    | function_generics_types_start VOID {
        xstrncpy($$, "void",  VAR_NAME_MAX);
    }
    ;

struct_: 
        STRUCT IDENTIFIER '<' struct_generics_types_start struct_generics_types '>' '{' fields '}' ';' {
            char* struct_name = $2;
            unsigned int fields = $8;
            BOOL anonymous = FALSE;
            BOOL generics = num_struct_generics_types > 0;

            $$ = sNodeTree_create_struct(struct_name, fields, generics, anonymous, gSName, gSLine);
        }
        | STRUCT IDENTIFIER struct_generics_types_start '{' fields '}' ';' {
            char* struct_name = $2;
            unsigned int fields = $5;
            BOOL anonymous = FALSE;
            BOOL generics = FALSE;

            $$ = sNodeTree_create_struct(struct_name, fields, generics, anonymous, gSName, gSLine);
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

function_generics_types: type {
        char type_name[VAR_NAME_MAX];
        get_typedef($1, type_name);

        xstrncpy(function_generics_types[num_function_generics_types], type_name, VAR_NAME_MAX);
        num_function_generics_types++;

        xstrncpy($$, type_name, VAR_NAME_MAX);
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

function_generics_types_start: {
    num_function_generics_types = 0;
    };

struct_generics_types_start: {
    num_struct_generics_types = 0;
    };

struct_generics_types: IDENTIFIER {
        xstrncpy(struct_generics_types[0], $1, VAR_NAME_MAX);

        num_struct_generics_types = 1;
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

union_: UNION IDENTIFIER '{' fields '}' ';' { char* union_name = $2;
            unsigned int fields = $4;
            BOOL anonymous = FALSE;

            $$ = sNodeTree_create_union(union_name, fields, anonymous, gSName, gSLine);
        }
        ;

fields:  { 
            fields = sNodeTree_create_struct_fields(gSName, gSLine); $$ = fields; 
        }
        | type_and_variable_name ';' { fields = sNodeTree_create_struct_fields(gSName, gSLine); append_field_to_fields(fields, variable_name, $1); $$ = fields; }
        | fields type_and_variable_name ';' { $$ = fields; append_field_to_fields(fields, variable_name, $2); }
        ;

function: 
        function_result_type function_struct_type ':' ':' IDENTIFIER '(' func_params_start func_params ')' '{' block '}' block_end 
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
            xstrncat(fun_name, $5, VAR_NAME_MAX);

            char fun_base_name[VAR_NAME_MAX];

            xstrncpy(fun_base_name, $5, VAR_NAME_MAX);

            unsigned int function_params = $8;
            unsigned int node_block = $11;
            BOOL generics = num_function_generics_types > 0;
            BOOL method_generics = num_method_generics_types > 0;

            $$ = it = sNodeTree_create_function(fun_name, fun_base_name, function_params, result_type, node_block, var_arg, inline_, static_, inherit_, generics, method_generics, gSName, gSLine);
        }
        | function_result_type IDENTIFIER '(' func_params_start func_params ')' '{' block '}' block_end {
            char* result_type = $1;
            char* fun_name = $2;
            unsigned int function_params = $5;
            unsigned int node_block = $8;
            BOOL generics = FALSE;
            BOOL method_generics = num_method_generics_types > 0;

            $$ = it = sNodeTree_create_function(fun_name, fun_name, function_params, result_type, node_block, var_arg, inline_, static_, inherit_, generics, num_method_generics_types, gSName, gSLine);
        }
        | function_result_type IDENTIFIER '(' func_params_start func_params ')' ';' {
            char* result_type = $1;
            char* fun_name = $2;
            unsigned int function_params = $5;
            $$ = it = sNodeTree_create_external_function(fun_name, function_params, result_type, var_arg, inherit_, gSName, gSLine);
        }
        | EXTERN function_result_type IDENTIFIER '(' func_params_start func_params ')' ';' {
            char* result_type = $2;
            char* fun_name = $3;
            unsigned int function_params = $6;
            $$ = it = sNodeTree_create_external_function(fun_name, function_params, result_type, var_arg, inherit_, gSName, gSLine);
        }
        ;

func_params_start: {
        var_arg = FALSE;
        }
        ;

func_params:       { func_params = sNodeTree_create_function_params(gSName, gSLine); $$ = func_params; }
        | VOID { func_params = sNodeTree_create_function_params(gSName, gSLine); $$ = func_params; }
        | type_and_variable_name { func_params = sNodeTree_create_function_params(gSName, gSLine); append_param_to_function_params(func_params, $1, variable_name); $$ = func_params; }
        | func_params ',' type_and_variable_name { $$ = func_params; append_param_to_function_params(func_params, $3, variable_name); }
        | func_params ',' '.' '.' '.' {
            var_arg = TRUE;
        }
        ;

block:  statment                  { 
            prev_block = block;
            block = sNodeTree_create_block(gSName, gSLine); append_node_to_node_block(block, $1); $$ = block; 
        } 
        | block statment          { 
            $$ = block; append_node_to_node_block(block, $2); 
        }
        ;

block_end: {
        block = prev_block;
        $$ = block;
        };

statment: exp ';'              { $$ = $1; }
    | RETURN ';'               { $$ = sNodeTree_create_return(0, gSName, gSLine); }
    | RETURN '(' exp ')' ';'   { $$ = sNodeTree_create_return($3, gSName, gSLine); }
    | RETURN exp ';'  { $$ = sNodeTree_create_return($2, gSName, gSLine); }
    | IF '(' exp ')' '{' block '}' block_end {
        unsigned int if_exp = $3;
        unsigned int if_block = $6;
        int elif_num = 0;
        unsigned int elif_exps[ELIF_NUM_MAX];
        unsigned int elif_blocks[ELIF_NUM_MAX];
        unsigned else_block = 0;
        
        $$ = sNodeTree_create_if(if_exp, if_block, elif_num, elif_exps, elif_blocks, else_block, gSName, gSLine);
    }
    | IF '(' exp ')' '{' block '}' block_end ELSE '{' block '}' block_end 
    {
        unsigned int if_exp = $3;
        unsigned int if_block = $6;
        int elif_num = 0;
        unsigned int elif_exps[ELIF_NUM_MAX];
        unsigned int elif_blocks[ELIF_NUM_MAX];
        unsigned int else_block = $11;
        
        $$ = sNodeTree_create_if(if_exp, if_block, elif_num, elif_exps, elif_blocks, else_block, gSName, gSLine);
    }
    | IF '(' exp ')' '{' block '}' block_end ELSE IF prepare_elif_statment elif_statment ELSE '{' block '}' block_end 
    {
        unsigned int if_exp = $3;
        unsigned int if_block = $6;
        unsigned int else_block = $15;
        
        $$ = sNodeTree_create_if(if_exp, if_block, elif_num, elif_exps, elif_blocks, else_block, gSName, gSLine);
    }
    | IF '(' exp ')' '{' block '}' block_end ELSE IF prepare_elif_statment elif_statment {
        unsigned int if_exp = $3;
        unsigned int if_block = $6;
        unsigned else_block = 0;
        
        $$ = sNodeTree_create_if(if_exp, if_block, elif_num, elif_exps, elif_blocks, else_block, gSName, gSLine);
    }
    | type_and_variable_name ';' {
        char* type_name = $1;
        char* var_name = variable_name;
        BOOL global = FALSE;
        BOOL extern_ = FALSE;

        $$ = sNodeTree_create_define_variable(type_name, var_name, global, extern_, gSName, gSLine);
    }
    ;

prepare_elif_statment: '(' exp ')' '{' block '}' block_end {
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
    ELSE IF '(' exp ')' '{' block '}' block_end {
        elif_exps[elif_num] = $4;
        elif_blocks[elif_num] = $7;
        elif_num++;

        if(elif_num >= ELIF_NUM_MAX) {
            fprintf(stderr, "overflow else if number\n");
            exit(2);
        }
    }
    | elif_statment ELSE IF '(' exp ')' '{' block '}' block_end {
        elif_exps[elif_num] = $5;
        elif_blocks[elif_num] = $8;
        elif_num++;

        if(elif_num >= ELIF_NUM_MAX) {
            fprintf(stderr, "overflow else if number\n");
            exit(2);
        }
    }
    ;

exp: node {
        $$ = $1;
    }
    | exp '+' exp      { $$ = sNodeTree_create_add($1, $3, 0, gSName, gSLine); }
    | exp '-' exp    { $$ = sNodeTree_create_sub($1, $3, 0, gSName, gSLine); }
    | exp STAR exp   { $$ = sNodeTree_create_mult($1, $3, 0, gSName, gSLine); }
    | exp '/' exp    { $$ = sNodeTree_create_div($1, $3, 0, gSName, gSLine); }
    | exp EQEQ exp   { $$ = sNodeTree_create_equals($1, $3, gSName, gSLine); }
    | exp NOT_EQ exp { $$ = sNodeTree_create_not_equals($1, $3, gSName, gSLine); }
    | exp ANDAND exp { $$ = sNodeTree_create_and_and($1, $3, gSName, gSLine); }
    | exp OROR exp   { $$ = sNodeTree_create_or_or($1, $3, gSName, gSLine); }
    | '(' exp ')'    { $$ = $2; }
    ;

node: 
        INTNUM                { $$ = it = sNodeTree_create_int_value($1, gSName, gSLine); }
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
        | type_and_variable_name '=' exp  { $$ = sNodeTree_create_store_variable(variable_name, $1, $3, TRUE, gSName, gSLine); }
        | IDENTIFIER '=' exp { $$ = sNodeTree_create_store_variable($1, "", $3, FALSE, gSName, gSLine); }

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
        | exp '.' IDENTIFIER '(' method_params_start method_params ')' {
            append_param_to_params($6, $1);
            $$ = sNodeTree_create_function_call($3, $6, TRUE, FALSE, gSName, gSLine);
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
        | exp '.' INHERIT '(' method_params_start method_params ')' {
            append_param_to_params($6, $1);
            $$ = sNodeTree_create_function_call("inherit", $6, TRUE, TRUE, gSName, gSLine);
        }
        | exp '.' IDENTIFIER {
            $$ = sNodeTree_create_load_field($3, $1, gSName, gSLine);
        }
        | exp '.' IDENTIFIER '=' exp  { 
            $$ = sNodeTree_create_store_field($3, $1, $5, gSName, gSLine); 
        }
        | NEW type {
            char* type_name = $2;
            unsigned int object_num = 0;

            $$ = sNodeTree_create_object(type_name, object_num, gSName, gSLine);
        }
        | NEW type '[' exp ']'  {
            char* type_name = $2;
            unsigned int object_num = $4;

            $$ = sNodeTree_create_object(type_name, object_num, gSName, gSLine);
        }
        | CLONE exp {
            unsigned int exp = $2;

            $$ = sNodeTree_create_clone(exp, gSName, gSLine);
        }
        | type LAMBDA '(' func_params_start func_params ')' '{' block '}' block_end {
            char* result_type_name = $1;
            unsigned int function_params = $5;
            unsigned int node_block = $8;

            $$ = sNodeTree_create_coroutine(function_params, result_type_name, node_block, var_arg, gSName, gSLine);
        }
        | exp '(' params ')' {
            $$ = sNodeTree_create_lambda_call($1, $3, gSName, gSLine);
        }
        ;

method_params_start: {
        params = sNodeTree_create_params(gSName, gSLine); 
        };

method_params :
        exp { append_param_to_params(params, $1); $$ = params; }
        | exp ',' method_params { $$ = params; append_param_to_params(params, $1); }
        ;

params :       { params = sNodeTree_create_params(gSName, gSLine); $$ = params; }
        | exp { params = sNodeTree_create_params(gSName, gSLine); append_param_to_params(params, $1); $$ = params; }
        | exp ',' params { $$ = params; append_param_to_params(params, $1); }
        ;

%%
int yyerror(char *msg)
{
    fprintf(stderr, "%s %d: %s\n", gSName, gSLine, msg);
    return 0;
}
