inline void xassert(char* msg, bool exp) 
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

inline char*% xsprintf(char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    char* tmp;
    int len = vasprintf(&tmp, msg, args);
    va_end(args);

    return dummy_heap tmp;
}

inline char* ncstrncpy(char* des, char* src, int size)
{
    char* result;

    result = strncpy(des, src, size-1);
    des[size-1] = 0;

    return result;
}

inline void*% ncmalloc(long long size)
{
    void* result = malloc(size);

    if(result == NULL) {
        fprintf(stderr, "can't get heap memory. size %d. ncmalloc\n", size);
        exit(2);
    }

    return dummy_heap result;
}

inline void*% nccalloc(long long num, long long nsize)
{
    void* result = calloc(num, nsize);

    if(result == NULL) {
        fprintf(stderr, "can't get heap memory. nccalloc num %d nsize %d\n", num, nsize);

        exit(2);
    }

    memset(result, 0, num*nsize);

    return dummy_heap result;
}

inline void*% ncrealloc(void *block, long long int size)
{
#ifdef __DARWIN__
    void* result = calloc(1, size);
    memcpy(result, block, size);
    free(block);

    if(result == NULL) {
        fprintf(stderr, "can't get heap memory. realloc size %d. realloc memory %p\n", size, block);
        exit(2);
    }

    return dummy_heap result;
#else
    void* result = realloc(block, size);

    if(result == NULL) {
        fprintf(stderr, "can't get heap memory. realloc size %d. realloc memory %p\n", size, block);
        exit(2);
    }

    return dummy_heap result;
#endif
}

inline long long ncmalloc_usable_size(void* block)
{
#ifdef __DARWIN__
    return malloc_size(block);
#else
    return malloc_usable_size(block);
#endif
}

inline void*% ncmemdup(void*% block)
{
#ifdef __DARWIN__
    long long size = malloc_size(block);
#else
    long long size = malloc_usable_size(block);
#endif

    if (!block) return (void*)0;

    void*% ret = ncmalloc(size);

    if (ret) {
        char* p = ret;
        char* p2 = block;
        while(p - ret < size) {
            *p = *p2;
            p++;
            p2++;
        }
    }

    return ret;
}

typedef char*% string;
typedef wchar_t*% wstring;

inline string string(char* str)
{
    int len = strlen(str);

    string result = new char[len + 1];

    strcpy(result, str);

    return result;
}

/*
inline string xbasename(char* path)
{
    char* p = path + strlen(path);
    
    while(p >= path) {
        if(*p == '/') {
            break;
        }
        else {
            p--;
        }
    }
    
    if(p < path) {
        return string(path);
    }
    else {
        return string(p+1);  
    }
}

inline string xrealpath(char* path)
{
    char* result = realpath(path, null);

    string result2 = string(result);

    free(result);

    return result2;
}


inline void p(char* str)
{
    puts(str);
}

//////////////////////////////
/// int
//////////////////////////////
inline bool int::equals(int left, int right) 
{
    return left == right;
}

inline int int::get_hash_key(int value)
{
    return value;
}

inline string int::to_string(int value) {
    return xsprintf("%c", value);
}

inline int int::compare(int left, int right) {
    if(left < right) {
        return -1;
    }
    else if(left > right) {
        return 1;
    }
    else {
        return 0;
    }
}

//////////////////////////////
/// char
//////////////////////////////
inline bool char::equals(char left, char right)
{
    return left == right;
}

inline int char::get_hash_key(char value)
{
    return value;
}

inline string char::to_string(char value) {
    return xsprintf("%c", value);
}

inline int char::compare(char left, char right) {
    if(left < right) {
        return -1;
    }
    else if(left > right) {
        return 1;
    }
    else {
        return 0;
    }
}

//////////////////////////////
/// char* 
//////////////////////////////

inline bool char*::equals(char* left, char* right)
{
    return strcmp(left, right) == 0;
}

inline int char*::length(char* str)
{
    return strlen(str);
}

inline int char*::get_hash_key(char* value)
{
    int result = 0;
    char* p = value;
    while(*p) {
        result += (*p);
        p++;
    }
    return result;
}

inline string char*::to_string(char* value) 
{
    return string(value);
}

inline int char*::compare(char* left, char* right) 
{
    return strcmp(left, right);
}

inine wstring char*::to_wstring(char* value) 
{
    return wstring(value);
}

/*
/// int ///
impl int
{
    inline bool equals(int left, int right) 
    {
        return left == right;
    }

    inline int get_hash_key(int value)
    {
        return value;
    }

    inline string to_string(int value) {
        return xasprintf("%c", value);
    }

    inline int compare(int left, int right) {
        if(left < right) {
            return -1;
        }
        else if(left > right) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

/*
/// wchar_t ///
extern wstring operator+(wchar_t* left, wchar_t* right);
extern wstring operator*(wchar_t* left, int num);

impl wchar_t
{
    inline bool equals(wchar_t left, wchar_t right)
    {
        return left == right;
    }

    inline int get_hash_key(wchar_t value)
    {
        return value;
    }

    inline string to_string(wchar_t value) {
        return xasprintf("%lc", value);
    }

    inline int compare(wchar_t left, wchar_t right) {
        if(left < right) {
            return -1;
        }
        else if(left > right) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

impl wchar_t*
{
    inline bool equals(wchar_t* left, wchar_t* right)
    {
        return wcscmp(left, right) == 0;
    }

    inline int length(wchar_t* str)
    {
        return wcslen(str);
    }

    inline int get_hash_key(wchar_t* value)
    {
        int result = 0;
        wchar_t* p = value;
        while(*p) {
            result += (*p);
            p++;
        }
        return result;
    }

    inline string to_string(wchar_t* str, char* default_value) {
        return string_from_wchar_t(str, default_value);
    }

    inline wstring to_wstring(wchar_t* str) {
        return wstring_from_wchar_t(str);
    }

    inline int compare(wstring& left, wstring& right) {
        return wcscmp(left, right);
    }
}

/// buffer ///
struct buffer {
    char* buf;
    int len;
    int size;
};

impl buffer 
{
    initialize();
    finalize();

    void append(buffer* self, char* mem, size_t size);
    void append_char(buffer* self, char c);
    void append_str(buffer* self, char* str);
    void append_nullterminated_str(buffer* self, char* str);
    inline void append_int(buffer* self, int value) {
        self.append((char*)&value, sizeof(int));
    }
    inline void append_long(buffer* self, long long int value) {
        self.append((char*)&value, sizeof(long long int));
    }
    inline void append_short(buffer* self, short value) {
        self.append((char*)&value, sizeof(short));
    }
    inline void alignment(buffer* self) {
        int len = self.len;
        len = (len + 3) & ~3;

        for(int i=self.len; i<len; i++) {
            self.append_char('\0');
        }
    }

    string to_string(buffer* self);

    int length(buffer* self);

    inline int compare(buffer* left, buffer* right) {
        return strcmp(left.buf, right.buf);
    }
}

/// regex ///
struct regex_struct {
    string str;
    pcre* regex;

    bool ignore_case;
    bool multiline;
    bool global;
    bool extended;
    bool dotall;
    bool anchored;
    bool dollar_endonly;
    bool ungreedy;

    int options;
};

typedef regex_struct*% nregex;

extern nregex regex(char* str, bool ignore_case, bool multiline, bool global, bool extended, bool dotall, bool anchored, bool dollar_endonly, bool ungreedy);

ruby_macro regex {
    param_line = ENV['PARAMS'];

    n = 0;

    
    if param_line[n] == "/"
      n = n + 1
    elsif param_line[n] == "\""
      n = n + 1
    end

    str = ""

    ignore_case = false;
    multiline = false;
    global = false;
    extended = false;
    dotall = false;
    anchored = false;
    dollar_endonly = false;
    ungreedy = false;

    while(n < param_line.length()) do
      c = param_line[n];
      c2 = param_line[n+1]

      if c == "\\" && c2 == "/"
          str = str + c + c2

          n = n + 2
      elsif c == "\\" && c2 == "\""
          str = str + c + c2

          n = n + 2
      elsif c == "/" || c == "\""
          n = n + 1;

          while(n < param_line.length()) do
              c = param_line[n];

              if c == "i"
                  ignore_case = true;
              elsif c == "m"
                  multiline = true;
              elsif c == "g"
                  global = true;
              elsif c == "s"
                  dotall = true;
              elsif c == "A"
                  anchoared = true;
              elsif c == "D"
                  dollar_endonly = true;
              elsif c == "U"
                  ungreedy = true;
              elsif c == "x"
                  extended = true;
              end

              n = n + 1;
          end
      else
          str = str + c
      end

      n = n + 1;
    end

    puts("regex(\"#{str}\", #{ignore_case}, #{multiline}, #{global}, #{extended}, #{dotall}, #{anchored}, #{dollar_endonly}, #{ungreedy})");
}

/// list ///
struct list_item<T>
{
    T& item;
    struct list_item<T>*? prev;
    struct list_item<T>*? next;
}

struct list<T>
{
    list_item<T>*? head;
    list_item<T>*? tail;
    int len;
}

/// string ///
extern string operator+(string& left, string& right);
extern string operator*(string& left, int num);

impl string
{
    extern bool equals(string& left, string& right);
    extern int length(string& str);
    extern int get_hash_key(string& value);
    extern string substring(string& str, int head, int tail);
    extern int index(string& str, char* search_str, int default_value);
    extern int rindex(string& str, char* search_str, int default_value);
    extern int index_regex(string& str, nregex reg, int default_value);
    extern int rindex_regex(string& str, nregex reg, int default_value);
    extern string&delete(string& str, int position);
    extern string& delete_range(string& str, int head, int tail);
    extern string printable(string& str);
    extern string sub(string& self, nregex reg, char* replace, list<string>?* group_strings);
    extern bool match(string& self, nregex reg, list<string>?* group_strings);
    list<string>*% scan(string& self, nregex reg);
    extern wstring to_wstring(string& self);
    string reverse(string& str);
    list<string>*% split_char(string& self, char c);
    list<string>*% split(string& self, nregex reg);

    inline int compare(string& left, string& right) {
        return strcmp(left, right);
    }
    
    extern void replace(string& self, int index, char c);
    extern char item(string& self, int index, char default_value);
    extern string reverse(string& self);
    
    extern nregex to_regex(string& self);
    buffer*% to_buffer(string& self);
}

/// wstring ///
extern wstring operator+(wstring& left, wstring& right);
extern wstring operator*(wstring& left, int num);

impl wstring
{
    extern bool equals(wstring& left, wstring& right);
    extern int length(wstring& str);
    extern int get_hash_key(wstring& value);
    wstring reverse(wstring& str);
    extern wstring substring(wstring& str, int head, int tail);
    extern int index(wstring& str, wchar_t* search_str, int default_value);
    extern int rindex(wstring& str, wchar_t* search_str, int default_value);
    extern wstring& delete(wstring& str, int position);
    extern wstring& delete_range(wstring& str, int head, int tail);

    extern string to_string(wstring& self, char* default_value);
    extern wstring printable(wstring& str);

    inline int compare(wstring& left, wstring& right) {
        return wcscmp(left, right);
    }
    
    extern void replace(wstring& self, int index, wchar_t c);
    extern wchar_t item(wstring& self, int index, wchar_t default_value);
}

/// vector ///
struct vector<T> 
{
    T&* items;
    int len;
    int size;
};

impl vector<T> 
{
    initialize() 
    {
        self.size = 16;
        self.len = 0;
        self.items = borrow new T[self.size];
    }
    vector<T>%* initialize_with_values(vector<T>%* self, int len, T& value) 
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

    vector<T>%* clone(vector<T>* self) {
        var result = new vector<T>.initialize();

        for(int i=0; i<self.len; i++) {
            T& it = self.items[i];
            if(isheap(T)) {
                result.push_back(clone it);
            }
            else {
                result.push_back(dummy_heap it);
            }
        }

        return result;
    }

    finalize()
    {
        if(isheap(T)) {
            for(int i=0; i<self.len; i++) 
            {
                delete self.items[i];

            }
        }
        delete self.items;
    }
    
    void push_back(vector<T>* self, T item) {
        managed item;

        if(self.len == self.size) {
            var new_size = self.size * 2;
            var items = self.items;

            self.items = borrow new T[new_size];

            int i;
            for(i=0; i<self.size; i++) {
                self.items[i] = items[i];
            }

            self.size = new_size;

            delete items;
        }

        self.items[self.len] = item;
        self.len++;
    }

    T pop_back(vector<T>* self, T& default_value)
    {
        if(self.len == 0) {
            return dummy_heap default_value;
        }

        T result = (T)self.items[self.len-1];

        self.len--;

        return result;
    }

    T& item(vector<T>* self, int index, T& default_value) 
    {
        if(index < 0) {
            index += self.len;
        }

        if(index >= 0 && index < self.len)
        {
            return self.items[index];
        }

        return default_value;
    }
    T clone_item(vector<T>* self, int index, T& default_value) 
    {
        if(index < 0) {
            index += self.len;
        }

        if(index >= 0 && index < self.len)
        {
            if(isheap(T)) {
                return clone self.items[index];
            }
            else {
                return dummy_heap self.items[index];
            }
        }

        return dummy_heap default_value;
    }
    void each(vector<T>* self, void (*block_)(T&,int,bool*)) {
        for(int i_=0; i_<self.len; i_++) {
            bool end_flag_ = false;
            block_(self.items[i_], i_, &end_flag_);
            if(end_flag_ == true) {
                break;
            }
        };
    }

    int find(vector<T>* self, T& item, int default_value) {
        int result = default_value;
        self.each {
            if(it.equals(item)) {
                result = it2;
                *it3 = true;
                return;
            }
        }

        return result;
    }

    template <R> vector<R>*% map(vector<T>* self, R (*block_)(T&))
    {
        var result_ = new vector<R>.initialize();

        for(int i_=0; i_<self.len; i_++) {
            result_.push_back(block_(self.items[i_]));
        }

        result_
    }

    bool equals(vector<T>* left, vector<T>* right)
    {
        if(left.len != right.len) {
            return false;
        }

        for(int i=0; i<left.len; i++) {
            if(!(left.items[i].equals(right.items[i])))
            {
                return false;
            }
        }

        return true;
    }

    bool replace(vector<T>* self, int index, T value) 
    {
        if(index < 0) {
            index += self.len;
        }

        if(index >= 0 && index < self.len)
        {
            if(isheap(T)) {
                delete self.items[index];
            }

            self.items[index] = value;

            return true;
        }

        return false;
    }

    int length(vector<T>* self)
    {
        return self.len;
    }

    void reset(vector<T>* self) {
        self.len = 0;
    }
    
    list<T>*% to_list(vector<T>* self) {
        var result = new vector<T>.initialize();
        
        self.each {
            if(isheap(T)) {
                result.push_back(clone it);
            }
            else {
                result.push_back(dummy_heap it);
            }
        }
        
        return result;
    }
}

ruby_macro vec {
    params = [];
    param = "";
    dquort = false;
    squort = false;
    param_line = ENV['PARAMS'];
    n = 0;
    while(n < param_line.length()) do
        c = param_line[n];
        n = n + 1;

        if (dquort || squort) && c == "\\"
            param.concat(c);
            
            c = param_line[n];
            n = n + 1;

            param.concat(c);
        elsif c == "\""
            param.concat(c);
            dquort = !dquort
        elsif c == "'"
            param.concat(c);
            squort = !squort
        elsif dquort || squort
            param.concat(c);
        elsif c == ","
            if param.length() > 0
                params.push(param); param = ""
            end
        else
            param.concat(c);
        end
    end

    if param.length() != 0
        params.push(param);
    end

    if params.length() > 0
        puts("{");
        puts("var result = new vector<typeof(#{params[0]})>.initialize();");

        params.each do |param|
            puts("result.push_back(#{param});");
        end

        puts("result");
        puts("}");
    end
}

/// list ///
impl list <T>
{
    initialize() {
        self.head = null;
        self.tail = null;
        self.len = 0;
    }

    finalize() {
        list_item<T>* it = self.head;
        while(it != null) {
            if(isheap(T)) {
                delete it.item;
            }
            var prev_it = it;
            it = it.next;
            delete prev_it;
        }
    }

    list<T>*% clone(list<T>* self) {
        var result = new list<T>.initialize();

        list_item<T>* it = self.head;
        while(it != null) {
            if(isheap(T)) {
                result.push_back(clone it.item);
            }
            else {
                result.push_back(dummy_heap it.item);
            }

            it = it.next;
        }

        return result;
    }

    void reset(list<T>* self) {
        list_item<T>* it = self.head;
        while(it != null) {
            if(isheap(T)) {
                delete it.item;
            }
            var prev_it = it;
            it = it.next;
            delete prev_it;
        }

        self.head = null;
        self.tail = null;

        self.len = 0;
    }

    void push_back(list<T>* self, T item) 
    {
        managed item;

        if(self.len == 0) {
            list_item<T>* litem = borrow new list_item<T>;
            litem.prev = null;
            litem.next = null;
            litem.item = item;
            
            self.tail = litem;
            self.head = litem;
        }
        else if(self.len == 1) {
            list_item<T>* litem = borrow new list_item<T>;

            litem.prev = self.head;
            litem.next = null;
            litem.item = item;
            
            self.tail = litem;
            self.head.next = litem;
        }
        else {
            list_item<T>* litem = borrow new list_item<T>;

            litem.prev = self.tail;
            litem.next = null;
            litem.item = item;
            
            self.tail.next = litem;
            self.tail = litem;
        }

        self.len++;
    }

    T pop_back(list<T>* self, T& default_value)
    {
        if(self.len == 0) {
            return dummy_heap default_value;
        }
        else if(self.len == 1) {
            T result = (T)self.head.item;

            delete self.head;

            self.head = null;
            self.tail = null;

            self.len--;

            if(isheap(T)) {
                return clone result;
            }
            else {
                return dummy_heap result;
            }
        }
        else if(self.len == 2) {
            T result = (T)self.tail.item;

            delete self.tail;

            self.tail = self.head;
            self.head.next = null;
            self.head.prev = null;

            self.len--;

            if(isheap(T)) {
                return clone result;
            }
            else {
                return dummy_heap result;
            }
        }
        else {
            T result = (T)self.tail.item;

            list_item<T>* it = self.tail;

            self.tail = self.tail.prev;
            self.tail.next = null;

            delete it;

            self.len--;

            if(isheap(T)) {
                return clone result;
            }
            else {
                return dummy_heap result;
            }
        }
    }
    
    T pop_front(list<T>* self, T& default_value)
    {
        if(self.len == 0) {
            return dummy_heap default_value;
        }
        else if(self.len == 1) {
            T result = (T)self.head.item;

            delete self.head;

            self.head = null;
            self.tail = null;

            self.len = 0;

            if(isheap(T)) {
                return clone result;
            }
            else {
                return dummy_heap result;
            }
        }
        else if(self.len == 2) {
            T result = (T)self.head.item;

            var head_before = self.head;

            self.head = self.head.next;
            self.head.prev = null;
            self.head.next = null;
            
            delete head_before;

            self.len--;

            if(isheap(T)) {
                return clone result;
            }
            else {
                return dummy_heap result;
            }
        }
        else {
            T result = (T)self.head.item;

            var head_before = self.head;

            self.head = self.head.next;
            self.head.prev = null;
            
            delete head_before;

            self.len--;

            if(isheap(T)) {
                return clone result;
            }
            else {
                return dummy_heap result;
            }
        }
    }

    void insert(list<T>* self, int position, T item)
    {
        if(position < 0) {
            position += self.len + 1;
        }
        if(position < 0) {
            position = 0;
        }
        if(self.len == 0 || position >= self.len) 
        {
            self.push_back(item);
            return;
        }

        managed item;

        if(position == 0) {
            list_item<T>* litem = borrow new list_item<T>;

            litem.prev = null;
            litem.next = self.head;
            litem.item = item;
            
            self.head.prev = litem;
            self.head = litem;

            self.len++;
        }
        else if(self.len == 1) {
            var litem = borrow new list_item<T>;

            litem.prev = self.head;
            litem.next = self.tail;
            litem.item = item;
            
            self.tail.prev = litem;
            self.head.next = litem;

            self.len++;
        }
        else {
            list_item<T>?* it = self.head;
            var i = 0;
            while(it != null) {
                if(position == i) {
                    list_item<T>* litem = borrow new list_item<T>;

                    litem.prev = it.prev;
                    litem.next = it;
                    litem.item = item;

                    it.prev.next = litem;
                    it.prev = litem;

                    self.len++;
                }

                it = it.next;
                i++;
            }
        }
    }

    void delete(list<T>* self, int position)
    {
        if(position < 0) {
            position += self.len + 1;
        }

        if(position >= 0 && position < self.len)
        {
            if(self.len == 1) {
                if(isheap(T)) {
                    delete self.head.item;
                }
                delete self.head;

                self.head = null;
                self.tail = null;

                self.len = 0;
            }
            else if(self.len == 2) {
                if(position == 0) {
                    list_item<T>?* it = self.head;

                    self.head = it.next;

                    self.head.prev = null;
                    self.head.next = null;

                    self.tail = self.head;

                    if(isheap(T)) {
                        delete it.item;
                    }
                    delete it;

                    self.len--;
                }
                else {
                    list_item<T>?* it = self.tail;

                    self.head.next = null;
                    self.head.prev = null;

                    self.tail = self.head;

                    if(isheap(T)) {
                        delete it.item;
                    }
                    delete it;

                    self.len--;
                }
            }
            else {
                list_item<T>?* it = self.head;
                var i = 0;
                while(it != null) {
                    if(position == i) {
                        if(i == 0) {
                            self.head = it.next;
                            self.head.prev = null;

                            if(isheap(T)) {
                                delete it.item;
                            }
                            delete it;

                            self.len--;
                        }
                        else if(i == self.len-1)
                        {
                           self.tail = it.prev;
                           self.tail.next = null;
                           if(isheap(T)) 
                           {
                                delete it.item;
                            }
                            delete it;

                            self.len--;
                        }
                        else {
                            it.prev.next = it.next;
                            it.next.prev = it.prev;
                            if(isheap(T)) {
                                delete it.item;
                            }
                            delete it;

                            self.len--;
                        }
                        break;
                    }

                    it = it.next;
                    i++;
                }
            }
        }
    }

    void delete_range(list<T>* self, int head, int tail)
    {
        if(head < 0) {
            head += self.len;
        }
        if(tail < 0) {
            tail += self.len + 1;
        }

        if(head > tail) {
            int tmp = tail;
            tail = head;
            head = tmp;
        }

        if(head < 0) {
            head = 0;
        }

        if(tail > self.len) {
            tail = self.len;
        }

        if(head == tail) {
            return;
        }

        if(head == 0 && tail == self.len) 
        {
            self.reset();
        }
        else if(head == 0) {
            list_item<T>?* it = self.head;
            var i = 0;
            while(it != null) {
                if(i < tail) {
                    if(isheap(T)) {
                        delete it.item;
                    }
                    list_item<T>?* prev_it = it;

                    it = it.next;
                    i++;

                    delete prev_it;

                    self.len--;
                }
                else if(i == tail) {
                    self.head = it;
                    self.head.prev = null;
                    break;
                }
                else {
                    it = it.next;
                    i++;
                }
            }
        }
        else if(tail == self.len) {
            list_item<T>?* it = self.head;
            var i = 0;
            while(it != null) {
                if(i == head) {
                    self.tail = it.prev;
                    self.tail.next = null;
                }

                if(i >= head) {
                    if(isheap(T)) {
                        delete it.item;
                    }
                    list_item<T>?* prev_it = it;

                    it = it.next;
                    i++;

                    delete prev_it;

                    self.len--;
                }
                else {
                    it = it.next;
                    i++;
                }
            }
        }
        else {
            list_item<T>?* it = self.head;

            list_item<T>?* head_prev_it = null;
            list_item<T>?* tail_it = null;


            var i = 0;
            while(it != null) {
                if(i == head) {
                    head_prev_it = it.prev;
                }
                if(i == tail) {
                    tail_it = it;
                }

                if(i >= head && i < tail) 
                {
                    if(isheap(T)) {
                        delete it.item;
                    }
                    list_item<T>?* prev_it = it;

                    it = it.next;
                    i++;

                    delete prev_it;

                    self.len--;
                }
                else {
                    it = it.next;
                    i++;
                }
            }

            if(head_prev_it != null) {
                head_prev_it.next = tail_it;
            }
            if(tail_it != null) {
                tail_it.prev = head_prev_it;
            }
        }
    }

    void replace(list<T>* self, int position, T item)
    {
        managed item;

        if(position < 0) {
            position += self.len;
        }

        list_item<T>?* it = self.head;
        var i = 0;
        while(it != null) {
            if(position == i) {
                if(isheap(T)) {
                    delete it.item;
                }

                it.item = item;
                break;
            }
            it = it.next;
            i++;
        };
    }
    
    T& item(list<T>* self, int position, T& default_value) 
    {
        if(position < 0) {
            position += self.len;
        }

        list_item<T>?* it = self.head;
        var i = 0;
        while(it != null) {
            if(position == i) {
                return it.item;
            }
            it = it.next;
            i++;
        };

        return default_value;
    }

    T clone_item(list<T>* self, int position, T& default_value) 
    {
        if(position < 0) {
            position += self.len;
        }

        list_item<T>?* it = self.head;
        var i = 0;
        while(it != null) {
            if(position == i) {
                if(isheap(T)) {
                    return clone it.item;
                }
                else {
                    return dummy_heap it.item;
                }
            }
            it = it.next;
            i++;
        };

        return dummy_heap default_value;
    }
    
    void each(list<T>* self, void (*block_)(T&,int,bool*)) {
        list_item<T>?* it_ = self.head;
        var i_ = 0;
        while(it_ != null) {
            bool end_flag_ = false;
            block_(it_.item, i_, &end_flag_);

            if(end_flag_ == true) {
                break;
            }
            it_ = it_.next;
            i_++;
        }
    }

    list<T>*% sublist(list<T>* self, int begin, int tail) {
        list<T>%* result = new list<T>.initialize();

        if(begin < 0) {
            begin += self.len;
        }

        if(tail < 0) {
            tail += self.len + 1;
        }

        if(begin < 0) {
            begin = 0;
        }

        if(tail >= self.len) {
            tail = self.len;
        }


        list_item<T>?* it = self.head;
        var i = 0;
        while(it != null) {
            if(i >= begin && i < tail) {
                if(isheap(T)) {
                    result.push_back(clone it.item);
                }
                else {
                    result.push_back(dummy_heap it.item);
                }
            }
            it = it.next;
            i++;
        };

        return result;
    }

    list<T>*% reverse(list<T>* self) {
        list<T>%* result = new list<T>.initialize();

        list_item<T>?* it = self.tail;
        while(it != null) {
            if(isheap(T)) {
                result.push_back(clone it.item);
            }
            else {
                result.push_back(dummy_heap it.item);
            }
            it = it.prev;
        };

        return result;
    }
    string join(list<string>* self, char* separator) {
        buffer%* buf = new buffer.initialize();

        list_item<T>?* it = self.head;
        var i = 0;
        while(it != null) {
            if(i == self.length() - 1) {
                buf.append_str(it.item);
            }
            else {
                buf.append_str(it.item);
                buf.append_str(separator);
            }

            it = it.next;
            i++;
        }

        return string(buf.buf);
    }
    list<T>*% merge_list(list<T>* left, list<T>* right) {
        var result = new list<T>.initialize();

        list_item<T>*? it = left.head;
        list_item<T>*? it2= right.head;

        while(true) {
            if(it && it2) {
                if(it.item == null) {
                    it = it.next;
                }
                else if(it2.item == null) {
                    it2 = it2.next;
                }
                else if(it.item.compare(it2.item) <= 0) 
                {
                    if(isheap(T)) {
                        result.push_back(clone it.item);
                    }
                    else {
                        result.push_back(dummy_heap it.item);
                    }

                    it = it.next;
                }
                else {
                    if(isheap(T)) {
                        result.push_back(clone it2.item);
                    }
                    else {
                        result.push_back(dummy_heap it2.item);
                    }


                    it2 = it2.next;
                }
            }

            if(it == null) {
                if(it2 != null) {
                    while(it2 != null) {
                        if(isheap(T)) {
                            result.push_back(clone it2.item);
                        }
                        else {
                            result.push_back(dummy_heap it2.item);
                        }

                        it2 = it2.next;
                    }
                }
                break;
            }
            else if(it2 == null) {
                if(it != null) {
                    while(it != null) {
                        if(isheap(T)) {
                            result.push_back(clone it.item);
                        }
                        else {
                            result.push_back(dummy_heap it.item);
                        }

                        it = it.next;
                    }
                }
                break;
            }
        }

        return result;
    }
    list<T>*% merge_sort(list<T>* self) {
        if(self.head == null) {
            return clone self;
        }
        if(self.head.next == null) {
            return clone self;
        }

        var list1 = new list<T>.initialize();
        var list2 = new list<T>.initialize();

        list_item<T>* it = self.head;

        while(true) {
            if(isheap(T)) {
                list1.push_back(clone it.item);
            }
            else {
                list1.push_back(dummy_heap it.item);
            }

            if(isheap(T)) {
                list2.push_back(clone it.next.item);
            }
            else {
                list2.push_back(dummy_heap it.next.item);
            }

            if(it.next.next == null) {
                break;
            }

            it = it.next.next;

            if(it.next == null) {
                if(isheap(T)) {
                    list1.push_back(clone it.item);
                }
                else {
                    list1.push_back(dummy_heap it.item);
                }
                break;
            }
        }

        return list1.merge_sort().merge_list( list2.merge_sort());
    }
    list<T>*% sort(list<T>* self) {
        return self.merge_sort();
    }
    list<T>*% merge_list2(list<T>* left, list<T>* right, int (*compare)(T&,T&)) {
        var result = new list<T>.initialize();

        list_item<T>*? it = left.head;
        list_item<T>*? it2= right.head;

        while(true) {
            if(it && it2) {
                if(it.item == null) {
                    it = it.next;
                }
                else if(it2.item == null) {
                    it2 = it2.next;
                }
                else if(compare(it.item, it2.item) <= 0) 
                {
                    if(isheap(T)) {
                        result.push_back(clone it.item);
                    }
                    else {
                        result.push_back(dummy_heap it.item);
                    }

                    it = it.next;
                }
                else {
                    if(isheap(T)) {
                        result.push_back(clone it2.item);
                    }
                    else {
                        result.push_back(dummy_heap it2.item);
                    }


                    it2 = it2.next;
                }
            }

            if(it == null) {
                if(it2 != null) {
                    while(it2 != null) {
                        if(isheap(T)) {
                            result.push_back(clone it2.item);
                        }
                        else {
                            result.push_back(dummy_heap it2.item);
                        }

                        it2 = it2.next;
                    }
                }
                break;
            }
            else if(it2 == null) {
                if(it != null) {
                    while(it != null) {
                        if(isheap(T)) {
                            result.push_back(clone it.item);
                        }
                        else {
                            result.push_back(dummy_heap it.item);
                        }

                        it = it.next;
                    }
                }
                break;
            }
        }

        return result;
    }
    list<T>*% merge_sort2(list<T>* self, int (*compare)(T&,T&)) {
        if(self.head == null) {
            return clone self;
        }
        if(self.head.next == null) {
            return clone self;
        }

        var list1 = new list<T>.initialize();
        var list2 = new list<T>.initialize();

        list_item<T>* it = self.head;

        while(true) {
            if(isheap(T)) {
                list1.push_back(clone it.item);
            }
            else {
                list1.push_back(dummy_heap it.item);
            }

            if(isheap(T)) {
                list2.push_back(clone it.next.item);
            }
            else {
                list2.push_back(dummy_heap it.next.item);
            }

            if(it.next.next == null) {
                break;
            }

            it = it.next.next;

            if(it.next == null) {
                if(isheap(T)) {
                    list1.push_back(clone it.item);
                }
                else {
                    list1.push_back(dummy_heap it.item);
                }
                break;
            }
        }

        return list1.merge_sort2(compare).merge_list2( list2.merge_sort2(compare), compare);
    }
    list<T>*% sort_block(list<T>* self, int (*compare)(T&,T&)) {
        return self.merge_sort2(compare);
    }

    list<T>*% uniq(list<T>* self) {
        list<T>*% result = new list<T>.initialize();

        if(self.length() > 0) {
            T& item_before = self.item(0, null);

            if(isheap(T)) {
                result.push_back(clone item_before);
            }
            else {
                result.push_back(dummy_heap item_before);
            }

            self.sublist(1,-1).each {
                if(!it.equals(item_before)) {
                    if(isheap(T)) {
                        result.push_back(clone it);
                    }
                    else {
                        result.push_back(dummy_heap it);
                    }
                }

                item_before = it;
            }
        }

        return result;
    }

    int find(list<T>* self, T& item, int default_value) {
        int result = default_value;
        self.each {
            if(it.equals(item)) {
                result = it2;
                *it3 = true;
                return;
            }
        }

        return result;
    }

    bool equals(list<T>* left, list<T>* right)
    {
        if(left.len != right.len) {
            return false;
        }

        list_item<T>?* it = left.head;
        list_item<T>?* it2 = right.head;

        while(it != null) {
            if(!it.item.equals(it2.item)) {
                return false;
            }

            it = it.next;
            it2 = it2.next;
        }

        return true;
    }

    int length(list<T>* self)
    {
        return self.len;
    }
    template <R> list<R>*% map(list<T>* self, R (*block_)(T&))
    {
        var result_ = new list<R>.initialize();

        list_item<T>?* it_ = self.head;
        while(it_ != null) {
            result_.push_back(block_(it_.item));

            it_ = it_.next;
        }

        result_
    }
    list<T>*% filter(list<T>* self, bool (*block_)(T&))
    {
        var result_ = new list<T>.initialize();

        list_item<T>?* it_ = self.head;
        while(it_ != null) {
            if(block_(it_.item)) {
                if(isheap(T)) {
                    result_.push_back(clone it_.item);
                }
                else {
                    result_.push_back(dummy_heap it_.item);
                }
            }

            it_ = it_.next;
        }

        result_
    } 
    
    vector<T> to_vector(list<T>* self) {
        var result = new list<T>.initialize();
        
        self.each {
            if(isheap(T)) {
                result.push_back(clone it);
            }
            else {
                result.push_back(dummy_heap it);
            }
        }
        
        return result;
    }
}

ruby_macro list {
    params = [];
    param = "";
    dquort = false;
    squort = false;
    param_line = ENV['PARAMS'];
    n = 0;
    while(n < param_line.length()) do
        c = param_line[n];
        n = n + 1;

        if (dquort || squort) && c == "\\"
            param.concat(c);
            
            c = param_line[n];
            n = n + 1;

            param.concat(c);
        elsif c == "\""
            param.concat(c);
            dquort = !dquort
        elsif c == "'"
            param.concat(c);
            squort = !squort
        elsif dquort || squort
            param.concat(c);
        elsif c == ","
            if param.length() > 0
                params.push(param); param = ""
            end
        else
            param.concat(c);
        end
    end

    if param.length() != 0
        params.push(param);
    end

    if params.length() > 0
        puts("{");
        puts("var result = new list<typeof(#{params[0]})>.initialize();");

        params.each do |param|
            puts("result.push_back(#{param});");
        end

        puts("result");
        puts("}");
    end
}


struct tuple1<T>
{
    T v1;
}

impl tuple1 <T>
{
    initialize() {
    }

    bool equals(tuple1<T>* left, tuple1<T>* right)
    {
        if(!left.v1.equals(right.v1)) {
            return false;
        }

        return true;
    }
}

struct tuple2<T, T2>
{
    T v1;
    T2 v2;
}

impl tuple2 <T, T2>
{
    initialize() {
    }

    bool equals(tuple2<T, T2>* left, tuple2<T, T2>* right)
    {
        if(!left.v1.equals(right.v1)) {
            return false;
        }
        if(!left.v2.equals(right.v2)) {
            return false;
        }

        return true;
    }
}

struct tuple3<T, T2, T3>
{
    T v1;
    T2 v2;
    T3 v3;
}

impl tuple3 <T, T2, T3>
{
    initialize() {
    }

    bool equals(tuple3<T, T2, T3>* left, tuple3<T, T2, T3>* right)
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
}

struct tuple4<T, T2, T3, T4>
{
    T v1;
    T2 v2;
    T3 v3;
    T4 v3;
}

impl tuple4 <T, T2, T3, T4>
{
    initialize() {
    }

    bool equals(tuple4<T, T2, T3, T4>* left, tuple4<T, T2, T3, T4>* right)
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
}

ruby_macro tuple {
    params = [];
    param = "";
    dquort = false;
    squort = false;
    param_line = ENV['PARAMS'];
    n = 0;
    while(n < param_line.length()) do
        c = param_line[n];
        n = n + 1;

        if (dquort || squort) && c == "\\"
            param.concat(c);
            
            c = param_line[n];
            n = n + 1;

            param.concat(c);
        elsif c == "\""
            param.concat(c);
            dquort = !dquort
        elsif c == "'"
            param.concat(c);
            squort = !squort
        elsif dquort || squort
            param.concat(c);
        elsif c == ","
            if param.length() > 0
                params.push(param); param = ""
            end
        else
            param.concat(c);
        end
    end

    if param.length() != 0
        params.push(param);
    end

    if params.length() == 1
    then
        puts("{");
        puts("var result = new tuple1<typeof(#{params[0]})>;");

        puts("result.v1 = #{params[0]};");

        puts("result");
        puts("}");
    end

    if params.length() == 2 
    then
        puts("{");
        puts("var result = new tuple2<typeof(#{params[0]}),typeof(#{params[1]})>;");

        puts("result.v1 = #{params[0]};");
        puts("result.v2 = #{params[1]};");

        puts("result");
        puts("}");
    end

    if params.length() == 3
    then
        puts("{");
        puts("var result = new tuple3<typeof(#{params[0]}),typeof(#{params[1]}),typeof(#{params[2]})>;");

        puts("result.v1 = #{params[0]};");
        puts("result.v2 = #{params[1]};");
        puts("result.v3 = #{params[2]};");

        puts("result");
        puts("}");
    end

    if params.length() == 4
    then
        puts("{");
        puts("var result = new tuple4<typeof(#{params[0]}),typeof(#{params[1]}),typeof(#{params[2]}),typeof(#{params[3]})>;");

        puts("result.v1 = #{params[0]};");
        puts("result.v2 = #{params[1]};");
        puts("result.v3 = #{params[2]};");
        puts("result.v4 = #{params[3]};");

        puts("result");
        puts("}");
    end
}

struct map<T, T2>
{
    T&* keys;
    bool* item_existance;
    T2&* items;
    int size;
    int len;
}

#define MAP_TABLE_DEFAULT_SIZE 128

impl map <T, T2>
{
    initialize() {
        self.keys = borrow new T[MAP_TABLE_DEFAULT_SIZE];
        self.items = borrow new T2[MAP_TABLE_DEFAULT_SIZE];
        self.item_existance = borrow new bool[MAP_TABLE_DEFAULT_SIZE];

        for(int i=0; i<MAP_TABLE_DEFAULT_SIZE; i++)
        {
            self.item_existance[i] = false;
        }

        self.size = MAP_TABLE_DEFAULT_SIZE;
        self.len = 0;
    }

    finalize() {
        for(int i=0; i<self.size; i++) {
            if(self.item_existance[i]) {
                if(isheap(T2)) {
                    delete self.items[i];
                }
            }
        }
        delete self.items;

        for(int i=0; i<self.size; i++) {
            if(self.item_existance[i]) {
                if(isheap(T)) {
                    delete self.keys[i];
                }
            }
        }
        delete self.keys;

        delete self.item_existance;
    }

    map<T, T2>*% clone(map<T, T2>* self)
    {
        var result = new map<T,T2>.initialize();

        self.each {
            if(isheap(T)) {
                if(isheap(T2)) {
                    result.insert(clone it, clone it2);
                }
                else {
                    result.insert(clone it, dummy_heap it2);
                }
            }
            else {
                if(isheap(T2)) {
                    result.insert(dummy_heap it, clone it2);
                }
                else {
                    result.insert(dummy_heap it, dummy_heap it2);
                }
            }
        }

        return result;
    }

    void each(map<T, T2>* self, void (*block_)(T&,T2&,bool*)) 
    {
        for(int i_=0; i_<self.size; i_++) {
            if(self.item_existance[i_]) {
                bool end_flag_ = false;
                block_(self.keys[i_], self.items[i_], &end_flag_);
                if(end_flag_ == true) {
                    break;
                }
            }
        }
    }

    void rehash(map<T,T2>* self) {
        int size = self.size * 3;
        T&* keys = borrow new T[size];
        T2&* items = borrow new T2[size];
        bool* item_existance = borrow new bool[size];

        int len = 0;

        self.each {
            int hash = ((T)it).get_hash_key() % size;
            int n = hash;

            while(true) {
                if(item_existance[n])
                {
                    n++;

                    if(n >= size) {
                        n = 0;
                    }
                    else if(n == hash) {
                        fprintf(stderr, "unexpected error in map.rehash(1)\n");
                        exit(2);
                    }
                }
                else {
                    item_existance[n] = true;
                    keys[n] = it;
                    items[n] = it2;

                    len++;
                    break;
                }
            }
        }

        delete self.items;
        delete self.item_existance;
        delete self.keys;

        self.keys = keys;
        self.items = items;
        self.item_existance = item_existance;

        self.size = size;
        self.len = len;
    }

    bool find(map<T, T2>* self, T& key) {
        int hash = ((T)key).get_hash_key() % self.size;
        int it = hash;

        while(true) {
            if(self.item_existance[it])
            {
                if(self.keys[it].equals(key))
                {
                    return true;
                }

                it++;

                if(it >= self.size) {
                    it = 0;
                }
                else if(it == hash) {
                    return false;
                }
            }
            else {
                return false;
            }
        }

        return false;
    }

    T2& at(map<T, T2>* self, T& key, T2& default_value) 
    {
        int hash = ((T)key).get_hash_key() % self.size;
        int it = hash;

        while(true) {
            if(self.item_existance[it])
            {
                if(self.keys[it].equals(key))
                {
                    return self.items[it];
                }

                it++;

                if(it >= self.size) {
                    it = 0;
                }
                else if(it == hash) {
                    return default_value;
                }
            }
            else {
                return default_value;
            }
        }

        return default_value;
    }

    T2 at_clone(map<T, T2>* self, T& key, T2& default_value) 
    {
        int hash = ((T)key).get_hash_key() % self.size;
        int it = hash;

        while(true) {
            if(self.item_existance[it])
            {
                if(self.keys[it].equals(key))
                {
                    if(isheap(T)) {
                        return clone self.items[it];
                    }
                    else {
                        return dummy_heap self.items[it];
                    }
                }

                it++;

                if(it >= self.size) {
                    it = 0;
                }
                else if(it == hash) {
                    return dummy_heap default_value;
                }
            }
            else {
                return dummy_heap default_value;
            }
        }

        return dummy_heap default_value;
    }

    void insert(map<T,T2>* self, T key, T2 item) 
    {
        managed key;
        managed item;

        if(self.len*2 >= self.size) {
            self.rehash();
        }

        int hash = ((T)key).get_hash_key() % self.size;
        int it = hash;

        while(true) {
            if(self.item_existance[it])
            {
                if(self.keys[it].equals(key)) 
                {
                    if(isheap(T)) {
                        delete dummy_heap self.keys[it];
                    }
                    if(isheap(T2)) {
                        delete dummy_heap self.items[it];
                    }
                    self.keys[it] = key;
                    self.items[it] = item;

                    break;
                }

                it++;

                if(it >= self.size) {
                    it = 0;
                }
                else if(it == hash) {
                    fprintf(stderr, "unexpected error in map.insert\n");
                    exit(2);
                }
            }
            else {
                self.item_existance[it] = true;
                self.keys[it] = key;
                self.items[it] = item;

                self.len++;

                break;
            }
        }
    }

    bool equals(map<T, T2>* left, map<T, T2>* right)
    {
        if(left.len != right.len) {
            return false;
        }

        bool result = true;
        left.each {
            if(right.find(it)) {
                T2& default_value;
                T2 item = right.at(it, default_value);
                if(!it2.equals(item)) {
                    result = false;
                }
            }
            else {
                result = false;
            }
        }

        return result;
    }

    int length(map<T, T2>* self) {
        return self.len;
    }
}

ruby_macro map {
    params = [];
    param = "";
    dquort = false;
    squort = false;
    param_line = ENV['PARAMS'];
    n = 0;
    while(n < param_line.length()) do
        c = param_line[n];
        n = n + 1;

        if (dquort || squort) && c == "\\"
            param.concat(c);
            
            c = param_line[n];
            n = n + 1;

            param.concat(c);
        elsif c == "\""
            param.concat(c);
            dquort = !dquort
        elsif c == "'"
            param.concat(c);
            squort = !squort
        elsif dquort || squort
            param.concat(c);
        elsif c == ","
            if param.length() > 0
                params.push(param); param = ""
            end
        elsif c == ":"
            if param.length() > 0
                params.push(param); param = ""
            end
        else
            param.concat(c);
        end
    end

    if param.length() != 0
        params.push(param);
    end

    if params.length() >= 2
    then
        puts("{");
        puts("var result = new map<typeof(#{params[0]}), typeof(#{params[1]})>.initialize();");

        key = nil;
        for it in params do
            if key == nil
            then
                key = it;
            else
                puts("result.insert(#{key}, #{it});");
                key = nil;
            end
        end

        puts("result");
        puts("}");
    end
}




/// char* ///
extern string operator+(char* left, char* right);
extern string operator*(char* left, int num);

impl char
{
    inline bool equals(char left, char right)
    {
        return left == right;
    }

    inline int get_hash_key(char value)
    {
        return value;
    }

    inline string to_string(char value) {
        return xasprintf("%c", value);
    }

    inline int compare(char left, char right) {
        if(left < right) {
            return -1;
        }
        else if(left > right) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

impl char*
{
    inline bool equals(char* left, char* right)
    {
        return strcmp(left, right) == 0;
    }

    inline int length(char* str)
    {
        return strlen(str);
    }

    inline int get_hash_key(char* value)
    {
        int result = 0;
        char* p = value;
        while(*p) {
            result += (*p);
            p++;
        }
        return result;
    }

    inline string to_string(char* value) {
        return string(value);
    }

    inline int compare(char* left, char* right) {
        return strcmp(left, right);
    }
    
    inline wstring to_wstring(char* value) {
        return wstring(value);
    }
}

/// wchar_t ///
extern wstring operator+(wchar_t* left, wchar_t* right);
extern wstring operator*(wchar_t* left, int num);

impl wchar_t
{
    inline bool equals(wchar_t left, wchar_t right)
    {
        return left == right;
    }

    inline int get_hash_key(wchar_t value)
    {
        return value;
    }

    inline string to_string(wchar_t value) {
        return xasprintf("%lc", value);
    }

    inline int compare(wchar_t left, wchar_t right) {
        if(left < right) {
            return -1;
        }
        else if(left > right) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

impl wchar_t*
{
    inline bool equals(wchar_t* left, wchar_t* right)
    {
        return wcscmp(left, right) == 0;
    }

    inline int length(wchar_t* str)
    {
        return wcslen(str);
    }

    inline int get_hash_key(wchar_t* value)
    {
        int result = 0;
        wchar_t* p = value;
        while(*p) {
            result += (*p);
            p++;
        }
        return result;
    }

    inline string to_string(wchar_t* str, char* default_value) {
        return string_from_wchar_t(str, default_value);
    }

    inline wstring to_wstring(wchar_t* str) {
        return wstring_from_wchar_t(str);
    }

    inline int compare(wstring& left, wstring& right) {
        return wcscmp(left, right);
    }
}

/// buffer ///
struct buffer {
    char* buf;
    int len;
    int size;
};

impl buffer 
{
    initialize();
    finalize();

    void append(buffer* self, char* mem, size_t size);
    void append_char(buffer* self, char c);
    void append_str(buffer* self, char* str);
    void append_nullterminated_str(buffer* self, char* str);
    inline void append_int(buffer* self, int value) {
        self.append((char*)&value, sizeof(int));
    }
    inline void append_long(buffer* self, long long int value) {
        self.append((char*)&value, sizeof(long long int));
    }
    inline void append_short(buffer* self, short value) {
        self.append((char*)&value, sizeof(short));
    }
    inline void alignment(buffer* self) {
        int len = self.len;
        len = (len + 3) & ~3;

        for(int i=self.len; i<len; i++) {
            self.append_char('\0');
        }
    }

    string to_string(buffer* self);

    int length(buffer* self);

    inline int compare(buffer* left, buffer* right) {
        return strcmp(left.buf, right.buf);
    }
}

/// regex ///
struct regex_struct {
    string str;
    pcre* regex;

    bool ignore_case;
    bool multiline;
    bool global;
    bool extended;
    bool dotall;
    bool anchored;
    bool dollar_endonly;
    bool ungreedy;

    int options;
};

typedef regex_struct*% nregex;

extern nregex regex(char* str, bool ignore_case, bool multiline, bool global, bool extended, bool dotall, bool anchored, bool dollar_endonly, bool ungreedy);

ruby_macro regex {
    param_line = ENV['PARAMS'];

    n = 0;

    
    if param_line[n] == "/"
      n = n + 1
    elsif param_line[n] == "\""
      n = n + 1
    end

    str = ""

    ignore_case = false;
    multiline = false;
    global = false;
    extended = false;
    dotall = false;
    anchored = false;
    dollar_endonly = false;
    ungreedy = false;

    while(n < param_line.length()) do
      c = param_line[n];
      c2 = param_line[n+1]

      if c == "\\" && c2 == "/"
          str = str + c + c2

          n = n + 2
      elsif c == "\\" && c2 == "\""
          str = str + c + c2

          n = n + 2
      elsif c == "/" || c == "\""
          n = n + 1;

          while(n < param_line.length()) do
              c = param_line[n];

              if c == "i"
                  ignore_case = true;
              elsif c == "m"
                  multiline = true;
              elsif c == "g"
                  global = true;
              elsif c == "s"
                  dotall = true;
              elsif c == "A"
                  anchoared = true;
              elsif c == "D"
                  dollar_endonly = true;
              elsif c == "U"
                  ungreedy = true;
              elsif c == "x"
                  extended = true;
              end

              n = n + 1;
          end
      else
          str = str + c
      end

      n = n + 1;
    end

    puts("regex(\"#{str}\", #{ignore_case}, #{multiline}, #{global}, #{extended}, #{dotall}, #{anchored}, #{dollar_endonly}, #{ungreedy})");
}

/// list ///
struct list_item<T>
{
    T& item;
    struct list_item<T>*? prev;
    struct list_item<T>*? next;
}

struct list<T>
{
    list_item<T>*? head;
    list_item<T>*? tail;
    int len;
}

/// string ///
extern string operator+(string& left, string& right);
extern string operator*(string& left, int num);

impl string
{
    extern bool equals(string& left, string& right);
    extern int length(string& str);
    extern int get_hash_key(string& value);
    extern string substring(string& str, int head, int tail);
    extern int index(string& str, char* search_str, int default_value);
    extern int rindex(string& str, char* search_str, int default_value);
    extern int index_regex(string& str, nregex reg, int default_value);
    extern int rindex_regex(string& str, nregex reg, int default_value);
    extern string&delete(string& str, int position);
    extern string& delete_range(string& str, int head, int tail);
    extern string printable(string& str);
    extern string sub(string& self, nregex reg, char* replace, list<string>?* group_strings);
    extern bool match(string& self, nregex reg, list<string>?* group_strings);
    list<string>*% scan(string& self, nregex reg);
    extern wstring to_wstring(string& self);
    string reverse(string& str);
    list<string>*% split_char(string& self, char c);
    list<string>*% split(string& self, nregex reg);

    inline int compare(string& left, string& right) {
        return strcmp(left, right);
    }
    
    extern void replace(string& self, int index, char c);
    extern char item(string& self, int index, char default_value);
    extern string reverse(string& self);
    
    extern nregex to_regex(string& self);
    buffer*% to_buffer(string& self);
}

/// wstring ///
extern wstring operator+(wstring& left, wstring& right);
extern wstring operator*(wstring& left, int num);

impl wstring
{
    extern bool equals(wstring& left, wstring& right);
    extern int length(wstring& str);
    extern int get_hash_key(wstring& value);
    wstring reverse(wstring& str);
    extern wstring substring(wstring& str, int head, int tail);
    extern int index(wstring& str, wchar_t* search_str, int default_value);
    extern int rindex(wstring& str, wchar_t* search_str, int default_value);
    extern wstring& delete(wstring& str, int position);
    extern wstring& delete_range(wstring& str, int head, int tail);

    extern string to_string(wstring& self, char* default_value);
    extern wstring printable(wstring& str);

    inline int compare(wstring& left, wstring& right) {
        return wcscmp(left, right);
    }
    
    extern void replace(wstring& self, int index, wchar_t c);
    extern wchar_t item(wstring& self, int index, wchar_t default_value);
}

/// vector ///
struct vector<T> 
{
    T&* items;
    int len;
    int size;
};

impl vector<T> 
{
    initialize() 
    {
        self.size = 16;
        self.len = 0;
        self.items = borrow new T[self.size];
    }
    vector<T>%* initialize_with_values(vector<T>%* self, int len, T& value) 
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

    vector<T>%* clone(vector<T>* self) {
        var result = new vector<T>.initialize();

        for(int i=0; i<self.len; i++) {
            T& it = self.items[i];
            if(isheap(T)) {
                result.push_back(clone it);
            }
            else {
                result.push_back(dummy_heap it);
            }
        }

        return result;
    }

    finalize()
    {
        if(isheap(T)) {
            for(int i=0; i<self.len; i++) 
            {
                delete self.items[i];

            }
        }
        delete self.items;
    }
    
    void push_back(vector<T>* self, T item) {
        managed item;

        if(self.len == self.size) {
            var new_size = self.size * 2;
            var items = self.items;

            self.items = borrow new T[new_size];

            int i;
            for(i=0; i<self.size; i++) {
                self.items[i] = items[i];
            }

            self.size = new_size;

            delete items;
        }

        self.items[self.len] = item;
        self.len++;
    }

    T pop_back(vector<T>* self, T& default_value)
    {
        if(self.len == 0) {
            return dummy_heap default_value;
        }

        T result = (T)self.items[self.len-1];

        self.len--;

        return result;
    }

    T& item(vector<T>* self, int index, T& default_value) 
    {
        if(index < 0) {
            index += self.len;
        }

        if(index >= 0 && index < self.len)
        {
            return self.items[index];
        }

        return default_value;
    }
    T clone_item(vector<T>* self, int index, T& default_value) 
    {
        if(index < 0) {
            index += self.len;
        }

        if(index >= 0 && index < self.len)
        {
            if(isheap(T)) {
                return clone self.items[index];
            }
            else {
                return dummy_heap self.items[index];
            }
        }

        return dummy_heap default_value;
    }
    void each(vector<T>* self, void (*block_)(T&,int,bool*)) {
        for(int i_=0; i_<self.len; i_++) {
            bool end_flag_ = false;
            block_(self.items[i_], i_, &end_flag_);
            if(end_flag_ == true) {
                break;
            }
        };
    }

    int find(vector<T>* self, T& item, int default_value) {
        int result = default_value;
        self.each {
            if(it.equals(item)) {
                result = it2;
                *it3 = true;
                return;
            }
        }

        return result;
    }

    template <R> vector<R>*% map(vector<T>* self, R (*block_)(T&))
    {
        var result_ = new vector<R>.initialize();

        for(int i_=0; i_<self.len; i_++) {
            result_.push_back(block_(self.items[i_]));
        }

        result_
    }

    bool equals(vector<T>* left, vector<T>* right)
    {
        if(left.len != right.len) {
            return false;
        }

        for(int i=0; i<left.len; i++) {
            if(!(left.items[i].equals(right.items[i])))
            {
                return false;
            }
        }

        return true;
    }

    bool replace(vector<T>* self, int index, T value) 
    {
        if(index < 0) {
            index += self.len;
        }

        if(index >= 0 && index < self.len)
        {
            if(isheap(T)) {
                delete self.items[index];
            }

            self.items[index] = value;

            return true;
        }

        return false;
    }

    int length(vector<T>* self)
    {
        return self.len;
    }

    void reset(vector<T>* self) {
        self.len = 0;
    }
    
    list<T>*% to_list(vector<T>* self) {
        var result = new vector<T>.initialize();
        
        self.each {
            if(isheap(T)) {
                result.push_back(clone it);
            }
            else {
                result.push_back(dummy_heap it);
            }
        }
        
        return result;
    }
}

ruby_macro vec {
    params = [];
    param = "";
    dquort = false;
    squort = false;
    param_line = ENV['PARAMS'];
    n = 0;
    while(n < param_line.length()) do
        c = param_line[n];
        n = n + 1;

        if (dquort || squort) && c == "\\"
            param.concat(c);
            
            c = param_line[n];
            n = n + 1;

            param.concat(c);
        elsif c == "\""
            param.concat(c);
            dquort = !dquort
        elsif c == "'"
            param.concat(c);
            squort = !squort
        elsif dquort || squort
            param.concat(c);
        elsif c == ","
            if param.length() > 0
                params.push(param); param = ""
            end
        else
            param.concat(c);
        end
    end

    if param.length() != 0
        params.push(param);
    end

    if params.length() > 0
        puts("{");
        puts("var result = new vector<typeof(#{params[0]})>.initialize();");

        params.each do |param|
            puts("result.push_back(#{param});");
        end

        puts("result");
        puts("}");
    end
}

/// list ///
impl list <T>
{
    initialize() {
        self.head = null;
        self.tail = null;
        self.len = 0;
    }

    finalize() {
        list_item<T>* it = self.head;
        while(it != null) {
            if(isheap(T)) {
                delete it.item;
            }
            var prev_it = it;
            it = it.next;
            delete prev_it;
        }
    }

    list<T>*% clone(list<T>* self) {
        var result = new list<T>.initialize();

        list_item<T>* it = self.head;
        while(it != null) {
            if(isheap(T)) {
                result.push_back(clone it.item);
            }
            else {
                result.push_back(dummy_heap it.item);
            }

            it = it.next;
        }

        return result;
    }

    void reset(list<T>* self) {
        list_item<T>* it = self.head;
        while(it != null) {
            if(isheap(T)) {
                delete it.item;
            }
            var prev_it = it;
            it = it.next;
            delete prev_it;
        }

        self.head = null;
        self.tail = null;

        self.len = 0;
    }

    void push_back(list<T>* self, T item) 
    {
        managed item;

        if(self.len == 0) {
            list_item<T>* litem = borrow new list_item<T>;
            litem.prev = null;
            litem.next = null;
            litem.item = item;
            
            self.tail = litem;
            self.head = litem;
        }
        else if(self.len == 1) {
            list_item<T>* litem = borrow new list_item<T>;

            litem.prev = self.head;
            litem.next = null;
            litem.item = item;
            
            self.tail = litem;
            self.head.next = litem;
        }
        else {
            list_item<T>* litem = borrow new list_item<T>;

            litem.prev = self.tail;
            litem.next = null;
            litem.item = item;
            
            self.tail.next = litem;
            self.tail = litem;
        }

        self.len++;
    }

    T pop_back(list<T>* self, T& default_value)
    {
        if(self.len == 0) {
            return dummy_heap default_value;
        }
        else if(self.len == 1) {
            T result = (T)self.head.item;

            delete self.head;

            self.head = null;
            self.tail = null;

            self.len--;

            if(isheap(T)) {
                return clone result;
            }
            else {
                return dummy_heap result;
            }
        }
        else if(self.len == 2) {
            T result = (T)self.tail.item;

            delete self.tail;

            self.tail = self.head;
            self.head.next = null;
            self.head.prev = null;

            self.len--;

            if(isheap(T)) {
                return clone result;
            }
            else {
                return dummy_heap result;
            }
        }
        else {
            T result = (T)self.tail.item;

            list_item<T>* it = self.tail;

            self.tail = self.tail.prev;
            self.tail.next = null;

            delete it;

            self.len--;

            if(isheap(T)) {
                return clone result;
            }
            else {
                return dummy_heap result;
            }
        }
    }
    
    T pop_front(list<T>* self, T& default_value)
    {
        if(self.len == 0) {
            return dummy_heap default_value;
        }
        else if(self.len == 1) {
            T result = (T)self.head.item;

            delete self.head;

            self.head = null;
            self.tail = null;

            self.len = 0;

            if(isheap(T)) {
                return clone result;
            }
            else {
                return dummy_heap result;
            }
        }
        else if(self.len == 2) {
            T result = (T)self.head.item;

            var head_before = self.head;

            self.head = self.head.next;
            self.head.prev = null;
            self.head.next = null;
            
            delete head_before;

            self.len--;

            if(isheap(T)) {
                return clone result;
            }
            else {
                return dummy_heap result;
            }
        }
        else {
            T result = (T)self.head.item;

            var head_before = self.head;

            self.head = self.head.next;
            self.head.prev = null;
            
            delete head_before;

            self.len--;

            if(isheap(T)) {
                return clone result;
            }
            else {
                return dummy_heap result;
            }
        }
    }

    void insert(list<T>* self, int position, T item)
    {
        if(position < 0) {
            position += self.len + 1;
        }
        if(position < 0) {
            position = 0;
        }
        if(self.len == 0 || position >= self.len) 
        {
            self.push_back(item);
            return;
        }

        managed item;

        if(position == 0) {
            list_item<T>* litem = borrow new list_item<T>;

            litem.prev = null;
            litem.next = self.head;
            litem.item = item;
            
            self.head.prev = litem;
            self.head = litem;

            self.len++;
        }
        else if(self.len == 1) {
            var litem = borrow new list_item<T>;

            litem.prev = self.head;
            litem.next = self.tail;
            litem.item = item;
            
            self.tail.prev = litem;
            self.head.next = litem;

            self.len++;
        }
        else {
            list_item<T>?* it = self.head;
            var i = 0;
            while(it != null) {
                if(position == i) {
                    list_item<T>* litem = borrow new list_item<T>;

                    litem.prev = it.prev;
                    litem.next = it;
                    litem.item = item;

                    it.prev.next = litem;
                    it.prev = litem;

                    self.len++;
                }

                it = it.next;
                i++;
            }
        }
    }

    void delete(list<T>* self, int position)
    {
        if(position < 0) {
            position += self.len + 1;
        }

        if(position >= 0 && position < self.len)
        {
            if(self.len == 1) {
                if(isheap(T)) {
                    delete self.head.item;
                }
                delete self.head;

                self.head = null;
                self.tail = null;

                self.len = 0;
            }
            else if(self.len == 2) {
                if(position == 0) {
                    list_item<T>?* it = self.head;

                    self.head = it.next;

                    self.head.prev = null;
                    self.head.next = null;

                    self.tail = self.head;

                    if(isheap(T)) {
                        delete it.item;
                    }
                    delete it;

                    self.len--;
                }
                else {
                    list_item<T>?* it = self.tail;

                    self.head.next = null;
                    self.head.prev = null;

                    self.tail = self.head;

                    if(isheap(T)) {
                        delete it.item;
                    }
                    delete it;

                    self.len--;
                }
            }
            else {
                list_item<T>?* it = self.head;
                var i = 0;
                while(it != null) {
                    if(position == i) {
                        if(i == 0) {
                            self.head = it.next;
                            self.head.prev = null;

                            if(isheap(T)) {
                                delete it.item;
                            }
                            delete it;

                            self.len--;
                        }
                        else if(i == self.len-1)
                        {
                           self.tail = it.prev;
                           self.tail.next = null;
                           if(isheap(T)) 
                           {
                                delete it.item;
                            }
                            delete it;

                            self.len--;
                        }
                        else {
                            it.prev.next = it.next;
                            it.next.prev = it.prev;
                            if(isheap(T)) {
                                delete it.item;
                            }
                            delete it;

                            self.len--;
                        }
                        break;
                    }

                    it = it.next;
                    i++;
                }
            }
        }
    }

    void delete_range(list<T>* self, int head, int tail)
    {
        if(head < 0) {
            head += self.len;
        }
        if(tail < 0) {
            tail += self.len + 1;
        }

        if(head > tail) {
            int tmp = tail;
            tail = head;
            head = tmp;
        }

        if(head < 0) {
            head = 0;
        }

        if(tail > self.len) {
            tail = self.len;
        }

        if(head == tail) {
            return;
        }

        if(head == 0 && tail == self.len) 
        {
            self.reset();
        }
        else if(head == 0) {
            list_item<T>?* it = self.head;
            var i = 0;
            while(it != null) {
                if(i < tail) {
                    if(isheap(T)) {
                        delete it.item;
                    }
                    list_item<T>?* prev_it = it;

                    it = it.next;
                    i++;

                    delete prev_it;

                    self.len--;
                }
                else if(i == tail) {
                    self.head = it;
                    self.head.prev = null;
                    break;
                }
                else {
                    it = it.next;
                    i++;
                }
            }
        }
        else if(tail == self.len) {
            list_item<T>?* it = self.head;
            var i = 0;
            while(it != null) {
                if(i == head) {
                    self.tail = it.prev;
                    self.tail.next = null;
                }

                if(i >= head) {
                    if(isheap(T)) {
                        delete it.item;
                    }
                    list_item<T>?* prev_it = it;

                    it = it.next;
                    i++;

                    delete prev_it;

                    self.len--;
                }
                else {
                    it = it.next;
                    i++;
                }
            }
        }
        else {
            list_item<T>?* it = self.head;

            list_item<T>?* head_prev_it = null;
            list_item<T>?* tail_it = null;


            var i = 0;
            while(it != null) {
                if(i == head) {
                    head_prev_it = it.prev;
                }
                if(i == tail) {
                    tail_it = it;
                }

                if(i >= head && i < tail) 
                {
                    if(isheap(T)) {
                        delete it.item;
                    }
                    list_item<T>?* prev_it = it;

                    it = it.next;
                    i++;

                    delete prev_it;

                    self.len--;
                }
                else {
                    it = it.next;
                    i++;
                }
            }

            if(head_prev_it != null) {
                head_prev_it.next = tail_it;
            }
            if(tail_it != null) {
                tail_it.prev = head_prev_it;
            }
        }
    }

    void replace(list<T>* self, int position, T item)
    {
        managed item;

        if(position < 0) {
            position += self.len;
        }

        list_item<T>?* it = self.head;
        var i = 0;
        while(it != null) {
            if(position == i) {
                if(isheap(T)) {
                    delete it.item;
                }

                it.item = item;
                break;
            }
            it = it.next;
            i++;
        };
    }
    
    T& item(list<T>* self, int position, T& default_value) 
    {
        if(position < 0) {
            position += self.len;
        }

        list_item<T>?* it = self.head;
        var i = 0;
        while(it != null) {
            if(position == i) {
                return it.item;
            }
            it = it.next;
            i++;
        };

        return default_value;
    }

    T clone_item(list<T>* self, int position, T& default_value) 
    {
        if(position < 0) {
            position += self.len;
        }

        list_item<T>?* it = self.head;
        var i = 0;
        while(it != null) {
            if(position == i) {
                if(isheap(T)) {
                    return clone it.item;
                }
                else {
                    return dummy_heap it.item;
                }
            }
            it = it.next;
            i++;
        };

        return dummy_heap default_value;
    }
    
    void each(list<T>* self, void (*block_)(T&,int,bool*)) {
        list_item<T>?* it_ = self.head;
        var i_ = 0;
        while(it_ != null) {
            bool end_flag_ = false;
            block_(it_.item, i_, &end_flag_);

            if(end_flag_ == true) {
                break;
            }
            it_ = it_.next;
            i_++;
        }
    }

    list<T>*% sublist(list<T>* self, int begin, int tail) {
        list<T>%* result = new list<T>.initialize();

        if(begin < 0) {
            begin += self.len;
        }

        if(tail < 0) {
            tail += self.len + 1;
        }

        if(begin < 0) {
            begin = 0;
        }

        if(tail >= self.len) {
            tail = self.len;
        }


        list_item<T>?* it = self.head;
        var i = 0;
        while(it != null) {
            if(i >= begin && i < tail) {
                if(isheap(T)) {
                    result.push_back(clone it.item);
                }
                else {
                    result.push_back(dummy_heap it.item);
                }
            }
            it = it.next;
            i++;
        };

        return result;
    }

    list<T>*% reverse(list<T>* self) {
        list<T>%* result = new list<T>.initialize();

        list_item<T>?* it = self.tail;
        while(it != null) {
            if(isheap(T)) {
                result.push_back(clone it.item);
            }
            else {
                result.push_back(dummy_heap it.item);
            }
            it = it.prev;
        };

        return result;
    }
    string join(list<string>* self, char* separator) {
        buffer%* buf = new buffer.initialize();

        list_item<T>?* it = self.head;
        var i = 0;
        while(it != null) {
            if(i == self.length() - 1) {
                buf.append_str(it.item);
            }
            else {
                buf.append_str(it.item);
                buf.append_str(separator);
            }

            it = it.next;
            i++;
        }

        return string(buf.buf);
    }
    list<T>*% merge_list(list<T>* left, list<T>* right) {
        var result = new list<T>.initialize();

        list_item<T>*? it = left.head;
        list_item<T>*? it2= right.head;

        while(true) {
            if(it && it2) {
                if(it.item == null) {
                    it = it.next;
                }
                else if(it2.item == null) {
                    it2 = it2.next;
                }
                else if(it.item.compare(it2.item) <= 0) 
                {
                    if(isheap(T)) {
                        result.push_back(clone it.item);
                    }
                    else {
                        result.push_back(dummy_heap it.item);
                    }

                    it = it.next;
                }
                else {
                    if(isheap(T)) {
                        result.push_back(clone it2.item);
                    }
                    else {
                        result.push_back(dummy_heap it2.item);
                    }


                    it2 = it2.next;
                }
            }

            if(it == null) {
                if(it2 != null) {
                    while(it2 != null) {
                        if(isheap(T)) {
                            result.push_back(clone it2.item);
                        }
                        else {
                            result.push_back(dummy_heap it2.item);
                        }

                        it2 = it2.next;
                    }
                }
                break;
            }
            else if(it2 == null) {
                if(it != null) {
                    while(it != null) {
                        if(isheap(T)) {
                            result.push_back(clone it.item);
                        }
                        else {
                            result.push_back(dummy_heap it.item);
                        }

                        it = it.next;
                    }
                }
                break;
            }
        }

        return result;
    }
    list<T>*% merge_sort(list<T>* self) {
        if(self.head == null) {
            return clone self;
        }
        if(self.head.next == null) {
            return clone self;
        }

        var list1 = new list<T>.initialize();
        var list2 = new list<T>.initialize();

        list_item<T>* it = self.head;

        while(true) {
            if(isheap(T)) {
                list1.push_back(clone it.item);
            }
            else {
                list1.push_back(dummy_heap it.item);
            }

            if(isheap(T)) {
                list2.push_back(clone it.next.item);
            }
            else {
                list2.push_back(dummy_heap it.next.item);
            }

            if(it.next.next == null) {
                break;
            }

            it = it.next.next;

            if(it.next == null) {
                if(isheap(T)) {
                    list1.push_back(clone it.item);
                }
                else {
                    list1.push_back(dummy_heap it.item);
                }
                break;
            }
        }

        return list1.merge_sort().merge_list( list2.merge_sort());
    }
    list<T>*% sort(list<T>* self) {
        return self.merge_sort();
    }
    list<T>*% merge_list2(list<T>* left, list<T>* right, int (*compare)(T&,T&)) {
        var result = new list<T>.initialize();

        list_item<T>*? it = left.head;
        list_item<T>*? it2= right.head;

        while(true) {
            if(it && it2) {
                if(it.item == null) {
                    it = it.next;
                }
                else if(it2.item == null) {
                    it2 = it2.next;
                }
                else if(compare(it.item, it2.item) <= 0) 
                {
                    if(isheap(T)) {
                        result.push_back(clone it.item);
                    }
                    else {
                        result.push_back(dummy_heap it.item);
                    }

                    it = it.next;
                }
                else {
                    if(isheap(T)) {
                        result.push_back(clone it2.item);
                    }
                    else {
                        result.push_back(dummy_heap it2.item);
                    }


                    it2 = it2.next;
                }
            }

            if(it == null) {
                if(it2 != null) {
                    while(it2 != null) {
                        if(isheap(T)) {
                            result.push_back(clone it2.item);
                        }
                        else {
                            result.push_back(dummy_heap it2.item);
                        }

                        it2 = it2.next;
                    }
                }
                break;
            }
            else if(it2 == null) {
                if(it != null) {
                    while(it != null) {
                        if(isheap(T)) {
                            result.push_back(clone it.item);
                        }
                        else {
                            result.push_back(dummy_heap it.item);
                        }

                        it = it.next;
                    }
                }
                break;
            }
        }

        return result;
    }
    list<T>*% merge_sort2(list<T>* self, int (*compare)(T&,T&)) {
        if(self.head == null) {
            return clone self;
        }
        if(self.head.next == null) {
            return clone self;
        }

        var list1 = new list<T>.initialize();
        var list2 = new list<T>.initialize();

        list_item<T>* it = self.head;

        while(true) {
            if(isheap(T)) {
                list1.push_back(clone it.item);
            }
            else {
                list1.push_back(dummy_heap it.item);
            }

            if(isheap(T)) {
                list2.push_back(clone it.next.item);
            }
            else {
                list2.push_back(dummy_heap it.next.item);
            }

            if(it.next.next == null) {
                break;
            }

            it = it.next.next;

            if(it.next == null) {
                if(isheap(T)) {
                    list1.push_back(clone it.item);
                }
                else {
                    list1.push_back(dummy_heap it.item);
                }
                break;
            }
        }

        return list1.merge_sort2(compare).merge_list2( list2.merge_sort2(compare), compare);
    }
    list<T>*% sort_block(list<T>* self, int (*compare)(T&,T&)) {
        return self.merge_sort2(compare);
    }

    list<T>*% uniq(list<T>* self) {
        list<T>*% result = new list<T>.initialize();

        if(self.length() > 0) {
            T& item_before = self.item(0, null);

            if(isheap(T)) {
                result.push_back(clone item_before);
            }
            else {
                result.push_back(dummy_heap item_before);
            }

            self.sublist(1,-1).each {
                if(!it.equals(item_before)) {
                    if(isheap(T)) {
                        result.push_back(clone it);
                    }
                    else {
                        result.push_back(dummy_heap it);
                    }
                }

                item_before = it;
            }
        }

        return result;
    }

    int find(list<T>* self, T& item, int default_value) {
        int result = default_value;
        self.each {
            if(it.equals(item)) {
                result = it2;
                *it3 = true;
                return;
            }
        }

        return result;
    }

    bool equals(list<T>* left, list<T>* right)
    {
        if(left.len != right.len) {
            return false;
        }

        list_item<T>?* it = left.head;
        list_item<T>?* it2 = right.head;

        while(it != null) {
            if(!it.item.equals(it2.item)) {
                return false;
            }

            it = it.next;
            it2 = it2.next;
        }

        return true;
    }

    int length(list<T>* self)
    {
        return self.len;
    }
    template <R> list<R>*% map(list<T>* self, R (*block_)(T&))
    {
        var result_ = new list<R>.initialize();

        list_item<T>?* it_ = self.head;
        while(it_ != null) {
            result_.push_back(block_(it_.item));

            it_ = it_.next;
        }

        result_
    }
    list<T>*% filter(list<T>* self, bool (*block_)(T&))
    {
        var result_ = new list<T>.initialize();

        list_item<T>?* it_ = self.head;
        while(it_ != null) {
            if(block_(it_.item)) {
                if(isheap(T)) {
                    result_.push_back(clone it_.item);
                }
                else {
                    result_.push_back(dummy_heap it_.item);
                }
            }

            it_ = it_.next;
        }

        result_
    } 
    
    vector<T> to_vector(list<T>* self) {
        var result = new list<T>.initialize();
        
        self.each {
            if(isheap(T)) {
                result.push_back(clone it);
            }
            else {
                result.push_back(dummy_heap it);
            }
        }
        
        return result;
    }
}

ruby_macro list {
    params = [];
    param = "";
    dquort = false;
    squort = false;
    param_line = ENV['PARAMS'];
    n = 0;
    while(n < param_line.length()) do
        c = param_line[n];
        n = n + 1;

        if (dquort || squort) && c == "\\"
            param.concat(c);
            
            c = param_line[n];
            n = n + 1;

            param.concat(c);
        elsif c == "\""
            param.concat(c);
            dquort = !dquort
        elsif c == "'"
            param.concat(c);
            squort = !squort
        elsif dquort || squort
            param.concat(c);
        elsif c == ","
            if param.length() > 0
                params.push(param); param = ""
            end
        else
            param.concat(c);
        end
    end

    if param.length() != 0
        params.push(param);
    end

    if params.length() > 0
        puts("{");
        puts("var result = new list<typeof(#{params[0]})>.initialize();");

        params.each do |param|
            puts("result.push_back(#{param});");
        end

        puts("result");
        puts("}");
    end
}


struct tuple1<T>
{
    T v1;
}

impl tuple1 <T>
{
    initialize() {
    }

    bool equals(tuple1<T>* left, tuple1<T>* right)
    {
        if(!left.v1.equals(right.v1)) {
            return false;
        }

        return true;
    }
}

struct tuple2<T, T2>
{
    T v1;
    T2 v2;
}

impl tuple2 <T, T2>
{
    initialize() {
    }

    bool equals(tuple2<T, T2>* left, tuple2<T, T2>* right)
    {
        if(!left.v1.equals(right.v1)) {
            return false;
        }
        if(!left.v2.equals(right.v2)) {
            return false;
        }

        return true;
    }
}

struct tuple3<T, T2, T3>
{
    T v1;
    T2 v2;
    T3 v3;
}

impl tuple3 <T, T2, T3>
{
    initialize() {
    }

    bool equals(tuple3<T, T2, T3>* left, tuple3<T, T2, T3>* right)
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
}

struct tuple4<T, T2, T3, T4>
{
    T v1;
    T2 v2;
    T3 v3;
    T4 v3;
}

impl tuple4 <T, T2, T3, T4>
{
    initialize() {
    }

    bool equals(tuple4<T, T2, T3, T4>* left, tuple4<T, T2, T3, T4>* right)
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
}

ruby_macro tuple {
    params = [];
    param = "";
    dquort = false;
    squort = false;
    param_line = ENV['PARAMS'];
    n = 0;
    while(n < param_line.length()) do
        c = param_line[n];
        n = n + 1;

        if (dquort || squort) && c == "\\"
            param.concat(c);
            
            c = param_line[n];
            n = n + 1;

            param.concat(c);
        elsif c == "\""
            param.concat(c);
            dquort = !dquort
        elsif c == "'"
            param.concat(c);
            squort = !squort
        elsif dquort || squort
            param.concat(c);
        elsif c == ","
            if param.length() > 0
                params.push(param); param = ""
            end
        else
            param.concat(c);
        end
    end

    if param.length() != 0
        params.push(param);
    end

    if params.length() == 1
    then
        puts("{");
        puts("var result = new tuple1<typeof(#{params[0]})>;");

        puts("result.v1 = #{params[0]};");

        puts("result");
        puts("}");
    end

    if params.length() == 2 
    then
        puts("{");
        puts("var result = new tuple2<typeof(#{params[0]}),typeof(#{params[1]})>;");

        puts("result.v1 = #{params[0]};");
        puts("result.v2 = #{params[1]};");

        puts("result");
        puts("}");
    end

    if params.length() == 3
    then
        puts("{");
        puts("var result = new tuple3<typeof(#{params[0]}),typeof(#{params[1]}),typeof(#{params[2]})>;");

        puts("result.v1 = #{params[0]};");
        puts("result.v2 = #{params[1]};");
        puts("result.v3 = #{params[2]};");

        puts("result");
        puts("}");
    end

    if params.length() == 4
    then
        puts("{");
        puts("var result = new tuple4<typeof(#{params[0]}),typeof(#{params[1]}),typeof(#{params[2]}),typeof(#{params[3]})>;");

        puts("result.v1 = #{params[0]};");
        puts("result.v2 = #{params[1]};");
        puts("result.v3 = #{params[2]};");
        puts("result.v4 = #{params[3]};");

        puts("result");
        puts("}");
    end
}

struct map<T, T2>
{
    T&* keys;
    bool* item_existance;
    T2&* items;
    int size;
    int len;
}

#define MAP_TABLE_DEFAULT_SIZE 128

impl map <T, T2>
{
    initialize() {
        self.keys = borrow new T[MAP_TABLE_DEFAULT_SIZE];
        self.items = borrow new T2[MAP_TABLE_DEFAULT_SIZE];
        self.item_existance = borrow new bool[MAP_TABLE_DEFAULT_SIZE];

        for(int i=0; i<MAP_TABLE_DEFAULT_SIZE; i++)
        {
            self.item_existance[i] = false;
        }

        self.size = MAP_TABLE_DEFAULT_SIZE;
        self.len = 0;
    }

    finalize() {
        for(int i=0; i<self.size; i++) {
            if(self.item_existance[i]) {
                if(isheap(T2)) {
                    delete self.items[i];
                }
            }
        }
        delete self.items;

        for(int i=0; i<self.size; i++) {
            if(self.item_existance[i]) {
                if(isheap(T)) {
                    delete self.keys[i];
                }
            }
        }
        delete self.keys;

        delete self.item_existance;
    }

    map<T, T2>*% clone(map<T, T2>* self)
    {
        var result = new map<T,T2>.initialize();

        self.each {
            if(isheap(T)) {
                if(isheap(T2)) {
                    result.insert(clone it, clone it2);
                }
                else {
                    result.insert(clone it, dummy_heap it2);
                }
            }
            else {
                if(isheap(T2)) {
                    result.insert(dummy_heap it, clone it2);
                }
                else {
                    result.insert(dummy_heap it, dummy_heap it2);
                }
            }
        }

        return result;
    }

    void each(map<T, T2>* self, void (*block_)(T&,T2&,bool*)) 
    {
        for(int i_=0; i_<self.size; i_++) {
            if(self.item_existance[i_]) {
                bool end_flag_ = false;
                block_(self.keys[i_], self.items[i_], &end_flag_);
                if(end_flag_ == true) {
                    break;
                }
            }
        }
    }

    void rehash(map<T,T2>* self) {
        int size = self.size * 3;
        T&* keys = borrow new T[size];
        T2&* items = borrow new T2[size];
        bool* item_existance = borrow new bool[size];

        int len = 0;

        self.each {
            int hash = ((T)it).get_hash_key() % size;
            int n = hash;

            while(true) {
                if(item_existance[n])
                {
                    n++;

                    if(n >= size) {
                        n = 0;
                    }
                    else if(n == hash) {
                        fprintf(stderr, "unexpected error in map.rehash(1)\n");
                        exit(2);
                    }
                }
                else {
                    item_existance[n] = true;
                    keys[n] = it;
                    items[n] = it2;

                    len++;
                    break;
                }
            }
        }

        delete self.items;
        delete self.item_existance;
        delete self.keys;

        self.keys = keys;
        self.items = items;
        self.item_existance = item_existance;

        self.size = size;
        self.len = len;
    }

    bool find(map<T, T2>* self, T& key) {
        int hash = ((T)key).get_hash_key() % self.size;
        int it = hash;

        while(true) {
            if(self.item_existance[it])
            {
                if(self.keys[it].equals(key))
                {
                    return true;
                }

                it++;

                if(it >= self.size) {
                    it = 0;
                }
                else if(it == hash) {
                    return false;
                }
            }
            else {
                return false;
            }
        }

        return false;
    }

    T2& at(map<T, T2>* self, T& key, T2& default_value) 
    {
        int hash = ((T)key).get_hash_key() % self.size;
        int it = hash;

        while(true) {
            if(self.item_existance[it])
            {
                if(self.keys[it].equals(key))
                {
                    return self.items[it];
                }

                it++;

                if(it >= self.size) {
                    it = 0;
                }
                else if(it == hash) {
                    return default_value;
                }
            }
            else {
                return default_value;
            }
        }

        return default_value;
    }

    T2 at_clone(map<T, T2>* self, T& key, T2& default_value) 
    {
        int hash = ((T)key).get_hash_key() % self.size;
        int it = hash;

        while(true) {
            if(self.item_existance[it])
            {
                if(self.keys[it].equals(key))
                {
                    if(isheap(T)) {
                        return clone self.items[it];
                    }
                    else {
                        return dummy_heap self.items[it];
                    }
                }

                it++;

                if(it >= self.size) {
                    it = 0;
                }
                else if(it == hash) {
                    return dummy_heap default_value;
                }
            }
            else {
                return dummy_heap default_value;
            }
        }

        return dummy_heap default_value;
    }

    void insert(map<T,T2>* self, T key, T2 item) 
    {
        managed key;
        managed item;

        if(self.len*2 >= self.size) {
            self.rehash();
        }

        int hash = ((T)key).get_hash_key() % self.size;
        int it = hash;

        while(true) {
            if(self.item_existance[it])
            {
                if(self.keys[it].equals(key)) 
                {
                    if(isheap(T)) {
                        delete dummy_heap self.keys[it];
                    }
                    if(isheap(T2)) {
                        delete dummy_heap self.items[it];
                    }
                    self.keys[it] = key;
                    self.items[it] = item;

                    break;
                }

                it++;

                if(it >= self.size) {
                    it = 0;
                }
                else if(it == hash) {
                    fprintf(stderr, "unexpected error in map.insert\n");
                    exit(2);
                }
            }
            else {
                self.item_existance[it] = true;
                self.keys[it] = key;
                self.items[it] = item;

                self.len++;

                break;
            }
        }
    }

    bool equals(map<T, T2>* left, map<T, T2>* right)
    {
        if(left.len != right.len) {
            return false;
        }

        bool result = true;
        left.each {
            if(right.find(it)) {
                T2& default_value;
                T2 item = right.at(it, default_value);
                if(!it2.equals(item)) {
                    result = false;
                }
            }
            else {
                result = false;
            }
        }

        return result;
    }

    int length(map<T, T2>* self) {
        return self.len;
    }
}

ruby_macro map {
    params = [];
    param = "";
    dquort = false;
    squort = false;
    param_line = ENV['PARAMS'];
    n = 0;
    while(n < param_line.length()) do
        c = param_line[n];
        n = n + 1;

        if (dquort || squort) && c == "\\"
            param.concat(c);
            
            c = param_line[n];
            n = n + 1;

            param.concat(c);
        elsif c == "\""
            param.concat(c);
            dquort = !dquort
        elsif c == "'"
            param.concat(c);
            squort = !squort
        elsif dquort || squort
            param.concat(c);
        elsif c == ","
            if param.length() > 0
                params.push(param); param = ""
            end
        elsif c == ":"
            if param.length() > 0
                params.push(param); param = ""
            end
        else
            param.concat(c);
        end
    end

    if param.length() != 0
        params.push(param);
    end

    if params.length() >= 2
    then
        puts("{");
        puts("var result = new map<typeof(#{params[0]}), typeof(#{params[1]})>.initialize();");

        key = nil;
        for it in params do
            if key == nil
            then
                key = it;
            else
                puts("result.insert(#{key}, #{it});");
                key = nil;
            end
        end

        puts("result");
        puts("}");
    end
}

/// others ///
extern void xassert(char* msg, bool exp);

#include <limits.h>
#include <pcre.h>

/// string ///
string string(char* str)
{
    int len = strlen(str);

    string result = new char[len + 1];

    strcpy(result, str);

    result
}

string string_from_wchar_t(wchar_t* wstr, char* default_value)
{
    int len = MB_LEN_MAX*(wcslen(wstr)+1);

    string result = new char[len];

    if(wcstombs(result, wstr, len) < 0) 
    {
        xstrncpy(result, default_value, len);
    }

    result
}

string operator+(char* left, char* right)
{
    int len1 = strlen(left);
    int len2 = strlen(right);

    string result = new char[len1 + len2 + 1];

    strcpy(result, left);
    strcat(result, right);

    result
}

string operator*(char* left, int num)
{
    int len = strlen(left);

    string result = new char[len * num + 1];

    result[0] = '\0';

    for(int i=0; i<num; i++) {
        strcat(result, left);
    }

    result
}

string operator+(string& left, string& right)
{
    int len1 = strlen(left);
    int len2 = strlen(right);

    string result = new char[len1 + len2 + 1];

    strcpy(result, left);
    strcat(result, right);

    result
}

string operator*(string& left, int num)
{
    int len = strlen(left);

    string result = new char[len * num + 1];

    result[0] = '\0';

    for(int i=0; i<num; i++) {
        strcat(result, left);
    }

    result
}

impl string
{
    bool equals(string& left, string& right)
    {
        return strcmp(left, right) == 0;
    }

    int length(string& str)
    {
        return strlen(str);
    }

    int get_hash_key(string& value)
    {
        int result = 0;
        char* p = value;
        while(*p) {
            result += (*p);
            p++;
        }
        return result;
    }

    string reverse(string& str) {
        int len = strlen(str);
        string result = new char[len + 1];

        for(int i=0; i<len; i++) {
            result[i] = str[len-i-1];
        }

        result[len] = '\0';

        return result;
    }

    string substring(string& str, int head, int tail)
    {
        if(str == null) {
            return string("");
        }

        int len = strlen(str);

        if(head < 0) {
            head += len;
        }
        if(tail < 0) {
            tail += len + 1;
        }

        if(head > tail) {
            return str.substring(tail, head).reverse();
        }

        if(head < 0) {
            head = 0;
        }

        if(tail >= len) {
            tail = len;
        }

        if(head == tail) {
            return string("");
        }

        if(tail-head+1 < 1) {
            return string("");
        }

        string result = new char[tail-head+1];

        ncmemcpy(result, str + head, tail-head);
        result[tail-head] = '\0';

        return result;
    }
    int index(string& str, char* search_str, int default_value)
    {
        char* head = strstr(str, search_str);

        if(head == null) {
            return default_value;
        }

        return head - str;
    }
    int rindex(string& str, char* search_str, int default_value)
    {
        int len = strlen(search_str);
        char* p = str + strlen(str) - len;

        while(p >= str) {
            if(strncmp(p, search_str, len) == 0) {
                return p - str;
            }

            p--;
        }

        return default_value;
    }
    int index_regex(string& self, nregex reg, int default_value)
    {
        int ovec_max = 16;
        int start[ovec_max];
        int end[ovec_max];
        int ovec_value[ovec_max * 3];

        int result = default_value;
        
        int offset = 0;

        const char* err;
        int erro_ofs;

        int options = reg.options;
        char* str = reg.str;

        pcre* re = pcre_compile(str, options, &err, &erro_ofs, null);

        while(true) {
            int options = PCRE_NEWLINE_LF;
            int len = strlen(self);
            int regex_result = pcre_exec(re, 0, self, len, offset, options, ovec_value, ovec_max*3);

            for(int i=0; i<ovec_max; i++) {
                start[i] = ovec_value[i*2];
            }
            for(int i=0; i<ovec_max; i++) {
                end[i] = ovec_value[i*2+1];
            }

            /// match and no group strings ///
            if(regex_result == 1 || regex_result > 0) 
            {
                result = start[0];
                break;
            }
            /// no match ///
            {
                break;
            }
        }

        return result;
    }
    int rindex_regex(string& self, nregex reg, int default_value)
    {
        const char* err;
        int erro_ofs;

        int options = reg.options;
        char* str = reg.str;

        pcre* re = pcre_compile(str, options, &err, &erro_ofs, null);

        string self2 = self.reverse();
        
        int ovec_max = 16;
        int start[ovec_max];
        int end[ovec_max];
        int ovec_value[ovec_max * 3];

        int result = default_value;
        
        int offset = 0;

        while(true) {
            int options = PCRE_NEWLINE_LF;
            int len = strlen(self2);
            int regex_result = pcre_exec(re, 0, self2, len, offset, options, ovec_value, ovec_max*3);

            for(int i=0; i<ovec_max; i++) {
                start[i] = ovec_value[i*2];
            }
            for(int i=0; i<ovec_max; i++) {
                end[i] = ovec_value[i*2+1];
            }

            /// match and no group strings ///
            if(regex_result == 1 || regex_result > 0) 
            {
                result = strlen(self) -1 - start[0];
                break;
            }
            /// no match ///
            {
                break;
            }
        }

        return result;
    }
}

//#include <wctype.h>
//#include <wchar.h>
#include <limits.h>
#include <pcre.h>

/// wstring ///
wstring wstring(char* str)
{
    int len = strlen(str);

wstring a = new wchar_t[1];
// I can't understand. this requires for s309x apline linux,... hmm is it my mistake?

    wstring wstr = new wchar_t[len+1];

    int ret = mbstowcs(wstr, str, len+1);
    wstr[ret] = '\0';

    if(ret < 0) {
        wstr[0] = 0;
    }

    return wstr;
}

wstring wstring_from_wchar_t(wchar_t* str)
{
    int len = wcslen(str);

    wstring wstr = new wchar_t[len + 1];

    wcscpy(wstr, str);

    return wstr;
}

wstring operator+(wchar_t* left, wchar_t* right)
{
    int len1 = wcslen(left);
    int len2 = wcslen(right);

    wstring result = new wchar_t[len1 + len2 + 1];

    wcscpy(result, left);
    wcscat(result, right);

    result
}

wstring operator*(wchar_t* left, int num)
{
    int len = wcslen(left);

    wstring result = new wchar_t[len * num + 1];

    result[0] = '\0';

    for(int i=0; i<num; i++) {
        wcscat(result, left);
    }

    result
}

wstring operator+(wstring& left, wstring& right)
{
    int len1 = wcslen(left);
    int len2 = wcslen(right);

    wstring result = new wchar_t[len1 + len2 + 1];

    wcscpy(result, left);
    wcscat(result, right);

    result
}

wstring operator*(wstring& left, int num)
{
    int len = wcslen(left);

    wstring result = new wchar_t[len * num + 1];

    result[0] = '\0';

    for(int i=0; i<num; i++) {
        wcscat(result, left);
    }

    result
}

impl wchar_t
{
    wstring substring(wchar_t* str, int head, int tail)
    {
        if(str == null) {
            return wstring("");
        }

        int len = wcslen(str);

        if(head < 0) {
            head += len;
        }
        if(tail < 0) {
            tail += len + 1;
        }

        if(head > tail) {
            return wstring("");
        }

        if(head < 0) {
            head = 0;
        }

        if(tail >= len) {
            tail = len;
        }

        if(head == tail) {
            return wstring("");
        }

        if(tail-head+1 < 1) {
            return wstring("");
        }

        wstring result = new wchar_t[tail-head+1];

        ncmemcpy(result, str + head, sizeof(wchar_t)*(tail-head));
        result[tail-head] = '\0';

        return result;
    }
}


impl wstring
{
    bool equals(wstring& left, wstring& right)
    {
        return wcscmp(left, right) == 0;
    }

    int length(wstring& str)
    {
        return wcslen(str);
    }

    int get_hash_key(wstring& value)
    {
        int result = 0;
        wchar_t* p = value;
        while(*p) {
            result += (*p);
            p++;
        }
        return result;
    }

    string to_string(wstring& self, char* default_value) 
    {
        int len = MB_LEN_MAX*(wcslen(self)+1);

        string result = new char[len];

        if(wcstombs(result, self, len) < 0) 
        {
            result = string(default_value);
        }

        result
    }

    wstring reverse(wstring& str) {
        int len = wcslen(str);
        wstring result = new wchar_t[len + 1];

        for(int i=0; i<len; i++) {
            result[i] = str[len-i-1];
        }

        result[len] = '\0';

        return result;
    }

    wstring substring(wstring& str, int head, int tail)
    {
        if(str == null) {
            return wstring("");
        }

        int len = wcslen(str);

        if(head < 0) {
            head += len;
        }
        if(tail < 0) {
            tail += len + 1;
        }

        if(head > tail) {
            return str.substring(tail, head).reverse();
        }

        if(head < 0) {
            head = 0;
        }

        if(tail >= len) {
            tail = len;
        }

        if(head == tail) {
            return wstring("");
        }

        if(tail-head+1 < 1) {
            return wstring("");
        }

        wstring result = new wchar_t[tail-head+1];

        ncmemcpy(result, str + head, sizeof(wchar_t)*(tail-head));
        result[tail-head] = '\0';

        return result;
    }

    int index(wstring& str, wchar_t* search_str, int default_value)
    {
        wchar_t* head = wcsstr(str, search_str);

        if(head == null) {
            return default_value;
        }

        return ((head - str) / sizeof(wchar_t));
    }
    int rindex(wstring& str, wchar_t* search_str, int default_value)
    {
        int len = wcslen(search_str);

        wchar_t* p = str + wcslen(str) - len;

        while(p >= str) {
            if(wcsncmp(p, search_str, len) == 0) {
                return ((p - str) / sizeof(wchar_t));
            }

            p--;
        }

        return default_value;
    }
    wstring& delete(wstring& str, int position) {
        int len = wcslen(str);
        
        if(position < 0) {
            position += len;
        }

        if(position < 0) {
            position = 0;
        }

        if(position >= len) {
            position = len -1;

            if(position < 0) {
                return str;
            }
        }

        wstring sub_str = str.substring(position+1, -1);

        ncmemcpy(str + position, sub_str, sizeof(wchar_t)*(sub_str.length()+1));
        
        return str;
    }
    wstring& delete_range(wstring& str, int head, int tail) {
        int len = wcslen(str);

        if(len == 0) {
            return str;
        }
        
        if(head < 0) {
           head += len;
        }
        
        if(tail < 0) {
           tail += len + 1;
        }

        if(head < 0) {
            head = 0;
        }

        if(tail < 0) {
            return str;
        }

        if(tail >= len) {
            tail = len;
        }
        
        wstring sub_str = str.substring(tail, -1);

        ncmemcpy(str + head, sub_str, sizeof(wchar_t)*(sub_str.length()+1));

        return str;
    }
    wstring printable(wstring& str)
    {
        int len = str.length();
        wstring result = new wchar_t[len*2+1];

        int n = 0;
        for(int i=0; i<len; i++) {
            wchar_t c = str[i];

            if((c >= 0 && c < ' ') 
                || c == 127)
            {
                result[n++] = '^';
                result[n++] = c + 'A' - 1;
            }
            else {
                result[n++] = c;
            }
        }

        result[n] = '\0'

        return result;
    }
    
    void replace(wstring& self, int index, wchar_t c) {
        int len = wcslen(self);

        if(wcscmp(self, wstring("")) == 0) {
            return;
        }
        
        if(index < 0) {
           index += len;
        }

        if(index >= len) {
            index = len-1;
        }

        if(index < 0) {
            index = 0;
        }
        
        self[index] = c;
    }
    
    wchar_t item(wstring& self, int index, wchar_t default_value)
    {
        int len = wcslen(self);

        if(wcscmp(self, wstring("")) == 0) {
            return default_value;
        }
        
        if(index < 0) {
           index += len;
        }

        if(index < 0 || index >= len) {
            return default_value;
        }
        
        
        return self[index];
    }
}

char* xstrncpy(char* des, char* src, int size)
{
    char* result;

    result = strncpy(des, src, size-1);
    des[size-1] = 0;

    return result;
}

char* xstrncat(char* des, char* str, int size)
{
    char* result;

    result = strncat(des, str, size-1);
    des[size-1] = 0;

    return result;
}

nregex regex(char* str, bool ignore_case, bool multiline, bool global, bool extended, bool dotall, bool anchored, bool dollar_endonly, bool ungreedy)
{
    var result = new regex_struct;

    const char* err;
    int erro_ofs;

    int options = PCRE_UTF8 | (ungreedy ? PCRE_UNGREEDY:0);
    //int options = PCRE_UTF8 | (ignore_case ? PCRE_CASELESS:0) | (multiline ? PCRE_MULTILINE : 0) | (extended ? PCRE_EXTENDED :0) | (dotall ? PCRE_DOTALL :0) | (dollar_endonly ? PCRE_DOLLAR_ENDONLY:0) | (ungreedy ? PCRE_UNGREEDY:0);

    //result.regex = pcre_compile(str, options, &err, &erro_ofs, NULL);

    result.str = string(str);
    result.ignore_case = ignore_case;
    result.multiline = multiline;
    result.global = global;
    result.extended = extended;
    result.dotall = dotall;
    result.anchored = anchored;
    result.dollar_endonly = dollar_endonly;
    result.ungreedy;
    result.options = options;

    return result;
}
*/
