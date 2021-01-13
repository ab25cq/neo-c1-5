//#include <stdio.h>

typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;

struct __pthread_mutex_s
{
  short __spins; short __elision;
  __pthread_list_t __list;
};

int main()
{
    char path[123];

    struct __pthread_mutex_s aaa;


    return 0;
}
