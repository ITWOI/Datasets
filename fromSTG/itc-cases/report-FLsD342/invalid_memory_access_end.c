#include "header_func.h"
extern void invalid_memory_access_001 (){
    int *ptr, a;
    int flag = 10;
    (flag == 10) ? (ptr = (int *)malloc(10 * sizeof(int))) : (a = 5);
    if (ptr != ((void *)0)) {
        (flag == 10) ? (*(ptr + 1) = 10) : (a = 100);
        if (flag == 10) {
            free(ptr);
        }
    }
    if (flag == 10)
        a = *(ptr + 1);
}
