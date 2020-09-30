extern "C"
{
#include "common.h"
#include <sys/stat.h>
}

#include "llvm/IR/Verifier.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/DIBuilder.h"
#include "llvm/IR/Metadata.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Verifier.h"

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/Passes/PassBuilder.h"

#if LLVM_VERSION_MAJOR >= 4
#include "llvm/Bitcode/BitcodeWriter.h"
#else
#include "llvm/Bitcode/ReaderWriter.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Pass.h"
#endif

using namespace llvm;

LLVMContext TheContext;
IRBuilder<> Builder(TheContext);
Module* TheModule;
std::unique_ptr<FunctionPassManager> TheFPM;
FunctionAnalysisManager TheFAM(false);

GlobalVariable* gLVTableValue;

//DebugInfo KSDbgInfo;

//DIBuilder* DBuilder;

#include "llvm/Support/FileSystem.h"

struct LVALUEStruct {
    sNodeType* type;
    Value* value;
    Value* address;
    sVar* var;
    BOOL binded_value;
    BOOL load_field;
};

typedef struct LVALUEStruct LVALUE;

LVALUE* gLLVMStack;
LVALUE* gLLVMStackHead;

struct sFunctionStruct {
    char mName[VAR_NAME_MAX];
    Function* mLLVMFunction;
    sNodeType* mResultType;
    int mNumParams;
    sNodeType* mParamTypes[PARAMS_MAX];
};

typedef sFunctionStruct sFunction;

std::map<std::string, sFunction> gFuncs;

BOOL create_llvm_type_from_node_type(Type** result_type, sNodeType* node_type, sNodeType* generics_type, sCompileInfo* info)
{
    sCLClass* klass = node_type->mClass;

    if(klass->mFlags & CLASS_FLAGS_ENUM) 
    {
        *result_type = IntegerType::get(TheContext, 32);
    }
    else if(node_type->mSizeNum > 0) {
        *result_type = IntegerType::get(TheContext, node_type->mSizeNum*8);
    }
    else if(type_identify_with_class_name(node_type, "char"))
    {
        *result_type = IntegerType::get(TheContext, 8);
    }
    else if(type_identify_with_class_name(node_type, "short"))
    {
        *result_type = IntegerType::get(TheContext, 16);
    }
    else if(type_identify_with_class_name(node_type, "int"))
    {
        *result_type = IntegerType::get(TheContext, 32);
    }
    else if(type_identify_with_class_name(node_type, "long"))
    {
        *result_type = IntegerType::get(TheContext, 64);
    }
    else if(type_identify_with_class_name(node_type, "__uint128_t"))
    {
        *result_type = IntegerType::get(TheContext, 128);
    }
    else if(type_identify_with_class_name(node_type, "float"))
    {
        *result_type = Type::getFloatTy(TheContext);
    }
    else if(type_identify_with_class_name(node_type, "double"))
    {
        *result_type = Type::getDoubleTy(TheContext);
    }
    else if(type_identify_with_class_name(node_type, "long_double"))
    {
        *result_type = Type::getFP128Ty(TheContext);
    }
    else if(type_identify_with_class_name(node_type, "any"))
    {
        *result_type = IntegerType::get(TheContext, 64);
    }
    else if(type_identify_with_class_name(node_type, "bool"))
    {
        *result_type = IntegerType::get(TheContext, 1);
    }
    else if(type_identify_with_class_name(node_type, "void"))
    {
        if(node_type->mPointerNum > 0) {
            *result_type = IntegerType::get(TheContext, 8);
        }
        else {
            *result_type = Type::getVoidTy(TheContext);
        }
    }

    int i;
    for(i=0; i<node_type->mPointerNum; i++) {
        *result_type = PointerType::get(*result_type, 0);
    }

    if(node_type->mArrayDimentionNum == -1) {
        *result_type = PointerType::get(*result_type, 0);
    }

    for(i=0; i<node_type->mArrayDimentionNum; i++) {
        *result_type = ArrayType::get(*result_type, node_type->mArrayNum[i]);
    }

    return TRUE;
}

BOOL get_size_from_node_type(uint64_t* result, sNodeType* node_type, sNodeType* generics_type, sCompileInfo* info)
{
    sNodeType* node_type2 = clone_node_type(node_type);

    sCLClass* klass = node_type->mClass;

    char* class_name = klass->mName;

    if(node_type2->mSizeNum > 0) {
        *result = node_type2->mSizeNum;
    }
    else if(node_type2->mPointerNum > 0) {
        *result = 4;
    }
    else {
        Type* llvm_type;
        if(!create_llvm_type_from_node_type(&llvm_type, node_type2, node_type2, info))
        {
            return FALSE;
        }

        DataLayout data_layout(TheModule);

        *result = data_layout.getTypeAllocSize(llvm_type);
    }

    return TRUE;
}

BOOL cast_right_type_to_left_type(sNodeType* left_type, sNodeType** right_type, LVALUE* rvalue, sCompileInfoStruct* info)
{
    sCLClass* left_class = left_type->mClass;
    sCLClass* right_class = (*right_type)->mClass;

    if(left_type->mSizeNum > 0) {
        Type* llvm_type;
        if(!create_llvm_type_from_node_type(&llvm_type, left_type, left_type, info))
        {
            return FALSE;
        }
        
        if(rvalue) {
            uint64_t left_alloc_size;
            if(!get_size_from_node_type(&left_alloc_size, left_type, left_type, info))
            {
                return FALSE;
            }

            uint64_t right_alloc_size;
            if(!get_size_from_node_type(&right_alloc_size, *right_type, *right_type, info))
            {
                return FALSE;
            }

            if(left_alloc_size < right_alloc_size) {
                rvalue->value = Builder.CreateCast(Instruction::Trunc, rvalue->value, llvm_type);
                rvalue->type = clone_node_type(left_type);
            }
            else {
                rvalue->value = Builder.CreateCast(Instruction::SExt, rvalue->value, llvm_type);
                rvalue->type = clone_node_type(left_type);
            }
        }

        *right_type = clone_node_type(left_type);
    }
    else if(left_type->mPointerNum > 0) 
    {
        if(type_identify_with_class_name(*right_type, "lambda")) 
        {
            if(rvalue) {
                Type* llvm_type;
                if(!create_llvm_type_from_node_type(&llvm_type, left_type, left_type, info))
                {
                    return FALSE;
                }

                rvalue->value = Builder.CreateCast(Instruction::BitCast, rvalue->value, llvm_type);
                rvalue->type = clone_node_type(left_type);
            }

            *right_type = clone_node_type(left_type);
        }
        else if((left_type->mPointerNum-1 == (*right_type)->mPointerNum) && (*right_type)->mArrayDimentionNum == 1) 
        {
            if(rvalue) {
                Type* llvm_type;
                if(!create_llvm_type_from_node_type(&llvm_type, left_type, left_type, info))
                {
                    return FALSE;
                }

                if(!info->no_output) {
#if __DARWIN__
                    Value* index = ConstantInt::get(TheContext, llvm::APInt(32, 0));
                    rvalue->value = Builder.CreateGEP(rvalue->address, index);
                    rvalue->value = Builder.CreateCast(Instruction::BitCast, rvalue->value, llvm_type);
                    rvalue->type = clone_node_type(left_type);
#else
                    rvalue->value = Builder.CreateCast(Instruction::BitCast, rvalue->address, llvm_type);
                    rvalue->type = clone_node_type(left_type);
#endif
                }
            }

            *right_type = clone_node_type(left_type);
        }
        else if((*right_type)->mPointerNum > 0) {
            if(rvalue) {
                Type* llvm_type;
                if(!create_llvm_type_from_node_type(&llvm_type, left_type, left_type, info))
                {
                    return FALSE;
                }

                rvalue->value = Builder.CreateCast(Instruction::BitCast, rvalue->value, llvm_type);
                rvalue->type = clone_node_type(left_type);
            }

            *right_type = clone_node_type(left_type);
        }
        else if((*right_type)->mPointerNum == 0) {
            if(rvalue) {
                if(!type_identify_with_class_name(*right_type, "long"))
                {
                    if(left_type->mPointerNum > 0)
                    {
                    }
                    else {
                        rvalue->value = Builder.CreateCast(Instruction::SExt, rvalue->value, IntegerType::get(TheContext, 64), "sext10");
                        rvalue->value = Builder.CreateCast(Instruction::IntToPtr, rvalue->value, IntegerType::get(TheContext, 64), "IntToPtr9");
                    }
                }

                Type* llvm_type;
                if(!create_llvm_type_from_node_type(&llvm_type, left_type, left_type, info))
                {
                    return FALSE;
                }

                rvalue->value = Builder.CreateCast(Instruction::IntToPtr, rvalue->value, llvm_type, "IntToPtr10");
                rvalue->type = clone_node_type(left_type);
            }

            *right_type = clone_node_type(left_type);
        }
    }
    else if(left_type->mArrayDimentionNum == 1 && (*right_type)->mPointerNum == left_type->mPointerNum+1) 
    {
        if(rvalue) {
            Type* llvm_type;
            if(!create_llvm_type_from_node_type(&llvm_type, left_type, left_type, info))
            {
                return FALSE;
            }

            rvalue->value = Builder.CreateCast(Instruction::BitCast, rvalue->value, llvm_type);
            rvalue->type = clone_node_type(left_type);
        }

        *right_type = clone_node_type(left_type);
    }
    else if(type_identify_with_class_name(left_type, "bool"))
    {
        if(rvalue) {
            if((*right_type)->mPointerNum > 0)
            {
                rvalue->value = Builder.CreateCast(Instruction::PtrToInt, rvalue->value, IntegerType::get(TheContext, 64));

                Value* cmp_right_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);
                rvalue->value = Builder.CreateICmpNE(rvalue->value, cmp_right_value);
            }
            else if(type_identify_with_class_name(*right_type, "long")) {
                Value* cmp_right_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);
                rvalue->value = Builder.CreateICmpNE(rvalue->value, cmp_right_value);
            }
            else if(type_identify_with_class_name(*right_type, "int")) {
                Value* cmp_right_value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);
                rvalue->value = Builder.CreateICmpNE(rvalue->value, cmp_right_value);
            }
            else if(type_identify_with_class_name(*right_type, "short")) {
                Value* cmp_right_value = ConstantInt::get(Type::getInt16Ty(TheContext), (uint16_t)0);
                rvalue->value = Builder.CreateICmpNE(rvalue->value, cmp_right_value);
            }
            else if(type_identify_with_class_name(*right_type, "char")) {
                Value* cmp_right_value = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0);
                rvalue->value = Builder.CreateICmpNE(rvalue->value, cmp_right_value);
            }
            else {
                rvalue->value = Builder.CreateCast(Instruction::Trunc, rvalue->value, IntegerType::get(TheContext, 1));
            }

            rvalue->type = create_node_type_with_class_name("bool");
        }

        *right_type = create_node_type_with_class_name("bool");
    }
    else if(type_identify_with_class_name(left_type, "char"))
    {
        if((*right_type)->mPointerNum > 0)
        {
            if(rvalue) {
                rvalue->value = Builder.CreateCast(Instruction::PtrToInt, rvalue->value, IntegerType::get(TheContext, 8));
                rvalue->type = create_node_type_with_class_name("char");
            }

            *right_type = create_node_type_with_class_name("char");
        }
        else if(type_identify_with_class_name(*right_type, "long") || type_identify_with_class_name(*right_type, "int") || type_identify_with_class_name(*right_type, "short"))
        {
            if(rvalue) {
                rvalue->value = Builder.CreateCast(Instruction::Trunc, rvalue->value, IntegerType::get(TheContext, 8));
                rvalue->type = create_node_type_with_class_name("char");
            }

            *right_type = create_node_type_with_class_name("char");
        }
        else if(type_identify_with_class_name(*right_type, "bool"))
        {
            if(rvalue) {
                rvalue->value = Builder.CreateCast(Instruction::ZExt, rvalue->value, IntegerType::get(TheContext, 8), "sext11");
                rvalue->type = create_node_type_with_class_name("char");
            }

            *right_type = create_node_type_with_class_name("char");
        }
    }
    else if(type_identify_with_class_name(left_type, "short"))
    {
        if((*right_type)->mPointerNum > 0)
        {
            if(rvalue) {
                rvalue->value = Builder.CreateCast(Instruction::PtrToInt, rvalue->value, IntegerType::get(TheContext, 16));
                rvalue->type = create_node_type_with_class_name("short");
            }

            *right_type = create_node_type_with_class_name("short");
        }
        else if(type_identify_with_class_name(*right_type, "long") || type_identify_with_class_name(*right_type, "int"))
        {
            if(rvalue) {
                rvalue->value = Builder.CreateCast(Instruction::Trunc, rvalue->value, IntegerType::get(TheContext, 16));
                rvalue->type = create_node_type_with_class_name("short");
            }

            *right_type = create_node_type_with_class_name("short");
        }
        else if(type_identify_with_class_name(*right_type, "char") || type_identify_with_class_name(*right_type, "bool"))
        {
            if(rvalue) {
                rvalue->value = Builder.CreateCast(Instruction::ZExt, rvalue->value, IntegerType::get(TheContext, 32), "sext12");
                rvalue->type = create_node_type_with_class_name("short");
            }

            *right_type = create_node_type_with_class_name("short");
        }
    }
    else if(type_identify_with_class_name(left_type, "int"))
    {
        if((*right_type)->mPointerNum > 0)
        {
            if(rvalue) {
                rvalue->value = Builder.CreateCast(Instruction::PtrToInt, rvalue->value, IntegerType::get(TheContext, 32));
                rvalue->type = create_node_type_with_class_name("int");
            }

            *right_type = create_node_type_with_class_name("int");
        }
        else if(type_identify_with_class_name(*right_type, "long"))
        {
            if(rvalue) {
                rvalue->value = Builder.CreateCast(Instruction::Trunc, rvalue->value, IntegerType::get(TheContext, 32));
                rvalue->type = create_node_type_with_class_name("int");
            }

            *right_type = create_node_type_with_class_name("int");
        }
        else if(type_identify_with_class_name(*right_type, "short") || type_identify_with_class_name(*right_type, "char") || type_identify_with_class_name(*right_type, "bool"))
        {
            if(rvalue) {
                rvalue->value = Builder.CreateCast(Instruction::ZExt, rvalue->value, IntegerType::get(TheContext, 32), "sext13");
                rvalue->type = create_node_type_with_class_name("int");
            }

            *right_type = create_node_type_with_class_name("int");
        }
    }
    else if(type_identify_with_class_name(left_type, "long"))
    {
        if((*right_type)->mPointerNum > 0)
        {
            if(rvalue) {
                rvalue->value = Builder.CreateCast(Instruction::PtrToInt, rvalue->value, IntegerType::get(TheContext, 64));
                rvalue->type = create_node_type_with_class_name("long");
            }

            *right_type = create_node_type_with_class_name("long");
        }
        else if(type_identify_with_class_name(*right_type, "long"))
        {
            *right_type = create_node_type_with_class_name("long");
        }
        else if(type_identify_with_class_name(*right_type, "int") || type_identify_with_class_name(*right_type, "short") || type_identify_with_class_name(*right_type, "char") || type_identify_with_class_name(*right_type, "bool"))
        {
            if(rvalue) {
                rvalue->value = Builder.CreateCast(Instruction::ZExt, rvalue->value, IntegerType::get(TheContext, 64), "sext14");
                rvalue->type = create_node_type_with_class_name("long");
            }

            *right_type = create_node_type_with_class_name("long");
        }
    }

    return TRUE;
}

BOOL add_function(char* fun_name, sNodeType* result_type, int num_params, sNodeType** param_types, sCompileInfo* info)
{
    sFunction fun;

    xstrncpy(fun.mName, fun_name, VAR_NAME_MAX);
    fun.mResultType = clone_node_type(result_type);
    fun.mNumParams = num_params;

    Type* llvm_result_type;
    if(!create_llvm_type_from_node_type(&llvm_result_type, result_type, result_type, info))
    {
        return TRUE;
    }

    std::vector<Type *> llvm_param_types;

    int i;
    for(i=0; i<num_params; i++) {
        sNodeType* param_type = param_types[i];

        Type* llvm_param_type;
        if(!create_llvm_type_from_node_type(&llvm_param_type, param_type, param_type, info))
        {
            return FALSE;
        }
        llvm_param_types.push_back(llvm_param_type);

        fun.mParamTypes[i] = clone_node_type(param_types[i]);
    }

    FunctionType* function_type = FunctionType::get(llvm_result_type, llvm_param_types, false);
    Function* llvm_fun = Function::Create(function_type, Function::ExternalLinkage, fun_name, TheModule);
    fun.mLLVMFunction = llvm_fun;

    gFuncs[fun_name] = fun;

    return TRUE;
}

void compile_err_msg(sCompileInfo* info, const char* msg, ...)
{
    char msg2[1024];

    va_list args;
    va_start(args, msg);
    vsnprintf(msg2, 1024, msg, args);
    va_end(args);

    static int output_num = 0;

    if(output_num < COMPILE_ERR_MSG_MAX) {
        fprintf(stderr, "%s:%d: %s\n", info->sname, info->sline, msg2);
    }
    output_num++;
}

void start_to_make_native_code()
{
    char module_name[PATH_MAX + 128];
    if(gSName[0] == '\0') {
        snprintf(module_name, PATH_MAX, "Module stdin");
    }
    else {
        snprintf(module_name, PATH_MAX, "Module %s", gSName);
    }

    TheModule = new Module(module_name, TheContext);

    if(gNCDebug) {
        TheModule->addModuleFlag(Module::Warning, "Debug Info Version", DEBUG_METADATA_VERSION);
        TheModule->addModuleFlag(llvm::Module::Warning, "Dwarf Version", 2);
    }

    const char* cwd = getenv("PWD");

    if(cwd == NULL) {
        cwd = ".";
    }

#if LLVM_VERSION_MAJOR <= 9
    TheFPM = llvm::make_unique<FunctionPassManager>(TheModule);
#else
    TheFPM = std::make_unique<FunctionPassManager>(TheModule);
#endif
}

void output_native_code()
{
    //DBuilder->finalize();
    free(gLLVMStack);

    if(gSName[0] == '\0') {
        xstrncpy(gSName, "stdin", PATH_MAX);
    }

    {
#if LLVM_VERSION_MAJOR >= 7
    char path[PATH_MAX];
    snprintf(path, PATH_MAX, "%s.ll", gSName);

    (void)unlink(path);

    std::error_code ecode;
    llvm::raw_fd_ostream output_stream(path, ecode, llvm::sys::fs::F_None);

    std::string err_str;
    raw_string_ostream err_ostream(err_str);

    TheModule->print(output_stream, nullptr);
    output_stream.flush();

    (void)chmod(path, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
#elif LLVM_VERSION_MAJOR >= 4
    char path[PATH_MAX]; 
    snprintf(path, PATH_MAX, "%s.ll", gSName);

    (void)unlink(path);

    std::error_code ecode;
    llvm::raw_fd_ostream output_stream(path, ecode, llvm::sys::fs::F_None);

    std::string err_str;
    raw_string_ostream err_ostream(err_str);

    TheModule->print(output_stream, nullptr);
    output_stream.flush();

    (void)chmod(path, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
#else
    char path[PATH_MAX];
    snprintf(path, PATH_MAX, "%s.ll", gSName);

    (void)unlink(path);

    std::error_code ecode;
    llvm::raw_fd_ostream output_stream(path, ecode, llvm::sys::fs::F_None);

    std::string err_str;
    raw_string_ostream err_ostream(err_str);

    TheModule->print(output_stream, nullptr);
    output_stream.flush();

    (void)chmod(path, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);

    verifyModule(*TheModule);
#endif
    }

    delete TheModule;
}

static Type* get_lvtable_type()
{
    char buf[128];

    snprintf(buf, 128, "char*[%d]", LOCAL_VARIABLE_MAX);

    sNodeType* lvtable_node_type = create_node_type_with_class_name(buf);

    Type* lvtable_type;
    if(!create_llvm_type_from_node_type(&lvtable_type, lvtable_node_type, lvtable_node_type, NULL))
    {
        fprintf(stderr, "unexpected err\n");
        exit(2);
    }

    return lvtable_type;
}

void llvm_init()
{
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    start_to_make_native_code();

    gLLVMStack = (LVALUE*)xcalloc(1, sizeof(LVALUE)*NEO_C_STACK_SIZE);
    gLLVMStackHead = gLLVMStack;

    Type* lvtable_type = get_lvtable_type();

    gLVTableValue = new GlobalVariable(*TheModule, lvtable_type, false, GlobalValue::InternalLinkage, 0, "gLVTable");
    gLVTableValue->setAlignment(8);

    ConstantAggregateZero* initializer = ConstantAggregateZero::get(lvtable_type);

    gLVTableValue->setInitializer(initializer);
}

void llvm_final()
{
    output_native_code();
}

void dec_stack_ptr(int value, sCompileInfo* info)
{
    gLLVMStack -= value;

    info->stack_num -= value;
}

void push_value_to_stack_ptr(LVALUE* value, sCompileInfo* info)
{
    *gLLVMStack= *value;
    gLLVMStack++;

    info->stack_num++;
}

void arrange_stack(sCompileInfo* info, int top)
{
    if(info->stack_num > top) {
        dec_stack_ptr(info->stack_num-top, info);
    }
    if(info->stack_num < top) {
        fprintf(stderr, "%s %d: unexpected stack value. The stack num is %d. top is %d\n", gSName, gSLine, info->stack_num, top);
        exit(2);
    }
}

LVALUE* get_value_from_stack(int offset)
{
    return gLLVMStack + offset;
}


void llvm_change_block(BasicBlock* current_block, BasicBlock** current_block_before, sCompileInfo* info, BOOL no_free_right_objects)
{
/*
    if(!no_free_right_objects) {
        free_right_value_objects(info);
    }
*/

    *current_block_before = (BasicBlock*)info->current_block;

    Builder.SetInsertPoint(current_block);
    info->current_block = current_block;
}

static BOOL compile_block(unsigned int node_block, sCompileInfo* info, BOOL* last_expression_is_return)
{
    int num_nodes = gNodes[node_block].uValue.sBlock.mNumNodes;
    unsigned int* nodes = gNodes[node_block].uValue.sBlock.mNodes;

    sVarTable* lv_table = info->lv_table;
    info->lv_table = init_block_vtable(lv_table, FALSE);

    int i;
    for(i=0; i<num_nodes; i++) {
        unsigned int node = nodes[i];
        if(!compile(node, info)) {
            return FALSE;
        }

        dec_stack_ptr(info->stack_num, info);

        *last_expression_is_return = gNodes[node].mNodeType == kNodeTypeReturn;
    }

    info->lv_table= lv_table;

    return TRUE;
}

int get_llvm_alignment_from_node_type(sNodeType* node_type)
{
    int result = 0;

    sCLClass* klass = node_type->mClass;

    if(klass->mFlags & CLASS_FLAGS_STRUCT) {
        result = 8;
    }
    else if(klass->mFlags & CLASS_FLAGS_UNION) {
        result = 8;
    }
    else if(node_type->mPointerNum > 0) {
        result = 8;
    }
    else if(type_identify_with_class_name(node_type, "char"))
    {
        result = 1;
    }
    else if(type_identify_with_class_name(node_type, "short"))
    {
        result = 2;
    }
    else if(type_identify_with_class_name(node_type, "int"))
    {
        result = 4;
    }
    else if(type_identify_with_class_name(node_type, "bool"))
    {
        result = 1;
    }
    else if(type_identify_with_class_name(node_type, "lambda"))
    {
        result = 8;
    }

    return result;
}

void store_address_to_lvtable(int index, Value* address)
{
    Value* lvtable_value2 = Builder.CreateCast(Instruction::BitCast, gLVTableValue, PointerType::get(PointerType::get(IntegerType::get(TheContext, 8), 0), 0));

    Value* lvalue = lvtable_value2;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(32, index));
    Value* element_address_value = Builder.CreateGEP(lvalue, rvalue);
    Value* address2 = Builder.CreateCast(Instruction::BitCast, address, PointerType::get(IntegerType::get(TheContext, 8), 0));

    Builder.CreateAlignedStore(address2, element_address_value, 8);
}

BOOL compile_function(unsigned int node, sCompileInfo* info)
{
    char fun_name[VAR_NAME_MAX];
    xstrncpy(fun_name, gNodes[node].uValue.sFunction.mName, VAR_NAME_MAX);
    int num_params = gNodes[node].uValue.sFunction.mNumParams;

    sParserParam params[PARAMS_MAX];

    int i;
    for(i=0; i<num_params; i++) {
        sParserParam* param = gNodes[node].uValue.sFunction.mParams + i;
        xstrncpy(params[i].mName, param->mName, VAR_NAME_MAX);
        xstrncpy(params[i].mTypeName, param->mTypeName, VAR_NAME_MAX);
        params[i].mType = create_node_type_with_class_name(param->mTypeName);
    }

    sNodeType* result_type = create_node_type_with_class_name(gNodes[node].uValue.sFunction.mResultTypeName);

    unsigned int node_block = gNodes[node].uValue.sFunction.mNodeBlock;

    sNodeType* param_types[PARAMS_MAX];

    for(i=0; i<num_params; i++) {
        param_types[i] = params[i].mType;
    }

    if(!add_function(fun_name, result_type, num_params, param_types, info)) {
        return FALSE;
    }

    sFunction fun = gFuncs[fun_name];

    Function* llvm_fun = fun.mLLVMFunction;

    info->llvm_function = llvm_fun;

    int n = 0;
    std::vector<Value *> llvm_params;
    for(auto &llvm_param : llvm_fun->args()) {
        sParserParam param = params[n];
        char* var_name = param.mName;

        llvm_params.push_back(&llvm_param);
        llvm_param.setName(var_name);
        
        n++;
    }

    sVarTable* lv_table = info->lv_table;
    info->lv_table = init_block_vtable(lv_table, FALSE);

    BasicBlock* current_block_before;
    BasicBlock* current_block = BasicBlock::Create(TheContext, "entry", llvm_fun);
    llvm_change_block(current_block, &current_block_before, info, FALSE);

    info->andand_result_var = (void*)Builder.CreateAlloca(IntegerType::get(TheContext, 1), 0, "andand_result_var");
    info->oror_result_var = (void*)Builder.CreateAlloca(IntegerType::get(TheContext, 1), 0, "andand_result_var");

    /// ready for params ///
    for(i=0; i<num_params; i++) {
        sParserParam param = params[i];
        char* var_name = param.mName;

        sNodeType* var_type = create_node_type_with_class_name(param.mTypeName);

        BOOL readonly = FALSE;
        BOOL constant = FALSE;
        BOOL global = FALSE;
        int index = -1;
        void* llvm_value = NULL;
        if(!add_variable_to_table(info->lv_table, var_name, var_type, llvm_value,  index, global, constant))
        {
            compile_err_msg(info, "overflow variable table");
            return FALSE;
        }

        sVar* var = get_variable_from_table(info->lv_table, (char*)var_name);

        Type* llvm_type;
        if(!create_llvm_type_from_node_type(&llvm_type, var_type, var_type, info))
        {
            compile_err_msg(info, "Getting llvm type failed(6)");
            show_node_type(var_type);
            info->err_num++;
            return FALSE;
        }

        int alignment = get_llvm_alignment_from_node_type(var_type);

        Value* address = Builder.CreateAlloca(llvm_type, 0, var_name);
        var->mLLVMValue = address;

        Builder.CreateAlignedStore(llvm_params[i], address, alignment);

        BOOL parent = FALSE;
        index = get_variable_index(info->lv_table, var_name, &parent);

        store_address_to_lvtable(index, address);
    }

    BOOL last_expression_is_return = FALSE;
    if(!compile_block(node_block, info, &last_expression_is_return)) {
        return FALSE;
    }

    verifyFunction(*llvm_fun);

    // Run the optimizer on the function.
    //TheFPM->run(*llvm_fun, TheFAM);

    info->type = create_node_type_with_class_name("void");

    if(info->no_output) {
        llvm_fun->eraseFromParent();
    }

    info->lv_table = lv_table;

    return TRUE;
}

BOOL compile_external_function(unsigned int node, sCompileInfo* info)
{
    char fun_name[VAR_NAME_MAX];
    xstrncpy(fun_name, gNodes[node].uValue.sFunction.mName, VAR_NAME_MAX);
    int num_params = gNodes[node].uValue.sFunction.mNumParams;

    sParserParam params[PARAMS_MAX];

    int i;
    for(i=0; i<num_params; i++) {
        sParserParam* param = gNodes[node].uValue.sFunction.mParams + i;
        xstrncpy(params[i].mName, param->mName, VAR_NAME_MAX);
        xstrncpy(params[i].mTypeName, param->mTypeName, VAR_NAME_MAX);
        params[i].mType = create_node_type_with_class_name(param->mTypeName);
    }

    sNodeType* result_type = create_node_type_with_class_name(gNodes[node].uValue.sFunction.mResultTypeName);

    sNodeType* param_types[PARAMS_MAX];

    for(i=0; i<num_params; i++) {
        param_types[i] = params[i].mType;
    }

    if(!add_function(fun_name, result_type, num_params, param_types, info)) {
        return FALSE;
    }

    return TRUE;
}

static BOOL compile_int_value(unsigned int node, sCompileInfo* info)
{
    int value = gNodes[node].uValue.mIntValue;

    LVALUE llvm_value;
    llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(32, value, true)); 
    llvm_value.type = create_node_type_with_class_name("int");
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("int");

    return TRUE;
}

Value* llvm_create_string(char* str)
{
    Constant* str_constant = ConstantDataArray::getString(TheModule->getContext(), str, true);

    GlobalVariable* gvar = new GlobalVariable(*TheModule, ArrayType::get(IntegerType::get(TheContext, 8), strlen(str)+1), true, GlobalValue::PrivateLinkage, 0, "global_string");
    gvar->setAlignment(1);

    gvar->setInitializer(str_constant);

    Value* value = Builder.CreateCast(Instruction::BitCast, gvar, PointerType::get(IntegerType::get(TheContext, 8), 0));

    return value;
}

static BOOL compile_str_value(unsigned int node, sCompileInfo* info)
{
    char buf[512];
    xstrncpy(buf, gNodes[node].uValue.mStrValue, 512);

    LVALUE llvm_value;
    llvm_value.value = llvm_create_string(buf);
    llvm_value.type = create_node_type_with_class_name("char*");
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("char*");

    return TRUE;
}

static BOOL compile_add(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    LVALUE lvalue = *get_value_from_stack(-1);

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    LVALUE rvalue = *get_value_from_stack(-1);

    LVALUE llvm_value;

    llvm_value.value = Builder.CreateAdd(lvalue.value, rvalue.value, "addtmp", false, true);
    llvm_value.type = clone_node_type(left_type);
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    dec_stack_ptr(2, info);
    push_value_to_stack_ptr(&llvm_value, info);

    info->type = clone_node_type(llvm_value.type);

    return TRUE;
}

static BOOL compile_return(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    LVALUE lvalue = *get_value_from_stack(-1);

    dec_stack_ptr(1, info);

    Builder.CreateRet(lvalue.value);

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

Value* load_address_to_lvtable(int index, sNodeType* var_type, sCompileInfo* info)
{
    Value* lvtable_value2 = Builder.CreateCast(Instruction::BitCast, gLVTableValue, PointerType::get(PointerType::get(IntegerType::get(TheContext, 8), 0), 0));

    Value* lvalue = lvtable_value2;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(32, index));
    Value* element_address_value = Builder.CreateGEP(lvalue, rvalue);

    Value* pointer_value = Builder.CreateAlignedLoad(element_address_value, 8);

    int alignment = get_llvm_alignment_from_node_type(var_type);

    Type* llvm_type;
    (void)create_llvm_type_from_node_type(&llvm_type, var_type, var_type, info);

    Value* pointer_value2 = Builder.CreateCast(Instruction::BitCast, pointer_value, PointerType::get(llvm_type, 0));

    return pointer_value2;
}


static BOOL compile_store_varialbe(unsigned int node, sCompileInfo* info)
{
    char var_name[VAR_NAME_MAX];
    char type_name[VAR_NAME_MAX];

    xstrncpy(var_name, gNodes[node].uValue.sStoreVariable.mVarName, VAR_NAME_MAX);
    xstrncpy(type_name, gNodes[node].uValue.sStoreVariable.mTypeName, VAR_NAME_MAX);
    BOOL alloc = gNodes[node].uValue.sStoreVariable.mAlloc;

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    LVALUE rvalue = *get_value_from_stack(-1);

    int index = -1;
    if(alloc) {
        sNodeType* var_type = create_node_type_with_class_name(type_name);

        BOOL readonly = FALSE;
        BOOL constant = FALSE;
        BOOL global = FALSE;
        void* llvm_value = NULL;
        if(!add_variable_to_table(info->lv_table, var_name, var_type, llvm_value,  index, global, constant))
        {
            compile_err_msg(info, "overflow variable table");
            return FALSE;
        }

        Type* llvm_var_type;
        if(!create_llvm_type_from_node_type(&llvm_var_type, var_type, var_type, info))
        {
            return TRUE;
        }

        int alignment = get_llvm_alignment_from_node_type(var_type);
        
        Value* address = Builder.CreateAlloca(llvm_var_type, 0, var_name);

        sVar* var = get_variable_from_table(info->lv_table, var_name);

        var->mLLVMValue = address;

        store_address_to_lvtable(index, address);
    }

    if(!info->no_output) {
        sVar* var = get_variable_from_table(info->lv_table, var_name);
        sNodeType* var_type = var->mType;

        Type* llvm_var_type;
        if(!create_llvm_type_from_node_type(&llvm_var_type, var_type, var_type, info))
        {
            return TRUE;
        }

        int alignment = get_llvm_alignment_from_node_type(var_type);

        BOOL parent = FALSE;
        index = get_variable_index(info->lv_table, var_name, &parent);

        Value* var_address;
        if(parent && !var->mGlobal) {
            var_address = load_address_to_lvtable(index, var_type, info);
        }
        else {
            var_address = (Value*)var->mLLVMValue;
        }

        if(var_address == nullptr) {
            compile_err_msg(info, "Invalid storing variable %s\n", var_name);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        Value* rvalue2 = Builder.CreateCast(Instruction::BitCast, rvalue.value, llvm_var_type);

        //std_move(var_address, var->mType, &rvalue, alloc, info);

        Builder.CreateAlignedStore(rvalue2, var_address, alignment);
    }

    info->type = right_type;

    return TRUE;
}

static BOOL compile_load_variable(unsigned int node, sCompileInfo* info)
{
    char var_name[VAR_NAME_MAX];

    xstrncpy(var_name, gNodes[node].uValue.sLoadVariable.mVarName, VAR_NAME_MAX);

    sVar* var = get_variable_from_table(info->lv_table, var_name);

    if(var == NULL || var->mType == NULL) {
        compile_err_msg(info, "undeclared variable %s", var_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    sNodeType* var_type = clone_node_type(var->mType);
    if(var_type == NULL || var_type->mClass == NULL) 
    {
        compile_err_msg(info, "null type %s", var_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    BOOL constant = var->mConstant;

    if(constant) {
    }
    else {
        BOOL parent = FALSE;
        int index = get_variable_index(info->lv_table, var_name, &parent);

        Value* var_address;
        if(parent && !var->mGlobal) {
            var_address = load_address_to_lvtable(index, var_type, info);
        }
        else {
            var_address = (Value*)var->mLLVMValue;
        }

        if(var_address == nullptr && !info->no_output) {
            compile_err_msg(info, "Invalid variable. %s. load variable", var_name);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        int alignment = get_llvm_alignment_from_node_type(var_type);

        LVALUE llvm_value;

        llvm_value.value = Builder.CreateAlignedLoad(var_address, alignment, var_name);

        llvm_value.type = var_type;
        llvm_value.address = var_address;
        llvm_value.var = var;
        llvm_value.binded_value = TRUE;
        llvm_value.load_field = FALSE;

        push_value_to_stack_ptr(&llvm_value, info);

        sNodeType* result_type = var_type;

        info->type = clone_node_type(result_type);
    }

    return TRUE;
}

Value* get_dummy_value(sNodeType* node_type, sCompileInfo* info)
{
    Type* llvm_type;
    if(!create_llvm_type_from_node_type(&llvm_type, node_type, node_type, info))
    {
        return FALSE;
    }

    Value* address = Builder.CreateAlloca(llvm_type, 0, "dummy");

    int alignment = get_llvm_alignment_from_node_type(node_type);

    return Builder.CreateAlignedLoad(address, alignment, "dummy_value");
}

BOOL compile_function_call(unsigned int node, sCompileInfo* info)
{
    char fun_name[VAR_NAME_MAX];
    xstrncpy(fun_name, gNodes[node].uValue.sFunctionCall.mFunName, VAR_NAME_MAX);
    int num_params = gNodes[node].uValue.sFunctionCall.mNumParams;

    unsigned int params[PARAMS_MAX];
    int i;
    for(i=0; i<num_params; i++) {
        params[i] = gNodes[node].uValue.sFunctionCall.mParams[i];
    }

    sFunction fun = gFuncs[fun_name];

    /// compile parametors ///
    sNodeType* param_types[PARAMS_MAX];
    std::vector<Value*> llvm_params;
    for(i=0; i<num_params; i++) {
        if(!compile(params[i], info)) {
            return FALSE;
        }

        param_types[i] = clone_node_type(info->type);
    }
    for(i=0; i<num_params; i++) {
        LVALUE* param = get_value_from_stack(-i-1);

        llvm_params.push_back(param->value);
    }


    sNodeType* result_type = clone_node_type(fun.mResultType);

    if(!info->no_output) {
        Function* llvm_fun = fun.mLLVMFunction;

        if(llvm_fun == nullptr) {
            return TRUE;
        }

        LVALUE llvm_value;
        llvm_value.value = Builder.CreateCall(llvm_fun, llvm_params);
        llvm_value.type = clone_node_type(result_type);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(result_type);
    }
    else {
        LVALUE llvm_value;
        llvm_value.value = get_dummy_value(result_type, info);
        llvm_value.type = clone_node_type(result_type);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(result_type);
    }

    return TRUE;
}

static BOOL compile_if(unsigned int node, sCompileInfo* info)
{
    unsigned int else_block = gNodes[node].uValue.sIf.mElseBlock;
    int elif_num = gNodes[node].uValue.sIf.mElifNum;

    /// compile expression ///
    unsigned int if_exp = gNodes[node].uValue.sIf.mIfExp;

    if(!compile(if_exp, info)) {
        return FALSE;
    }

    sNodeType* conditional_type = info->type;

    LVALUE conditional_value = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    sNodeType* bool_type = create_node_type_with_class_name("bool");

    if(auto_cast_posibility(bool_type, conditional_type)) {
        if(!cast_right_type_to_left_type(bool_type, &conditional_type, &conditional_value, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    if(!type_identify_with_class_name(conditional_type, "bool")) {
        compile_err_msg(info, "This conditional type is not bool");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    Function* llvm_function = (Function*)info->llvm_function;

    BasicBlock* cond_then_block = BasicBlock::Create(TheContext, "cond_jump_then", llvm_function);
    BasicBlock* cond_else_block = NULL;

    BasicBlock* cond_elif_block[ELIF_NUM_MAX];
    BasicBlock* cond_elif_then_block[ELIF_NUM_MAX];
    if(elif_num > 0) {
        int i;
        for(i=0; i<elif_num; i++) {
            char buf[128];
            snprintf(buf, 128, "cond_jump_elif%d\n", i);

            cond_elif_block[i] = BasicBlock::Create(TheContext, buf, llvm_function);

            snprintf(buf, 128, "cond_jump_elif_then%d\n", i);

            cond_elif_then_block[i] = BasicBlock::Create(TheContext, buf, llvm_function);
        }
    }

    if(else_block) {
        cond_else_block = BasicBlock::Create(TheContext, "cond_else_block", llvm_function);
    }
    BasicBlock* cond_end_block = BasicBlock::Create(TheContext, "cond_end", llvm_function);

    if(elif_num > 0) {
        Builder.CreateCondBr(conditional_value.value, cond_then_block, cond_elif_block[0]);
    }
    else if(else_block) {
        Builder.CreateCondBr(conditional_value.value, cond_then_block, cond_else_block);
    }
    else {
        Builder.CreateCondBr(conditional_value.value, cond_then_block, cond_end_block);
    }

    BasicBlock* current_block_before;
    llvm_change_block(cond_then_block, &current_block_before, info, FALSE);

    unsigned int if_block = gNodes[node].uValue.sIf.mIfBlock;
    sNodeType* result_type = create_node_type_with_class_name("void");

    BOOL last_expression_is_return = FALSE;
    if(!compile_block(if_block, info, &last_expression_is_return)) {
        return FALSE;
    }

    if(!last_expression_is_return) {
        Builder.CreateBr(cond_end_block);
    }

    //// elif ///
    if(elif_num > 0) {
        int i;
        for(i=0; i<elif_num; i++) {
            BasicBlock* current_block_before;
            llvm_change_block(cond_elif_block[i], &current_block_before, info, FALSE);

            unsigned int if_exp = gNodes[node].uValue.sIf.mElifExps[i];

            if(!compile(if_exp, info)) {
                return FALSE;
            }

            sNodeType* conditional_type = info->type;

            LVALUE conditional_value = *get_value_from_stack(-1);
            dec_stack_ptr(1, info);

            sNodeType* bool_type = create_node_type_with_class_name("bool");

            if(auto_cast_posibility(bool_type, conditional_type)) {
                if(!cast_right_type_to_left_type(bool_type, &conditional_type, &conditional_value, info))
                {
                    compile_err_msg(info, "Cast failed");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }

            if(!type_identify_with_class_name(conditional_type, "bool")) 
            {
                compile_err_msg(info, "This conditional type is not bool");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            if(i == elif_num-1) {
                if(else_block) {
                    Builder.CreateCondBr(conditional_value.value, cond_elif_then_block[i], cond_else_block);
                }
                else {
                    Builder.CreateCondBr(conditional_value.value, cond_elif_then_block[i], cond_end_block);
                }
            }
            else {
                Builder.CreateCondBr(conditional_value.value, cond_elif_then_block[i], cond_elif_block[i+1]);
            }

            BasicBlock* current_block_before2;
            llvm_change_block(cond_elif_then_block[i], &current_block_before2, info, FALSE);

            unsigned int elif_block = gNodes[node].uValue.sIf.mElifBlocks[i];

            BOOL last_expression_is_return = FALSE;

            if(!compile_block(elif_block, info, &last_expression_is_return))
            {
                return FALSE;
            }

            if(!last_expression_is_return) {
                Builder.CreateBr(cond_end_block);
            }
        }
    }

    if(else_block) {
        BasicBlock* current_block_before;
        llvm_change_block(cond_else_block, &current_block_before, info, FALSE);

        BOOL last_expression_is_return = FALSE;

        if(!compile_block(else_block, info, &last_expression_is_return))
        {
            return FALSE;
        }

        if(!last_expression_is_return) {
            Builder.CreateBr(cond_end_block);
        }
    }

    BasicBlock* current_block_before2;
    llvm_change_block(cond_end_block, &current_block_before2, info, FALSE);

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

BOOL compile(unsigned int node, sCompileInfo* info)
{
//show_node(node);
    
    xstrncpy(info->sname, gNodes[node].mSName, PATH_MAX);
    info->sline = gNodes[node].mLine;

    switch(gNodes[node].mNodeType) {
        case kNodeTypeFunction:
            if(!compile_function(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeIntValue:
            if(!compile_int_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeCStringValue:
            if(!compile_str_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeAdd:
            if(!compile_add(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeReturn:
            if(!compile_return(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeSub:
            break;

        case kNodeTypeMult:
            break;

        case kNodeTypeDiv:
            break;

        case kNodeTypeBlock:
            break;

        case kNodeTypeStoreVariable:
            if(!compile_store_varialbe(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLoadVariable:
            if(!compile_load_variable(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeFunctionCall:
            if(!compile_function_call(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeExternalFunction:
            if(!compile_external_function(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeIf:
            if(!compile_if(node, info)) {
                return FALSE;
            }
            break;
    }
    

    return TRUE;
}

