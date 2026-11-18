#include "header_func.h"
extern int memory_leak_002_func_001 (int flag){
    int ret;
    if (flag == 0) {
        ret = 0;
    } else
        ret = 1;
    return ret;
}
extern void memory_leak_002 (){
    double *dptr;
    int flag = 0;
    if (memory_leak_002_func_001(flag) == 0) {
        dptr = (double *)malloc(5 * sizeof(double));
        if (dptr != ((void *)0)) {
            *(dptr + 1) = 10.5;
        }
    }
    if (memory_leak_002_func_001(flag) != 0) {
    }
    ;
}
