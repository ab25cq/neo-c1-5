int puts(char* str);

int exit(int rc);

void xassert(char* msg, bool exp) 
{
    puts(msg);

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

    xassert("test...", true);

    return 0; 
}

