#include "common.h"

struct sTypeDefTable
{
    char mName[VAR_NAME_MAX];
    sNodeType* mItem;
};

static struct sTypeDefTable gTypeDefTable[TYPEDEF_MAX];

void init_typedef()
{
    memset(gTypeDefTable, 0, sizeof(struct sTypeDefTable)*TYPEDEF_MAX);
}

void add_typedef(char* name, sNodeType* node_type)
{
    unsigned int hash_value = get_hash_key(name, TYPEDEF_MAX);

    struct sTypeDefTable* it = gTypeDefTable + hash_value;

    while(1) {
        if(strcmp(it->mName,"") == 0) {
            xstrncpy(it->mName, name, VAR_NAME_MAX);
            it->mItem = clone_node_type(node_type);
            break;
        }
        else {
            it++;

            if(it == gTypeDefTable + TYPEDEF_MAX)
            {
                it = gTypeDefTable;
            }
            else if(it == gTypeDefTable + hash_value)
            {
                fprintf(stderr, "overflow typedef number\n");
                exit(2);
            }
        }
    }
}

sNodeType* get_typedef(char* name)
{
    sNodeType* result = NULL;

    if(strcmp(name, "") == 0) {
        return NULL;
    }

    unsigned int hash_value = get_hash_key(name, TYPEDEF_MAX);

    struct sTypeDefTable* it = gTypeDefTable + hash_value;

    while(1) {
        if(strcmp(it->mName, name) == 0) {
            result = clone_node_type(it->mItem);
            break;
        }
        else {
            it++;

            if(it == gTypeDefTable + TYPEDEF_MAX)
            {
                it = gTypeDefTable;
            }
            else if(it == gTypeDefTable + hash_value)
            {
                break;
            }
        }
    }

    return result;
}

