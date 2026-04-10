#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline uint32_t lpCurrentEncodedSizeUnsafe(unsigned char *p) ;

static inline unsigned long lpEncodeBacklenBytes(uint64_t l) ;


void _serverAssert(const char *estr, const char *file, int line);

static inline unsigned char *lpSkip(unsigned char *p) ;

static inline void lpAssertValidEntry(unsigned char *lp, size_t lpbytes, unsigned char *p);

size_t lpBytes(unsigned char *lp);

unsigned char *lpFirst(unsigned char *lp) ;

unsigned char *lpNext(unsigned char *lp, unsigned char *p) ;


int ll2string(char *s, size_t len, long long value);

static inline unsigned char *lpGetWithBuf(unsigned char *p, int64_t *count, unsigned char *intbuf) ;

static inline uint32_t lpCurrentEncodedSizeBytes(const unsigned char encoding) ;

static inline uint64_t lpDecodeBacklen(unsigned char *p) ;

int lpValidateNext(unsigned char *lp, unsigned char **pp, size_t lpbytes) ;

unsigned long lpLength(unsigned char *lp) ;

unsigned char *lpGet(unsigned char *p, int64_t *count, unsigned char *intbuf) ;

extern FILE *stdout;
;
#endif