int puts(char* str);

int exit(int rc);
int printf(char* str, ...);
void*% calloc(size_t nmemb, size_t size);
void free(void *ptr);

int fun() {
    return 2;
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

bool int::fun(int self) {
    printf("self %d\n", self);

    return true;
}

bool const_test(const char* str) 
{
    puts(str);
    return true;
}

extern char* strcpy(char* str, char* str2);
extern int strlen(char* str);
extern char* strcat(char* str, char* str2);

inline char*% string(char* str) 
{
    char*% result = new char[strlen(str) + 1];

    strcpy(result, str);

    return result;
}

char*% string2(char*% str) 
{
    char*% result = new char[strlen(str) + 6];

    strcpy(result, str);
    strcat(result, "+ABC");

    return result;
}

char*% string_test1(char*% var) 
{
    char*% a = new char[128];

    strcpy(a, var);

    puts(a);

    return a;
}

struct Data {
    int a;
    int b;
};

union Data2 {
    int a;
    long b;
};


int main() 
{
    puts("HELLO WORLD");

    xassert("test1", true);

    xassert("message passing test", 3.fun());
    xassert("const test", const_test("ABC"));

    char*% b = string_test1(string2(string("ABC")));

    puts(b);

    int xxx = 123;

    xassert("eqeq test", xxx == 123);

    int (*aaa)(int) = int lambda(int a) { return 123; };

//    int lambda() a = int lambda() { printf("%d\n", xxx); return 123; };

/*
    Data data;

    Data2 data2;

    data.a = 111;

    xassert("store and load field test", data.a == 111);
*/

    return 0; 
}

