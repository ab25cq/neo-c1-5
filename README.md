# neo-c2 compiler language

version 0.9.9

```
> vim hello.c
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include <wchar.h>
#include <limits.h>
#include <pcre.h>
#include "neo-c2.h"

int main() 
{
    string("123,456,789").split(REGEX(",", false)).each (
        void lambda(string& it, int it2, bool* it3) {
            puts(it);
        }
    );

    exit(0);
}

> neo-c2 hello.c
> clang -o hello hello.c.ll -lpcre
> ./hello
123
456
789
```

# 提供できる機能

1. 完ぺきではないがC言語とある程度の互換性。特にヘッダーをincludeしたりライブラリをリンクする場合には問題ないと思われます。

2. GCはないが自動的にオブジェクトが削除されるヒープシステム。右辺値や変数に代入した場合、自動的にfreeが呼ばれます。

3. mixin-layers機能。関数をレイヤーを重ねるように上書きしていけます。

4. string, regex, vector, list, map, tupleなどのコンテナライブラリや文字列ライブラリ。C言語に欠けたコンテナライブラリや正規表現による文字列操作などを提供します。この機能を提供するためにはneo-c2.hをincludeしてください。すべてinlineで定義されているため、neo-c2.hをincludeしない場合は普通のCコンパイラとして機能します。neo-c2.hはシステム側にはインストールされません。言語本体からコピーして使ってください。そのためオリジナルのコレクションや文字列ライブラリを作ることも可能です。

5. 簡易なオブジェクト指向機能。mixin-layersシステムがあるため継承やポリモフィズムは提供しませんが、メッセージパッシングは行えます。

6. Generics, Method Generics. 関数を生成するタイプのGenericsを実装しています。

7. lambda。親のスタックにアクセスできるコルーチンを提供します。型推論はありませんが、関数にルーチンを変数のように渡せます。


# インストール

```
sudo apt-get intall clang gcc g++ make autoconf llvm-dev git libpcre2-dev gdb valgrind xctags flex bison

git clone https://github.com/ab25cq/neo-c2

cd neo-c2

./configure --with-optimize
make
sudo make install
```

# テストした環境

Debian x86_64

# 変更点


# 紹介

* string

```
typedef char*% string;
```

と宣言されています。%は自動的にfreeされるヒープのことです。値の生成はstring("aaa")などとします。そのままchar*型を引数にとる関数に渡せます。


```
    string str = string("ABC");

    if(strcmp(str, "ABC") == 0) {
        puts("equals");
    }
    else {
        puts("not equals");
    }
```

可変長の文字列でないため、そのヒープ自体の伸長などはできません。その場合はbufferクラスを使ってください。

フォーマット文字列を使いたい場合は以下を使います。

```
string xsprintf(char* str, ...);
```

例

```
    string str = string("ABC");
    string str2 = string("DEF");
    int n = 1;
    string str3 = xsprintf("%s+%s+%d", str, str2, n);
```

メソッドには以下があります。

```
inline bool string::equals(string& left, string& right);
inline int string::get_hash_key(string& value);
inline string string::to_string(string& value);
inline int string::compare(string& left, string& right);
inline int string::length(string& str);
inline wstring string::to_wstring(string& value);
inline string string::reverse(string& str);
inline string string::substring(string& str, int head, int tail);
inline int string::index(string& str, char* search_str, int default_value);
inline int string::rindex(string& str, char* search_str, int default_value);
inline string& string::delete(string& str, int position);
inline string& string::delete_range(string& str, int head, int tail);
inline string string::printable(string& str);
inline buffer*% string::to_buffer(string& self);
inline list!<string>*% string::split_char(string& self, char c);
inline char string::item(string& self, int index, char default_value);
inline string& string::replace(string& self, int index, char c);
```

regexを扱うメソッドには以下があります。

```
inline int string::index_regex(string& self, nregex reg, int default_value);
inline int string::rindex_regex(string& self, nregex reg, int default_value);
inline string string::sub(string& self, nregex reg, char* replace, list!<string>* group_strings);
inline bool string::match(string& self, nregex reg, list!<string>* group_strings);
inline list!<string>*% string::scan(string& self, nregex reg);
inline list!<string>*% string::split(string& self, nregex reg);
inline nregex string::to_regex(string& self);
```

nregexはREGEX(".+", false)などと生成します。第二引数はglobalのon/offのフラグです。

* list

listは双方向リストです。コレクションの主力となるクラスです。vectorと違いランダムアクセス（indexによる要素の取り出し）遅いですが、挿入や連結などが速いです。vectorはランダムアクセスは最速ですが他の場合はlistを使っておけばいいでしょう。

以下のように使います。

```
    list!<string>*% li = new list!<string>.initialize();

    li.push_back(string("AAA"));
    li.push_back(string("BBB"));
    li.push_back(string("CCC"));

    li.each (
        void lambda(string& it, int it2, bool* it3) {
            puts(it);
        }
    );
```

生成されたstringはliがfreeされる場合に自動的にfreeされます。lambdaのitは"AAA"や"BBB"や"CCC"が入ってます。lambdaのit2はループの回数、it3はループから脱出する場合*it3 = true; returnとして脱出できます。(breakのようなもの)

```
list!<T>*% list!<T>::initialize(list!<T>*% self);
void list!<T>::finalize(list!<T>* self);

void list!<T>::reset(list!<T>* self);
void list!<T>::push_back(list!<T>* self, T item);
T& list!<T>::item(list!<T>* self, int position, T& default_value);
T list!<T>::pop_back(list!<T>* self, T& default_value);
list!<T>*% list!<T>::clone(list!<T>* self);
void list!<T>::insert(list!<T>* self, int position, T item);
void list!<T>::delete(list!<T>* self, int position);
void list!<T>::delete_range(list!<T>* self, int head, int tail);
T list!<T>::pop_front(list!<T>* self, T& default_value);
void list!<T>::replace(list!<T>* self, int position, T item);
void list!<T>::each(list!<T>* self, void (*block_)(T&,int,bool*));
list!<T>*% list!<T>::sublist(list!<T>* self, int begin, int tail);
int list!<T>::length(list!<T>* self);
list!<T>*% list!<T>::reverse(list!<T>* self);
string list!<T>::join(list!<string>* self, char* separator);
list!<T>*% list!<T>::merge_list(list!<T>* left, list!<T>* right);
list!<T>*% list!<T>::merge_sort(list!<T>* self);
list!<T>*% list!<T>::sort(list!<T>* self);
template !<R> list!<R>*% list!<T>::map(list!<T>* self, R (*block_)(T&));
list!<T>*% list!<T>::uniq(list!<T>* self);
int list!<T>::find(list!<T>* self, T& item, int default_value);
bool list!<T>::equals(list!<T>* left, list!<T>* right);
list!<T>*% list!<T>::filter(list!<T>* self, bool (*block_)(T&));
```

T&はTにもし、%があり自動freeの対象になる場合は&をつけることによって、%を外します。つまりTがヒープの場合もC++でいうmoveが起こらず所有権は渡されません。push_backの場合Tとitemの引数がTとなっているため、所有権の移動が起こり自動freeの対象となります。

要素のアクセスにはitemを使います。itemなどのpostionは-1が末尾を示します。

```
    list!<char*>*% li = list!<char*>.initialize();
    
    li.push_back("AAA");
    li.push_back("BBB");
    li.push_back("CCC");

    if(strcmp(li.item(-1, null), "CCC") == 0) {
        puts("true");
    }
    else {
        puts("false");
    }
```

itemのnullの部分はデフォルト値で、positionが範囲外なら、nullを返します。

findで分かりやすいでしょう。

```
    list!<char*>*% li = list!<char*>.initialize();
    
    li.push_back("AAA");
    li.push_back("BBB");
    li.push_back("CCC");

    if(li.find("DDD", null) != null) {
        puts("found");
    }
    else {
        puts("not found");
    }

    list!<int>*% li2 = list!<int>.initialize();
    
    li2.push_back(1);
    li2.push_back(2);
    li2.push_back(3);

    if(li2.find(5, -1) != -1) {
        puts("found");
    }
    else {
        puts("not found");
    }
```

sublistの範囲は第二引数のインデックスは含みません。

```
    list!<char*>*% li = list!<char*>.initialize();
    
    li.push_back("AAA");
    li.push_back("BBB");
    li.push_back("CCC");
    li.push_back("DDD");

    li.sublist(0,2).each (
        void lambda(char* it, int it2, bool* it3) {
            puts(it);
        }
    );
```
は"AAA"と"BBB"のみ出力されます。

sublistのインデックスが<0なら末尾から数えたインデックスを示します。

```
    list!<char*>*% li = list!<char*>.initialize();
    
    li.push_back("AAA");
    li.push_back("BBB");
    li.push_back("CCC");
    li.push_back("DDD");

    li.sublist(2,-1).each (
        void lambda(char* it, int it2, bool* it3) {
            puts(it);
        }
    );
```

は"CCC"と"DDD"のみ出力されます。

mapは型推論を行いません。

```
    list!<string>*% li = new list!<string>.initialize();

    li.push_back(string("1"));
    li.push_back(string("2"));
    li.push_back(string("3"));

    list!<int>*% li13 = li99.map(
        int lambda(string& item) { return atoi(item); }
    );

    printf("li13 %d\n", li13.length());

    li13.each(void lambda(int it, int it2, bool* it3) {
        printf("it %d it2 %d\n", it, it2);
    });
```

* vector

```
vector!<T>*% vector!<T>::initialize(vector!<T>*% self);
void vector!<T>::finalize(vector!<T>* self);

void vector!<T>::push_back(vector!<T>* self, T item);
T& vector!<T>::item(vector!<T>* self, int index, T& default_value);
vector!<T>*% vector!<T>::clone(vector!<T>* self);
int vector!<T>::length(vector!<T>* self);
void vector!<T>::each(vector!<T>* self, void (*block_)(T&,int,bool*));
int vector!<T>::find(vector!<T>* self, T& item, int default_value);
T vector!<T>::pop_back(vector!<T>* self, T& default_value);
template !<R> vector!<R>*% vector!<T>::map(vector!<T>* self, R (*block_)(T&));
bool vector!<T>::equals(vector!<T>* left, vector!<T>* right);
bool vector!<T>::replace(vector!<T>* self, int index, T value);
list!<T>*% vector!<T>::to_list(vector!<T>* self);
vector!<T>*% list!<T>::to_vector(list!<T>* self);
```

サンプル。

```
    vector!<int>*% v = vector!<int>.initialize();

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    vector!<int>*% v2 = vector!<int>.initialize();

    v2.push_back(1);
    v2.push_back(2);
    v2.push_back(3);

    xassert("vector test", v.equals(v2));

    v.each (
        void lambda(int it, int it2, bool* it3) {
            printf("index %d item %d\n", it2, it);
        }
    );

    xassert("vector test2", v.item(0, -1) == 1);
```

eachのit2にはインデックスが入っています。

vectorのitemはlistより高速でO(1)でアクセスできます。

* map

```
map!<T,T2>*% map!<T,T2>::initialize(map!<T,T2>*% self);
void map!<T,T2>::finalize(map!<T,T2>* self);
void map!<T,T2>::each(map!<T, T2>* self, void (*block_)(T&,T2&,bool*));
map!<T, T2>*% map!<T,T2>::clone(map!<T, T2>* self);
void map!<T,T2>::rehash(map!<T,T2>* self);
bool map!<T,T2>::find(map!<T, T2>* self, T& key);
T2& map!<T,T2>::at(map!<T, T2>* self, T& key, T2& default_value);
void map!<T,T2>::insert(map!<T,T2>* self, T key, T2 item);
bool map!<T,T2>::equals(map!<T, T2>* left, map!<T, T2>* right);
int map!<T,T2>::length(map!<T, T2>* self);
```

mapはシンプルです。insertで値を格納して、atでアクセスできます。

```
    map!<char*,int>*% m1 = new map!<char*, int>.initialize();

    m1.insert("AAA", 1);
    m2.insert("BBB", 2);
    m3.insert("CCC", 3);

    if(m1.at("AAA", -1) == 1) {
        puts("found");
    }

    if(m1.at("DDD", -1) == -1) {
        puts("not found");
    }
```

insertは型引数がstringなどであった場合insertは所有権の移動が起こります。自動的にfreeされます。

* tuple

```
struct tuple1!<T>
{
    T v1;
};

bool tuple1!<T>::equals(tuple1!<T>* left, tuple1!<T>* right)
{
    if(!left.v1.equals(right.v1)) {
        return false;
    }

    return true;
}

struct tuple2!<T, T2>
{
    T v1;
    T2 v2;
};

bool tuple2!<T,T2>::equals(tuple2!<T, T2>* left, tuple2!<T, T2>* right)
{
    if(!left.v1.equals(right.v1)) {
        return false;
    }
    if(!left.v2.equals(right.v2)) {
        return false;
    }

    return true;
}

struct tuple3!<T, T2, T3>
{
    T v1;
    T2 v2;
    T3 v3;
};

bool tuple3!<T,T2,T3>::equals(tuple3!<T, T2, T3>* left, tuple3!<T, T2, T3>* right)
{
    if(!left.v1.equals(right.v1)) {
        return false;
    }
    if(!left.v2.equals(right.v2)) {
        return false;
    }
    if(!left.v3.equals(right.v3)) {
        return false;
    }

    return true;
}

struct tuple4!<T, T2, T3, T4>
{
    T v1;
    T2 v2;
    T3 v3;
    T4 v4;
};

bool tuple4!<T,T2,T3,T4>::equals(tuple4!<T, T2, T3, T4>* left, tuple4!<T, T2, T3, T4>* right)
{
    if(!left.v1.equals(right.v1)) {
        return false;
    }
    if(!left.v2.equals(right.v2)) {
        return false;
    }
    if(!left.v3.equals(right.v3)) {
        return false;
    }
    if(!left.v4.equals(right.v4)) {
        return false;
    }

    return true;
}

```

tupleの定義です。tupleはフィールドに直接アクセスします。tupleはtuple4までしかないので、4つまでしか作れません。また気が向けば、10くらいまでは定義してもいいですよ。

使い方は

```
    tuple3!<int, string, char*>*% t1 = new tuple3!<int, string, char*>.initialize();

    t1.v1 = 123;
    t1.v2 = string("ABC");
    t1.v3 = "DEF";
```

などです。

* buffer

可変長の文字列です。

```
struct buffer {
    char* buf;
    int len;
    int size;
};

inline buffer*% buffer::initialize(buffer*% self);
inline void buffer::finalize(buffer* self);
inline int buffer::length(buffer* self);
inline void buffer::append(buffer* self, char* mem, size_t size);
inline void buffer::append_char(buffer* self, char c);
inline void buffer::append_str(buffer* self, char* str);
inline void buffer::append_nullterminated_str(buffer* self, char* str);
inline string buffer::to_string(buffer* self);

```

定義はこれです。可変長の文字列っていうか、メモリーです。一応null-terminatedさていますが、バイナリも格納できるはずです。

```
    buffer*% buf = new buffer.initialize();
    
    buf.append_str("AAA,");
    buf.append_str("BBB,");
    buf.append_str("CCC");

    buf.to_string().split(REGEX(",", false)).each (
        void lambda(string& it, int it2, bool* it3) {
            puts(it);
        }
    );
```

AAA\nBBB\nCCC\nが出力されます。

* ヒープシステム

Rustとは違います。もう少し楽に扱えて強力かもしれませんが、かなり危険なシステムとなっております。基本的に最初のころはsegmentation faultが起こるでしょう。デバッグ方法としてはprintfデバッグや、コメントアウトデバッグがあります。printfデバッグがかなり有効です。この時デバッグ方法としては関数の途中であっても行頭にprintf(...などとしてデバッグしてデバッグが終わったらegrep ^p *.ncなどとしてデバッグコードの位置を検出して消してしまう方法がいいと思います。Cやその他フリーインデントの言語でもよく使う方法です。動的メモリーのデバッグ方法としてはvalgrindも有効です。不正なメモリアクセスすべてを検出できます。

と、ちょっと気分が萎えたと思いますが、ヒープについて書いています。

オブジェクトの生成はnewによって行います。

```
    char*% a = new char[128];
```

この場合C言語だとfree(a)としないといけませんが、neo-cはaは変数の寿命が消える時点でfreeされます。変数に代入された場合は所有権の移動がされます。

```
    char*% a = new char[128];

    char*% b = a;

    /// aはアクセスできない変数
```

所有権を移動させたくない場合は以下のようにします。

```
    char*% a = new char[128];

    strncpy(a, "ABC", 128);

    char* b = a;

    puts(a);
    puts(b);
```

%をつけない場合所有権は移動されません。つまり左辺値と右辺値の型両方に%がついていないと所有権は移動されないということです。

右辺値で生成されたヒープは自動的にfreeされます。

```
    void fun(char* str) 
    {
        puts(str);
    }

    int main() {
        fun(string("AAA"));
    }
```

string("AAA")でchar*%が生成されますが、funにはchar*と%がついていないため、string("AAA")で生成されたメモリーは自動的にfreeされます。つまり一時的に生成されたオブジェクトはすべてfreeされます。以下のようなことが可能です。

```
    list!<char*>*% li = new list!<char*>.initialize();

    li.push_back("AAA");
    li.push_back("BBB");
    li.push_back("CCC");

    li.sublist(0,1).each (
        void lambda(char* it, int it2, bool* it3) {
            puts(it);
        }
    );
```

li.sublist(0,1)では内部でlist<char>*%が生成されていますがeachの第一引数は%がないため、eachが実行された後にfreeされます。

構造体にもフィールドに%をつければ、再帰的にfreeされます。

```
    struct MyStruct {
        string field1;
        list!<string>*% field2;
    };

    int main() {
        MyStruct*% a = new MyStruct;

        a.field1 = string("AAA");
        a.field2 = new list!<string>.initialize();

        a.field2.push_back(string("AAA"));
        a.field2.push_back(string("BBB"));

        return 0;
    }
```

この場合もすべてのオブジェクトがfreeされます。newの後にinitializeがつけた場合はコンストラクタを呼び出す場合です。以下のようにコンストラクタを定義します。

```
struct MyStruct {
    string field1;
    list!<string>*% field2;
};

MyStruct*% MyStruct::initialize(MyStruct*% self) {
    self.field1 = string("AAA");
    self.field2 = new list!<string>.initialize();

    self.field2.push_back(string("AAA"));
    self.field2.push_back(string("BBB"));

    return self;
}

int main() {
    MyStruct*% a = new MyStruct.initialize();

    return 0;
}
```

オブジェクトはcloneによってディープコピーできます。

```
struct MyStruct {
    string field1;
    list!<string>*% field2;
};

MyStruct*% MyStruct::initialize(MyStruct*% self) {
    self.field1 = string("AAA");
    self.field2 = new list!<string>.initialize();

    self.field2.push_back(string("AAA"));
    self.field2.push_back(string("BBB"));

    return self;
}

int main() {
    MyStruct*% a = new MyStruct.initialize();

    MyStruct*% b = clone a;

    return 0;
}
```

この場合aとbのfield1, field2の値は同じです。浅いコピーではないため単にアドレスのコピーではなくアドレスが違いますが内容が同じです。

メソッドの定義は以下のようにします。

```
struct MyStruct {
    string field1;
    list!<string>*% field2;
};

MyStruct*% MyStruct::initialize(MyStruct*% self) {
    self.field1 = string("AAA");
    self.field2 = new list!<string>.initialize();

    self.field2.push_back(string("AAA"));
    self.field2.push_back(string("BBB"));

    return self;
}

void MyStruct::show(MyStruct* self) {
    puts(self.field1);

    self.field2.each (
        void lambda(string& it, int it2, bool* it3) {
            puts(it);
        }
    );
}

int main() {
    var a = new MyStruct.initialize();

    a.show();

    return 0;
}
```

第一引数のselfは省略できません。ついでにファイナライザの定義も説明しておきましょう。

```
struct MyStruct {
    string field1;
    list!<string>*% field2;
};

MyStruct*% MyStruct::initialize(MyStruct*% self) {
    self.field1 = string("AAA");
    self.field2 = new list!<string>.initialize();

    self.field2.push_back(string("AAA"));
    self.field2.push_back(string("BBB"));

    return self;
}

void MyStruct::finalize(MyStruct* self) {
    puts("MyStruct was freed");
}

void MyStruct::show(MyStruct* self) {
    puts(self.field1);

    self.field2.each (
        void lambda(string& it, int it2, bool* it3) {
            puts(it);
        }
    );
}

int main() {
    MyStruct*% a = new MyStruct.initialize();

    a.show();

    return 0;
}
```

aが範囲外になるときメッセージが表示されます。構造体のフィールドのfreeが自動的にされるのにファイナライザがあるのはなぜかですが、オブジェクトのヒープをクラス側で管理したいときのためにあります。以下のようにです。

```
struct MyStruct {
    char* field1;
    list!<string>* field2;
};

MyStruct*% MyStruct::initialize(MyStruct*% self) {
    self.field1 = borrow string("AAA");
    self.field2 = borrow new list<string>.initialize();

    self.field2.push_back(string("AAA"));
    self.field2.push_back(string("BBB"));

    return self;
}

void MyStruct::finalize(MyStruct* self) {
    delete self.field1;
    delete self.field2;
}

int main() {
    MySturct*% a = new MyStruct.initialize();

    return 0;
}
```

こうするとオブジェクトのヒープの管理がクラス側でできます。borrowはヒープのマークを消すために使用します。borrowをつけないとstring("AAA")の時点で左辺値に%がついていないためstring("AAA")が不要なオブジェクトと判断されて、その時点でfreeされてしまうためです。クラス側でヒープの管理を行う場合cloneも定義しないとダメとなります。以下のようにです。

```
struct MyStruct {
    char* field1;
    list!<string>* field2;
};

MyStruct*% MyStruct::initialize(MyStruct*% self) {
    self.field1 = borrow string("AAA");
    self.field2 = borrow new list<string>.initialize();

    self.field2.push_back(string("AAA"));
    self.field2.push_back(string("BBB"));

    return self;
}

void MyStruct::finalize(MyStruct* self) {
    delete self.field1;
    delete self.field2;
}

MyStruct%* MyStruct::clone(MyStruct* self) {
    MyStruct*% result = new MyStruct;

    result.field1 = borrow clone self.field1;
    result.field2 = borrow clone self.field2;

    return result;
}

int main() {
    MyStruct*% a = new MyStruct.initialize();

    MyStruct*% b = clone a;

    return 0;
}
```

ちょっと気分が落ちましたか？まあ、たいていの場合はfinalizeやcloneは定義せずに済むはずです。%のマークをフィールドにつけておきましょう。

あとborrowとは逆に存在しているヒープを指し示す%がついたポインタにヒープのマークをつけるにはdummy_heapを使います。

```
vector!<string>*% fun(string str, bool flag) {
    vector!<string>* result = borrow new vector!<string>.initialize();

    if(flag) {
        result.push_back(str);
    }
    else {
        puts(str);
    }

    return dummy_heap result;
}
```

Genericsで%がついた型とそうでない型を使う場合に必要となるかもしれません。GenericsとヒープシステムですがGenericsでヒープの所有権を移動させたくない場合はT&などとします。

```
struct MyStruct<T> {
    char*% field1;
    list!<T>%* field2;
};

MyStruct!<T>*% MyStruct!<T>::initialize(MyStruct!<T>*% self) {
    self.field1 = borrow string("AAA");
    self.field2 = borrow new list<T>.initialize();

    return self;
}

T& MyStruct!<T>::getField2Element(MyStruct!<T>* self) {
    return self.field2.item(1, null);
}

int main() {
    MyStruct!<string>*% a = new MyStruct!<string>.initialize();

    a.field2.push_back(string("AAA"));
    a.field2.push_back(string("BBB"));
    a.field2.push_back(string("CCC"));

    puts(a.getField2Element());

    return 0;
}
```

この場合getField2Eelementの戻り値はstring(char*%)ではなくchar*のため所有権の移動は起こりません。GenericsでTがヒープの型か、そうでないかを判定したい場合isheap(T)を使います。例えばvecotrの初期値を持った要素をnを作るinitializeは以下のように定義されてます。
```
    vector!<T>*% vector!<T>::initialize_with_values(vector!<T>*% self, int len, T& value) 
    {
        self.size = len;
        self.len = len;
        self.items = borrow new T[self.size];

        for(int i=0; i<len; i++) {
            if(isheap(T)) {
                self.items[i] = borrow clone value;
            }
            else {
                self.items[i] = value;
            }
        }

        return self;
    }
```

new vector<int>.initialize_with_values(5, 128)とすれば128の要素を5個持つvectorが作られますが、isheap(T)でTがヒープのオブジェクトの場合は、borrowしてcloneしてself.items[i]に代入して(self.itemsはクラス側で管理されるオブジェクト)そうでない場合は普通に代入してます。

* mixin-layersシステム

mixin-layersは要するにメソッドの上書きを認めるシステムです。上手に使うと小さな完成したアプリケーションにレイヤーを重ねるようにして、機能追加していけます。例えばデバッグするときなどに有効で、レイヤーを巻き戻してもアプリは完成形であるため、どのレイヤーでバグが起こったか、レイヤーを巻き戻してデバッグしたりすることができます。

以下が例です。

ヘッダーがcommon.hとすると

```
    struct MyStruct {
        string field1;
        string field2;
    };

    void MyStruct::show(MyStruct* self);

    inherit void MyStruct::show(MyStruct* self);
```

となりレイヤー1のソース側が01base.ncは

```
    #include "common.h"

    void MyStruct::show(MyStruct* self) {
        puts(self.field1);
    }
```

二つ目のレイヤーが02extend.nc

```
    #include "common.h"

    void MyStruct::show(MyStruct* self) {
        self.inherit();

        puts(self.field2);
    }
```

となります。inheritは上書きされる対象の関数を呼び出します。

main関数を含むmain.ncは以下のように定義すればいいでしょう。

```
    #include "common.h"

    int main()
    {
        MyStruct*% data = new MyStruct;

        data.show();

        return 0;
    }
```

まあ、あまりありがたみはありませんが。 neo-c1と違って、構造体へのフィールドの追加は認めていません。構造体はまとめて定義してください。関数だけ、レイヤーを重ねられます。またneo-c1と違って、GenericsやMethodGenericsの関数の上書きも多分動くはずです。一応テストしましたが。

* inline関数

neo-c2はinline展開しません。単なるstaticな関数です。申し訳ないですが手抜きさせてもらいました。コードの生成量は増えますが、特に問題ないはずです。

