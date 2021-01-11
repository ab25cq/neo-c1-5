#include "common.h"

sVarTable* gHeadVTable;

void init_vtable()
{
    gHeadVTable = NULL;
}

void final_vtable()
{
    sVarTable* it;

    it = gHeadVTable;
    while(it) {
        sVarTable* next;

        next = it->mNext;
        free(it);

        it = next;
    }
}

static int mNumVarTables = 0;

sVarTable* init_var_table()
{
    sVarTable* result;

    result = xcalloc(1, sizeof(sVarTable));

    result->mNext = gHeadVTable;
    gHeadVTable = result;

    result->mID = mNumVarTables++;

    return result;
}

sVarTable* clone_var_table(sVarTable* lv_table)
{
    sVarTable* result = init_var_table();

    result->mMaxBlockVarNum = lv_table->mMaxBlockVarNum;
    result->mBlockLevel = lv_table->mBlockLevel;
    result->mID = lv_table->mID;
    result->mCoroutineTop = lv_table->mCoroutineTop;

    sVarTable* it = lv_table;

    sVar* p = it->mLocalVariables;

    while(1) {
        if(p->mName[0] != 0) {
            if(!add_variable_to_table(result, p->mName, p->mType, p->mLLVMValue, p->mIndex, p->mGlobal, p->mConstant))
            {
                fprintf(stderr, "overflow variable table11\n");
                exit(2);
            }
        }

        p++;

        if(p == lv_table->mLocalVariables + LOCAL_VARIABLE_MAX) {
            break;
        }
    }

    if(it->mParent) {
        result->mParent = clone_var_table(it->mParent);
    }
    else {
        result->mParent = NULL;
    }

    result->mVarNum = lv_table->mVarNum;

    return result;
}

void restore_var_table(sVarTable* left, sVarTable* right)
{
    sVarTable* it = left;
    sVarTable* it2 = right;

    while(it && it2) {
        sVar* p = it->mLocalVariables;

        while(1) {
            if(p->mName[0] != 0) {
                sVar* p2 = it2->mLocalVariables;
                while(1) {
                    if(p2->mName[0] != 0 && strcmp(p->mName, p2->mName) == 0) 
                    {
                        p->mType = p2->mType;
                    }

                    p2++;

                    if(p2 == it2->mLocalVariables + LOCAL_VARIABLE_MAX) {
                        break;
                    }
                }
            }

            p++;

            if(p == it->mLocalVariables + LOCAL_VARIABLE_MAX) {
                break;
            }
        }

        it = it->mParent;
        it2 = it2->mParent;
    }
}

//////////////////////////////////////////////////
// local variable table
//////////////////////////////////////////////////
// result: (true) success (false) overflow the table or a variable which has the same name exists
BOOL add_variable_to_table(sVarTable* table, char* name, sNodeType* type_, void* llvm_value, int index, BOOL global, BOOL constant)
{
    int hash_value;
    sVar* p;

    hash_value = get_hash_key(name, LOCAL_VARIABLE_MAX);
    p = table->mLocalVariables + hash_value;

    while(1) {
        if(p->mName[0] == 0) {
            xstrncpy(p->mName, name, VAR_NAME_MAX);
            if(index == -1) {
                p->mIndex = table->mVarNum++;
            }
            else {
                p->mIndex = index;
            }

            if(type_) {
                p->mType = clone_node_type(type_);
            }
            else {
                p->mType = NULL;
            }
            p->mBlockLevel = table->mBlockLevel;
            p->mLLVMValue = llvm_value;
            p->mGlobal = global;
            p->mConstant = constant;

            if(table->mVarNum >= LOCAL_VARIABLE_MAX) {
                return FALSE;
            }

            return TRUE;
        }
        else {
            if(strcmp(p->mName, name) == 0) {
                return TRUE;

/*
                if(p->mBlockLevel < table->mBlockLevel) {
                    xstrncpy(p->mName, name, VAR_NAME_MAX);
                    p->mIndex = table->mVarNum++;
                    if(type_) {
                        p->mType = clone_node_type(type_);
                    }
                    else {
                        p->mType = NULL;
                    }

                    p->mBlockLevel = table->mBlockLevel;
                    p->mLLVMValue = llvm_value;

                    if(table->mVarNum >= LOCAL_VARIABLE_MAX) {
                        return FALSE;
                    }

                    return TRUE;
                }
                else {
                    return FALSE;
                }
*/
            }
            else {
                p++;

                if(p == table->mLocalVariables + LOCAL_VARIABLE_MAX) {
                    p = table->mLocalVariables;
                }
                else if(p == table->mLocalVariables + hash_value) {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}

sVar* get_variable_from_index(sVarTable* table, int index)
{
    int hash_value;
    sVar* p;

    p = table->mLocalVariables;

    while(1) {
        if(p->mName[0] != 0 && p->mIndex == index) {
            return p;
        }

        p++;

        if(p == table->mLocalVariables + LOCAL_VARIABLE_MAX) {
            break;
        }
    }

    return NULL;
}

// result: (null) not found (sVar*) found
sVar* get_variable_from_this_table_only(sVarTable* table, char* name)
{
    int hash_value;
    sVar* p;

    hash_value = get_hash_key(name, LOCAL_VARIABLE_MAX);

    p = table->mLocalVariables + hash_value;

    while(1) {
        if(p->mName[0] == 0) {
            return NULL;
        }
        else if(strcmp((char*)p->mName, name) == 0) {
            return p;
        }

        p++;

        if(p == table->mLocalVariables + LOCAL_VARIABLE_MAX) {
            p = table->mLocalVariables;
        }
        else if(p == table->mLocalVariables + hash_value) {
            return NULL;
        }
    }
}

BOOL is_included_var_from_this_table_only(sVarTable* table, sVar* var_)
{
    int hash_value = 0;

    sVar* p = table->mLocalVariables + hash_value;

    while(1) {
        if(p == var_) {
            return TRUE;
        }

        p++;

        if(p == table->mLocalVariables + LOCAL_VARIABLE_MAX) {
            return FALSE;
        }
    }
}

void check_already_added_variable(sVarTable* table, char* name)
{
    sVar* var_ = get_variable_from_this_table_only(table, name);
    
    if(var_ != NULL && !var_->mGlobal) {
        fprintf(stderr, "Variable (%s) has already_added in this variable table", name);
        exit(2);
    }
}

// result: (null) not found (sVar*) found
sVar* get_variable_from_table(sVarTable* table, char* name)
{
    sVarTable* it;
    sVar* var_;

    it = table;

    while(it) {
        var_ = get_variable_from_this_table_only(it, name);

        if(var_) {
            return var_;
        }

        it = it->mParent;
    }

    return NULL;
}

static int get_sum_of_parent_var_num(sVarTable* table)
{
    int n = 0;
    sVarTable* p = table->mParent;

    while(p) {
        n += p->mVarNum;
        p = p->mParent;
    }

    return n;
}

int get_variable_index(sVarTable* table, char* name, BOOL* parent)
{
    sVarTable* it = table;

    while(it) {
        sVar* var_ = get_variable_from_this_table_only(it, name);

        if(var_) {
            return var_->mIndex + get_sum_of_parent_var_num(it);
        }

        it = it->mParent;
        *parent = TRUE;
    }

    return -1;
}

int get_var_num(sVarTable* table)
{
    return table->mVarNum + table->mMaxBlockVarNum;
}

int get_parent_var_num_of_sum(sVarTable* table)
{
    return get_sum_of_parent_var_num(table);
}

void set_max_block_var_num(sVarTable* lv_table, sVarTable* old_table)
{
    /// get local var number of this block ///
    int lv_num_of_this_block = lv_table->mVarNum + lv_table->mMaxBlockVarNum;
    if(lv_num_of_this_block > old_table->mMaxBlockVarNum) {
       old_table->mMaxBlockVarNum = lv_num_of_this_block;
    }
}

void show_vtable_current_only(sVarTable* table)
{
    sVarTable* it = table;

    while(it) {
        sVar* p = it->mLocalVariables;

        while(1) {
            if(p->mName[0] != 0) {
                printf("name %s index %d block level %d constant %d value %p global %d\n", p->mName, p->mIndex, p->mBlockLevel, p->mConstant, p->mLLVMValue, p->mGlobal);

                if(p->mType && p->mType->mClass) 
                {
                    printf("%s\n", p->mType->mClass->mName);
                }
            }

            p++;

            if(p == it->mLocalVariables + LOCAL_VARIABLE_MAX) {
                break;
            }
        }
        break;
    }
}

void show_vtable(sVarTable* table)
{
    sVarTable* it = table;

    while(it) {
        sVar* p = it->mLocalVariables;

        while(1) {
            if(p->mName[0] != 0) {
                printf("name %s index %d block level %d constant %d value %p global %d\n", p->mName, p->mIndex, p->mBlockLevel, p->mConstant, p->mLLVMValue, p->mGlobal);

                if(p->mType && p->mType->mClass) 
                {
                    printf("%s\n", p->mType->mClass->mName);
                }
            }

            p++;

            if(p == it->mLocalVariables + LOCAL_VARIABLE_MAX) {
                break;
            }
        }

        it = it->mParent;
    }
}




