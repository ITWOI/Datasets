#include "header_func.h"
extern void free_nondynamic_allocated_memory_005 (){
    char *ptr = "a";
    int a = 0, b = 2;
    while (a < b)
        {
            a++;
            if (a == 1)
                free(ptr);
        }
}
