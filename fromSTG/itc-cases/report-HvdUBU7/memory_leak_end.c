#include "header_func.h"
extern void memory_leak_007_func_001 (int len){
    memory_leak_007_gbl_ptr = ((void *)0);
    if (a == 'a')
        memory_leak_007_gbl_ptr = malloc(sizeof(char) * (len + 1));
}
extern void memory_leak_007 (){
    char *str = "This is a string";
    memory_leak_007_func_001(strlen(str));
    strcpy(memory_leak_007_gbl_ptr, str);
}
