extern void free_nondynamic_allocated_memory_004 (){
    char *ptr = "a";
    int a = 2, b = 0;
    while (a > b)
        free(ptr);
}


