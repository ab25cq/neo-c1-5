#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stddef.h>
#include "xfunc.h"

char* xstrncpy(char* des, const char* src, int size)
{
    char* result;

    result = strncpy(des, src, size-1);
    des[size-1] = 0;

    return result;
}

char* xstrncat(char* des, const char* str, int size)
{
    char* result;

    result = strncat(des, str, size-1);
    des[size-1] = 0;

    return result;
}

ALLOC void* xmalloc(size_t size)
{
    void* buf;

    buf = malloc(size);

    if(buf == NULL) {
        fprintf(stderr, "It is not enough memory");
        exit(1);
    }

    return buf;
}

ALLOC char* xstrdup(const char* str)
{
    char* buf;

    buf = strdup(str);

    if(buf == NULL) {
        fprintf(stderr, "It is not enough memory\n");
        exit(1);
    }

    return buf;
}

ALLOC void* xrealloc(void* ptr, size_t size)
{
    void* buf;

    buf = realloc(ptr, size);

    if(buf == NULL) {
        fprintf(stderr, "It is not enough memory\n");
        exit(1);
    }

    return buf;
}

ALLOC void* xcalloc(size_t count, size_t size)
{
    void* buf;

    buf = calloc(count, size);

    if(buf == NULL) {
        fprintf(stderr, "It is not enough memory\n");
        exit(1);
    }

    return buf;
}
