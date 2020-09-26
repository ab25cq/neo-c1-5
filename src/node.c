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

unsigned int sNodeTree_create_function(char* fun_name, unsigned int function_params, char* result_type_name, unsigned int node_block, char* sname, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeFunction;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

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
}

unsigned int sNodeTree_create_return(unsigned int left, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeReturn;

    xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = 0;
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
