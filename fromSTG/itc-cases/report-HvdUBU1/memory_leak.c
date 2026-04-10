extern void memory_leak_001_func_001 (int len, char **stringPtr){
    char *p = malloc(sizeof(char) * (len + 1));
    *stringPtr = p;
}


extern void memory_leak_001 (){
    char *str = "This is a string";
    char *str1;
    memory_leak_001_func_001(strlen(str), &str1);
    strcpy(str1, str);
}


