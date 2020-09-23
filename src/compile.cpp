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

extern "C"
{
void dec_stack_ptr(int value, sCompileInfo* info)
{
    gLLVMStack -= value;

    info->stack_num -= value;
}

BOOL compile(unsigned int node, sCompileInfo* info)
{
show_node(node);

    switch(gNodes[node].mNodeType) {
        case kNodeTypeFunction:
            break;

        case kNodeTypeIntValue:
            break;

        case kNodeTypeAdd:
            break;

        case kNodeTypeSub:
            break;

        case kNodeTypeMult:
            break;

        case kNodeTypeDiv:
            break;

        case kNodeTypeBlock:
            break;
    }
    

    return TRUE;
}

}
