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
std::map<std::string, std::pair<Type*, sNodeType*>> gLLVMStructType;

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
    bool existance;
    char mID[VAR_NAME_MAX];
    char mName[VAR_NAME_MAX];
    char mBaseName[VAR_NAME_MAX];
    Function* mLLVMFunction;
    char mResultTypeName[VAR_NAME_MAX];
    int mNumParams;
    char mParamTypes[PARAMS_MAX][VAR_NAME_MAX];
    char mParamNames[PARAMS_MAX][VAR_NAME_MAX];
    BOOL mVarArg;
    BOOL mInline;
    BOOL mStatic;
    BOOL mCoroutine;
    BOOL mInherit;
    BOOL mExternal;
    unsigned int mNodeBlock;
    BOOL mGenerics;
    BOOL mMethodGenerics;
    int mVersion;
};

typedef sFunctionStruct sFunction;

std::map<std::string, std::vector<sFunction>> gFuncs;

///////////////////////////////////////////////////////////////////////
// type
///////////////////////////////////////////////////////////////////////
BOOL create_llvm_type_from_node_type(Type** result_type, sNodeType* node_type, sNodeType* generics_type, sCompileInfo* info);
BOOL get_size_from_node_type(uint64_t* result, sNodeType* node_type, sNodeType* generics_type, sCompileInfo* info);
void compile_err_msg(sCompileInfo* info, const char* msg, ...);

static BOOL is_generics_type(sNodeType* node_type)
{
    sCLClass* klass = node_type->mClass;

    if(klass->mFlags & CLASS_FLAGS_GENERICS)
    {
        return TRUE;
    }
    else {
        int i;
        for(i=0; i<node_type->mNumGenericsTypes; i++)
        {
            sNodeType* node_type2 = node_type->mGenericsTypes[i];

            if(is_generics_type(node_type2))
            {
                return TRUE;
            }
        }
    }

    return FALSE;
}

static void create_real_struct_name(char* real_struct_name, int size_real_struct_name, int num_generics, sNodeType* generics_types[GENERICS_TYPES_MAX])
{
    if(num_generics > 0) {
        xstrncat(real_struct_name, "_", size_real_struct_name);
    }

    int i;
    for(i=0; i<num_generics; i++) {
        sNodeType* node_type = generics_types[i];

        xstrncat(real_struct_name, node_type->mClass->mName, size_real_struct_name);

        int j;
        for(j=0; j<node_type->mPointerNum; j++)
        {
            xstrncat(real_struct_name, "p", size_real_struct_name);
        }

        create_real_struct_name(real_struct_name, size_real_struct_name, node_type->mNumGenericsTypes, node_type->mGenericsTypes);

        if(i != num_generics-1) {
            xstrncat(real_struct_name, "_", size_real_struct_name);
        }
    }
}

static BOOL create_llvm_union_type(sNodeType* node_type, sNodeType* generics_type, sCompileInfo* info)
{
    sCLClass* klass = node_type->mClass;

    char* class_name = klass->mName;

    char real_struct_name[REAL_STRUCT_NAME_MAX];
    int size_real_struct_name = REAL_STRUCT_NAME_MAX;
    xstrncpy(real_struct_name, class_name, size_real_struct_name);

    create_real_struct_name(real_struct_name, size_real_struct_name, node_type->mNumGenericsTypes, node_type->mGenericsTypes);

    if(gLLVMStructType[real_struct_name].first == nullptr) 
    {
        StructType* struct_type = StructType::create(TheContext, real_struct_name);
        std::vector<Type*> fields;

        uint64_t max_size = 0;
        Type* max_size_field = NULL;

        int i;
        for(i=0; i<klass->mNumFields; i++) {
            sNodeType* field = clone_node_type(klass->mFields[i]);

            sNodeType* generics_type2 = generics_type;

            BOOL success_solve;
            (void)solve_generics(&field, field, &success_solve);

            if(success_solve)
            {
                generics_type2 = field;
            }

            if(!success_solve) {
                BOOL success_solve;
                (void)solve_generics(&field, generics_type, &success_solve);

                if(success_solve)
                {
                    generics_type2 = generics_type;
                }
            }


            Type* field_type;
            if(!create_llvm_type_from_node_type(&field_type, field, generics_type2, info))
            {
                return FALSE;
            }

            uint64_t alloc_size = 0;
            if(!get_size_from_node_type(&alloc_size, field, generics_type2, info))
            {
                return FALSE;
            }

            if(alloc_size > max_size) {
                max_size = alloc_size;

                max_size_field = field_type;
            }
        }

        if(max_size_field) {
            fields.push_back(max_size_field);
        }

        if(struct_type->isOpaque()) {
            struct_type->setBody(fields, false);
        }

        std::pair<Type*, sNodeType*> pair_value;
        pair_value.first = struct_type;
        pair_value.second = clone_node_type(node_type);
        pair_value.second->mNumFields = node_type->mClass->mNumFields;

        gLLVMStructType[real_struct_name] = pair_value;
    }
    else if(klass->mUndefinedStructType) {
        StructType* struct_type = (StructType*)klass->mUndefinedStructType;
        std::vector<Type*> fields;

        uint64_t max_size = 0;
        Type* max_size_field = NULL;

        int i;
        for(i=0; i<klass->mNumFields; i++) {
            sNodeType* field = clone_node_type(klass->mFields[i]);

            sNodeType* generics_type2 = generics_type;

            BOOL success_solve;
            (void)solve_generics(&field, field, &success_solve);

            if(success_solve)
            {
                generics_type2 = field;
            }

            if(!success_solve) {
                BOOL success_solve;
                (void)solve_generics(&field, generics_type, &success_solve);

                if(success_solve)
                {
                    generics_type2 = generics_type;
                }
            }

            Type* field_type;
            if(!create_llvm_type_from_node_type(&field_type, field, generics_type2, info))
            {
                return FALSE;
            }

            uint64_t alloc_size = 0;
            if(!get_size_from_node_type(&alloc_size, field, generics_type2, info))
            {
                return FALSE;
            }

            if(alloc_size > max_size) {
                max_size = alloc_size;

                max_size_field = field_type;
            }
        }

        if(max_size_field) {
            fields.push_back(max_size_field);
        }

        if(struct_type->isOpaque()) {
            struct_type->setBody(fields, false);
        }

        klass->mUndefinedStructType = NULL;
    }

    return TRUE;
}

static BOOL solve_undefined_strcut_type(sNodeType* node_type, sNodeType* generics_type, char* real_struct_name, sCompileInfo* info)
{
    sCLClass* klass = node_type->mClass;

    if(klass->mUndefinedStructType) {
        StructType* struct_type = (StructType*)klass->mUndefinedStructType;
        std::vector<Type*> fields;

        int i;
        for(i=0; i<klass->mNumFields; i++) {
            sNodeType* field = clone_node_type(klass->mFields[i]);

            sNodeType* generics_type2 = generics_type;

            if(!is_generics_type(field) && field->mNumGenericsTypes > 0)
            {
                generics_type2 = clone_node_type(field);
            }
            else {
                BOOL success_solve;
                (void)solve_generics(&field, field, &success_solve);

                if(!solve_generics(&field, generics_type, &success_solve))
                {
                    return FALSE;
                }
            }

            if(field->mClass == klass && field->mPointerNum == 0)
            {
                return FALSE;
            }

            Type* field_type;
            if(!create_llvm_type_from_node_type(&field_type, field, generics_type2, info))
            {
                compile_err_msg(info, "Getting llvm type failed(1002)");
                show_node_type(field);
                show_node_type(generics_type2);
                return FALSE;
            }

            fields.push_back(field_type);
        }

        if(struct_type->isOpaque()) {
            struct_type->setBody(fields, false);
        }

        klass->mUndefinedStructType = NULL;

        std::pair<Type*, sNodeType*> pair_value;
        pair_value.first = struct_type;
        pair_value.second = clone_node_type(node_type);
        pair_value.second->mNumFields = node_type->mClass->mNumFields;

        gLLVMStructType[real_struct_name] = pair_value;
    }

    return TRUE;
}

static BOOL create_llvm_struct_type(sNodeType* node_type, sNodeType* generics_type, BOOL new_create, sCompileInfo* info)
{
    int i;
    for(i=0; i<generics_type->mNumGenericsTypes; i++)
    {
        sNodeType* node_type2 = generics_type->mGenericsTypes[i];

        sCLClass* klass = node_type2->mClass;
        if(klass->mFlags & CLASS_FLAGS_STRUCT)
        {
            if(!create_llvm_struct_type(node_type2, node_type2, new_create, info))
            {
                return FALSE;
            }
        }
    }

    sCLClass* klass = node_type->mClass;

    char* class_name = klass->mName;

    char real_struct_name[REAL_STRUCT_NAME_MAX];
    int size_real_struct_name = REAL_STRUCT_NAME_MAX;
    xstrncpy(real_struct_name, class_name, size_real_struct_name);

    create_real_struct_name(real_struct_name, size_real_struct_name, node_type->mNumGenericsTypes, node_type->mGenericsTypes);

    if(klass->mUndefinedStructType)
    {
        if(!solve_undefined_strcut_type(node_type, generics_type, real_struct_name, info))
        {
            return FALSE;
        }
    }
    else if(gLLVMStructType[real_struct_name].first == nullptr)
    {
        if(TheModule->getTypeByName(real_struct_name) == nullptr)
        {
            StructType* struct_type = StructType::create(TheContext, real_struct_name);
            std::vector<Type*> fields;

            std::pair<Type*, sNodeType*> pair_value;
            pair_value.first = struct_type;
            pair_value.second = clone_node_type(node_type);
            pair_value.second->mNumFields = node_type->mClass->mNumFields;

            gLLVMStructType[real_struct_name] = pair_value;

            int i;
            for(i=0; i<klass->mNumFields; i++) {
                sNodeType* field = clone_node_type(klass->mFields[i]);


                sNodeType* generics_type2 = generics_type;

                if(!is_generics_type(field) && field->mNumGenericsTypes > 0)
                {
                    generics_type2 = clone_node_type(field);
                }
                else {
                    BOOL success_solve;
                    (void)solve_generics(&field, generics_type, &success_solve);
                }

                if(field->mClass == klass && field->mPointerNum == 0)
                {
                    return FALSE;
                }
                Type* field_type;

                if(!create_llvm_type_from_node_type(&field_type, field, generics_type2, info))
                {
                    compile_err_msg(info, "Getting llvm type failed(1001)");
                    show_node_type(field);
                    show_node_type(generics_type2);
                    return FALSE;
                }

                fields.push_back(field_type);
            }

            if(struct_type->isOpaque()) 
            {
                struct_type->setBody(fields, false);
            }
        }
    }

    return TRUE;
}

BOOL create_llvm_type_from_node_type(Type** result_type, sNodeType* node_type, sNodeType* generics_type, sCompileInfo* info)
{
    sCLClass* klass = node_type->mClass;

    if(klass->mFlags & CLASS_FLAGS_STRUCT) 
    {
        sCLClass* klass = node_type->mClass;

        char* class_name = klass->mName;

        char real_struct_name[REAL_STRUCT_NAME_MAX];
        int size_real_struct_name = REAL_STRUCT_NAME_MAX;
        xstrncpy(real_struct_name, class_name, size_real_struct_name);

        create_real_struct_name(real_struct_name, size_real_struct_name, node_type->mNumGenericsTypes, node_type->mGenericsTypes);

        sNodeType* struct_node_type = NULL;
        if(gLLVMStructType[real_struct_name].first != nullptr)
        {
            struct_node_type = gLLVMStructType[real_struct_name].second;
        }

        if(struct_node_type == nullptr)
        {
            if(!create_llvm_struct_type(node_type, generics_type, TRUE, info))
            {
                return FALSE;
            }
        }

        *result_type = gLLVMStructType[real_struct_name].first;
    }
    else if(klass->mFlags & CLASS_FLAGS_UNION) 
    {
        if(klass->mUndefinedStructType && node_type->mPointerNum == 0)
        {
            return FALSE;
        }

        sCLClass* klass = node_type->mClass;

        char* class_name = klass->mName;

        char real_struct_name[REAL_STRUCT_NAME_MAX];
        int size_real_struct_name = REAL_STRUCT_NAME_MAX;
        xstrncpy(real_struct_name, class_name, size_real_struct_name);

        create_real_struct_name(real_struct_name, size_real_struct_name, node_type->mNumGenericsTypes, node_type->mGenericsTypes);

        if(gLLVMStructType[real_struct_name].first == nullptr) 
        {
            if(!create_llvm_union_type(node_type, generics_type, info))
            {
                return FALSE;
            }
        }

        *result_type = gLLVMStructType[real_struct_name].first;
    }
    else if(klass->mFlags & CLASS_FLAGS_ENUM) 
    {
        *result_type = IntegerType::get(TheContext, 32);
    }
    else if((klass->mFlags & CLASS_FLAGS_GENERICS) || (klass->mFlags & CLASS_FLAGS_METHOD_GENERICS))
    {
        if(info && info->no_output) {
            *result_type = IntegerType::get(TheContext, 64);
        }
        else {
            return FALSE;
        }
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
    else if(type_identify_with_class_name(node_type, "lambda"))
    {
        int num_params = node_type->mNumParams;
        sNodeType* fun_result_type = node_type->mResultType;

        Type* llvm_result_type;
        if(!create_llvm_type_from_node_type(&llvm_result_type, fun_result_type, generics_type, info))
        {
            return FALSE;
        }

        std::vector<Type *> llvm_param_types;

        int i;
        for(i=0; i<num_params; i++) {
            sNodeType* param_type = node_type->mParamTypes[i];

            Type* llvm_param_type;
            if(!create_llvm_type_from_node_type(&llvm_param_type, param_type, generics_type, info))
            {
                return FALSE;
            }

            llvm_param_types.push_back(llvm_param_type);
        }
    
        *result_type = FunctionType::get(llvm_result_type, llvm_param_types, false);

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

///////////////////////////////////////////////////////////////////////
// function
///////////////////////////////////////////////////////////////////////
BOOL function_existance(char* fun_name)
{
    std::vector<sFunction> fun = gFuncs[fun_name];
    return fun.size() != 0;
}

static BOOL entry_llvm_function(sFunction* fun, sNodeType* generics_type, sCompileInfo* info)
{
    char result_type_name[VAR_NAME_MAX];

    char fun_name[VAR_NAME_MAX];
    xstrncpy(fun_name, fun->mName, VAR_NAME_MAX);

    xstrncpy(result_type_name, fun->mResultTypeName, VAR_NAME_MAX);

    BOOL var_arg = fun->mVarArg;
    BOOL inline_ = fun->mInline;
    BOOL inherit_ = fun->mInherit;
    BOOL static_ = fun->mStatic;
    int num_params = fun->mNumParams;
    unsigned int node_block = fun->mNodeBlock;
    BOOL generics = fun->mGenerics;
    BOOL method_generics = fun->mGenerics;
    BOOL coroutine = fun->mCoroutine;
    BOOL version = fun->mVersion;

    if(version > 0) {
        char version_str[128];
        snprintf(version_str, 128, "_%d", version);

        xstrncat(fun_name, version_str, VAR_NAME_MAX);
    }

/*
    Function* llvm_entried_fun = TheModule->getFunction(fun_name);

    if(llvm_entried_fun) {
        fun->mLLVMFunction = llvm_entried_fun;
        return TRUE;
    }
*/

    char param_types[PARAMS_MAX][VAR_NAME_MAX];
    char param_names[PARAMS_MAX][VAR_NAME_MAX];

    int i;
    for(i=0; i<num_params; i++) {
        xstrncpy(param_types[i], fun->mParamTypes[i], VAR_NAME_MAX);
        xstrncpy(param_names[i], fun->mParamNames[i], VAR_NAME_MAX);
    }

    sNodeType* result_type = create_node_type_with_class_name(result_type_name);

    if(result_type == NULL || result_type->mClass == NULL) {
        return FALSE;
    }

    BOOL success_solve;
    (void)solve_generics(&result_type, generics_type, &success_solve);

    Type* llvm_result_type;
    if(!create_llvm_type_from_node_type(&llvm_result_type, result_type, result_type, info))
    {
        return TRUE;
    }

    std::vector<Type *> llvm_param_types;

    for(i=0; i<num_params; i++) {
        sNodeType* param_type = create_node_type_with_class_name(param_types[i]);

        if(param_type == NULL || param_type->mClass == NULL) {
            return FALSE;
        }

        BOOL success_solve;
        (void)solve_generics(&param_type, generics_type, &success_solve);

        Type* llvm_param_type;
        if(!create_llvm_type_from_node_type(&llvm_param_type, param_type, param_type, info))
        {
            return FALSE;
        }

        llvm_param_types.push_back(llvm_param_type);
    }

    if(inline_ || static_) {
        FunctionType* function_type = FunctionType::get(llvm_result_type, llvm_param_types, var_arg);
        Function* llvm_fun = Function::Create(function_type, Function::InternalLinkage, fun_name, TheModule);
        fun->mLLVMFunction = llvm_fun;
    }
    else {
        FunctionType* function_type = FunctionType::get(llvm_result_type, llvm_param_types, var_arg);
        Function* llvm_fun = Function::Create(function_type, Function::ExternalLinkage, fun_name, TheModule);
        fun->mLLVMFunction = llvm_fun;
    }

    return TRUE;
}

void get_version(sFunction* fun, char* fun_name)
{
    int external_version = 0;
    int fun_version = 0;
    for(int i=0; i<gFuncs[fun_name].size(); i++) {
        sFunction fun = gFuncs[fun_name][i];
        if(fun.mExternal) {
            external_version++;
        }
        else {
            fun_version++;
        }
    }

    if(fun->mExternal) {
        fun->mVersion = external_version;
    }
    else {
        fun->mVersion = fun_version;
    }
}


BOOL add_function(char* fun_name, char* fun_base_name, char* result_type_name, int num_params, char** param_types, char** param_names, BOOL var_arg, BOOL inline_, BOOL inherit_, BOOL static_, unsigned int node_block, BOOL generics, BOOL coroutine, BOOL method_generics, sCompileInfo* info)
{
    sFunction fun;

    fun.existance = true;

    xstrncpy(fun.mName, fun_name, VAR_NAME_MAX);
    xstrncpy(fun.mBaseName, fun_base_name, VAR_NAME_MAX);

    xstrncpy(fun.mResultTypeName, result_type_name, VAR_NAME_MAX);
    fun.mVarArg = var_arg;
    fun.mInline = inline_;
    fun.mStatic = static_;
    fun.mNumParams = num_params;
    fun.mNodeBlock = node_block;
    fun.mGenerics = generics;
    fun.mMethodGenerics = method_generics;
    fun.mCoroutine = coroutine;
    fun.mInherit = inherit_;
    fun.mVersion = 0;

    int i;
    for(i=0; i<num_params; i++) {
        xstrncpy(fun.mParamTypes[i], param_types[i], VAR_NAME_MAX);
        xstrncpy(fun.mParamNames[i], param_names[i], VAR_NAME_MAX);
    }

    if(!generics && !method_generics) {
        if(inherit_) {
            if(gFuncs[fun_name].size() == 0) {
                compile_err_msg(info, "invalid inherit %s\n", fun_name);
                return FALSE;
            }
            else {
                get_version(&fun, fun_name);
            }

            if(!entry_llvm_function(&fun, NULL, info)) {
                return FALSE;
            }

            gFuncs[fun_name].push_back(fun);
        }
        else {
            if(!entry_llvm_function(&fun, NULL, info)) {
                return FALSE;
            }

            if(gFuncs[fun_name].size() == 0) {
                gFuncs[fun_name].push_back(fun);
            }
        }
    }
    else {
        if(inherit_) {
            if(gFuncs[fun_name].size() == 0) {
                compile_err_msg(info, "invalid inherit %s\n", fun_name);
                return FALSE;
            }
            else {
                get_version(&fun, fun_name);

                gFuncs[fun_name].push_back(fun);
            }
        }
        else {
            if(gFuncs[fun_name].size() == 0) {
                gFuncs[fun_name].push_back(fun);
            }
        }
    }

    return TRUE;
}

void push_value_to_stack_ptr(LVALUE* value, sCompileInfo* info);
void append_heap_object_to_right_value(LVALUE* llvm_value, sCompileInfo* info);

BOOL call_function(const char* fun_name, Value** params, int num_params, const char* struct_name, BOOL no_err_output, sNodeType* generics_type, sCompileInfo* info)
{
    char real_fun_name[VAR_NAME_MAX];

    if(strcmp(struct_name, "") == 0) {
        snprintf(real_fun_name, VAR_NAME_MAX, "%s", fun_name);
    }
    else {
        snprintf(real_fun_name, VAR_NAME_MAX, "%s_%s", struct_name, fun_name);
    }

    sFunction fun;
    if(gFuncs[real_fun_name].size() == 0) {
        //compile_err_msg(info, "Function not found(%s)\n", real_fun_name);
        //info->err_num++;
        return TRUE;
    }
    else {
        fun = gFuncs[real_fun_name][gFuncs[real_fun_name].size()-1];
    }

    sNodeType* param_types[PARAMS_MAX];
    memset(param_types, 0, sizeof(sNodeType*)*PARAMS_MAX);

    Function* llvm_fun = fun.mLLVMFunction;

    if(llvm_fun == nullptr) {
        dec_stack_ptr(num_params, info);
        return FALSE;
    }

    std::vector<Value*> llvm_params;

    int i;
    for(i=0; i<num_params; i++) {
        Value* param = params[i];
        llvm_params.push_back(param);
    }
    dec_stack_ptr(num_params, info);

    sNodeType* result_type = create_node_type_with_class_name(fun.mResultTypeName);

    if(result_type == NULL || result_type->mClass == NULL) {
        dec_stack_ptr(num_params, info);
        return FALSE;
    }

    if(type_identify_with_class_name(result_type, "void"))
    {
        Builder.CreateCall(llvm_fun, llvm_params);

        info->type = clone_node_type(result_type);
    }
    else {
        LVALUE llvm_value;
        llvm_value.value = Builder.CreateCall(llvm_fun, llvm_params);
        llvm_value.type = clone_node_type(result_type);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(result_type);

        if(llvm_value.type->mHeap && !llvm_value.binded_value &&& llvm_value.var) 
        {
            append_heap_object_to_right_value(&llvm_value, info);
        }
    }

    return TRUE;
}

///////////////////////////////////////////////////////////////////////
// heap
///////////////////////////////////////////////////////////////////////
void* new_right_value_objects_container(sCompileInfo* info)
{
    void* result = (void*)info->right_value_objects;
    info->right_value_objects = (void*)new std::map<Value*, std::pair<sNodeType*, int>>;

    return result;
}

void restore_right_value_objects_container(void* right_value_objects, sCompileInfo* info)
{
    info->right_value_objects = right_value_objects;
}

/*
int create_generics_finalize_method(sNodeType* node_type2, Function** llvm_fun, sCompileInfo* info)
{
    int generics_fun_num = gGenericsFunNum++;

    char struct_name[VAR_NAME_MAX+128];
    if(strcmp(node_type2->mTypeName, "") == 0)
    {
        xstrncpy(struct_name, node_type2->mClass->mName, VAR_NAME_MAX+128);
    }
    else {
        xstrncpy(struct_name, node_type2->mTypeName, VAR_NAME_MAX+128);
    }

    char real_fun_name[REAL_FUN_NAME_MAX];
    create_real_fun_name(real_fun_name, REAL_FUN_NAME_MAX, "finalize", struct_name);

    std::vector<sFunction*>& funcs = gFuncs[real_fun_name];

    if(funcs.size() == 0) {
        return -1;
    }

    sFunction* fun = funcs[funcs.size()-1];

    if(fun->mResultType != nullptr) {
        LVALUE saved_llvm_stack[NEO_C_STACK_SIZE];

        memcpy(saved_llvm_stack, gLLVMStackHead, sizeof(LVALUE)*NEO_C_STACK_SIZE);

        int stack_num_before = info->stack_num;

        /// get function ///
        int num_method_generics_types = 0;
        sNodeType* method_generics_types[GENERICS_TYPES_MAX];
        memset(method_generics_types, 0, sizeof(sNodeType*)*GENERICS_TYPES_MAX);

        sNodeType* generics_type = clone_node_type(node_type2);

        LVALUE* llvm_stack = gLLVMStack;
        int stack_num = info->stack_num;

        char* buf = fun->mBlockText;

        char sname[PATH_MAX];
        xstrncpy(sname, fun->mSName, PATH_MAX);

        int sline = fun->mSLine;

        BOOL in_clang = fun->mInCLang;
        BOOL var_arg = fun->mVarArg;

        char* generics_type_names[GENERICS_TYPES_MAX];

        int j;
        for(j=0; j<fun->mNumGenerics; j++) {
            generics_type_names[j] = fun->mGenericsTypeNames[j];
        }

        char* method_generics_type_names[GENERICS_TYPES_MAX];

        for(j=0; j<fun->mNumMethodGenerics; j++) {
            method_generics_type_names[j] = fun->mMethodGenericsTypeNames[j];
        }

        unsigned int node = 0;
        if(!parse_generics_fun(&node, buf, fun, sname, sline, struct_name, generics_type, num_method_generics_types, method_generics_types, fun->mNumGenerics, generics_type_names, fun->mNumMethodGenerics, method_generics_type_names, info->pinfo, info, generics_fun_num, in_clang, fun->mVersion, var_arg, TRUE))
        {
            gLLVMStack = llvm_stack;
            info->stack_num = stack_num;
            return -1;
        }

        gNodes[node].mLine = info->pinfo->sline;
        xstrncpy(gNodes[node].mSName, info->pinfo->sname, PATH_MAX);

        if(!compile(node, info)) {
            gLLVMStack = llvm_stack;
            info->stack_num = stack_num;
            return -1;
        }

        LVALUE* fun_value = get_value_from_stack(-1);

        *llvm_fun = (Function*)fun_value->value;

        info->stack_num = stack_num;
        gLLVMStack = llvm_stack;

        memcpy(gLLVMStackHead, saved_llvm_stack, sizeof(LVALUE)*NEO_C_STACK_SIZE);
        info->stack_num = stack_num_before;
        gLLVMStack = gLLVMStackHead + info->stack_num;
    }
    

    return generics_fun_num;
}
*/



static BOOL call_destructor(Value* obj, sNodeType* node_type, sCompileInfo* info)
{
    LVALUE* llvm_stack = gLLVMStack;
    int stack_num_before = info->stack_num;
    sNodeType* info_type_before = info->type;

/*
    if(node_type->mNumGenericsTypes > 0) 
    {
        Function* llvm_fun;

        int finalize_generics_fun_num = create_generics_finalize_method(node_type, &llvm_fun, info);

        if(finalize_generics_fun_num != -1)
        {
            std::vector<Value*> llvm_params;

            llvm_params.push_back(obj);

            Builder.CreateCall(llvm_fun, llvm_params);

            info->stack_num = stack_num_before;
            gLLVMStack = llvm_stack;
            info->type = info_type_before;

            return TRUE;
        }
    }
    else {
*/
        Value* params[PARAMS_MAX];

        params[0] = obj;

        LVALUE llvm_value;
        llvm_value.value = obj;
        llvm_value.type = clone_node_type(node_type);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        push_value_to_stack_ptr(&llvm_value, info);

        int num_params = 1;

        char* struct_name = node_type->mClass->mName;

        if(call_function("finalize", params, num_params, struct_name, TRUE, NULL, info))
        {
            info->stack_num = stack_num_before;
            gLLVMStack = llvm_stack;
            info->type = info_type_before;
            return TRUE;
        }
        else {
            char method_name[BUFSIZ];
            snprintf(method_name, BUFSIZ, "finalize_%s", info->sname);

            if(call_function(method_name, params, num_params, struct_name, TRUE, NULL, info))
            {
                info->stack_num = stack_num_before;
                gLLVMStack = llvm_stack;
                info->type = info_type_before;
                return TRUE;
            }
        }
//    }

    info->stack_num = stack_num_before;
    gLLVMStack = llvm_stack;
    info->type = info_type_before;

    return FALSE;
}

void free_object(sNodeType* node_type, void* address, BOOL force_delete, sCompileInfo* info);

static void call_field_destructor(Value* obj, sNodeType* node_type, sCompileInfo* info)
{
    Value* obj2 = Builder.CreateCast(Instruction::PtrToInt, obj, IntegerType::get(TheContext, 64));
    Value* cmp_right_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);
    Value* conditional = Builder.CreateICmpNE(obj2, cmp_right_value);

    sFunction* fun = (sFunction*)info->function;

    Function* llvm_function = fun->mLLVMFunction;

    BasicBlock* cond_then_block = BasicBlock::Create(TheContext, "cond_then_block", llvm_function);
    BasicBlock* cond_end_block = BasicBlock::Create(TheContext, "cond_end", llvm_function);

    Builder.CreateCondBr(conditional, cond_then_block, cond_end_block);

    Builder.SetInsertPoint(cond_then_block);
    info->current_block = cond_then_block;

    sCLClass* klass = node_type->mClass;

    sNodeType* node_type2 = clone_node_type(node_type);
    node_type2->mPointerNum = 0;

    Type* llvm_struct_type;
    if(!create_llvm_type_from_node_type(&llvm_struct_type, node_type2, node_type2, info))
    {
        fprintf(stderr, "%s %d: The error at create_llvm_type_from_node_type\n", info->sname, info->sline);
        return;
    }

    int i;
    for(i=0; i<klass->mNumFields; i++) {
        sNodeType* field_type = clone_node_type(klass->mFields[i]);

        BOOL success_solve;
        if(!solve_generics(&field_type, node_type, &success_solve))
        {
            fprintf(stderr, "%s %d: The error at solve_generics\n", info->sname, info->sline);
            return;
        }
        sCLClass* field_class = field_type->mClass;

        if(field_type->mHeap && field_type->mPointerNum > 0)
        {
            if(type_identify(node_type, field_type)) {
/*
#if LLVM_VERSION_MAJOR >= 7
                Value* field_address = Builder.CreateStructGEP(obj, i);
#else
                Value* field_address = Builder.CreateStructGEP(llvm_struct_type, obj, i);
#endif
                Value* obj2 = Builder.CreateAlignedLoad(field_address, 8);

                if(!call_destructor(obj2, field_type, info)) {
                    fprintf(stderr, "%s %d: can't make finalize of recursive field(3)(%s)\n", info->sname, info->sline, field_type->mClass->mName);
                    exit(2);
                }
*/
            }
            else {
                Type* llvm_field_type;
                if(!create_llvm_type_from_node_type(&llvm_field_type, field_type, field_type, info))
                {
                    fprintf(stderr, "%s %d: The error at create_llvm_type_from_node_type\n", info->sname, info->sline);
                    return;
                }

#if LLVM_VERSION_MAJOR >= 7
                Value* field_address = Builder.CreateStructGEP(obj, i);
#else
                Value* field_address = Builder.CreateStructGEP(llvm_struct_type, obj, i);
#endif
                free_object(field_type, field_address, FALSE, info);
            }
        }
    }

    Builder.CreateBr(cond_end_block);

    Builder.SetInsertPoint(cond_end_block);
    info->current_block = cond_end_block;;
}

static void free_right_value_object(sNodeType* node_type, void* obj, BOOL force_delete, sCompileInfo* info)
{
    BOOL exist_recursive_field = FALSE;

    Value* obj2 = (Value*)obj;

    sCLClass* klass = node_type->mClass;

    sNodeType* node_type2 = clone_node_type(node_type);
    node_type2->mPointerNum = 0;

    Type* llvm_struct_type;
    if(!create_llvm_type_from_node_type(&llvm_struct_type, node_type2, node_type2, info))
    {
        fprintf(stderr, "%s %d: The error at create_llvm_type_from_node_type\n", info->sname, info->sline);
        return;
    }

    int i;
    for(i=0; i<klass->mNumFields; i++) {
        sNodeType* field_type = clone_node_type(klass->mFields[i]);

        BOOL success_solve;
        if(!solve_generics(&field_type, node_type, &success_solve))
        {
            fprintf(stderr, "%s %d: The error at solve_generics\n", info->sname, info->sline);
            return;
        }
        sCLClass* field_class = field_type->mClass;

        if(field_type->mHeap && field_type->mPointerNum > 0)
        {
            if(type_identify(node_type, field_type))
            {
                BOOL exist_finalize_method = FALSE;
/*
                if(node_type->mNumGenericsTypes > 0) 
                {
                    Function* llvm_fun;
                    int finalize_generics_fun_num = create_generics_finalize_method(node_type, &llvm_fun, info);

                    if(finalize_generics_fun_num != -1)
                    {
                        exist_finalize_method = TRUE;
                    }
                }
                else {
                    char fun_name[BUFSIZ];
                    snprintf(fun_name, BUFSIZ, "finalize_%s", info->sname);

                    char real_fun_name[VAR_NAME_MAX];
                    snprintf(real_fun_name, VAR_NAME_MAX, "%s_%s", klass->mName, fun_name);

                    sFunction fun = gFuncs[real_fun_name];
//                }

*/
/*
                if(!exist_finalize_method) {
                    LVALUE* llvm_stack = gLLVMStack;
                    int stack_num = info->stack_num;

                    if(!make_finalize_for_recursive_field_type(node_type, info)) {
                        fprintf(stderr, "%s %d: can't make finalize of recursive field(2)(%s)\n", info->sname, info->sline, node_type->mClass->mName);
                        exit(2);
                    }
                    
                    gLLVMStack = llvm_stack;
                    info->stack_num = stack_num;
                }
*/

                exist_recursive_field = TRUE;
            }
        }
    }

    if((force_delete || node_type->mHeap ) && node_type->mPointerNum > 0) 
    {
        if(node_type->mPointerNum == 1 && !info->no_output)
        {
            if(exist_recursive_field) {
                //call_field_destructor(obj2, node_type, info);
                if(!call_destructor(obj2, node_type, info)) {
                    fprintf(stderr, "%s %d: can't make finalize of recursive field(3)(%s)\n", info->sname, info->sline, node_type->mClass->mName);
                    exit(2);
                }
            }
            else {
                call_destructor(obj2, node_type, info);
                call_field_destructor(obj2, node_type, info);
            }
        }
    }

    /// free ///
    if((force_delete || node_type->mHeap ) && node_type->mPointerNum > 0 && !info->no_output) 
    {
        Function* fun = TheModule->getFunction("free");

        if(fun == nullptr) {
            fprintf(stderr, "require free\n");
            exit(2);
        }

        std::vector<Value*> params2;
        Value* param = Builder.CreateCast(Instruction::BitCast, obj2, PointerType::get(IntegerType::get(TheContext, 8), 0));

        params2.push_back(param);
        Builder.CreateCall(fun, params2);
    }

    std::map<Value*, std::pair<sNodeType*, int>>* right_value_objects = (std::map<Value*, std::pair<sNodeType*, int>>*)info->right_value_objects;
    right_value_objects->erase(obj2);
}

void free_object(sNodeType* node_type, void* address, BOOL force_delete, sCompileInfo* info)
{
    Value* obj = Builder.CreateAlignedLoad((Value*)address, 8);
    free_right_value_object(node_type, obj, force_delete, info);
}

void std_move(Value* var_address, sNodeType* lvar_type, LVALUE* rvalue, BOOL alloc, sCompileInfo* info)
{
    sVar* rvar = rvalue->var;
    sNodeType* rvalue_type = rvalue->type;
    if(lvar_type->mHeap && rvalue_type->mHeap) {
        if(lvar_type->mHeap && var_address && !alloc && lvar_type->mPointerNum > 0) {
            free_object(lvar_type, var_address, FALSE, info);
        }

        if(rvar) {
            rvar->mLLVMValue = NULL;
        }
    }

    if(lvar_type->mHeap)
    {
        std::map<Value*, std::pair<sNodeType*, int>>* right_value_objects = (std::map<Value*, std::pair<sNodeType*, int>>*)info->right_value_objects;
        if(right_value_objects->count(rvalue->value) > 0)
        {
            right_value_objects->erase(rvalue->value);
        }
    }
}

void free_right_value_objects(sCompileInfo* info)
{
    std::map<Value*, std::pair<sNodeType*, int>>* right_value_objects = (std::map<Value*, std::pair<sNodeType*, int>>*)info->right_value_objects;

    std::map<Value*, std::pair<sNodeType*, int>> old_heap_objects(*right_value_objects);

    right_value_objects->clear();

    for(std::pair<Value*, std::pair<sNodeType*, int>> it: old_heap_objects) 
    {
        Value* address = it.first;

        sNodeType* node_type = it.second.first; 
        int flag = it.second.second;

        if(flag <= 0) {
            free_right_value_object(node_type, address, FALSE, info);
        }
        else {
            flag--;

            std::pair<sNodeType*, int> pair_value;
            pair_value.first = clone_node_type(node_type);
            pair_value.second = flag;

            (*right_value_objects)[address] = pair_value;
        }
    }
}

void remove_from_right_value_object(Value* value, sCompileInfo* info)
{
    std::map<Value*, std::pair<sNodeType*, int>>* right_value_objects = (std::map<Value*, std::pair<sNodeType*, int>>*)info->right_value_objects;
    if(right_value_objects->count(value) > 0)
    {
        right_value_objects->erase(value);
    }
}

void append_heap_object_to_right_value(LVALUE* llvm_value, sCompileInfo* info)
{
    if(llvm_value->type->mHeap) {
        std::map<Value*, std::pair<sNodeType*, int>>* right_value_objects = (std::map<Value*, std::pair<sNodeType*, int>>*)info->right_value_objects;

        if(right_value_objects->count(llvm_value->value) == 0)
        {
            int flg = (*right_value_objects)[llvm_value->value].second;

            flg = 1;

            std::pair<sNodeType*, int> pair_value;
            pair_value.first = clone_node_type(llvm_value->type);
            pair_value.second = 0;

            (*right_value_objects)[llvm_value->value] = pair_value;
        }
    }
}

void free_objects(sVarTable* table, Value* inhibit_free_object_address, sCompileInfo* info)
{
    sVar* p = table->mLocalVariables;

    while(1) {
        if(p->mName[0] != 0) {
            sNodeType* node_type = p->mType;
            sCLClass* klass = node_type->mClass;

            if(node_type->mHeap)
            {
                if(p->mLLVMValue && p->mLLVMValue != inhibit_free_object_address)
                {
                    free_object(p->mType, p->mLLVMValue, FALSE, info);
                    p->mLLVMValue = NULL;
                }
            }
        }

        p++;

        if(p == table->mLocalVariables + LOCAL_VARIABLE_MAX) {
            break;
        }
    }
}

void free_objects_with_parents(Value* inhibit_free_object_address, sCompileInfo* info)
{
    sVarTable* it = info->lv_table;

    while(it != NULL) 
    {
        free_objects(it, inhibit_free_object_address, info);

        if(it->mCoroutineTop) {
            break;
        }

        it = it->mParent;
    }
}

/*
static BOOL call_clone_method(sNodeType* node_type, Value** address, sCompileInfo* info)
{
    LVALUE* llvm_stack = gLLVMStack;
    int stack_num_before = info->stack_num;
    sNodeType* info_type_before = info->type;

    char real_fun_name[REAL_FUN_NAME_MAX];

    Value* obj = Builder.CreateAlignedLoad(*address, 8);

    char struct_name[VAR_NAME_MAX+128];
    if(strcmp(node_type->mTypeName, "") == 0)
    {
        xstrncpy(struct_name, node_type->mClass->mName, VAR_NAME_MAX+128);
    }
    else {
        xstrncpy(struct_name, node_type->mTypeName, VAR_NAME_MAX+128);
    }

    create_real_fun_name(real_fun_name, REAL_FUN_NAME_MAX, "clone", struct_name);

    std::vector<sFunction*>& funcs = gFuncs[real_fun_name];

    if(funcs.size() > 0 && node_type->mPointerNum == 1) {
        Value* obj2 = Builder.CreateCast(Instruction::PtrToInt, obj, IntegerType::get(TheContext, 64));
        Value* cmp_right_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);
        Value* conditional = Builder.CreateICmpNE(obj2, cmp_right_value);

        BasicBlock* cond_then_block = BasicBlock::Create(TheContext, "cond_then_block", llvm_function);
        BasicBlock* cond_end_block = BasicBlock::Create(TheContext, "cond_end", llvm_function);

        Builder.CreateCondBr(conditional, cond_then_block, cond_end_block);

        Builder.SetInsertPoint(cond_then_block);
        info->current_block = cond_then_block;

        Value* params[PARAMS_MAX];

        params[0] = obj;

        int num_params = 1;

        if(!call_function("clone", params, num_params, struct_name, FALSE, node_type, info))
        {
            char method_name[BUFSIZ];
            snprintf(method_name, BUFSIZ, "clone_%s", info->sname);

            if(!call_function(method_name, params, num_params, struct_name, FALSE, node_type, info))
            {
                compile_err_msg(info, "Not found found clone function");
                info->err_num++;
                exit(2);
            }
        }

        LVALUE llvm_value = *get_value_from_stack(-1);

        *address = llvm_value.value;

        remove_from_right_value_object(*address, info);

        dec_stack_ptr(1, info);

        gLLVMStack = llvm_stack;
        info->stack_num = stack_num_before;
        info->type = info_type_before;

        Builder.CreateBr(cond_end_block);

        Builder.SetInsertPoint(cond_end_block);
        info->current_block = cond_end_block;

        return TRUE;
    }

    char fun_name[BUFSIZ];
    snprintf(fun_name, BUFSIZ, "clone_%s", info->sname);

    create_real_fun_name(real_fun_name, REAL_FUN_NAME_MAX, fun_name, struct_name);

    std::vector<sFunction*>& funcs2 = gFuncs[real_fun_name];

    if(funcs2.size() > 0 && node_type->mPointerNum == 1) {
        Value* obj2 = Builder.CreateCast(Instruction::PtrToInt, obj, IntegerType::get(TheContext, 64));
        Value* cmp_right_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);
        Value* conditional = Builder.CreateICmpNE(obj2, cmp_right_value);

        BasicBlock* cond_then_block = BasicBlock::Create(TheContext, "cond_then_block", llvm_function);
        BasicBlock* cond_end_block = BasicBlock::Create(TheContext, "cond_end", llvm_function);

        Builder.CreateCondBr(conditional, cond_then_block, cond_end_block);

        Builder.SetInsertPoint(cond_then_block);
        info->current_block = cond_then_block;

        Value* params[PARAMS_MAX];

        params[0] = obj;

        int num_params = 1;

        char method_name[BUFSIZ];
        snprintf(method_name, BUFSIZ, "clone_%s", info->sname);

        if(!call_function(method_name, params, num_params, struct_name, FALSE, node_type, info))
        {
            compile_err_msg(info, "Not found found clone function");
            info->err_num++;
            exit(2);
        }

        LVALUE llvm_value = *get_value_from_stack(-1);

        *address = llvm_value.value;

        remove_from_right_value_object(*address, info);

        dec_stack_ptr(1, info);

        gLLVMStack = llvm_stack;
        info->stack_num = stack_num_before;
        info->type = info_type_before;

        Builder.CreateBr(cond_end_block);

        Builder.SetInsertPoint(cond_end_block);
        info->current_block = cond_end_block;

        return TRUE;
    }

    gLLVMStack = llvm_stack;
    info->stack_num = stack_num_before;
    info->type = info_type_before;

    return FALSE;
}

Value* clone_object(sNodeType* node_type, Value* address, sCompileInfo* info)
{
    sCLClass* klass = node_type->mClass;

    sNodeType* node_type2 = clone_node_type(node_type);
    node_type2->mPointerNum = 0;

    Type* llvm_struct_type;
    if(!create_llvm_type_from_node_type(&llvm_struct_type, node_type2, node_type2, info))
    {
        fprintf(stderr, "%s %d: The error at create_llvm_type_from_node_type\n", info->sname, info->sline);
        exit(2);
    }

    int i;
    for(i=0; i<klass->mNumFields; i++) {
        sNodeType* field_type = clone_node_type(klass->mFields[i]);

        BOOL success_solve;
        if(!solve_generics(&field_type, node_type, &success_solve))
        {
            fprintf(stderr, "%s %d: The error at solve_generics\n", info->sname, info->sline);
            exit(2);
        }
        sCLClass* field_class = field_type->mClass;

        if(field_type->mHeap && field_type->mPointerNum > 0)
        {
            if(type_identify(node_type, field_type))
            {
                BOOL exist_clone_method = FALSE;

                char fun_name[BUFSIZ];
                snprintf(fun_name, BUFSIZ, "clone_%s", info->sname);

                char real_fun_name[REAL_FUN_NAME_MAX];
                create_real_fun_name(real_fun_name, REAL_FUN_NAME_MAX, fun_name, klass->mName);

                std::vector<sFunction*>& funcs = gFuncs[real_fun_name];
                if(funcs.size() != 0) {
                    exist_clone_method = TRUE;
                }

                if(!exist_clone_method) {
                    LVALUE* llvm_stack = gLLVMStack;
                    int stack_num = info->stack_num;

                    if(!make_clone_for_recursive_field_type(node_type, info)) {
                        fprintf(stderr, "%s %d: can't make clone of recursive field(2)(%s)\n", info->sname, info->sline, node_type->mClass->mName);
                        exit(2);
                    }

                    gLLVMStack = llvm_stack;
                    info->stack_num = stack_num;
                }
            }
        }
    }

    BOOL execute_clone_method = call_clone_method(node_type, &address, info);

    if(execute_clone_method) {
        return address;
    }

    Value* obj = Builder.CreateAlignedLoad(address, 8);
    if(node_type->mPointerNum > 0) {
        Value* obj2 = Builder.CreateCast(Instruction::PtrToInt, obj, IntegerType::get(TheContext, 64));
        Value* cmp_right_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);
        Value* conditional = Builder.CreateICmpNE(obj2, cmp_right_value);

        BasicBlock* cond_then_block = BasicBlock::Create(TheContext, "cond_then_block", llvm_function);
        BasicBlock* cond_end_block = BasicBlock::Create(TheContext, "cond_end", llvm_function);

        Builder.CreateCondBr(conditional, cond_then_block, cond_end_block);

        Builder.SetInsertPoint(cond_then_block);
        info->current_block = cond_then_block;

        sCLClass* klass = node_type->mClass;

        Value* src_obj = Builder.CreateAlignedLoad(address, 8);

        sNodeType* left_type = create_node_type_with_class_name("char*");
        sNodeType* right_type = clone_node_type(node_type);

        LVALUE rvalue;
        rvalue.value = src_obj;
        rvalue.type = clone_node_type(node_type);
        rvalue.address = nullptr;
        rvalue.var = nullptr;
        rvalue.binded_value = FALSE;
        rvalue.load_field = FALSE;

        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "can't clone this value");
            exit(2);
        }

        /// memdup ///
        Function* fun = TheModule->getFunction("memdup");

        if(fun == nullptr) {
            fprintf(stderr, "require ncmemdup\n");
            exit(2);
        }

        std::vector<Value*> params2;
        Value* param = rvalue.value;
        params2.push_back(param);

        Value* address2 = Builder.CreateCall(fun, params2);

        sNodeType* left_type2 = clone_node_type(node_type);
        sNodeType* right_type2 = create_node_type_with_class_name("char*");

        LVALUE rvalue2;
        rvalue2.value = address2;
        rvalue2.type = create_node_type_with_class_name("char*");
        rvalue2.address = nullptr;
        rvalue2.var = nullptr;
        rvalue2.binded_value = FALSE;
        rvalue2.load_field = FALSE;

        if(!cast_right_type_to_left_type(left_type2, &right_type2, &rvalue2, info))
        {
            compile_err_msg(info, "can't clone this value");
            exit(2);
        }

        Value* address3 = rvalue2.value;

        sNodeType* node_type2 = clone_node_type(node_type);
        node_type2->mPointerNum = 0;

        Type* llvm_struct_type;
        (void)create_llvm_type_from_node_type(&llvm_struct_type, node_type2, node_type2, info);

        if(node_type->mPointerNum == 1) {
            int i;
            for(i=0; i<klass->mNumFields; i++) {
                sNodeType* field_type = clone_node_type(klass->mFields[i]);
                sCLClass* field_class = field_type->mClass;

                Type* llvm_field_type;
                (void)create_llvm_type_from_node_type(&llvm_field_type, field_type, node_type2, info);

                int alignment = get_llvm_alignment_from_node_type(field_type);

                if(field_type->mHeap) 
                {
#if LLVM_VERSION_MAJOR >= 7
                    Value* field_address = Builder.CreateStructGEP(address3, i);
#else
                    Value* field_address = Builder.CreateStructGEP(llvm_struct_type, address3, i);
#endif
                    Value* field_value = clone_object(field_type, field_address, info);

                    Builder.CreateAlignedStore(field_value,  field_address, alignment);
                }
            }
        }

        Builder.CreateBr(cond_end_block);

        Builder.SetInsertPoint(cond_end_block);
        info->current_block = cond_end_block;

        return address3;
    }
    else {
        return obj;
    }
}
*/

///////////////////////////////////////////////////////////////////////
// compiler
///////////////////////////////////////////////////////////////////////
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

static void start_to_make_native_code()
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

static void output_native_code()
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

Value* llvm_create_string(char* str)
{
    Constant* str_constant = ConstantDataArray::getString(TheModule->getContext(), str, true);

    GlobalVariable* gvar = new GlobalVariable(*TheModule, ArrayType::get(IntegerType::get(TheContext, 8), strlen(str)+1), true, GlobalValue::PrivateLinkage, 0, "global_string");
    gvar->setAlignment(1);

    gvar->setInitializer(str_constant);

    Value* value = Builder.CreateCast(Instruction::BitCast, gvar, PointerType::get(IntegerType::get(TheContext, 8), 0));

    return value;
}

Value* load_address_to_lvtable(int index, sNodeType* var_type, sCompileInfo* info)
{
    if(index >= LOCAL_VARIABLE_MAX) {
        fprintf(stderr, "overflow local variable number\n");
        exit(1);
    }

    Value* lvtable_value2 = Builder.CreateCast(Instruction::BitCast, (Value*)info->lv_table_value, PointerType::get(PointerType::get(IntegerType::get(TheContext, 8), 0), 0));

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

void store_address_to_lvtable(int index, Value* address, sCompileInfo* info)
{
    if(index >= LOCAL_VARIABLE_MAX) {
        fprintf(stderr, "overflow local variable number\n");
        exit(1);
    }

    Value* lvtable_value2 = Builder.CreateCast(Instruction::BitCast, (Value*)info->lv_table_value, PointerType::get(PointerType::get(IntegerType::get(TheContext, 8), 0), 0));

    Value* lvalue = lvtable_value2;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(32, index));
    Value* element_address_value = Builder.CreateGEP(lvalue, rvalue);
    Value* address2 = Builder.CreateCast(Instruction::BitCast, address, PointerType::get(IntegerType::get(TheContext, 8), 0));

    Builder.CreateAlignedStore(address2, element_address_value, 8);
}

void create_internal_functions()
{
    Type* result_type;
    std::vector<Type *> type_params;
    Type* param1_type;
    Type* param2_type;
    Type* param3_type;
    Type* param4_type;
    Type* param5_type;
    Type* param6_type;
    Type* param7_type;
    Type* param8_type;
    Type* param9_type;
    Type* param10_type;
    Type* param11_type;
    Type* param12_type;
    Type* param13_type;
    Type* param14_type;
    Type* param15_type;
    FunctionType* function_type;
}

void llvm_init()
{
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    start_to_make_native_code();

    gLLVMStack = (LVALUE*)xcalloc(1, sizeof(LVALUE)*NEO_C_STACK_SIZE);
    gLLVMStackHead = gLLVMStack;

    create_internal_functions();
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

BOOL compile_block(unsigned int node_block, sCompileInfo* info, BOOL* last_expression_is_return)
{
    int num_nodes = gNodes[node_block].uValue.sBlock.mNumNodes;
    unsigned int* nodes = gNodes[node_block].uValue.sBlock.mNodes;

    sVarTable* lv_table = info->lv_table;
    info->lv_table = init_var_table();
    info->lv_table->mParent = lv_table;

    int i;
    for(i=0; i<num_nodes; i++) {
        unsigned int node = nodes[i];
        if(!compile(node, info)) {
            return FALSE;
        }
        free_right_value_objects(info);

        dec_stack_ptr(info->stack_num, info);

        *last_expression_is_return = gNodes[node].mNodeType == kNodeTypeReturn;
    }

    if(!*last_expression_is_return) {
        free_objects(info->lv_table, nullptr, info);
    }

    if(info->err_num > 0) {
        fprintf(stderr, "compile error\n");
        exit(2);
    }

    info->lv_table= lv_table;

    return TRUE;
}


///////////////////////////////////////////////////////////////////////
// main
///////////////////////////////////////////////////////////////////////
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

static BOOL compile_str_value(unsigned int node, sCompileInfo* info)
{
    char buf[512];
    xstrncpy(buf, gNodes[node].uValue.mStrValue, 512);

    LVALUE llvm_value;
    llvm_value.value = llvm_create_string(buf);
    llvm_value.type = create_node_type_with_class_name("const char*");
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("const char*");

    return TRUE;
}

static BOOL compile_true(unsigned int node, sCompileInfo* info)
{
    LVALUE llvm_value;
    llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(1, 1, true)); 
    llvm_value.type = create_node_type_with_class_name("bool");
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

static BOOL compile_false(unsigned int node, sCompileInfo* info)
{
    LVALUE llvm_value;
    llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(1, 0, true)); 
    llvm_value.type = create_node_type_with_class_name("bool");
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("bool");

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

    if(left_type->mArrayDimentionNum == 1 && is_number_type(right_type))
    {
        left_type->mArrayDimentionNum = 0;
        left_type->mPointerNum++;

        Type* llvm_left_type;
        if(!create_llvm_type_from_node_type(&llvm_left_type, left_type, left_type, info))
        {
            compile_err_msg(info, "Getting llvm type failed(10)");
            show_node_type(left_type);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        Value* left_value = Builder.CreateCast(Instruction::BitCast, lvalue.address, llvm_left_type);
        Value* left_value2 = Builder.CreateCast(Instruction::PtrToInt, left_value, IntegerType::get(TheContext, 64));

        Value* right_value;
        if(type_identify_with_class_name(right_type, "long")) {
            right_value = rvalue.value;
        }
        else {
            if(right_type->mPointerNum > 0 || right_type->mArrayDimentionNum > 0) {
                right_value = Builder.CreateCast(Instruction::PtrToInt, rvalue.value, IntegerType::get(TheContext, 64), "sext1-p");
            }
            else {
                right_value = Builder.CreateCast(Instruction::SExt, rvalue.value, IntegerType::get(TheContext, 64), "sext1");
            }
        }

        Type* llvm_var_type;
        if(!create_llvm_type_from_node_type(&llvm_var_type, left_type, left_type, info))
        {
            compile_err_msg(info, "Getting llvm type failed(10)");
            show_node_type(left_type);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        sNodeType* left_type3 = clone_node_type(left_type);
        left_type3->mPointerNum--;

        uint64_t alloc_size = 0;
        if(!get_size_from_node_type(&alloc_size, left_type3, left_type3, info))
        {
            return FALSE;
        }

        Value* alloc_size_value = ConstantInt::get(Type::getInt64Ty(TheContext), alloc_size);

        right_value = Builder.CreateMul(right_value, alloc_size_value, "multtmp", false, true);

        sNodeType* left_type2 = clone_node_type(left_type);
        left_type2->mHeap = FALSE;

        LVALUE llvm_value;
        llvm_value.value = Builder.CreateAdd(left_value2, right_value, "addtmp", false, true);
        llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, llvm_var_type, "intToPtr1");
        llvm_value.type = clone_node_type(left_type2);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(2, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(left_type2);
    }
    else if(left_type->mPointerNum > 0 && is_number_type(right_type)) {
        Value* left_value = Builder.CreateCast(Instruction::PtrToInt, lvalue.value, IntegerType::get(TheContext, 64));

        Value* right_value;
        if(type_identify_with_class_name(right_type, "long")) {
            right_value = rvalue.value;
        }
        else {
            if(right_type->mPointerNum > 0 || right_type->mArrayDimentionNum > 0) {
                right_value = Builder.CreateCast(Instruction::PtrToInt, rvalue.value, IntegerType::get(TheContext, 64), "sextXYZ-p");
            }
            else {
                right_value = Builder.CreateCast(Instruction::SExt, rvalue.value, IntegerType::get(TheContext, 64), "sextXYZ");
            }
        }

        Type* llvm_var_type;
        if(!create_llvm_type_from_node_type(&llvm_var_type, left_type, left_type, info))
        {
            compile_err_msg(info, "Getting llvm type failed(10)");
            show_node_type(left_type);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        sNodeType* left_type3 = clone_node_type(left_type);
        left_type3->mPointerNum--;

        uint64_t alloc_size = 0;
        if(!get_size_from_node_type(&alloc_size, left_type3, left_type3, info))
        {
            return FALSE;
        }

        Value* alloc_size_value = ConstantInt::get(Type::getInt64Ty(TheContext), alloc_size);

        right_value = Builder.CreateMul(right_value, alloc_size_value, "multtmp", false, true);

        sNodeType* left_type2 = clone_node_type(left_type);
        left_type2->mHeap = FALSE;

        LVALUE llvm_value;
        llvm_value.value = Builder.CreateAdd(left_value, right_value, "addtmp", false, true);
        llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, llvm_var_type, "intToPtr2");
        llvm_value.type = clone_node_type(left_type2);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(2, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(left_type2);
    }
    else if(is_number_type(left_type) && is_number_type(right_type))
    {
        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        LVALUE llvm_value;

        llvm_value.value = Builder.CreateAdd(lvalue.value, rvalue.value, "addtmp", false, true);
        llvm_value.type = clone_node_type(right_type);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(2, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(llvm_value.type);
    }
    else {
        compile_err_msg(info, "invalid type for operator +");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
    }

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

    int index = -1;
    if(alloc) {
        sNodeType* var_type = create_node_type_with_class_name(type_name);
        if(var_type == NULL || var_type->mClass == NULL) {
            compile_err_msg(info, "Invalid type name %s\n", type_name);
            return FALSE;
        }

        BOOL success_solve;
        (void)solve_generics(&var_type, info->generics_type, &success_solve);

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

        BOOL parent = FALSE;
        int index = get_variable_index(info->lv_table, var_name, &parent);

        store_address_to_lvtable(index, address, info);
    }

    sVar* var = get_variable_from_table(info->lv_table, var_name);
    sNodeType* var_type = var->mType;

    if(auto_cast_posibility(var_type, right_type)) {
        if(!cast_right_type_to_left_type(var_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    if(!substitution_posibility(var_type, right_type, FALSE)) 
    {
        compile_err_msg(info, "The different type between left type and right type. store variable. var name is %s", var_name);
        show_node_type(var_type);
        show_node_type(right_type);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }


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

//    Value* rvalue2 = Builder.CreateCast(Instruction::BitCast, rvalue.value, llvm_var_type);

    std_move(var_address, var->mType, &rvalue, alloc, info);

    Builder.CreateAlignedStore(rvalue.value, var_address, alignment);

    info->type = right_type;

    return TRUE;
}

static BOOL compile_load_variable(unsigned int node, sCompileInfo* info)
{
    char var_name[VAR_NAME_MAX];

    xstrncpy(var_name, gNodes[node].uValue.sLoadVariable.mVarName, VAR_NAME_MAX);

    sVar* var = get_variable_from_table(info->lv_table, var_name);

    if(var == NULL || var->mType == NULL) {
        compile_err_msg(info, "undeclared variable(1) %s", var_name);
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

BOOL create_llvm_function(sFunction* fun, sCompileInfo* info)
{
    void* right_value_objects = new_right_value_objects_container(info);

    int num_params = fun->mNumParams;
    BOOL coroutine = fun->mCoroutine;

    sParserParam params[PARAMS_MAX];

    int i;
    for(i=0; i<num_params; i++) {
        xstrncpy(params[i].mName, fun->mParamNames[i], VAR_NAME_MAX);
        xstrncpy(params[i].mTypeName, fun->mParamTypes[i], VAR_NAME_MAX);
        params[i].mType = create_node_type_with_class_name(params[i].mTypeName);

        BOOL success_solve;
        (void)solve_generics(&params[i].mType, info->generics_type, &success_solve);

        if(params[i].mType == NULL || params[i].mType->mClass == NULL) {
            compile_err_msg(info, "Invalid type name %s\n", fun->mParamNames[i]);
            return FALSE;
        }
    }

    sNodeType* result_type = create_node_type_with_class_name(fun->mResultTypeName);
    BOOL success_solve;
    (void)solve_generics(&result_type, info->generics_type, &success_solve);

    Function* llvm_fun = fun->mLLVMFunction;

    unsigned int node_block = fun->mNodeBlock;

    sFunction* function = (sFunction*)info->function;
    info->function = fun;
    info->function_result_type = result_type;

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
    info->lv_table = init_var_table();

    if(coroutine) {
        info->lv_table->mCoroutineTop = TRUE;
        info->lv_table->mParent = lv_table;
    }

    BasicBlock* current_block_before;
    BasicBlock* current_block = BasicBlock::Create(TheContext, "entry", llvm_fun);
    llvm_change_block(current_block, &current_block_before, info, FALSE);

    info->andand_result_var = (void*)Builder.CreateAlloca(IntegerType::get(TheContext, 1), 0, "andand_result_var");
    info->oror_result_var = (void*)Builder.CreateAlloca(IntegerType::get(TheContext, 1), 0, "andand_result_var");

    if(!coroutine) {
        Type* lvtable_type = get_lvtable_type();

        static int func_num = 0;

        char buf[VAR_NAME_MAX];
        snprintf(buf, VAR_NAME_MAX, "gLVTable%d", func_num);
        func_num++;

        GlobalVariable* lv_table_value = new GlobalVariable(*TheModule, lvtable_type, false, GlobalValue::InternalLinkage, 0, buf);
        lv_table_value->setAlignment(8);

        ConstantAggregateZero* initializer = ConstantAggregateZero::get(lvtable_type);

        lv_table_value->setInitializer(initializer);

        info->lv_table_value = (void*)lv_table_value;
    }


    /// ready for params ///
    for(i=0; i<num_params; i++) {
        sParserParam param = params[i];
        char* var_name = param.mName;

        sNodeType* var_type = create_node_type_with_class_name(param.mTypeName);

        BOOL success_solve;
        (void)solve_generics(&var_type, info->generics_type, &success_solve);

        if(var_type == NULL || var_type->mClass == NULL) {
            compile_err_msg(info, "Invalid type name %s\n", param.mTypeName);
            return FALSE;
        }

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

        store_address_to_lvtable(index, address, info);
    }

    BOOL last_expression_is_return = FALSE;
    if(!compile_block(node_block, info, &last_expression_is_return)) {
        return FALSE;
    }

    if(type_identify_with_class_name(result_type, "void")) {
        Builder.CreateRet(nullptr);
    }

    free_objects_with_parents(nullptr, info);

    verifyFunction(*llvm_fun);

    // Run the optimizer on the function.
    //TheFPM->run(*llvm_fun, TheFAM);

    info->lv_table = lv_table;

    restore_right_value_objects_container(right_value_objects, info);

    BasicBlock* current_block_before2;
    llvm_change_block(current_block_before, &current_block_before2, info, FALSE);

    info->function = function;

    return TRUE;
}

BOOL compile_function(unsigned int node, sCompileInfo* info)
{
    char fun_name[VAR_NAME_MAX];
    xstrncpy(fun_name, gNodes[node].uValue.sFunction.mName, VAR_NAME_MAX);

    char fun_base_name[VAR_NAME_MAX];
    xstrncpy(fun_base_name, gNodes[node].uValue.sFunction.mBaseName, VAR_NAME_MAX);

    int num_params = gNodes[node].uValue.sFunction.mNumParams;
    BOOL var_arg = gNodes[node].uValue.sFunction.mVarArg;
    BOOL inline_ = gNodes[node].uValue.sFunction.mInline;
    BOOL static_ = gNodes[node].uValue.sFunction.mStatic;
    BOOL coroutine = gNodes[node].uValue.sFunction.mCoroutine;
    BOOL generics = gNodes[node].uValue.sFunction.mGenerics;
    BOOL method_generics = gNodes[node].uValue.sFunction.mMethodGenerics;
    BOOL inherit_ = gNodes[node].uValue.sFunction.mInherit;
    BOOL external = gNodes[node].uValue.sFunction.mExternal;
    
    char* result_type_name = gNodes[node].uValue.sFunction.mResultTypeName;

    unsigned int node_block = gNodes[node].uValue.sFunction.mNodeBlock;

    char* param_types[PARAMS_MAX];
    char* param_names[PARAMS_MAX];

    int i;
    for(i=0; i<num_params; i++) {
        param_types[i] = gNodes[node].uValue.sFunction.mParams[i].mTypeName;
        param_names[i] = gNodes[node].uValue.sFunction.mParams[i].mName;
    }

    if(!add_function(fun_name, fun_base_name, result_type_name, num_params, param_types, param_names, var_arg, inline_, inherit_, static_, node_block, generics, coroutine, method_generics, info)) {
        return FALSE;
    }

    if(!generics && !method_generics) {
        sFunction fun = gFuncs[fun_name][gFuncs[fun_name].size()-1];

        if(!create_llvm_function(&fun, info)) {
            return FALSE;
        }
    }

    if(coroutine) {
        sFunction fun = gFuncs[fun_name][0];

        Function* llvm_fun = fun.mLLVMFunction;

        sNodeType* lambda_type = create_node_type_with_class_name("lambda");

        lambda_type->mResultType = create_node_type_with_class_name(result_type_name);
        lambda_type->mNumParams = num_params;
        for(i=0; i<num_params; i++) {
            lambda_type->mParamTypes[i] = create_node_type_with_class_name(param_types[i]);

            BOOL success_solve;
            (void)solve_generics(&lambda_type->mParamTypes[i], info->generics_type, &success_solve);
        }

        LVALUE llvm_value;
        llvm_value.value = llvm_fun;
        llvm_value.type = lambda_type;
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        push_value_to_stack_ptr(&llvm_value, info);

        info->type = lambda_type;
    }
    else {
        info->type = create_node_type_with_class_name("void");
    }

    return TRUE;
}

BOOL compile_external_function(unsigned int node, sCompileInfo* info)
{
    char fun_name[VAR_NAME_MAX];
    xstrncpy(fun_name, gNodes[node].uValue.sFunction.mName, VAR_NAME_MAX);
    char fun_base_name[VAR_NAME_MAX];
    xstrncpy(fun_base_name, gNodes[node].uValue.sFunction.mName, VAR_NAME_MAX);
    int num_params = gNodes[node].uValue.sFunction.mNumParams;
    BOOL var_arg = gNodes[node].uValue.sFunction.mVarArg;
    BOOL inherit_ = gNodes[node].uValue.sFunction.mInherit;

    sParserParam params[PARAMS_MAX];

    int i;
    for(i=0; i<num_params; i++) {
        sParserParam* param = gNodes[node].uValue.sFunction.mParams + i;
        xstrncpy(params[i].mName, param->mName, VAR_NAME_MAX);
        xstrncpy(params[i].mTypeName, param->mTypeName, VAR_NAME_MAX);
        params[i].mType = create_node_type_with_class_name(param->mTypeName);
        if(params[i].mType == NULL || params[i].mType->mClass == NULL) {
            compile_err_msg(info, "Invalid type name %s\n", param->mTypeName);
            return FALSE;
        }
    }

    char* result_type_name = gNodes[node].uValue.sFunction.mResultTypeName;

    char* param_types[PARAMS_MAX];
    char* param_names[PARAMS_MAX];

    for(i=0; i<num_params; i++) {
        sParserParam* param = gNodes[node].uValue.sFunction.mParams + i;
        param_types[i] = param->mTypeName;
        param_names[i] = param->mName;
    }

    if(!add_function(fun_name, fun_base_name, result_type_name, num_params, param_types, param_names, var_arg, FALSE, inherit_, FALSE, 0, FALSE, FALSE, FALSE, info)) {
        return FALSE;
    }

    return TRUE;
}

static BOOL compile_return(unsigned int node, sCompileInfo* info)
{
    int right_node = gNodes[node].mRight;

    if(right_node != 0) {
        if(!compile(right_node, info)) {
            return FALSE;
        }

        sNodeType* right_type = clone_node_type(info->type);

        LVALUE rvalue = *get_value_from_stack(-1);

        dec_stack_ptr(1, info);

        sNodeType* left_type = info->function_result_type;

        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        if(!substitution_posibility(left_type, right_type, FALSE)) 
        {
            compile_err_msg(info, "The different type between left type and right type. returing value.");
            show_node_type(left_type);
            show_node_type(right_type);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        if(right_type->mHeap && left_type->mHeap) {
            free_objects_with_parents(rvalue.address, info);
        }
        else {
            free_objects_with_parents(nullptr, info);
        }
        Builder.CreateRet(rvalue.value);
    }
    else {
        free_objects_with_parents(nullptr, info);
        Builder.CreateRet(nullptr);
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

static BOOL create_generics_function(char* id, char* fun_name, sCLClass* klass, sFunction* fun, sCompileInfo* info) 
{
    sFunction generics_fun = *fun;

    char real_fun_name2[VAR_NAME_MAX];

    if(klass) {
        xstrncpy(real_fun_name2, klass->mName, VAR_NAME_MAX);

        create_real_struct_name(real_fun_name2, VAR_NAME_MAX, info->generics_type->mNumGenericsTypes, info->generics_type->mGenericsTypes);

        xstrncat(real_fun_name2, "_", VAR_NAME_MAX);
        xstrncat(real_fun_name2, fun_name, VAR_NAME_MAX);
    }
    else {
        xstrncpy(real_fun_name2, fun_name, VAR_NAME_MAX);
    }

    xstrncpy(generics_fun.mID, id, VAR_NAME_MAX);
    xstrncpy(generics_fun.mName, real_fun_name2, VAR_NAME_MAX);

    if(!entry_llvm_function(&generics_fun, info->generics_type, info)) {
        return FALSE;
    }

    if(!create_llvm_function(&generics_fun, info)) {
        return FALSE;
    }

    gFuncs[real_fun_name2].push_back(generics_fun);

    *fun = gFuncs[real_fun_name2][gFuncs[real_fun_name2].size()-1];

    return TRUE;
}

void solve_method_generics(char* node_type, char** method_generics_types)
{
    int i;
    for(i=0; i<GENERICS_TYPES_MAX; i++) {
        char generics_type_name[VAR_NAME_MAX];
        snprintf(generics_type_name, VAR_NAME_MAX, "mgenerics%d", i);

        char result_type[VAR_NAME_MAX];

        char* p = node_type;
        char* p2 = result_type;
        while(*p) {
            if(memcmp(p, generics_type_name, strlen(generics_type_name)) == 0) {
                memcpy(p2, method_generics_types[i], strlen(method_generics_types[i]));
                p += strlen(generics_type_name);
                p2 += strlen(method_generics_types[i]);
            }
            else {
                *p2++ = *p++;
            }
        }
        *p2 = '\0';

        xstrncpy(node_type, result_type, VAR_NAME_MAX);
    }
}

void determine_method_generics_core(sNodeType* left_type, sNodeType* right_type, char** method_generics_types)
{
    int n;
    if(sscanf(left_type->mClass->mName, "mgenerics%d", &n) == 1) {
        xstrncpy(method_generics_types[n], right_type->mClass->mName, VAR_NAME_MAX);
    }

    int i;
    for(i=0; i<left_type->mNumGenericsTypes; i++) {
        if(i < right_type->mNumGenericsTypes) {
            determine_method_generics_core(left_type->mGenericsTypes[i], right_type->mGenericsTypes[i], method_generics_types);
        }
    }
    for(i=0; i<left_type->mNumParams; i++) {
        if(i < right_type->mNumParams) {
            determine_method_generics_core(left_type->mParamTypes[i], right_type->mParamTypes[i], method_generics_types);
        }
    }

    if(left_type->mResultType && right_type->mResultType) {
        determine_method_generics_core(left_type->mResultType, right_type->mResultType, method_generics_types);
    }
}

void determine_method_generics(char* method_generics_types[VAR_NAME_MAX], sFunction* fun, sNodeType** param_types)
{
    int i;
    for(i=0; i<fun->mNumParams; i++) {
        sNodeType* left_type = create_node_type_with_class_name(fun->mParamTypes[i]);
        sNodeType* right_type = param_types[i];

        determine_method_generics_core(left_type, right_type, method_generics_types);
    }
}

BOOL compile_function_call(unsigned int node, sCompileInfo* info)
{
    BOOL lambda_call = gNodes[node].uValue.sFunctionCall.mLambdaCall;
    BOOL inherit_ = gNodes[node].uValue.sFunctionCall.mInherit;

    int num_params = gNodes[node].uValue.sFunctionCall.mNumParams;
    BOOL message_passing = gNodes[node].uValue.sFunctionCall.mMessagePassing;

    unsigned int params[PARAMS_MAX];
    int i;
    for(i=0; i<num_params; i++) {
        params[i] = gNodes[node].uValue.sFunctionCall.mParams[i];
    }

    Value* llvm_fun;
    std::vector<Value*> llvm_params;
    sNodeType* result_type;
    sNodeType* generics_type = info->generics_type;

    if(lambda_call) {
        unsigned int lambda_node = gNodes[node].mLeft;

        /// go ///
        if(!compile(lambda_node, info)) {
            return FALSE;
        }

        sNodeType* lambda_type = clone_node_type(info->type);
        LVALUE lambda_value = *get_value_from_stack(-1);

        sNodeType* param_types[PARAMS_MAX];
        LVALUE param_values[PARAMS_MAX];

        for(i=0; i<num_params; i++) {
            if(!compile(params[i], info)) {
                return FALSE;
            }

            param_types[i] = clone_node_type(info->type);
            param_values[i] = *get_value_from_stack(-1);
        }

        if(!type_identify_with_class_name(lambda_type, "lambda")) {
            compile_err_msg(info, "invalid type of calling co-routine\n");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        if(num_params != lambda_type->mNumParams) {
            compile_err_msg(info, "invalid param number of calling co-routine\n");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        for(i=0; i<num_params; i++) {
            sNodeType* left_type = lambda_type->mParamTypes[i];
            sNodeType* right_type = param_types[num_params-i-1];

            LVALUE rvalue = param_values[num_params-i-1];

            if(auto_cast_posibility(left_type, right_type)) {
                if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
                {
                    compile_err_msg(info, "Cast failed");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }

            if(!substitution_posibility(left_type, right_type, FALSE)) 
            {
                compile_err_msg(info, "Calling lambda function parametor #%d is invalid. The different type between left type and right type.", i);
                show_node_type(left_type);
                show_node_type(right_type);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            if(left_type->mHeap && right_type->mHeap)
            {
                if(rvalue.binded_value && rvalue.var)
                {
                    std_move(NULL, left_type, &rvalue, FALSE, info);
                }
                else {
                    remove_from_right_value_object(rvalue.value, info);
                }
            }
            else if(right_type->mHeap && !rvalue.binded_value)
            {
                append_heap_object_to_right_value(&rvalue, info);
            }

            llvm_params.push_back(rvalue.value);
        }

        result_type = lambda_type->mResultType;
        llvm_fun = lambda_value.value;
    }
    else {
        char fun_name[VAR_NAME_MAX];

        xstrncpy(fun_name, gNodes[node].uValue.sFunctionCall.mFunName, VAR_NAME_MAX);

        sNodeType* param_types[PARAMS_MAX];
        LVALUE param_values[PARAMS_MAX];

        for(i=0; i<num_params; i++) {
            if(!compile(params[i], info)) {
                return FALSE;
            }

            param_types[i] = clone_node_type(info->type);
            param_values[i] = *get_value_from_stack(-1);
        }
        sNodeType* param_types2[PARAMS_MAX];
        LVALUE param_values2[PARAMS_MAX];

        for(i=0; i<num_params; i++) {
            param_types2[i] = param_types[num_params-i-1];
            param_values2[i] = param_values[num_params-i-1];
        }

        sFunction fun;
        memset(&fun, 0, sizeof(sFunction));

        if(message_passing) {
            info->generics_type = clone_node_type(param_types2[0]);

            sCLClass* klass = param_types2[0]->mClass;

            char real_fun_name[VAR_NAME_MAX];

            if(inherit_) {
                sFunction* current_function = (sFunction*)info->function;

                xstrncpy(real_fun_name, current_function->mID, VAR_NAME_MAX);
                sCLClass* klass = param_types2[0]->mClass;

                int current_version = current_function->mVersion;

                if(gFuncs[real_fun_name].size() == 0 || gFuncs[real_fun_name].size() < current_version-1) {
                    compile_err_msg(info, "Function not found(inherit) %s\n", real_fun_name);
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return FALSE;
                }

                fun = gFuncs[real_fun_name][current_function->mVersion-1];

                xstrncpy(fun_name, fun.mBaseName, VAR_NAME_MAX);
            }
            else {
                xstrncpy(real_fun_name, klass->mName, VAR_NAME_MAX);
                xstrncat(real_fun_name, "_", VAR_NAME_MAX);
                xstrncat(real_fun_name, fun_name, VAR_NAME_MAX);

                if(gFuncs[real_fun_name].size() == 0) {
                    compile_err_msg(info, "Function not found(1) %s\n", real_fun_name);
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return FALSE;
                }

                fun = gFuncs[real_fun_name][gFuncs[real_fun_name].size()-1];
            }

            if(fun.mMethodGenerics) {
                char* method_generics_types[GENERICS_TYPES_MAX];
                int i;
                for(i=0; i<GENERICS_TYPES_MAX; i++) {
                    method_generics_types[i] = (char*)xcalloc(1, sizeof(char)*VAR_NAME_MAX);
                }
                determine_method_generics(method_generics_types, &fun, param_types2);

                sFunction fun2 = fun;

                solve_method_generics(fun2.mResultTypeName, method_generics_types);

                for(i=0; i<fun2.mNumParams; i++) {
                    solve_method_generics(fun2.mParamTypes[i], method_generics_types);
                }

                for(i=0; i<GENERICS_TYPES_MAX; i++) {
                    free(method_generics_types[i]);
                }

                fun = fun2;

                if(!create_generics_function(real_fun_name, fun_name, klass, &fun, info)) {
                    return FALSE;
                }
            }
            else if(fun.mGenerics) {
                if(!create_generics_function(real_fun_name, fun_name, klass, &fun, info)) {
                    return FALSE;
                }
            }
            else {
                fun = gFuncs[real_fun_name][gFuncs[real_fun_name].size()-1];
            }
        }
        else {
            info->generics_type = NULL;

            //fun = gFuncs[fun_name][gFuncs[fun_name].size()-1];
            
            if(inherit_) {
                sFunction* current_function = (sFunction*)info->function;

                char real_fun_name[VAR_NAME_MAX];

                xstrncpy(real_fun_name, current_function->mName, VAR_NAME_MAX);
                sCLClass* klass = param_types2[0]->mClass;

                int current_version = current_function->mVersion;
                if(gFuncs[fun_name].size() < current_version-1) {
                    compile_err_msg(info, "Function not found(inherit) %s\n", fun_name);
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return FALSE;
                }

                fun = gFuncs[real_fun_name][current_function->mVersion-1];
            }
            else {
                fun = gFuncs[fun_name][gFuncs[fun_name].size()-1];
            }

            if(fun.mMethodGenerics) {
                char* method_generics_types[GENERICS_TYPES_MAX];
                int i;
                for(i=0; i<GENERICS_TYPES_MAX; i++) {
                    method_generics_types[i] = (char*)xcalloc(1, sizeof(char)*VAR_NAME_MAX);
                }
                determine_method_generics(method_generics_types, &fun, param_types2);

                sFunction fun2 = fun;

                solve_method_generics(fun2.mResultTypeName, method_generics_types);

                for(i=0; i<fun2.mNumParams; i++) {
                    solve_method_generics(fun2.mParamTypes[i], method_generics_types);
                }
                for(i=0; i<GENERICS_TYPES_MAX; i++) {
                    free(method_generics_types[i]);
                }

                fun = fun2;

                if(!create_generics_function(fun_name, fun_name, NULL, &fun, info)) {
                    return FALSE;
                }
            }

            if(!fun.existance) {
                compile_err_msg(info, "Function not found(2) %s\n", fun_name);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        /// cast and type checking ///
        if(!fun.mVarArg) {
            if(fun.mNumParams != num_params) {
                compile_err_msg(info, "Calling function parametor number is invalid %s\n", fun_name);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            for(i=0; i<num_params; i++) {
                sNodeType* left_type = create_node_type_with_class_name(fun.mParamTypes[i]);
                sNodeType* right_type = param_types[num_params-i-1];

                BOOL success_solve;
                (void)solve_generics(&left_type, info->generics_type, &success_solve);

                LVALUE rvalue = param_values[num_params-i-1];

                if(auto_cast_posibility(left_type, right_type)) {
                    if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
                    {
                        compile_err_msg(info, "Cast failed");
                        info->err_num++;

                        info->type = create_node_type_with_class_name("int"); // dummy

                        return TRUE;
                    }
                }

                if(!substitution_posibility(left_type, right_type, FALSE)) 
                {
                    compile_err_msg(info, "Calling function(%s) parametor #%d is invalid. The different type between left type and right type.", fun_name, i);
                    show_node_type(left_type);
                    show_node_type(right_type);
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }

                if(left_type->mHeap && right_type->mHeap)
                {
                    if(rvalue.binded_value && rvalue.var)
                    {
                        std_move(NULL, left_type, &rvalue, FALSE, info);
                    }
                    else {
                        remove_from_right_value_object(rvalue.value, info);
                    }
                }
                else if(right_type->mHeap && !rvalue.binded_value)
                {
                    append_heap_object_to_right_value(&rvalue, info);
                }

                llvm_params.push_back(rvalue.value);
            }
        }
        else {
            if(fun.mNumParams > num_params) {
                compile_err_msg(info, "Calling function parametor number is invalid %s\n", fun_name);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            for(i=0; i<num_params; i++) {
                LVALUE rvalue = param_values[num_params-i-1];
                llvm_params.push_back(rvalue.value);
            }
        }

        result_type = create_node_type_with_class_name(fun.mResultTypeName);
        llvm_fun = fun.mLLVMFunction;

        if(llvm_fun == nullptr) {
            return TRUE;
        }
    }

    BOOL success_solve;
    (void)solve_generics(&result_type, info->generics_type, &success_solve);

    LVALUE llvm_value;
    llvm_value.value = Builder.CreateCall(llvm_fun, llvm_params);
    llvm_value.type = clone_node_type(result_type);
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = clone_node_type(result_type);

    info->generics_type = generics_type;

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

    sFunction* fun = (sFunction*)info->function;

    Function* llvm_function = fun->mLLVMFunction;

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


static BOOL compile_create_object(unsigned int node, sCompileInfo* info)
{
    char type_name[VAR_NAME_MAX];

    xstrncpy(type_name, gNodes[node].uValue.sCreateObject.mTypeName, VAR_NAME_MAX);

    sNodeType* node_type = create_node_type_with_class_name(type_name);

    if(node_type == NULL || node_type->mClass == NULL) {
        compile_err_msg(info, "Invalid type name %s\n", type_name);
        return FALSE;
    }

    sNodeType* node_type2 = clone_node_type(node_type);
    node_type2->mHeap = TRUE;

    unsigned int left_node = gNodes[node].mLeft;

    Value* object_num;
    if(left_node == 0) {
        object_num = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)1);
    }
    else {
        if(!compile(left_node, info)) {
            return FALSE;
        }

        if(!is_number_type(info->type)) {
            compile_err_msg(info, "Require number value for []");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        sNodeType* left_type;
        if(sizeof(size_t) == 4) {
            left_type = create_node_type_with_class_name("int");
        }
        else {
            left_type = create_node_type_with_class_name("long");
        }

        LVALUE llvm_value = *get_value_from_stack(-1);
        dec_stack_ptr(1, info);

        sNodeType* right_type = clone_node_type(llvm_value.type);

        if(auto_cast_posibility(left_type, right_type)) 
        {
            if(!cast_right_type_to_left_type(left_type, &right_type, &llvm_value, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        object_num = llvm_value.value;
    }

    /// calloc ///
    uint64_t size;
    if(!get_size_from_node_type(&size, node_type2, node_type2, info))
    {
        compile_err_msg(info, "Getting allocate size error(8)");
        show_node_type(node_type2);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    Function* fun = TheModule->getFunction("calloc");

    if(fun == nullptr) {
        fprintf(stderr, "require calloc\n");
        exit(2);
    }

    std::vector<Value*> params2;

    Value* param = object_num;
    params2.push_back(param);

    Value* param2;
    if(sizeof(size_t) == 4) {
        param2 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)size);
    }
    else {
        param2 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)size);
    }

    params2.push_back(param2);

    Value* address = Builder.CreateCall(fun, params2);

    node_type2->mPointerNum++;

    Type* llvm_type;
    if(!create_llvm_type_from_node_type(&llvm_type, node_type2, node_type2, info))
    {
        compile_err_msg(info, "Getting llvm type failed(9)");
        show_node_type(node_type2);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    address = Builder.CreateCast(Instruction::BitCast, address, llvm_type);

    /// result ///
    LVALUE llvm_value;
    llvm_value.value = address;
    llvm_value.type = clone_node_type(node_type2);
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    append_heap_object_to_right_value(&llvm_value, info);

    info->type = clone_node_type(node_type2);

    return TRUE;
}

static BOOL compile_clone(unsigned int node, sCompileInfo* info)
{
/*
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    LVALUE lvalue = *get_value_from_stack(-1);

    if(lvalue.address == nullptr) {
        compile_err_msg(info, "Can't get address of this value on clone operator");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    sNodeType* left_type = clone_node_type(info->type);
    sNodeType* left_type2 = clone_node_type(left_type);
    left_type2->mHeap = TRUE;

    Value* obj = clone_object(left_type, lvalue.address, info);

    dec_stack_ptr(1, info);

    LVALUE llvm_value;
    llvm_value.value = obj;
    llvm_value.type = clone_node_type(left_type2);
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    append_heap_object_to_right_value(&llvm_value, info);

    info->type = clone_node_type(left_type2);
*/

    return TRUE;
}

BOOL compile_struct(unsigned int node, sCompileInfo* info)
{
    char struct_name[VAR_NAME_MAX];
    xstrncpy(struct_name, gNodes[node].uValue.sStruct.mName, VAR_NAME_MAX);
    unsigned int fields_node = gNodes[node].uValue.sStruct.mFields;

    int num_fields = gNodes[fields_node].uValue.sFields.mNumFields;
    char type_fields[STRUCT_FIELD_MAX][VAR_NAME_MAX];
    char name_fields[STRUCT_FIELD_MAX][VAR_NAME_MAX];
    int i;
    for(i=0; i<num_fields; i++) {
        xstrncpy(type_fields[i], gNodes[fields_node].uValue.sFields.mTypeFields[i], VAR_NAME_MAX);
        xstrncpy(name_fields[i], gNodes[fields_node].uValue.sFields.mNameFields[i], VAR_NAME_MAX);
    }

    BOOL anonymous = gNodes[node].uValue.sStruct.mAnonymous;
    BOOL generics = gNodes[node].uValue.sStruct.mGenerics;

    sCLClass* klass = alloc_struct(struct_name, anonymous);

    sNodeType* fields[STRUCT_FIELD_MAX];

    for(i=0; i<num_fields; i++) {
        fields[i] = create_node_type_with_class_name(type_fields[i]);
        add_field_to_struct(klass, name_fields[i], fields[i]);
    }

    if(!generics) {
        sNodeType* struct_type = create_node_type_with_class_name(klass->mName);

        sNodeType* generics_type = struct_type;
        BOOL new_create = TRUE;
        (void)create_llvm_struct_type(struct_type, generics_type, new_create, info);
    }

    return TRUE;
}

BOOL compile_union(unsigned int node, sCompileInfo* info)
{
    char struct_name[VAR_NAME_MAX];
    xstrncpy(struct_name, gNodes[node].uValue.sStruct.mName, VAR_NAME_MAX);
    unsigned int fields_node = gNodes[node].uValue.sStruct.mFields;

    int num_fields = gNodes[fields_node].uValue.sFields.mNumFields;
    char type_fields[STRUCT_FIELD_MAX][VAR_NAME_MAX];
    char name_fields[STRUCT_FIELD_MAX][VAR_NAME_MAX];
    int i;
    for(i=0; i<num_fields; i++) {
        xstrncpy(type_fields[i], gNodes[fields_node].uValue.sFields.mTypeFields[i], VAR_NAME_MAX);
        xstrncpy(name_fields[i], gNodes[fields_node].uValue.sFields.mNameFields[i], VAR_NAME_MAX);
    }

    BOOL anonymous = gNodes[node].uValue.sStruct.mAnonymous;
    BOOL anonymous_var_name = FALSE;

    sCLClass* klass = alloc_union(struct_name, anonymous, anonymous_var_name);

    sNodeType* fields[STRUCT_FIELD_MAX];

    for(i=0; i<num_fields; i++) {
        fields[i] = create_node_type_with_class_name(type_fields[i]);
        add_field_to_union(klass, name_fields[i], fields[i]);
    }

    sNodeType* struct_type = create_node_type_with_class_name(klass->mName);

    sNodeType* generics_type = struct_type;
    (void)create_llvm_union_type(struct_type, generics_type, info);

    return TRUE;
}

static BOOL compile_define_variable(unsigned int node, sCompileInfo* info)
{
    char var_name[VAR_NAME_MAX];
    xstrncpy(var_name, gNodes[node].uValue.sDefineVariable.mVarName, VAR_NAME_MAX);
    char type_name[VAR_NAME_MAX];
    xstrncpy(type_name, gNodes[node].uValue.sDefineVariable.mTypeName, VAR_NAME_MAX);
    BOOL extern_ = gNodes[node].uValue.sDefineVariable.mExtern;

    sNodeType* var_type = create_node_type_with_class_name(type_name);
    if(var_type == NULL || var_type->mClass == NULL) {
        compile_err_msg(info, "Invalid type name %s\n", type_name);
        return FALSE;
    }

    BOOL success_solve;
    solve_generics(&var_type, info->generics_type, &success_solve);

    BOOL readonly = FALSE;
    BOOL constant = FALSE;
    BOOL global = gNodes[node].uValue.sDefineVariable.mGlobal;
    void* llvm_value = NULL;
    int index = -1;
    if(!add_variable_to_table(info->lv_table, var_name, var_type, llvm_value,  index, global, constant))
    {
        compile_err_msg(info, "overflow variable table");
        return FALSE;
    }

    sVar* var = get_variable_from_table(info->lv_table, var_name);

    if(var == NULL) {
        compile_err_msg(info, "undeclared variable(2) %s", var_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    Value* index_value = NULL;
    if(var_type->mDynamicArrayNum != 0) {
        unsigned int node = var_type->mDynamicArrayNum;

        if(!compile(node, info)) {
            return FALSE;
        }

        sNodeType* index_type = info->type;

        if(!type_identify_with_class_name(index_type, "int"))
        {
            compile_err_msg(info, "Invalid index type");

            show_node_type(index_type);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        LVALUE llvm_value = *get_value_from_stack(-1);

        index_value = llvm_value.value;

        dec_stack_ptr(1, info);
    }

    Type* llvm_var_type;
    if(!create_llvm_type_from_node_type(&llvm_var_type, var_type, var_type, info))
    {
        compile_err_msg(info, "Getting llvm type failed");
        show_node_type(var_type);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    int alignment = get_llvm_alignment_from_node_type(var_type);

    if(var_type->mDynamicArrayNum != 0) {
        Value* address = Builder.CreateAlloca(llvm_var_type, 0, var_name);
        if(!info->no_output) {
            var->mLLVMValue = address;
        }

        BOOL parent = FALSE;
        int index = get_variable_index(info->lv_table, var_name, &parent);

        store_address_to_lvtable(index, address, info);

        sNodeType* element_type = clone_node_type(var_type);

        element_type->mPointerNum--;

        Type* llvm_element_type;
        if(!create_llvm_type_from_node_type(&llvm_element_type, element_type, element_type, info))
        {
            compile_err_msg(info, "Getting llvm type failed(1)");
            show_node_type(element_type);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        Value* value = Builder.CreateAlloca(llvm_element_type, index_value, "element_memory");

        Builder.CreateAlignedStore(value, address, alignment);
    }
    else if(var->mConstant) {
        compile_err_msg(info, "Require right value for constant");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }
    else if(global) {
        if(extern_) {
            if(var->mLLVMValue == NULL && TheModule->getNamedGlobal(var_name) == nullptr)
            {
                GlobalVariable* address = new GlobalVariable(*TheModule, llvm_var_type, false, GlobalValue::ExternalLinkage, 0, var_name, nullptr, GlobalValue::NotThreadLocal, 0, true);

                address->setAlignment(alignment);
                var->mLLVMValue = address;

                BOOL parent = FALSE;
                int index = get_variable_index(info->lv_table, var_name, &parent);

                store_address_to_lvtable(index, address, info);
            }
        }
        else {
            if(TheModule->getNamedGlobal(var_name) != nullptr)
            {
                TheModule->getNamedGlobal(var_name)->eraseFromParent();
            }
            
            GlobalVariable* address = new GlobalVariable(*TheModule, llvm_var_type, false, GlobalValue::ExternalLinkage, 0, var_name, nullptr, GlobalValue::NotThreadLocal, 0, false);

            address->setAlignment(alignment);

            ConstantAggregateZero* initializer = ConstantAggregateZero::get(llvm_var_type);

            address->setInitializer(initializer);

            var->mLLVMValue = address;

            BOOL parent = FALSE;
            int index = get_variable_index(info->lv_table, var_name, &parent);

            store_address_to_lvtable(index, address, info);
        }
    }
    else {
        if(!info->no_output) {
            Value* address = Builder.CreateAlloca(llvm_var_type, 0, var_name);

            var->mLLVMValue = address;

            BOOL parent = FALSE;
            int index = get_variable_index(info->lv_table, var_name, &parent);

            store_address_to_lvtable(index, address, info);
        }
    }

    info->type = var_type;

    return TRUE;
}

static BOOL compile_equals(unsigned int node, sCompileInfo* info)
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

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    if(!type_identify(left_type, right_type)) {
        compile_err_msg(info, "Operand posibility failed");
        show_node_type(left_type);
        show_node_type(right_type);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }


    LVALUE llvm_value;
    llvm_value.value = Builder.CreateICmpEQ(lvalue.value, rvalue.value, "eqtmpX");
    llvm_value.type = create_node_type_with_class_name("bool");
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    dec_stack_ptr(2, info);
    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

static BOOL compile_not_equals(unsigned int node, sCompileInfo* info)
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

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    if(!type_identify(left_type, right_type)) {
        compile_err_msg(info, "Operand posibility failed");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    LVALUE llvm_value;
    llvm_value.value = Builder.CreateICmpNE(lvalue.value, rvalue.value, "noteqtmp");
    llvm_value.type = create_node_type_with_class_name("bool");
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    dec_stack_ptr(2, info);
    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

static BOOL compile_load_field(unsigned int node, sCompileInfo* info)
{
    char var_name[VAR_NAME_MAX]; 
    xstrncpy(var_name, gNodes[node].uValue.sLoadField.mVarName, VAR_NAME_MAX);

    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    if(!(left_type->mClass->mFlags & CLASS_FLAGS_STRUCT) && !(left_type->mClass->mFlags & CLASS_FLAGS_UNION)) {
        compile_err_msg(info, "This is not struct type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(left_type->mPointerNum > 1) {
        compile_err_msg(info, "This is pointer of pointer type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    int field_index = get_field_index(left_type->mClass, var_name, NULL);

    if(field_index == -1) {
        compile_err_msg(info, "The field(%s) is not found", var_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* field_type = clone_node_type(left_type->mClass->mFields[field_index]);

    BOOL success_solve;
    if(!solve_generics(&field_type, left_type, &success_solve)) {
        compile_err_msg(info, "Can't solve generics types(13)");
        show_node_type(field_type);
        show_node_type(left_type);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    Type* llvm_field_type;
    if(!create_llvm_type_from_node_type(&llvm_field_type, field_type, field_type, info))
    {
        compile_err_msg(info, "Getting llvm type failed(13)");
        show_node_type(field_type);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    LVALUE lvalue = *get_value_from_stack(-1);

    sNodeType* left_type2 = clone_node_type(left_type);
    left_type2->mPointerNum = 0;

    Type* llvm_struct_type;
    if(!create_llvm_type_from_node_type(&llvm_struct_type, left_type2, left_type2, info))
    {
        compile_err_msg(info, "Getting llvm type failed(14)");
        show_node_type(left_type2);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    Value* field_address;
    if(left_type->mClass->mFlags & CLASS_FLAGS_UNION) {
        if(left_type->mPointerNum == 0) {
            if(lvalue.address == NULL) {
                field_address = NULL;
            }
            else {
                field_address = Builder.CreateCast(Instruction::BitCast, lvalue.address, PointerType::get(llvm_field_type, 0));
            }
        }
        else {
            field_address = Builder.CreateCast(Instruction::BitCast, lvalue.value, PointerType::get(llvm_field_type, 0));
        }
    }
    else {
        if(left_type->mPointerNum == 0) {
#if LLVM_VERSION_MAJOR >= 7
            field_address = Builder.CreateStructGEP(lvalue.address, field_index);
#else
            field_address = Builder.CreateStructGEP(llvm_struct_type, lvalue.address, field_index);
#endif
        }
        else {
#if LLVM_VERSION_MAJOR >= 7
            field_address = Builder.CreateStructGEP(lvalue.value, field_index);
#else
            field_address = Builder.CreateStructGEP(llvm_struct_type, lvalue.value, field_index);
#endif
        }
    }

    int alignment = get_llvm_alignment_from_node_type(field_type);

    Value* field_address2;
    if(field_address == NULL) {
        field_address2 = NULL;
    }
    else {
        field_address2 = Builder.CreateCast(Instruction::BitCast, field_address, PointerType::get(llvm_field_type, 0));
    }

    LVALUE llvm_value;
    if(field_type->mArrayDimentionNum == 1) {
        llvm_value.value = field_address2;
    }
    else {
        if(field_address2 == NULL) {
            llvm_value.value = Builder.CreateCast(Instruction::BitCast, lvalue.value, llvm_field_type);
        }
        else {
            llvm_value.value = Builder.CreateAlignedLoad(field_address2, alignment);
        }
    }

    llvm_value.type = clone_node_type(field_type);
    llvm_value.address = field_address2;
    llvm_value.var = nullptr;
    llvm_value.binded_value = TRUE;
    llvm_value.load_field = TRUE;

    if(field_type->mArrayDimentionNum == 1) {
        sNodeType* field_type2 = clone_node_type(field_type);

        field_type2->mArrayDimentionNum = 0;
        field_type2->mPointerNum++;

        if(!cast_right_type_to_left_type(field_type2, &field_type, &llvm_value, info))
        {
            return FALSE;
        }
    }

    info->type = clone_node_type(field_type);

    dec_stack_ptr(1, info);
    push_value_to_stack_ptr(&llvm_value, info);

    return TRUE;
}

static BOOL compile_store_field(unsigned int node, sCompileInfo* info)
{
    char var_name[VAR_NAME_MAX];
    xstrncpy(var_name, gNodes[node].uValue.sStoreField.mVarName, VAR_NAME_MAX);

    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    if(!(left_type->mClass->mFlags & CLASS_FLAGS_STRUCT) && !(left_type->mClass->mFlags & CLASS_FLAGS_UNION)) {
        compile_err_msg(info, "This is not struct type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    LVALUE lvalue = *get_value_from_stack(-1);

    /// compile right node ///
    unsigned int rnode = gNodes[node].mRight;

    if(!compile(rnode, info)) {
        return FALSE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    LVALUE rvalue = *get_value_from_stack(-1);


    int field_index = get_field_index(left_type->mClass, var_name, NULL);

    if(field_index == -1) {
        compile_err_msg(info, "The field(%s) is not found", var_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* field_type = clone_node_type(left_type->mClass->mFields[field_index]);

    BOOL success_solve;
    if(!solve_generics(&field_type, left_type, &success_solve)) {
        compile_err_msg(info, "Can't solve generics types(11)");
        show_node_type(field_type);
        show_node_type(left_type);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(auto_cast_posibility(field_type, right_type)) {
        if(!cast_right_type_to_left_type(field_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }
    
    if(!substitution_posibility(field_type, right_type, FALSE)) {
        compile_err_msg(info, "The different type between left type and right type. store field");
        show_node_type(field_type);
        show_node_type(right_type);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* left_type2 = clone_node_type(left_type);
    left_type2->mPointerNum = 0;

    Type* llvm_struct_type;
    if(!create_llvm_type_from_node_type(&llvm_struct_type, left_type2, left_type2, info))
    {
        compile_err_msg(info, "Getting llvm type failed(11)");
        show_node_type(left_type2);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    Type* llvm_field_type;
    if(!create_llvm_type_from_node_type(&llvm_field_type, field_type, field_type, info))
    {
        compile_err_msg(info, "Getting llvm type failed(12)");
        show_node_type(field_type);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    int alignment = get_llvm_alignment_from_node_type(field_type);

    Value* field_address;

    if(left_type->mClass->mFlags & CLASS_FLAGS_UNION) {
        if(left_type->mPointerNum == 0) {
            field_address = Builder.CreateCast(Instruction::BitCast, lvalue.address, PointerType::get(llvm_field_type, 0));
        }
        else {
            field_address = Builder.CreateCast(Instruction::BitCast, lvalue.value, PointerType::get(llvm_field_type, 0));
        }
    }
    else {
        if(left_type->mPointerNum == 0) {
#if LLVM_VERSION_MAJOR >= 7
            field_address = Builder.CreateStructGEP(lvalue.address, field_index);
#else
            field_address = Builder.CreateStructGEP(llvm_struct_type, lvalue.address, field_index);
#endif
        }
        else {
#if LLVM_VERSION_MAJOR >= 7
            field_address = Builder.CreateStructGEP(lvalue.value, field_index);
#else
            field_address = Builder.CreateStructGEP(llvm_struct_type, lvalue.value, field_index);
#endif
        }
    }

    Value* rvalue2 = rvalue.value;

    BOOL alloc = FALSE;
    std_move(field_address, field_type, &rvalue, alloc, info);

    Builder.CreateAlignedStore(rvalue2, field_address, alignment);

    info->type = right_type;

    dec_stack_ptr(2, info);
    push_value_to_stack_ptr(&rvalue, info);

    return TRUE;
}

static BOOL compile_and_and(unsigned int node, sCompileInfo* info)
{
    sFunction* fun = (sFunction*)info->function;

    Function* llvm_function = fun->mLLVMFunction;

    Value* result_var = (Value*)info->andand_result_var;

    /// compile expression ///
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE conditional_value = *get_value_from_stack(-1);

    sNodeType* bool_type = create_node_type_with_class_name("bool");

    if(auto_cast_posibility(bool_type, left_type)) {
        if(!cast_right_type_to_left_type(bool_type, &left_type, &conditional_value, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }
    }

    if(!type_identify_with_class_name(left_type, "bool")) {
        compile_err_msg(info, "Left expression is not bool type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    Builder.CreateAlignedStore(conditional_value.value, result_var, 1);

    BasicBlock* cond_then_block = BasicBlock::Create(TheContext, "cond_jump_then", llvm_function);

    BasicBlock* cond_end_block = BasicBlock::Create(TheContext, "cond_jump_end", llvm_function);

    free_right_value_objects(info);

    Builder.CreateCondBr(conditional_value.value, cond_then_block, cond_end_block);

    BasicBlock* current_block_before;
    llvm_change_block(cond_then_block, &current_block_before, info, FALSE);

    /// compile right expression ///
    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE conditional_value2 = *get_value_from_stack(-1);

    if(auto_cast_posibility(bool_type, right_type)) {
        if(!cast_right_type_to_left_type(bool_type, &right_type, &conditional_value2, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }
    }

    if(!type_identify_with_class_name(right_type, "bool")) {
        compile_err_msg(info, "Right expression is not bool type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    Value* andand_value = Builder.CreateAnd(conditional_value.value, conditional_value2.value, "andand");

    Builder.CreateAlignedStore(andand_value, result_var, 1);

    free_right_value_objects(info);
    Builder.CreateBr(cond_end_block);

    BasicBlock* current_block_before2;
    llvm_change_block(cond_end_block, &current_block_before2, info, FALSE);

    dec_stack_ptr(2, info);

    LVALUE llvm_value;
    llvm_value.value = Builder.CreateAlignedLoad(result_var, 1, "andand_result_value");
    llvm_value.type = create_node_type_with_class_name("bool");
    llvm_value.address = result_var;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}


static BOOL compile_or_or(unsigned int node, sCompileInfo* info)
{
    sFunction* fun = (sFunction*)info->function;

    Function* llvm_function = fun->mLLVMFunction;

    Value* result_var = (Value*)info->oror_result_var;

    /// compile expression ///
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE conditional_value = *get_value_from_stack(-1);

    sNodeType* bool_type = create_node_type_with_class_name("bool");

    if(auto_cast_posibility(bool_type, left_type)) {
        if(!cast_right_type_to_left_type(bool_type, &left_type, &conditional_value, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }
    }

    if(!type_identify_with_class_name(left_type, "bool")) {
        compile_err_msg(info, "Right expression is not bool type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    Builder.CreateAlignedStore(conditional_value.value, result_var, 1);

    BasicBlock* cond_then_block = BasicBlock::Create(TheContext, "cond_jump_then", llvm_function);

    BasicBlock* cond_end_block = BasicBlock::Create(TheContext, "cond_jump_end", llvm_function);;

    free_right_value_objects(info);

    Builder.CreateCondBr(conditional_value.value, cond_end_block, cond_then_block);

    BasicBlock* current_block_before;
    llvm_change_block(cond_then_block, &current_block_before, info, FALSE);

    /// compile right expression ///
    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE conditional_value2 = *get_value_from_stack(-1);

    if(auto_cast_posibility(bool_type, right_type)) {
        if(!cast_right_type_to_left_type(bool_type, &right_type, &conditional_value2, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }
    }

    if(!type_identify_with_class_name(right_type, "bool")) {
        compile_err_msg(info, "Right expression is not bool type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    Value* oror_value = Builder.CreateOr(conditional_value.value, conditional_value2.value, "oror");

    Builder.CreateAlignedStore(oror_value, result_var, 1);

    free_right_value_objects(info);
    Builder.CreateBr(cond_end_block);

    BasicBlock* current_block_before2;
    llvm_change_block(cond_end_block, &current_block_before2, info, FALSE);

    dec_stack_ptr(2, info);

    LVALUE llvm_value;
    llvm_value.value = Builder.CreateAlignedLoad(result_var, 1, "oror_result_value");
    llvm_value.type = create_node_type_with_class_name("bool");
    llvm_value.address = result_var;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("bool");

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

        case kNodeTypeTrue:
            if(!compile_true(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeFalse:
            if(!compile_false(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeCreateObject:
            if(!compile_create_object(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeClone:
            if(!compile_clone(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeStruct:
            if(!compile_struct(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeUnion:
            if(!compile_union(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeDefineVariable:
            if(!compile_define_variable(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeEquals:
            if(!compile_equals(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeNotEquals:
            if(!compile_not_equals(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLoadField:
            if(!compile_load_field(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeStoreField:
            if(!compile_store_field(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeAndAnd:
            if(!compile_and_and(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeOrOr:
            if(!compile_or_or(node, info)) {
                return FALSE;
            }
            break;
    }
    

    return TRUE;
}

