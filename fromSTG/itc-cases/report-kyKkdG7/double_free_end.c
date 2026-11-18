#include "header_func.h"
extern void double_free_007 (){
    char *ptr = (char *)malloc(sizeof(char));
    int a = 0;
    for (a = 0; a < 2; a++) {
        free(ptr);
    }
}
