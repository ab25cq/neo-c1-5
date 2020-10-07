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
%token <cval> POINTER
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
%type <rval> program 
%type <cval> type 
%type <cval> type_name
%type <cval> type_attribute
%type <node> function block block_end add_sub statment mult_div node func_params func_params_start exp store_var params elif_statment prepare_elif_statment object method_params struct_ fields union_;

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

type:
    type_name {
        xstrncpy($$, $1, VAR_NAME_MAX);
    }
    | type_name POINTER {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncat($$, $2, VAR_NAME_MAX);
    }
    | type_name POINTER '%' {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncat($$, $2, VAR_NAME_MAX);
        xstrncat($$, "%", VAR_NAME_MAX);
    }
    | type_attribute type_name {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncpy($$, $2, VAR_NAME_MAX);
    }
    | type_attribute type_name POINTER {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncat($$, $2, VAR_NAME_MAX);
        xstrncat($$, $3, VAR_NAME_MAX);
    }
    | type_attribute type_name POINTER '%' {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncat($$, $2, VAR_NAME_MAX);
        xstrncat($$, $3, VAR_NAME_MAX);
        xstrncat($$, "%", VAR_NAME_MAX);
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

type_name: IDENTIFIER {
        char type_name[VAR_NAME_MAX];
        get_typedef($1, type_name);

        xstrncpy($$, type_name, VAR_NAME_MAX);
    }
    | VOID {
        xstrncpy($$, "void",  VAR_NAME_MAX);
    }
    ;

struct_: STRUCT IDENTIFIER '{' fields '}' ';' {
            char* struct_name = $2;
            unsigned int fields = $4;
            BOOL anonymous = FALSE;

            $$ = sNodeTree_create_struct(struct_name, fields, anonymous, gSName, gSLine);
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
        | type IDENTIFIER ';' { fields = sNodeTree_create_struct_fields(gSName, gSLine); append_field_to_fields(fields, $2, $1); $$ = fields; }
        | fields type IDENTIFIER ';' { $$ = fields; append_field_to_fields(fields, $3, $2); }
        ;

function: 
        type IDENTIFIER ':' ':' IDENTIFIER '(' func_params_start func_params ')' '{' block '}' block_end {
            char* result_type = $1;

            char fun_name[VAR_NAME_MAX];
            xstrncpy(fun_name, $2, VAR_NAME_MAX);
            xstrncat(fun_name, "_", VAR_NAME_MAX);
            xstrncat(fun_name, $5, VAR_NAME_MAX);

            unsigned int function_params = $8;
            unsigned int node_block = $11;
            BOOL inline_ = FALSE;
            BOOL static_ = FALSE;

            $$ = it = sNodeTree_create_function(fun_name, function_params, result_type, node_block, var_arg, inline_, static_, gSName, gSLine);
        }
        | type IDENTIFIER '(' func_params_start func_params ')' '{' block '}' block_end {
            char* result_type = $1;
            char* fun_name = $2;
            unsigned int function_params = $5;
            unsigned int node_block = $8;
            BOOL inline_ = FALSE;
            BOOL static_ = FALSE;

            $$ = it = sNodeTree_create_function(fun_name, function_params, result_type, node_block, var_arg, inline_, static_, gSName, gSLine);
        }
        | INLINE type IDENTIFIER ':' ':' IDENTIFIER '(' func_params_start func_params ')' '{' block '}' block_end {
            char* result_type = $1;

            char fun_name[VAR_NAME_MAX];
            xstrncpy(fun_name, $3, VAR_NAME_MAX);
            xstrncat(fun_name, "_", VAR_NAME_MAX);
            xstrncat(fun_name, $6, VAR_NAME_MAX);

            unsigned int function_params = $9;
            unsigned int node_block = $12;
            BOOL inline_ = TRUE;
            BOOL static_ = FALSE;

            $$ = it = sNodeTree_create_function(fun_name, function_params, result_type, node_block, var_arg, inline_, static_, gSName, gSLine);
        }
        | INLINE type IDENTIFIER '(' func_params_start func_params ')' '{' block '}' block_end {
            char* result_type = $2;
            char* fun_name = $3;
            unsigned int function_params = $6;
            unsigned int node_block = $9;
            BOOL inline_ = TRUE;
            BOOL static_ = FALSE;

            $$ = it = sNodeTree_create_function(fun_name, function_params, result_type, node_block, var_arg, inline_, static_, gSName, gSLine);
        }
        | STATIC type IDENTIFIER ':' ':' IDENTIFIER '(' func_params_start func_params ')' '{' block '}' block_end {
            char* result_type = $2;

            char fun_name[VAR_NAME_MAX];
            xstrncpy(fun_name, $3, VAR_NAME_MAX);
            xstrncat(fun_name, "_", VAR_NAME_MAX);
            xstrncat(fun_name, $6, VAR_NAME_MAX);

            unsigned int function_params = $9;
            unsigned int node_block = $12;
            BOOL inline_ = FALSE;
            BOOL static_ = TRUE;

            $$ = it = sNodeTree_create_function(fun_name, function_params, result_type, node_block, var_arg, inline_, static_, gSName, gSLine);
        }
        | STATIC type IDENTIFIER '(' func_params_start func_params ')' '{' block '}' block_end {
            char* result_type = $2;
            char* fun_name = $3;
            unsigned int function_params = $6;
            unsigned int node_block = $9;
            BOOL inline_ = FALSE;
            BOOL static_ = TRUE;

            $$ = it = sNodeTree_create_function(fun_name, function_params, result_type, node_block, var_arg, inline_, static_, gSName, gSLine);
        }
        | type IDENTIFIER '(' func_params_start func_params ')' ';' {
            char* result_type = $1;
            char* fun_name = $2;
            unsigned int function_params = $5;
            $$ = it = sNodeTree_create_external_function(fun_name, function_params, result_type, var_arg, gSName, gSLine);
        }
        | EXTERN type IDENTIFIER '(' func_params_start func_params ')' ';' {
            char* result_type = $2;
            char* fun_name = $3;
            unsigned int function_params = $6;
            $$ = it = sNodeTree_create_external_function(fun_name, function_params, result_type, var_arg, gSName, gSLine);
        }
        ;

func_params_start: {
        var_arg = FALSE;
        }
        ;

func_params:       { func_params = sNodeTree_create_function_params(gSName, gSLine); $$ = func_params; }
        | VOID { func_params = sNodeTree_create_function_params(gSName, gSLine); $$ = func_params; }
        | type IDENTIFIER { func_params = sNodeTree_create_function_params(gSName, gSLine); append_param_to_function_params(func_params, $1, $2); $$ = func_params; }
        | func_params ',' type IDENTIFIER { $$ = func_params; append_param_to_function_params(func_params, $3, $4); }
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
    | type IDENTIFIER ';' {
        char* type_name = $1;
        char* var_name = $2;
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

exp: store_var { $$ = $1; }
    ;


store_var:  add_sub                  { $$ = $1; }
     | type IDENTIFIER '=' add_sub  { $$ = sNodeTree_create_store_variable($2, $1, $4, TRUE, gSName, gSLine); }
     | IDENTIFIER '=' add_sub { $$ = sNodeTree_create_store_variable($1, "", $3, FALSE, gSName, gSLine); }
     ;

add_sub:  mult_div                  { $$ = $1; }
        | add_sub '+' mult_div      { $$ = it = sNodeTree_create_add($1, $3, 0, gSName, gSLine); }
        | add_sub '-' mult_div      { $$ = it = sNodeTree_create_sub($1, $3, 0, gSName, gSLine); }
        ;

mult_div: node                    { $$ = $1; }
        | mult_div POINTER node       { $$ = it = sNodeTree_create_mult($1, $3, 0, gSName, gSLine); }
        | mult_div '/' node       { $$ = it = sNodeTree_create_div($1, $3, 0, gSName, gSLine); }
        ;

node: 
        INTNUM                { $$ = it = sNodeTree_create_int_value($1, gSName, gSLine); }
        | CSTRING {
            $$ = it = sNodeTree_create_c_string($1, gSName, gSLine);
        }
        | '(' exp ')'    { $$ = it = $2; }
        | IDENTIFIER '(' ')' {
            $$ = sNodeTree_create_function_call($1, 0, FALSE, gSName, gSLine);
        }
        | IDENTIFIER {
            $$ = sNodeTree_create_load_variable($1, gSName, gSLine);
        }
        | IDENTIFIER '(' params ')' {
            $$ = sNodeTree_create_function_call($1, $3, FALSE, gSName, gSLine);
        }
        | object '.' IDENTIFIER '(' method_params ')' {
            $$ = sNodeTree_create_function_call($3, $5, TRUE, gSName, gSLine);
        }
        | object '.' IDENTIFIER '(' ')' {
            $$ = sNodeTree_create_function_call($3, $1, TRUE, gSName, gSLine);
        }
        | TOKEN_TRUE {
            $$ = sNodeTree_create_true(gSName, gSLine);
        }
        | TOKEN_FALSE {
            $$ = sNodeTree_create_false(gSName, gSLine);
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
        | type '{' block '}' block_end {
            char* type_name = $1;
            unsigned int block = $3;

            $$ = sNodeTree_create_coroutine(type_name, block, gSName, gSLine);
        }
        ;

object:
        exp {
            params = sNodeTree_create_params(gSName, gSLine); 
            append_param_to_params(params, $1);
            $$ = params;
        }
        ;

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
