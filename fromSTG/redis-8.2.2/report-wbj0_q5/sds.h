#include "header_func.h"
static inline size_t hi_sdslen (const hisds s){
    unsigned char flags = s[-1];
    switch (flags & 7) {
      case 0:
        return ((flags) >> 3);
      case 1:
        return ((struct hisdshdr8 *)((s) - (sizeof(struct hisdshdr8))))->len;
      case 2:
        return ((struct hisdshdr16 *)((s) - (sizeof(struct hisdshdr16))))->len;
      case 3:
        return ((struct hisdshdr32 *)((s) - (sizeof(struct hisdshdr32))))->len;
      case 4:
        return ((struct hisdshdr64 *)((s) - (sizeof(struct hisdshdr64))))->len;
    }
    return 0;
}
