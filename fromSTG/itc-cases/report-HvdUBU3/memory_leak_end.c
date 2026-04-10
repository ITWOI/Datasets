#include "header_func.h"
extern void memory_leak_003 (){
    float *ptr = (float *)malloc(5 * sizeof(float));
    int *p = (int *)malloc(5 * sizeof(int));
    if (ptr != ((void *)0)) {
        ;
    }
}
