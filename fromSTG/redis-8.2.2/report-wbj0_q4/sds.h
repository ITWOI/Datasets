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
static inline void hi_sdssetlen (hisds s, size_t newlen){
    unsigned char flags = s[-1];
    switch (flags & 7) {
      case 0:
        {
            unsigned char *fp = ((unsigned char *)s) - 1;
            *fp = (unsigned char)(0 | (newlen << 3));
        }
        break;
      case 1:
        ((struct hisdshdr8 *)((s) - (sizeof(struct hisdshdr8))))->len = (uint8_t)newlen;
        break;
      case 2:
        ((struct hisdshdr16 *)((s) - (sizeof(struct hisdshdr16))))->len = (uint16_t)newlen;
        break;
      case 3:
        ((struct hisdshdr32 *)((s) - (sizeof(struct hisdshdr32))))->len = (uint32_t)newlen;
        break;
      case 4:
        ((struct hisdshdr64 *)((s) - (sizeof(struct hisdshdr64))))->len = (uint64_t)newlen;
        break;
    }
}
