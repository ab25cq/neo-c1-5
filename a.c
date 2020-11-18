#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


int main() {
    char c[128];
    char c2[128];

    __builtin_memmove(c, c2, 128);
    __builtin_memcpy(c, c2, 128);
    __builtin_memset(c, 0, 128);

    return 0;
}
