#include "header_func.h"
extern int invalid_memory_access_005_func_001 (int flag){
    int ret;
    if (flag == 0) {
        ret = 0;
    } else
        ret = 1;
    return ret;
}
extern void invalid_memory_access_005_func_002 (){
    invalid_memory_access_005_doubleptr_gbl = (char *)malloc(10 * sizeof(char));
    if (invalid_memory_access_005_doubleptr_gbl != ((void *)0))
        strcpy(invalid_memory_access_005_doubleptr_gbl, "TEST");
}
extern void invalid_memory_access_005_func_003 (){
    free(invalid_memory_access_005_doubleptr_gbl);
}
extern void invalid_memory_access_005_func_004 (){
    char s[10];
    strcpy(s, invalid_memory_access_005_doubleptr_gbl);
}
extern void invalid_memory_access_005 (){
    int flag = 10;
    if (invalid_memory_access_005_func_001(flag) == 0) {
        ;
    } else {
        invalid_memory_access_005_func_002();
    }
    if (invalid_memory_access_005_func_001(flag) == 0) {
        ;
    } else {
        invalid_memory_access_005_func_003();
    }
    if (invalid_memory_access_005_func_001(flag) == 0) {
        ;
    } else {
        invalid_memory_access_005_func_004();
    }
}
