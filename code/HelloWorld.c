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

// aaaa
// aaaa

int main() 
{ 
    puts("HELLO WORLD");

    xassert("test1", true);

    xassert("message passing test", 3.fun());

    return 0; 
}

