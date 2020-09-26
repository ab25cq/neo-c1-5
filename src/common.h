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
#define VAR_NAME_MAX 128
#define CLASS_NUM_MAX 512*2*2*2*2*2
#define PARSER_ERR_MSG_MAX 5
#define COMPILE_ERR_MSG_MAX 5
#define NEO_C_STACK_SIZE 512
#define LOCAL_VARIABLE_MAX 4096*2
#define PARAMS_MAX 32
#define METHOD_DEFAULT_PARAM_MAX 128
#define SOURCE_EXPRESSION_MAX 4096*2
#define ELIF_NUM_MAX 128
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

sCLClass* get_class(char* class_name);
sCLClass* alloc_struct(char* class_name, BOOL anonymous);
sCLClass* alloc_enum(char* class_name);
void add_fields_to_struct(sCLClass* klass, int num_fields, char** field_name, struct sNodeTypeStruct* fields[STRUCT_FIELD_MAX]);
sCLClass* alloc_union(char* class_name, BOOL anonymous, BOOL anonymous_var_name);
void add_fields_to_union(sCLClass* klass, int num_fields, char** field_name, struct sNodeTypeStruct* fields[STRUCT_FIELD_MAX]);
unsigned int get_hash_key(char* name, unsigned int max);
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
sNodeType* create_node_type_with_class_name(char* class_name);
sNodeType* create_node_type_with_class_pointer(sCLClass* klass);
BOOL cast_posibility(sNodeType* left_type, sNodeType* right_type);
BOOL auto_cast_posibility(sNodeType* left_type, sNodeType* right_type);

BOOL substitution_posibility(sNodeType* left_type, sNodeType* right_type, BOOL no_output);
BOOL type_identify(sNodeType* left, sNodeType* right);
BOOL type_identify_with_class_name(sNodeType* left, char* right_class_name);
BOOL is_number_type(sNodeType* node_type);
void show_node_type(sNodeType* node_type);
BOOL solve_generics(sNodeType** node_type, sNodeType* generics_type, BOOL* success_solve);
BOOL solve_method_generics(sNodeType** node_type, int num_method_generics_types, sNodeType* method_generics_types[GENERICS_TYPES_MAX]);
BOOL substitution_posibility(sNodeType* left_type, sNodeType* right_type, BOOL no_output);
BOOL is_typeof_type(sNodeType* node_type);
BOOL included_generics_type(sNodeType* node_type, sCLClass* checked_class[], int* num_checked_class);
BOOL get_type_of_method_generics(sNodeType* method_generics_types[GENERICS_TYPES_MAX], sNodeType* fun_param_type, sNodeType* param_type);
void create_type_name_from_node_type(char* type_name, int type_name_max, sNodeType* node_type, BOOL neo_c);
  
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

void add_typedef(char* name, sNodeType* node_type);
sNodeType* get_typedef(char* name);

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
extern int gSLine;
extern int gErrNum;

/////////////////////////////// 
// node.c
/////////////////////////////// 
enum eNodeType { kNodeTypeIntValue, kNodeTypeAdd, kNodeTypeSub, kNodeTypeMult, kNodeTypeDiv, kNodeTypeBlock, kNodeTypeFunction, kNodeTypeFunctionParams , kNodeTypeReturn, kNodeTypeStoreVariable };

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

        struct {
            unsigned int* mNodes;
            unsigned int mSizeNodes;
            unsigned int mNumNodes;

            sVarTable* mLVTable;

            sBuf mSource;
        } sBlock;
        struct {
            char mVarName[VAR_NAME_MAX];
            char mTypeName[VAR_NAME_MAX];
            BOOL mAlloc;
        } sStoreVariable;
        struct {
            char mName[VAR_NAME_MAX];
            sParserParam mParams[PARAMS_MAX];
            int mNumParams;
            char mResultTypeName[VAR_NAME_MAX];
            unsigned int mNodeBlock;
        } sFunction;

        struct {
            int mNumParams;
            sParserParam mParams[PARAMS_MAX];
        } sFunctionParams;
    } uValue;
};

typedef struct sNodeTreeStruct sNodeTree;

extern sNodeTree* gNodes;

void append_node_to_node_block(unsigned int node_block, unsigned int node);
void append_param_to_function_params(unsigned int function_params, char* type_name, char* name);
void show_node(unsigned int node);
void init_nodes();
void free_nodes();

unsigned int sNodeTree_create_int_value(int value, char* sname, int sline);
unsigned int sNodeTree_create_add(unsigned int left, unsigned int right, unsigned int middle, char* sname, int sline);
unsigned int sNodeTree_create_sub(unsigned int left, unsigned int right, unsigned int middle, char* sname, int sline);
unsigned int sNodeTree_create_mult(unsigned int left, unsigned int right, unsigned int middle, char* sname, int sline);
unsigned int sNodeTree_create_div(unsigned int left, unsigned int right, unsigned int middle, char* sname, int sline);
unsigned int sNodeTree_create_function(char* fun_name, unsigned int function_params, char* result_type_name, unsigned int node_block, char* sname, int sline);
unsigned int sNodeTree_create_function_params(char* sname, int sline);
unsigned int sNodeTree_create_store_variable(char* var_name, char* type_name, unsigned int right, BOOL alloc, char* sname, int sline);

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

    sVarTable* lv_table;

    char sname[PATH_MAX];
    int sline;
};

typedef struct sCompileInfoStruct sCompileInfo;

void dec_stack_ptr(int value, sCompileInfo* info);
BOOL compile(unsigned int node, sCompileInfo* info);
void llvm_init();
void llvm_final();

extern BOOL gNCDebug;

#endif

