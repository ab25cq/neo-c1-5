#include "common.h"

struct sTypeDefTable
{
    char mName[VAR_NAME_MAX];
    char mItem[VAR_NAME_MAX];
};

static struct sTypeDefTable gTypeDefTable[TYPEDEF_MAX];

void init_typedef()
{
    memset(gTypeDefTable, 0, sizeof(struct sTypeDefTable)*TYPEDEF_MAX);
}

void add_typedef(char* name, char* type_name)
{
    unsigned int hash_value = get_hash_key(name, TYPEDEF_MAX);

    struct sTypeDefTable* it = gTypeDefTable + hash_value;

    while(1) {
        if(strcmp(it->mName,"") == 0) {
            xstrncpy(it->mName, name, VAR_NAME_MAX);
            xstrncpy(it->mItem, type_name, VAR_NAME_MAX);
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

void get_typedef(char* name, char* result)
{
    xstrncpy(result, name, VAR_NAME_MAX);

    if(strcmp(name, "") == 0) {
        return;
    }

    unsigned int hash_value = get_hash_key(name, TYPEDEF_MAX);

    struct sTypeDefTable* it = gTypeDefTable + hash_value;

    while(1) {
        if(strcmp(it->mName, name) == 0) {
            xstrncpy(result, it->mItem, VAR_NAME_MAX);
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
}

