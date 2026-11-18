extern void wrong_arguments_func_pointer_002 (){
    char *str;
    char *str1 = ((void *)0);
    void (*fptr)(char *);
    fptr = (void (*)(char *))wrong_arguments_func_pointer_002_func_001;
    fptr(str1);
    ;
    ;
    ;
}


