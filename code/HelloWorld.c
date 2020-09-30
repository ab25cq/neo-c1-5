int puts(char* str);

int exit(int rc);

/*
bool xassert(char* msg, bool exp) 
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
*/
// aaaa
// aaaa

int main() 
{ 
    puts("HELLO WORLD");

    if(0) {
        puts("if ok");
    }
    else if(0) {
        puts("else if ok1");
    }
    else if(0) {
        puts("else if ok2");
    }
    else {
        puts("else");
    }

    return 0; 
}

