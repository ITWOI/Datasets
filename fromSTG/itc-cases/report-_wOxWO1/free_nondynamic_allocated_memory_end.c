#include "header_func.h"
extern void free_nondynamic_allocated_memory_001 (){
    char *ptr = "a";
    int flag = 1;
    if (flag > 0)
        free(ptr);
}
