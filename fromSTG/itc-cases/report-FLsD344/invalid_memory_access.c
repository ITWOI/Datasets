extern void invalid_memory_access_003 (){
    invalid_memory_access_003_uni_001 *u = (invalid_memory_access_003_uni_001 *)malloc(5 * sizeof(invalid_memory_access_003_uni_001));
    invalid_memory_access_003_uni_001 *p = ((void *)0);
    if (u != ((void *)0)) {
        u->s1 = (invalid_memory_access_003_s_001 *)malloc(sizeof(invalid_memory_access_003_s_001));
        if (u->s1 != ((void *)0))
            u->s1->a = (int *)malloc(5 * sizeof(int));
        p = u;
        p->s1->a[0] = 1;
        ;
        ;
        ;
        ;
    }
}


