int fun(int a, int b) {
    return a + b;
}

enum { kA = 123, kB, kC };

int main() {
    int (*aaa)(int,int) = fun;

    aaa(1,2);

    printf("kA %d kB %d kC %d\n", kA, kB, kC);

    return 0;
}
