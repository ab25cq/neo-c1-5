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

    const char* cwd = getenv("PWD");

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
    TheFPM = std::make_unique<FunctionPassManager>(TheModule);
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
    start_to_make_native_code(gSName);

    Type* lvtable_type = get_lvtable_type();

    gLVTableValue = new GlobalVariable(*TheModule, lvtable_type, false, GlobalValue::InternalLinkage, 0, "gLVTable");
    gLVTableValue->setAlignment(8);

    ConstantAggregateZero* initializer = ConstantAggregateZero::get(lvtable_type);

    gLVTableValue->setInitializer(initializer);
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

BOOL compile_block(unsigned int node_block, sCompileInfo* info)
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

    if(!compile_block(node_block, info)) {
        return FALSE;
    }

llvm_fun->print(llvm::errs(), nullptr);

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
    }
    

    return TRUE;
}

