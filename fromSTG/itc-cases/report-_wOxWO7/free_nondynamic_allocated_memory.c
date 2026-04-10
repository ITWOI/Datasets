extern void free_nondynamic_allocated_memory_007 (){
    free_nondynamic_allocated_memory_struct_007 free_nondynamic_allocated_memory_st;
    free_nondynamic_allocated_memory_str = &free_nondynamic_allocated_memory_st;
    free(free_nondynamic_allocated_memory_str);
}


