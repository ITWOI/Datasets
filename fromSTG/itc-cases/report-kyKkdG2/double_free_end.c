#include "header_func.h"
extern void double_free_002 (){
    char *ptr = (char *)malloc(sizeof(char));
    if (1)
        free(ptr);
    free(ptr);
}
