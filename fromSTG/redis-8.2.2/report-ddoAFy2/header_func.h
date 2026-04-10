#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

void *zmalloc(size_t size);


void _serverAssert(const char *estr, const char *file, int line);


size_t lzf_compress(const void *const in_data, size_t in_len, void *out_data, size_t out_len);


void zfree(void *ptr);


void *zrealloc(void *ptr, size_t size);


size_t lzf_decompress(const void *const in_data, size_t in_len, void *out_data, size_t out_len);

int __quicklistDecompressNode(quicklistNode *node) ;

int __quicklistCompressNode(quicklistNode *node) ;

void __quicklistCompress(const quicklist *quicklist, quicklistNode *node) ;

void __quicklistInsertNode(quicklist *quicklist, quicklistNode *old_node, quicklistNode *new_node, int after) ;

static const size_t optimization_level[] = {4096, 8192, 16384, 32768, 65536};
;
static size_t quicklistNodeNegFillLimit(int fill) ;

void quicklistNodeLimit(int fill, size_t *size, unsigned int *count) ;

static size_t packed_threshold = 0;
;
static int isLargeElement(size_t sz, int fill) ;

int quicklistNodeExceedsLimit(int fill, size_t new_sz, unsigned int new_count) ;

quicklistNode *quicklistCreateNode(void) ;


unsigned char *lpPrepend(unsigned char *lp, unsigned char *s, uint32_t slen);


unsigned char *lpNew(size_t capacity);

static quicklistNode *__quicklistCreateNode(int container, void *value, size_t sz) ;

static void __quicklistInsertPlainNode(quicklist *quicklist, quicklistNode *old_node, void *value, size_t sz, int after) ;

int _quicklistNodeAllowInsert(const quicklistNode *node, const int fill, const size_t sz) ;


size_t lpBytes(unsigned char *lp);

void _quicklistInsertNodeBefore(quicklist *quicklist, quicklistNode *old_node, quicklistNode *new_node) ;


unsigned char *lpAppend(unsigned char *lp, unsigned char *s, uint32_t slen);

void _quicklistInsertNodeAfter(quicklist *quicklist, quicklistNode *old_node, quicklistNode *new_node) ;

int quicklistPushHead(quicklist *quicklist, void *value, size_t sz) ;

int quicklistPushTail(quicklist *quicklist, void *value, size_t sz) ;

#endif