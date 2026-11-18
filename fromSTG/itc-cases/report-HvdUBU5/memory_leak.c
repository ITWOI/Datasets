extern void memory_leak_005 (){
    memory_leak_005_uni_001 *u = (memory_leak_005_uni_001 *)malloc(5 * sizeof(memory_leak_005_uni_001));
    memory_leak_005_uni_001 *p = (memory_leak_005_uni_001 *)malloc(5 * sizeof(memory_leak_005_uni_001));
    p = u;
    p->s1.a = 1;
    free(u);
}


