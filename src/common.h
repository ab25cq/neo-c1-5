#ifndef COMMON_H
#define COMMON_H 1

#include "config.h"
#include "buffer.h"
#include "xfunc.h"
#include "alignment.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <stdarg.h>

//////////////////////////////
/// limits 
//////////////////////////////
#define GENERICS_TYPES_MAX 10
#define BLOCK_NEST_MAX 256*2
#define FIELDS_NEST_MAX 64
#define VAR_NAME_MAX 128
#define CLASS_NUM_MAX 512*2*2*2*2*2
#define PARSER_ERR_MSG_MAX 5
#define COMPILE_ERR_MSG_MAX 5
#define NEO_C_STACK_SIZE 512
#define LOCAL_VARIABLE_MAX 512*2
#define PARAMS_MAX 32
#define METHOD_DEFAULT_PARAM_MAX 128
#define SOURCE_EXPRESSION_MAX 4096*2
#define ELIF_NUM_MAX 128
#define ELIF_NEST_MAX 64
#define BLOCK_NUM_MAX 128
#define STRUCT_FIELD_MAX 256
#define REAL_FUN_NAME_MAX (VAR_NAME_MAX*PARAMS_MAX+32)
#define REAL_STRUCT_NAME_MAX (VAR_NAME_MAX*PARAMS_MAX+32)
#define IMPL_DEF_MAX 512
#define EXTERNAL_OBJECT_MAX 4096
#define INIT_ARRAY_MAX 128
#define LOOP_NEST_MAX 1024
#define TYPEDEF_MAX 4096
#define MACRO_MAX 1024
#define ARRAY_DIMENTION_MAX 5
#define SWITCH_STASTMENT_NODE_MAX 4096*2

#define clint64 long long      // for 32 bit cpu

//////////////////////////////
/// progressive declaration
//////////////////////////////
struct sNodeTypeStruct;
struct sCompileInfoStruct;

//////////////////////////////
/// klass.c 
//////////////////////////////
#define CLASS_FLAGS_PRIMITIVE 0x01
#define CLASS_FLAGS_STRUCT 0x02
#define CLASS_FLAGS_NUMBER 0x04
#define CLASS_FLAGS_UNSIGNED_NUMBER 0x08
#define CLASS_FLAGS_GENERICS 0x10
#define CLASS_FLAGS_METHOD_GENERICS 0x20
#define CLASS_FLAGS_UNION 0x040
#define CLASS_FLAGS_ANONYMOUS 0x080
#define CLASS_FLAGS_ENUM 0x100
#define CLASS_FLAGS_ANONYMOUS_VAR_NAME 0x200

struct sCLClassStruct {
    clint64 mFlags;

    char mName[VAR_NAME_MAX];

    int mGenericsNum;
    int mMethodGenericsNum;
    
    struct sNodeTypeStruct* mFields[STRUCT_FIELD_MAX];
    char mNameFields[STRUCT_FIELD_MAX][VAR_NAME_MAX];
    int mNumFields;

    void* mUndefinedStructType;
};

typedef struct sCLClassStruct sCLClass;

struct sClassTableStruct
{
    char* mName;
    sCLClass* mItem;
    BOOL mFreed;
    BOOL mInitialized;

    struct sClassTableStruct* mNextClass;
};

typedef struct sClassTableStruct sClassTable;

extern sClassTable* gHeadClassTable;

void class_init();
void class_final();

BOOL is_type_name(char* name);

sCLClass* get_class(char* class_name);
sCLClass* alloc_struct(const char* class_name, BOOL anonymous);
sCLClass* alloc_enum(char* class_name);
void add_field_to_struct(sCLClass* klass, const char* field_name, struct sNodeTypeStruct* field_type);
sCLClass* alloc_union(char* class_name, BOOL anonymous, BOOL anonymous_var_name);
void add_field_to_union(sCLClass* klass, char* field_name, struct sNodeTypeStruct* field_type);
unsigned int get_hash_key(const char* name, unsigned int max);
int get_field_index(sCLClass* klass, char* var_name, int* parent_field_index);
sCLClass* clone_class(sCLClass* klass);

//////////////////////////////
/// node_type.c
//////////////////////////////
struct sNodeTypeStruct {
    sCLClass* mClass;

    struct sNodeTypeStruct* mGenericsTypes[GENERICS_TYPES_MAX];
    int mNumGenericsTypes;

    int mArrayNum[ARRAY_DIMENTION_MAX];
    int mArrayDimentionNum;
    BOOL mNullable;
    BOOL mUnsigned;
    int mPointerNum;
    BOOL mConstant;
    BOOL mRegister;
    BOOL mVolatile;
    BOOL mStatic;
    int mSizeNum;
    BOOL mManaged;

    struct sNodeTypeStruct* mParamTypes[PARAMS_MAX];
    struct sNodeTypeStruct* mResultType;
    int mNumParams;

    BOOL mHeap;
    BOOL mDummyHeap;
    BOOL mNoHeap;

    unsigned int mDynamicArrayNum;

    int mArrayInitializeNum;

    unsigned int mTypeOfExpression;

    int mFinalizeGenericsFunNum;

    int mNumFields;

    char mTypeName[VAR_NAME_MAX];
    int mTypePointerNum;
};

typedef struct sNodeTypeStruct sNodeType;

void init_node_types();
void free_node_types();

BOOL check_the_same_fields(sNodeType* left_node, sNodeType* right_node);

sNodeType* clone_node_type(sNodeType* node_type);
sNodeType* create_node_type_with_class_name(const char* class_name);
sNodeType* create_node_type_with_class_pointer(sCLClass* klass);
BOOL cast_posibility(sNodeType* left_type, sNodeType* right_type);
BOOL auto_cast_posibility(sNodeType* left_type, sNodeType* right_type);

BOOL substitution_posibility(sNodeType* left_type, sNodeType* right_type, BOOL no_output);
BOOL type_identify(sNodeType* left, sNodeType* right);
BOOL type_identify_with_class_name(sNodeType* left, const char* right_class_name);
BOOL is_number_type(sNodeType* node_type);
void show_node_type(sNodeType* node_type);
BOOL solve_generics(sNodeType** node_type, sNodeType* generics_type, BOOL* success_solve);
BOOL solve_method_generics(sNodeType** node_type, int num_method_generics_types, sNodeType* method_generics_types[GENERICS_TYPES_MAX]);
BOOL substitution_posibility(sNodeType* left_type, sNodeType* right_type, BOOL no_output);
BOOL is_typeof_type(sNodeType* node_type);
BOOL included_generics_type(sNodeType* node_type, sCLClass* checked_class[], int* num_checked_class);
BOOL get_type_of_method_generics(sNodeType* method_generics_types[GENERICS_TYPES_MAX], sNodeType* fun_param_type, sNodeType* param_type);
void create_type_name_from_node_type(char* type_name, int type_name_max, sNodeType* node_type, BOOL neo_c);
BOOL is_generics_type(sNodeType* node_type);
  
//////////////////////////////
/// vtable.c
//////////////////////////////
struct sVarStruct {
    char mName[VAR_NAME_MAX];
    int mIndex;
    sNodeType* mType;

    int mBlockLevel;

    BOOL mConstant;
    void* mLLVMValue;

    BOOL mGlobal;
};

typedef struct sVarStruct sVar;

struct sVarTableStruct {
    int mID;
    sVar mLocalVariables[LOCAL_VARIABLE_MAX];  // open address hash
    int mVarNum;
    int mMaxBlockVarNum;

    int mBlockLevel;

    BOOL mCoroutineTop;

    struct sVarTableStruct* mParent;            // make linked list
    struct sVarTableStruct* mNext;              // for free var table
};

typedef struct sVarTableStruct sVarTable;

void init_vtable();
void final_vtable();

BOOL is_included_var_from_this_table_only(sVarTable* table, sVar* var);
sVarTable* init_block_vtable(sVarTable* lv_table, BOOL no_increment_block_level);

sVarTable* init_var_table();
sVarTable* clone_var_table(sVarTable* lv_table);
void restore_var_table(sVarTable* left, sVarTable* right);

void set_max_block_var_num(sVarTable* new_table, sVarTable* lv_table);

int get_variable_index(sVarTable* table, char* name, BOOL* parent);

void check_already_added_variable(sVarTable* table, char* name);

// result: (true) success (false) overflow the table or a variable which has the same name exists
BOOL add_variable_to_table(sVarTable* table, char* name, sNodeType* type_, void* llvm_value, int index, BOOL global, BOOL constant);

// result: (null) not found (sVar*) found
sVar* get_variable_from_table(sVarTable* table, char* name);

// result: (null) not found (sVar*) found
sVar* get_variable_from_index(sVarTable* table, int index);

int get_var_num(sVarTable* table);
void show_vtable(sVarTable* table);
void show_vtable_current_only(sVarTable* table);

int get_parent_var_num_of_sum(sVarTable* table);

void free_objects(sVarTable* table, struct sCompileInfoStruct* info);

// result: (null) not found (sVar*) found
sVar* get_variable_from_this_table_only(sVarTable* table, char* name);

/////////////////////////////// 
// typedef.c
/////////////////////////////// 
void init_typedef();

void add_typedef(char* name, char* node_type);
void get_typedef(char* name, char* result);

/////////////////////////////// 
// parser.c
/////////////////////////////// 
struct sParserParamStruct 
{
    char mName[VAR_NAME_MAX];
    char mTypeName[VAR_NAME_MAX];
    sNodeType* mType;
};

typedef struct sParserParamStruct sParserParam;

extern char gSName[PATH_MAX];
extern char gSNameOriginal[PATH_MAX];
extern int yylineno;

/////////////////////////////// 
// node.c
/////////////////////////////// 
enum eNodeType { kNodeTypeTrue, kNodeTypeFalse, kNodeTypeNull, kNodeTypeIntValue, kNodeTypeCharValue, kNodeTypeAdd, kNodeTypeSub, kNodeTypeMult, kNodeTypeDiv, kNodeTYpeMod, kNodeTypeBlock, kNodeTypeFunction, kNodeTypeParams, kNodeTypeFunctionParams , kNodeTypeReturn, kNodeTypeStoreVariable, kNodeTypeFunctionCall, kNodeTypeExternalFunction, kNodeTypeLoadVariable, kNodeTypeCStringValue, kNodeTypeIf, kNodeTypeCreateObject, kNodeTypeTypeDef, kNodeTypeClone, kNodeTypeDelete, kNodeTypeFields, kNodeTypeStruct, kNodeTypeUnion, kNodeTypeDefineVariable, kNodeTypeEquals, kNodeTypeNotEquals, kNodeTypeLoadField, kNodeTypeStoreField, kNodeTypeAndAnd, kNodeTypeOrOr, kNodeTypeGT, kNodeTypeLT, kNodeTypeGE, kNodeTypeLE, kNodeTypeMod, kNodeTypeLShift, kNodeTypeRShift, kNodeTypeOr, kNodeTypeXor, kNodeTypeAnd, kNodeTypeLogicalDenial, kNodeTypeComplement, kNodeTypeRefference, kNodeTypeDerefference, kNodeTypePlusEq, kNodeTypeMinusEq, kNodeTypeMultEq, kNodeTypeDivEq, kNodeTypeModEq, kNodeTypeAndEq, kNodeTypeXorEq, kNodeTypeOrEq, kNodeTypeLShiftEq, kNodeTypeRShiftEq, kNodeTypeLoadElement, kNodeTypeStoreElement, kNodeTypeArrayInitializer, kNodeTypeFor, kNodeTypeWhile, kNodeTypeDoWhile, kNodeTypeSwitch, kNodeTypeCase, kNodeTypeBreak, kNodeTypeContinue, kNodeTypeCast, kNodeTypeSizeOf1, kNodeTypeSizeOf2, kNodeTypeAlignOf1, kNodeTypeAlignOf2, kNodeTypeCoroutine, kNodeTypeConditional, kNodeTypeDummyHeap, kNodeTypeManaged, kNodeTypeStoreAddress, kNodeTypeIsHeap, kNodeTypeBorrow };

struct sNodeTreeStruct 
{
    enum eNodeType mNodeType;

    unsigned int mLeft;
    unsigned int mRight;
    unsigned int mMiddle;

    char mSName[PATH_MAX];
    int mLine;

    union {
        int mIntValue;
        char mStrValue[512];
        char mCharValue;

        struct {
            unsigned int* mNodes;
            unsigned int mSizeNodes;
            unsigned int mNumNodes;

            BOOL mCreateLVTable;

            sVarTable* mLVTable;

            sBuf mSource;
        } sBlock;
        struct {
            char mVarName[VAR_NAME_MAX];
            char mTypeName[VAR_NAME_MAX];
            BOOL mAlloc;
            BOOL mGlobal;
        } sStoreVariable;
        struct {
            char mVarName[VAR_NAME_MAX];
        } sLoadVariable;
        struct {
            char mName[VAR_NAME_MAX];
            char mBaseName[VAR_NAME_MAX];
            sParserParam mParams[PARAMS_MAX];
            int mNumParams;
            char mResultTypeName[VAR_NAME_MAX];
            unsigned int mNodeBlock;
            BOOL mVarArg;
            BOOL mInline;
            BOOL mInherit;
            BOOL mExternal;
            BOOL mStatic;
            BOOL mCoroutine;
            BOOL mGenerics;
            BOOL mMethodGenerics;
            sVarTable* mLVTable;
        } sFunction;
        struct {
            char mFunName[VAR_NAME_MAX];
            int mNumParams;
            unsigned mParams[PARAMS_MAX];
            BOOL mMessagePassing;
            BOOL mLambdaCall;
            BOOL mInherit;
            char mRealFunName[VAR_NAME_MAX];
        } sFunctionCall;
        struct {
            char mVarName[VAR_NAME_MAX];
        } sLoadField;
        struct {
            char mVarName[VAR_NAME_MAX];
        } sStoreField;

        struct {
            int mNumParams;
            sParserParam mParams[PARAMS_MAX];
        } sFunctionParams;

        struct {
            int mNumParams;
            unsigned int mParams[PARAMS_MAX];
        } sParams;
        struct {
            unsigned int mIfExp;
            unsigned int mIfBlock;
            int mElifNum;
            unsigned int mElifExps[ELIF_NUM_MAX];
            unsigned int mElifBlocks[ELIF_NUM_MAX];
            unsigned int mElseBlock;

            sVarTable* mLVTable;
        } sIf;
        struct {
            char mTypeName[VAR_NAME_MAX];
        } sCreateObject;
        struct {
            int mNumFields;
            char mTypeFields[STRUCT_FIELD_MAX][VAR_NAME_MAX];
            char mNameFields[STRUCT_FIELD_MAX][VAR_NAME_MAX];
        } sFields;
        struct {
            char mName[VAR_NAME_MAX];
            unsigned int mFields;
            BOOL mAnonymous;
            BOOL mGenerics;
        } sStruct;
        struct {
            char mVarName[VAR_NAME_MAX];
            char mTypeName[VAR_NAME_MAX];
            BOOL mGlobal;
            BOOL mExtern;
            unsigned int mInitValue;
        } sDefineVariable;
        struct {
            unsigned int mIndex[ARRAY_DIMENTION_MAX];
            int mArrayDimentionNum;
        } sStoreElement;

        struct {
            unsigned int mIndex[ARRAY_DIMENTION_MAX];
            int mArrayDimentionNum;
        } sLoadElement;
        struct {
            int mNumArrayValue;
            unsigned int mArrayValues[INIT_ARRAY_MAX];
            BOOL mGlobal;
            char mVarName[VAR_NAME_MAX];
        } sArrayInitializer;
        struct {
            unsigned int mExpressionNode;
            unsigned int mExpressionNode2;
            unsigned int mExpressionNode3;
            unsigned int mForNodeBlock;
        } sFor;
        struct {
            unsigned int mExpressionNode;
            unsigned int mWhileNodeBlock;
        } sWhile;
        struct {
            unsigned int mSwitchExpression[SWITCH_STASTMENT_NODE_MAX];
            int mNumSwitchExpression;
            unsigned int mExpression;
        } sSwitch;
        struct {
            unsigned int mExpression;
            BOOL mLastCase;
            BOOL mFirstCase;
            BOOL mCaseAfterReturn;
            unsigned int mFirstStatment;
            unsigned int mLastStatment;
        } sCase;
        struct {
            char mTypeName[VAR_NAME_MAX];
        } sCast;
        struct {
            char mTypeName[VAR_NAME_MAX];
            char mVarName[VAR_NAME_MAX];
        } sSizeOf;
        struct {
            char mTypeName[VAR_NAME_MAX];
            char mVarName[VAR_NAME_MAX];
        } sIsHeap;
        struct {
            char mTypeName[VAR_NAME_MAX];
            char mVarName[VAR_NAME_MAX];
        } sAlignOf;
        struct {
            char mName[VAR_NAME_MAX];
            char mTypeName[VAR_NAME_MAX];
        } sTypeDef;
        struct {
            char mVarName[VAR_NAME_MAX];
        } sManaged;
    } uValue;
};

typedef struct sNodeTreeStruct sNodeTree;

extern sNodeTree* gNodes;

void append_field_to_fields(unsigned int fields, char* name, char* type_name);
void append_node_to_node_block(unsigned int node_block, unsigned int node);
void append_param_to_function_params(unsigned int function_params, char* type_name, char* name);
void show_node(unsigned int node);
void init_nodes();
void free_nodes();

unsigned int sNodeTree_create_int_value(int value, char* sname, int sline);
unsigned int sNodeTree_create_conditional(unsigned int conditional, unsigned int value1, unsigned int value2, char* sname, int sline);
unsigned int sNodeTree_case_expression(unsigned int expression_node, BOOL first_case, BOOL last_case, BOOL case_after_return, unsigned int first_statment, BOOL last_statment, char* sname, int sline);
unsigned int sNodeTree_create_char_value(char value, char* sname, int sline);
unsigned int sNodeTree_create_true(char* sname, int sline);
unsigned int sNodeTree_create_false(char* sname, int sline);
unsigned int sNodeTree_create_if(unsigned int if_exp, unsigned int if_block, int elif_num, unsigned int* elif_exps, unsigned int* elif_blocks, unsigned int else_block, char* sname, int sline);
unsigned int sNodeTree_create_add(unsigned int left, unsigned int right, char* sname, int sline);
unsigned int sNodeTree_create_sub(unsigned int left, unsigned int right, char* sname, int sline);
unsigned int sNodeTree_create_mult(unsigned int left, unsigned int right, char* sname, int sline);
unsigned int sNodeTree_create_div(unsigned int left, unsigned int right, char* sname, int sline);
unsigned int sNodeTree_create_lshift(unsigned int left, unsigned int right, char* sname, int sline);
unsigned int sNodeTree_create_rshift(unsigned int left, unsigned int right, char* sname, int sline);
unsigned int sNodeTree_create_mod(unsigned int left, unsigned int right, char* sname, int sline);
unsigned int sNodeTree_create_or(unsigned int left, unsigned int right, char* sname, int sline);
unsigned int sNodeTree_create_xor(unsigned int left, unsigned int right, char* sname, int sline);
unsigned int sNodeTree_create_and(unsigned int left, unsigned int right, char* sname, int sline);
unsigned int sNodeTree_create_function(unsigned int node, char* fun_name, char* fun_base_name, unsigned int function_params, char* result_type_name, unsigned int node_block, BOOL var_arg, BOOL inline_, BOOL static_, BOOL inherit_, BOOL generics, BOOL method_generics, char* sname, int sline);
unsigned int sNodeTree_create_function_params(char* sname, int sline);
unsigned int sNodeTree_create_params(char* sname, int sline);
void append_param_to_params(unsigned int params, unsigned int param);
void append_param_to_params_at_head(unsigned int params, unsigned int param);
unsigned int sNodeTree_create_store_variable(char* var_name, char* type_name, unsigned int right, BOOL alloc, BOOL global, char* sname, int sline);
unsigned int sNodeTree_create_external_function(char* fun_name, unsigned int function_params, char* result_type_name, BOOL var_arg, BOOL inherite_, char* sname, int sline);
unsigned int sNodeTree_create_load_variable(char* var_name, char* sname, int sline);
unsigned int sNodeTree_create_block(BOOL create_lv_table, char* sname, int sline);
unsigned int sNodeTree_create_return(unsigned int right, unsigned int middle, char* sname, int sline);
unsigned int sNodeTree_create_function_call(char* fun_name, unsigned int params, BOOL message_passing, BOOL inherit_, char* sname, int sline);
unsigned int sNodeTree_create_c_string(char* value, char* sname, int sline);
unsigned int sNodeTree_create_object(char* type_name, unsigned int object_num, char* sname, int sline);
unsigned int sNodeTree_create_clone(unsigned int left, char* sname, int sline);
unsigned int sNodeTree_create_coroutine(unsigned int function_params, char* result_type_name, unsigned int node_block, BOOL var_arg, char* sname, int sline);
unsigned int sNodeTree_create_struct_fields(char* sname, int sline);
unsigned int sNodeTree_create_struct(char* struct_name, unsigned int fields, BOOL generics, BOOL anonymous, char* sname, int sline);
unsigned int sNodeTree_create_generics_struct(char* struct_name, int num_generics, char** generics_types, unsigned int fields, BOOL anonymous, char* sname, int sline);
unsigned int sNodeTree_create_union(char* struct_name, unsigned int fields, BOOL anonymous, char* sname, int sline);
unsigned int sNodeTree_create_define_variable(char* type_name, char* var_name, BOOL global, BOOL extern_, unsigned int init_value, char* sname, int sline);
unsigned int sNodeTree_create_equals(unsigned int left, unsigned int right,  char* sname, int sline);
unsigned int sNodeTree_create_not_equals(unsigned int left, unsigned int right, char* sname, int sline);
unsigned int sNodeTree_create_lambda_call(unsigned int lambda_node, unsigned int params, char* sname, int sline);
unsigned int sNodeTree_create_store_field(char* var_name, unsigned int left_node, unsigned int right_node, char* sname, int sline);
unsigned int sNodeTree_create_load_field(char* name, unsigned int left_node, char* sname, int sline);
unsigned int sNodeTree_create_or_or(unsigned int left_node, unsigned int right_node, char* sname, int sline);
unsigned int sNodeTree_create_and_and(unsigned int left_node, unsigned int right_node, char* sname, int sline);
unsigned int sNodeTree_create_gt(unsigned int left, unsigned int right, char* sname, int sline);
unsigned int sNodeTree_create_lt(unsigned int left, unsigned int right,  char* sname, int sline);
unsigned int sNodeTree_create_ge(unsigned int left, unsigned int right,  char* sname, int sline);
unsigned int sNodeTree_create_le(unsigned int left, unsigned int right, char* sname, int sline);
unsigned int sNodeTree_create_logical_denial(unsigned int left, char* sname, int sline);
unsigned int sNodeTree_create_complement(unsigned int left, char* sname, int sline);
unsigned int sNodeTree_create_derefference(unsigned int left, char* sname, int sline);
unsigned int sNodeTree_create_refference(unsigned int left, char* sname, int sline);
unsigned int sNodeTree_create_plus_eq(unsigned int left, unsigned int right, char* sname, int sline);
unsigned int sNodeTree_create_minus_eq(unsigned int left, unsigned int right, char* sname, int sline);
unsigned int sNodeTree_create_load_array_element(unsigned int array, unsigned int index_node[], int num_dimention, char* sname, int sline);
unsigned int sNodeTree_create_store_element(unsigned int array, unsigned int index_node[], int num_dimention, unsigned int right_node, char* sname, int sline);
unsigned int sNodeTree_create_array_initializer(int left, char* var_name, int num_array_value, unsigned int* array_values, BOOL global, char* sname, int sline);
unsigned int sNodeTree_pre_create_function(unsigned int function_params, char* sname, int sline);

//////////////////////////////////
// compile.cpp
//////////////////////////////////
struct sCompileInfoStruct
{
    BOOL no_output;
    int err_num;
    int stack_num;
    sNodeType* type;
    void* current_block;

    void* andand_result_var;
    void* oror_result_var;
    void* lv_table_value;

    sVarTable* lv_table;
    sVarTable* gv_table;

    char sname[PATH_MAX];
    int sline;

    void* function;
    sNodeType* function_result_type;

    void* right_value_objects;

    sNodeType* generics_type;

    void* switch_expression;
    sNodeType* switch_expression_type;
    void* case_else_block;
    void* case_then_block;

    void* loop_end_block[LOOP_NEST_MAX];
    int num_loop;
    void* loop_begin_block[LOOP_NEST_MAX];
    int num_loop2;

    sVarTable* loop_top_lv_table;
    void* loop_top_block;

    BOOL pre_compiling_generics_function;
    char** method_generics_types;

    void* entry_block;
};

typedef struct sCompileInfoStruct sCompileInfo;

BOOL function_existance(char* fun_name);
void dec_stack_ptr(int value, sCompileInfo* info);
BOOL compile(unsigned int node, sCompileInfo* info);
BOOL pre_compile(unsigned int node, sCompileInfo* info);
void llvm_init();
void llvm_final();

BOOL get_const_value_from_node(int* array_size, unsigned int array_size_node, sCompileInfo* cinfo);

extern BOOL gNCDebug;
extern sCompileInfo cinfo;
extern sVarTable* gLVTable;

BOOL pre_compile_block(unsigned int node_block, sCompileInfo* info);
void free_right_value_objects(sCompileInfo* info);

#endif

