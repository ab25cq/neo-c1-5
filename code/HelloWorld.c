int puts(char* str);

int exit(int rc);

bool xassert(char* msg, bool exp) 
{
    puts(msg);

    if(exp) {
        puts("ok");
    }
    else {
        puts("failed");
        exit(2);
    }
}

int main() 
{ 
    int a = 1+1;
    return a; 
}

