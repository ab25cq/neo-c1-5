int puts(char* str);

int exit(int rc);

int printf(char* str, ...);

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

    return 0; 
}

