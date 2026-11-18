#include "header_func.h"
extern void free_nondynamic_allocated_memory_003 (){
    char **ptr;
    char *ptr1 = "STRING";
    ptr = &ptr1;
    free(ptr);
}
