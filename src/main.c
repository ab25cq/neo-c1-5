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

char gSNameOriginal[PATH_MAX];

extern FILE *yyin, *yyout;

void parser_err_msg(char* msg)
{
    static int output_num = 0;

    if(output_num < PARSER_ERR_MSG_MAX) {
        //fprintf(stderr, "%s:%d: %s\n", gSName, yylloc.first_line, msg);
    }

    output_num++;
}

extern sCompileInfo cinfo;
extern int yyparse();

int main(int argc, char** argv)
{
    char sname[PATH_MAX];
    gSName[0] = '\0';

    int i;
    for(i=1; i<argc; i++) {
        /// options ///
        if(argv[i][0] == '-') {
            if(strcmp(argv[i], "-g") == 0) {
                gNCDebug = TRUE;
            }
        }
        else {
            xstrncpy(sname, argv[i], PATH_MAX);
            xstrncpy(gSNameOriginal, argv[i], PATH_MAX);
            snprintf(gSName, PATH_MAX, "%s.pp", argv[i]);
        }
    }

    char* cflags = getenv("CFLAGS");
    char cmd[1024];
#ifdef __DARWIN__
    if(cflags) {
        snprintf(cmd, 1024, "clang -D_GNU_SOURCE -E %s -I/opt/local/include %s > %s", cflags, sname, gSName);
    }
    else {
        snprintf(cmd, 1024, "clang -D_GNU_SOURCE -E %s -I/opt/local/include > %s", sname, gSName);
    }
#else
    if(cflags) {
        snprintf(cmd, 1024, "cpp -D_GNU_SOURCE %s -C %s > %s", cflags, sname, gSName);
    }
    else {
        snprintf(cmd, 1024, "cpp -D_GNU_SOURCE -C %s > %s", sname, gSName);
    }
#endif

    puts(cmd);
    int rc = system(cmd);

    if(rc != 0) {
        fprintf(stderr, "failed to cpp(1)\n");
        exit(2);
    }

    compiler_init();

    memset(&cinfo, 0, sizeof(sCompileInfo));

    cinfo.gv_table = init_var_table();

    yylineno = 1;

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
