int puts(char* str);

int exit(int rc);

int printf(char* str, ...);

bool int::fun(int self) {
    printf("self %d\n", self);

    return true;
}

void xassert(char* msg, bool exp) 
{
    printf("%s...", msg);

    if(exp) {
        puts("yes");
    }
    else {
        puts("no");
        exit(2);
    }
}

bool const_test(const char* str) 
{
    puts(str);
    return true;
}

/*
extern char* strcpy(char* str, char* str2);

char*% string_test1() {
    char*% result = new char[128];


}
*/

// aaaa
// aaaa

int main() 
{ 
    puts("HELLO WORLD");

    xassert("test1", true);

    xassert("message passing test", 3.fun());
    xassert("const test", const_test("ABC"));

    return 0; 
}

