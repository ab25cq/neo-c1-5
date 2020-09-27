%{
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "common.h"

unsigned int it;
unsigned int block;
unsigned int func_params;
unsigned int params;
extern int yyerror(char *msg);
extern int yylex();
sCompileInfo cinfo;
%}

%union {
    int ival;
    unsigned int node;
    char cval[128];
    int rval;
}

%token <ival> INTNUM 
%token <cval> IDENTIFIER
%token <cval> VOID
%token <cval> EXTERN
%token <cval> RETURN
%type <rval> program 
%type <node> function block add_sub return_op mult_div node func_params var function_call params;

%start program

%%
program : { 
            memset(&cinfo, 0, sizeof(sCompileInfo));
            cinfo.no_output = FALSE;
            cinfo.err_num = 0;
            cinfo.stack_num = 0;
            cinfo.type = NULL;
        }
        | program function {
            $$ = compile($1, &cinfo);
        }
        ;

function : 
        VOID IDENTIFIER '(' func_params ')' '{' block '}' '\n' {
            char* result_type = "void";
            char* fun_name = $2;
            unsigned int function_params = $4;
            unsigned int node_block = $7;
            $$ = it = sNodeTree_create_function(fun_name, function_params, result_type, node_block, gSName, gSLine);
        }
        | IDENTIFIER IDENTIFIER '(' func_params ')' '{' block '}' '\n' {
            char* result_type = $1;
            char* fun_name = $2;
            unsigned int function_params = $4;
            unsigned int node_block = $7;
            $$ = it = sNodeTree_create_function(fun_name, function_params, result_type, node_block, gSName, gSLine);
        }
        | IDENTIFIER IDENTIFIER '(' func_params ')' ';' '\n' {
            char* result_type = $1;
            char* fun_name = $2;
            unsigned int function_params = $4;
            $$ = it = sNodeTree_create_external_function(fun_name, function_params, result_type, gSName, gSLine);
        }
        | VOID IDENTIFIER '(' func_params ')' ';' '\n' {
            char* result_type = "void";
            char* fun_name = $2;
            unsigned int function_params = $4;
            $$ = it = sNodeTree_create_external_function(fun_name, function_params, result_type, gSName, gSLine);
        }
        | EXTERN IDENTIFIER IDENTIFIER '(' func_params ')' ';' '\n' {
            char* result_type = $2;
            char* fun_name = $3;
            unsigned int function_params = $5;
            $$ = it = sNodeTree_create_external_function(fun_name, function_params, result_type, gSName, gSLine);
        }
        | EXTERN VOID IDENTIFIER '(' func_params ')' ';' '\n' {
            char* result_type = "void";
            char* fun_name = $3;
            unsigned int function_params = $5;
            $$ = it = sNodeTree_create_external_function(fun_name, function_params, result_type, gSName, gSLine);
        }
        ;

func_params :       { func_params = sNodeTree_create_function_params(gSName, gSLine); $$ = func_params; }
        | VOID { func_params = sNodeTree_create_function_params(gSName, gSLine); $$ = func_params; }
        | IDENTIFIER IDENTIFIER { func_params = sNodeTree_create_function_params(gSName, gSLine); append_param_to_function_params(func_params, $1, $2); $$ = func_params; }
        | func_params ',' IDENTIFIER IDENTIFIER { $$ = func_params; append_param_to_function_params(func_params, $3, $4); }
        ;

block:  return_op                  { block = sNodeTree_create_block(gSName, gSLine); append_node_to_node_block(block, $1); $$ = block; } 
        | return_op ';'            { block = sNodeTree_create_block(gSName, gSLine); append_node_to_node_block(block, $1); $$ = block;  }
        | return_op ';' '\n'       { block = sNodeTree_create_block(gSName, gSLine); append_node_to_node_block(block, $1); $$ = block;  }
        | block return_op ';'      { $$ = block; append_node_to_node_block(block, $2); }
        | block return_op ';' '\n' { $$ = block; append_node_to_node_block(block, $2); }
        ;

return_op: var                  { $$ = $1; }
    | RETURN '(' var ')'        { $$ = sNodeTree_create_return($3, gSName, gSLine); }
    | RETURN var  { $$ = sNodeTree_create_return($2, gSName, gSLine); }
    ;


var:  add_sub                  { $$ = $1; }
     | IDENTIFIER IDENTIFIER '=' add_sub  { $$ = sNodeTree_create_store_variable($2, $1, $4, TRUE, gSName, gSLine); }
     | IDENTIFIER '=' add_sub { $$ = sNodeTree_create_store_variable($1, "", $3, FALSE, gSName, gSLine); }
     ;

add_sub:  mult_div                  { $$ = $1; }
        | add_sub '+' mult_div      { $$ = it = sNodeTree_create_add($1, $3, 0, gSName, gSLine); }
        | add_sub '-' mult_div      { $$ = it = sNodeTree_create_sub($1, $3, 0, gSName, gSLine); }
        ;

mult_div: node                    { $$ = $1; }
        | mult_div '*' node       { $$ = it = sNodeTree_create_mult($1, $3, 0, gSName, gSLine); }
        | mult_div '/' node       { $$ = it = sNodeTree_create_div($1, $3, 0, gSName, gSLine); }
        ;

node  : 
        INTNUM                { $$ = it = sNodeTree_create_int_value($1, gSName, gSLine); }
        | '(' mult_div ')'    { $$ = it = $2; }
        | function_call { $$ = it = $1; }
        ;

function_call:
        IDENTIFIER '(' params ')' {
            $$ = sNodeTree_create_function_call($1, $3, gSName, gSLine);
        }
        ;

params :       { params = sNodeTree_create_params(gSName, gSLine); $$ = params; }
        | block { params = sNodeTree_create_params(gSName, gSLine); append_param_to_params(params, $1); $$ = params; }
        | block ',' params { $$ = params; append_param_to_params(params, $1); }
        ;

%%
int yyerror(char *msg)
{
    fprintf(stderr, "%s %d: %s\n", gSName, gSLine, msg);
    return 0;
}
