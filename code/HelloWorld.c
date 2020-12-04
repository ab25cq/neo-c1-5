#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
//#include <wchar.h>
#include "neo-c2.h" 

struct sData;
typedef struct sData sDataType;

sDataType* gSData;

#define AAAAA 12345

long int gAAAAAA = AAAAA;
typedef long unsigned int size_t;

int puts(char* str);

int exit(int rc);
int printf(char* str, ...);
void*% calloc(size_t nmemb, size_t size);
void free(void *ptr);
int atoi(const char* str);
int atoi(const char* str);
int strcmp(const char* str1, const char* str2);

int funXXX() {
int a = 0;
int b = 1/a;
    puts("called fun");
    return 2;
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

struct GenericsData!<T> {
    T a;
    T b;
};

typedef int(*fXXX)(int);

int GenericsData!<T>::show(GenericsData!<T> self)
{
    T a;
    a = 555;
    T b = 666;

    self.a = a;
    self.b = b;

    printf("%d %d\n", self.a, self.b);

    fXXX xxx = int lambda(int c) { return 555 + c; };

    xassert("generics lambda test", xxx(1) == self.a + 1);

    return a;
}

struct GenericsData2!<T> {
    T a;
};

void GenericsData2!<T>::fun(GenericsData2!<T>* self)
{
    GenericsData!<int> data;
    data.a = 123;
    data.b = 234;
    data.show();
}


template !<M> M fun2(M a) {
    return a + 1;
}

template !<M> M fun3(M (*aaa)(char*), char* bbb) {
    return aaa(bbb);
}

template !<M> M GenericsData!<T>::map(GenericsData!<T> self, M (*aaa)(T))
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

struct GenericsData3!<T> {
    T a;
    T b;
};

void GenericsData3!<T>::fun(GenericsData3!<T> self)
{
    puts("GenericsData3!<T>::fun version1");
    GenericsData2!<int>* xyz = new GenericsData2!<int>;

    xyz.fun();
}

inherit void GenericsData3!<T>::fun(GenericsData3!<T> self)
{
    self.inherit();
    puts("GenericsData3!<T>::fun version2");
    GenericsData2!<int>* xyz = new GenericsData2!<int>;

    xyz.fun();
}

int gA;
int gB = 123;

enum { kA, kB, kC };

enum { kA2 = 123, kB2, kC2 };

struct Data3 {
    int a:8;
    int b:4;
};

int gArray[3] = { 1, 2, 3 };

char gArray2[3] = "AB";

int gArray3[] = { 1, 2, 3 };

int gArray4[3][3][3] = {
    { 1,2,3,
    2,3,4,
    5,6,7 },

    { 1,2,3,
    1,2,3,
    1,2,3 },

    { 11,12,13,
    14,15,16,
    17, 18, 19 }
};



#ifndef NULL
#define NULL ((void*)0)
#endif

typedef int (*fAAA)(int);

struct sArrayTest {
    int a[128];
};

struct sFinalizeTest {
    int a;
    int b;
};

sFinalizeTest*% sFinalizeTest::initialize(sFinalizeTest*% self)
{
    self.a = 123;
    self.b = 234;

    return self;
}

void sFinalizeTest::show(sFinalizeTest* self)
{
    printf("sFinalizeTest::show %d %d\n" , self.a, self.b);
}

void sFinalizeTest::finalize(sFinalizeTest* self)
{
    printf("finalize %p\n", self);
    printf("sFinalizeTest::finalize %d %d\n" , self.a, self.b);
}

struct sFinalizeTest2!<T> {
    T a;
    T b;
};

sFinalizeTest2!<T>*% sFinalizeTest2!<T>::initialize(sFinalizeTest2!<T>*% self)
{
    self.a = 123;
    self.b = 234;

    return self;
}

void sFinalizeTest2!<T>::show(sFinalizeTest2!<T>* self)
{
    printf("sFinalizeTest2<T>::show %d %d\n" , self.a, self.b);
}

void sFinalizeTest2!<T>::finalize(sFinalizeTest2!<T>* self)
{
    printf("sFinalizeTest2<T>::finalize %d %d\n" , self.a, self.b);
}

struct sCloneTest {
    int a;
    int b;
};

struct sCloneTest2 {
    sCloneTest*% a;
    int b;
};

struct sCloneTest3!<T> {
    T a;
    T b;
};

sCloneTest3!<T>*% sCloneTest3!<T>::clone(sCloneTest3!<T>* self)
{
    sCloneTest3!<T>*% result = new sCloneTest3!<T>;

    result.a = self.a;
    result.b = self.b;

    return result;
}

struct sCloneTest4 {
    int a;
    int b;
};

sCloneTest4*% sCloneTest4::clone(sCloneTest4* self)
{
    sCloneTest4*% result = new sCloneTest4;

printf("sCloneTest4::clone %d %d\n", self.a, self.b);

    result.a = self.a;
    result.b = self.b;

    return result;
}


int main() 
{
    puts("HELLO WORLD");

    char*% start_str = string("AAA");

    int start_a = 111;
    printf("a %d\n", start_a);

    xassert("test1", true);

    xassert("message passing test", 3.fun() == 123);
    xassert("const test", const_test("ABC"));

    char*% b = string_test1(string2(string("ABC")));

    puts(b);

    int xxx = 123;

    xassert("eqeq test", xxx == 123);

    fAAA aaa = int lambda(int c) { puts("FUN"); printf("xxx %d\n", xxx); return xxx + c; };

    xassert("function pointer test", aaa(1) == 124);

    xassert("eqeq test", xxx == 123);

    Data data;

    data.a = 123;
    data.b = 234;

    xassert("load field and store test", data.a == 123 && data.b == 234);

    GenericsData!<int> data2;

    data2.a = 123;
    data2.b = 234;

    xassert("load field and store test2", data2.a == 123 && data2.b == 234);
    xassert("generics fun test", data2.show() == 555);

    xassert("method generics fun test", fun2(123) == 124);

    xassert("method generics fun test2", fun3(int lambda(char* str) { return atoi(str); }, "123") == 123);

    xassert("map test", data2.map(int lambda(int c) { return c + 1; }) == 124);

    inheritFun();

    GenericsData2!<int>* xyz = new GenericsData2!<int>;
    xyz.fun();

    GenericsData3!<int> xyz2;

    xyz2.fun();

    gA = 1;

    xassert("global variable", gA == 1);
    xassert("global variable2", gB == 123);

    xassert("enum test", kA == 0 && kB==1 && kC == 2);
    xassert("enum test2", kA2 == 123 && kB2== 124 && kC2 == 125);

    struct { int a; int b; } anonyumous_struct_data;

    anonyumous_struct_data.a = 123;
    anonyumous_struct_data.b = 234;

    xassert("anonymous struct test", anonyumous_struct_data.a == 123 && anonyumous_struct_data.b == 234);

    union { int a; int b; } anonyumous_union_data;

    anonyumous_union_data.a = 123;

    xassert("anonyumous_union_data test" ,anonyumous_union_data.b == 123);

    Data3 data3;

    data3.a = 123;
    data3.b = 234;

    xassert("struct bit test", data3.a == 123 && data3.b == 234);

    xassert("gt lt ge le", 1 > 0 && 2 <= 2 && 3 < 4 && 1 <= 1);

    xassert("shift", (2 >> 1) == 1 && (2 << 1) == 4);
    xassert("and or xor", (1 & 1) && (1 | 0) && (1 ^ 0));

    Data3*% data3_2 = new Data3;

    data3_2->a = 234;
    data3_2->b = 345;

    xassert("struct bit test2", data3_2->a == 234 && data3_2->b == 345);

    xassert("logical denial", !0);

    char compl_a = 0xFFFE;
    xassert("complement ", ~compl_a == 1);

    int data4 = 123;
    int* p_data4 = &data4;

    xassert("pointer", *p_data4 == 123);

    int** pp_data4 = &p_data4;

    xassert("pointer2", **pp_data4 == 123);

    char*% str2 = new char[128];
    strcpy(str2, "ABC");
    (*str2) ++;

    xassert("inc test", strcmp(str2, "BBC") == 0);

    (*str2) --;

    xassert("inc test2", strcmp(str2, "ABC") == 0);

    (*str2) += 2;

    xassert("inc test3", strcmp(str2, "CBC") == 0);

    int plus_plus = 1;

    xassert("plus_plus test", ++plus_plus == 2);
    xassert("plus_plus test", plus_plus == 2);

    xassert("minus minus test test", --plus_plus == 1 && plus_plus == 1);

    int mult_eq = 12;

    mult_eq *= 2;

    xassert("mult eq test", mult_eq == 24);

    char array[100];

    strcpy(array, "ABC");


    xassert("array test", strcmp(array, "ABC") == 0);

    int array_num = 128;
    char array2[array_num];

    strcpy(array2, "ABC");

    xassert("array test2", strcmp(array2, "ABC") == 0);

    int array3[3];

    array3[0] = 123;

    xassert("array test3", array3[0] == 123);

    int array4[3][3];

    array4[1][2] = 123;

    xassert("array test4", array4[1][2] == 123);

    char array5[10][100];

    strcpy(array5[0], "ABC");
    strcpy(array5[1], "DEF");

    xassert("array test5", strcmp(array5[0], "ABC") == 0 && strcmp(array5[1], "DEF") == 0);

    xassert("array initializer test", gArray[0] == 1 && gArray[1] == 2 && gArray[2] == 3);

    gArray[1] = 123;

    xassert("global array test", gArray[1] == 123);

    int array6[3] = { 1, 2, 3 };

    xassert("array initializer test2", array6[0] == 1 && array6[1] == 2 && array6[2] == 3);

    char array7[3] = "AB";

    xassert("array initializer test3", strcmp(array7, "AB") == 0);

    xassert("array initializer test4", strcmp(gArray2, "AB") == 0);

    xassert("array initializer test5", gArray3[0] == 1 && gArray3[1] == 2 && gArray3[2] == 3);

    int array8[] = { 1, 2, 3 };

    xassert("array initializer test6", array8[0] == 1 && array8[1] == 2 && array8[2] == 3);

    char ccc = '\n';
    char ccc2 = 'a';
    char ccc3 = '\0';

    xassert("char test", ccc == '\n' && ccc2 == 'a' && ccc3 == '\0');

    for(int i=0; i<3; i++) {
        printf("i %d\n", i);
    }

    int i=0;
    while(i<3) {
        printf("i %d\n", i);
        i++;
    }

    i = 0;
    do {
        printf("i %d\n", i);
        i++;
    } while( i < 3);

    switch(1) {
        case 2:
        case 1:
            puts("1 or 2");
            break;

        case 3:
            puts("3");
            break;

        default:
            puts("default");
            break;
    }

    int aaaaaa = gArray4[0][1][2];

    xassert("global array initializer test", aaaaaa == 4);

    xassert("array initializer test", gArray4[1][1][1] == 2 && gArray4[2][0][1] == 12);

    int ay[2][2][3] = { 
        { 1,2,3 }, { 4,5,6 },
        { 7,8,9 }, { 11,12,13 }
    };

    xassert("local array initializer test", ay[0][1][2] == 6);

    ay[0][1][2] = 123;

    xassert("local array test", ay[0][1][2] == 123);

    char* aa[2] = { "AAA", "BBB" };

    xassert("local cstring array initializer test", strcmp(aa[0], "AAA") == 0 && strcmp(aa[1], "BBB") == 0);

    int nnnnn = 123;

    char* bbbbbbbbb = (char*)nnnnn;

    int mmmmm = (int)bbbbbbbbb;

    xassert("cast test", mmmmm == 123);

    xassert("sizeof test", sizeof(int) == 4);

    int a[2];
    xassert("sizeof test", sizeof(a) == 8);

    long aaaaaaa = 123;
    long unsigned int bbbbbbbb = 123;

    //funXXX();

    int conditional = 1;

    xassert("conditional", (conditional == 1 ? 2:0) == 2);

    int api_level = 1;
    xassert("conditional2", (api_level == 1 ? api_level: -1) == 1);

    int asss = 1;
    int bsss = 2;

    xassert("xsprintf", strcmp(xsprintf("%d %d", asss, bsss), "1 2") == 0);

    char ades[1024];
    char* des = ades;

    int dessize = 1;

    des[dessize-1] = '\0';

//    xassert("char* equals", "AAA".equals("AAA"));

    char ccc = 'A';
    char* p = &ccc;

    xassert("pointer test", *p == 'A');

    int lenX = 1, lenX2 = 2;

    xassert("varible test", lenX == 1 && lenX2 == 2);

    puts(1.to_string());

    if(false) {
        puts("AAA");
    }
    else if(true) {
        puts("BBB");
    }
    else {
        puts("CCC");
    }

    xassert("int compare", 1.compare(1) == 0);
    xassert("char compare", "AAA".compare("AAA") == 0);

    sArrayTest array_test;

    array_test.a[0] = 123;
    array_test.a[1] = 234;

    xassert("field array test", array_test.a[0] == 123 && array_test.a[1] == 234);

    sFinalizeTest*% finalize_test1 = new sFinalizeTest.initialize();

    finalize_test1.show();

    sFinalizeTest2!<int>*% finalize_test2 = new sFinalizeTest2!<int>.initialize();

    finalize_test2.show();

    buffer*% buf = new buffer.initialize();

    buf.append_str("ABC");
    buf.append_str("DEF");

    xassert("buffer test", buf.to_string().equals("ABCDEF"));

    list!<int>*% li1 = new list!<int>.initialize();

    li1.push_back(1);
    li1.push_back(2);
    li1.push_back(3);

    xassert("list test", li1.item(0, -1) == 1 && li1.item(1, -1) == 2 && li1.item(2, -1) == 3);

    sCloneTest*% clone_test = new sCloneTest;

    clone_test.a = 123;
    clone_test.b = 234;

    sCloneTest*% clone_test2 = clone clone_test;

    xassert("clone test", clone_test2.a == 123 && clone_test2.b == 234);

    sCloneTest2*% clone_test3 = new sCloneTest2;

    clone_test3.a = new sCloneTest;

    clone_test3.a.a = 123;
    clone_test3.a.b = 234;

    clone_test3.b = 345;

    sCloneTest2*% clone_test4 = clone clone_test3;

    xassert("clone test2", clone_test4.a.a == 123 && clone_test4.a.b == 234 && clone_test4.b == 345);

    sCloneTest4*% clone_test5 = new sCloneTest4;

    clone_test5.a = 123;
    clone_test5.b = 234;

    sCloneTest4*% clone_test6 = clone clone_test5;

    xassert("clone test3", clone_test6.a == 123 && clone_test6.b == 234);

    sCloneTest3!<int>*% clone_test7 = new sCloneTest3!<int>;

    clone_test7.a = 123;
    clone_test7.b = 234;

    sCloneTest3!<int>*% clone_test8 = clone clone_test7;

    xassert("clone test4", clone_test8.a == 123 && clone_test8.b == 234);

    list!<int>*% li2 = new list!<int>.initialize();

    li2.push_back(1);
    li2.push_back(2);
    li2.push_back(3);

    xassert("list test", li2.item(0, -1) == 1 && li2.item(1, -1) == 2 && li2.item(2, -1) == 3);

    list!<int>*% li3 = clone li2;

    xassert("list test2", li3.item(0, -1) == 1 && li3.item(1, -1) == 2 && li3.item(2, -1) == 3);

    li3.insert(1, 5);

    xassert("list test3", li3.item(1, -1) == 5 && li3.item(2, -1) == 2 && li3.item(3, -1) == 3);

    li3.delete(1);

    xassert("list test4", li3.item(0, -1) == 1 && li3.item(1, -1) == 2 && li3.item(2, -1) == 3);

    list!<int>*% li4 = clone li2;

    li4.delete_range(0,2);

    xassert("list test5", li4.item(0, -1) == 3);

    list!<int>*% li5 = clone li2;

    int ah = li5.pop_front(-1);

    xassert("list test6", ah == 1 && li5.item(0, -1) == 2);

    list!<int>*% li6 = clone li2;

    li6.replace(0, 5);

    xassert("list test7", li6.item(0, -1) == 5 && li6.item(1, -1) == 2 && li6.item(2, -1) == 3);

    list!<int>*% li7 = clone li2;

    li7.each(void lambda(int it, int it2, bool* it3) {
            printf("it %d it2 %d\n", it, it2);
        }
    );

    return 0;
}


/*
    for(int i=0; i<3; i++) {
        printf("i %d\n", i);

        if(i == 2) {
            continue;
        }
    }
*/
/*
*/
