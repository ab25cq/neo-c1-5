#include "common.h"
#include <libgen.h>

BOOL gNCDebug = FALSE;
char gMainModulePath[PATH_MAX];

static void compiler_init()
{
    init_node_types();
    init_vtable();
    init_typedef();
    init_nodes();
    class_init();
    llvm_init();
}

static void compiler_final()
{
    llvm_final();
    class_final();
    final_vtable();
    free_nodes();
    free_node_types();
}

char* gVersion = "0.0.1";

char gSName[PATH_MAX];
int gSLine;
int gErrNum;

void parser_err_msg(char* msg)
{
    static int output_num = 0;

    if(output_num < PARSER_ERR_MSG_MAX) {
        fprintf(stderr, "%s:%d: %s\n", gSName, gSLine, msg);
    }

    output_num++;
}

int main(int argc, char** argv)
{
    compiler_init();

    xstrncpy(gSName, "main", PATH_MAX);
    gSLine = 1;
    gErrNum = 0;
    yyparse();

    compiler_final();

    return 0;
}
