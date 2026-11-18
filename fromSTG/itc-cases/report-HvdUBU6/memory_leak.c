extern char * memory_leak_006_func_001 (int len){
    char *stringPtr = malloc(sizeof(char) * (len + 1));
    return stringPtr;
}


extern void memory_leak_006 (){
    char *str = "This is a string";
    char *str1 = memory_leak_006_func_001(strlen(str));
    if (str1 != ((void *)0)) {
        ;
    }
}


