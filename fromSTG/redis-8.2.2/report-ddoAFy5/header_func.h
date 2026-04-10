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

void __quicklistInsertNode(quicklist *quicklist, quicklistNode *old_node, quicklistNode *new_node, int after) ;

quicklistBookmark *_quicklistBookmarkFindByNode(quicklist *ql, quicklistNode *node);

void _quicklistBookmarkDelete(quicklist *ql, quicklistBookmark *bm);

void __quicklistDelNode(quicklist *quicklist, quicklistNode *node) ;


unsigned char *lpDelete(unsigned char *lp, unsigned char *p, unsigned char **newp);


size_t lpBytes(unsigned char *lp);


unsigned char *lpReplace(unsigned char *lp, unsigned char **p, unsigned char *s, uint32_t slen);

void quicklistInsertAfter(quicklistIter *iter, quicklistEntry *entry, void *value, const size_t sz);

quicklistNode *_quicklistSplitNode(quicklistNode *node, int offset, int after);

int quicklistDelIndex(quicklist *quicklist, quicklistNode *node, unsigned char **p) ;

quicklistNode *_quicklistMergeNodes(quicklist *quicklist, quicklistNode *center);


unsigned char *lpSeek(unsigned char *lp, long index);

quicklistIter *quicklistGetIteratorEntryAtIdx(quicklist *quicklist, const long long index, quicklistEntry *entry);

void quicklistReplaceEntry(quicklistIter *iter, quicklistEntry *entry, void *data, size_t sz) ;

void quicklistReleaseIterator(quicklistIter *iter);


unsigned char *lpMerge(unsigned char **first, unsigned char **second);


unsigned long lpLength(unsigned char *lp);

int _quicklistNodeAllowMerge(const quicklistNode *a, const quicklistNode *b, const int fill) ;

quicklistNode *_quicklistListpackMerge(quicklist *quicklist, quicklistNode *a, quicklistNode *b) ;


unsigned char *lpDeleteRange(unsigned char *lp, long index, unsigned long num);

static void __quicklistInsertPlainNode(quicklist *quicklist, quicklistNode *old_node, void *value, size_t sz, int after) ;

int _quicklistNodeAllowInsert(const quicklistNode *node, const int fill, const size_t sz) ;


unsigned char *lpInsertString(unsigned char *lp, unsigned char *s, uint32_t slen, unsigned char *p, int where, unsigned char **newp);


unsigned char *lpAppend(unsigned char *lp, unsigned char *s, uint32_t slen);

void _quicklistInsert(quicklistIter *iter, quicklistEntry *entry, void *value, const size_t sz, int after) ;

quicklistIter *quicklistGetIterator(quicklist *quicklist, int direction) ;


unsigned char *lpNext(unsigned char *lp, unsigned char *p);


unsigned char *lpPrev(unsigned char *lp, unsigned char *p);


unsigned char *lpGetValue(unsigned char *p, unsigned int *slen, long long *lval);

int quicklistNext(quicklistIter *iter, quicklistEntry *entry) ;

quicklistIter *quicklistGetIteratorAtIdx(quicklist *quicklist, const int direction, const long long idx) ;

#endif