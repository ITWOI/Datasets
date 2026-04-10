extern void memory_leak_004 (){
    int *ptr = (int *)calloc(5, sizeof(int));
    int *p1 = (int *)calloc(5, sizeof(int));
    int *p2 = ((void *)0);
    p1 = ptr;
    p2 = p1;
    *(p2 + 4) = 1;
    free(ptr);
}


