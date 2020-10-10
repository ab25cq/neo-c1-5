int fun(int a, int b) {
    return a + b;
}

int main() {
    int (*aaa)(int,int) = fun;

    aaa(1,2);

    return 0;
}
