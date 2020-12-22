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
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/Passes/PassBuilder.h"
//#include "/usr/include/llvm/Transforms/Utils/Cloning.h"

#if LLVM_VERSION_MAJOR >= 4
#include "llvm/Bitcode/BitcodeWriter.h"
#else
#include "llvm/Bitcode/ReaderWriter.h"
//#include "llvm/Assembly/PrintModulePass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Pass.h"
#endif


//#include "llvm/Module.h"
//#include "llvm/Function.h"

using namespace llvm;

//#include "llvm/IR/LegacyPassManager.h"
//#include "llvm/IR/DerivedTypes.h"
//#include "llvm/Support/raw_ostream.h"
//#include "llvm/ExecutionEngine/Orc/LambdaResolver.h"
//#include "llvm/Transforms/Scalar.h"
//#include "llvm/ADT/iterator_range.h"
//#include "llvm/ADT/STLExtras.h"
//#include "llvm/ExecutionEngine/JITSymbol.h"
//#include "llvm/ExecutionEngine/RTDyldMemoryManager.h"
//#include "llvm/ExecutionEngine/RuntimeDyld.h"
//#include "llvm/ExecutionEngine/SectionMemoryManager.h"
//#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
//#include "llvm/ExecutionEngine/Orc/IRCompileLayer.h"
//#include "llvm/IR/DataLayout.h"
//#include "llvm/IR/Mangler.h"
#include "llvm/Support/FileSystem.h"
//#include "llvm/Support/SourceMgr.h"
//#include "llvm/Support/MemoryBuffer.h"
//#include "llvm/Support/DynamicLibrary.h"
/*
#if LLVM_VERSION_MAJOR == 3
#include "llvm/ExecutionEngine/Orc/ObjectLinkingLayer.h"
#endif
#include "llvm/Target/TargetMachine.h"
#include "llvm-c/BitWriter.h"
#include "llvm/IRReader/IRReader.h"
#if LLVM_VERSION_MAJOR == 3
#include "llvm/Bitcode/ReaderWriter.h"
#endif
*/


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

struct DebugInfo {
    DICompileUnit* TheCU;
    DIType* DblTy;
    std::vector<DIScope*> LexicalBlock;

};

DebugInfo KSDbgInfo;

DIBuilder* DBuilder;

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
    sVarTable* mLVTable;
};

typedef sFunctionStruct sFunction;

std::map<std::string, std::vector<sFunction>> gFuncs;

struct sRightHeapValueStruct {
    sNodeType* mNodeType;
    int mFlag;
    Value* mVariableValue;
};

typedef struct sRightHeapValueStruct sRightHeapValue;

///////////////////////////////////////////////////////////////////////
// debug
///////////////////////////////////////////////////////////////////////
static void emitLocaltion(DebugInfo* info, int sline)
{
    Builder.SetCurrentDebugLocation(DebugLoc());

    DIScope* scope;

    if(info->LexicalBlock.empty()) {
        scope = info->TheCU;
    }
    else {
        scope = info->LexicalBlock.back();
    }

    Builder.SetCurrentDebugLocation(DebugLoc::get(sline, 0, scope));
}

void setCurrentDebugLocation(int sline)
{
    emitLocaltion(&KSDbgInfo, sline);
}

static DIType* create_debug_type(sNodeType* node_type) 
{

#if LLVM_VERSION_MAJOR >= 5
    DIType* result = nullptr;
    
    if(node_type->mPointerNum > 0) {
        result = DBuilder->createBasicType("pointer", 64, dwarf::DW_ATE_address);
    }
    else if(node_type->mArrayDimentionNum > 0) {
        result = DBuilder->createBasicType("pointer", 64, dwarf::DW_ATE_address);
    }
    else if(type_identify_with_class_name(node_type, "int")) {
        result = DBuilder->createBasicType("int", 32, dwarf::DW_ATE_signed);
    }
    else if(type_identify_with_class_name(node_type, "char")) {
        result = DBuilder->createBasicType("char", 8, dwarf::DW_ATE_signed);
    }
    else if(type_identify_with_class_name(node_type, "short")) {
        result = DBuilder->createBasicType("short", 16, dwarf::DW_ATE_signed);
    }
    else if(type_identify_with_class_name(node_type, "long")) {
        result = DBuilder->createBasicType("long", 64, dwarf::DW_ATE_signed);
    }
    else if(type_identify_with_class_name(node_type, "float")) {
        result = DBuilder->createBasicType("float", 32, dwarf::DW_ATE_float);
    }
    else if(type_identify_with_class_name(node_type, "_Float16") || type_identify_with_class_name(node_type, "_Float16x")) 
    {
        result = DBuilder->createBasicType("float", 16, dwarf::DW_ATE_float);
    }
    else if(type_identify_with_class_name(node_type, "_Float32") || type_identify_with_class_name(node_type, "_Float32x")) 
    {
        result = DBuilder->createBasicType("float", 32, dwarf::DW_ATE_float);
    }
    else if(type_identify_with_class_name(node_type, "_Float64") || type_identify_with_class_name(node_type, "_Float64x")) 
    {
        result = DBuilder->createBasicType("float", 64, dwarf::DW_ATE_float);
    }
    else if(type_identify_with_class_name(node_type, "_Float128") || type_identify_with_class_name(node_type, "_Float128x")) 
    {
        result = DBuilder->createBasicType("float", 128, dwarf::DW_ATE_float);
    }
else {
result = DBuilder->createBasicType("int", 32, dwarf::DW_ATE_lo_user);
}

    return result;
#else 
    DIType* result = nullptr;
    
    if(node_type->mPointerNum > 0) {
        result = DBuilder->createBasicType("pointer", 64, 8, dwarf::DW_ATE_address);
    }
    else if(node_type->mArrayDimentionNum > 0) {
        result = DBuilder->createBasicType("pointer", 64, 8, dwarf::DW_ATE_address);
    }
    else if(type_identify_with_class_name(node_type, "int")) {
        result = DBuilder->createBasicType("int", 32, 4, dwarf::DW_ATE_signed);
    }
    else if(type_identify_with_class_name(node_type, "char")) {
        result = DBuilder->createBasicType("char", 8, 4, dwarf::DW_ATE_signed);
    }
    else if(type_identify_with_class_name(node_type, "short")) {
        result = DBuilder->createBasicType("short", 16, 4, dwarf::DW_ATE_signed);
    }
    else if(type_identify_with_class_name(node_type, "long")) {
        result = DBuilder->createBasicType("long", 64, 8, dwarf::DW_ATE_signed);
    }
    else if(type_identify_with_class_name(node_type, "float")) {
        result = DBuilder->createBasicType("float", 32, 4, dwarf::DW_ATE_float);
    }
else {
result = DBuilder->createBasicType("int", 32, 4, dwarf::DW_ATE_lo_user);
}

    return result;
#endif
}

static DISubroutineType* createDebugFunctionType(sFunction* function, DIFile* unit)
{
    SmallVector<Metadata *, 8> EltTys;

    sNodeType* result_type = create_node_type_with_class_name(function->mResultTypeName);

    DIType* debug_result_type = create_debug_type(result_type);

    EltTys.push_back(debug_result_type);

    for(int i = 0; i<function->mNumParams; i++) {
        sNodeType* arg_type = create_node_type_with_class_name(function->mParamTypes[i]);
        DIType* debug_arg_type = create_debug_type(result_type);

        EltTys.push_back(debug_arg_type);
    }

    return DBuilder->createSubroutineType(DBuilder->getOrCreateTypeArray(EltTys));
}

void createDebugFunctionInfo(int sline, const char* fun_name, sFunction* function, Function* llvm_function)
{
    DebugInfo* info = &KSDbgInfo;

    DIFile* unit = DBuilder->createFile(KSDbgInfo.TheCU->getFilename()
                    , KSDbgInfo.TheCU->getDirectory());

    std::string fun_name2 = fun_name;
    std::string linkage_name = fun_name;

    DISubroutineType* subrouting_type 
        = createDebugFunctionType(function, unit);

//    DITemplateParameterArray retained_nodes = subrouting_type->getTemplateParams();

#if LLVM_VERSION_MAJOR >= 9
    DISubprogram* sp = DBuilder->createFunction(
        unit, fun_name2, linkage_name, unit, sline
        , subrouting_type, sline);
#else
    DISubprogram* sp = DBuilder->createFunction(
        unit, fun_name2, linkage_name, unit, sline
        , subrouting_type, false, true, sline
        , llvm::DINode::DIFlags::FlagAccessibility, false, nullptr);
#endif

    llvm_function->setSubprogram(sp);

    KSDbgInfo.LexicalBlock.push_back(sp);

    emitLocaltion(&KSDbgInfo, sline);
}

void finishDebugFunctionInfo()
{
    KSDbgInfo.LexicalBlock.pop_back();
}

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

static void solve_method_generics2(sNodeType** node_type, char** method_generics_types);

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

            solve_method_generics2(&field, info->method_generics_types);

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

            solve_method_generics2(&field, info->method_generics_types);

            BOOL success_solve;
            (void)solve_generics(&field, field, &success_solve);

            solve_method_generics2(&field, info->method_generics_types);

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

static void create_undefined_llvm_struct_type(sNodeType* node_type)
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

        std::pair<Type*, sNodeType*> pair_value;
        pair_value.first = struct_type;
        pair_value.second = clone_node_type(node_type);
        pair_value.second->mNumFields = node_type->mClass->mNumFields;

        gLLVMStructType[real_struct_name] = pair_value;

        klass->mUndefinedStructType = struct_type;
    }
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

                solve_method_generics2(&field, info->method_generics_types);

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

                solve_method_generics2(&field, info->method_generics_types);

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
        return FALSE;
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
            else if(type_identify_with_class_name(*right_type, "bool")) {
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

static BOOL entry_llvm_function(sFunction* fun, sNodeType* generics_type, sCompileInfo* info, Function** llvm_fun)
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

    for(int i=0; i<num_params; i++) {
        xstrncpy(param_types[i], fun->mParamTypes[i], VAR_NAME_MAX);
        xstrncpy(param_names[i], fun->mParamNames[i], VAR_NAME_MAX);
    }


    sNodeType* result_type = create_node_type_with_class_name(result_type_name);

    if(result_type == NULL || result_type->mClass == NULL) {
        return FALSE;
    }

    BOOL success_solve;
    (void)solve_generics(&result_type, generics_type, &success_solve);

    solve_method_generics2(&result_type, info->method_generics_types);

    Type* llvm_result_type;
    if(!create_llvm_type_from_node_type(&llvm_result_type, result_type, result_type, info))
    {
        return TRUE;
    }

    std::vector<Type *> llvm_param_types;

    int i;
    for(i=0; i<num_params; i++) {
        sNodeType* param_type = create_node_type_with_class_name(param_types[i]);

        if(param_type == NULL || param_type->mClass == NULL) {
            return FALSE;
        }

        BOOL success_solve;
        (void)solve_generics(&param_type, generics_type, &success_solve);

        solve_method_generics2(&param_type, info->method_generics_types);

        Type* llvm_param_type;
        if(!create_llvm_type_from_node_type(&llvm_param_type, param_type, param_type, info))
        {
            return FALSE;
        }

        if(type_identify_with_class_name(param_type, "__builtin_va_list")) {
            llvm_param_type = PointerType::get(llvm_param_type, 0);
        }

        llvm_param_types.push_back(llvm_param_type);
    }

    if(inline_ || static_) {
        FunctionType* function_type = FunctionType::get(llvm_result_type, llvm_param_types, var_arg);
        *llvm_fun = Function::Create(function_type, Function::InternalLinkage, fun_name, TheModule);
        fun->mLLVMFunction = *llvm_fun;
    }
    else {
        FunctionType* function_type = FunctionType::get(llvm_result_type, llvm_param_types, var_arg);
        *llvm_fun = Function::Create(function_type, Function::ExternalLinkage, fun_name, TheModule);
        fun->mLLVMFunction = *llvm_fun;
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


BOOL add_function(char* fun_name, char* fun_base_name, char* result_type_name, int num_params, char** param_types, char** param_names, BOOL var_arg, BOOL inline_, BOOL inherit_, BOOL static_, unsigned int node_block, BOOL generics, BOOL coroutine, BOOL method_generics, sVarTable* lv_table, sCompileInfo* info)
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
    if(lv_table) {
        fun.mLVTable = clone_var_table(lv_table);
    }
    else {
        fun.mLVTable = NULL;
    }

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

            Function* llvm_fun = NULL;
            if(!entry_llvm_function(&fun, info->generics_type, info, &llvm_fun)) {
                return FALSE;
            }

            gFuncs[fun_name].push_back(fun);
        }
        else {
            Function* llvm_fun = NULL;
            if(!entry_llvm_function(&fun, info->generics_type, info, &llvm_fun)) {
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
    info->right_value_objects = (void*)new std::map<Value*, sRightHeapValueStruct>;

    return result;
}

void restore_right_value_objects_container(void* right_value_objects, sCompileInfo* info)
{
    info->right_value_objects = right_value_objects;
}

static void convert_type_to_struct_name(sNodeType* node_type, char* type_name2)
{
    if(strcmp(node_type->mClass->mName, "char") == 0 && node_type->mPointerNum == 1 && node_type->mHeap) {
        xstrncpy(type_name2, "string", VAR_NAME_MAX);
    }
    else if(strcmp(node_type->mClass->mName, "int") == 0 && node_type->mPointerNum == 1 && node_type->mHeap) {
        xstrncpy(type_name2, "wstring", VAR_NAME_MAX);
    }
    else {
        xstrncpy(type_name2, node_type->mClass->mName, VAR_NAME_MAX);

        if(node_type->mClass->mFlags & CLASS_FLAGS_NUMBER) {
            int i;
            for(i=0; i<node_type->mPointerNum; i++) {
                xstrncat(type_name2, "p", VAR_NAME_MAX);
            }
        }
    }
}

static BOOL create_generics_function(char* id, char* fun_name, sCLClass* klass, sFunction* fun, char* real_fun_name2, sCompileInfo* info, int sline, BOOL pre_compile, BOOL inherit_) ;

static BOOL call_destructor(Value* obj, sNodeType* node_type, sCompileInfo* info)
{
    //LVALUE* llvm_stack = gLLVMStack;
    //int stack_num_before = info->stack_num;
    //sNodeType* info_type_before = info->type;

    if(node_type->mNumGenericsTypes > 0) 
    {
        sCLClass* klass = node_type->mClass;
        char* id = "finalize";
        char* fun_name = "finalize";

        char real_fun_name[VAR_NAME_MAX];

        char type_name2[VAR_NAME_MAX];
        convert_type_to_struct_name(node_type, type_name2);

        xstrncpy(real_fun_name, type_name2, VAR_NAME_MAX);
        xstrncat(real_fun_name, "_", VAR_NAME_MAX);
        xstrncat(real_fun_name, fun_name, VAR_NAME_MAX);

        if(gFuncs[real_fun_name].size() == 0) {
            return TRUE;
        }

        sFunction fun = gFuncs[real_fun_name][gFuncs[real_fun_name].size()-1];

        char real_fun_name2[VAR_NAME_MAX];

        int sline = yylineno;

        sNodeType* generics_type = info->generics_type;
        info->generics_type = clone_node_type(node_type);

        BOOL pre_compile = TRUE;
        BOOL inherit_ = FALSE;
        if(!create_generics_function(id, fun_name, klass, &fun, real_fun_name2, info, sline, pre_compile, inherit_))
        {
            return FALSE;
        }

        info->generics_type = generics_type;

        Function* llvm_fun = TheModule->getFunction(real_fun_name2);

        if(llvm_fun == nullptr) {
            return TRUE;
        }

        std::vector<Value*> llvm_params;
        Value* param = obj;

        llvm_params.push_back(param);

        Builder.CreateCall(llvm_fun, llvm_params);
    }
    else {
        char finalize_method_name[VAR_NAME_MAX];

        char struct_name[VAR_NAME_MAX];

        convert_type_to_struct_name(node_type, struct_name);

        snprintf(finalize_method_name, VAR_NAME_MAX, "%s_finalize", struct_name);

        Function* llvm_fun = TheModule->getFunction(finalize_method_name);

        if(llvm_fun == nullptr) {
            return FALSE;
        }

        std::vector<Value*> llvm_params;
        Value* param = obj;

        llvm_params.push_back(param);

        Builder.CreateCall(llvm_fun, llvm_params);
    }

    //info->stack_num = stack_num_before;
    //gLLVMStack = llvm_stack;
    //info->type = info_type_before;

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

        solve_method_generics2(&field_type, info->method_generics_types);

        sCLClass* field_class = field_type->mClass;

        if(field_type->mHeap && field_type->mPointerNum > 0)
        {
            if(type_identify(node_type, field_type)) {
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

Value* llvm_create_string(char* str);

static void free_right_value_object(sNodeType* node_type, void* obj, BOOL force_delete, sCompileInfo* info)
{
    BOOL exist_recursive_field = FALSE;

    Value* obj2 = (Value*)obj;

    sCLClass* klass = node_type->mClass;

    sNodeType* node_type2 = clone_node_type(node_type);
    node_type2->mPointerNum = 0;

    if(info->generics_type) {
        BOOL success_solve;
        if(!solve_generics(&node_type2, info->generics_type, &success_solve))
        {
            fprintf(stderr, "%s %d: The error at solve_generics\n", info->sname, info->sline);
            return;
        }

        solve_method_generics2(&node_type2, info->method_generics_types);

        if(!solve_generics(&node_type, info->generics_type, &success_solve))
        {
            fprintf(stderr, "%s %d: The error at solve_generics\n", info->sname, info->sline);
            return;
        }

        solve_method_generics2(&node_type, info->method_generics_types);
    }

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

        solve_method_generics2(&field_type, info->method_generics_types);
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

                sNodeType* generics_type = info->generics_type;
                info->generics_type = clone_node_type(node_type);

                if(!call_destructor(obj2, node_type, info)) {
                    fprintf(stderr, "%s %d: can't make finalize of recursive field(3)(%s)\n", info->sname, info->sline, node_type->mClass->mName);
                    exit(2);
                }

                info->generics_type = generics_type;
            }
            else {
                sNodeType* generics_type = info->generics_type;
                info->generics_type = clone_node_type(node_type);

                call_destructor(obj2, node_type, info);
                call_field_destructor(obj2, node_type, info);

                info->generics_type = generics_type;
            }
        }
    }

    /// free ///
    if((force_delete || node_type->mHeap ) && node_type->mPointerNum > 0 && !info->no_output) 
    {
        Function* fun = TheModule->getFunction("ncfree");

        if(fun == nullptr) {
            fprintf(stderr, "require free\n");
            exit(2);
        }

        std::vector<Value*> params2;
        Value* param = Builder.CreateCast(Instruction::BitCast, obj2, PointerType::get(IntegerType::get(TheContext, 8), 0));
        params2.push_back(param);

        Value* param2 = llvm_create_string(node_type->mClass->mName);
        params2.push_back(param2);

        Builder.CreateCall(fun, params2);
    }

    std::map<Value*, sRightHeapValueStruct>* right_value_objects = (std::map<Value*, sRightHeapValueStruct>*)info->right_value_objects;
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
        std::map<Value*, sRightHeapValueStruct>* right_value_objects = (std::map<Value*, sRightHeapValueStruct>*)info->right_value_objects;
        if(right_value_objects->count(rvalue->value) > 0)
        {
            right_value_objects->erase(rvalue->value);
        }
    }
}

void free_right_value_objects(sCompileInfo* info)
{
    if(info->no_output) {
        return;
    }

    if(info->right_value_objects) {
        std::map<Value*, sRightHeapValue>* right_value_objects = (std::map<Value*, sRightHeapValue>*)info->right_value_objects;

        std::map<Value*, sRightHeapValue> old_heap_objects(*right_value_objects);

        right_value_objects->clear();

        for(std::pair<Value*, sRightHeapValue> it: old_heap_objects) 
        {
            sNodeType* node_type = it.second.mNodeType;
            int flag = it.second.mFlag;
            Value* variable_value = it.second.mVariableValue;

            int alignment = get_llvm_alignment_from_node_type(node_type);

            Value* address = Builder.CreateAlignedLoad(variable_value, alignment);

//            Value* address = it.first;

            if(flag <= 0) {
                free_right_value_object(node_type, address, FALSE, info);
            }
            else {
                flag--;

                sRightHeapValue right_heap_value;

                right_heap_value.mNodeType = clone_node_type(node_type);
                right_heap_value.mFlag = flag;
                right_heap_value.mVariableValue = variable_value;

                (*right_value_objects)[address] = right_heap_value;
            }
        }
    }
}

void remove_from_right_value_object(Value* value, sCompileInfo* info)
{
    std::map<Value*, sRightHeapValue>* right_value_objects = (std::map<Value*, sRightHeapValue>*)info->right_value_objects;
    if(right_value_objects->count(value) > 0)
    {
        right_value_objects->erase(value);
    }
}

void append_heap_object_to_right_value(LVALUE* llvm_value, sCompileInfo* info)
{
    if(llvm_value->type->mHeap) {
        std::map<Value*, sRightHeapValue>* right_value_objects = (std::map<Value*, sRightHeapValue>*)info->right_value_objects;

        if(right_value_objects->count(llvm_value->value) == 0)
        {
            int flg = (*right_value_objects)[llvm_value->value].mFlag;

            flg = 1;

            sNodeType* node_type = clone_node_type(llvm_value->type);

            Type* llvm_type;
            (void)create_llvm_type_from_node_type(&llvm_type, node_type, node_type, info);

            BasicBlock* entry_block = (BasicBlock*)info->entry_block;

            BasicBlock* current_block = Builder.GetInsertBlock();
            BasicBlock::iterator current_point = Builder.GetInsertPoint();

            BasicBlock::iterator point = entry_block->getFirstInsertionPt();
            Builder.SetInsertPoint(entry_block, point);

            static int n = 0;
            char name[128];
            snprintf(name, 128, "right_heap_value%d", n++);

            Value* variable_value = Builder.CreateAlloca(llvm_type, 0, name);
            
            Builder.SetInsertPoint(current_block, current_point);

            int alignment = get_llvm_alignment_from_node_type(node_type);

            Builder.CreateAlignedStore(llvm_value->value, variable_value, alignment);

            sRightHeapValue right_heap_value;

            right_heap_value.mNodeType = clone_node_type(llvm_value->type);
            right_heap_value.mFlag = 0;
            right_heap_value.mVariableValue = variable_value;

            (*right_value_objects)[llvm_value->value] = right_heap_value;
        }
    }
}

void free_objects(sVarTable* table, Value* inhibit_free_object_address, sCompileInfo* info)
{
    if(info->no_output) {
        return;
    }

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
    if(info->no_output) {
        return;
    }

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

void free_objects_until_loop_top(Value* inhibit_free_object_address, sCompileInfo* info)
{
    if(info->no_output) {
        return;
    }

    sVarTable* it = info->lv_table;

    while(it != NULL) 
    {
        if(info->loop_top_lv_table == it) {
            break;
        }

        free_objects(it, inhibit_free_object_address, info);

        it = it->mParent;
    }
}

static BOOL call_clone_method(sNodeType* node_type, Value** address, sCompileInfo* info)
{
    Value* obj = Builder.CreateAlignedLoad(*address, 8);

    char type_name2[VAR_NAME_MAX];
    convert_type_to_struct_name(node_type, type_name2);

    char real_fun_name[REAL_FUN_NAME_MAX];

    xstrncpy(real_fun_name, type_name2, VAR_NAME_MAX);
    xstrncat(real_fun_name, "_", VAR_NAME_MAX);
    xstrncat(real_fun_name, "clone", VAR_NAME_MAX);

    std::vector<sFunction>& funcs = gFuncs[real_fun_name];

    if(funcs.size() > 0) {
        if(node_type->mNumGenericsTypes > 0) 
        {
            sFunction fun = gFuncs[real_fun_name][gFuncs[real_fun_name].size()-1];

            char real_fun_name2[VAR_NAME_MAX];

            int sline = yylineno;

            sCLClass* klass = node_type->mClass;
            char* id = "clone";
            char* fun_name = "clone";

            sNodeType* generics_type = info->generics_type;
            info->generics_type = node_type;

            BOOL pre_compile = TRUE;
            BOOL inherit_ = FALSE;
            if(!create_generics_function(id, fun_name, klass, &fun, real_fun_name2, info, sline, pre_compile, inherit_))
            {
                return FALSE;
            }

            info->generics_type = generics_type;

            Function* fun2 = TheModule->getFunction(real_fun_name2);

            if(fun2 == nullptr) {
                compile_err_msg(info, "require %s\n", real_fun_name2);
                return FALSE;
            }

            std::vector<Value*> llvm_params;
            Value* param = obj;
            llvm_params.push_back(param);

            Value* address2 = Builder.CreateCall(fun2, llvm_params);

            *address = address2;

            remove_from_right_value_object(*address, info);

            return TRUE;
        }
        else {
            Function* fun = funcs[funcs.size()-1].mLLVMFunction;

            if(fun == nullptr) {
                compile_err_msg(info, "require %s\n", real_fun_name);
                return FALSE;
            }

            std::vector<Value*> llvm_params;
            Value* param = obj;
            llvm_params.push_back(param);

            Value* address2 = Builder.CreateCall(fun, llvm_params);

            *address = address2;

            remove_from_right_value_object(*address, info);

            return TRUE;
        }
    }

    return FALSE;
}

Value* clone_object(sNodeType* node_type, Value* address, sCompileInfo* info)
{
    sCLClass* klass = node_type->mClass;

    Value* obj = Builder.CreateAlignedLoad(address, 8);

    if(node_type->mPointerNum == 0) {
        return obj;
    }

    sNodeType* generics_type = info->generics_type;
    info->generics_type = clone_node_type(node_type);

    BOOL execute_clone_method = call_clone_method(node_type, &address, info);

    info->generics_type = generics_type;

    if(execute_clone_method) {
        return address;
    }

    /// memdup ///
    Function* fun = TheModule->getFunction("ncmemdup");

    if(fun == nullptr) {
        compile_err_msg(info, "require ncmemdup for clone\n");
        return FALSE;
    }

    std::vector<Value*> params2;

    Value* param = Builder.CreateCast(Instruction::BitCast, obj, PointerType::get(IntegerType::get(TheContext, 8), 0));
    params2.push_back(param);

    Value* address2 = Builder.CreateCall(fun, params2);

    LVALUE rvalue2;
    rvalue2.value = address2;
    rvalue2.type = create_node_type_with_class_name("void*");
    rvalue2.address = nullptr;
    rvalue2.var = nullptr;
    rvalue2.binded_value = FALSE;
    rvalue2.load_field = FALSE;

    if(!cast_right_type_to_left_type(node_type, &rvalue2.type, &rvalue2, info))
    {
        compile_err_msg(info, "can't clone this value");
        return FALSE;
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

    return address3;
}

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

    TheModule->addModuleFlag(Module::Warning, "Debug Info Version", DEBUG_METADATA_VERSION);
    TheModule->addModuleFlag(llvm::Module::Warning, "Dwarf Version", 2);

    const char* cwd = getenv("PWD");

    if(cwd == NULL) {
        cwd = ".";
    }

    if(gNCDebug) {
        DBuilder = new DIBuilder(*TheModule);

#if LLVM_VERSION_MAJOR >= 5
        KSDbgInfo.TheCU = DBuilder->createCompileUnit(
            dwarf::DW_LANG_C, DBuilder->createFile(gSNameOriginal, cwd), "neo-c2", 0, "", 0);
#else
        KSDbgInfo.TheCU = DBuilder->createCompileUnit(
            dwarf::DW_LANG_C, gSName, cwd, "neo-c", false, "", 0);
#endif
    }

#if LLVM_VERSION_MAJOR <= 9
    TheFPM = llvm::make_unique<FunctionPassManager>(TheModule);
#else
    TheFPM = std::make_unique<FunctionPassManager>(TheModule);
#endif
}

static void output_native_code()
{
    if(gNCDebug) {
        DBuilder->finalize();
    }
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

void create_global_lvtable(sCompileInfo* info)
{
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

void declare_builtin_functions()
{
    Type* param1_type;
    Type* param2_type;
    Type* param3_type;
    Type* param4_type;
    Type* param5_type;
    Type* param6_type;
    Type* param7_type;
    Type* param8_type;
    Type* param9_type;
    Type* result_type;

    std::vector<Type *> params;

    FunctionType* function_type;

    /// va_list ///
    params.clear();

    StructType* struct_type = StructType::create(TheContext, "__builtin_va_list");

    std::vector<Type*> fields;
#ifdef __X86_64_CPU__
    param1_type = IntegerType::get(TheContext,32);
    fields.push_back(param1_type);

    param2_type = IntegerType::get(TheContext,32);
    fields.push_back(param2_type);

    param3_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    fields.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    fields.push_back(param4_type);

    if(struct_type->isOpaque()) {
        struct_type->setBody(fields, false);
    }
#else
    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    fields.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    fields.push_back(param2_type);

    param3_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    fields.push_back(param3_type);

    param4_type = IntegerType::get(TheContext,32);
    fields.push_back(param4_type);

    param5_type = IntegerType::get(TheContext,32);
    fields.push_back(param5_type);

    if(struct_type->isOpaque()) {
        struct_type->setBody(fields, false);
    }
#endif

    sCLClass* va_list_struct = alloc_struct("__builtin_va_list", FALSE);

    int num_fields = 1;
    sNodeType* field;

    const char* field_name = "field";
    field = create_node_type_with_class_name("char*");

    add_field_to_struct(va_list_struct, field_name, field);

    sCLClass* builtin_va_list_struct = alloc_struct("__builtin_va_list", FALSE);

    add_field_to_struct(builtin_va_list_struct, field_name, field);

    sNodeType* node_type = create_node_type_with_class_pointer(va_list_struct);

    std::pair<Type*, sNodeType*> pair_value;

    pair_value.first = struct_type;
    pair_value.second = clone_node_type(node_type);

    gLLVMStructType["__builtin_va_list"] = pair_value;

    /// va_start ///
    params.clear();

    {
        char* param_types[PARAMS_MAX];
        char* param_names[PARAMS_MAX];

        char* result_type_name = "void";

        int num_params = 1;
        param_names[0] = "p";
        param_types[0] = "char*";

        BOOL var_arg = FALSE;
        BOOL inline_ = FALSE;
        BOOL inherit_ = FALSE;
        BOOL static_ = FALSE;
        BOOL generics = FALSE;
        BOOL coroutine = FALSE;
        BOOL method_generics = FALSE;
        add_function("llvm.va_start", "llvm.va_start", result_type_name, num_params, param_types, param_names, var_arg, inline_, inherit_, static_, 0, generics, coroutine, method_generics, NULL, &cinfo);
        add_function("__builtin_va_start", "__builtin_va_list", result_type_name, num_params, param_types, param_names, var_arg, inline_, inherit_, static_, 0, generics, coroutine, method_generics, NULL, &cinfo);
    }

    {
        char* param_types[PARAMS_MAX];
        char* param_names[PARAMS_MAX];

        char* result_type_name = "void";

        int num_params = 1;
        param_names[0] = "p";
        param_types[0] = "char*";

        BOOL var_arg = FALSE;
        BOOL inline_ = FALSE;
        BOOL inherit_ = FALSE;
        BOOL static_ = FALSE;
        BOOL generics = FALSE;
        BOOL coroutine = FALSE;
        BOOL method_generics = FALSE;
        add_function("llvm.va_end", "llvm.va_end", result_type_name, num_params, param_types, param_names, var_arg, inline_, inherit_, static_, 0, generics, coroutine, method_generics, NULL, &cinfo);
        add_function("__builtin_va_end", "__builtin_va_end", result_type_name, num_params, param_types, param_names, var_arg, inline_, inherit_, static_, 0, generics, coroutine, method_generics, NULL, &cinfo);
    }

    {
        char* param_types[PARAMS_MAX];
        char* param_names[PARAMS_MAX];

        char* result_type_name = "void";

        int num_params = 4;

        param_names[0] = "b1";
        param_types[0] = "char*";

        param_names[1] = "b2";
        param_types[1] = "char*";

        param_names[2] = "len";
/*
#ifdef __32BIT_CPU__
        param_types[2] = "int";
#else
*/
        param_types[2] = "long";
//#endif

        param_names[3] = "v";
        param_types[3] = "bool";

        BOOL var_arg = FALSE;
        BOOL inline_ = FALSE;
        BOOL inherit_ = FALSE;
        BOOL static_ = FALSE;
        BOOL generics = FALSE;
        BOOL coroutine = FALSE;
        BOOL method_generics = FALSE;
        add_function("__builtin_memmove", "__builtin_memmove", result_type_name, num_params, param_types, param_names, var_arg, inline_, inherit_, static_, 0, generics, coroutine, method_generics, NULL, &cinfo);
        add_function("llvm.memmove.p0i8.p0i8.i64", "llvm.memmove", result_type_name, num_params, param_types, param_names, var_arg, inline_, inherit_, static_, 0, generics, coroutine, method_generics, NULL, &cinfo);
    }
    {
        char* param_types[PARAMS_MAX];
        char* param_names[PARAMS_MAX];

        char* result_type_name = "void";

        int num_params = 4;

        param_names[0] = "b1";
        param_types[0] = "char*";

        param_names[1] = "b2";
        param_types[1] = "char*";

        param_names[2] = "len";
/*
#ifdef __32BIT_CPU__
        param_types[2] = "int";
#else
*/
        param_types[2] = "long";
//#endif

        param_names[3] = "v";
        param_types[3] = "bool";

        BOOL var_arg = FALSE;
        BOOL inline_ = FALSE;
        BOOL inherit_ = FALSE;
        BOOL static_ = FALSE;
        BOOL generics = FALSE;
        BOOL coroutine = FALSE;
        BOOL method_generics = FALSE;
        add_function("__builtin_memcpy", "__builtin_memcpy", result_type_name, num_params, param_types, param_names, var_arg, inline_, inherit_, static_, 0, generics, coroutine, method_generics, NULL, &cinfo);
        add_function("llvm.memcpy.p0i8.p0i8.i64", "llvm.memcpy", result_type_name, num_params, param_types, param_names, var_arg, inline_, inherit_, static_, 0, generics, coroutine, method_generics, NULL, &cinfo);
    }
    {
        char* param_types[PARAMS_MAX];
        char* param_names[PARAMS_MAX];

        char* result_type_name = "void";

        int num_params = 4;
        param_names[0] = "buf";
        param_types[0] = "char*";

        param_names[1] = "ch";
        param_types[1] = "char";

        param_names[2] = "n";
/*
#ifdef __32BIT_CPU__
        param_types[2] = "int";
#else
*/
        param_types[2] = "long";
//#endif

        param_names[3] = "v";
        param_types[3] = "bool";

        BOOL var_arg = FALSE;
        BOOL inline_ = FALSE;
        BOOL inherit_ = FALSE;
        BOOL static_ = FALSE;
        BOOL generics = FALSE;
        BOOL coroutine = FALSE;
        BOOL method_generics = FALSE;
        add_function("__builtin_memset", "__builtin_memset", result_type_name, num_params, param_types, param_names, var_arg, inline_, inherit_, static_, 0, generics, coroutine, method_generics, NULL, &cinfo);
        add_function("llvm.memset.p0i8.i64", "llvm.memset", result_type_name, num_params, param_types, param_names, var_arg, inline_, inherit_, static_, 0, generics, coroutine, method_generics, NULL, &cinfo);
    }

/*
    sCLClass* va_list_struct = alloc_struct("__builtin_va_list", FALSE);

    va_list_struct->setBody(fields, false);

    //add_field_to_struct(va_list_struct, field_name, field_type);

    sCLClass* klass = alloc_struct("__builtin_va_list", FALSE);

    sNodeType* field = create_node_type_with_class_name("char*");

    add_field_to_struct(klass, "a", field);

    field = create_node_type_with_class_name("char*");

    add_field_to_struct(klass, "b", field);

    field = create_node_type_with_class_name("char*");

    add_field_to_struct(klass, "c", field);

    field = create_node_type_with_class_name("int");

    add_field_to_struct(klass, "d", field);

    field = create_node_type_with_class_name("int");

    add_field_to_struct(klass, "e", field);
*/


/*

    sNodeType* node_type = create_node_type_with_class_pointer(va_list_struct);

    std::pair<Type*, sNodeType*> pair_value;

    pair_value.first = struct_type;
    pair_value.second = clone_node_type(node_type);

    gLLVMStructType["__builtin_va_list"] = pair_value;

    /// va_start ///
    params.clear();

    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    params.push_back(param1_type);
    {
        std::vector<Type *> llvm_param_types;
        sNodeType* param_types[PARAMS_MAX];
        char param_names[PARAMS_MAX][VAR_NAME_MAX];

        sNodeType* result_type = create_node_type_with_class_name("void");

        int num_params = 1;
        xstrncpy(param_names[0], "p", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("char*");

        BOOL var_arg = TRUE;

        char method_generics_type_names[GENERICS_TYPES_MAX][VAR_NAME_MAX];

        memset(method_generics_type_names, 0, sizeof(char)*GENERICS_TYPES_MAX*VAR_NAME_MAX);

        char generics_type_names[GENERICS_TYPES_MAX][VAR_NAME_MAX];

        memset(generics_type_names, 0, sizeof(char)*GENERICS_TYPES_MAX*VAR_NAME_MAX);

        Function* llvm_fun;
        sFunction* neo_c_fun = NULL;

        char* param_names2[PARAMS_MAX];
        int i;
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }
        char* method_generics_type_names2[GENERICS_TYPES_MAX];
        int num_method_generics = 0;
        for(i=0; i<num_method_generics; i++) {
            method_generics_type_names2[i] = method_generics_type_names[i];
        }
        char* generics_type_names2[GENERICS_TYPES_MAX];
        int num_generics = 0;
        for(i=0; i<num_generics; i++) {
            generics_type_names2[i] = generics_type_names[i];
        }
        add_function("llvm.va_start", "llvm.va_start", "", param_names2, param_types, num_params, result_type, 0, method_generics_type_names2, TRUE, var_arg, NULL, 0, generics_type_names2, FALSE, FALSE, NULL, 0, TRUE, TRUE, 0, &llvm_fun, NULL, FALSE, NULL, -1, "llvm.va_start", &neo_c_fun);
    }

    /// va_end ///
    params.clear();

    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    params.push_back(param1_type);

    {
        std::vector<Type *> llvm_param_types;
        sNodeType* param_types[PARAMS_MAX];
        char param_names[PARAMS_MAX][VAR_NAME_MAX];

        sNodeType* result_type = create_node_type_with_class_name("void");

        int num_params = 1;
        xstrncpy(param_names[0], "p", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("char*");

        BOOL var_arg = FALSE;

        char method_generics_type_names[GENERICS_TYPES_MAX][VAR_NAME_MAX];

        memset(method_generics_type_names, 0, sizeof(char)*GENERICS_TYPES_MAX*VAR_NAME_MAX);

        char generics_type_names[GENERICS_TYPES_MAX][VAR_NAME_MAX];

        memset(generics_type_names, 0, sizeof(char)*GENERICS_TYPES_MAX*VAR_NAME_MAX);

        Function* llvm_fun;
        sFunction* neo_c_fun = NULL;

        char* param_names2[PARAMS_MAX];
        int i;
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }
        char* method_generics_type_names2[GENERICS_TYPES_MAX];
        int num_method_generics = 0;
        for(i=0; i<num_method_generics; i++) {
            method_generics_type_names2[i] = method_generics_type_names[i];
        }
        char* generics_type_names2[GENERICS_TYPES_MAX];
        int num_generics = 0;
        for(i=0; i<num_generics; i++) {
            generics_type_names2[i] = generics_type_names[i];
        }
        add_function("llvm.va_end", "llvm.va_end", "", param_names2, param_types, num_params, result_type, 0, method_generics_type_names2, TRUE, var_arg, NULL, 0, generics_type_names2, FALSE, FALSE, NULL, 0, TRUE, TRUE, 0, &llvm_fun, NULL, FALSE, NULL, -1, "llvm.va_end", &neo_c_fun);
    }

    /// va_copy ///
    params.clear();

    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    params.push_back(param1_type);
    param2_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    params.push_back(param1_type);

    {
        std::vector<Type *> llvm_param_types;
        sNodeType* param_types[PARAMS_MAX];
        char param_names[PARAMS_MAX][VAR_NAME_MAX];

        sNodeType* result_type = create_node_type_with_class_name("void");

        int num_params = 2;
        xstrncpy(param_names[0], "p", VAR_NAME_MAX);
        xstrncpy(param_names[1], "p2", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("char*");
        param_types[1] = create_node_type_with_class_name("char*");

        BOOL var_arg = FALSE;

        char method_generics_type_names[GENERICS_TYPES_MAX][VAR_NAME_MAX];

        memset(method_generics_type_names, 0, sizeof(char)*GENERICS_TYPES_MAX*VAR_NAME_MAX);

        char generics_type_names[GENERICS_TYPES_MAX][VAR_NAME_MAX];

        memset(generics_type_names, 0, sizeof(char)*GENERICS_TYPES_MAX*VAR_NAME_MAX);

        Function* llvm_fun;
        sFunction* neo_c_fun = NULL;

        char* param_names2[PARAMS_MAX];
        int i;
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }
        char* method_generics_type_names2[GENERICS_TYPES_MAX];
        int num_method_generics = 0;
        for(i=0; i<num_method_generics; i++) {
            method_generics_type_names2[i] = method_generics_type_names[i];
        }
        char* generics_type_names2[GENERICS_TYPES_MAX];
        int num_generics = 0;
        for(i=0; i<num_generics; i++) {
            generics_type_names2[i] = generics_type_names[i];
        }
        add_function("llvm.va_copy", "llvm.va_copy", "", param_names2, param_types, num_params, result_type, 0, method_generics_type_names2, TRUE, var_arg, NULL, 0, generics_type_names2, FALSE, FALSE, NULL, 0, TRUE, TRUE, 0, &llvm_fun, NULL, FALSE, NULL, -1, "llvm.va_copy", &neo_c_fun);
    }

    /// llvm.memset ///
#ifdef __32BIT_CPU__
    params.clear();

    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    params.push_back(param1_type);
    param2_type = IntegerType::get(TheContext,8);
    params.push_back(param2_type);
    param3_type = IntegerType::get(TheContext,32);
    params.push_back(param3_type);
    param4_type = IntegerType::get(TheContext,1);
    params.push_back(param4_type);

    {
        std::vector<Type *> llvm_param_types;
        sNodeType* param_types[PARAMS_MAX];
        char param_names[PARAMS_MAX][VAR_NAME_MAX];

        sNodeType* result_type = create_node_type_with_class_name("void");

        int num_params = 4;
        xstrncpy(param_names[0], "dest", VAR_NAME_MAX);
        xstrncpy(param_names[1], "val", VAR_NAME_MAX);
        xstrncpy(param_names[2], "len", VAR_NAME_MAX);
        xstrncpy(param_names[3], "isvolatile", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("void*");
        param_types[1] = create_node_type_with_class_name("char");
        param_types[2] = create_node_type_with_class_name("int");
        param_types[3] = create_node_type_with_class_name("bool");

        BOOL var_arg = FALSE;

        char method_generics_type_names[GENERICS_TYPES_MAX][VAR_NAME_MAX];

        memset(method_generics_type_names, 0, sizeof(char)*GENERICS_TYPES_MAX*VAR_NAME_MAX);

        char generics_type_names[GENERICS_TYPES_MAX][VAR_NAME_MAX];

        memset(generics_type_names, 0, sizeof(char)*GENERICS_TYPES_MAX*VAR_NAME_MAX);

        Function* llvm_fun;
        sFunction* neo_c_fun = NULL;

        char* param_names2[PARAMS_MAX];
        int i;
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }
        char* method_generics_type_names2[GENERICS_TYPES_MAX];
        int num_method_generics = 0;
        for(i=0; i<num_method_generics; i++) {
            method_generics_type_names2[i] = method_generics_type_names[i];
        }
        char* generics_type_names2[GENERICS_TYPES_MAX];
        int num_generics = 0;
        for(i=0; i<num_generics; i++) {
            generics_type_names2[i] = generics_type_names[i];
        }
        add_function("llvm.memset.p0i8.i32", "llvm.memset.p0i8.i32", "", param_names2, param_types, num_params, result_type, 0, method_generics_type_names2, TRUE, var_arg, NULL, 0, generics_type_names2, FALSE, FALSE, NULL, 0, TRUE, TRUE, 0, &llvm_fun, NULL, FALSE, NULL, -1, "llvm.va_copy", &neo_c_fun);
    }
#else
    params.clear();

    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    params.push_back(param1_type);
    param2_type = IntegerType::get(TheContext,8);
    params.push_back(param2_type);
    param3_type = IntegerType::get(TheContext,64);
    params.push_back(param3_type);
    param4_type = IntegerType::get(TheContext,1);
    params.push_back(param4_type);

    {
        std::vector<Type *> llvm_param_types;
        sNodeType* param_types[PARAMS_MAX];
        char param_names[PARAMS_MAX][VAR_NAME_MAX];

        sNodeType* result_type = create_node_type_with_class_name("void");

        int num_params = 4;
        xstrncpy(param_names[0], "dest", VAR_NAME_MAX);
        xstrncpy(param_names[1], "val", VAR_NAME_MAX);
        xstrncpy(param_names[2], "len", VAR_NAME_MAX);
        xstrncpy(param_names[3], "isvolatile", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("void*");
        param_types[1] = create_node_type_with_class_name("char");
        param_types[2] = create_node_type_with_class_name("long");
        param_types[3] = create_node_type_with_class_name("bool");

        BOOL var_arg = FALSE;

        char method_generics_type_names[GENERICS_TYPES_MAX][VAR_NAME_MAX];

        memset(method_generics_type_names, 0, sizeof(char)*GENERICS_TYPES_MAX*VAR_NAME_MAX);

        char generics_type_names[GENERICS_TYPES_MAX][VAR_NAME_MAX];

        memset(generics_type_names, 0, sizeof(char)*GENERICS_TYPES_MAX*VAR_NAME_MAX);

        Function* llvm_fun;
        sFunction* neo_c_fun = NULL;

        char* param_names2[PARAMS_MAX];
        int i;
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }
        char* method_generics_type_names2[GENERICS_TYPES_MAX];
        int num_method_generics = 0;
        for(i=0; i<num_method_generics; i++) {
            method_generics_type_names2[i] = method_generics_type_names[i];
        }
        char* generics_type_names2[GENERICS_TYPES_MAX];
        int num_generics = 0;
        for(i=0; i<num_generics; i++) {
            generics_type_names2[i] = generics_type_names[i];
        }
        add_function("llvm.memset.p0i8.i64", "llvm.memset.p0i8.i64", "", param_names2, param_types, num_params, result_type, 0, method_generics_type_names2, TRUE, var_arg, NULL, 0, generics_type_names2, FALSE, FALSE, NULL, 0, TRUE, TRUE, 0, &llvm_fun, NULL, FALSE, NULL, -1, "llvm.va_copy", &neo_c_fun);
    }

#endif
*/
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
    declare_builtin_functions();
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
        fprintf(stderr, "%s %d: unexpected stack value. The stack num is %d. top is %d\n", gSName, yylineno, info->stack_num, top);
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


BOOL compile_block(unsigned int node_block, sCompileInfo* info, BOOL* last_expression_is_return, BOOL loop_top)
{
    int num_nodes = gNodes[node_block].uValue.sBlock.mNumNodes;
    unsigned int* nodes = gNodes[node_block].uValue.sBlock.mNodes;

    sVarTable* lv_table = info->lv_table;
    info->lv_table = gNodes[node_block].uValue.sBlock.mLVTable;

    sVarTable* loop_top_lv_table = info->loop_top_lv_table;
    if(loop_top) {
        info->loop_top_lv_table = info->lv_table;
    }

    int i;
    for(i=0; i<num_nodes; i++) {
        unsigned int node = nodes[i];

        int sline = gNodes[node].mLine;
        if(gNCDebug) {
            setCurrentDebugLocation(sline);
        }

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

    if(loop_top) {
        info->loop_top_lv_table = loop_top_lv_table;
    }

    info->lv_table= lv_table;

    return TRUE;
}

BOOL pre_compile_block(unsigned int node_block, sCompileInfo* info)
{
    int num_nodes = gNodes[node_block].uValue.sBlock.mNumNodes;
    unsigned int* nodes = gNodes[node_block].uValue.sBlock.mNodes;

    BOOL create_lv_table = gNodes[node_block].uValue.sBlock.mCreateLVTable;

    sVarTable* lv_table = info->lv_table;
    if(create_lv_table) {
        sVarTable* block_lv_table = init_var_table();
        block_lv_table->mParent = info->lv_table;
        gNodes[node_block].uValue.sBlock.mLVTable = block_lv_table;
    }
    else {
        gNodes[node_block].uValue.sBlock.mLVTable = info->lv_table;
    }

    int i;
    for(i=0; i<num_nodes; i++) {
        unsigned int node = nodes[i];

        if(!pre_compile(node, info)) {
            return FALSE;
        }

        dec_stack_ptr(info->stack_num, info);
    }

    info->lv_table= lv_table;

    return TRUE;
}

///////////////////////////////////////////////////////////////////////
// extra
///////////////////////////////////////////////////////////////////////
BOOL get_const_value_from_node(int* array_size, unsigned int array_size_node, sCompileInfo* cinfo)
{
    if(!compile(array_size_node, cinfo)) {
        return FALSE;
    }

    sNodeType* node_type = cinfo->type;

    LVALUE llvm_value = *get_value_from_stack(-1);

    dec_stack_ptr(1, cinfo);

    Value* value = llvm_value.value;

    ConstantInt* constant_value;

    if(constant_value = dyn_cast<ConstantInt>(value)) {
        *array_size = constant_value->getSExtValue();
    }
    else {
        return FALSE;
    }

    return TRUE;
}

static BOOL create_llvm_function(sFunction* fun, sVarTable* fun_lv_table, sCompileInfo* info, int sline, BOOL pre_compile)
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

        solve_method_generics2(&params[i].mType, info->method_generics_types);

        if(params[i].mType == NULL || params[i].mType->mClass == NULL) {
            compile_err_msg(info, "Invalid type name %s 3\n", fun->mParamNames[i]);
            return FALSE;
        }
    }

    sNodeType* result_type = create_node_type_with_class_name(fun->mResultTypeName);
    BOOL success_solve;
    (void)solve_generics(&result_type, info->generics_type, &success_solve);

    solve_method_generics2(&result_type, info->method_generics_types);

    Function* llvm_fun = fun->mLLVMFunction;

    unsigned int node_block = fun->mNodeBlock;

    sFunction* function = (sFunction*)info->function;
    info->function = fun;
    sNodeType* function_result_type = info->function_result_type;
    info->function_result_type = clone_node_type(result_type);

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
    info->lv_table = fun_lv_table;

    char* fun_name = fun->mName;
    Function* llvm_function = fun->mLLVMFunction;

    if(gNCDebug) {
        createDebugFunctionInfo(sline, fun_name, fun, fun->mLLVMFunction);
    }

    BasicBlock* current_block_before;
    BasicBlock* current_block = BasicBlock::Create(TheContext, "entry", llvm_fun);

    BasicBlock* entry_block_before = (BasicBlock*)info->entry_block;
    info->entry_block = current_block;

    llvm_change_block(current_block, &current_block_before, info, FALSE);

    /// ready for params ///
    for(i=0; i<num_params; i++) {
        sParserParam param = params[i];

        sNodeType* param_type = create_node_type_with_class_name(param.mTypeName);

        char* var_name = param.mName;

        sVar* var = get_variable_from_table(info->lv_table, (char*)var_name);
        sNodeType* var_type;

        if(var == NULL) {
            var_type = clone_node_type(param_type);
            BOOL success_solve;
            (void)solve_generics(&var_type, info->generics_type, &success_solve);

            solve_method_generics2(&var_type, info->method_generics_types);

            if(var_type == NULL || var_type->mClass == NULL) {
                compile_err_msg(info, "Invalid type name %s 4\n", param.mTypeName);
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
        }
        else {
            var->mType = clone_node_type(param_type);
            BOOL success_solve;
            (void)solve_generics(&var->mType, info->generics_type, &success_solve);

            solve_method_generics2(&var->mType, info->method_generics_types);

            var_type = var->mType;
        }

        var = get_variable_from_table(info->lv_table, (char*)var_name);

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
        int index = get_variable_index(info->lv_table, var_name, &parent);

        store_address_to_lvtable(index, address, info);
    }

    gNodes[node_block].uValue.sBlock.mLVTable = fun_lv_table;

    if(pre_compile) {
        if(!pre_compile_block(node_block, &cinfo)) {
            fprintf(stderr, "%s %d: faield to pre-compile\n", gSName, yylineno);
            exit(2);
        }
    }

    BOOL last_expression_is_return = FALSE;
    BOOL loop_top = FALSE;
    if(!compile_block(node_block, info, &last_expression_is_return, loop_top)) {
        return FALSE;
    }

    if(!last_expression_is_return || info->no_output) {
        if(type_identify_with_class_name(result_type, "void") && result_type->mPointerNum == 0) {
            Builder.CreateRet(nullptr);
        }
        else {
            Value* value = get_dummy_value(result_type, info);
            Builder.CreateRet(value);
        }
    }

    verifyFunction(*llvm_fun);

    // Run the optimizer on the function.
    //TheFPM->run(*llvm_fun, TheFAM);

    info->lv_table = lv_table;

    restore_right_value_objects_container(right_value_objects, info);

    BasicBlock* current_block_before2;
    llvm_change_block(current_block_before, &current_block_before2, info, FALSE);

    if(gNCDebug) {
        finishDebugFunctionInfo();
    }

    info->function = function;
    info->function_result_type = function_result_type;

    info->andand_result_var = NULL;
    info->oror_result_var = NULL;

    info->entry_block = entry_block_before;

    return TRUE;
}

static BOOL create_generics_function(char* id, char* fun_name, sCLClass* klass, sFunction* fun, char* real_fun_name2, sCompileInfo* info, int sline, BOOL pre_compile, BOOL inherit_) 
{
    int stack_num = info->stack_num;
    info->stack_num = 0;

    if(klass && info->generics_type) {
        xstrncpy(real_fun_name2, klass->mName, VAR_NAME_MAX);

        create_real_struct_name(real_fun_name2, VAR_NAME_MAX, info->generics_type->mNumGenericsTypes, info->generics_type->mGenericsTypes);

        xstrncat(real_fun_name2, "_", VAR_NAME_MAX);
        xstrncat(real_fun_name2, fun_name, VAR_NAME_MAX);
    }
    else if(fun->mMethodGenerics) {
        xstrncpy(real_fun_name2, fun_name, VAR_NAME_MAX);

        int i;
        for(i=0; i<fun->mNumParams; i++) {
            xstrncat(real_fun_name2, "_", VAR_NAME_MAX);
            xstrncat(real_fun_name2, fun->mParamTypes[i], VAR_NAME_MAX);
        }
    }
    else {
        xstrncpy(real_fun_name2, fun_name, VAR_NAME_MAX);
    }

    sFunction generics_fun = *fun;

    xstrncpy(generics_fun.mID, id, VAR_NAME_MAX);
    xstrncpy(generics_fun.mName, real_fun_name2, VAR_NAME_MAX);

    if(gFuncs[real_fun_name2].size() > 0 && !inherit_) {
        int n = gFuncs[real_fun_name2].size();
        *fun = gFuncs[real_fun_name2][n-1];
    }
    else {
        gFuncs[real_fun_name2].push_back(generics_fun);

        Function* llvm_fun = NULL;
        if(!entry_llvm_function(&generics_fun, info->generics_type, info, &llvm_fun)) {
            return FALSE;
        }

        int n = gFuncs[real_fun_name2].size();
        gFuncs[real_fun_name2][n-1].mLLVMFunction = llvm_fun;

        sVarTable* fun_lv_table = clone_var_table(generics_fun.mLVTable);

        void* lv_table_value = info->lv_table_value;
        create_global_lvtable(info);

        if(!create_llvm_function(&generics_fun, fun_lv_table, info, sline, pre_compile)) {
            return FALSE;
        }

        info->lv_table_value = lv_table_value;

        *fun = gFuncs[real_fun_name2][gFuncs[real_fun_name2].size()-1];
    }

    info->stack_num = stack_num;

    return TRUE;
}

static void solve_method_generics2(sNodeType** node_type, char** method_generics_types)
{
    if(method_generics_types) {
        if(type_identify_with_class_name(*node_type, "lambda")) 
        {
            solve_method_generics2(&(*node_type)->mResultType, method_generics_types);

            int i;
            for(i=0; i<(*node_type)->mNumParams; i++)
            {
                solve_method_generics2(&(*node_type)->mParamTypes[i], method_generics_types);
            }
        }
        else {
            int i;
            for(i=0; i<GENERICS_TYPES_MAX; i++) {
                char generics_type_name[VAR_NAME_MAX];
                snprintf(generics_type_name, VAR_NAME_MAX, "mgenerics%d", i);

                char result_type[VAR_NAME_MAX];

                if(strcmp((*node_type)->mClass->mName, generics_type_name) == 0) {
                    sNodeType* generics_type = create_node_type_with_class_name(method_generics_types[i]);

                    *node_type = generics_type;
                    break;
                }

                int j;
                for(j=0; j<(*node_type)->mNumGenericsTypes; j++) {
                    solve_method_generics2(&(*node_type)->mGenericsTypes[j], method_generics_types);
                }
            }
        }
    }
}

static void solve_method_generics(char* node_type, char** method_generics_types)
{
/*
    sNodeType* node_type2 = create_node_type_with_class_name(node_type);

    solve_method_generics2(&node_type2, method_generics_types);

    char new_node_type[VAR_NAME_MAX];

    new_node_type[0] = '\0';

    create_type_name_from_node_type(new_node_type, VAR_NAME_MAX, node_type2, TRUE);

    xstrncpy(node_type, new_node_type, VAR_NAME_MAX);
*/
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

static void determine_method_generics_core(sNodeType* left_type, sNodeType* right_type, char** method_generics_types)
{
    int n;
    if(sscanf(left_type->mClass->mName, "mgenerics%d", &n) == 1) {
        xstrncpy(method_generics_types[n], right_type->mClass->mName, VAR_NAME_MAX);

        int i;
        for(i=0; i<right_type->mPointerNum; i++) {
            xstrncat(method_generics_types[n], "*", VAR_NAME_MAX);
        }

        if(right_type->mHeap) {
            xstrncat(method_generics_types[n], "%", VAR_NAME_MAX);
        }
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

static void determine_method_generics(char* method_generics_types[VAR_NAME_MAX], sFunction* fun, sNodeType** param_types)
{
    int i;
    for(i=0; i<fun->mNumParams; i++) {
        sNodeType* left_type = create_node_type_with_class_name(fun->mParamTypes[i]);
        sNodeType* right_type = param_types[i];

        determine_method_generics_core(left_type, right_type, method_generics_types);
    }
}



///////////////////////////////////////////////////////////////////////
// main
///////////////////////////////////////////////////////////////////////
static BOOL compile_int_value(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("int");
        return TRUE;
    }

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

static BOOL pre_compile_int_value(unsigned int node, sCompileInfo* info)
{
    info->type = create_node_type_with_class_name("int");

    return TRUE;
}

static BOOL compile_char_value(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("char");
        return TRUE;
    }

    char value = gNodes[node].uValue.mCharValue;

    LVALUE llvm_value;
    llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(8, value, true)); 
    llvm_value.type = create_node_type_with_class_name("char");
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("char");

    return TRUE;
}

static BOOL pre_compile_char_value(unsigned int node, sCompileInfo* info)
{
    info->type = create_node_type_with_class_name("char");

    return TRUE;
}

static BOOL compile_str_value(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("const char*");
        return TRUE;
    }

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

static BOOL pre_compile_str_value(unsigned int node, sCompileInfo* info)
{
    info->type = create_node_type_with_class_name("const char*");

    return TRUE;
}

static BOOL compile_true(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("bool");
        return TRUE;
    }

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

static BOOL pre_compile_true(unsigned int node, sCompileInfo* info)
{
    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

static BOOL compile_false(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("bool");
        return TRUE;
    }

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

static BOOL pre_compile_false(unsigned int node, sCompileInfo* info)
{
    info->type = create_node_type_with_class_name("bool");
    return TRUE;
}

static BOOL compile_null(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void*");
        return TRUE;
    }

    LVALUE llvm_value;
    llvm_value.value = ConstantInt::get(Type::getInt1Ty(TheContext), 0);
    llvm_value.value = Builder.CreateCast(Instruction::BitCast, llvm_value.value, PointerType::get(IntegerType::get(TheContext, 8), 0));
    llvm_value.type = create_node_type_with_class_name("void*");
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("void*");

    return TRUE;
}

static BOOL pre_compile_null(unsigned int node, sCompileInfo* info)
{
    info->type = create_node_type_with_class_name("void*");
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

    if(info->no_output) {
        info->type = clone_node_type(left_type);
        return TRUE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    LVALUE rvalue = *get_value_from_stack(-1);

    if(!(left_type->mPointerNum > 0 && is_number_type(right_type)))
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
    }

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
    else if(left_type->mPointerNum > 0 && is_number_type(right_type))
    {
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

static BOOL pre_compile_add(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    int right_node = gNodes[node].mRight;
    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = clone_node_type(left_type);

    return TRUE;
}

static BOOL compile_sub(unsigned int node, sCompileInfo* info)
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

    if(info->no_output) {
        info->type = clone_node_type(left_type);
        return TRUE;
    }

    LVALUE rvalue = *get_value_from_stack(-1);

    if(!(left_type->mPointerNum > 0 && is_number_type(right_type)))
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
    }

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
                right_value = Builder.CreateCast(Instruction::PtrToInt, rvalue.value, IntegerType::get(TheContext, 64), "sextX-p");
            }
            else {
                right_value = Builder.CreateCast(Instruction::SExt, rvalue.value, IntegerType::get(TheContext, 64), "sextX");
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
        llvm_value.value = Builder.CreateSub(left_value, right_value, "subtmp", false, true);
        llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, llvm_var_type, "IntTOPtr3a");
        llvm_value.type = clone_node_type(left_type2);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(2, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(left_type2);
    }
    else if((left_type->mPointerNum > 0 || left_type->mArrayDimentionNum == 1) && (right_type->mPointerNum > 0 || right_type->mArrayDimentionNum == 1))
    {
        Value* left_value = Builder.CreateCast(Instruction::PtrToInt, lvalue.value, IntegerType::get(TheContext, 64));
        Value* right_value = Builder.CreateCast(Instruction::PtrToInt, rvalue.value, IntegerType::get(TheContext, 64));

        sNodeType* node_type = create_node_type_with_class_name("long");

        Type* llvm_var_type;
        if(!create_llvm_type_from_node_type(&llvm_var_type, node_type, node_type, info))
        {
            compile_err_msg(info, "Getting llvm type failed(10)");
            show_node_type(left_type);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
        LVALUE llvm_value;
        llvm_value.value = Builder.CreateSub(left_value, right_value, "subtmp", false, true);
        llvm_value.value = Builder.CreateCast(Instruction::BitCast, llvm_value.value, llvm_var_type);
        llvm_value.type = clone_node_type(node_type);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(2, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(node_type);
    }
    else if(left_type->mPointerNum > 0 && is_number_type(right_type))
    {
        Value* left_value = Builder.CreateCast(Instruction::PtrToInt, lvalue.value, IntegerType::get(TheContext, 64));

        Value* right_value;
        if(type_identify_with_class_name(right_type, "long")) {
            right_value = rvalue.value;
        }
        else {
            if(right_type->mPointerNum > 0 || right_type->mArrayDimentionNum > 0) {
                right_value = Builder.CreateCast(Instruction::PtrToInt, rvalue.value, IntegerType::get(TheContext, 64), "sextY-p");
            }
            else {
                right_value = Builder.CreateCast(Instruction::SExt, rvalue.value, IntegerType::get(TheContext, 64), "sextY");
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
        llvm_value.value = Builder.CreateSub(left_value, right_value, "subtmp", false, true);
        llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, llvm_var_type, "IntTOPtr4b");
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
        LVALUE llvm_value;
        llvm_value.value = Builder.CreateSub(lvalue.value, rvalue.value, "subttmp", false, true);
        llvm_value.type = clone_node_type(right_type);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(2, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = llvm_value.type;
    }
    else {
        compile_err_msg(info, "invalid type for operator -");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
    }

    return TRUE;
}

static BOOL pre_compile_sub(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    int right_node = gNodes[node].mRight;
    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = clone_node_type(left_type);

    return TRUE;
}

static BOOL compile_mult(unsigned int node, sCompileInfo* info)
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

    if(info->no_output) {
        info->type = clone_node_type(left_type);
        return TRUE;
    }

    LVALUE rvalue = *get_value_from_stack(-1);

    if(!(left_type->mPointerNum > 0 && is_number_type(right_type)))
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
    }

    if(is_number_type(left_type) && is_number_type(right_type))
    {
        LVALUE llvm_value;
        llvm_value.value = Builder.CreateMul(lvalue.value, rvalue.value, "multtmp", false, true);
        llvm_value.type = clone_node_type(right_type);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(2, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = llvm_value.type;
    }
    else {
        compile_err_msg(info, "invalid type for operator *");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
    }

    return TRUE;
}

static BOOL pre_compile_mult(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    int right_node = gNodes[node].mRight;
    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = clone_node_type(left_type);

    return TRUE;
}

static BOOL compile_div(unsigned int node, sCompileInfo* info)
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

    if(info->no_output) {
        info->type = clone_node_type(left_type);
        return TRUE;
    }

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

    if(is_number_type(left_type) && is_number_type(right_type))
    {
        LVALUE llvm_value;
        if(left_type->mUnsigned) {
            llvm_value.value = Builder.CreateUDiv(lvalue.value, rvalue.value, "divtmp");
        }
        else {
            llvm_value.value = Builder.CreateSDiv(lvalue.value, rvalue.value, "divtmp");
        }
        llvm_value.type = clone_node_type(left_type);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(2, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = llvm_value.type;
    }
    else {
        compile_err_msg(info, "invalid type for operator /");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
    }

    return TRUE;
}

static BOOL pre_compile_div(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    int right_node = gNodes[node].mRight;
    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = clone_node_type(left_type);

    return TRUE;
}

static BOOL compile_mod(unsigned int node, sCompileInfo* info)
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

    if(info->no_output) {
        info->type = clone_node_type(left_type);
        return TRUE;
    }

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

    if(is_number_type(left_type) && is_number_type(right_type))
    {
        LVALUE llvm_value;
        if(left_type->mUnsigned) {
            llvm_value.value = Builder.CreateURem(lvalue.value, rvalue.value, "remtmp");
        }
        else {
            llvm_value.value = Builder.CreateSRem(lvalue.value, rvalue.value, "remtmp");
        }
        llvm_value.type = clone_node_type(left_type);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(2, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = llvm_value.type;
    }
    else {
        compile_err_msg(info, "invalid type for operator /");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
    }

    return TRUE;
}

static BOOL pre_compile_mod(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    int right_node = gNodes[node].mRight;
    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = clone_node_type(left_type);

    return TRUE;
}

static BOOL compile_lshift(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }
    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    if(info->no_output) {
        info->type = clone_node_type(left_type);
        return TRUE;
    }

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

    if(is_number_type(left_type) && is_number_type(right_type))
    {
        LVALUE llvm_value;
        llvm_value.value = Builder.CreateShl(lvalue.value, rvalue.value, "lshifttmp");
        llvm_value.type = clone_node_type(right_type);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(2, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = llvm_value.type;
    }
    else {
        compile_err_msg(info, "invalid type for operator <<");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
    }

    return TRUE;
}

static BOOL pre_compile_lshift(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    int right_node = gNodes[node].mRight;
    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = clone_node_type(left_type);

    return TRUE;
}

static BOOL compile_rshift(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }
    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    if(info->no_output) {
        info->type = clone_node_type(left_type);
        return TRUE;
    }

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

    if(is_number_type(left_type) && is_number_type(right_type))
    {
        LVALUE llvm_value;
        llvm_value.value = Builder.CreateAShr(lvalue.value, rvalue.value, "rshifttmp");
        llvm_value.type = clone_node_type(right_type);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(2, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = llvm_value.type;
    }
    else {
        compile_err_msg(info, "invalid type for operator >>");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
    }

    return TRUE;
}

static BOOL pre_compile_rshift(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    int right_node = gNodes[node].mRight;
    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = clone_node_type(left_type);

    return TRUE;
}

static BOOL compile_or(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }
    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    if(info->no_output) {
        info->type = clone_node_type(left_type);
        return TRUE;
    }

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

    if(is_number_type(left_type) && is_number_type(right_type))
    {
        LVALUE llvm_value;
        llvm_value.value = Builder.CreateOr(lvalue.value, rvalue.value, "ortmp");
        llvm_value.type = clone_node_type(right_type);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(2, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = llvm_value.type;
    }
    else {
        compile_err_msg(info, "invalid type for operator |");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
    }

    return TRUE;
}

static BOOL pre_compile_or(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!pre_compile(left_node, info)) {
        return FALSE;
    }
    sNodeType* left_type = info->type;

    int right_node = gNodes[node].mRight;
    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = clone_node_type(left_type);

    return TRUE;
}

static BOOL compile_and(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }
    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    if(info->no_output) {
        info->type = clone_node_type(left_type);
        return TRUE;
    }

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

    if(is_number_type(left_type) && is_number_type(right_type))
    {
        LVALUE llvm_value;
        llvm_value.value = Builder.CreateAnd(lvalue.value, rvalue.value, "andtmp");
        llvm_value.type = clone_node_type(right_type);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(2, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = llvm_value.type;
    }
    else {
        compile_err_msg(info, "invalid type for operator &");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
    }

    return TRUE;
}

static BOOL pre_compile_and(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    int right_node = gNodes[node].mRight;
    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = clone_node_type(left_type);

    return TRUE;
}

static BOOL compile_xor(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }
    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    if(info->no_output) {
        info->type = clone_node_type(left_type);
        return TRUE;
    }

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

    if(is_number_type(left_type) && is_number_type(right_type))
    {
        LVALUE llvm_value;
        llvm_value.value = Builder.CreateXor(lvalue.value, rvalue.value, "xortmp");
        llvm_value.type = clone_node_type(right_type);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(2, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = llvm_value.type;
    }
    else {
        compile_err_msg(info, "invalid type for operator ^");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
    }

    return TRUE;
}

static BOOL pre_compile_xor(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    int right_node = gNodes[node].mRight;
    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = clone_node_type(left_type);

    return TRUE;
}

static BOOL compile_store_variable(unsigned int node, sCompileInfo* info)
{
    char var_name[VAR_NAME_MAX];
    char type_name[VAR_NAME_MAX];

    xstrncpy(var_name, gNodes[node].uValue.sStoreVariable.mVarName, VAR_NAME_MAX);
    xstrncpy(type_name, gNodes[node].uValue.sStoreVariable.mTypeName, VAR_NAME_MAX);

    BOOL alloc = gNodes[node].uValue.sStoreVariable.mAlloc;
    BOOL global = gNodes[node].uValue.sStoreVariable.mGlobal;

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    if(info->no_output) {
        info->type = clone_node_type(right_type);
        return TRUE;
    }

    if(alloc) {
        sNodeType* var_type = create_node_type_with_class_name(type_name);

        if(var_type == NULL || var_type->mClass == NULL) {
            fprintf(stderr, "Invalid type name (%s)\n", type_name);
            exit(1);
        }

        BOOL readonly = FALSE;
        BOOL constant = var_type->mConstant;

        int index = -1;
        void* llvm_value = NULL;
        if(global) {
            if(!add_variable_to_table(info->gv_table, var_name, var_type, llvm_value,  index, global, constant))
            {
                fprintf(stderr, "overflow variable table");
                exit(2);
            }
        }
    }

    LVALUE rvalue = *get_value_from_stack(-1);

    sVar* var;
    var = get_variable_from_table(info->lv_table, var_name);

    if(var == NULL) {
        var = get_variable_from_table(info->gv_table, var_name);
    }

    if(var == NULL) {
        compile_err_msg(info, "undeclared variable %s(27)", var_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    global = var->mGlobal;

    /// type inference ///
    sNodeType* left_type = NULL;
    if(var->mType == NULL) {
        left_type = clone_node_type(right_type);
        var->mType = clone_node_type(right_type);
    }
    else {
        left_type = clone_node_type(var->mType);
    }

    BOOL success_solve;
    (void)solve_generics(&left_type, info->generics_type, &success_solve);

    solve_method_generics2(&left_type, info->method_generics_types);

    //var->mType = clone_node_type(left_type);

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
        compile_err_msg(info, "The different type between left type and right type. store variable. var name is %s(1)", var_name);
        show_node_type(left_type);
        show_node_type(right_type);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    Type* llvm_var_type;
    if(!create_llvm_type_from_node_type(&llvm_var_type, left_type, left_type, info))
    {
        compile_err_msg(info, "Getting llvm type failed(1). var name is %s", var_name);
        show_node_type(left_type);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(type_identify_with_class_name(left_type, "__builtin_va_list")) {
        llvm_var_type = ArrayType::get(llvm_var_type, 1);
    }

    int alignment = get_llvm_alignment_from_node_type(left_type);

    BOOL constant = var->mConstant;
    BOOL static_ = var->mType->mStatic;

    if(alloc) {
         if(global) {
            var->mLLVMValue = NULL;

            if(constant) {
                Value* rvalue2 = rvalue.value;

                if(dyn_cast<Constant>(rvalue2)) {
                    var->mLLVMValue = dyn_cast<Constant>(rvalue2);
                }
                else {
                    compile_err_msg(info, "Invalid Global Variable Initializer. Require Constant Value");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }

                info->type = clone_node_type(left_type);
            }
            else {
                if(TheModule->getNamedGlobal(var_name) != nullptr)
                {
                    TheModule->getNamedGlobal(var_name)->eraseFromParent();
                }

                GlobalVariable* address = new GlobalVariable(*TheModule, llvm_var_type, var->mConstant, GlobalValue::ExternalLinkage, 0, var_name);
                address->setAlignment(alignment);

                Value* rvalue2 = rvalue.value;

                if(dyn_cast<Constant>(rvalue2)) {
                    Constant* rvalue3 = dyn_cast<Constant>(rvalue2);
                    address->setInitializer(rvalue3);
                }
                else {
                    compile_err_msg(info, "Invalid Global Variable Initializer. Require Constant Value");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }

                var->mLLVMValue = address;

                info->type = clone_node_type(left_type);
            }
        }
        else if(constant) {
            Value* rvalue2 = rvalue.value;

            if(dyn_cast<Constant>(rvalue2)) {
                Constant* rvalue3 = dyn_cast<Constant>(rvalue2);

                var->mLLVMValue = rvalue3;

                info->type = clone_node_type(left_type);
            }
            else {
                compile_err_msg(info, "Invalid Variable Initializer. Require Constant Value");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }
        else if(static_) {
            sFunction* function = (sFunction*)info->function;

            char static_var_name[VAR_NAME_MAX*2];
            snprintf(static_var_name, VAR_NAME_MAX*2, "%s_%s", function->mName, var_name);

            if(var->mLLVMValue == NULL && TheModule->getNamedGlobal(static_var_name) == nullptr)
            {
                GlobalVariable* address = new GlobalVariable(*TheModule, llvm_var_type, var->mConstant, GlobalValue::ExternalLinkage, 0, static_var_name);
                address->setAlignment(alignment);

                Value* rvalue2 = rvalue.value;

                if(dyn_cast<Constant>(rvalue2)) {
                    Constant* rvalue3 = dyn_cast<Constant>(rvalue2);
                    address->setInitializer(rvalue3);
                }
                else {
                    compile_err_msg(info, "Invalid variable initializer. Require constant value");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }

                var->mLLVMValue = address;

                BOOL parent = FALSE;
                int index = get_variable_index(info->lv_table, var_name, &parent);

                store_address_to_lvtable(index, address, info);

                info->type = clone_node_type(left_type);
            }
            else {
                compile_err_msg(info, "Redifined static variable");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }
        else {
            Value* address = Builder.CreateAlloca(llvm_var_type, 0, var_name);

            var->mLLVMValue = address;

            BOOL parent = FALSE;
            int index = get_variable_index(info->lv_table, var_name, &parent);

            store_address_to_lvtable(index, address, info);

            sNodeType* var_type = left_type;

            Value* var_address;
            if(parent) {
                var_address = load_address_to_lvtable(index, var_type, info);
            }
            else {
                var_address = (Value*)var->mLLVMValue;
            }

            if(var_address == nullptr) {
                compile_err_msg(info, "Invalid variable.store variable(3)");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            Value* rvalue2 = Builder.CreateCast(Instruction::BitCast, rvalue.value, llvm_var_type);

            std_move(var_address, var->mType, &rvalue, alloc, info);

            Builder.CreateAlignedStore(rvalue2, var_address, alignment);

            info->type = clone_node_type(left_type);
        }
    }
    else {
        Value* var_address;

/*
        if(constant) {
            compile_err_msg(info, "Variable(%s) is constant variable", var->mName);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
*/
        if(global) {
            var_address = (Value*)var->mLLVMValue;
        }
        else if(static_) {
            var_address = (Value*)var->mLLVMValue;
        }
        else {
            BOOL parent = FALSE;
            int index = get_variable_index(info->lv_table, var_name, &parent);

            sNodeType* var_type = left_type;

            if(parent) {
                var_address = load_address_to_lvtable(index, var_type, info);
            }
            else {
                var_address = (Value*)var->mLLVMValue;
            }
        }

        if(var_address == nullptr) {
            compile_err_msg(info, "Invalid variable.store variable(4)");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        Value* rvalue2 = Builder.CreateCast(Instruction::BitCast, rvalue.value, llvm_var_type);

        std_move(var_address, var->mType, &rvalue, alloc, info);

        Builder.CreateAlignedStore(rvalue2, var_address, alignment);

        info->type = clone_node_type(left_type);
    }

    return TRUE;
}

BOOL pre_compile_store_variable(unsigned int node, sCompileInfo* info)
{
    char var_name[VAR_NAME_MAX];
    xstrncpy(var_name, gNodes[node].uValue.sStoreVariable.mVarName, VAR_NAME_MAX);
    char type_name[VAR_NAME_MAX];
    xstrncpy(type_name, gNodes[node].uValue.sStoreVariable.mTypeName, VAR_NAME_MAX);
    BOOL alloc = gNodes[node].uValue.sStoreVariable.mAlloc;
    BOOL global = gNodes[node].uValue.sStoreVariable.mGlobal;

    unsigned int right_node = gNodes[node].mRight;

    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    if(alloc) {
        sNodeType* var_type = create_node_type_with_class_name(type_name);

        if(var_type == NULL || var_type->mClass == NULL) {
            fprintf(stderr, "Invalid type name (%s)\n", type_name);
            exit(1);
        }

        BOOL readonly = FALSE;
        BOOL constant = var_type->mConstant;

        int index = -1;
        void* llvm_value = NULL;
        if(!add_variable_to_table(info->lv_table, var_name, var_type, llvm_value,  index, global, constant))
        {
            fprintf(stderr, "overflow variable table");
            exit(2);
        }
    }

    info->type = clone_node_type(right_type);

    return node;
}

static BOOL compile_load_variable(unsigned int node, sCompileInfo* info)
{
    char var_name[VAR_NAME_MAX];

    xstrncpy(var_name, gNodes[node].uValue.sLoadVariable.mVarName, VAR_NAME_MAX);

    sVar* var = get_variable_from_table(info->lv_table, var_name);

    if(var == NULL) {
        var = get_variable_from_table(info->gv_table, var_name);
    }

    if(var == NULL || var->mType == NULL) {
        compile_err_msg(info, "undeclared variable(1-2) %s", var_name);
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

    BOOL success_solve;
    solve_generics(&var_type, info->generics_type, &success_solve);

    solve_method_generics2(&var_type, info->method_generics_types);

    if(info->no_output) {
        info->type = var_type;
        return TRUE;
    }

    BOOL constant = var->mConstant;
    BOOL global = var->mGlobal;

    if(constant && global) {
        LVALUE llvm_value;
        llvm_value.value = (Value*)var->mLLVMValue;
        llvm_value.type = var_type;
        llvm_value.address = nullptr;
        llvm_value.var = var;
        llvm_value.binded_value = TRUE;
        llvm_value.load_field = FALSE;

        push_value_to_stack_ptr(&llvm_value, info);

        sNodeType* result_type = var_type;

        info->type = clone_node_type(result_type);
    }
    else {
        Value* var_address;
        if(var->mGlobal) {
            var_address = (Value*)var->mLLVMValue;
        }
        else {
            BOOL parent = FALSE;
            int index = get_variable_index(info->lv_table, var_name, &parent);

            if(parent) {
                var_address = load_address_to_lvtable(index, var_type, info);
            }
            else {
                var_address = (Value*)var->mLLVMValue;
            }
        }

        if(var_address == nullptr && !info->no_output) {
            compile_err_msg(info, "Invalid variable. %s. load variable(X)", var_name);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        int alignment = get_llvm_alignment_from_node_type(var_type);

        LVALUE llvm_value;

        if(type_identify_with_class_name(var_type, "__builtin_va_list")) {
            Value* indices[2];

            indices[0] = ConstantInt::get(Type::getInt32Ty(TheContext), 0);
            indices[1] = ConstantInt::get(Type::getInt32Ty(TheContext), 0);

            llvm_value.value = Builder.CreateInBoundsGEP(var_address, ArrayRef<Value*>(indices, 2));
        }
        else {
            llvm_value.value = Builder.CreateAlignedLoad(var_address, alignment, var_name);
        }

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

static BOOL pre_compile_load_variable(unsigned int node, sCompileInfo* info)
{
    char var_name[VAR_NAME_MAX];

    xstrncpy(var_name, gNodes[node].uValue.sLoadVariable.mVarName, VAR_NAME_MAX);

    sVar* var = get_variable_from_table(info->lv_table, var_name);

    if(var == NULL) {
        var = get_variable_from_table(info->gv_table, var_name);
    }

    if(var == NULL || var->mType == NULL) {
        compile_err_msg(info, "undeclared variable(1-3) %s", var_name);
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

    BOOL success_solve;
    solve_generics(&var_type, info->generics_type, &success_solve);

    solve_method_generics2(&var_type, info->method_generics_types);

    info->type = var_type;
    return TRUE;
}


BOOL compile_function(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

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

    sVarTable* fun_lv_table = gNodes[node].uValue.sFunction.mLVTable;

    char* param_types[PARAMS_MAX];
    char* param_names[PARAMS_MAX];

    int i;
    for(i=0; i<num_params; i++) {
        param_types[i] = gNodes[node].uValue.sFunction.mParams[i].mTypeName;
        param_names[i] = gNodes[node].uValue.sFunction.mParams[i].mName;
    }

    if(!add_function(fun_name, fun_base_name, result_type_name, num_params, param_types, param_names, var_arg, inline_, inherit_, static_, node_block, generics, coroutine, method_generics, fun_lv_table, info)) {
        return FALSE;
    }

    if(!generics && !method_generics) {
        sFunction fun = gFuncs[fun_name][gFuncs[fun_name].size()-1];

        int sline = gNodes[node].mLine;
        BOOL pre_compile = FALSE;
        if(!create_llvm_function(&fun, fun_lv_table, info, sline, pre_compile)) {
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

            solve_method_generics2(&lambda_type->mParamTypes[i], info->method_generics_types);
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

BOOL pre_compile_function(unsigned int node, sCompileInfo* info)
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

    if(!coroutine) {
        create_global_lvtable(info);
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

BOOL compile_coroutine(unsigned int node, sCompileInfo* info)
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

    sVarTable* lv_table = info->lv_table;

    sVarTable* fun_lv_table = init_var_table();
    fun_lv_table->mCoroutineTop = TRUE;
    fun_lv_table->mParent = cinfo.lv_table;
    info->lv_table = fun_lv_table;

    char real_fun_name[VAR_NAME_MAX];
    char real_fun_base_name[VAR_NAME_MAX];

    static int n = 0;
    n++;

    snprintf(real_fun_name, VAR_NAME_MAX, "%s_%d", fun_name, n);
    snprintf(real_fun_base_name, VAR_NAME_MAX, "%s_%d", fun_base_name, n);

    if(!add_function(real_fun_name, real_fun_base_name, result_type_name, num_params, param_types, param_names, var_arg, inline_, inherit_, static_, node_block, generics, coroutine, method_generics, fun_lv_table, info)) {
        return FALSE;
    }

    if(!generics && !method_generics) {
        sFunction fun = gFuncs[real_fun_name][gFuncs[real_fun_name].size()-1];

        int sline = gNodes[node].mLine;
        BOOL pre_compile = TRUE;
        if(!create_llvm_function(&fun, fun_lv_table, info, sline, pre_compile)) {
            return FALSE;
        }
    }

    sFunction fun = gFuncs[real_fun_name][0];

    Function* llvm_fun = fun.mLLVMFunction;

    sNodeType* lambda_type = create_node_type_with_class_name("lambda");

    lambda_type->mResultType = create_node_type_with_class_name(result_type_name);
    lambda_type->mNumParams = num_params;
    for(i=0; i<num_params; i++) {
        lambda_type->mParamTypes[i] = create_node_type_with_class_name(param_types[i]);

        BOOL success_solve;
        (void)solve_generics(&lambda_type->mParamTypes[i], info->generics_type, &success_solve);

        solve_method_generics2(&lambda_type->mParamTypes[i], info->method_generics_types);
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

    info->lv_table = lv_table;

    return TRUE;
}

BOOL pre_compile_coroutine(unsigned int node, sCompileInfo* info)
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

    sVarTable* lv_table = info->lv_table;

    sVarTable* fun_lv_table = init_var_table();
    fun_lv_table->mCoroutineTop = TRUE;
    fun_lv_table->mParent = cinfo.lv_table;
    info->lv_table = fun_lv_table;
    gNodes[node_block].uValue.sBlock.mLVTable = fun_lv_table;

    char* param_types[PARAMS_MAX];
    char* param_names[PARAMS_MAX];

    int i;
    for(i=0; i<num_params; i++) {
        param_types[i] = gNodes[node].uValue.sFunction.mParams[i].mTypeName;
        param_names[i] = gNodes[node].uValue.sFunction.mParams[i].mName;
    }

    char real_fun_name[VAR_NAME_MAX];
    char real_fun_base_name[VAR_NAME_MAX];

    static int n = 0;
    n++;

    snprintf(real_fun_name, VAR_NAME_MAX, "%s_%d", fun_name, n);
    snprintf(real_fun_base_name, VAR_NAME_MAX, "%s_%d", fun_base_name, n);

    sNodeType* lambda_type = create_node_type_with_class_name("lambda");

    lambda_type->mResultType = create_node_type_with_class_name(result_type_name);
    lambda_type->mNumParams = num_params;
    for(i=0; i<num_params; i++) {
        lambda_type->mParamTypes[i] = create_node_type_with_class_name(param_types[i]);

        BOOL success_solve;
        (void)solve_generics(&lambda_type->mParamTypes[i], info->generics_type, &success_solve);

        solve_method_generics2(&lambda_type->mParamTypes[i], info->method_generics_types);
    }

    LVALUE llvm_value;
    llvm_value.value = NULL;
    llvm_value.type = lambda_type;
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = lambda_type;

    info->lv_table = lv_table;

    return TRUE;
}

BOOL compile_external_function(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

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
            compile_err_msg(info, "Invalid type name %s 5\n", param->mTypeName);
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

    if(!add_function(fun_name, fun_base_name, result_type_name, num_params, param_types, param_names, var_arg, FALSE, inherit_, FALSE, 0, FALSE, FALSE, FALSE, NULL, info)) {
        return FALSE;
    }

    return TRUE;
}

BOOL pre_compile_external_function(unsigned int node, sCompileInfo* info)
{
    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

static BOOL compile_return(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

    int right_node = gNodes[node].mRight;
    int middle_node = gNodes[node].mMiddle;

    if(right_node != 0) {
        if(!compile(right_node, info)) {
            return FALSE;
        }

        sNodeType* right_type = clone_node_type(info->type);

        LVALUE rvalue = *get_value_from_stack(-1);
        Value* ret_value = rvalue.value;

        sNodeType* left_type = clone_node_type(info->function_result_type);

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
            compile_err_msg(info, "The different type between left type and right type. returing value.(2)");
            show_node_type(left_type);
            show_node_type(right_type);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        remove_from_right_value_object(rvalue.value, info);

        if(right_type->mHeap && left_type->mHeap) {
            free_objects_with_parents(rvalue.address, info);
        }
        else {
            free_objects_with_parents(nullptr, info);
        }
        free_right_value_objects(info);
        dec_stack_ptr(1, info);

        ret_value = rvalue.value;
        Builder.CreateRet(ret_value);
    }
    else {
        free_right_value_objects(info);
        free_objects_with_parents(nullptr, info);
        Builder.CreateRet(nullptr);
    }

    info->type = create_node_type_with_class_name("void");

    if(middle_node != 0) {
        if(!compile(middle_node, info)) {
            return FALSE;
        }
    }

    return TRUE;
}

static BOOL pre_compile_return(unsigned int node, sCompileInfo* info)
{
    int right_node = gNodes[node].mRight;
    int middle_node = gNodes[node].mMiddle;

    if(right_node != 0) {
        if(!pre_compile(right_node, info)) {
            return FALSE;
        }
    }

    if(middle_node != 0) {
        if(!pre_compile(middle_node, info)) {
            return FALSE;
        }
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}


BOOL compile_function_call(unsigned int node, sCompileInfo* info)
{
    int num_params = gNodes[node].uValue.sFunctionCall.mNumParams;
    int i;
    unsigned int params[PARAMS_MAX];
    for(i=0; i<num_params; i++) {
        params[i] = gNodes[node].uValue.sFunctionCall.mParams[i];
    }

    BOOL lambda_call = gNodes[node].uValue.sFunctionCall.mLambdaCall;
    BOOL inherit_ = gNodes[node].uValue.sFunctionCall.mInherit;

    BOOL message_passing = gNodes[node].uValue.sFunctionCall.mMessagePassing;

    Value* llvm_fun;
    std::vector<Value*> llvm_params;
    sNodeType* result_type;
    sNodeType* generics_type = info->generics_type;

    char fun_name[VAR_NAME_MAX];

    char* sname = gSName;
    int sline = gNodes[node].mLine;

    xstrncpy(fun_name, gNodes[node].uValue.sFunctionCall.mFunName, VAR_NAME_MAX);
    if(strcmp(fun_name, "__builtin_va_start") == 0) {
        xstrncpy(fun_name, "llvm.va_start", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_va_end") == 0) {
        xstrncpy(fun_name, "llvm.va_end", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_memmove") == 0) {
        xstrncpy(fun_name, "llvm.memmove.p0i8.p0i8.i64", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_memcpy") == 0) {
        xstrncpy(fun_name, "llvm.memcpy.p0i8.p0i8.i64", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_memset") == 0) {
        xstrncpy(fun_name, "llvm.memset.p0i8.i64", VAR_NAME_MAX);
    }

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
                compile_err_msg(info, "Calling lambda function parametor #%d is invalid. The different type between left type and right type.(3)", i);
                show_node_type(left_type);
                show_node_type(right_type);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            if(!info->no_output) {
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
            }

            llvm_params.push_back(rvalue.value);
        }

        result_type = lambda_type->mResultType;
        llvm_fun = lambda_value.value;
    }
    else {
        sNodeType* param_types[PARAMS_MAX];
        LVALUE param_values[PARAMS_MAX];

printf("%s %d: %s\n", gSName, yylineno, fun_name);
if(info->generics_type)show_node_type(info->generics_type);

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

                    char** method_generics_types_before = info->method_generics_types;
                    info->method_generics_types = method_generics_types;

                    fun = fun2;

                    char real_fun_name2[VAR_NAME_MAX];
                    int sline = gNodes[node].mLine;
                    //info->no_output = FALSE;
                    BOOL pre_compile = FALSE;
                    if(!create_generics_function(real_fun_name, fun_name, klass, &fun, real_fun_name2, info, sline, pre_compile, inherit_)) {
                        return FALSE;
                    }
                    //info->no_output = TRUE;

                    xstrncpy(gNodes[node].uValue.sFunctionCall.mRealFunName, real_fun_name2, VAR_NAME_MAX);
                    info->method_generics_types = method_generics_types_before;

                    for(i=0; i<GENERICS_TYPES_MAX; i++) {
                        free(method_generics_types[i]);
                    }
                }
                else if(fun.mGenerics) {
                    int sline = gNodes[node].mLine;
                    char real_fun_name2[VAR_NAME_MAX];
                    //info->no_output = FALSE;
                    BOOL pre_compile = FALSE;
                    if(!create_generics_function(real_fun_name, fun_name, klass, &fun, real_fun_name2, info, sline, pre_compile, inherit_)) {
                        return FALSE;
                    }
                    //info->no_output = TRUE;

                    xstrncpy(gNodes[node].uValue.sFunctionCall.mRealFunName, real_fun_name2, VAR_NAME_MAX);
                }
                else {
                    fun = gFuncs[real_fun_name][gFuncs[real_fun_name].size()-1];
                }
            }
            else {
                sNodeType* node_type = param_types2[0];

                char type_name2[VAR_NAME_MAX];
                convert_type_to_struct_name(node_type, type_name2);

                xstrncpy(real_fun_name, type_name2, VAR_NAME_MAX);
                xstrncat(real_fun_name, "_", VAR_NAME_MAX);
                xstrncat(real_fun_name, fun_name, VAR_NAME_MAX);

                if(gFuncs[real_fun_name].size() == 0) {
                    compile_err_msg(info, "Function not found(1)a %s\n", real_fun_name);
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

                char** method_generics_types_before = info->method_generics_types;
                info->method_generics_types = method_generics_types;

                fun = fun2;

                char real_fun_name2[VAR_NAME_MAX];
                int sline = gNodes[node].mLine;

                BOOL pre_compile = FALSE;
                if(!create_generics_function(real_fun_name, fun_name, klass, &fun, real_fun_name2, info, sline, pre_compile, inherit_)) {
                    return FALSE;
                }
                
                std::vector<sFunction> v = gFuncs[real_fun_name2];

                fun = v[v.size()-1];

                for(i=0; i<GENERICS_TYPES_MAX; i++) {
                    free(method_generics_types[i]);
                }

                info->method_generics_types = method_generics_types_before;
            }
            else if(fun.mGenerics) {
                int sline = gNodes[node].mLine;
                char real_fun_name2[VAR_NAME_MAX];
                BOOL pre_compile = FALSE;
                if(!create_generics_function(real_fun_name, fun_name, klass, &fun, real_fun_name2, info, sline, pre_compile, inherit_)) {

                    return FALSE;
                }

                xstrncpy(gNodes[node].uValue.sFunctionCall.mRealFunName, real_fun_name2, VAR_NAME_MAX);
                //char* real_fun_name2 = gNodes[node].uValue.sFunctionCall.mRealFunName;
                
                std::vector<sFunction> v = gFuncs[real_fun_name2];

                fun = v[v.size()-1];
            }
            else {
                fun = gFuncs[real_fun_name][gFuncs[real_fun_name].size()-1];
            }
        }
        else {
            info->generics_type = NULL;

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

                    fun = fun2;

                    char real_fun_name2[VAR_NAME_MAX];
                    int sline = gNodes[node].mLine;
                    //info->no_output = FALSE;
                    BOOL pre_compile = FALSE;
                    if(!create_generics_function(real_fun_name, fun_name, klass, &fun, real_fun_name2, info, sline, pre_compile, inherit_)) {
                        return FALSE;
                    }
                    //info->no_output = TRUE;

                    xstrncpy(gNodes[node].uValue.sFunctionCall.mRealFunName, real_fun_name2, VAR_NAME_MAX);

                    for(i=0; i<GENERICS_TYPES_MAX; i++) {
                        free(method_generics_types[i]);
                    }
                }
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

                fun = fun2;

                char** method_generics_types_before = info->method_generics_types;
                info->method_generics_types = method_generics_types;

                int sline = gNodes[node].mLine;
                char real_fun_name2[VAR_NAME_MAX];
                BOOL pre_compile = FALSE;
                if(!create_generics_function(fun_name, fun_name, NULL, &fun, real_fun_name2, info, sline, pre_compile, inherit_)) {
                    return FALSE;
                }

                xstrncpy(gNodes[node].uValue.sFunctionCall.mRealFunName, real_fun_name2, VAR_NAME_MAX);
                //char* real_fun_name2 = gNodes[node].uValue.sFunctionCall.mRealFunName;
                
                std::vector<sFunction> v = gFuncs[real_fun_name2];

                fun = v[v.size()-1];

                for(i=0; i<GENERICS_TYPES_MAX; i++) {
                    free(method_generics_types[i]);
                }

                info->method_generics_types = method_generics_types_before;
            }

            if(!fun.existance) {
                compile_err_msg(info, "Function not found(2) %s\n", fun_name);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        /// cast and type checking ///
        if(strcmp(fun_name, "llvm.memmove.p0i8.p0i8.i64") == 0 || strcmp(fun_name, "llvm.memcpy.p0i8.p0i8.i64") == 0 || strcmp(fun_name, "llvm.memset.p0i8.i64") == 0)
        {
            for(i=0; i<num_params; i++) {
                sNodeType* left_type = create_node_type_with_class_name(fun.mParamTypes[i]);
                sNodeType* right_type = param_types[num_params-i-1];

                BOOL success_solve;
                (void)solve_generics(&left_type, info->generics_type, &success_solve);

                solve_method_generics2(&left_type, info->method_generics_types);

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
                    compile_err_msg(info, "Calling function(%s) parametor #%d is invalid. The different type between left type and right type.(1)", fun_name, i);
                    show_node_type(left_type);
                    show_node_type(right_type);
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }

                if(!info->no_output) {
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
                }

                llvm_params.push_back(rvalue.value);
            }

            Value* value = ConstantInt::get(TheContext, llvm::APInt(1, 0, true)); 
            llvm_params.push_back(value);
        }
        else if(strcmp(fun_name, "llvm.va_start") == 0 || strcmp(fun_name, "llvm.va_end") == 0)
        {
            if(fun.mNumParams > num_params) {
                compile_err_msg(info, "Calling function parametor number is invalid %s (2)\n", fun_name);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            LVALUE param = param_values[num_params-0-1];

            param.value = Builder.CreateCast(Instruction::BitCast, param.value, PointerType::get(Type::getInt8Ty(TheContext), 0));

            llvm_params.push_back(param.value);
        }
        else if(!fun.mVarArg) {
            if(fun.mNumParams != num_params) {
                compile_err_msg(info, "Calling function parametor number is invalid %s(left %d, right %d) (3)\n", fun_name, fun.mNumParams, num_params);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            for(i=0; i<num_params; i++) {
                sNodeType* left_type = create_node_type_with_class_name(fun.mParamTypes[i]);
                sNodeType* right_type = param_types[num_params-i-1];

                BOOL success_solve;
                (void)solve_generics(&left_type, info->generics_type, &success_solve);

                solve_method_generics2(&left_type, info->method_generics_types);

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
                    compile_err_msg(info, "Calling function(%s) parametor #%d is invalid. The different type between left type and right type. (4)", fun_name, i);
                    show_node_type(left_type);
                    show_node_type(right_type);
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }

                if(!info->no_output) {
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
                }

                llvm_params.push_back(rvalue.value);
            }
        }
        else {
            if(fun.mNumParams > num_params) {
                compile_err_msg(info, "Calling function parametor number is invalid %s (5)\n", fun_name);
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

    solve_method_generics2(&result_type, info->method_generics_types);

    if(!info->no_output) {
        LVALUE llvm_value;
        llvm_value.value = Builder.CreateCall(llvm_fun, llvm_params);
        llvm_value.type = clone_node_type(result_type);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        push_value_to_stack_ptr(&llvm_value, info);
    }

    info->type = clone_node_type(result_type);

    info->generics_type = generics_type;

    return TRUE;
} 

BOOL pre_compile_function_call(unsigned int node, sCompileInfo* info)
{
    int num_params = gNodes[node].uValue.sFunctionCall.mNumParams;
    int i;
    unsigned int params[PARAMS_MAX];
    for(i=0; i<num_params; i++) {
        params[i] = gNodes[node].uValue.sFunctionCall.mParams[i];
    }

    BOOL lambda_call = gNodes[node].uValue.sFunctionCall.mLambdaCall;
    BOOL inherit_ = gNodes[node].uValue.sFunctionCall.mInherit;

    BOOL message_passing = gNodes[node].uValue.sFunctionCall.mMessagePassing;

    if(info->pre_compiling_generics_function) {
        return TRUE;
    }

    Value* llvm_fun;
    std::vector<Value*> llvm_params;
    sNodeType* result_type;
    sNodeType* generics_type = info->generics_type;

    char fun_name[VAR_NAME_MAX];

    xstrncpy(fun_name, gNodes[node].uValue.sFunctionCall.mFunName, VAR_NAME_MAX);

    if(lambda_call) {
        unsigned int lambda_node = gNodes[node].mLeft;

        /// go ///
        if(!pre_compile(lambda_node, info)) {
            return FALSE;
        }

        for(i=0; i<num_params; i++) {
            if(!pre_compile(params[i], info)) {
                return FALSE;
            }
        }
    }
    else {
        for(i=0; i<num_params; i++) {
            if(!pre_compile(params[i], info)) {
                return FALSE;
            }
        }
    }

    //BOOL no_output = info->no_output;
    //info->no_output = TRUE;

    /// generate generics function ///
    if(lambda_call) {
        unsigned int lambda_node = gNodes[node].mLeft;

        /// go ///
        if(!pre_compile(lambda_node, info)) {
            return FALSE;
        }

        sNodeType* lambda_type = clone_node_type(info->type);

        for(i=0; i<num_params; i++) {
            if(!pre_compile(params[i], info)) {
                return FALSE;
            }
        }

        result_type = lambda_type->mResultType;
    }
    else {
        sNodeType* param_types[PARAMS_MAX];
        LVALUE param_values[PARAMS_MAX];

        for(i=0; i<num_params; i++) {
            if(!pre_compile(params[i], info)) {
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
                //info->no_output = no_output;
                return TRUE;
            }
            else {
                sNodeType* node_type = param_types2[0];

                BOOL success_solve;
                (void)solve_generics(&node_type, info->generics_type, &success_solve);

                solve_method_generics2(&node_type, info->method_generics_types);

                char type_name2[VAR_NAME_MAX];
                convert_type_to_struct_name(node_type, type_name2);

                xstrncpy(real_fun_name, type_name2, VAR_NAME_MAX);
                xstrncat(real_fun_name, "_", VAR_NAME_MAX);
                xstrncat(real_fun_name, fun_name, VAR_NAME_MAX);

                if(gFuncs[real_fun_name].size() == 0) {
                    return TRUE;
/*
                    compile_err_msg(info, "Function not found(1)b %s\n", real_fun_name);
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return FALSE;
*/
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

                fun = fun2;

                char real_fun_name2[VAR_NAME_MAX];
                int sline = gNodes[node].mLine;

/*
                BOOL pre_compile = FALSE;
                if(!create_generics_function(real_fun_name, fun_name, klass, &fun, real_fun_name2, info, sline, pre_compile, inherit_)) {
                    return FALSE;
                }
*/

                xstrncpy(gNodes[node].uValue.sFunctionCall.mRealFunName, real_fun_name2, VAR_NAME_MAX);

                for(i=0; i<GENERICS_TYPES_MAX; i++) {
                    free(method_generics_types[i]);
                }
            }
            else if(fun.mGenerics) {
                int sline = gNodes[node].mLine;
                char real_fun_name2[VAR_NAME_MAX];
                BOOL pre_compile = FALSE;
/*
                if(!create_generics_function(real_fun_name, fun_name, klass, &fun, real_fun_name2, info, sline, pre_compile, inherit_)) {

                    return FALSE;
                }
*/

                xstrncpy(gNodes[node].uValue.sFunctionCall.mRealFunName, real_fun_name2, VAR_NAME_MAX);
            }
            else {
                fun = gFuncs[real_fun_name][gFuncs[real_fun_name].size()-1];
            }
        }
        else {
            info->generics_type = NULL;

            if(inherit_) {
                //info->no_output = no_output;
                info->generics_type = generics_type;
                return TRUE;
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

                fun = fun2;

/*
                int sline = gNodes[node].mLine;
                char real_fun_name2[VAR_NAME_MAX];
                BOOL pre_compile = FALSE;
                if(!create_generics_function(fun_name, fun_name, NULL, &fun, real_fun_name2, info, sline, pre_compile, inherit_)) {
                    info->generics_type = generics_type;
                    return FALSE;
                }
*/

//                xstrncpy(gNodes[node].uValue.sFunctionCall.mRealFunName, real_fun_name2, VAR_NAME_MAX);

                for(i=0; i<GENERICS_TYPES_MAX; i++) {
                    free(method_generics_types[i]);
                }
            }

            if(!fun.existance) {
                compile_err_msg(info, "Function not found(2) %s\n", fun_name);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                info->generics_type = generics_type;
                return TRUE;
            }
        }

        result_type = create_node_type_with_class_name(fun.mResultTypeName);
    }

    info->type = clone_node_type(result_type);

    //info->no_output = no_output;

    info->generics_type = generics_type;

    return TRUE;
}

static BOOL compile_if(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

/*
    sVarTable* lv_table = info->lv_table;
    info->lv_table = gNodes[node].uValue.sIf.mLVTable;
*/

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
    BOOL loop_top = FALSE;
    if(!compile_block(if_block, info, &last_expression_is_return, loop_top)) {
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

            BOOL loop_top = FALSE;
            if(!compile_block(elif_block, info, &last_expression_is_return, loop_top))
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
        BOOL loop_top = FALSE;
        if(!compile_block(else_block, info, &last_expression_is_return, loop_top))
        {
            return FALSE;
        }

        if(!last_expression_is_return) {
            Builder.CreateBr(cond_end_block);
        }
    }

    BasicBlock* current_block_before2;
    llvm_change_block(cond_end_block, &current_block_before2, info, FALSE);
//    info->lv_table = lv_table;

//    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

static BOOL pre_compile_if(unsigned int node, sCompileInfo* info)
{
    unsigned int else_block = gNodes[node].uValue.sIf.mElseBlock;
    int elif_num = gNodes[node].uValue.sIf.mElifNum;

/*
    sVarTable* lv_table = info->lv_table;
    sVarTable* block_lv_table = init_var_table();
    block_lv_table->mParent = info->lv_table;
    gNodes[node].uValue.sIf.mLVTable = block_lv_table;
*/

    /// compile expression ///
    unsigned int if_exp = gNodes[node].uValue.sIf.mIfExp;
    unsigned int if_block = gNodes[node].uValue.sIf.mIfBlock;

    if(!pre_compile(if_exp, info)) {
        return FALSE;
    }

    if(!pre_compile_block(if_block, info)) {
        return FALSE;
    }

    //// elif ///
    if(elif_num > 0) {
        int i;
        for(i=0; i<elif_num; i++) {
            unsigned int if_exp = gNodes[node].uValue.sIf.mElifExps[i];

            unsigned int elif_block = gNodes[node].uValue.sIf.mElifBlocks[i];

            if(!pre_compile(if_exp, info)) {
                return FALSE;
            }

            if(!pre_compile_block(elif_block, info)) {
                return FALSE;
            }
        }
    }

    if(else_block) {
        if(!pre_compile_block(else_block, info)) {
            return FALSE;
        }
    }

    info->type = create_node_type_with_class_name("void");
//    info->lv_table = lv_table;

    return TRUE;
}

static BOOL compile_create_object(unsigned int node, sCompileInfo* info)
{
    char type_name[VAR_NAME_MAX];

    xstrncpy(type_name, gNodes[node].uValue.sCreateObject.mTypeName, VAR_NAME_MAX);

    sNodeType* node_type = create_node_type_with_class_name(type_name);

    if(node_type == NULL || node_type->mClass == NULL) {
        compile_err_msg(info, "Invalid type name %s 6\n", type_name);
        return FALSE;
    }

    sNodeType* node_type2 = clone_node_type(node_type);

    BOOL success_solve;
    solve_generics(&node_type2, info->generics_type, &success_solve);

    solve_method_generics2(&node_type2, info->method_generics_types);
    node_type2->mHeap = TRUE;

    if(info->no_output) {
        info->type = node_type2;
        return TRUE;
    }

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

    Function* fun = TheModule->getFunction("nccalloc");

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

    Value* param3;
    param3 = llvm_create_string(type_name);

    params2.push_back(param3);

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

static BOOL pre_compile_create_object(unsigned int node, sCompileInfo* info)
{
    char type_name[VAR_NAME_MAX];

    xstrncpy(type_name, gNodes[node].uValue.sCreateObject.mTypeName, VAR_NAME_MAX);

    sNodeType* node_type = create_node_type_with_class_name(type_name);

    sNodeType* node_type2 = clone_node_type(node_type);

    BOOL success_solve;
    solve_generics(&node_type2, info->generics_type, &success_solve);

    solve_method_generics2(&node_type2, info->method_generics_types);
    node_type2->mHeap = TRUE;

    unsigned int left_node = gNodes[node].mLeft;

    Value* object_num;
    if(left_node == 0) {
    }
    else {
        if(!pre_compile(left_node, info)) {
            return FALSE;
        }
    }

    info->type = clone_node_type(node_type2);

    return TRUE;
}

static BOOL compile_clone(unsigned int node, sCompileInfo* info)
{
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

    return TRUE;
}

static BOOL pre_compile_clone(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);
    sNodeType* left_type2 = clone_node_type(left_type);
    left_type2->mHeap = TRUE;

    info->type = clone_node_type(left_type2);

    return TRUE;
}

static BOOL compile_delete(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

    unsigned int left_node = gNodes[node].mLeft;

    if(left_node == 0) {
        compile_err_msg(info, "require delete target object");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(!compile(left_node, info)) {
        return FALSE;
    }

    LVALUE llvm_value = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    remove_from_right_value_object(llvm_value.value, info);

    sNodeType* node_type = clone_node_type(info->type);

    free_object(node_type, llvm_value.address, TRUE, info);

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

static BOOL pre_compile_delete(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

BOOL compile_struct(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

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

    if(num_fields == 0) {
        if(!generics) {
            sNodeType* node_type = create_node_type_with_class_pointer(klass);
            BOOL new_create = TRUE;
            (void)create_llvm_struct_type(node_type, node_type, new_create, info);
            
            create_undefined_llvm_struct_type(node_type);
        }
    }
    else {
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
    }

    return TRUE;
}

BOOL pre_compile_struct(unsigned int node, sCompileInfo* info)
{
    
    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

BOOL compile_union(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

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

BOOL pre_compile_union(unsigned int node, sCompileInfo* info)
{

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

static BOOL compile_define_variable(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

    char var_name[VAR_NAME_MAX];
    xstrncpy(var_name, gNodes[node].uValue.sDefineVariable.mVarName, VAR_NAME_MAX);
    char type_name[VAR_NAME_MAX];
    xstrncpy(type_name, gNodes[node].uValue.sDefineVariable.mTypeName, VAR_NAME_MAX);
    BOOL extern_ = gNodes[node].uValue.sDefineVariable.mExtern;
    BOOL global = gNodes[node].uValue.sDefineVariable.mGlobal;

    unsigned int init_value = gNodes[node].uValue.sDefineVariable.mInitValue;

    sVar* var;

    sNodeType* var_type = create_node_type_with_class_name(type_name);
    if(var_type == NULL || var_type->mClass == NULL) {
        fprintf(stderr, "Invalid type name %s\n", type_name);
        return FALSE;
    }

    Value* llvm_value = NULL;
    BOOL constant = var_type->mConstant;
    int index = -1;
    if(global) {
        if(!add_variable_to_table(info->gv_table, var_name, var_type, llvm_value,  index, global, constant))
        {
            fprintf(stderr, "overflow variable table");
            return FALSE;
        }
    }

    if(global) {
        var = get_variable_from_table(info->gv_table, var_name);

        if(var == NULL) {
            compile_err_msg(info, "undeclared variable(22) %s", var_name);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }
    }
    else {
        var = get_variable_from_table(info->lv_table, var_name);

        if(var == NULL) {
            compile_err_msg(info, "undeclared variable(23) %s", var_name);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }
    }

    var_type = var->mType;

    BOOL success_solve;
    solve_generics(&var_type, info->generics_type, &success_solve);

    solve_method_generics2(&var_type, info->method_generics_types);

    var->mType = clone_node_type(var_type);

    if(var_type->mDynamicArrayNum != 0) {
        unsigned int node = var_type->mDynamicArrayNum;

        if(!compile(node, info)) {
            return FALSE;
        }

        LVALUE llvm_value = *get_value_from_stack(-1);

        Value* index_value = llvm_value.value;
        ConstantInt* const_index_value = NULL;

        dec_stack_ptr(1, info);

        if(dyn_cast<Constant>(llvm_value.value)) 
        {
            index_value = llvm_value.value;
            const_index_value = dyn_cast<ConstantInt>(llvm_value.value);
            var_type->mArrayNum[0] = const_index_value->getSExtValue();
            var_type->mArrayDimentionNum = 1;
        }
        else {
            sNodeType* index_type = info->type;

            if(!type_identify_with_class_name(index_type, "int"))
            {
                compile_err_msg(info, "Invalid index type");

                show_node_type(index_type);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            index_value = llvm_value.value;
            const_index_value = NULL;
            var_type->mPointerNum++;
        }

        if(global) {
            if(const_index_value == NULL) {
                compile_err_msg(info, "Global Variable dynami index array should be constant");
                show_node_type(var_type);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
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

            if(extern_) {
                if(var->mLLVMValue == NULL && TheModule->getNamedGlobal(var_name) == nullptr)
                {
                    GlobalVariable* address = new GlobalVariable(*TheModule, llvm_var_type, false, GlobalValue::ExternalLinkage, 0, var_name, nullptr, GlobalValue::NotThreadLocal, 0, true);

                    address->setAlignment(alignment);
                    var->mLLVMValue = address;
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
            }
        }
        else {
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
    }
/*
    else if(var->mConstant) {
        compile_err_msg(info, "Require right value for constant");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }
*/
    else if(global) {
        Type* llvm_var_type;
        if(!create_llvm_type_from_node_type(&llvm_var_type, var_type, var_type, info))
        {
            compile_err_msg(info, "Getting llvm type failed");
            show_node_type(var_type);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        if(type_identify_with_class_name(var_type, "__builtin_va_list")) {
            llvm_var_type = ArrayType::get(llvm_var_type, 1);
        }

        int alignment = get_llvm_alignment_from_node_type(var_type);

        if(extern_) {
            if(var->mLLVMValue == NULL && TheModule->getNamedGlobal(var_name) == nullptr)
            {
                GlobalVariable* address = new GlobalVariable(*TheModule, llvm_var_type, false, GlobalValue::ExternalLinkage, 0, var_name, nullptr, GlobalValue::NotThreadLocal, 0, true);

                address->setAlignment(alignment);
                var->mLLVMValue = address;
            }
        }
        else {
            if(TheModule->getNamedGlobal(var_name) != nullptr)
            {
                TheModule->getNamedGlobal(var_name)->eraseFromParent();
            }
            
            GlobalVariable* address = new GlobalVariable(*TheModule, llvm_var_type, false, GlobalValue::ExternalLinkage, 0, var_name, nullptr, GlobalValue::NotThreadLocal, 0, false);

            address->setAlignment(alignment);
            if(init_value != 0) {
                if(!compile(init_value, info)) {
                    return FALSE;
                }

                LVALUE rvalue = *get_value_from_stack(-1);

                if(dyn_cast<Constant>(rvalue.value)) 
                {
                    Constant* initializer = dyn_cast<Constant>(rvalue.value);

                    address->setInitializer(initializer);

                    var->mLLVMValue = address;
                }
                else {
                    compile_err_msg(info, "global variable initializer should be constant value");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }
            else {
                ConstantAggregateZero* initializer = ConstantAggregateZero::get(llvm_var_type);

                address->setInitializer(initializer);

                var->mLLVMValue = address;
            }
        }
    }
    else {
        Type* llvm_var_type;
        if(!create_llvm_type_from_node_type(&llvm_var_type, var_type, var_type, info))
        {
            compile_err_msg(info, "Getting llvm type failed");
            show_node_type(var_type);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        if(type_identify_with_class_name(var_type, "__builtin_va_list")) {
            llvm_var_type = ArrayType::get(llvm_var_type, 1);
        }

        int alignment = get_llvm_alignment_from_node_type(var_type);

        Value* address = Builder.CreateAlloca(llvm_var_type, 0, var_name);

        var->mLLVMValue = address;

        BOOL parent = FALSE;
        int index = get_variable_index(info->lv_table, var_name, &parent);

        store_address_to_lvtable(index, address, info);
    }

    info->type = var_type;

    return TRUE;
}

static BOOL pre_compile_define_variable(unsigned int node, sCompileInfo* info)
{
    char var_name[VAR_NAME_MAX];
    xstrncpy(var_name, gNodes[node].uValue.sDefineVariable.mVarName, VAR_NAME_MAX);
    char type_name[VAR_NAME_MAX];
    xstrncpy(type_name, gNodes[node].uValue.sDefineVariable.mTypeName, VAR_NAME_MAX);
    BOOL extern_ = gNodes[node].uValue.sDefineVariable.mExtern;
    BOOL global = gNodes[node].uValue.sDefineVariable.mGlobal;
    unsigned int init_value = gNodes[node].uValue.sDefineVariable.mInitValue;
    sVar* var;

    sNodeType* var_type = create_node_type_with_class_name(type_name);
    if(var_type == NULL || var_type->mClass == NULL) {
        fprintf(stderr, "Invalid type name %s\n", type_name);
        return FALSE;
    }

    Value* llvm_value = NULL;
    BOOL constant = var_type->mConstant;
    int index = -1;

    if(!add_variable_to_table(info->lv_table, var_name, var_type, llvm_value,  index, global, constant))
    {
        fprintf(stderr, "overflow variable table");
        return FALSE;
    }

    if(global) {
        var = get_variable_from_table(info->gv_table, var_name);

        if(var == NULL) {
            compile_err_msg(info, "undeclared variable(24) %s", var_name);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }
    }
    else {
        var = get_variable_from_table(info->lv_table, var_name);

        if(var == NULL) {
            compile_err_msg(info, "undeclared variable(25) %s", var_name);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }
    }

    var_type = var->mType;

    var->mType = clone_node_type(var_type);

    Value* index_value = NULL;
    if(var_type->mDynamicArrayNum != 0) {
        unsigned int node = var_type->mDynamicArrayNum;

        if(!pre_compile(node, info)) {
            return FALSE;
        }
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

static BOOL compile_equals(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("bool");
        return TRUE;
    }

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
        compile_err_msg(info, "Operand posibility failed. equals");
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

static BOOL pre_compile_equals(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    int right_node = gNodes[node].mRight;
    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

static BOOL compile_not_equals(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("bool");
        return TRUE;
    }

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

static BOOL pre_compile_not_equals(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    int right_node = gNodes[node].mRight;
    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

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

    solve_method_generics2(&field_type, info->method_generics_types);

    if(info->no_output) {
        info->type = field_type;
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

static BOOL pre_compile_load_field(unsigned int node, sCompileInfo* info)
{
    char var_name[VAR_NAME_MAX]; 
    xstrncpy(var_name, gNodes[node].uValue.sLoadField.mVarName, VAR_NAME_MAX);

    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!pre_compile(lnode, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    int field_index = get_field_index(left_type->mClass, var_name, NULL);

    sNodeType* field_type = clone_node_type(left_type->mClass->mFields[field_index]);

    BOOL success_solve;
    solve_generics(&field_type, left_type, &success_solve);

    solve_method_generics2(&field_type, info->method_generics_types);

    info->type = clone_node_type(field_type);

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

    if(info->no_output) {
        info->type = right_type;
        return TRUE;
    }

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

    solve_method_generics2(&field_type, info->method_generics_types);

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

static BOOL pre_compile_store_field(unsigned int node, sCompileInfo* info)
{
    char var_name[VAR_NAME_MAX];
    xstrncpy(var_name, gNodes[node].uValue.sStoreField.mVarName, VAR_NAME_MAX);

    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!pre_compile(lnode, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    /// compile right node ///
    unsigned int rnode = gNodes[node].mRight;

    if(!pre_compile(rnode, info)) {
        return FALSE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    info->type = right_type;

    return TRUE;
}

static BOOL compile_and_and(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("bool");
        return TRUE;
    }

    sFunction* fun = (sFunction*)info->function;

    Function* llvm_function = fun->mLLVMFunction;

    info->andand_result_var = (void*)Builder.CreateAlloca(IntegerType::get(TheContext, 1), 0, "andand_result_var");

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

    //free_right_value_objects(info);

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

    //free_right_value_objects(info);
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

static BOOL pre_compile_and_and(unsigned int node, sCompileInfo* info)
{
    /// compile expression ///
    unsigned int left_node = gNodes[node].mLeft;

    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    unsigned int right_node = gNodes[node].mRight;

    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

static BOOL compile_or_or(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("bool");
        return TRUE;
    }

    sFunction* fun = (sFunction*)info->function;

    Function* llvm_function = fun->mLLVMFunction;

    info->oror_result_var = (void*)Builder.CreateAlloca(IntegerType::get(TheContext, 1), 0, "oror_result_var");
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

    //free_right_value_objects(info);

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

    //free_right_value_objects(info);
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

static BOOL pre_compile_or_or(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    unsigned int right_node = gNodes[node].mRight;

    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

static BOOL compile_gt(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("bool");
        return TRUE;
    }

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
    if(left_type->mUnsigned || right_type->mUnsigned) {
        llvm_value.value = Builder.CreateICmpUGT(lvalue.value, rvalue.value, "getmp");
    }
    else {
        llvm_value.value = Builder.CreateICmpSGT(lvalue.value, rvalue.value, "gttmp");
    }
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

static BOOL pre_compile_gt(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    int right_node = gNodes[node].mRight;
    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

static BOOL compile_lt(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("bool");
        return TRUE;
    }

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
    if(left_type->mUnsigned || right_type->mUnsigned) {
        llvm_value.value = Builder.CreateICmpULT(lvalue.value, rvalue.value, "letmp");
    }
    else {
        llvm_value.value = Builder.CreateICmpSLT(lvalue.value, rvalue.value, "letmp");
    }
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

static BOOL pre_compile_lt(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    int right_node = gNodes[node].mRight;
    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

static BOOL compile_ge(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("bool");
        return TRUE;
    }

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
    if(left_type->mUnsigned || right_type->mUnsigned) {
        llvm_value.value = Builder.CreateICmpUGE(lvalue.value, rvalue.value, "getmp");
    }
    else {
        llvm_value.value = Builder.CreateICmpSGE(lvalue.value, rvalue.value, "getmp");
    }
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

static BOOL pre_compile_ge(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    int right_node = gNodes[node].mRight;
    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

static BOOL compile_le(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("bool");
        return TRUE;
    }

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
    if(left_type->mUnsigned || right_type->mUnsigned) {
        llvm_value.value = Builder.CreateICmpULE(lvalue.value, rvalue.value, "leeqtmp");
    }
    else {
        llvm_value.value = Builder.CreateICmpSLE(lvalue.value, rvalue.value, "leeqtmp");
    }
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

static BOOL pre_compile_le(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    int right_node = gNodes[node].mRight;
    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

static BOOL compile_logical_denial(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("bool");
        return TRUE;
    }

    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }
    sNodeType* left_type = clone_node_type(info->type);

    LVALUE lvalue = *get_value_from_stack(-1);

    sNodeType* bool_type = create_node_type_with_class_name("bool");

    if(auto_cast_posibility(bool_type, left_type)) {
        if(!cast_right_type_to_left_type(bool_type, &left_type, &lvalue, info))
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

    LVALUE rvalue;
    rvalue.value = ConstantInt::get(Type::getInt1Ty(TheContext), 0);
    rvalue.type = nullptr;
    rvalue.address = nullptr;
    rvalue.var = nullptr;
    rvalue.binded_value = FALSE;
    rvalue.load_field = FALSE;

    LVALUE llvm_value;
    llvm_value.value = Builder.CreateICmpEQ(lvalue.value, rvalue.value, "logical denial");
    llvm_value.type = create_node_type_with_class_name("bool");
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    dec_stack_ptr(1, info);
    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

static BOOL pre_compile_logical_denial(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

static BOOL compile_complement(unsigned int node, sCompileInfo* info)
{
    int expression_node = gNodes[node].mLeft;

    if(!compile(expression_node, info))
    {
        return FALSE;
    }

    sNodeType* left_node_type = clone_node_type(info->type);

    if(info->no_output) {
        info->type = left_node_type;
        return TRUE;
    }

    LVALUE lvalue = *get_value_from_stack(-1);
    
    if(type_identify_with_class_name(left_node_type, "char"))
    {
        LVALUE rvalue;
        rvalue.value = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0xFF);

        LVALUE llvm_value;
        llvm_value.value = Builder.CreateXor(lvalue.value, rvalue.value, "xortmp");
        llvm_value.type = clone_node_type(left_node_type);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(1, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type= left_node_type;
    }
    else if(type_identify_with_class_name(left_node_type, "short"))
    {
        LVALUE rvalue;
        rvalue.value = ConstantInt::get(Type::getInt16Ty(TheContext), (uint16_t)0xFFFF);

        LVALUE llvm_value;
        llvm_value.value = Builder.CreateXor(lvalue.value, rvalue.value, "xortmp");
        llvm_value.type = clone_node_type(left_node_type);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(1, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type= left_node_type;
    }
    else if(type_identify_with_class_name(left_node_type, "int"))
    {
        LVALUE rvalue;
        rvalue.value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0xFFFFFFFF);

        LVALUE llvm_value;
        llvm_value.value = Builder.CreateXor(lvalue.value, rvalue.value, "xortmp");
        llvm_value.type = clone_node_type(left_node_type);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(1, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type= left_node_type;
    }
    else if(type_identify_with_class_name(left_node_type, "long"))
    {
        LVALUE rvalue;
        rvalue.value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0xFFFFFFFFFFFFFFFF);

        LVALUE llvm_value;
        llvm_value.value = Builder.CreateXor(lvalue.value, rvalue.value, "xortmp");
        llvm_value.type = clone_node_type(left_node_type);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(1, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type= left_node_type;
    }
    else {
        compile_err_msg(info, "Invalid type for operator ~");
        info->err_num++;
    }

    return TRUE;
}

static BOOL pre_compile_complement(unsigned int node, sCompileInfo* info)
{
    int expression_node = gNodes[node].mLeft;

    if(!pre_compile(expression_node, info))
    {
        return FALSE;
    }

    sNodeType* left_node_type = clone_node_type(info->type);

    info->type = left_node_type;

    return TRUE;
}

static BOOL compile_dereffernce(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    sNodeType* derefference_type = clone_node_type(left_type);

    if(info->no_output) {
        info->type = derefference_type;
        return TRUE;
    }

    if(derefference_type->mPointerNum == 0) {
        compile_err_msg(info, "This is not pointer type1(%s)", derefference_type->mClass->mName);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    int alignment = get_llvm_alignment_from_node_type(derefference_type);

    derefference_type->mPointerNum--;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    LVALUE llvm_value;
    llvm_value.value = Builder.CreateAlignedLoad(lvalue.value, alignment, "derefference_value");
    llvm_value.type = derefference_type;
    llvm_value.address = lvalue.value;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = derefference_type;

    return TRUE;
}

static BOOL pre_compile_dereffernce(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    sNodeType* derefference_type = clone_node_type(left_type);

    info->type = derefference_type;

    return TRUE;
}

static BOOL compile_reffernce(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    if(info->no_output) {
        sNodeType* left_type = info->type;

        sNodeType* refference_type = clone_node_type(left_type);

        refference_type->mPointerNum++;

        info->type = refference_type;

        return TRUE;
    }

    if(lvalue.address == nullptr) {
        compile_err_msg(info, "Can't get address of this value on & operator");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    sNodeType* left_type = info->type;

    sNodeType* refference_type = clone_node_type(left_type);

    refference_type->mPointerNum++;

    LVALUE llvm_value;
    llvm_value.value = lvalue.address;
    llvm_value.type = refference_type;
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = refference_type;

    return TRUE;
}

static BOOL pre_compile_reffernce(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    sNodeType* refference_type = clone_node_type(left_type);

    refference_type->mPointerNum++;

    info->type = refference_type;

    return TRUE;
}

static BOOL compile_plus_eq(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

    unsigned int left_node = gNodes[node].mLeft;

    BOOL derefference = gNodes[left_node].mNodeType == kNodeTypeDerefference;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    if(left_type->mPointerNum > 0) {
        left_type->mPointerNum--;

        if(derefference && left_type->mPointerNum == 0) {
            int alignment = get_llvm_alignment_from_node_type(left_type);

            Value* address = lvalue.value;

            Type* llvm_left_type;
            if(!create_llvm_type_from_node_type(&llvm_left_type, left_type, left_type, info))
            {
                compile_err_msg(info, "Getting llvm type failed(10)");
                show_node_type(left_type);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            Value* left_value = address;
            Value* left_value2 = Builder.CreateCast(Instruction::PtrToInt, left_value, IntegerType::get(TheContext, 64));

            Value* right_value;
            if(type_identify_with_class_name(right_type, "long")) {
                right_value = rvalue.value;
            }
            else {
                if(right_type->mPointerNum > 0 || right_type->mArrayDimentionNum > 0) {
                    right_value = Builder.CreateCast(Instruction::PtrToInt, rvalue.value, IntegerType::get(TheContext, 64), "sextZ-p");
                }
                else {
                    right_value = Builder.CreateCast(Instruction::SExt, rvalue.value, IntegerType::get(TheContext, 64), "sextZ");
                }
            }

            uint64_t alloc_size = 0;
            if(!get_size_from_node_type(&alloc_size, left_type, left_type, info))
            {
                return FALSE;
            }

            Value* alloc_size_value = ConstantInt::get(Type::getInt64Ty(TheContext), alloc_size);

            right_value = Builder.CreateMul(right_value, alloc_size_value, "multtmp", false, true);

            Value* value = Builder.CreateAdd(left_value2, right_value, "adddtmp", false, true);
            value = Builder.CreateCast(Instruction::IntToPtr, value, PointerType::get(llvm_left_type,0), "IntTOPtr5c");
            Builder.CreateAlignedStore(value, lvalue.address, alignment);
        }
        else {
            int alignment = get_llvm_alignment_from_node_type(left_type);

            if(auto_cast_posibility(left_type, right_type)) {
                if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
                {
                    compile_err_msg(info, "Cast failed");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }

            Value* address = lvalue.value;

            Value* add_lvalue = Builder.CreateAlignedLoad(address, alignment);
            Value* add_rvalue = rvalue.value;

            Value* value = Builder.CreateAdd(add_lvalue, add_rvalue, "addtmp", false, true);

            Builder.CreateAlignedStore(value, address, alignment);
        }
    }
    else {
        int alignment = get_llvm_alignment_from_node_type(left_type);

        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        Value* address = lvalue.address;

        Value* add_lvalue = Builder.CreateAlignedLoad(address, alignment);
        Value* add_rvalue = rvalue.value;

        Value* value = Builder.CreateAdd(add_lvalue, add_rvalue, "addtmp", false, true);

        Builder.CreateAlignedStore(value, address, 8);
    }

    return TRUE;
}

static BOOL pre_compile_plus_eq(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    unsigned int right_node = gNodes[node].mRight;

    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

static BOOL compile_minus_eq(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

    unsigned int left_node = gNodes[node].mLeft;

    BOOL derefference = gNodes[left_node].mNodeType == kNodeTypeDerefference;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    if(left_type->mPointerNum > 0) {
        left_type->mPointerNum--;

        if(derefference && left_type->mPointerNum == 0) {
            int alignment = get_llvm_alignment_from_node_type(left_type);

            Value* address = lvalue.value;

            Type* llvm_left_type;
            if(!create_llvm_type_from_node_type(&llvm_left_type, left_type, left_type, info))
            {
                compile_err_msg(info, "Getting llvm type failed(10)");
                show_node_type(left_type);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            Value* left_value = address;
            Value* left_value2 = Builder.CreateCast(Instruction::PtrToInt, left_value, IntegerType::get(TheContext, 64));

            Value* right_value;
            if(type_identify_with_class_name(right_type, "long")) {
                right_value = rvalue.value;
            }
            else {
                if(right_type->mPointerNum > 0 || right_type->mArrayDimentionNum > 0) {
                    right_value = Builder.CreateCast(Instruction::PtrToInt, rvalue.value, IntegerType::get(TheContext, 64), "sext3-p");
                }
                else {
                    right_value = Builder.CreateCast(Instruction::SExt, rvalue.value, IntegerType::get(TheContext, 64), "sext3");
                }
            }

            uint64_t alloc_size = 0;
            if(!get_size_from_node_type(&alloc_size, left_type, left_type, info))
            {
                return FALSE;
            }

            Value* alloc_size_value = ConstantInt::get(Type::getInt64Ty(TheContext), alloc_size);

            right_value = Builder.CreateMul(right_value, alloc_size_value, "multtmp", false, true);

            Value* value = Builder.CreateSub(left_value2, right_value, "subtmp", false, true);
            value = Builder.CreateCast(Instruction::IntToPtr, value, PointerType::get(llvm_left_type,0), "IntTOPtr6d");
            Builder.CreateAlignedStore(value, lvalue.address, alignment);
        }
        else {
            int alignment = get_llvm_alignment_from_node_type(left_type);

            if(auto_cast_posibility(left_type, right_type)) {
                if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
                {
                    compile_err_msg(info, "Cast failed");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }

            Value* address = lvalue.value;

            Value* add_lvalue = Builder.CreateAlignedLoad(address, alignment);
            Value* add_rvalue = rvalue.value;

            Value* value = Builder.CreateSub(add_lvalue, add_rvalue, "subtmp", false, true);

            Builder.CreateAlignedStore(value, address, alignment);
        }
    }
    else {
        int alignment = get_llvm_alignment_from_node_type(left_type);

        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        Value* address = lvalue.address;

        Value* add_lvalue = Builder.CreateAlignedLoad(address, alignment);
        Value* add_rvalue = rvalue.value;

        Value* value = Builder.CreateSub(add_lvalue, add_rvalue, "subtmp", false, true);

        Builder.CreateAlignedStore(value, address, 8);
    }

    return TRUE;
}

static BOOL pre_compile_minus_eq(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    unsigned int right_node = gNodes[node].mRight;

    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

static BOOL compile_mult_eq(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

    unsigned int left_node = gNodes[node].mLeft;

    BOOL derefference = gNodes[left_node].mNodeType == kNodeTypeDerefference;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    int alignment = get_llvm_alignment_from_node_type(left_type);

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    Value* address = lvalue.address;

    Value* add_lvalue = Builder.CreateAlignedLoad(address, alignment);
    Value* add_rvalue = rvalue.value;

    Value* value = Builder.CreateMul(add_lvalue, add_rvalue, "multmp", false, true);

    Builder.CreateAlignedStore(value, address, 8);

    return TRUE;
}

static BOOL pre_compile_mult_eq(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    unsigned int right_node = gNodes[node].mRight;

    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

static BOOL compile_div_eq(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

    unsigned int left_node = gNodes[node].mLeft;

    BOOL derefference = gNodes[left_node].mNodeType == kNodeTypeDerefference;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    int alignment = get_llvm_alignment_from_node_type(left_type);

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    Value* address = lvalue.address;

    Value* add_lvalue = Builder.CreateAlignedLoad(address, alignment);
    Value* add_rvalue = rvalue.value;

    Value* value;
    if(left_type->mUnsigned) {
        value = Builder.CreateUDiv(add_lvalue, add_rvalue, "divtmp");
    }
    else {
        value = Builder.CreateSDiv(add_lvalue, add_rvalue, "divtmp");
    }

    Builder.CreateAlignedStore(value, address, 8);

    return TRUE;
}

static BOOL pre_compile_div_eq(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    unsigned int right_node = gNodes[node].mRight;

    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

static BOOL compile_mod_eq(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

    unsigned int left_node = gNodes[node].mLeft;

    BOOL derefference = gNodes[left_node].mNodeType == kNodeTypeDerefference;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    int alignment = get_llvm_alignment_from_node_type(left_type);

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    Value* address = lvalue.address;

    Value* add_lvalue = Builder.CreateAlignedLoad(address, alignment);
    Value* add_rvalue = rvalue.value;

    Value* value;
    if(left_type->mUnsigned) {
        value = Builder.CreateURem(add_lvalue, add_rvalue, "remtmp");
    }
    else {
        value = Builder.CreateSRem(add_lvalue, add_rvalue, "remtmp");
    }

    Builder.CreateAlignedStore(value, address, 8);

    return TRUE;
}

static BOOL pre_compile_mod_eq(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    unsigned int right_node = gNodes[node].mRight;

    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

static BOOL compile_and_eq(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

    unsigned int left_node = gNodes[node].mLeft;

    BOOL derefference = gNodes[left_node].mNodeType == kNodeTypeDerefference;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    int alignment = get_llvm_alignment_from_node_type(left_type);

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    Value* address = lvalue.address;

    Value* add_lvalue = Builder.CreateAlignedLoad(address, alignment);
    Value* add_rvalue = rvalue.value;

    Value* value = Builder.CreateAnd(add_lvalue, add_rvalue, "andtmp");

    Builder.CreateAlignedStore(value, address, 8);

    return TRUE;
}

static BOOL pre_compile_and_eq(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    unsigned int right_node = gNodes[node].mRight;

    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

static BOOL compile_xor_eq(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

    unsigned int left_node = gNodes[node].mLeft;

    BOOL derefference = gNodes[left_node].mNodeType == kNodeTypeDerefference;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    int alignment = get_llvm_alignment_from_node_type(left_type);

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    Value* address = lvalue.address;

    Value* add_lvalue = Builder.CreateAlignedLoad(address, alignment);
    Value* add_rvalue = rvalue.value;

    Value* value = Builder.CreateXor(add_lvalue, add_rvalue, "xortmp");

    Builder.CreateAlignedStore(value, address, 8);

    return TRUE;
}

static BOOL pre_compile_xor_eq(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    unsigned int right_node = gNodes[node].mRight;

    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

static BOOL compile_or_eq(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

    unsigned int left_node = gNodes[node].mLeft;

    BOOL derefference = gNodes[left_node].mNodeType == kNodeTypeDerefference;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    int alignment = get_llvm_alignment_from_node_type(left_type);

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    Value* address = lvalue.address;

    Value* add_lvalue = Builder.CreateAlignedLoad(address, alignment);
    Value* add_rvalue = rvalue.value;

    Value* value = Builder.CreateOr(add_lvalue, add_rvalue, "ortmp");

    Builder.CreateAlignedStore(value, address, 8);

    return TRUE;
}

static BOOL pre_compile_or_eq(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    unsigned int right_node = gNodes[node].mRight;

    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

static BOOL compile_lshift_eq(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

    unsigned int left_node = gNodes[node].mLeft;

    BOOL derefference = gNodes[left_node].mNodeType == kNodeTypeDerefference;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    int alignment = get_llvm_alignment_from_node_type(left_type);

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    Value* address = lvalue.address;

    Value* add_lvalue = Builder.CreateAlignedLoad(address, alignment);
    Value* add_rvalue = rvalue.value;

    Value* value = Builder.CreateShl(add_lvalue, add_rvalue, "lshifttmp");

    Builder.CreateAlignedStore(value, address, 8);

    return TRUE;
}

static BOOL pre_compile_lshift_eq(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    unsigned int right_node = gNodes[node].mRight;

    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

static BOOL compile_rshift_eq(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

    unsigned int left_node = gNodes[node].mLeft;

    BOOL derefference = gNodes[left_node].mNodeType == kNodeTypeDerefference;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    int alignment = get_llvm_alignment_from_node_type(left_type);

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    Value* address = lvalue.address;

    Value* add_lvalue = Builder.CreateAlignedLoad(address, alignment);
    Value* add_rvalue = rvalue.value;

    Value* value = Builder.CreateAShr(add_lvalue, add_rvalue, "rshifttmp");

    Builder.CreateAlignedStore(value, address, 8);

    return TRUE;
}

static BOOL pre_compile_rshift_eq(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    unsigned int right_node = gNodes[node].mRight;

    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

static BOOL compile_load_element(unsigned int node, sCompileInfo* info)
{
    int num_dimention = gNodes[node].uValue.sLoadElement.mArrayDimentionNum;
    int i;
    unsigned int index_node[ARRAY_DIMENTION_MAX];
    for(i=0; i<num_dimention; i++) {
        index_node[i] = gNodes[node].uValue.sLoadElement.mIndex[i];
    }
    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);

    sVar* var = lvalue.var;

    if(left_type->mArrayDimentionNum == 0 && left_type->mPointerNum == 0) 
    {
        compile_err_msg(info, "neo-c can't get an element from this type.");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    /// compile middle node ///
    LVALUE rvalue[ARRAY_DIMENTION_MAX];
    for(i=0; i<num_dimention; i++) {
        unsigned int mnode = index_node[i];

        if(!compile(mnode, info)) {
            return FALSE;
        }

        sNodeType* middle_type = info->type;

        rvalue[i] = *get_value_from_stack(-1);

        sNodeType* int_type = create_node_type_with_class_name("int");

        if(!cast_right_type_to_left_type(int_type, &middle_type, &rvalue[i], info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        if(!type_identify_with_class_name(middle_type, "int")) {
            compile_err_msg(info, "Type of index should be number");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    /// generate code ///
    sNodeType* var_type = clone_node_type(left_type);

    if(var_type->mArrayDimentionNum > 0) {
        var_type->mArrayDimentionNum-=num_dimention;
    }
    else {
        var_type->mPointerNum--;
    }

    //if(var_type->mPointerNum == 0) {
        var_type->mHeap = FALSE;
    //}

    if(info->no_output) {
        info->type = var_type;
        return TRUE;
    }

    /// go ///
    Value* element_value;
    Value* load_element_addresss;
    if(!info->no_output) {
        if(left_type->mArrayDimentionNum > num_dimention) {
            int i;
            Value* lvalue2 = lvalue.address;

            load_element_addresss = lvalue2;

            Value* indices[left_type->mArrayDimentionNum+1];

            int j;
            for(j=0; j<left_type->mArrayDimentionNum-num_dimention; j++) {
                indices[j] = ConstantInt::get(TheContext, llvm::APInt(32, 0, false)); 
            }
            int k=0;
            for(; j<left_type->mArrayDimentionNum; j++, k++) {
                indices[j] = rvalue[k].value;
            }
            load_element_addresss = Builder.CreateInBoundsGEP(load_element_addresss, ArrayRef<Value*>(indices, left_type->mArrayDimentionNum));

            for(j=0; j<left_type->mArrayDimentionNum; j++) {
                indices[j] = ConstantInt::get(TheContext, llvm::APInt(32, 0, false)); 
            }
            load_element_addresss = Builder.CreateInBoundsGEP(load_element_addresss, ArrayRef<Value*>(indices, left_type->mArrayDimentionNum));

            sNodeType* var_type3 = clone_node_type(var_type);
            var_type3->mPointerNum -= num_dimention;
            var_type3->mPointerNum+=2;
            var_type3->mArrayDimentionNum = 0;

            Type* llvm_var_type2;
            if(!create_llvm_type_from_node_type(&llvm_var_type2, var_type3, var_type3, info))
            {
                compile_err_msg(info, "Getting llvm type failed(10)");
                show_node_type(var_type3);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            int alignment = get_llvm_alignment_from_node_type(var_type);

            if(var_type3->mPointerNum == 0) {
                element_value = Builder.CreateAlignedLoad(load_element_addresss, alignment, "element");
            }
            else {
                load_element_addresss = Builder.CreateCast(Instruction::BitCast, load_element_addresss, llvm_var_type2);
                element_value = load_element_addresss;
            }
        }
        else if(left_type->mArrayDimentionNum == 1) {
            sNodeType* var_type2 = clone_node_type(var_type);
            var_type2->mPointerNum++;

            Type* llvm_var_type;
            if(!create_llvm_type_from_node_type(&llvm_var_type, var_type2, var_type2, info))
            {
                compile_err_msg(info, "Getting llvm type failed(10)");
                show_node_type(var_type2);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            Value* lvalue2 = Builder.CreateCast(Instruction::BitCast, lvalue.address, llvm_var_type);
            load_element_addresss = Builder.CreateGEP(lvalue2, rvalue[0].value, "element_address");

            int alignment = get_llvm_alignment_from_node_type(var_type);

            element_value = Builder.CreateAlignedLoad(load_element_addresss, alignment, "element");
        }
        else if(left_type->mArrayDimentionNum == 2) {
            int i;
            Value* lvalue2 = lvalue.address;

            load_element_addresss = lvalue2;

            Value* indices[2];

            indices[0] = ConstantInt::get(TheContext, llvm::APInt(32, 0, false)); 

            indices[1] = rvalue[0].value;

            load_element_addresss = Builder.CreateInBoundsGEP(load_element_addresss, ArrayRef<Value*>(indices, 2));

            indices[0] = ConstantInt::get(TheContext, llvm::APInt(32, 0, false)); 

            indices[1] = rvalue[1].value;

            load_element_addresss = Builder.CreateInBoundsGEP(load_element_addresss, ArrayRef<Value*>(indices, 2));

            sNodeType* var_type3 = clone_node_type(var_type);
            var_type3->mPointerNum -= num_dimention;
            var_type3->mPointerNum+=2;
            var_type3->mArrayDimentionNum = 0;

            Type* llvm_var_type2;
            if(!create_llvm_type_from_node_type(&llvm_var_type2, var_type3, var_type3, info))
            {
                compile_err_msg(info, "Getting llvm type failed(10)");
                show_node_type(var_type3);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            int alignment = get_llvm_alignment_from_node_type(var_type);

            if(var_type3->mPointerNum == 0) {
                element_value = Builder.CreateAlignedLoad(load_element_addresss, alignment, "element");
            }
            else {
                load_element_addresss = Builder.CreateCast(Instruction::BitCast, load_element_addresss, llvm_var_type2);
                element_value = load_element_addresss;
            }
        }
        else if(left_type->mArrayDimentionNum == 3) {
            int i;
            Value* lvalue2 = lvalue.address;

            load_element_addresss = lvalue2;

            Value* indices[2];

            indices[0] = ConstantInt::get(TheContext, llvm::APInt(32, 0, false)); 

            indices[1] = rvalue[0].value;

            load_element_addresss = Builder.CreateInBoundsGEP(load_element_addresss, ArrayRef<Value*>(indices, 2));

            indices[0] = ConstantInt::get(TheContext, llvm::APInt(32, 0, false)); 

            indices[1] = rvalue[1].value;

            load_element_addresss = Builder.CreateInBoundsGEP(load_element_addresss, ArrayRef<Value*>(indices, 2));

            indices[0] = ConstantInt::get(TheContext, llvm::APInt(32, 0, false)); 

            indices[1] = rvalue[2].value;

            load_element_addresss = Builder.CreateInBoundsGEP(load_element_addresss, ArrayRef<Value*>(indices, 2));

            sNodeType* var_type3 = clone_node_type(var_type);
            var_type3->mPointerNum -= num_dimention;
            var_type3->mPointerNum+=2;
            var_type3->mArrayDimentionNum = 0;

            Type* llvm_var_type2;
            if(!create_llvm_type_from_node_type(&llvm_var_type2, var_type3, var_type3, info))
            {
                compile_err_msg(info, "Getting llvm type failed(10)");
                show_node_type(var_type3);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            int alignment = get_llvm_alignment_from_node_type(var_type);

            element_value = Builder.CreateAlignedLoad(load_element_addresss, alignment, "element");
        }
        else if(left_type->mArrayDimentionNum > 3) {
            int i;
            Value* lvalue2 = lvalue.address;

            load_element_addresss = lvalue2;

            Value* indices[left_type->mArrayDimentionNum+1];

            int j;
            for(j=0; j<left_type->mArrayDimentionNum-num_dimention; j++) {
                indices[j] = ConstantInt::get(TheContext, llvm::APInt(32, 0, false)); 
            }
            int k=0;
            for(; j<left_type->mArrayDimentionNum; j++, k++) {
                indices[j] = rvalue[k].value;
            }
            load_element_addresss = Builder.CreateInBoundsGEP(load_element_addresss, ArrayRef<Value*>(indices, left_type->mArrayDimentionNum));

            for(j=0; j<left_type->mArrayDimentionNum; j++) {
                indices[j] = ConstantInt::get(TheContext, llvm::APInt(32, 0, false)); 
            }
            load_element_addresss = Builder.CreateInBoundsGEP(load_element_addresss, ArrayRef<Value*>(indices, left_type->mArrayDimentionNum));

            sNodeType* var_type3 = clone_node_type(var_type);
            var_type3->mPointerNum -= num_dimention;
            var_type3->mPointerNum+=2;
            var_type3->mArrayDimentionNum = 0;

            Type* llvm_var_type2;
            if(!create_llvm_type_from_node_type(&llvm_var_type2, var_type3, var_type3, info))
            {
                compile_err_msg(info, "Getting llvm type failed(10)");
                show_node_type(var_type3);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            int alignment = get_llvm_alignment_from_node_type(var_type);

            if(var_type3->mPointerNum == 0) {
                element_value = Builder.CreateAlignedLoad(load_element_addresss, alignment, "element");
            }
            else {
                load_element_addresss = Builder.CreateCast(Instruction::BitCast, load_element_addresss, llvm_var_type2);
                element_value = load_element_addresss;
            }
        }
        else {
            Value* lvalue2 = lvalue.value;

            load_element_addresss = lvalue2;

            for(i=0; i<num_dimention; i++) {
                load_element_addresss = Builder.CreateGEP(load_element_addresss, rvalue[i].value, "element_addressB");
            }

            int alignment = get_llvm_alignment_from_node_type(var_type);

            element_value = Builder.CreateAlignedLoad(load_element_addresss, alignment, "element");
        }

        LVALUE llvm_value;
        llvm_value.value = element_value;
        llvm_value.type = clone_node_type(var_type);
        llvm_value.address = load_element_addresss;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(1+num_dimention, info);
        push_value_to_stack_ptr(&llvm_value, info);
    }

    info->type = clone_node_type(var_type);

    return TRUE;
}

static BOOL pre_compile_load_element(unsigned int node, sCompileInfo* info)
{
    int num_dimention = gNodes[node].uValue.sLoadElement.mArrayDimentionNum;
    int i;
    unsigned int index_node[ARRAY_DIMENTION_MAX];
    for(i=0; i<num_dimention; i++) {
        index_node[i] = gNodes[node].uValue.sLoadElement.mIndex[i];
    }
    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!pre_compile(lnode, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    /// compile middle node ///
    LVALUE rvalue[ARRAY_DIMENTION_MAX];
    for(i=0; i<num_dimention; i++) {
        unsigned int mnode = index_node[i];

        if(!pre_compile(mnode, info)) {
            return FALSE;
        }
    }

    /// generate code ///
    sNodeType* var_type = clone_node_type(left_type);

    if(var_type->mArrayDimentionNum > 0) {
        var_type->mArrayDimentionNum-=num_dimention;
    }
    else {
        var_type->mPointerNum--;
    }

    //if(var_type->mPointerNum == 0) {
        var_type->mHeap = FALSE;
    //}

    info->type = var_type;

    return TRUE;
}

BOOL compile_store_element(unsigned int node, sCompileInfo* info)
{
    int num_dimention = gNodes[node].uValue.sStoreElement.mArrayDimentionNum;
    int i;
    unsigned int index_node[ARRAY_DIMENTION_MAX];
    for(i=0; i<num_dimention; i++) {
        index_node[i] = gNodes[node].uValue.sStoreElement.mIndex[i];
    }

    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);

    if(left_type->mArrayDimentionNum == 0 && left_type->mPointerNum == 0) 
    {
        compile_err_msg(info, "neo-c can't get an element from this type.");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    /// compile middle node ///
    LVALUE mvalue[ARRAY_DIMENTION_MAX];

    for(i=0; i<num_dimention; i++) {
        unsigned int mnode = index_node[i];

        if(!compile(mnode, info)) {
            return FALSE;
        }

        sNodeType* middle_type = info->type;

        LVALUE llvm_value = *get_value_from_stack(-1);

        sNodeType* int_type = create_node_type_with_class_name("int");

        if(!cast_right_type_to_left_type(int_type, &middle_type, &llvm_value, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        if(!type_identify_with_class_name(middle_type, "int")) {
            compile_err_msg(info, "Type of index should be number");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        mvalue[i] = *get_value_from_stack(-1);
    }

    /// compile right node ///
    unsigned int rnode = gNodes[node].mRight;

    if(!compile(rnode, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    if(info->no_output) {
        info->type = clone_node_type(right_type);
        return TRUE;
    }

    LVALUE rvalue = *get_value_from_stack(-1);

    sNodeType* var_type = clone_node_type(left_type);

    if(var_type->mArrayDimentionNum > 0) {
        var_type->mArrayDimentionNum--;
        //var_type->mPointerNum++;
    }
    else {
        var_type->mPointerNum--;
    }
    var_type->mHeap = right_type->mHeap;

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
        compile_err_msg(info, "The different type between left type and right type, store element");
        show_node_type(var_type);
        show_node_type(right_type);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    /// generate code ///
    if(info->no_output) {
    }
    else {
        Value* lvalue2;
        if(left_type->mArrayDimentionNum == 1) {
            sNodeType* var_type2 = clone_node_type(var_type);
            var_type2->mPointerNum++;

            Type* llvm_var_type;
            if(!create_llvm_type_from_node_type(&llvm_var_type, var_type2, var_type2, info))
            {
                compile_err_msg(info, "Getting llvm type failed(11)");
                show_node_type(var_type2);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            Value* lvalue2 = Builder.CreateCast(Instruction::BitCast, lvalue.address, llvm_var_type);
            Value* load_element_addresss = Builder.CreateGEP(lvalue2, mvalue[0].value, "element_addressC");

            int alignment = get_llvm_alignment_from_node_type(var_type);

            Builder.CreateAlignedStore(rvalue.value, load_element_addresss, alignment);
        }
        else if(left_type->mArrayDimentionNum == 2) {
            Value* load_element_addresss = lvalue.address;
            Value* indices[2];

            indices[0] = ConstantInt::get(Type::getInt32Ty(TheContext), 0);
            indices[1] = mvalue[0].value;

            load_element_addresss = Builder.CreateInBoundsGEP(load_element_addresss, ArrayRef<Value*>(indices, 2));

            indices[0] = ConstantInt::get(Type::getInt32Ty(TheContext), 0);
            indices[1] = mvalue[1].value;

            load_element_addresss = Builder.CreateInBoundsGEP(load_element_addresss, ArrayRef<Value*>(indices, 2));

            sNodeType* var_type3 = clone_node_type(var_type);
            var_type3->mPointerNum = 1;
            var_type3->mArrayDimentionNum = 0;

            Type* llvm_var_type2;
            if(!create_llvm_type_from_node_type(&llvm_var_type2, var_type3, var_type3, info))
            {
                compile_err_msg(info, "Getting llvm type failed(10)");
                show_node_type(var_type3);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            //load_element_addresss = Builder.CreateCast(Instruction::BitCast, load_element_addresss, llvm_var_type2);

            int alignment = get_llvm_alignment_from_node_type(var_type);

            Builder.CreateAlignedStore(rvalue.value, load_element_addresss, alignment);
        }
        else if(left_type->mArrayDimentionNum == 3) {
            Value* load_element_addresss = lvalue.address;
            Value* indices[2];

            indices[0] = ConstantInt::get(Type::getInt32Ty(TheContext), 0);
            indices[1] = mvalue[0].value;

            load_element_addresss = Builder.CreateInBoundsGEP(load_element_addresss, ArrayRef<Value*>(indices, 2));

            indices[0] = ConstantInt::get(Type::getInt32Ty(TheContext), 0);
            indices[1] = mvalue[1].value;

            load_element_addresss = Builder.CreateInBoundsGEP(load_element_addresss, ArrayRef<Value*>(indices, 2));

            indices[0] = ConstantInt::get(Type::getInt32Ty(TheContext), 0);
            indices[1] = mvalue[2].value;

            load_element_addresss = Builder.CreateInBoundsGEP(load_element_addresss, ArrayRef<Value*>(indices, 2));

            sNodeType* var_type3 = clone_node_type(var_type);
            var_type3->mPointerNum = 1;
            var_type3->mArrayDimentionNum = 0;

            Type* llvm_var_type2;
            if(!create_llvm_type_from_node_type(&llvm_var_type2, var_type3, var_type3, info))
            {
                compile_err_msg(info, "Getting llvm type failed(10)");
                show_node_type(var_type3);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            //load_element_addresss = Builder.CreateCast(Instruction::BitCast, load_element_addresss, llvm_var_type2);

            int alignment = get_llvm_alignment_from_node_type(var_type);

            Builder.CreateAlignedStore(rvalue.value, load_element_addresss, alignment);
        }
        else if(left_type->mArrayDimentionNum > 1) {
            Value* load_element_addresss = lvalue.address;
            for(i=0; i<num_dimention; i++) {
                Value* indices[num_dimention-i];

                int j;
                for(j=i; j<num_dimention; j++) {
                    indices[j-i] = mvalue[j].value;
                }

                load_element_addresss = Builder.CreateInBoundsGEP(load_element_addresss, ArrayRef<Value*>(indices, num_dimention-i));
            }

            sNodeType* var_type3 = clone_node_type(var_type);
            var_type3->mPointerNum = 1;
            var_type3->mArrayDimentionNum = 0;

            Type* llvm_var_type2;
            if(!create_llvm_type_from_node_type(&llvm_var_type2, var_type3, var_type3, info))
            {
                compile_err_msg(info, "Getting llvm type failed(10)");
                show_node_type(var_type3);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            load_element_addresss = Builder.CreateCast(Instruction::BitCast, load_element_addresss, llvm_var_type2);

            int alignment = get_llvm_alignment_from_node_type(var_type);

            Builder.CreateAlignedStore(rvalue.value, load_element_addresss, alignment);
        }
        else {
            Value* lvalue2 = lvalue.value;

            Value* element_address = lvalue2;
            for(i=0; i<num_dimention; i++) {
                element_address = Builder.CreateGEP(element_address, mvalue[i].value, "element_addressD");
            }

            int alignment = get_llvm_alignment_from_node_type(var_type);

            //BOOL alloc = FALSE;
            //std_move(element_address, var_type, &rvalue, alloc, info);

            Builder.CreateAlignedStore(rvalue.value, element_address, alignment);
        }

        dec_stack_ptr(2+num_dimention, info);
        push_value_to_stack_ptr(&rvalue, info);
    }

    info->type = clone_node_type(right_type);

    return TRUE;
}

BOOL pre_compile_store_element(unsigned int node, sCompileInfo* info)
{
    int num_dimention = gNodes[node].uValue.sStoreElement.mArrayDimentionNum;
    int i;
    unsigned int index_node[ARRAY_DIMENTION_MAX];
    for(i=0; i<num_dimention; i++) {
        index_node[i] = gNodes[node].uValue.sStoreElement.mIndex[i];
    }

    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!pre_compile(lnode, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    /// compile middle node ///
    LVALUE mvalue[ARRAY_DIMENTION_MAX];

    for(i=0; i<num_dimention; i++) {
        unsigned int mnode = index_node[i];

        if(!pre_compile(mnode, info)) {
            return FALSE;
        }

        sNodeType* middle_type = info->type;
    }

    /// compile right node ///
    unsigned int rnode = gNodes[node].mRight;

    if(!pre_compile(rnode, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    info->type = clone_node_type(right_type);
    return TRUE;
}

BOOL compile_array_initializer(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

    int num_array_value = gNodes[node].uValue.sArrayInitializer.mNumArrayValue;
    unsigned int array_values[INIT_ARRAY_MAX];
    memcpy(array_values, gNodes[node].uValue.sArrayInitializer.mArrayValues, sizeof(unsigned int)*INIT_ARRAY_MAX);

    char var_name[VAR_NAME_MAX];

    xstrncpy(var_name, gNodes[node].uValue.sArrayInitializer.mVarName, VAR_NAME_MAX);

    BOOL global = gNodes[node].uValue.sArrayInitializer.mGlobal;

    /// compile node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    sVar* var;
    if(global) {
        sVar* var = get_variable_from_table(info->gv_table, var_name);

        if(var == NULL) {
            compile_err_msg(info, "var is null (%s)\n", var_name);
            info->err_num++;
            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        sNodeType* var_type = var->mType;

        if(var_type->mArrayDimentionNum == 1) {
            std::vector<Constant *> init_data(num_array_value);

            int i;
            for(i=0; i<num_array_value; i++) {
                /// compile node ///
                unsigned int element_node = array_values[i];

                if(!compile(element_node, info)) {
                    return FALSE;
                }

                sNodeType* right_type = clone_node_type(info->type);

                LVALUE rvalue = *get_value_from_stack(-1);

                dec_stack_ptr(1, info);

                if(dyn_cast<Constant>(rvalue.value)) 
                {
                    init_data[i] = dyn_cast<Constant>(rvalue.value);
                }
                else {
                    compile_err_msg(info, "Require Constant Value");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }

            sNodeType* var_element_type = clone_node_type(var_type);
            var_element_type->mPointerNum--;

            Type* var_llvm_element_type;
            if(!create_llvm_type_from_node_type(&var_llvm_element_type, var_element_type, var_element_type, info))
            {
                compile_err_msg(info, "Getting llvm type failed(13)");
                show_node_type(var_element_type);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            int alignment = get_llvm_alignment_from_node_type(var_element_type);

            GlobalVariable* address = (GlobalVariable*)var->mLLVMValue;

            Constant* constant_array = ConstantArray::get(ArrayType::get(var_llvm_element_type, num_array_value), init_data);
            address->setAlignment(alignment);

            ConstantAggregateZero* initializer = ConstantAggregateZero::get(var_llvm_element_type);

            address->setInitializer(constant_array);
        }
        else if(var_type->mArrayDimentionNum == 2) {
            int array_num = var_type->mArrayNum[1];

            sNodeType* var_element_type = clone_node_type(var_type);
            var_element_type->mArrayDimentionNum--;
            var_element_type->mPointerNum--;

            Type* var_llvm_element_type;
            if(!create_llvm_type_from_node_type(&var_llvm_element_type, var_element_type, var_element_type, info))
            {
                compile_err_msg(info, "Getting llvm type failed(13)");
                show_node_type(var_element_type);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            std::vector<Constant*> init_data;
            std::vector<Constant*> init_datas;
            int i;
            for(i=0; i<num_array_value; i++) {
                /// compile node ///
                unsigned int element_node = array_values[i];

                if(!compile(element_node, info)) {
                    return FALSE;
                }

                sNodeType* right_type = clone_node_type(info->type);

                LVALUE rvalue = *get_value_from_stack(-1);

                dec_stack_ptr(1, info);

                if(dyn_cast<Constant>(rvalue.value)) 
                {
                    if(i % array_num == 0 && i != 0) {
                        Constant* constant_data = ConstantArray::get(ArrayType::get(var_llvm_element_type, array_num), init_data);
                        init_datas.push_back(constant_data);
                        init_data.clear();
                    }
                    init_data.push_back(dyn_cast<Constant>(rvalue.value));
                }
                else {
                    compile_err_msg(info, "Require Constant Value");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }

            Constant* constant_data = ConstantArray::get(ArrayType::get(var_llvm_element_type, array_num), init_data);
            init_datas.push_back(constant_data);
            init_data.clear();
            int alignment = get_llvm_alignment_from_node_type(var_element_type);

            GlobalVariable* address = (GlobalVariable*)var->mLLVMValue;


            Constant* initializer = ConstantArray::get(ArrayType::get(var_llvm_element_type, array_num), init_datas);
            address->setAlignment(alignment);

            address->setInitializer(initializer);
        }
        else if(var_type->mArrayDimentionNum == 3) {
            int array_num = var_type->mArrayNum[1];
            int array_num2 = var_type->mArrayNum[2];

            sNodeType* var_element_type0 = clone_node_type(var_type);
            var_element_type0->mArrayDimentionNum-=3;
            var_element_type0->mPointerNum--;

            Type* var_llvm_element_type0;
            if(!create_llvm_type_from_node_type(&var_llvm_element_type0, var_element_type0, var_element_type0, info))
            {
                compile_err_msg(info, "Getting llvm type failed(13)");
                show_node_type(var_element_type0);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            sNodeType* var_element_type = clone_node_type(var_type);
            var_element_type->mArrayDimentionNum-=2;
            var_element_type->mPointerNum--;

            Type* var_llvm_element_type;
            if(!create_llvm_type_from_node_type(&var_llvm_element_type, var_element_type, var_element_type, info))
            {
                compile_err_msg(info, "Getting llvm type failed(13)");
                show_node_type(var_element_type);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            sNodeType* var_element_type2 = clone_node_type(var_type);
            var_element_type2->mArrayDimentionNum--;
            var_element_type2->mPointerNum--;

            Type* var_llvm_element_type2;
            if(!create_llvm_type_from_node_type(&var_llvm_element_type2, var_element_type2, var_element_type2, info))
            {
                compile_err_msg(info, "Getting llvm type failed(13)");
                show_node_type(var_element_type);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }


            std::vector<Constant*> init_data;
            std::vector<Constant*> init_datas;
            std::vector<Constant*> init_datas2;
            int i;
            for(i=0; i<num_array_value; i++) {
                /// compile node ///
                unsigned int element_node = array_values[i];

                if(!compile(element_node, info)) {
                    return FALSE;
                }

                sNodeType* right_type = clone_node_type(info->type);

                LVALUE rvalue = *get_value_from_stack(-1);

                dec_stack_ptr(1, info);

                if(dyn_cast<Constant>(rvalue.value)) 
                {
                    if(i % array_num == 0 && i != 0) {
                        Constant* constant_data = ConstantArray::get(ArrayType::get(var_llvm_element_type0, array_num), init_data);
                        init_datas.push_back(constant_data);
                        init_data.clear();
                    }
                    if(i % (array_num * array_num2) == 0 && i != 0) {
                        Constant* constant_data = ConstantArray::get(ArrayType::get(var_llvm_element_type, array_num2), init_datas);
                        init_datas2.push_back(constant_data);
                        init_data.clear();
                        init_datas.clear();
                    }
                    init_data.push_back(dyn_cast<Constant>(rvalue.value));
                }
                else {
                    compile_err_msg(info, "Require Constant Value");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }

            Constant* constant_data = ConstantArray::get(ArrayType::get(var_llvm_element_type0, array_num), init_data);
            init_datas.push_back(constant_data);
            init_data.clear();

            Constant* constant_data2 = ConstantArray::get(ArrayType::get(var_llvm_element_type, array_num2), init_datas);
            init_datas2.push_back(constant_data2);
            init_data.clear();
            init_datas.clear();

            int alignment = get_llvm_alignment_from_node_type(var_element_type);

            GlobalVariable* address = (GlobalVariable*)var->mLLVMValue;

            Type* var_llvm_element_type3;
            if(!create_llvm_type_from_node_type(&var_llvm_element_type3, var_type, var_type, info))
            {
                compile_err_msg(info, "Getting llvm type failed(13)");
                show_node_type(var_element_type);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }


            Constant* initializer = ConstantArray::get(ArrayType::get(var_llvm_element_type2, array_num2), init_datas2);
            address->setAlignment(alignment);

            address->setInitializer(initializer);
        }
        else {
            compile_err_msg(info, "overflow dimetion of array initializer");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }
    else {
        sVar* var = get_variable_from_table(info->lv_table, var_name);

        sNodeType* var_type = var->mType;

        if(var_type->mArrayDimentionNum == 1) {
            sNodeType* var_type = var->mType;

            if(var_type == NULL || var_type->mClass == NULL) 
            {
                compile_err_msg(info, "null type %s", var_name);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy
                return TRUE;
            }

            BOOL parent = FALSE;
            int index = get_variable_index(info->lv_table, var_name, &parent);

            Value* var_address;
            if(parent) {
                var_address = load_address_to_lvtable(index, var_type, info);
            }
            else {
                var_address = (Value*)var->mLLVMValue;
            }

            if(var_address == nullptr) {
                compile_err_msg(info, "Invalid variable. %s. array with initialization", var_name);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            int alignment = get_llvm_alignment_from_node_type(var_type);

            var_address = Builder.CreateAlignedLoad(var_address, alignment);

            sNodeType* var_element_type = clone_node_type(var_type);
            var_element_type->mPointerNum++;
            var_element_type->mArrayDimentionNum = 0;

            Value* lvalue = (Value*)var->mLLVMValue;

            Type* llvm_var_type;
            if(!create_llvm_type_from_node_type(&llvm_var_type, var_element_type, var_element_type, info))
            {
                compile_err_msg(info, "Getting llvm type failed(11)");
                show_node_type(var_element_type);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            Value* lvalue2 = Builder.CreateCast(Instruction::BitCast, lvalue, llvm_var_type);

            int alignment2 = get_llvm_alignment_from_node_type(var_element_type);

            int i;
            for(i=0; i<num_array_value; i++) {
                /// compile node ///
                unsigned int element_node = array_values[i];

                if(!compile(element_node, info)) {
                    return FALSE;
                }

                sNodeType* right_type = info->type;

                LVALUE rvalue = *get_value_from_stack(-1);

                dec_stack_ptr(1, info);

                sNodeType* var_element_type2 = clone_node_type(var_type);
                var_element_type2->mArrayDimentionNum = 0;

                if(auto_cast_posibility(var_element_type2, right_type)) {
                    if(!cast_right_type_to_left_type(var_element_type2, &right_type, &rvalue, info))
                    {
                        compile_err_msg(info, "Cast failed");
                        info->err_num++;

                        info->type = create_node_type_with_class_name("int"); // dummy

                        return TRUE;
                    }
                }

                Value* mvalue = ConstantInt::get(Type::getInt64Ty(TheContext), i);

                Value* load_element_addresss = Builder.CreateGEP(lvalue2, mvalue, "element_address");

                Builder.CreateAlignedStore(rvalue.value, load_element_addresss, alignment2);
            }
        }
        else if(var_type->mArrayDimentionNum == 2) {
            sNodeType* var_type = var->mType;

            if(var_type == NULL || var_type->mClass == NULL) 
            {
                compile_err_msg(info, "null type %s", var_name);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy
                return TRUE;
            }

            BOOL parent = FALSE;
            int index = get_variable_index(info->lv_table, var_name, &parent);

            Value* var_address;
            if(parent) {
                var_address = load_address_to_lvtable(index, var_type, info);
            }
            else {
                var_address = (Value*)var->mLLVMValue;
            }

            if(var_address == nullptr) {
                compile_err_msg(info, "Invalid variable. %s. array with initialization", var_name);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
            int i;
            for(i=0; i<num_array_value; i++) {
                /// compile node ///
                unsigned int element_node = array_values[i];

                if(!compile(element_node, info)) {
                    return FALSE;
                }

                sNodeType* right_type = info->type;

                LVALUE rvalue = *get_value_from_stack(-1);

                dec_stack_ptr(1, info);

                sNodeType* var_element_type2 = clone_node_type(var_type);
                var_element_type2->mArrayDimentionNum = 0;

                if(auto_cast_posibility(var_element_type2, right_type)) {
                    if(!cast_right_type_to_left_type(var_element_type2, &right_type, &rvalue, info))
                    {
                        compile_err_msg(info, "Cast failed");
                        info->err_num++;

                        info->type = create_node_type_with_class_name("int"); // dummy

                        return TRUE;
                    }
                }

                Value* mvalue[2];

                int n = i / var_type->mArrayNum[0];
                mvalue[0] = ConstantInt::get(TheContext, llvm::APInt(32, n, false)); 
                n = i % var_type->mArrayNum[0];

                mvalue[1] = ConstantInt::get(TheContext, llvm::APInt(32, n, false)); 

                Value* load_element_addresss = var_address;
                Value* indices[2];

                indices[0] = ConstantInt::get(Type::getInt32Ty(TheContext), 0);
                indices[1] = mvalue[0];

                load_element_addresss = Builder.CreateInBoundsGEP(load_element_addresss, ArrayRef<Value*>(indices, 2));

                indices[0] = ConstantInt::get(Type::getInt32Ty(TheContext), 0);
                indices[1] = mvalue[1];

                load_element_addresss = Builder.CreateInBoundsGEP(load_element_addresss, ArrayRef<Value*>(indices, 2));

                sNodeType* var_type3 = clone_node_type(var_type);
                var_type3->mPointerNum = 1;
                var_type3->mArrayDimentionNum = 0;

                Type* llvm_var_type2;
                if(!create_llvm_type_from_node_type(&llvm_var_type2, var_type3, var_type3, info))
                {
                    compile_err_msg(info, "Getting llvm type failed(10)");
                    show_node_type(var_type3);
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }

                //load_element_addresss = Builder.CreateCast(Instruction::BitCast, load_element_addresss, llvm_var_type2);

                int alignment = get_llvm_alignment_from_node_type(var_type);

                Builder.CreateAlignedStore(rvalue.value, load_element_addresss, alignment);
            }
        }
        else if(var_type->mArrayDimentionNum == 3) {
            sNodeType* var_type = var->mType;

            if(var_type == NULL || var_type->mClass == NULL) 
            {
                compile_err_msg(info, "null type %s", var_name);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy
                return TRUE;
            }

            BOOL parent = FALSE;
            int index = get_variable_index(info->lv_table, var_name, &parent);

            Value* var_address;
            if(parent) {
                var_address = load_address_to_lvtable(index, var_type, info);
            }
            else {
                var_address = (Value*)var->mLLVMValue;
            }

            if(var_address == nullptr) {
                compile_err_msg(info, "Invalid variable. %s. array with initialization", var_name);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
            int i;
            for(i=0; i<num_array_value; i++) {
                /// compile node ///
                unsigned int element_node = array_values[i];

                if(!compile(element_node, info)) {
                    return FALSE;
                }

                sNodeType* right_type = info->type;

                LVALUE rvalue = *get_value_from_stack(-1);

                dec_stack_ptr(1, info);

                sNodeType* var_element_type2 = clone_node_type(var_type);
                var_element_type2->mArrayDimentionNum = 0;

                if(auto_cast_posibility(var_element_type2, right_type)) {
                    if(!cast_right_type_to_left_type(var_element_type2, &right_type, &rvalue, info))
                    {
                        compile_err_msg(info, "Cast failed");
                        info->err_num++;

                        info->type = create_node_type_with_class_name("int"); // dummy

                        return TRUE;
                    }
                }

                Value* mvalue[3];

                int n = i / (var_type->mArrayNum[0] * var_type->mArrayNum[1]);
                mvalue[0] = ConstantInt::get(TheContext, llvm::APInt(32, n, false)); 
                n = (i % (var_type->mArrayNum[0] * var_type->mArrayNum[1]) ) / var_type->mArrayNum[0];

                mvalue[1] = ConstantInt::get(TheContext, llvm::APInt(32, n, false)); 
                n = i % var_type->mArrayNum[0];

                mvalue[2] = ConstantInt::get(TheContext, llvm::APInt(32, n, false)); 

                Value* load_element_addresss = var_address;
                Value* indices[2];

                indices[0] = ConstantInt::get(Type::getInt32Ty(TheContext), 0);
                indices[1] = mvalue[0];

                load_element_addresss = Builder.CreateInBoundsGEP(load_element_addresss, ArrayRef<Value*>(indices, 2));

                indices[0] = ConstantInt::get(Type::getInt32Ty(TheContext), 0);
                indices[1] = mvalue[1];

                load_element_addresss = Builder.CreateInBoundsGEP(load_element_addresss, ArrayRef<Value*>(indices, 2));

                indices[0] = ConstantInt::get(Type::getInt32Ty(TheContext), 0);
                indices[1] = mvalue[2];

                load_element_addresss = Builder.CreateInBoundsGEP(load_element_addresss, ArrayRef<Value*>(indices, 2));

                sNodeType* var_type3 = clone_node_type(var_type);
                var_type3->mPointerNum = 1;
                var_type3->mArrayDimentionNum = 0;

                Type* llvm_var_type2;
                if(!create_llvm_type_from_node_type(&llvm_var_type2, var_type3, var_type3, info))
                {
                    compile_err_msg(info, "Getting llvm type failed(10)");
                    show_node_type(var_type3);
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }

                //load_element_addresss = Builder.CreateCast(Instruction::BitCast, load_element_addresss, llvm_var_type2);

                int alignment = get_llvm_alignment_from_node_type(var_type);

                Builder.CreateAlignedStore(rvalue.value, load_element_addresss, alignment);
            }
        }
        else {
            compile_err_msg(info, "overflow dimetion of array initializer");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

BOOL pre_compile_array_initializer(unsigned int node, sCompileInfo* info)
{
    int num_array_value = gNodes[node].uValue.sArrayInitializer.mNumArrayValue;
    unsigned int array_values[INIT_ARRAY_MAX];
    memcpy(array_values, gNodes[node].uValue.sArrayInitializer.mArrayValues, sizeof(unsigned int)*INIT_ARRAY_MAX);

    char var_name[VAR_NAME_MAX];

    xstrncpy(var_name, gNodes[node].uValue.sArrayInitializer.mVarName, VAR_NAME_MAX);

    BOOL global = gNodes[node].uValue.sArrayInitializer.mGlobal;

    /// compile node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!pre_compile(lnode, info)) {
        return FALSE;
    }

    sVar* var;
    if(global) {
    }
    else {
        int i;
        for(i=0; i<num_array_value; i++) {
            /// compile node ///
            unsigned int element_node = array_values[i];

            if(!pre_compile(element_node, info)) {
                return FALSE;
            }
        }
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

static BOOL compile_for_statment(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

    void* switch_expression = info->switch_expression;
    info->switch_expression = NULL;

    unsigned int for_block = gNodes[node].uValue.sFor.mForNodeBlock;

    sVarTable* lv_table = info->lv_table;
    info->lv_table = init_var_table();
    info->lv_table->mParent = lv_table;

    /// compile expression ///
    unsigned int expression_node = gNodes[node].uValue.sFor.mExpressionNode;

    if(!compile(expression_node, info)) {
        return FALSE;
    }

    /// compile expression ///
    sFunction* fun = (sFunction*)info->function;
    Function* llvm_function = fun->mLLVMFunction;
    BasicBlock* loop_top_block = BasicBlock::Create(TheContext, "loop_top_block", llvm_function);

    //free_right_value_objects(info);
    Builder.CreateBr(loop_top_block);

    BasicBlock* current_block_before;
    llvm_change_block(loop_top_block, &current_block_before, info, FALSE);

    unsigned int expression_node2 = gNodes[node].uValue.sFor.mExpressionNode2;

    if(!compile(expression_node2, info)) {
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

    BasicBlock* cond_then_block = BasicBlock::Create(TheContext, "cond_then_block", llvm_function);

    BasicBlock* cond_end_block = BasicBlock::Create(TheContext, "cond_end_block", llvm_function);

    info->loop_end_block[info->num_loop] = cond_end_block;
    info->num_loop++;

    if(info->num_loop >= LOOP_NEST_MAX) {
        compile_err_msg(info, "Over flow loop number. Loop number is %d. for", info->num_loop);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    info->loop_begin_block[info->num_loop2] = cond_then_block;
    info->num_loop2++;

    if(info->num_loop2 >= LOOP_NEST_MAX) {
        compile_err_msg(info, "Over flow loop number. Loop number is %d. for", info->num_loop2);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    //free_right_value_objects(info);
    Builder.CreateCondBr(conditional_value.value, cond_then_block, cond_end_block);

    BasicBlock* current_block_before2;
    llvm_change_block(cond_then_block, &current_block_before2, info, FALSE);

//    BasicBlock* current_block = (BasicBlock*)info->current_block;
//    info->current_block = for_block;

    /// block of for expression ///
    BOOL last_expression_is_return = FALSE;
    BOOL loop_top = TRUE;
    if(!compile_block(for_block, info, &last_expression_is_return, loop_top))
    {
        info->num_loop--;
        return FALSE;
    }

//    info->current_block = current_block;

    /// expression 3 ///
    unsigned int expression_node3 = gNodes[node].uValue.sFor.mExpressionNode3;

    last_expression_is_return = gNodes[expression_node3].mNodeType == kNodeTypeReturn;
    if(!compile(expression_node3, info)) {
        return FALSE;
    }

    if(!last_expression_is_return) {
        Builder.CreateBr(loop_top_block);
    }

    BasicBlock* current_block_before3;
    llvm_change_block(cond_end_block, &current_block_before3, info, FALSE);
    info->num_loop--;

    info->lv_table = lv_table;

    info->type = create_node_type_with_class_name("void");

    info->switch_expression = switch_expression;

    return TRUE;
}

static BOOL pre_compile_for_statment(unsigned int node, sCompileInfo* info)
{
    unsigned int for_block = gNodes[node].uValue.sFor.mForNodeBlock;

    /// compile expression ///
    unsigned int expression_node = gNodes[node].uValue.sFor.mExpressionNode;

    if(!pre_compile(expression_node, info)) {
        return FALSE;
    }

    unsigned int expression_node2 = gNodes[node].uValue.sFor.mExpressionNode2;

    if(!pre_compile(expression_node2, info)) {
        return FALSE;
    }

    /// block of for expression ///
    BOOL last_expression_is_return = FALSE;
    BOOL loop_top = TRUE;
    if(!pre_compile_block(for_block, info)) {
        return FALSE;
    }

    /// expression 3 ///
    unsigned int expression_node3 = gNodes[node].uValue.sFor.mExpressionNode3;

    if(!pre_compile(expression_node3, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

static BOOL compile_while_statment(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

    void* switch_expression_before = info->switch_expression;
    info->switch_expression = NULL;

    unsigned int while_node_block = gNodes[node].uValue.sWhile.mWhileNodeBlock;
    sFunction* fun = (sFunction*)info->function;
    Function* llvm_function = fun->mLLVMFunction;

    BasicBlock* loop_top_block = BasicBlock::Create(TheContext, "loop_top_block", llvm_function);

    Builder.CreateBr(loop_top_block);

    BasicBlock* current_block_before;
    llvm_change_block(loop_top_block, &current_block_before, info, FALSE);

    /// compile expression ///
    unsigned int expression_node = gNodes[node].uValue.sWhile.mExpressionNode;

    if(!compile(expression_node, info)) {
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

    BasicBlock* cond_then_block = BasicBlock::Create(TheContext, "cond_then_block", llvm_function);

    BasicBlock* cond_end_block = BasicBlock::Create(TheContext, "cond_end_block", llvm_function);

    info->loop_end_block[info->num_loop] = cond_end_block;
    info->num_loop++;

    if(info->num_loop >= LOOP_NEST_MAX) {
        compile_err_msg(info, "Over flow loop number. Loop number is %d. while(1)", info->num_loop);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    info->loop_begin_block[info->num_loop2] = cond_then_block;
    info->num_loop2++;

    if(info->num_loop2 >= LOOP_NEST_MAX) {
        compile_err_msg(info, "Over flow loop number. Loop number is %d. while(2)", info->num_loop2);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    Builder.CreateCondBr(conditional_value.value, cond_then_block, cond_end_block);

    BasicBlock* current_block_before2;
    llvm_change_block(cond_then_block, &current_block_before2, info, FALSE);

    //sNodeBlock* current_node_block = info->current_node_block;
    //info->current_node_block = while_node_block;
    
    BOOL loop_top = TRUE;
    BOOL last_expression_is_return = FALSE;
    if(!compile_block(while_node_block, info, &last_expression_is_return, loop_top))
    {
        info->num_loop--;
        return FALSE;
    }

    //info->current_node_block = current_node_block;

    if(!last_expression_is_return) {
        Builder.CreateBr(loop_top_block);
    }

    info->num_loop--;
    info->num_loop2--;

    //info->last_expression_is_return = last_expression_is_return_before;

    BasicBlock* current_block_before3;
    llvm_change_block(cond_end_block, &current_block_before3, info, FALSE);

    info->type = create_node_type_with_class_name("void");

    info->switch_expression = switch_expression_before;

    return TRUE;
}

static BOOL pre_compile_while_statment(unsigned int node, sCompileInfo* info)
{
    unsigned int while_node_block = gNodes[node].uValue.sWhile.mWhileNodeBlock;

    /// compile expression ///
    unsigned int expression_node = gNodes[node].uValue.sWhile.mExpressionNode;

    if(!pre_compile(expression_node, info)) {
        return FALSE;
    }

    if(!pre_compile_block(while_node_block, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

static BOOL compile_do_while_statment(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

    void* switch_expression_before = info->switch_expression;
    info->switch_expression = NULL;

    unsigned int while_node_block = gNodes[node].uValue.sWhile.mWhileNodeBlock;

    sFunction* fun = (sFunction*)info->function;
    Function* llvm_function = fun->mLLVMFunction;

    BasicBlock* loop_top_block = BasicBlock::Create(TheContext, "loop_top_block", llvm_function);

    Builder.CreateBr(loop_top_block);

    BasicBlock* current_block_before;
    llvm_change_block(loop_top_block, &current_block_before, info, FALSE);

    info->loop_begin_block[info->num_loop2] = loop_top_block;
    info->num_loop2++;

    if(info->num_loop2 >= LOOP_NEST_MAX) {
        compile_err_msg(info, "Over flow loop number. Loop number is %d. do while", info->num_loop2);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    BasicBlock* cond_end_block = BasicBlock::Create(TheContext, "cond_end_block", llvm_function);

    info->loop_end_block[info->num_loop] = cond_end_block;
    info->num_loop++;

    if(info->num_loop >= LOOP_NEST_MAX) {
        compile_err_msg(info, "Over flow loop number. Loop number is %d. do while", info->num_loop);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

//    sNodeBlock* current_node_block = info->current_node_block;
//    info->current_node_block = while_node_block;

    BOOL last_expression_is_return = FALSE;
    BOOL loop_top = TRUE;
    if(!compile_block(while_node_block, info, &last_expression_is_return, loop_top))
    {
        info->num_loop--;
        return FALSE;
    }

//    info->current_node_block = current_node_block;

    /// compile expression ///
    unsigned int expression_node = gNodes[node].uValue.sWhile.mExpressionNode;

    if(!compile(expression_node, info)) {
        return FALSE;
    }

    sNodeType* conditional_type = info->type;

    LVALUE conditional_value = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

//    free_right_value_objects(info);
    Builder.CreateCondBr(conditional_value.value, loop_top_block, cond_end_block);

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

    BasicBlock* current_block_before2;
    llvm_change_block(cond_end_block, &current_block_before2, info, FALSE);

    info->type = create_node_type_with_class_name("void");

    info->switch_expression = switch_expression_before;

    return TRUE;
}

static BOOL pre_compile_do_while_statment(unsigned int node, sCompileInfo* info)
{
    unsigned int while_node_block = gNodes[node].uValue.sWhile.mWhileNodeBlock;

    if(!pre_compile_block(while_node_block, info)) {
        return FALSE;
    }

    unsigned int expression_node = gNodes[node].uValue.sWhile.mExpressionNode;

    if(!pre_compile(expression_node, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

BOOL compile_switch_statment(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

    unsigned int* switch_expression = gNodes[node].uValue.sSwitch.mSwitchExpression;
    int num_switch_expression = gNodes[node].uValue.sSwitch.mNumSwitchExpression;
    unsigned int expression_node = gNodes[node].uValue.sSwitch.mExpression;
    sFunction* fun = (sFunction*)info->function;

    Function* llvm_function = fun->mLLVMFunction;

    BasicBlock* loop_end_block = BasicBlock::Create(TheContext, "end_block", llvm_function);

    info->loop_end_block[info->num_loop] = loop_end_block;
    info->num_loop++;

    if(info->num_loop >= LOOP_NEST_MAX) {
        compile_err_msg(info, "Over flow loop number. Loop number is %d. switch", info->num_loop);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(!compile(expression_node, info)) {
        return FALSE;
    }

    void* switch_expression_before = info->switch_expression;
    info->switch_expression = get_value_from_stack(-1)->value;
    sNodeType* switch_expression_type_before = info->switch_expression_type;
    info->switch_expression_type = clone_node_type(get_value_from_stack(-1)->type);
    dec_stack_ptr(1, info);

    info->case_else_block = nullptr;

    int i;
    unsigned int node2;
    for(i=0; i<num_switch_expression; i++) {
        int sline = info->sline;
        gNodes[node].mLine = info->sline;
        
        /// compile node ///
        node2 = switch_expression[i];

        info->sline = gNodes[node2].mLine;

        if(!compile(node2, info)) {
            info->num_loop--;
            return FALSE;
        }
    }

    BasicBlock* case_else_block;
    if(gNodes[node2].mNodeType == kNodeTypeReturn) {
        case_else_block = NULL;
    }
    else {
        case_else_block = (BasicBlock*)info->case_else_block;
    }

    if(case_else_block) {
        Builder.CreateBr(case_else_block);

        BasicBlock* current_block_before;
        llvm_change_block(case_else_block, &current_block_before, info, FALSE);
    }

    info->switch_expression = switch_expression_before;
    info->switch_expression_type = switch_expression_type_before;

    //free_right_value_objects(info);
    Builder.CreateBr(loop_end_block);

    BasicBlock* current_block_before;
    llvm_change_block(loop_end_block, &current_block_before, info, FALSE);

    info->type = create_node_type_with_class_name("void");

    info->case_else_block = nullptr;

    info->num_loop--;

    return TRUE;
}

BOOL pre_compile_switch_statment(unsigned int node, sCompileInfo* info)
{
    unsigned int* switch_expression = gNodes[node].uValue.sSwitch.mSwitchExpression;
    int num_switch_expression = gNodes[node].uValue.sSwitch.mNumSwitchExpression;
    unsigned int expression_node = gNodes[node].uValue.sSwitch.mExpression;
    sFunction* fun = (sFunction*)info->function;

    if(!pre_compile(expression_node, info)) {
        return FALSE;
    }

    int i;
    unsigned int node2;
    for(i=0; i<num_switch_expression; i++) {
        /// compile node ///
        node2 = switch_expression[i];

        if(!pre_compile(node2, info)) {
            return FALSE;
        }
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

BOOL compile_case_expression(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

    unsigned int expression_node = gNodes[node].uValue.sCase.mExpression;
    BOOL first_case = gNodes[node].uValue.sCase.mFirstCase;
    BOOL last_case = gNodes[node].uValue.sCase.mLastCase;
    BOOL case_after_return = gNodes[node].uValue.sCase.mCaseAfterReturn;
    unsigned int first_statment = gNodes[node].uValue.sCase.mFirstStatment;
    unsigned int last_statment = gNodes[node].uValue.sCase.mLastStatment;

    if(last_statment) {
        if(!compile(last_statment, info)) {
            return FALSE;
        }
    }

    sFunction* fun = (sFunction*)info->function;

    Function* llvm_function = fun->mLLVMFunction;

    BasicBlock* cond_then_block;
    if(first_case) {
        cond_then_block = BasicBlock::Create(TheContext, "cond_then_block", llvm_function);
        info->case_then_block = cond_then_block;
    }
    else {
        cond_then_block = (BasicBlock*)info->case_then_block;
    }
    BasicBlock* cond_else_block = BasicBlock::Create(TheContext, "cond_else_block", llvm_function);

    BasicBlock* case_else_block = (BasicBlock*)info->case_else_block;

    if(case_else_block) {
        if(first_case && !case_after_return) {
            Builder.CreateBr(case_else_block);
        }

        BasicBlock* current_block_before;
        llvm_change_block(case_else_block, &current_block_before, info, FALSE);
    }

    if(expression_node == 0) {
        Builder.CreateBr(cond_then_block);
    }
    else {
        if(!compile(expression_node, info)) {
            return FALSE;
        }

        LVALUE rvalue = *get_value_from_stack(-1);

        dec_stack_ptr(1, info);
        Value* lvalue = (Value*)info->switch_expression;
        sNodeType* left_type = info->switch_expression_type;

        if(lvalue == nullptr) {
            compile_err_msg(info, "No in the switch.");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        if(auto_cast_posibility(left_type, rvalue.type))
        {
            cast_right_type_to_left_type(left_type, &rvalue.type, &rvalue, info);
        }

        Value* conditional_value = Builder.CreateICmpEQ(lvalue, rvalue.value, "eqtmpY");
        free_right_value_objects(info);
        Builder.CreateCondBr(conditional_value, cond_then_block, cond_else_block);
    }

    if(last_case) {
        BasicBlock* current_block_before;
        llvm_change_block(cond_then_block, &current_block_before, info, FALSE);
    }

    info->case_else_block = cond_else_block;

    if(first_statment) {
        if(!compile(first_statment, info)) {
            return FALSE;
        }
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

BOOL pre_compile_case_expression(unsigned int node, sCompileInfo* info)
{
    unsigned int expression_node = gNodes[node].uValue.sCase.mExpression;
    BOOL first_case = gNodes[node].uValue.sCase.mFirstCase;
    BOOL last_case = gNodes[node].uValue.sCase.mLastCase;
    BOOL case_after_return = gNodes[node].uValue.sCase.mCaseAfterReturn;
    unsigned int first_statment = gNodes[node].uValue.sCase.mFirstStatment;
    unsigned int last_statment = gNodes[node].uValue.sCase.mLastStatment;

    if(last_statment) {
        if(!pre_compile(last_statment, info)) {
            return FALSE;
        }
    }

    sFunction* fun = (sFunction*)info->function;

    if(expression_node == 0) {
    }
    else {
        if(!pre_compile(expression_node, info)) {
            return FALSE;
        }
    }

    if(first_statment) {
        if(!pre_compile(first_statment, info)) {
            return FALSE;
        }
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

BOOL compile_break_expression(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

    if(info->num_loop <= 0) {
        compile_err_msg(info, "No in the loop");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    BasicBlock* loop_end_block = (BasicBlock*)info->loop_end_block[info->num_loop-1];
    //info->num_loop--;

    if(info->switch_expression == NULL && info->current_block) {
        free_objects_until_loop_top(nullptr, info);
    }
    Builder.CreateBr(loop_end_block);

    sFunction* fun = (sFunction*)info->function;

    Function* llvm_function = fun->mLLVMFunction;

    BasicBlock* after_break = BasicBlock::Create(TheContext, "after_break", llvm_function);

    BasicBlock* current_block_before;
    llvm_change_block(after_break, &current_block_before, info, FALSE);

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

BOOL pre_compile_break_expression(unsigned int node, sCompileInfo* info)
{
    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

BOOL compile_continue_expression(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

    if(info->num_loop2 <= 0) {
        compile_err_msg(info, "No in the loop");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    BasicBlock* loop_begin_block = (BasicBlock*)info->loop_begin_block[info->num_loop2-1];
    //info->num_loop2--;

    Builder.CreateBr(loop_begin_block);

    sFunction* fun = (sFunction*)info->function;

    Function* llvm_function = fun->mLLVMFunction;

    BasicBlock* after_continue = BasicBlock::Create(TheContext, "after_continue", llvm_function);

    BasicBlock* current_block_before;
    llvm_change_block(after_continue, &current_block_before, info, FALSE);

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

BOOL pre_compile_continue_expression(unsigned int node, sCompileInfo* info)
{
    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

BOOL compile_cast(unsigned int node, sCompileInfo* info)
{
    char type_name[VAR_NAME_MAX];
    xstrncpy(type_name, gNodes[node].uValue.sCast.mTypeName, VAR_NAME_MAX);
    sNodeType* right_type = create_node_type_with_class_name(type_name);
    
    if(right_type == NULL || right_type->mClass == NULL) {
        compile_err_msg(info, "Cast failed(%s)", type_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(info->no_output) {
        info->type = right_type;
        return TRUE;
    }

show_node_type(right_type);

    if(info->generics_type) {
        BOOL success_solve;
        (void)solve_generics(&right_type, info->generics_type, &success_solve);

        solve_method_generics2(&right_type, info->method_generics_types);
    }
show_node_type(right_type);

    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }
    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    if(!cast_right_type_to_left_type(right_type, &left_type, &lvalue, info))
    {
        compile_err_msg(info, "Cast failed(%s)", type_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    push_value_to_stack_ptr(&lvalue, info);

    info->type = clone_node_type(lvalue.type);

    return TRUE;
}

BOOL pre_compile_cast(unsigned int node, sCompileInfo* info)
{
    char type_name[VAR_NAME_MAX];
    xstrncpy(type_name, gNodes[node].uValue.sCast.mTypeName, VAR_NAME_MAX);
    sNodeType* right_type = create_node_type_with_class_name(type_name);

    int left_node = gNodes[node].mLeft;
    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    info->type = right_type;
    return TRUE;
}

static BOOL compile_sizeof1(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
#ifdef __32BIT_CPU__
        info->type = create_node_type_with_class_name("int");
#else
        info->type = create_node_type_with_class_name("long");
#endif
        return TRUE;
    }

    char type_name[VAR_NAME_MAX];
    xstrncpy(type_name, gNodes[node].uValue.sSizeOf.mTypeName, VAR_NAME_MAX);
    sNodeType* node_type2 = create_node_type_with_class_name(type_name);

    if(node_type2 == NULL || node_type2->mClass == NULL) {
        compile_err_msg(info, "Invalid type name(%s)1", type_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    uint64_t alloc_size = 0;
    if(!get_size_from_node_type(&alloc_size, node_type2, node_type2, info))
    {
        return FALSE;
    }

    /// result ///
#ifdef __32BIT_CPU__
    LVALUE llvm_value;
    llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(32, alloc_size, false)); 
    llvm_value.type = create_node_type_with_class_name("int");
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("int");
#else
    LVALUE llvm_value;
    llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(64, alloc_size, false)); 
    llvm_value.type = create_node_type_with_class_name("long");
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("long");
#endif

    return TRUE;
}

static BOOL pre_compile_sizeof1(unsigned int node, sCompileInfo* info)
{
#ifdef __32BIT_CPU__
    info->type = create_node_type_with_class_name("int");
#else
    info->type = create_node_type_with_class_name("long");
#endif

    return TRUE;
}

BOOL compile_sizeof2(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
#ifdef __32BIT_CPU__
        info->type = create_node_type_with_class_name("int");
#else
        info->type = create_node_type_with_class_name("long");
#endif
        return TRUE;
    }

    char var_name[VAR_NAME_MAX];
    xstrncpy(var_name, gNodes[node].uValue.sSizeOf.mVarName, VAR_NAME_MAX);
    sVar* var = get_variable_from_table(info->lv_table, var_name);

    if(var == NULL) {
        var = get_variable_from_table(info->gv_table, var_name);
    }

    if(var == NULL) {
        compile_err_msg(info, "Invalid var name(%s)", var_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }


    sNodeType* node_type2 = var->mType;

    if(node_type2 == NULL || node_type2->mClass == NULL) {
        compile_err_msg(info, "Invalid var name(%s)", var_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    uint64_t alloc_size = 0;
    if(!get_size_from_node_type(&alloc_size, node_type2, node_type2, info))
    {
        return FALSE;
    }

    /// result ///
#ifdef __32BIT_CPU__
    LVALUE llvm_value;
    llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(32, alloc_size, false)); 
    llvm_value.type = create_node_type_with_class_name("int");
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("int");
#else
    LVALUE llvm_value;
    llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(64, alloc_size, false)); 
    llvm_value.type = create_node_type_with_class_name("long");
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("long");
#endif

    return TRUE;
}

BOOL pre_compile_sizeof2(unsigned int node, sCompileInfo* info)
{
#ifdef __32BIT_CPU__
    info->type = create_node_type_with_class_name("int");
#else
    info->type = create_node_type_with_class_name("long");
#endif
    return TRUE;
}

static BOOL compile_alignof1(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
#ifdef __32BIT_CPU__
        info->type = create_node_type_with_class_name("int");
#else
        info->type = create_node_type_with_class_name("long");
#endif
        return TRUE;
    }

    char type_name[VAR_NAME_MAX];
    xstrncpy(type_name, gNodes[node].uValue.sSizeOf.mTypeName, VAR_NAME_MAX);
    sNodeType* node_type2 = create_node_type_with_class_name(type_name);

    if(node_type2 == NULL || node_type2->mClass == NULL) {
        compile_err_msg(info, "Invalid type name(%s)1", type_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    int alignment = get_llvm_alignment_from_node_type(node_type2);

#ifdef __32BIT_CPU__
    LVALUE llvm_value;
    llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(32, alignment, false)); 
    llvm_value.type = create_node_type_with_class_name("long");
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("int");

#else
    LVALUE llvm_value;
    llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(64, alignment, false)); 
    llvm_value.type = create_node_type_with_class_name("long");
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("long");

#endif

    return TRUE;
}

static BOOL pre_compile_alignof1(unsigned int node, sCompileInfo* info)
{
#ifdef __32BIT_CPU__
    info->type = create_node_type_with_class_name("int");
#else
    info->type = create_node_type_with_class_name("long");
#endif

    return TRUE;
}

BOOL compile_alignof2(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
#ifdef __32BIT_CPU__
        info->type = create_node_type_with_class_name("int");
#else
        info->type = create_node_type_with_class_name("long");
#endif
        return TRUE;
    }

    char var_name[VAR_NAME_MAX];
    xstrncpy(var_name, gNodes[node].uValue.sSizeOf.mVarName, VAR_NAME_MAX);
    sVar* var = get_variable_from_table(info->lv_table, var_name);

    if(var == NULL) {
        var = get_variable_from_table(info->gv_table, var_name);
    }

    if(var == NULL) {
        compile_err_msg(info, "Invalid var name(%s)", var_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }


    sNodeType* node_type2 = var->mType;

    if(node_type2 == NULL || node_type2->mClass == NULL) {
        compile_err_msg(info, "Invalid var name(%s)", var_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    int alignment = get_llvm_alignment_from_node_type(node_type2);

#ifdef __32BIT_CPU__
    LVALUE llvm_value;
    llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(32, alignment, false)); 
    llvm_value.type = create_node_type_with_class_name("long");
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("int");

#else
    LVALUE llvm_value;
    llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(64, alignment, false)); 
    llvm_value.type = create_node_type_with_class_name("long");
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("long");

#endif

    return TRUE;
}

BOOL pre_compile_alignof2(unsigned int node, sCompileInfo* info)
{
#ifdef __32BIT_CPU__
    info->type = create_node_type_with_class_name("int");
#else
    info->type = create_node_type_with_class_name("long");
#endif

    return TRUE;
}

BOOL compile_typedef(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("void");
        return TRUE;
    }

    char name[VAR_NAME_MAX];
    xstrncpy(name, gNodes[node].uValue.sTypeDef.mName, VAR_NAME_MAX);

    char type_name[VAR_NAME_MAX];
    xstrncpy(type_name, gNodes[node].uValue.sTypeDef.mTypeName, VAR_NAME_MAX);

    add_typedef(name, type_name);

    return TRUE;
}

BOOL pre_compile_typedef(unsigned int node, sCompileInfo* info)
{
    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

static BOOL compile_conditional(unsigned int node, sCompileInfo* info)
{
    /// compile expression ///
    unsigned int conditional_node = gNodes[node].mLeft;

    if(!compile(conditional_node, info)) 
    {
        return FALSE;
    }

    sNodeType* conditional_type = info->type;

    LVALUE conditional_value = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    sNodeType* bool_type = create_node_type_with_class_name("bool");

    if(auto_cast_posibility(bool_type, conditional_type)) 
    {
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

    int compile_time_value = -1;

    ConstantInt* constant_value;

    if(constant_value = dyn_cast<ConstantInt>(conditional_value.value)) 
    {
        compile_time_value = constant_value->getZExtValue();
    }

    LVALUE llvm_value;
    if(compile_time_value != -1) {
        if(compile_time_value) {
            unsigned int value1_node  = gNodes[node].mRight;

            if(!compile(value1_node, info)) 
            {
                return FALSE;
            }
        }
        else {
            unsigned int value2_node  = gNodes[node].mMiddle;

            if(!compile(value2_node, info)) 
            {
                return FALSE;
            }
        }

        if(type_identify_with_class_name(info->type, "void")) {
            memset(&llvm_value, 0, sizeof(LVALUE));
        }
        else {
            llvm_value = *get_value_from_stack(-1);
        }
    }
    else {
        sFunction* fun = (sFunction*)info->function;

        Function* llvm_function = fun->mLLVMFunction;

        BasicBlock* cond_then_block = BasicBlock::Create(TheContext, "cond_jump_then", llvm_function);
        BasicBlock* cond_else_block = BasicBlock::Create(TheContext, "cond_else_block", llvm_function);

        BasicBlock* cond_end_block = BasicBlock::Create(TheContext, "cond_end", llvm_function);

        free_right_value_objects(info);

        Builder.CreateCondBr(conditional_value.value, cond_then_block, cond_else_block);

        BasicBlock* current_block_before;
        llvm_change_block(cond_then_block, &current_block_before, info, FALSE);

        unsigned int value1_node  = gNodes[node].mRight;

        if(!compile(value1_node, info)) 
        {
            return FALSE;
        }

        LVALUE value1;
        Value* result_value;
        int result_value_alignment;
        sNodeType* value1_result_type;
        if(type_identify_with_class_name(info->type, "void")) {
            memset(&value1, 0, sizeof(LVALUE));

            value1_result_type = create_node_type_with_class_name("int");

            Type* llvm_result_type;
            if(!create_llvm_type_from_node_type(&llvm_result_type, value1_result_type, value1_result_type, info))
            {
                compile_err_msg(info, "Getting llvm type failed(99)");
                show_node_type(value1_result_type);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            IRBuilder<> builder(&llvm_function->getEntryBlock(), llvm_function->getEntryBlock().begin());

            result_value = builder.CreateAlloca(llvm_result_type, 0, "condtional_result_value");

            result_value_alignment = get_llvm_alignment_from_node_type(value1_result_type);

            Value* zero_value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);

            Builder.CreateAlignedStore(zero_value, result_value, result_value_alignment);
        }
        else {
            LVALUE value1 = *get_value_from_stack(-1);
            dec_stack_ptr(1, info);

            value1_result_type = clone_node_type(info->type);

            Type* llvm_result_type;
            if(!create_llvm_type_from_node_type(&llvm_result_type, value1_result_type, value1_result_type, info))
            {
                compile_err_msg(info, "Getting llvm type failed(99)");
                show_node_type(value1_result_type);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            IRBuilder<> builder(&llvm_function->getEntryBlock(), llvm_function->getEntryBlock().begin());

            result_value = builder.CreateAlloca(llvm_result_type, 0, "condtional_result_value");

            result_value_alignment = get_llvm_alignment_from_node_type(value1_result_type);

            Builder.CreateAlignedStore(value1.value, result_value, result_value_alignment);
        }

        Builder.CreateBr(cond_end_block);

        BasicBlock* current_block_before2;
        llvm_change_block(cond_else_block, &current_block_before2, info, FALSE);

        unsigned int value2_node  = gNodes[node].mMiddle;

        if(!compile(value2_node, info)) 
        {
            return FALSE;
        }

        LVALUE value2;
        if(type_identify_with_class_name(info->type, "void")) {
            memset(&value2, 0, sizeof(LVALUE));

            sNodeType* value2_result_type = create_node_type_with_class_name("int");

            Type* llvm_result_type;
            if(!create_llvm_type_from_node_type(&llvm_result_type, value2_result_type, value2_result_type, info))
            {
                compile_err_msg(info, "Getting llvm type failed(99)");
                show_node_type(value2_result_type);
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            IRBuilder<> builder(&llvm_function->getEntryBlock(), llvm_function->getEntryBlock().begin());

            Value* zero_value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);

            if(auto_cast_posibility(value1_result_type, value2_result_type)) 
            {
                if(!cast_right_type_to_left_type(value1_result_type
                                , &value2_result_type, &value2, info))
                {
                    compile_err_msg(info, "Cast failed");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }

            Builder.CreateAlignedStore(zero_value, result_value, result_value_alignment);
        }
        else {
            value2 = *get_value_from_stack(-1);
            dec_stack_ptr(1, info);
            sNodeType* value2_result_type = clone_node_type(info->type);

            if(auto_cast_posibility(value1_result_type, value2_result_type)) 
            {
                if(!cast_right_type_to_left_type(value1_result_type
                                , &value2_result_type, &value2, info))
                {
                    compile_err_msg(info, "Cast failed");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }

            Builder.CreateAlignedStore(value2.value, result_value, result_value_alignment);
        }

        Builder.CreateBr(cond_end_block);

        BasicBlock* current_block_before3;
        llvm_change_block(cond_end_block, &current_block_before3, info, FALSE);

        llvm_value.value = Builder.CreateAlignedLoad(result_value, result_value_alignment);
        llvm_value.type = clone_node_type(value1_result_type);
        llvm_value.address = nullptr;
        llvm_value.var = nullptr;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        info->type = clone_node_type(value1_result_type);

        push_value_to_stack_ptr(&llvm_value, info);
    }

    if(llvm_value.type->mHeap) {
        append_heap_object_to_right_value(&llvm_value, info);
    }

    return TRUE;
}

BOOL pre_compile_conditional(unsigned int node, sCompileInfo* info)
{
    /// compile expression ///
    unsigned int conditional_node = gNodes[node].mLeft;

    if(!pre_compile(conditional_node, info)) 
    {
        return FALSE;
    }

    sNodeType* conditional_type = info->type;

    unsigned int value1_node  = gNodes[node].mRight;

    if(!pre_compile(value1_node, info)) 
    {
        return FALSE;
    }

    unsigned int value2_node  = gNodes[node].mMiddle;

    if(!pre_compile(value2_node, info)) 
    {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

static BOOL compile_dummy_heap(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(left_node == 0) {
        compile_err_msg(info, "require dummy heap target object");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(!compile(left_node, info)) {
        return FALSE;
    }

    LVALUE llvm_value = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    llvm_value.type->mDummyHeap = TRUE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = clone_node_type(llvm_value.type);

    return TRUE;
}

static BOOL pre_compile_dummy_heap(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* result_type = clone_node_type(info->type);

    result_type->mDummyHeap = TRUE;

    info->type = result_type;

    return TRUE;
}


static BOOL compile_managed(unsigned int node, sCompileInfo* info)
{
    char* var_name = gNodes[node].uValue.sManaged.mVarName;

    sVar* var = get_variable_from_table(info->lv_table, var_name);

    if(var == NULL) {
        compile_err_msg(info, "undeclared variable %s(99)", var_name);
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

    var->mType->mHeap = FALSE;
    var->mType->mManaged = TRUE;

    info->type = create_node_type_with_class_name("void"); // dummy

    return TRUE;
}

static BOOL pre_compile_managed(unsigned int node, sCompileInfo* info)
{

    info->type = create_node_type_with_class_name("void"); // dummy

    return TRUE;
}

static BOOL compile_store_address(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    if(left_type->mPointerNum == 0) {
        compile_err_msg(info, "This is not pointer type2(%s)", left_type->mClass->mName);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    left_type->mPointerNum--;

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    Value* address = lvalue.value;
    Value* value = rvalue.value;

    int alignment = get_llvm_alignment_from_node_type(right_type);

    Builder.CreateAlignedStore(value, address, alignment);

    info->type = right_type;

    return TRUE;
}

static BOOL pre_compile_store_address(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    unsigned int right_node = gNodes[node].mRight;

    if(!pre_compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    info->type = right_type;

    return TRUE;
}

static BOOL compile_isheap(unsigned int node, sCompileInfo* info)
{
    if(info->no_output) {
        info->type = create_node_type_with_class_name("bool");
        return TRUE;
    }

    char type_name[VAR_NAME_MAX];
    xstrncpy(type_name, gNodes[node].uValue.sIsHeap.mTypeName, VAR_NAME_MAX);
    sNodeType* node_type2 = create_node_type_with_class_name(type_name);

    if(node_type2 == NULL || node_type2->mClass == NULL) {
        compile_err_msg(info, "Invalid type name(%s)1", type_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(info->generics_type) {
        BOOL success_solve;
        (void)solve_generics(&node_type2, info->generics_type, &success_solve);

        solve_method_generics2(&node_type2, info->method_generics_types);
    }

    BOOL is_heap = node_type2->mHeap;

    /// result ///
    LVALUE llvm_value;
    llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(1, is_heap, false)); 
    llvm_value.type = create_node_type_with_class_name("bool");
    llvm_value.address = nullptr;
    llvm_value.var = nullptr;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

static BOOL pre_compile_isheap(unsigned int node, sCompileInfo* info)
{
    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

static BOOL compile_borrow(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(left_node == 0) {
        compile_err_msg(info, "require borrow target object");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(!compile(left_node, info)) {
        return FALSE;
    }

    LVALUE llvm_value = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    if(info->no_output) {
        info->type = clone_node_type(llvm_value.type);
        return TRUE;
    }

    llvm_value.type->mHeap = FALSE;

    remove_from_right_value_object(llvm_value.value, info);

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = clone_node_type(llvm_value.type);

    return TRUE;
}

static BOOL pre_compile_borrow(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!pre_compile(left_node, info)) {
        return FALSE;
    }

    return TRUE;
}

BOOL compile(unsigned int node, sCompileInfo* info)
{
    if(node == 0) {
        return TRUE;
    }
//show_node(node);
//printf("%s %d TYPE %d\n", gSName, yylineno, gNodes[node].mNodeType);
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

        case kNodeTypeCharValue:
            if(!compile_char_value(node, info)) {
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
            if(!compile_sub(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeMult:
            if(!compile_mult(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeDiv:
            if(!compile_div(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeMod:
            if(!compile_mod(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeBlock:
            break;

        case kNodeTypeStoreVariable:
            if(!compile_store_variable(node, info)) {
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

        case kNodeTypeNull:
            if(!compile_null(node, info)) {
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

        case kNodeTypeDelete:
            if(!compile_delete(node, info)) {
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

        case kNodeTypeGT:
            if(!compile_gt(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLT:
            if(!compile_lt(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeGE:
            if(!compile_ge(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLE:
            if(!compile_le(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLShift:
            if(!compile_lshift(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeRShift:
            if(!compile_rshift(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeOr:
            if(!compile_or(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeAnd:
            if(!compile_and(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeXor:
            if(!compile_xor(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLogicalDenial:
            if(!compile_logical_denial(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeComplement:
            if(!compile_complement(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeRefference:
            if(!compile_reffernce(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeDerefference:
            if(!compile_dereffernce(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypePlusEq:
            if(!compile_plus_eq(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeMinusEq:
            if(!compile_minus_eq(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeMultEq:
            if(!compile_mult_eq(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeDivEq:
            if(!compile_div_eq(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeAndEq:
            if(!compile_and_eq(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeXorEq:
            if(!compile_xor_eq(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeOrEq:
            if(!compile_or_eq(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLShiftEq:
            if(!compile_lshift_eq(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeRShiftEq:
            if(!compile_rshift_eq(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLoadElement:
            if(!compile_load_element(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeStoreElement:
            if(!compile_store_element(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeArrayInitializer: {
            if(!compile_array_initializer(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeFor: {
            if(!compile_for_statment(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeWhile: {
            if(!compile_while_statment(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeDoWhile: {
            if(!compile_do_while_statment(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeSwitch: {
            if(!compile_switch_statment(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeCase: {
            if(!compile_case_expression(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeBreak: {
            if(!compile_break_expression(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeContinue: {
            if(!compile_continue_expression(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeCast: {
            if(!compile_cast(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeSizeOf1: {
            if(!compile_sizeof1(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeSizeOf2: {
            if(!compile_sizeof2(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeAlignOf1: {
            if(!compile_alignof1(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeAlignOf2: {
            if(!compile_alignof2(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeTypeDef: {
            if(!compile_typedef(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeCoroutine: {
            if(!compile_coroutine(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeConditional: {
            if(!compile_conditional(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeDummyHeap: {
            if(!compile_dummy_heap(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeManaged: {
            if(!compile_managed(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeStoreAddress:
            if(!compile_store_address(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeIsHeap:
            if(!compile_isheap(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeBorrow:
            if(!compile_borrow(node, info)) {
                return FALSE;
            }
            break;

        default:
            fprintf(stderr, "invalid node type\n");
            exit(2);
            break;
    }
//TheModule->print(llvm::errs(), nullptr);

    return TRUE;
}

BOOL pre_compile(unsigned int node, sCompileInfo* info)
{
    if(node == 0) {
        return TRUE;
    }

    xstrncpy(info->sname, gNodes[node].mSName, PATH_MAX);
    info->sline = gNodes[node].mLine;

    switch(gNodes[node].mNodeType) {
        case kNodeTypeFunction:
            if(!pre_compile_function(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeIntValue:
            if(!pre_compile_int_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeCharValue:
            if(!pre_compile_char_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeCStringValue:
            if(!pre_compile_str_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeAdd:
            if(!pre_compile_add(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeReturn:
            if(!pre_compile_return(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeSub:
            if(!pre_compile_sub(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeMult:
            if(!pre_compile_mult(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeDiv:
            if(!pre_compile_div(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeMod:
            if(!pre_compile_mod(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeBlock:
            break;

        case kNodeTypeStoreVariable:
            if(!pre_compile_store_variable(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLoadVariable:
            if(!pre_compile_load_variable(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeFunctionCall:
            if(!pre_compile_function_call(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeExternalFunction:
            if(!pre_compile_external_function(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeIf:
            if(!pre_compile_if(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeTrue:
            if(!pre_compile_true(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeFalse:
            if(!pre_compile_false(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeNull:
            if(!pre_compile_null(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeCreateObject:
            if(!pre_compile_create_object(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeClone:
            if(!pre_compile_clone(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeDelete:
            if(!pre_compile_delete(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeStruct:
            if(!pre_compile_struct(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeUnion:
            if(!pre_compile_union(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeDefineVariable:
            if(!pre_compile_define_variable(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeEquals:
            if(!pre_compile_equals(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeNotEquals:
            if(!pre_compile_not_equals(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLoadField:
            if(!pre_compile_load_field(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeStoreField:
            if(!pre_compile_store_field(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeAndAnd:
            if(!pre_compile_and_and(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeOrOr:
            if(!pre_compile_or_or(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeGT:
            if(!pre_compile_gt(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLT:
            if(!pre_compile_lt(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeGE:
            if(!pre_compile_ge(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLE:
            if(!pre_compile_le(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLShift:
            if(!pre_compile_lshift(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeRShift:
            if(!pre_compile_rshift(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeOr:
            if(!pre_compile_or(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeAnd:
            if(!pre_compile_and(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeXor:
            if(!pre_compile_xor(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLogicalDenial:
            if(!pre_compile_logical_denial(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeComplement:
            if(!pre_compile_complement(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeRefference:
            if(!pre_compile_reffernce(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeDerefference:
            if(!pre_compile_dereffernce(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypePlusEq:
            if(!pre_compile_plus_eq(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeMinusEq:
            if(!pre_compile_minus_eq(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeMultEq:
            if(!pre_compile_mult_eq(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeDivEq:
            if(!pre_compile_div_eq(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeAndEq:
            if(!pre_compile_and_eq(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeXorEq:
            if(!pre_compile_xor_eq(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeOrEq:
            if(!pre_compile_or_eq(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLShiftEq:
            if(!pre_compile_lshift_eq(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeRShiftEq:
            if(!pre_compile_rshift_eq(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLoadElement:
            if(!pre_compile_load_element(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeStoreElement:
            if(!pre_compile_store_element(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeArrayInitializer: {
            if(!pre_compile_array_initializer(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeFor: {
            if(!pre_compile_for_statment(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeWhile: {
            if(!pre_compile_while_statment(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeDoWhile: {
            if(!pre_compile_do_while_statment(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeSwitch: {
            if(!pre_compile_switch_statment(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeCase: {
            if(!pre_compile_case_expression(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeBreak: {
            if(!pre_compile_break_expression(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeContinue: {
            if(!pre_compile_continue_expression(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeCast: {
            if(!pre_compile_cast(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeSizeOf1: {
            if(!pre_compile_sizeof1(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeSizeOf2: {
            if(!pre_compile_sizeof2(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeAlignOf1: {
            if(!pre_compile_alignof1(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeAlignOf2: {
            if(!pre_compile_alignof2(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeTypeDef: {
            if(!pre_compile_typedef(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeCoroutine: {
            if(!pre_compile_coroutine(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeConditional: {
            if(!pre_compile_conditional(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeDummyHeap: {
            if(!pre_compile_dummy_heap(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeManaged: {
            if(!pre_compile_managed(node, info)) {
                return FALSE;
            }
            }
            break;

        case kNodeTypeStoreAddress:
            if(!pre_compile_store_address(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeIsHeap:
            if(!pre_compile_isheap(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeBorrow:
            if(!pre_compile_borrow(node, info)) {
                return FALSE;
            }
            break;

        default:
            fprintf(stderr, "invalid node type\n");
            exit(2);
            break;
    }

    return TRUE;
}

