int puts(char* str);

int exit(int rc);
int printf(char* str, ...);
void*% calloc(size_t nmemb, size_t size);
void free(void *ptr);
int atoi(const char* str);
int atoi(const char* str);

int fun() {
    puts("called fun");
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

int int::fun(int self) {
    puts("called int::fun");
    printf("self %d\n", self);

    return 123;
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

struct GenericsData<T> {
    T a;
    T b;
};

int GenericsData<T>::show(GenericsData<T> self)
{
    T a;
    a = 123;
    T b = 234;

    self.a = a;
    self.b = b;

    printf("%d %d\n", self.a, self.b);

    return 123;
}

struct GenericsData2<T> {
    T a;
};

void GenericsData2<T>::fun(GenericsData2<T>* self)
{
    GenericsData<int> data;
    data.a = 123;
    data.b = 234;
    data.show();
}

template <M> M fun2(M a) {
    return a + 1;
}

template <M> M fun3(M (*aaa)(char*), char* bbb) {
    return aaa(bbb);
}

template <M> M GenericsData<T>::map(GenericsData<T> self, M (*aaa)(T))
{
    self.a = 123;
    return aaa(self.a);
}


void inheritFun()
{
    puts("inheritFun version 1");
}

inherit void inheritFun()
{
    inherit();
    puts("inheritFun version 2");
}

struct GenericsData3<T> {
    T a;
    T b;
};

void GenericsData3<T>::fun(GenericsData3<T> self)
{
    puts("GenericsData3<T>::fun version1");
    GenericsData2<int>* xyz = new GenericsData2<int>;

    xyz.fun();
}

inherit void GenericsData3<T>::fun(GenericsData3<T> self)
{
    self.inherit();
    puts("GenericsData3<T>::fun version2");
    GenericsData2<int>* xyz = new GenericsData2<int>;

    xyz.fun();
}

//int gA;

//enum { kA, kB, kC };

int main() 
{
    puts("HELLO WORLD");

    xassert("test1", true);

    fun();

    xassert("message passing test", 3.fun() == 123);
    xassert("const test", const_test("ABC"));

    char*% b = string_test1(string2(string("ABC")));

    puts(b);

    int xxx = 123;

    xassert("eqeq test", xxx == 123);

    int (*aaa)() = int lambda() { puts("FUN"); return xxx; };

    xassert("function pointer test", aaa() == 123);

    Data data;

    data.a = 123;
    data.b = 234;

    xassert("load field and store test", data.a == 123 && data.b == 234);

    GenericsData<int> data2;

    data2.a = 123;
    data2.b = 234;

    xassert("load field and store test2", data2.a == 123 && data2.b == 234);

    xassert("generics fun test", data2.show() == 123);

    xassert("method generics fun test", fun2(123) == 124);

    xassert("method generics fun test2", fun3(int lambda(char* str) { return atoi(str); }, "123") == 123);

    xassert("map test", data2.map(int lambda(int c) { return c + 1; }) == 124);

    inheritFun();

    GenericsData2<int>* xyz = new GenericsData2<int>;

    xyz.fun();

    GenericsData3<int> xyz2;

    xyz2.fun();

//    xassert("enum test", kA == 0 && kB==1 && kC == 2);

    //gA = 1;

    //xassert("global variable", gA == 1);

    return 0;
}

