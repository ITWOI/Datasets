#include "header_func.h"
static inline unsigned char sdsType (const sds s){
    unsigned char flags = s[-1];
    return flags & 7;
}
static inline size_t sdslen (const sds s){
    switch (sdsType(s)) {
      case 0:
        return (((unsigned char)(s[-1])) >> 3);
      case 1:
        return ((struct sdshdr8 *)((s) - (sizeof(struct sdshdr8))))->len;
      case 2:
        return ((struct sdshdr16 *)((s) - (sizeof(struct sdshdr16))))->len;
      case 3:
        return ((struct sdshdr32 *)((s) - (sizeof(struct sdshdr32))))->len;
      case 4:
        return ((struct sdshdr64 *)((s) - (sizeof(struct sdshdr64))))->len;
    }
    return 0;
}
static inline void sdssetlen (sds s, size_t newlen){
    switch (sdsType(s)) {
      case 0:
        {
            unsigned char *fp = ((unsigned char *)s) - 1;
            *fp = 0 | (newlen << 3);
        }
        break;
      case 1:
        ((struct sdshdr8 *)((s) - (sizeof(struct sdshdr8))))->len = newlen;
        break;
      case 2:
        ((struct sdshdr16 *)((s) - (sizeof(struct sdshdr16))))->len = newlen;
        break;
      case 3:
        ((struct sdshdr32 *)((s) - (sizeof(struct sdshdr32))))->len = newlen;
        break;
      case 4:
        ((struct sdshdr64 *)((s) - (sizeof(struct sdshdr64))))->len = newlen;
        break;
    }
}
