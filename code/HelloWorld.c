#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include <wchar.h>
#include <limits.h>
#include <pcre.h>
//#include <dirent.h>
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
    M b = 1;
    return a + 1 + b;
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

enum __pid_type
  {
    F_OWNER_TID = 0,		/* Kernel thread.  */
    F_OWNER_PID,		/* Process.  */
    F_OWNER_PGRP,		/* Process group.  */
    F_OWNER_GID = F_OWNER_PGRP	/* Alternative, obsolete name.  */
  };

struct sVarTable {
    int mVarNum;
    int mMaxBlockVarNum;

    int mBlockLevel;
    
    struct sVarTable* mParent;
};

struct sVar 
{
    int a;
    int b;
};

extern sVar*% sVar::initialize(sVar*% self);

extern int sNodeTree_create_lambda();

struct _fpstate
{
  struct sVar st[8];
  struct sVar xmm[16];
};

struct sigcontext
{
  //__extension__ union
  union
    {
      struct sVar * fpstate;
      long long int __fpstate_word;
    };
};

typedef struct XXXX AAAAAAAAAAAAAAAA;

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

    xassert("method generics fun test", fun2(123) == 125);

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

    xassert("pointer test1", *p_data4 == 123);

    int** pp_data4 = &p_data4;

    xassert("pointer test2", **pp_data4 == 123);

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

    xassert("pointer test3", *p == 'A');

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
    });

    list!<int>*% li8 = li2.sublist(0,2);

    li8.each(void lambda(int it, int it2, bool* it3) {
        printf("it %d it2 %d\n", it, it2);
    });

    xassert("list test8", li8.length() == 2 && li8.item(0, -1) == 1 && li8.item(1, -1) == 2);

    list!<int>*% li9 = li2.reverse();

    xassert("list test9", li9.length() == 3 && li9.item(0, -1) == 3 && li9.item(1, -1) == 2 && li9.item(2, -1) == 1);

    list!<string>*% li10 = new list!<string>.initialize();

    li10.push_back(string("aaa"));
    li10.push_back(string("bbb"));
    li10.push_back(string("ccc"));

    xassert("list test10", li10.join(",").equals("aaa,bbb,ccc"));

    list!<string>*% li11 = new list!<string>.initialize();

    li11.push_back(string("CCC"));
    li11.push_back(string("AAA"));
    li11.push_back(string("BBB"));

    list!<string>*% li12 = li11.sort();

    xassert("list test11", li12.item(0, -1).equals("AAA") && li12.item(1,-1).equals("BBB") && li12.item(2, -1).equals("CCC"));

    list!<string>*% li99 = new list!<string>.initialize();

    li99.push_back(string("1"));
    li99.push_back(string("2"));
    li99.push_back(string("3"));

    list!<int>*% li13 = li99.map(
        int lambda(char* item) { return atoi(item); }
    );

    printf("li13 %d\n", li13.length());

    li13.each(void lambda(int it, int it2, bool* it3) {
        printf("it %d it2 %d\n", it, it2);
    });

    xassert("list test12", li13.item(0, -1) == 1 && li13.item(1, -1) == 2 && li13.item(2, -1) == 3);

    list!<int>*% li14 = new list!<int>.initialize();

    li14.push_back(1);
    li14.push_back(1);
    li14.push_back(2);
    li14.push_back(2);
    li14.push_back(3);

    list!<int>*% li15 = li14.uniq();

    xassert("list test13", li15.item(0, -1) == 1 && li15.item(1, -1) == 2 && li15.item(2, -1) == 3);

    list!<int>*% li100 = new list!<int>.initialize();

    li100.push_back(1);
    li100.push_back(1);
    li100.push_back(2);
    li100.push_back(2);
    li100.push_back(5);
    li100.push_back(3);

    printf("%d\n", li100.find(5, -1));

    xassert("list test14", li100.find(5, -1) == 4);

    list!<int>*% li116 = new list!<int>.initialize();

    li116.push_back(1);
    li116.push_back(2);
    li116.push_back(3);

    list!<int>*% li117 = new list!<int>.initialize();

    li117.push_back(1);
    li117.push_back(2);
    li117.push_back(3);

    xassert("list test15", li116.equals(li117));

    list!<int>*% li18 = new list!<int>.initialize();

    li18.push_back(1);
    li18.push_back(2);
    li18.push_back(3);

    list!<int>*% li19 = li18.filter(bool lambda(int it) {
        return it >= 2;
    }
    );

    xassert("list test16", li19.item(0, -1) == 2 && li19.item(1, -1) == 3);

    vector!<int>*% v1 = new vector!<int>.initialize();

    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    xassert("vector test1", v1.item(0, -1) == 1 && v1.item(1, -1) == 2 && v1.item(2, -1) == 3);

    vector!<int>*% v2 = clone v1;

    xassert("vector test2", v2.item(0, -1) == 1 && v2.item(1, -1) == 2 && v2.item(2, -1) == 3 && v2.length() == 3);

    v2.each (void lambda(int it, int it2, bool* it3) {
        printf("it %d it2 %d\n", it, it2);
    });

    xassert("vector test3", v2.find(1, -1) == 0);

    vector!<int>*% v3 = clone v1;

    xassert("vector test4", v3.pop_back(-1) == 3 && v3.length() == 2);

    vector!<int>*% v4 = clone v1;

    vector!<string>*% v5 = v4.map (
        string lambda(int it) {
            return xsprintf("%d", it);
        }
    );

    v5.each (
        void lambda(char* it, int it2, bool* it3) {
            printf("it %s it2 %d\n", it, it2);
        }
    );

    xassert("vector test5", v5.item(0, null).equals(string("1")) && v5.item(1, null).equals(string("2")) && v5.item(2, null).equals(string("3")) && v5.length() == 3);

    vector!<int>*% v6 = new vector!<int>.initialize();

    v6.push_back(1);
    v6.push_back(2);
    v6.push_back(3);

    vector!<int>*% v7 = new vector!<int>.initialize();

    v7.push_back(1);
    v7.push_back(2);
    v7.push_back(3);

    xassert("vector test6", v6.equals(v7));

    vector!<string>*% v8 = new vector!<string>.initialize();

    v8.push_back(string("aaa"));
    v8.push_back(string("bbb"));
    v8.push_back(string("ccc"));

    xassert("vector test7", v8.item(0, null).equals(string("aaa")));

   list!<string>*% li20 = v8.to_list();

    xassert("list test17", li20.item(0, null).equals(string("aaa")) && li20.item(1, null).equals(string("bbb")) && li20.item(2, null).equals(string("ccc")));

    vector!<string>*% v9 = new vector!<string>.initialize();

    v9.push_back(string("aaa"));
    v9.push_back(string("bbb"));
    v9.push_back(string("ccc"));

    v9.replace(0, string("DDD"));

    xassert("vector test7", v9.item(0, null).equals(string("DDD")) && v9.item(1, null).equals(string("bbb")) && v9.item(2,null).equals(string("ccc")) && v9.length() == 3);

    list!<string>*% li21 = v9.to_list();

    xassert("vector test8", li21.item(0, null).equals(string("DDD")) && li21.item(1, null).equals(string("bbb")) && li21.item(2,null).equals(string("ccc")) && li21.length() == 3);

    vector!<int>*% v10 = new vector!<int>.initialize_with_values(3, 10);

    xassert("vector test9", v10.item(0, -1) == 10 && v10.item(1, -1) == 10 && v10.item(2, -1) == 10 && v10.length() == 3);

    tuple4!<int,int,string,char*>*% t1 = new tuple4!<int,int,string,char*>;

    t1.v1 = 123;
    t1.v2 = 234;
    t1.v3 = string("ABC");
    t1.v4 = "DEF";

    xassert("tuple test1", t1.v1 == 123 && t1.v2 == 234 && t1.v3.equals(string("ABC")) && t1.v4.equals("DEF"));

    map!<string, int>*% m1 = new map!<string,int>.initialize();

    m1.insert(string("ABC"), 1);
    m1.insert(string("DEF"), 2);

    xassert("map test1", m1.at(string("ABC"), -1) == 1 && m1.at(string("DEF"), -1) == 2);

    map!<string, int>*% m2 = new map!<string,int>.initialize();

    m2.insert(string("ABC"), 1);
    m2.insert(string("DEF"), 2);

    xassert("map test2", m1.equals(m2));

    xassert("map test3", m1.find(string("ABC")));

    tuple3!<string, string, int>*% t2 = new tuple3!<string, string, int>;

    t2.v1 = string("ABC");
    t2.v2 = string("DEF");
    t2.v3 = 123;

    tuple3!<string, string, int>*% t3 = new tuple3!<string, string, int>;

    t3.v1 = string("ABC");
    t3.v2 = string("DEF");
    t3.v3 = 123;

    xassert("tuple test2", t2.equals(t3));

    xassert("char* test1", "ABC".equals("ABC"));

    xassert("char* test2", "ABC".length() == 3);

    xassert("char* test3", "ABC".to_string().equals("ABC"));

    xassert("char* test4", "ABC".compare("DEF") < 0);


    buffer*% b1 = new buffer.initialize();

    b1.append_str("ABC");
    b1.append_str("DEF");

    xassert("buffer test1", b1.to_string().equals("ABCDEF"));

    string str3 = string("ABC");

    printf("str %s\n", str3.reverse());

    xassert("string test", str3.reverse().equals("CBA"));

    list!<string>*% li22 = new list!<string>.initialize();

    li22.push_back(string("aaa"));
    li22.push_back(string("bbb"));
    li22.push_back(string("ccc"));

    xassert("string tsst2", li22.join(",").equals("aaa,bbb,ccc"));

    xassert("string tsst3", string("ABC").substring(1,3).equals("BC"));

    xassert("string tsst4", string("ABCDEF").index("C", -1) == 2);
    xassert("string test5", string("ABCDEFABC").rindex("C", -1) == 8);

    xassert("string test6", string("ABC").delete(1).equals("AC"));

    xassert("string test7", string("ABCDEFG").delete_range(1,3).equals("ADEFG"));

    buffer*% buf2 = string("ABC").to_buffer();

    buf2.append_str("DEF");

    xassert("string test8", buf2.to_string().equals("ABCDEF"));

    list!<string>*% li23 = string("ABC,DEF,GHI").split_char(',');

    xassert("string test8", li23.item(0, null).equals("ABC") && li23.item(1, null).equals("DEF") && li23.item(2, null).equals("GHI"));
    xassert("string test9", string("ABC").item(1, -1) == 'B');

    xassert("string test10", string("ABC").replace(1, 'D').equals("ADC"));

    xassert("wstring test1", wstring("ABC").reverse().equals(wstring("CBA")));

    xassert("wstring test2", wstring("ABC").substring(0,2).equals(wstring("AB")));

    xassert("wstring test3", wstring("ABC").index(wstring("B"), -1) == 1);

    xassert("wstring test4", wstring("ABCABC").rindex(wstring("B"), -1) == 4);

    xassert("wstring test5", wstring_from_wchar_t(wstring("ABC").delete(1)).equals(wstring("AC")));

    xassert("wstring test6", wstring_from_wchar_t(wstring("ABC").delete_range(0,1)).equals(wstring("BC")));

    xassert("wstring test7", wstring_from_wchar_t(wstring("ABC").replace(0, (wchar_t)'D')).equals(wstring("DBC")));
    wchar_t wc = wstring("ABC").item(0, -1);

    xassert("wstring test8", wc == (wchar_t)'A');

    int n = 16;
    int array9[n];

    array9[1] = 123;

    xassert("array test", array9[1] == 123);

    wstring wstr = wstring("ABC");

    while(wstr.equals(wstring("ABC"))) {
        wstr.replace(1, (wchar_t)'G');
    }

    wstring wstr2 = wstring("DEF");

    do {
        1+1;
    } while(wstr.equals(wstring("GHI")));

    int iiiiiii = 1;

    for(wstr2.equals(wstring("DEF")); iiiiiii < 2; wstr2.equals(wstring("DEF"))) {
        wstr2.replace(1, (wchar_t)'G');

        iiiiiii++;
    }

    xassert("string regex test1", string("ABC1DEF").index_regex(REGEX("[0-1]", false), -1) == 3);
    xassert("string regex test2", string("ABC1DEF").rindex_regex(REGEX("[0-1]", false), -1) == 3);
    xassert("string regex test3", string("ABC1DEF").sub(REGEX("[0-1]", false), "X", null).equals("ABCXDEF"));
    xassert("string regex test4", string("ABC1DEF").match(REGEX("[A-Z0-9]+", false), null));
    xassert("string regex test5", string("ABC1DEF").match(REGEX("^[A-Z]+$", false), null) == false);

    list!<string>*% li16 = string("ABC,123,DEF,GHI,567").scan(REGEX("\\d+", false));

    xassert("string regex test6", li16.item(0, null).equals("123") && li16.item(1, null).equals("567"));

    list!<string>*% li17 = string("ABC,DEF,GHI").split(REGEX(",", false));

    xassert("string regex test7", li17.item(0, null).equals("ABC") && li17.item(1, null).equals("DEF") && li17.item(2,null).equals("GHI"));

    string("123,456,789").split(REGEX(",", false)).each (
        void lambda(string& it, int it2, bool* it3) {
            puts(it);
        }
    );

    char path[PATH_MAX];

    char* system_path = "LLLL";
    snprintf(path, PATH_MAX, "%s/share/sevenstars/sevenstars.ss", system_path);

    return 0;
}


