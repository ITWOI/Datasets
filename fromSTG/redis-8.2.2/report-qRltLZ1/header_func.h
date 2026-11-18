#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
int lpStringToInt64(const char *s, unsigned long slen, int64_t *value) ;

static inline void lpEncodeIntegerGetType(int64_t v, unsigned char *intenc, uint64_t *enclen) ;

static inline uint32_t lpCurrentEncodedSizeUnsafe(unsigned char *p) ;

static inline unsigned long lpEncodeBacklenBytes(uint64_t l) ;


void _serverAssert(const char *estr, const char *file, int line);


void *zmalloc(size_t size);

static inline unsigned char *lpSkip(unsigned char *p) ;

static inline int lpEncodeGetType(unsigned char *ele, uint32_t size, unsigned char *intenc, uint64_t *enclen) ;

static inline unsigned long lpEncodeBacklen(unsigned char *buf, uint64_t l) ;


size_t je_malloc_usable_size(void *ptr);


void *zrealloc_usable(void *ptr, size_t size, size_t *usable);

static inline void lpEncodeString(unsigned char *buf, unsigned char *s, uint32_t len) ;

unsigned char *lpBatchInsert(unsigned char *lp, unsigned char *p, int where, listpackEntry *entries, unsigned int len, unsigned char **newp) ;

#endif