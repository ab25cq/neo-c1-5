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

/*
                case kNodeTypeSwitch:
                    free(gNodes[i].uValue.sSwitch.mSwitchExpression);
                    break;
*/

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

unsigned int sNodeTree_create_char_value(char value, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeCharValue;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].uValue.mCharValue = value;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_add(unsigned int left, unsigned int right, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeAdd;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_sub(unsigned int left, unsigned int right, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeSub;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_mult(unsigned int left, unsigned int right, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeMult;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_div(unsigned int left, unsigned int right, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeDiv;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_mod(unsigned int left, unsigned int right, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeMod;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_lshift(unsigned int left, unsigned int right, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLShift;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_rshift(unsigned int left, unsigned int right, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeRShift;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;
    return node;
}

unsigned int sNodeTree_create_or(unsigned int left, unsigned int right, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeOr;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_xor(unsigned int left, unsigned int right, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeXor;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_and(unsigned int left, unsigned int right, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeAnd;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_pre_create_function(unsigned int function_params, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeFunction;

    sVarTable* lv_table = init_var_table();
    gNodes[node].uValue.sFunction.mLVTable = lv_table;

    cinfo.lv_table = lv_table;

    gNodes[node].uValue.sFunction.mNumParams = gNodes[function_params].uValue.sFunctionParams.mNumParams;

    int i;
    for(i=0; i<gNodes[function_params].uValue.sFunctionParams.mNumParams; i++) {
        sParserParam* param = gNodes[function_params].uValue.sFunctionParams.mParams + i;
        xstrncpy(gNodes[node].uValue.sFunction.mParams[i].mName, param->mName, VAR_NAME_MAX);
        xstrncpy(gNodes[node].uValue.sFunction.mParams[i].mTypeName, param->mTypeName, VAR_NAME_MAX);

        char* var_name = param->mName;
        char* param_type = param->mTypeName;

        sNodeType* var_type = create_node_type_with_class_name(param_type);

        if(var_type == NULL || var_type->mClass == NULL) {
            fprintf(stderr, "%s %d: Invalid type name %s\n", gSName, yylineno, var_name);
            return FALSE;
        }

        BOOL constant = var_type->mConstant;
        BOOL global = FALSE;
        int index = -1;
        void* llvm_value = NULL;
        if(!add_variable_to_table(lv_table, var_name, var_type, llvm_value,  index, global, constant))
        {
            fprintf(stderr, "overflow variable table");
            return FALSE;
        }
    }

    return node;
}

unsigned int sNodeTree_create_function(unsigned int node, char* fun_name, char* fun_base_name, unsigned int function_params, char* result_type_name, unsigned int node_block, BOOL var_arg, BOOL inline_, BOOL static_, BOOL inherit_, BOOL generics, BOOL method_generics, char* sname, int sline)
{
    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].uValue.sFunction.mVarArg = var_arg;
    gNodes[node].uValue.sFunction.mInline = inline_;
    gNodes[node].uValue.sFunction.mInherit = inherit_;
    gNodes[node].uValue.sFunction.mStatic = static_;
    gNodes[node].uValue.sFunction.mCoroutine = FALSE;
    gNodes[node].uValue.sFunction.mGenerics = generics;
    gNodes[node].uValue.sFunction.mMethodGenerics = method_generics;
    gNodes[node].uValue.sFunction.mExternal = FALSE;

    xstrncpy(gNodes[node].uValue.sFunction.mName, fun_name, VAR_NAME_MAX);
    xstrncpy(gNodes[node].uValue.sFunction.mBaseName, fun_base_name, VAR_NAME_MAX);

    xstrncpy(gNodes[node].uValue.sFunction.mResultTypeName, result_type_name, VAR_NAME_MAX);

    gNodes[node].uValue.sFunction.mNodeBlock = node_block;

    if(!pre_compile(node, &cinfo)) {
        fprintf(stderr, "%s %d: faield to pre-compile\n", gSName, yylineno);
        exit(2);
    }

    if(!pre_compile_block(node_block, &cinfo)) {
        fprintf(stderr, "%s %d: faield to pre-compile\n", gSName, yylineno);
        exit(2);
    }

    return node;
}

unsigned int sNodeTree_create_block(BOOL create_lv_table, char* sname, int sline)
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
    gNodes[node].uValue.sBlock.mCreateLVTable = create_lv_table;
    gNodes[node].uValue.sBlock.mNodes = (unsigned int*)xcalloc(1, sizeof(unsigned int)*32);

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

unsigned int sNodeTree_create_external_function(char* fun_name, unsigned int function_params, char* result_type_name, BOOL var_arg, BOOL inherite_, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeExternalFunction;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].uValue.sFunction.mVarArg = var_arg;
    gNodes[node].uValue.sFunction.mInherit = inherite_;
    gNodes[node].uValue.sFunction.mCoroutine = FALSE;
    gNodes[node].uValue.sFunction.mGenerics = FALSE;
    gNodes[node].uValue.sFunction.mMethodGenerics = FALSE;
    gNodes[node].uValue.sFunction.mExternal = TRUE;

    xstrncpy(gNodes[node].uValue.sFunction.mName, fun_name, VAR_NAME_MAX);
    xstrncpy(gNodes[node].uValue.sFunction.mBaseName, fun_name, VAR_NAME_MAX);

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

unsigned int sNodeTree_create_return(unsigned int right, unsigned int middle, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeReturn;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

unsigned int sNodeTree_create_store_variable(char* var_name, char* type_name, unsigned int right, BOOL alloc, BOOL global, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStoreVariable;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    xstrncpy(gNodes[node].uValue.sStoreVariable.mVarName, var_name, VAR_NAME_MAX);
    xstrncpy(gNodes[node].uValue.sStoreVariable.mTypeName, type_name, VAR_NAME_MAX);
    gNodes[node].uValue.sStoreVariable.mAlloc = alloc;
    gNodes[node].uValue.sStoreVariable.mGlobal = global;

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

void append_param_to_params_at_head(unsigned int params, unsigned int param)
{
    int num_params = gNodes[params].uValue.sParams.mNumParams;

    gNodes[params].uValue.sParams.mNumParams++;

    if(gNodes[params].uValue.sParams.mNumParams >= PARAMS_MAX)
    {
        fprintf(stderr, "overflow parametor number\n");
        exit(2);
    }

    int i;
    for(i=num_params-1; i>0; i--) {
        gNodes[params].uValue.sParams.mParams[i] = gNodes[params].uValue.sParams.mParams[i-1];
    }
    gNodes[params].uValue.sParams.mParams[0] = param;
}

unsigned int sNodeTree_create_function_call(char* fun_name, unsigned int params, BOOL message_passing, BOOL inherit_, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeFunctionCall;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].uValue.sFunctionCall.mMessagePassing = message_passing;
    gNodes[node].uValue.sFunctionCall.mLambdaCall = FALSE;
    gNodes[node].uValue.sFunctionCall.mInherit = inherit_;

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

    xstrncpy(gNodes[node].uValue.sTypeDef.mTypeName, type_name, VAR_NAME_MAX);
    xstrncpy(gNodes[node].uValue.sTypeDef.mName, name, VAR_NAME_MAX);

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

unsigned int sNodeTree_create_coroutine(unsigned int function_params, char* result_type_name, unsigned int node_block, BOOL var_arg, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeCoroutine;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    static int coroutine_num = 0;
    coroutine_num++;

    char fun_name[VAR_NAME_MAX];
    snprintf(fun_name, VAR_NAME_MAX, "coroutine%d", coroutine_num);

    gNodes[node].uValue.sFunction.mVarArg = var_arg;
    gNodes[node].uValue.sFunction.mInline = FALSE;
    gNodes[node].uValue.sFunction.mStatic = TRUE;
    gNodes[node].uValue.sFunction.mCoroutine = TRUE;
    gNodes[node].uValue.sFunction.mGenerics = FALSE;
    gNodes[node].uValue.sFunction.mInherit = FALSE;
    gNodes[node].uValue.sFunction.mExternal = FALSE;

    xstrncpy(gNodes[node].uValue.sFunction.mName, fun_name, VAR_NAME_MAX);
    xstrncpy(gNodes[node].uValue.sFunction.mBaseName, fun_name, VAR_NAME_MAX);

    xstrncpy(gNodes[node].uValue.sFunction.mResultTypeName, result_type_name, VAR_NAME_MAX);
    gNodes[node].uValue.sFunction.mNodeBlock = node_block;

    if(function_params > 0) {
        gNodes[node].uValue.sFunction.mNumParams = gNodes[function_params].uValue.sFunctionParams.mNumParams;

        int i;
        for(i=0; i<gNodes[function_params].uValue.sFunctionParams.mNumParams; i++) {
            sParserParam* param = gNodes[function_params].uValue.sFunctionParams.mParams + i;
            xstrncpy(gNodes[node].uValue.sFunction.mParams[i].mName, param->mName, VAR_NAME_MAX);
            xstrncpy(gNodes[node].uValue.sFunction.mParams[i].mTypeName, param->mTypeName, VAR_NAME_MAX);
        }
    }
    else {
        gNodes[node].uValue.sFunction.mNumParams = 0;
    }

    int num_params = gNodes[node].uValue.sFunction.mNumParams;

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

unsigned int sNodeTree_create_struct(char* struct_name, unsigned int fields, BOOL generics, BOOL anonymous, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStruct;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    xstrncpy(gNodes[node].uValue.sStruct.mName, struct_name, VAR_NAME_MAX);
    gNodes[node].uValue.sStruct.mFields = fields;
    gNodes[node].uValue.sStruct.mAnonymous = anonymous;
    gNodes[node].uValue.sStruct.mGenerics = generics;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_union(char* struct_name, unsigned int fields, BOOL anonymous, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeUnion;

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

    BOOL readonly = FALSE;
    BOOL constant = FALSE;
    void* llvm_value = NULL;
    int index = -1;

    return node;
}

unsigned int sNodeTree_create_equals(unsigned int left, unsigned int right,  char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeEquals;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_not_equals(unsigned int left, unsigned int right, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeNotEquals;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_gt(unsigned int left, unsigned int right, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeGT;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_lt(unsigned int left, unsigned int right,  char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLT;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_ge(unsigned int left, unsigned int right,  char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeGE;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_le(unsigned int left, unsigned int right, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLE;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_lambda_call(unsigned int lambda_node, unsigned int params, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeFunctionCall;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = lambda_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].uValue.sFunctionCall.mMessagePassing = FALSE;
    gNodes[node].uValue.sFunctionCall.mLambdaCall = TRUE;
    gNodes[node].uValue.sFunctionCall.mInherit = FALSE;

    xstrncpy(gNodes[node].uValue.sFunctionCall.mFunName, "", VAR_NAME_MAX);

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

unsigned int sNodeTree_create_load_field(char* name, unsigned int left_node, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLoadField;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    xstrncpy(gNodes[node].uValue.sLoadField.mVarName, name, VAR_NAME_MAX);

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_store_field(char* var_name, unsigned int left_node, unsigned int right_node, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStoreField;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    xstrncpy(gNodes[node].uValue.sStoreField.mVarName, var_name, VAR_NAME_MAX);

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_and_and(unsigned int left_node, unsigned int right_node, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeAndAnd;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_or_or(unsigned int left_node, unsigned int right_node, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeOrOr;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_logical_denial(unsigned int left, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLogicalDenial;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_complement(unsigned int left, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeComplement;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_derefference(unsigned int left, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeDerefference;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_refference(unsigned int left, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeRefference;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_plus_eq(unsigned int left, unsigned int right, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypePlusEq;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_minus_eq(unsigned int left, unsigned int right, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeMinusEq;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_mult_eq(unsigned int left, unsigned int right, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeMultEq;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_div_eq(unsigned int left, unsigned int right, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeDivEq;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_mod_eq(unsigned int left, unsigned int right, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeModEq;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_and_eq(unsigned int left, unsigned int right, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeAndEq;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_xor_eq(unsigned int left, unsigned int right, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeXorEq;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_or_eq(unsigned int left, unsigned int right, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeOrEq;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_lshift_eq(unsigned int left, unsigned int right, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLShiftEq;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_rshift_eq(unsigned int left, unsigned int right, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeRShiftEq;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_load_array_element(unsigned int array, unsigned int index_node[], int num_dimention, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLoadElement;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].uValue.sLoadElement.mArrayDimentionNum = num_dimention;
    int i;
    for(i=0; i<num_dimention; i++) {
        gNodes[node].uValue.sLoadElement.mIndex[i] = index_node[num_dimention-i-1];
    }

    gNodes[node].mLeft = array;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_store_element(unsigned int array, unsigned int index_node[], int num_dimention, unsigned int right_node, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStoreElement;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].uValue.sStoreElement.mArrayDimentionNum = num_dimention;
    int i;
    for(i=0; i<num_dimention; i++) {
        gNodes[node].uValue.sStoreElement.mIndex[i] = index_node[num_dimention-i-1];
    }

    gNodes[node].mLeft = array;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_array_initializer(int left, char* var_name, int num_array_value, unsigned int* array_values, BOOL global, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeArrayInitializer;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    xstrncpy(gNodes[node].uValue.sArrayInitializer.mVarName, var_name, VAR_NAME_MAX);

    gNodes[node].uValue.sArrayInitializer.mNumArrayValue = num_array_value;
    memcpy(gNodes[node].uValue.sArrayInitializer.mArrayValues, array_values, sizeof(unsigned int)*INIT_ARRAY_MAX);
    gNodes[node].uValue.sArrayInitializer.mGlobal = global;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_while_statment(unsigned int expression_node, unsigned int while_node_block, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeWhile;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].uValue.sWhile.mExpressionNode = expression_node;
    gNodes[node].uValue.sWhile.mWhileNodeBlock = while_node_block;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_do_while_expression(unsigned int expression_node, unsigned int while_node_block, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeDoWhile;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].uValue.sWhile.mExpressionNode = expression_node;
    gNodes[node].uValue.sWhile.mWhileNodeBlock = while_node_block;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_switch_statment(unsigned int expression_node, int num_switch_expression, unsigned int* switch_expression, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeSwitch;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].uValue.sSwitch.mExpression = expression_node;
    memcpy(gNodes[node].uValue.sSwitch.mSwitchExpression, switch_expression, sizeof(unsigned int)*SWITCH_STASTMENT_NODE_MAX);
    gNodes[node].uValue.sSwitch.mNumSwitchExpression = num_switch_expression;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_case_expression(unsigned int expression_node, BOOL first_case, BOOL last_case, BOOL case_after_return, unsigned int first_statment, BOOL last_statment, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeCase;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].uValue.sCase.mExpression = expression_node;
    gNodes[node].uValue.sCase.mLastCase = last_case;
    gNodes[node].uValue.sCase.mFirstCase = first_case;
    gNodes[node].uValue.sCase.mCaseAfterReturn = case_after_return;
    gNodes[node].uValue.sCase.mFirstStatment = first_statment;
    gNodes[node].uValue.sCase.mLastStatment = last_statment;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_for_statment(unsigned int expression_node1, unsigned int expression_node2, unsigned int expression_node3, unsigned int for_node_block, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeFor;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].uValue.sFor.mExpressionNode = expression_node1;
    gNodes[node].uValue.sFor.mExpressionNode2 = expression_node2;
    gNodes[node].uValue.sFor.mExpressionNode3 = expression_node3;
    gNodes[node].uValue.sFor.mForNodeBlock = for_node_block;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_break_expression(char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeBreak;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_continue_expression(char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeContinue;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_cast(char* type_name, unsigned int left_node, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeCast;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    xstrncpy(gNodes[node].uValue.sCast.mTypeName, type_name, VAR_NAME_MAX);
    return node;
}

unsigned int sNodeTree_create_sizeof1(char* type_name, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeSizeOf1;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    xstrncpy(gNodes[node].uValue.sSizeOf.mTypeName, type_name, VAR_NAME_MAX);

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_sizeof2(char* var_name, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeSizeOf2;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    xstrncpy(gNodes[node].uValue.sSizeOf.mVarName, var_name, VAR_NAME_MAX);

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_alignof1(char* type_name, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeAlignOf1;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    xstrncpy(gNodes[node].uValue.sAlignOf.mTypeName, type_name, VAR_NAME_MAX);

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_alignof2(char* var_name, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeAlignOf2;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    xstrncpy(gNodes[node].uValue.sAlignOf.mVarName, var_name, VAR_NAME_MAX);

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_conditional(unsigned int conditional, unsigned int value1, unsigned int value2, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeConditional;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = conditional;
    gNodes[node].mRight = value1;
    gNodes[node].mMiddle = value2;

    return node;
}

unsigned int sNodeTree_create_dummy_heap(unsigned int object_node, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeDummyHeap;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = object_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_managed(char* var_name, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeManaged;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    xstrncpy(gNodes[node].uValue.sManaged.mVarName, var_name, VAR_NAME_MAX);

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

unsigned int sNodeTree_create_store_value_to_address(unsigned int address_node, unsigned int right_node, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStoreAddress;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = address_node;
    gNodes[node].mRight = right_node;
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
