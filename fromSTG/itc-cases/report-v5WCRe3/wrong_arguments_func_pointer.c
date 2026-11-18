extern int wrong_arguments_func_pointer_003_func_001 (int flag){
    int ret = 0;
    if (flag == 0) {
        ret = 0;
    } else
        ret = 1;
    return ret;
}


extern void wrong_arguments_func_pointer_003 (){
    float f;
    ;
    if (wrong_arguments_func_pointer_003_func_001(0) == 0) {
        long (*fptr)(float *);
        long a;
        fptr = (long (*)(float *))wrong_arguments_func_pointer_003_func_002;
        a = fptr(&f);
    }
}


