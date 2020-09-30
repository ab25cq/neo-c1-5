%{
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "common.h"

unsigned int it;
unsigned int prev_block;
unsigned int block;
unsigned int func_params;
unsigned int params;
extern int yyerror(char *msg);
extern int yylex();
sCompileInfo cinfo;
unsigned int elif_exps[ELIF_NUM_MAX];
unsigned int elif_blocks[ELIF_NUM_MAX];
int elif_num;
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
%token <cval> HEAP
%type <rval> program 
%type <cval> type 
%type <node> function block block_end add_sub statment mult_div node func_params exp store_var params elif_statment prepare_elif_statment else_statment;

%start program

%%
program: function { 
            $$ = compile($1, &cinfo);
        }
        | program function {
            $$ = compile($2, &cinfo);
        }
        ;

type:
    IDENTIFIER {
        xstrncpy($$, $1, VAR_NAME_MAX);
    }
    | IDENTIFIER POINTER {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncat($$, $2, VAR_NAME_MAX);
    }
    | IDENTIFIER POINTER HEAP {
        xstrncpy($$, $1, VAR_NAME_MAX);
        xstrncat($$, $2, VAR_NAME_MAX);
        xstrncat($$, $3, VAR_NAME_MAX);
    }
    ;

function: 
        VOID IDENTIFIER '(' func_params ')' '{' block '}' block_end {
            char* result_type = "void";
            char* fun_name = $2;
            unsigned int function_params = $4;
            unsigned int node_block = $7;
            $$ = it = sNodeTree_create_function(fun_name, function_params, result_type, node_block, gSName, gSLine);
        }
        | type IDENTIFIER '(' func_params ')' '{' block '}' block_end {
            char* result_type = $1;
            char* fun_name = $2;
            unsigned int function_params = $4;
            unsigned int node_block = $7;
            $$ = it = sNodeTree_create_function(fun_name, function_params, result_type, node_block, gSName, gSLine);
        }
        | type IDENTIFIER '(' func_params ')' ';' {
            char* result_type = $1;
            char* fun_name = $2;
            unsigned int function_params = $4;
            $$ = it = sNodeTree_create_external_function(fun_name, function_params, result_type, gSName, gSLine);
        }
        | VOID IDENTIFIER '(' func_params ')' ';' {
            char* result_type = "void";
            char* fun_name = $2;
            unsigned int function_params = $4;
            $$ = it = sNodeTree_create_external_function(fun_name, function_params, result_type, gSName, gSLine);
        }
        | EXTERN type IDENTIFIER '(' func_params ')' ';' {
            char* result_type = $2;
            char* fun_name = $3;
            unsigned int function_params = $5;
            $$ = it = sNodeTree_create_external_function(fun_name, function_params, result_type, gSName, gSLine);
        }
        | EXTERN VOID IDENTIFIER '(' func_params ')' ';' {
            char* result_type = "void";
            char* fun_name = $3;
            unsigned int function_params = $5;
            $$ = it = sNodeTree_create_external_function(fun_name, function_params, result_type, gSName, gSLine);
        }
        ;

func_params:       { func_params = sNodeTree_create_function_params(gSName, gSLine); $$ = func_params; }
        | VOID { func_params = sNodeTree_create_function_params(gSName, gSLine); $$ = func_params; }
        | type IDENTIFIER { func_params = sNodeTree_create_function_params(gSName, gSLine); append_param_to_function_params(func_params, $1, $2); $$ = func_params; }
        | func_params ',' type IDENTIFIER { $$ = func_params; append_param_to_function_params(func_params, $3, $4); }
        ;

block:  statment                  { 
            prev_block = block;
            block = sNodeTree_create_block(gSName, gSLine); append_node_to_node_block(block, $1); $$ = block; 
        } 
        | statment                { 
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
    | IF '(' exp ')' '{' block '}' block_end prepare_elif_statment elif_statment {
        unsigned int if_exp = $3;
        unsigned int if_block = $6;
        unsigned else_block = 0;
        
        $$ = sNodeTree_create_if(if_exp, if_block, elif_num, elif_exps, elif_blocks, else_block, gSName, gSLine);
    }
    | IF '(' exp ')' '{' block '}' block_end prepare_elif_statment elif_statment else_statment {
        unsigned int if_exp = $3;
        unsigned int if_block = $6;
        unsigned int else_block = $11;
        
        $$ = sNodeTree_create_if(if_exp, if_block, elif_num, elif_exps, elif_blocks, else_block, gSName, gSLine);
    }
    ;

prepare_elif_statment: {
    elif_num = 0;
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

else_statment: 
    ELSE '{' block '}' block_end {
        $$ = $3;
    }
    ;

exp: 
    store_var { $$ = $1; }
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
            $$ = sNodeTree_create_function_call($1, 0, gSName, gSLine);
        }
        | IDENTIFIER {
            $$ = sNodeTree_create_load_variable($1, gSName, gSLine);
        }
        | IDENTIFIER '(' params ')' {
            $$ = sNodeTree_create_function_call($1, $3, gSName, gSLine);
        }
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
