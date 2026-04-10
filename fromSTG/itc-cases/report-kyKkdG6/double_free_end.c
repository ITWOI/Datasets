#include "header_func.h"
extern void double_free_006 (){
    char *ptr = (char *)malloc(sizeof(char));
    int flag = 1;
    while (flag)
        {
            free(ptr);
            flag--;
        }
    free(ptr);
}
