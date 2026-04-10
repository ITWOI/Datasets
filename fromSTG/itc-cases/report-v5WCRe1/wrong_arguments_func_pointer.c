extern void wrong_arguments_func_pointer_001 (){
    int (*func)(int);
    int ret;
    func = (int (*)(int))wrong_arguments_func_pointer_001_func_001;
    ret = func(5);
}


