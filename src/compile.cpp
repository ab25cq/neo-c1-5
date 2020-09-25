extern "C"
{
#include "common.h"
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
};

typedef sFunctionStruct sFunction;

std::map<std::string, sFunction> gFuncs;

void start_to_make_native_code(char* sname)
{
    char sname2[PATH_MAX];
    xstrncpy(sname2, sname, PATH_MAX);

    char* sname3 = basename(sname2);

    char sname4[PATH_MAX];
    xstrncpy(sname4, sname3, PATH_MAX);

    char* p = sname4 + strlen(sname4);
    while(p >= sname4) {
        if(*p == '.') {
            *p = '\0';
            break;
        }
        else {
            p--;
        }
    }

    char module_name[PATH_MAX + 128];
    snprintf(module_name, PATH_MAX, "Module %s", sname4);
    TheModule = new Module(module_name, TheContext);

    if(gNCDebug) {
        TheModule->addModuleFlag(Module::Warning, "Debug Info Version", DEBUG_METADATA_VERSION);
        TheModule->addModuleFlag(llvm::Module::Warning, "Dwarf Version", 2);
    }

    //DBuilder = new DIBuilder(*TheModule);

    char* cwd = getenv("PWD");

    if(cwd == NULL) {
        cwd = ".";
    }

/*
#if LLVM_VERSION_MAJOR >= 5
    KSDbgInfo.TheCU = DBuilder->createCompileUnit(
        dwarf::DW_LANG_C, DBuilder->createFile(sname, cwd), "neo-c", 0, "", 0);
#else
    KSDbgInfo.TheCU = DBuilder->createCompileUnit(
        dwarf::DW_LANG_C, sname, cwd, "neo-c", false, "", 0);
#endif
*/

#if LLVM_VERSION_MAJOR <= 9
    TheFPM = llvm::make_unique<FunctionPassManager>(TheModule);
#else
    TheFPM = make_unique<FunctionPassManager>(TheModule);
#endif

    //create_internal_functions();
    //TheLabels.clear();
  
    gLLVMStack = (LVALUE*)xcalloc(1, sizeof(LVALUE)*NEO_C_STACK_SIZE);
    gLLVMStackHead = gLLVMStack;
    //declare_builtin_functions();
}

/*
void output_native_code(char* sname, bool optimize, char* throw_to_cflag)
{
    DBuilder->finalize();
    free(gLLVMStack);

#if LLVM_VERSION_MAJOR >= 7
    if(optimize) {
        puts("OPTIMIZATION PHASE");

        llvm::PassBuilder passBuilder;

        passBuilder.registerModuleAnalyses(moduleAnalysisManager);
        passBuilder.registerCGSCCAnalyses(cGSCCAnalysisManager);
        passBuilder.registerFunctionAnalyses(TheFAM);
        passBuilder.registerLoopAnalyses(loopAnalysisManager);

        passBuilder.buildModuleOptimizationPipeline(llvm::PassBuilder::OptimizationLevel::O3, false);
    }
#endif

    char sname2[PATH_MAX];
    xstrncpy(sname2, sname, PATH_MAX);

    char* p = sname2 + strlen(sname2);
    while(p >= sname2) {
        if(*p == '.') {
            *p = '\0';
            break;
        }
        else {
            p--;
        }
    }

    char module_name[PATH_MAX];
    xstrncpy(module_name, sname, PATH_MAX);

    char* module_name2 = basename(module_name);

    char module_name3[PATH_MAX];
    xstrncpy(module_name3, module_name2, PATH_MAX);

    p = module_name3 + strlen(module_name3);
    while(p >= module_name3) {
        if(*p == '.') {
            *p = '\0';
            break;
        }
        else {
            p--;
        }
    }

    {
#if LLVM_VERSION_MAJOR >= 7
    char path[PATH_MAX];
    snprintf(path, PATH_MAX, "%s.ll", sname2);

    (void)unlink(path);

    std::error_code ecode;
    llvm::raw_fd_ostream output_stream(path, ecode, llvm::sys::fs::F_None);

    std::string err_str;
    raw_string_ostream err_ostream(err_str);

//TheModule->print(llvm::errs(), nullptr);
    TheModule->print(output_stream, nullptr);
    output_stream.flush();
#elif LLVM_VERSION_MAJOR >= 4
    char path[PATH_MAX]; 
    snprintf(path, PATH_MAX, "%s.ll", sname2);

    (void)unlink(path);

    std::error_code ecode;
    llvm::raw_fd_ostream output_stream(path, ecode, llvm::sys::fs::F_None);

    std::string err_str;
    raw_string_ostream err_ostream(err_str);

    TheModule->print(output_stream, nullptr);
    output_stream.flush();
#else
    char path[PATH_MAX];
    snprintf(path, PATH_MAX, "%s.ll", sname2);

    (void)unlink(path);

    std::error_code ecode;
    llvm::raw_fd_ostream output_stream(path, ecode, llvm::sys::fs::F_None);

    std::string err_str;
    raw_string_ostream err_ostream(err_str);

    TheModule->print(output_stream, nullptr);
    output_stream.flush();

    verifyModule(*TheModule);
#endif
    }

#if LLVM_VERSION_MAJOR >= 7
    char path[PATH_MAX];
    snprintf(path, PATH_MAX, "%s.bc", sname2);

    (void)unlink(path);

    std::error_code ecode;
    llvm::raw_fd_ostream output_stream(path, ecode, llvm::sys::fs::F_None);

    std::string err_str;
    raw_string_ostream err_ostream(err_str);

    verifyModule(*TheModule);

    llvm::WriteBitcodeToFile(*TheModule, output_stream, true);
    output_stream.flush();
#elif LLVM_VERSION_MAJOR >= 4
    char path[PATH_MAX]; snprintf(path, PATH_MAX, "%s.bc", sname2);

    (void)unlink(path);

    std::error_code ecode;
    llvm::raw_fd_ostream output_stream(path, ecode, llvm::sys::fs::F_None);

    std::string err_str;
    raw_string_ostream err_ostream(err_str);

    verifyModule(*TheModule);

    llvm::WriteBitcodeToFile(TheModule, output_stream, true);
    output_stream.flush();
#else
    char path[PATH_MAX];
    snprintf(path, PATH_MAX, "%s.bc", sname2);

    (void)unlink(path);

    std::error_code ecode;
    llvm::raw_fd_ostream output_stream(path, ecode, llvm::sys::fs::F_None);

    std::string err_str;
    raw_string_ostream err_ostream(err_str);

    verifyModule(*TheModule);

    llvm::WriteBitcodeToFile(TheModule, output_stream, true);
    output_stream.flush();
#endif

    char command[PATH_MAX+256];

    snprintf(command, PATH_MAX+256, "%s.ll", sname2);
    int rc = chmod(command, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);

    if(rc != 0) {
        fprintf(stderr, "failed to compile(4) (%s) (%d)\n", command, rc);
        exit(2);
    }

    if(gNCDebug) {
        snprintf(command, PATH_MAX+128, "clang -g -c -o %s.o %s.ll %s", sname2, sname2, throw_to_cflag);
    }
    else {
        snprintf(command, PATH_MAX+128, "clang -c -o %s.o %s.ll %s", sname2, sname2, throw_to_cflag);
    }

    rc = system(command);

    if(rc != 0) {
        fprintf(stderr, "failed to compile(6) %d %s\n", rc, command);
        exit(2);
    }

    delete TheModule;
}
*/

void llvm_init()
{
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    start_to_make_native_code(gSName);
}

void llvm_final()
{
    //output_native_code(gSName, false, "");
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
        params[i].mType = clone_node_type(param->mType);
    }

    sNodeType* result_type = clone_node_type(gNodes[node].uValue.sFunction.mResultType);

    unsigned int node_block = gNodes[node].uValue.sFunction.mNodeBlock;

    Type* llvm_result_type;
    if(!create_llvm_type_from_node_type(&llvm_result_type, result_type, result_type, info))
    {
        return TRUE;
    }

    std::vector<Type *> llvm_param_types;

    for(i=0; i<num_params; i++) {
        sNodeType* param_type = params[i].mType;

        Type* llvm_param_type;
        if(!create_llvm_type_from_node_type(&llvm_param_type, param_type, param_type, info))
        {
            return TRUE;
        }
        llvm_param_types.push_back(llvm_param_type);
    }

    sFunction fun;

    xstrncpy(fun.mName, fun_name, VAR_NAME_MAX);

    FunctionType* function_type = FunctionType::get(llvm_result_type, llvm_param_types, false);
    Function* llvm_fun = Function::Create(function_type, Function::ExternalLinkage, fun_name, TheModule);
    fun.mLLVMFunction = llvm_fun;

    gFuncs[fun_name] = fun;

    xstrncpy(info->current_fun_name, fun_name, VAR_NAME_MAX);

    int n = 0;
    std::vector<Value *> llvm_params;
    for(auto &llvm_param : llvm_fun->args()) {
        sParserParam param = params[n];
        char* var_name = param.mName;

        llvm_params.push_back(&llvm_param);
        llvm_param.setName(var_name);
        
        n++;
    }

    BasicBlock* current_block_before;
    BasicBlock* current_block = BasicBlock::Create(TheContext, "entry", llvm_fun);
    llvm_change_block(current_block, &current_block_before, info, FALSE);

    info->andand_result_var = (void*)Builder.CreateAlloca(IntegerType::get(TheContext, 1), 0, "andand_result_var");
    info->oror_result_var = (void*)Builder.CreateAlloca(IntegerType::get(TheContext, 1), 0, "andand_result_var");

/*
    /// ready for params ///
    for(i=0; i<num_params; i++) {
        sParserParam param = params[i];
        char* var_name = param.mName;

        sVar* var = get_variable_from_table(node_block->mLVTable, (char*)var_name);

        sNodeType* var_type = var->mType;

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
        int index = get_variable_index(block_var_table, var_name, &parent);

        store_address_to_lvtable(index, address);
    }
*/
    int num_nodes = gNodes[node_block].uValue.sBlock.mNumNodes;
    unsigned int* nodes = gNodes[node_block].uValue.sBlock.mNodes;

    for(i=0; i<num_nodes; i++) {
        unsigned int node = nodes[i];
        if(!compile(node, info)) {
            return FALSE;
        }
    }

llvm_fun->print(llvm::errs(), nullptr);

    verifyFunction(*llvm_fun);

    // Run the optimizer on the function.
    TheFPM->run(*llvm_fun, TheFAM);

    info->type = create_node_type_with_class_name("void");

    if(info->no_output) {
        llvm_fun->eraseFromParent();
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

    info->type = right_type;

    return TRUE;
}

BOOL compile(unsigned int node, sCompileInfo* info)
{
show_node(node);
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
    }
    

    return TRUE;
}

