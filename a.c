#include <stdio.h>

enum { A, B=A };

int main() {
    int a = A;
    int b = B;

    printf("a %d b %d\n", a, b);

    return 0;
}
