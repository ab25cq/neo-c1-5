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

extern FILE *yyin, *yyout;

void parser_err_msg(char* msg)
{
    static int output_num = 0;

    if(output_num < PARSER_ERR_MSG_MAX) {
        fprintf(stderr, "%s:%d: %s\n", gSName, gSLine, msg);
    }

    output_num++;
}

extern int yyparse();

int main(int argc, char** argv)
{
    compiler_init();

    gSName[0] = '\0';

    int i;
    for(i=1; i<argc; i++) {
        /// options ///
        if(argv[i][0] == '-') {
        }
        else {
            xstrncpy(gSName, argv[i], PATH_MAX);
        }
    }

    gSLine = 1;

    if(gSName[0] == '\0') {
        yyparse();
    }
    else {
        yyin = fopen(gSName, "r");
        if(yyin == NULL) {
            fprintf(stderr, "can't open a input file\n");
            return 1;
        }

        yyparse();
    }

    compiler_final();

    return 0;
}
