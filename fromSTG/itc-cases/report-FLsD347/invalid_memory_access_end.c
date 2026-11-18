#include "header_func.h"
extern void invalid_memory_access_004_func_001 (int flag){
    if (flag > 0)
        invalid_memory_access_004_s_001_s_gbl = (invalid_memory_access_004_s_001 *)calloc(1, sizeof(invalid_memory_access_004_s_001));
}
extern int invalid_memory_access_004_func_002 (int flag){
    int i;
    switch (flag) {
      case 1:
        {
            if (invalid_memory_access_004_s_001_s_gbl != ((void *)0)) {
                invalid_memory_access_004_s_001_s_gbl->a = 10;
                invalid_memory_access_004_s_001_s_gbl->b = 10;
                invalid_memory_access_004_s_001_s_gbl->uninit = 10;
                free(invalid_memory_access_004_s_001_s_gbl);
            }
            break;
        }
      case 2:
        {
            if (invalid_memory_access_004_s_001_s_gbl != ((void *)0)) {
                invalid_memory_access_004_s_001_s_gbl->a = 20;
            }
            break;
        }
    }
    return invalid_memory_access_004_s_001_s_gbl->a;
}
extern void invalid_memory_access_004 (){
    int ret;
    invalid_memory_access_004_func_001(1);
    ret = invalid_memory_access_004_func_002(1);
}
