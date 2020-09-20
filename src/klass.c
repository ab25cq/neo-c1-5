#include "common.h"

sClassTable* gHeadClassTable = NULL;
static sClassTable gClassTable[CLASS_NUM_MAX];

unsigned int get_hash_key(char* name, unsigned int max)
{
    unsigned int result = 0;
    char* p = name;
    while(*p) {
        result += *p;
        p++;
    }

    return result % max;
}

static void free_class(sCLClass* klass)
{
    free(klass->mConst.mConst);
    free(klass);
}

static void remove_class(char* class_name_)
{
    unsigned int hash_key = get_hash_key(class_name_, CLASS_NUM_MAX);
    sClassTable* table = gClassTable;
    sClassTable** head_table = &gHeadClassTable;

    sClassTable* p = table + hash_key;

    while(1) {
        if(p->mName == NULL) {
            break;
        }
        else if(strcmp(p->mName, class_name_) == 0) {
            /// remove from liked list ///
            sClassTable* p2 = *head_table;
            sClassTable* p2_before = p2;

            while(p2) {
                if(p2->mItem == p->mItem) {
                    if(p2_before == *head_table) {
                        *head_table = p2->mNextClass;
                    }
                    else {
                        p2_before->mNextClass = p2->mNextClass;
                    }
                    break;
                }

                p2_before = p2;
                p2 = p2->mNextClass;
            }

            /// remove found class ///
            free(p->mName);
            free_class(p->mItem);

            p->mName = NULL;
            p->mItem = NULL;
            break;
        }
        else {
            p++;

            if(p == table + CLASS_NUM_MAX) {
                p = table;
            }
            else if(p == table + hash_key) {
                break;
            }
        }
    }
}

static BOOL put_class_to_table(char* class_name_, sCLClass* klass)
{
    remove_class(class_name_);

    sClassTable* table = gClassTable;
    sClassTable** head_table = &gHeadClassTable;

    unsigned int hash_key = get_hash_key(class_name_, CLASS_NUM_MAX);
    sClassTable* p = table + hash_key;

    while(1) {
        if(p->mName == NULL) {
            p->mName = xstrdup(class_name_);
            p->mItem = klass;

            p->mNextClass = *head_table;
            *head_table = p;
            break;
        }
        else {
            p++;

            if(p == table + CLASS_NUM_MAX) {
                p = table;
            }
            else if(p == table + hash_key) {
                return FALSE;
            }
        }
    }

    return TRUE;
}

static BOOL search_for_class_file(char* class_name_, char* class_file_name, size_t class_file_name_size, int version)
{
    char extname[PATH_MAX];

    snprintf(extname, PATH_MAX, ".ncl");

    if(version == 0) {
        /// current working directory ///
        char* cwd = getenv("PWD");

        if(cwd) {
            snprintf(class_file_name, class_file_name_size, "%s/%s%s", cwd, class_name_, extname);

            if(access(class_file_name, F_OK) == 0) {
                return TRUE;
            }
        }

        /// system shared directory ///
        snprintf(class_file_name, class_file_name_size, "%s/share/neo-c/%s%s", PREFIX, class_name_, extname);

        if(access(class_file_name, F_OK) == 0) {
            return TRUE;
        }
    }
    else {
        /// current working directory ///
        char* cwd = getenv("PWD");

        if(cwd) {
            snprintf(class_file_name, class_file_name_size, "%s/%s@%d%s", cwd, class_name_, version, extname);

            if(access(class_file_name, F_OK) == 0) {
                return TRUE;
            }
        }

        /// system shared directory ///
        snprintf(class_file_name, class_file_name_size, "%s/share/neo-c/%s@%d%s", PREFIX, class_name_, version, extname);

        if(access(class_file_name, F_OK) == 0) {
            return TRUE;
        }
    }

    return FALSE;
}

void read_from_file(char** p, void* buf, size_t size, char* head)
{
    memcpy(buf, *p, size);

    (*p) += size;

    alignment_pointer(p, head);
}

void read_char_from_file(char** p, char* c)
{
    *c = **p;
    (*p)++;
}

void read_int_from_file(char** p, int* n)
{
    *n = *(int*)(*p);
    (*p) += sizeof(int);
}

void read_long_from_file(char** p, clint64* n)
{
    *n = *(clint64*)(*p);
    (*p) +=sizeof(clint64);
}

void read_const_from_file(char** p, sConst* constant, char* head)
{
    int len;
    read_int_from_file(p, &len);

    sConst_init_with_size(constant, len+1);
    constant->mLen = len;

    read_from_file(p, constant->mConst, len, head);
}

static sCLClass* read_class_from_file(char* class_name_, char** p, char* head)
{
    sCLClass* klass = xcalloc(1, sizeof(sCLClass));

    read_const_from_file(p, &klass->mConst, head);

    int n;
    read_int_from_file(p, &n);
    klass->mClassNameOffset = n;

    return klass;
}

static sCLClass* load_class_from_class_file(char* class_name_, char* class_file_name)
{
    sBuf buf;
    if(!read_source(class_file_name, &buf)) {
        return NULL;
    }

    char* p = buf.mBuf;

    /// check magic number. Is this Clover object file? ///
    char c;

    if(*p != 11) { return NULL; }
    p++;
    if(*p != 12) { return NULL; }
    p++;
    if(*p != 34) { return NULL; }
    p++;
    if(*p != 55) { return NULL; }
    p++;
    if(*p != 'N') { return NULL; }
    p++;
    if(*p != 'E') { return NULL; }
    p++;
    if(*p != 'O') { return NULL; }
    p++;
    if(*p != 'C') { return NULL; }
    p++;

    alignment_pointer(&p, buf.mBuf);

    sCLClass* klass = read_class_from_file(class_name_, &p, buf.mBuf);

    if(klass == NULL) {
        fprintf(stderr, "Clover2 can't load class %s because of class file\n", class_name_);
        return NULL;
    }

    if(!put_class_to_table(class_name_, klass)) {
        fprintf(stderr, "overflow class number\n");
        exit(1);
    }

    return klass;
}

static sCLClass* load_class(char* class_name_, int version)
{
    char class_file_name[PATH_MAX+1];
    if(!search_for_class_file(class_name_, class_file_name, PATH_MAX, version)) {
        return NULL;
    }

    sCLClass* result = load_class_from_class_file(class_name_, class_file_name);

    return result;
}

sCLClass* get_class(char* class_name_)
{
    unsigned int hash_key = get_hash_key(class_name_, CLASS_NUM_MAX);
    sClassTable* table = gClassTable;
    sClassTable* p = table + hash_key;

    while(1) {
        if(p->mName) {
            if(strcmp(p->mName, class_name_) == 0) {
                sCLClass* result = p->mItem;
                return result;
            }
            else {
                p++;

                if(p == table + CLASS_NUM_MAX) {
                    p = table;
                }
                else if(p == table + hash_key) {
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    return load_class(class_name_, 0);
}

static sCLClass* alloc_class(char* class_name_, BOOL primitive_, BOOL struct_, BOOL number_type, BOOL unsigned_number, int generics_number, int method_generics_number, BOOL union_, BOOL anonymous, BOOL enum_, BOOL anonymous_var_name)
{
    sCLClass* klass = xcalloc(1, sizeof(sCLClass));

    sConst_init(&klass->mConst);

    klass->mFlags |= (primitive_ ? CLASS_FLAGS_PRIMITIVE:0) | (struct_ ? CLASS_FLAGS_STRUCT:0) | (number_type ? CLASS_FLAGS_NUMBER:0) | (unsigned_number ? CLASS_FLAGS_UNSIGNED_NUMBER:0) | (union_ ? CLASS_FLAGS_UNION:0) | (anonymous ? CLASS_FLAGS_ANONYMOUS:0) | (enum_ ? CLASS_FLAGS_ENUM:0) | (anonymous_var_name ? CLASS_FLAGS_ANONYMOUS_VAR_NAME:0);

    if(generics_number >= 0) {
        klass->mFlags |= CLASS_FLAGS_GENERICS;
    }
    if(method_generics_number >= 0) {
        klass->mFlags |= CLASS_FLAGS_METHOD_GENERICS;
    }

    klass->mClassNameOffset = append_str_to_constant_pool(&klass->mConst, class_name_, FALSE);

    klass->mGenericsNum = generics_number;
    klass->mMethodGenericsNum = method_generics_number;
    klass->mUndefinedStructType = NULL;

    klass->mVersion = 0;

    if(!put_class_to_table(class_name_, klass)) {
        fprintf(stderr, "overflow class number\n");
        exit(1);
    }

    return klass;
}

sCLClass* clone_class(sCLClass* klass)
{
    sCLClass* klass2 = xcalloc(1, sizeof(sCLClass));

    sConst_init(&klass2->mConst);

    klass2->mFlags = klass->mFlags;

    char* class_name_ = CLASS_NAME(klass);

    klass2->mClassNameOffset = append_str_to_constant_pool(&klass2->mConst, class_name_, FALSE);

    klass2->mGenericsNum = klass->mGenericsNum;
    klass2->mMethodGenericsNum = klass->mMethodGenericsNum;

    klass2->mNumFields = klass->mNumFields;

    int i;
    for(i=0; i<klass->mNumFields; i++) {
        char* field_name = CONS_str(&klass->mConst, klass->mFieldNameOffsets[i]);
        klass2->mFieldNameOffsets[i] = append_str_to_constant_pool(&klass2->mConst, field_name, FALSE);
        klass2->mFields[i] = clone_node_type(klass->mFields[i]);
    }

    return klass2;
}

sCLClass* alloc_struct(char* class_name_, BOOL anonymous)
{
    sCLClass* klass = alloc_class(class_name_, FALSE, TRUE, FALSE, FALSE, -1, -1, FALSE, anonymous, FALSE, FALSE);

    return klass;
}

sCLClass* alloc_enum(char* class_name_)
{
    sCLClass* klass = alloc_class(class_name_, FALSE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, TRUE, FALSE);

    return klass;
}

void add_fields_to_struct(sCLClass* klass, int num_fields, char** field_name, struct sNodeTypeStruct* fields[STRUCT_FIELD_MAX])
{
    if(klass->mNumFields + num_fields >= STRUCT_FIELD_MAX) {
        fprintf(stderr, "overflow field number of %s\n", CLASS_NAME(klass));
        exit(0);
    }

    int i;
    for(i=0; i<num_fields; i++) {
        unsigned int offset = append_str_to_constant_pool(&klass->mConst, field_name[i], FALSE);
        klass->mFieldNameOffsets[klass->mNumFields+i] = offset;
        klass->mFields[klass->mNumFields+i] = clone_node_type(fields[i]);
    }

    klass->mNumFields += num_fields;
}

sCLClass* alloc_union(char* class_name_, BOOL anonymous, BOOL anonymous_var_name)
{
    sCLClass* klass = alloc_class(class_name_, FALSE, FALSE, FALSE, FALSE, -1, -1, TRUE, anonymous, FALSE, anonymous_var_name);

    return klass;
}

void add_fields_to_union(sCLClass* klass, int num_fields, char** field_name, struct sNodeTypeStruct* fields[STRUCT_FIELD_MAX])
{
    klass->mNumFields = num_fields;

    if(klass->mNumFields >= STRUCT_FIELD_MAX) {
        fprintf(stderr, "overflow field number of %s\n", CLASS_NAME(klass));
        exit(0);
    }


    int i;
    for(i=0; i<num_fields; i++) {
        klass->mFieldNameOffsets[i] = append_str_to_constant_pool(&klass->mConst, field_name[i], FALSE);
        klass->mFields[i] = clone_node_type(fields[i]);
    }
}

void class_init()
{
    memset(gClassTable, 0, sizeof(sClassTable)*CLASS_NUM_MAX);

    alloc_class("bool", TRUE, FALSE, TRUE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("char", TRUE, FALSE, TRUE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("short", TRUE, FALSE, TRUE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("int", TRUE, FALSE, TRUE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("long", TRUE, FALSE, TRUE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("__uint128_t", TRUE, FALSE, TRUE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("void", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("float", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("double", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("long_double", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("any", FALSE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("TYPEOF", FALSE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("lambda", FALSE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("generics0", FALSE, FALSE, FALSE, FALSE, 0, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("generics1", FALSE, FALSE, FALSE, FALSE, 1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("generics2", FALSE, FALSE, FALSE, FALSE, 2, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("generics3", FALSE, FALSE, FALSE, FALSE, 3, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("generics4", FALSE, FALSE, FALSE, FALSE, 4, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("generics5", FALSE, FALSE, FALSE, FALSE, 5, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("generics6", FALSE, FALSE, FALSE, FALSE, 6, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("generics7", FALSE, FALSE, FALSE, FALSE, 7, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("generics8", FALSE, FALSE, FALSE, FALSE, 8, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("generics9", FALSE, FALSE, FALSE, FALSE, 9, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("mgenerics0", FALSE, FALSE, FALSE, FALSE, -1, 0, FALSE, FALSE, FALSE, FALSE);
    alloc_class("mgenerics1", FALSE, FALSE, FALSE, FALSE, -1, 1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("mgenerics2", FALSE, FALSE, FALSE, FALSE, -1, 2, FALSE, FALSE, FALSE, FALSE);
    alloc_class("mgenerics3", FALSE, FALSE, FALSE, FALSE, -1, 3, FALSE, FALSE, FALSE, FALSE);
    alloc_class("mgenerics4", FALSE, FALSE, FALSE, FALSE, -1, 4, FALSE, FALSE, FALSE, FALSE);
    alloc_class("mgenerics5", FALSE, FALSE, FALSE, FALSE, -1, 5, FALSE, FALSE, FALSE, FALSE);
    alloc_class("mgenerics6", FALSE, FALSE, FALSE, FALSE, -1, 6, FALSE, FALSE, FALSE, FALSE);
    alloc_class("mgenerics7", FALSE, FALSE, FALSE, FALSE, -1, 7, FALSE, FALSE, FALSE, FALSE);
    alloc_class("mgenerics8", FALSE, FALSE, FALSE, FALSE, -1, 8, FALSE, FALSE, FALSE, FALSE);
    alloc_class("mgenerics9", FALSE, FALSE, FALSE, FALSE, -1, 9, FALSE, FALSE, FALSE, FALSE);
    alloc_class("_Float16", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("_Float16x", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("_Float32", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("_Float32x", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("_Float64", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("_Float64x", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("_Float128", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("_Float128x", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);

    if(sizeof(size_t) == 4) {
        add_typedef("size_t", create_node_type_with_class_name("int"));
    }
    else {
        add_typedef("size_t", create_node_type_with_class_name("long"));
    }
    add_typedef("_Bool", create_node_type_with_class_name("bool"));
}

void class_final()
{
    sClassTable* p = gHeadClassTable;

    while(p) {
        if(p->mFreed == FALSE) {
            sClassTable* p2 = gHeadClassTable;
            while(p2) {
                if(p->mItem == p2->mItem) {   // typedef class
                    p2->mFreed = TRUE;
                }
                p2 = p2->mNextClass;
            }
            free_class(p->mItem);
            free(p->mName);
        }
        else {
            free(p->mName);
        }
        p = p->mNextClass;
    }
}

int get_field_index(sCLClass* klass, char* var_name, int* parent_field_index)
{
    if((klass->mFlags & CLASS_FLAGS_STRUCT) || (klass->mFlags & CLASS_FLAGS_UNION)) 
    {
        int i;
        for(i=0; i<klass->mNumFields; i++) {
            if(parent_field_index) {
                sNodeType* field_type = clone_node_type(klass->mFields[i]);

                sCLClass* field_class = field_type->mClass;

                if(field_class->mFlags & CLASS_FLAGS_ANONYMOUS_VAR_NAME)
                {
                    int result = get_field_index(field_class, var_name, NULL);

                    if(result != -1) {
                        *parent_field_index = i;
                        return result;
                    }
                }
            }

            char* field_name = CONS_str(&klass->mConst, klass->mFieldNameOffsets[i]);

            if(strcmp(field_name, var_name) == 0) {
                return i;
            }
        }
    }

    return -1;
}

