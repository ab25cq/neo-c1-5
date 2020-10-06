#include "common.h"

sNodeTree* gNodes;

int gSizeNodes = 0;
int gUsedNodes = 0;

void init_nodes()
{
    const int node_size = 32;

    if(gUsedNodes == 0) {
        gNodes = (sNodeTree*)xcalloc(1, sizeof(sNodeTree)*node_size);
        gSizeNodes = node_size;
        gUsedNodes = 1;   // 0 of index means null
    }
}

void free_nodes()
{
    if(gUsedNodes > 0) {
        int i;
        for(i=1; i<gUsedNodes; i++) {
            switch(gNodes[i].mNodeType) {
                case kNodeTypeBlock:
                    if(gNodes[i].uValue.sBlock.mNodes) free(gNodes[i].uValue.sBlock.mNodes);
                    free(gNodes[i].uValue.sBlock.mSource.mBuf);
                    break;

                default:
                    break;
            }
        }

        free(gNodes);

        gSizeNodes = 0;
        gUsedNodes = 0;
    }
}

// return node index
unsigned int alloc_node()
{
    if(gSizeNodes == gUsedNodes) {
        int new_size = (gSizeNodes+1) * 2;
        gNodes = (sNodeTree*)xrealloc(gNodes, sizeof(sNodeTree)*new_size);

        gSizeNodes = new_size;
    }

    return gUsedNodes++;
}

unsigned int sNodeTree_create_int_value(int value, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeIntValue;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].uValue.mIntValue = value;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_add(unsigned int left, unsigned int right, unsigned int middle, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeAdd;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

unsigned int sNodeTree_create_sub(unsigned int left, unsigned int right, unsigned int middle, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeSub;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

unsigned int sNodeTree_create_mult(unsigned int left, unsigned int right, unsigned int middle, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeMult;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

unsigned int sNodeTree_create_div(unsigned int left, unsigned int right, unsigned int middle, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeDiv;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

unsigned int sNodeTree_create_function(char* fun_name, unsigned int function_params, char* result_type_name, unsigned int node_block, BOOL var_arg, BOOL inline_, BOOL static_, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeFunction;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].uValue.sFunction.mVarArg = var_arg;
    gNodes[node].uValue.sFunction.mInline = inline_;
    gNodes[node].uValue.sFunction.mStatic = static_;

    xstrncpy(gNodes[node].uValue.sFunction.mName, fun_name, VAR_NAME_MAX);

    gNodes[node].uValue.sFunction.mNumParams = gNodes[function_params].uValue.sFunctionParams.mNumParams;

    int i;
    for(i=0; i<gNodes[function_params].uValue.sFunctionParams.mNumParams; i++) {
        sParserParam* param = gNodes[function_params].uValue.sFunctionParams.mParams + i;
        xstrncpy(gNodes[node].uValue.sFunction.mParams[i].mName, param->mName, VAR_NAME_MAX);
        xstrncpy(gNodes[node].uValue.sFunction.mParams[i].mTypeName, param->mTypeName, VAR_NAME_MAX);
    }

    xstrncpy(gNodes[node].uValue.sFunction.mResultTypeName, result_type_name, VAR_NAME_MAX);
    gNodes[node].uValue.sFunction.mNodeBlock = node_block;

    return node;
}

unsigned int sNodeTree_create_block(char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeBlock;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].uValue.sBlock.mSizeNodes = 32;
    gNodes[node].uValue.sBlock.mNumNodes = 0;
    gNodes[node].uValue.sBlock.mNodes = (unsigned int*)xcalloc(1, sizeof(unsigned int)*32);
    gNodes[node].uValue.sBlock.mLVTable = NULL;

    sBuf_init(&gNodes[node].uValue.sBlock.mSource);

    return node;
}

void append_node_to_node_block(unsigned int node_block, unsigned int node)
{
    if(gNodes[node_block].uValue.sBlock.mSizeNodes <= gNodes[node_block].uValue.sBlock.mNumNodes) {
        unsigned int new_size = gNodes[node_block].uValue.sBlock.mSizeNodes * 2;
        gNodes[node_block].uValue.sBlock.mNodes = (unsigned int*)xrealloc(gNodes[node_block].uValue.sBlock.mNodes, sizeof(unsigned int)*new_size);
        memset(gNodes[node_block].uValue.sBlock.mNodes + gNodes[node_block].uValue.sBlock.mSizeNodes, 0, sizeof(unsigned int)*(new_size-gNodes[node_block].uValue.sBlock.mSizeNodes));
        gNodes[node_block].uValue.sBlock.mSizeNodes = new_size;
    }

    gNodes[node_block].uValue.sBlock.mNodes[gNodes[node_block].uValue.sBlock.mNumNodes] = node;
    gNodes[node_block].uValue.sBlock.mNumNodes++;
}

unsigned int sNodeTree_create_function_params(char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeFunctionParams;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].uValue.sFunctionParams.mNumParams = 0;
    memset(&gNodes[node].uValue.sFunctionParams.mParams, 0, sizeof(sParserParam)*PARAMS_MAX);

    return node;
}

void append_param_to_function_params(unsigned int function_params, char* type_name, char* name)
{
    int num_params = gNodes[function_params].uValue.sFunctionParams.mNumParams;
    xstrncpy(gNodes[function_params].uValue.sFunctionParams.mParams[num_params].mName, name, VAR_NAME_MAX);
    xstrncpy(gNodes[function_params].uValue.sFunctionParams.mParams[num_params].mTypeName, type_name, VAR_NAME_MAX);

    gNodes[function_params].uValue.sFunctionParams.mNumParams++;

    if(gNodes[function_params].uValue.sFunctionParams.mNumParams >= PARAMS_MAX)
    {
        fprintf(stderr, "overflow parametor number\n");
        exit(2);
    }
}

unsigned int sNodeTree_create_external_function(char* fun_name, unsigned int function_params, char* result_type_name, BOOL var_arg, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeExternalFunction;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].uValue.sFunction.mVarArg = var_arg;

    xstrncpy(gNodes[node].uValue.sFunction.mName, fun_name, VAR_NAME_MAX);

    gNodes[node].uValue.sFunction.mNumParams = gNodes[function_params].uValue.sFunctionParams.mNumParams;

    int i;
    for(i=0; i<gNodes[function_params].uValue.sFunctionParams.mNumParams; i++) {
        sParserParam* param = gNodes[function_params].uValue.sFunctionParams.mParams + i;
        xstrncpy(gNodes[node].uValue.sFunction.mParams[i].mName, param->mName, VAR_NAME_MAX);
        xstrncpy(gNodes[node].uValue.sFunction.mParams[i].mTypeName, param->mTypeName, VAR_NAME_MAX);
    }

    xstrncpy(gNodes[node].uValue.sFunction.mResultTypeName, result_type_name, VAR_NAME_MAX);
    gNodes[node].uValue.sFunction.mNodeBlock = 0;

    return node;
}

unsigned int sNodeTree_create_return(unsigned int right, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeReturn;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_store_variable(char* var_name, char* type_name, unsigned int right, BOOL alloc, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStoreVariable;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    xstrncpy(gNodes[node].uValue.sStoreVariable.mVarName, var_name, VAR_NAME_MAX);
    xstrncpy(gNodes[node].uValue.sStoreVariable.mTypeName, type_name, VAR_NAME_MAX);
    gNodes[node].uValue.sStoreVariable.mAlloc = alloc;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_params(char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeParams;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].uValue.sParams.mNumParams = 0;
    memset(&gNodes[node].uValue.sParams.mParams, 0, sizeof(unsigned int)*PARAMS_MAX);

    return node;
}

void append_param_to_params(unsigned int params, unsigned int param)
{
    int num_params = gNodes[params].uValue.sParams.mNumParams;
    gNodes[params].uValue.sParams.mParams[num_params] = param;
    gNodes[params].uValue.sParams.mNumParams++;

    if(gNodes[params].uValue.sParams.mNumParams >= PARAMS_MAX)
    {
        fprintf(stderr, "overflow parametor number\n");
        exit(2);
    }
}

unsigned int sNodeTree_create_function_call(char* fun_name, unsigned int params, BOOL message_passing, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeFunctionCall;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].uValue.sFunctionCall.mMessagePassing = message_passing;

    xstrncpy(gNodes[node].uValue.sFunctionCall.mFunName, fun_name, VAR_NAME_MAX);

    if(params > 0) {
        gNodes[node].uValue.sFunctionCall.mNumParams = gNodes[params].uValue.sParams.mNumParams;
        int i;
        for(i=0; i<gNodes[params].uValue.sParams.mNumParams; i++) {
            gNodes[node].uValue.sFunctionCall.mParams[i] = gNodes[params].uValue.sParams.mParams[i];
        }
    }
    else {
        gNodes[node].uValue.sFunctionCall.mNumParams = 0;
    }

    return node;
}

unsigned int sNodeTree_create_load_variable(char* var_name, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLoadVariable;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    xstrncpy(gNodes[node].uValue.sLoadVariable.mVarName, var_name, VAR_NAME_MAX);

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_c_string(char* value, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeCStringValue;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    xstrncpy(gNodes[node].uValue.mStrValue, value, 512);

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_if(unsigned int if_exp, unsigned int if_block, int elif_num, unsigned int* elif_exps, unsigned int* elif_blocks, unsigned int else_block, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeIf;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].uValue.sIf.mIfExp = if_exp;
    gNodes[node].uValue.sIf.mIfBlock = if_block;
    gNodes[node].uValue.sIf.mElifNum = elif_num;
    int i;
    for(i=0; i<elif_num; i++) {
        gNodes[node].uValue.sIf.mElifExps[i] = elif_exps[i];
        gNodes[node].uValue.sIf.mElifBlocks[i] = elif_blocks[i];
    }

    gNodes[node].uValue.sIf.mElseBlock = else_block;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_true(char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeTrue;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_false(char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeFalse;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_object(char* type_name, unsigned int object_num, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeCreateObject;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    xstrncpy(gNodes[node].uValue.sCreateObject.mTypeName, type_name, VAR_NAME_MAX);

    gNodes[node].mLeft = object_num;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_typedef(char* name, char* type_name, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeTypeDef;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    add_typedef(name, type_name);

    return node;
}

unsigned int sNodeTree_create_clone(unsigned int left, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeClone;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_coroutine(char* type_name, unsigned int block, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeCoroutine;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].uValue.sCoroutine.mBlock = block;
    xstrncpy(gNodes[node].uValue.sCoroutine.mTypeName, type_name, VAR_NAME_MAX);

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_struct_fields(char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeFields;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].uValue.sFields.mNumFields = 0;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

void append_field_to_fields(unsigned int fields, char* name, char* type_name)
{
    int num_fields = gNodes[fields].uValue.sFields.mNumFields;
    xstrncpy(gNodes[fields].uValue.sFields.mNameFields[num_fields], name, VAR_NAME_MAX);
    xstrncpy(gNodes[fields].uValue.sFields.mTypeFields[num_fields], type_name, VAR_NAME_MAX);
    gNodes[fields].uValue.sFields.mNumFields++;

    if(gNodes[fields].uValue.sFields.mNumFields >= STRUCT_FIELD_MAX) {
        fprintf(stderr, "overflow field number\n");
        exit(2);
    }
}

unsigned int sNodeTree_create_struct(char* struct_name, unsigned int fields, BOOL anonymous, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStruct;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    xstrncpy(gNodes[node].uValue.sStruct.mName, struct_name, VAR_NAME_MAX);
    gNodes[node].uValue.sStruct.mFields = fields;
    gNodes[node].uValue.sStruct.mAnonymous = anonymous;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_define_variable(char* type_name, char* var_name, BOOL global, BOOL extern_, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeDefineVariable;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    xstrncpy(gNodes[node].uValue.sDefineVariable.mVarName, var_name, VAR_NAME_MAX);
    xstrncpy(gNodes[node].uValue.sDefineVariable.mTypeName, type_name, VAR_NAME_MAX);
    gNodes[node].uValue.sDefineVariable.mGlobal = global;
    gNodes[node].uValue.sDefineVariable.mExtern = extern_;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

void show_node(unsigned int node)
{
    switch(gNodes[node].mNodeType) {
        case kNodeTypeIntValue:
            printf("int value %d\n", gNodes[node].uValue.mIntValue);
            break;

        case kNodeTypeBlock: {
            printf("block num nodes %d\n", gNodes[node].uValue.sBlock.mNumNodes);
            int i;
            for(i=0; i<gNodes[node].uValue.sBlock.mNumNodes; i++) {
                show_node(gNodes[node].uValue.sBlock.mNodes[i]);
            }
            }
            break;

        case kNodeTypeFunction: {
            printf("function name %s num_params %d\n", gNodes[node].uValue.sFunction.mName, gNodes[node].uValue.sFunction.mNumParams);

            puts("result_type");
            puts(gNodes[node].uValue.sFunction.mResultTypeName);

            puts("params");
            printf("num_params %d\n", gNodes[node].uValue.sFunction.mNumParams);

            int i;
            for(i=0; i<gNodes[node].uValue.sFunction.mNumParams; i++) {
                sParserParam* param = gNodes[node].uValue.sFunction.mParams + i;

                printf("param #%d\n", i);
                puts(param->mName);
                puts(param->mTypeName);
            }

            puts("block");
            show_node(gNodes[node].uValue.sFunction.mNodeBlock);
            puts("block end");
            }
            break;

        case kNodeTypeAdd:
            puts("add");

            puts("left");
            show_node(gNodes[node].mLeft);

            puts("right");
            show_node(gNodes[node].mRight);
            break;

        case kNodeTypeSub:
            puts("sub");

            puts("left");
            show_node(gNodes[node].mLeft);

            puts("right");
            show_node(gNodes[node].mRight);
            break;

        case kNodeTypeMult:
            puts("mult");

            puts("left");
            show_node(gNodes[node].mLeft);

            puts("right");
            show_node(gNodes[node].mRight);
            break;

        case kNodeTypeDiv:
            puts("div");

            puts("left");
            show_node(gNodes[node].mLeft);

            puts("right");
            show_node(gNodes[node].mRight);
            break;

        case kNodeTypeReturn:
            puts("return");

            puts("left");
            show_node(gNodes[node].mLeft);

            break;

        case kNodeTypeStoreVariable:
            puts("store variable");
            break;

        default:
            printf("node type %d\n", gNodes[node].mNodeType);
            break;
    }
}
