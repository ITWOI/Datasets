extern void double_free_function_004 (){
    free(double_free_function_004_gbl_ptr);
}


extern void double_free_004 (){
    double_free_function_004_gbl_ptr = (char *)malloc(sizeof(char));
    double_free_function_004();
    free(double_free_function_004_gbl_ptr);
}


