#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int fun(int a, int b)
{
    return a + b;
}

void* xsprintf(char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    char* tmp;
    int len = vasprintf(&tmp, msg, args);
    va_end(args);

    return tmp;
}

int main() {

    return 0;
}
