#include "header_func.h"
extern void free_nondynamic_allocated_memory_006 (){
    free_nondynamic_allocated_memory_struct_006 *new_struct = malloc(sizeof(free_nondynamic_allocated_memory_struct_006));
    free_nondynamic_allocated_memory_struct_006 str;
    new_struct->next = &str;
    free(new_struct->next);
}
