extern void invalid_memory_access_002 (){
    char *buf = ((void *)0);
    if (staticflag1) {
        buf = (char *)malloc(100 * sizeof(char));
        if (buf != ((void *)0)) {
            memset(buf, 'A', 100 - 1);
            buf[100 - 1] = '\x00';
            free(buf);
        }
    }
    if (staticflag1) {
        printf("String= %s", buf);
    }
}


