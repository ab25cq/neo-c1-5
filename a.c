#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a = 123;
    int* b = &a;

    int c = 234;
    int* d = &c;

    *b = *d;

    if(*d == 234) {
        puts("OK");
    }

    int** e = &d;

    printf("%d\n", **e);

    int len = MB_LEN_MAX * 2;

    printf("len %d\n", len);

    return 0;
}
