
int fun() {
    int a = 0;
    int b = 1/a;
    return 123;
}

int main() {
    int (*aaa)() = int lambda() { return 123; };
    fun();

    return 0;
}
