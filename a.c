int fun(int a, int b) {
    return a + b;
}

int main() {
    int (*aaa)(int,int) = fun;

    return 0;
}
