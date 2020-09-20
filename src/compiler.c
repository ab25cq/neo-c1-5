#include "common.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libgen.h>

BOOL read_source(char* fname, sBuf* source)
{
    int f = open(fname, O_RDONLY);

    if(f < 0) {
        fprintf(stderr, "%s doesn't exist(2)\n", fname);
        return FALSE;
    }

    while(1) {
        char buf[BUFSIZ+1];
        int size = read(f, buf, BUFSIZ);

        if(size == 0) {
            break;
        }
        else if(size < 0) {
            fprintf(stderr, "unexpected error\n");
            close(f);
            return FALSE;
        }

        buf[size] = 0;
        sBuf_append_str(source, buf);

        if(size < BUFSIZ) {
            break;
        }
    }

    close(f);

    return TRUE;
}

BOOL delete_comment(sBuf* source, sBuf* source2)
{
    char* p = source->mBuf;

    BOOL in_string = FALSE;
    BOOL in_char = FALSE;

    while(*p) {
        if((in_string || in_char) && *p == '\\') {
            sBuf_append_char(source2, *p);
            p++;
            sBuf_append_char(source2, *p);
            p++;
        }
        /// comment1 ///
        else if(!in_string && !in_char && *p == '/' && *(p+1) == '*') {
            p+=2;
            int nest = 0;
            while(1) {
                if(*p == 0) {
                    fprintf(stderr, "there is not a comment end until source end with the comment begin in string %d in char %d\n", in_string, in_char);
                    return FALSE;
                }
                else if(*p == '/' && *(p+1) == '*') {
                    p+=2;
                    nest++;
                }
                else if(*p == '*' && *(p+1) == '/') {
                    p+=2;
                    if(nest == 0) {
                        break;
                    }

                    nest--;
                }
                else if(*p == '\n') {
                    sBuf_append_char(source2, *p);   // no delete line field for error message
                    p++;
                }
                else {
                    p++;
                }
            }
        }
        /// comment2 ///
        else if(!in_char && !in_string && *p == '/' && *(p+1) == '/') {
            p++;

            while(1) {
                if(*p == 0) {
                    break;
                }
                else if(*p == '\n') {
                    //p++;      // no delete line field for error message
                    break;
                }
                else {
                    p++;
                }
            }
        }
        else if(!in_char && *p == '"') {
            in_string = !in_string;
            sBuf_append_char(source2, *p);
            p++;
        }
        else if(!in_string && *p == '\'') {
            in_char = !in_char;
            sBuf_append_char(source2, *p);
            p++;
        }
        else if(*p == '\\' && *(p+1) == '/' && *(p+2) == '*') {
            sBuf_append_char(source2, *p);
            p++;
            sBuf_append_char(source2, *p);
            p++;
            sBuf_append_char(source2, *p);
            p++;
        }
        else if(*p == '\\' && *(p+1) == '#') {
            sBuf_append_char(source2, *p);
            p++;
            sBuf_append_char(source2, *p);
            p++;
        }
        else {
            sBuf_append_char(source2, *p);
            p++;
        }
    }

    return TRUE;
}

BOOL compile_source(char* fname, char* source, BOOL optimize, sVarTable* module_var_table)
{
    sParserInfo info;

    memset(&info, 0, sizeof(sParserInfo));
    sBuf_init(&info.mConst);
    info.p = source;
    info.source = source;
    xstrncpy(info.sname, fname, PATH_MAX);
    info.lv_table = module_var_table;
    info.sline = 1;
    info.parse_struct_phase = TRUE;

    char module_name[PATH_MAX];
    xstrncpy(module_name, fname, PATH_MAX);

    char* module_name2 = basename(module_name);

    char module_name3[PATH_MAX];
    xstrncpy(module_name3, module_name2, PATH_MAX);

    char* p = module_name3 + strlen(module_name3);
    while(p >= module_name3) {
        if(*p == '.') {
            *p = '\0';
            break;
        }
        else {
            p--;
        }
    }

    info.module_name = module_name3;

    sCompileInfo cinfo;
    memset(&cinfo, 0, sizeof(sCompileInfo));

    new_right_value_objects_container(&cinfo);


    xstrncpy(cinfo.fun_name, fname, VAR_NAME_MAX);

    cinfo.pinfo = &info;

    while(*info.p) {
        skip_spaces_and_lf(&info);
 
        int sline = info.sline;
        char* sname = info.sname;

        //info.sline_top = sline;

        if(*info.p == '#') {
            if(!parse_sharp(&info)) {
                free(info.mConst.mBuf);
                return FALSE;
            }
        }
        else if(parse_cmp(info.p, "__extension__") == 0)
        {
            info.p += 13;
            skip_spaces_and_lf(&info);
        }
        else {
            unsigned int node = 0;
            if(!expression(&node, &info)) {
                free(info.mConst.mBuf);
                return FALSE;
            }

            if(node == 0) {
                parser_err_msg(&info, "require an expression");
                info.err_num++;
                break;
            }

            if(info.change_sline) {
                info.change_sline = FALSE;

                gNodes[node].mLine = info.sline;
                xstrncpy(gNodes[node].mSName, info.sname, PATH_MAX);

                info.sline_top = info.sline;
            }
            else {
                gNodes[node].mLine = sline;
                xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
            }

/*
            if(info.err_num == 0)
            {
                cinfo.sline = gNodes[node].mLine;
                xstrncpy(cinfo.sname, gNodes[node].mSName, PATH_MAX);

                if(!compile(node, &cinfo)) {
                    free(info.mConst.mBuf);
                    return FALSE;
                }

                arrange_stack(&cinfo, 0);
            }
*/
        }

        if(*info.p == ';') {
            info.p++;
            skip_spaces_and_lf(&info);
        }
        skip_spaces_and_lf(&info);
    }

    if(info.err_num > 0 || cinfo.err_num > 0) {
        fprintf(stderr, "Parser error number is %d. Compile error number is %d\n", info.err_num, cinfo.err_num);
        free(info.mConst.mBuf);
        return FALSE;
    }

    memset(&info, 0, sizeof(sParserInfo));

    info.p = source;
    info.source = source;
    xstrncpy(info.sname, fname, PATH_MAX);
    info.sline = 1;
    info.parse_struct_phase = FALSE;
    info.lv_table = module_var_table;

    info.module_name = module_name3;

    memset(&cinfo, 0, sizeof(sCompileInfo));

    new_right_value_objects_container(&cinfo);

    xstrncpy(cinfo.fun_name, fname, VAR_NAME_MAX);
    cinfo.pinfo = &info;

    while(*info.p) {
        skip_spaces_and_lf(&info);
 
        int sline = info.sline;
        char* sname = info.sname;

        info.sline_top = sline;

        if(*info.p == '#') {
            if(!parse_sharp(&info)) {
                free(info.mConst.mBuf);
                return FALSE;
            }
        }
        else if(parse_cmp(info.p, "__extension__") == 0)
        {
            info.p += 13;
            skip_spaces_and_lf(&info);
        }
        else {
            unsigned int node = 0;
            if(!expression(&node, &info)) {
                free(info.mConst.mBuf);
                return FALSE;
            }

            if(node == 0) {
                parser_err_msg(&info, "require an expression");
                info.err_num++;
                break;
            }

            if(info.change_sline) {
                info.change_sline = FALSE;

                gNodes[node].mLine = info.sline;
                xstrncpy(gNodes[node].mSName, info.sname, PATH_MAX);

                info.sline_top = info.sline;
            }
            else {
                gNodes[node].mLine = sline;
                xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
            }

            if(info.err_num == 0)
            {

                cinfo.sline = gNodes[node].mLine;
                xstrncpy(cinfo.sname, gNodes[node].mSName, PATH_MAX);


                if(!compile(node, &cinfo)) {
                    free(info.mConst.mBuf);
                    return FALSE;
                }

                arrange_stack(&cinfo, 0);
            }
        }

        if(*info.p == ';') {
            info.p++;
            skip_spaces_and_lf(&info);
        }
        skip_spaces_and_lf(&info);
    }

    if(info.err_num > 0 || cinfo.err_num > 0) {
        fprintf(stderr, "Parser error number is %d. Compile error number is %d\n", info.err_num, cinfo.err_num);
        free(info.mConst.mBuf);
        return FALSE;
    }

    free(info.mConst.mBuf);

    return TRUE;
}
