#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline unsigned char sdsType(const sds s) ;


unsigned char *lpGet(unsigned char *p, int64_t *count, unsigned char *intbuf);


int string2ll(const char *s, size_t slen, long long *value);


void _serverAssert(const char *estr, const char *file, int line);


uint64_t intrev64(uint64_t v);

void streamEncodeID(void *buf, streamID *id) ;


int raxNext(raxIterator *it);


int raxPrev(raxIterator *it);

void streamDecodeID(void *buf, streamID *id) ;


unsigned char *lpFirst(unsigned char *lp);


unsigned char *lpNext(unsigned char *lp, unsigned char *p);

static inline int64_t lpGetIntegerIfValid(unsigned char *ele, int *valid) ;


unsigned char *lpLast(unsigned char *lp);


unsigned char *lpPrev(unsigned char *lp, unsigned char *p);

void streamIteratorStart(streamIterator *si, stream *s, streamID *start, streamID *end, int rev) ;

int streamIteratorGetID(streamIterator *si, streamID *id, int64_t *numfields) ;


void _serverPanic(const char *file, int line, const char *msg, ...);

extern const char *SDS_NOINIT;
;

sds sdsnewlen(const void *init, size_t initlen);

static inline void sdssetlen(sds s, size_t newlen) ;


sds sdscatfmt(sds s, const char *fmt, ...);


void addReplyBulkSds(client *c, sds s);

sds createStreamIDString(streamID *id) ;


robj *createObject(int type, void *ptr);

int streamIDEqZero(streamID *id) ;

int streamCompareID(streamID *a, streamID *b) ;

extern struct sharedObjectsStruct shared;
;

robj *createStringObject(const char *ptr, size_t len);

static inline size_t sdslen(const sds s) ;

robj *createObjectFromStreamID(streamID *id) ;

size_t streamReplyWithRangeFromConsumerPEL(client *c, stream *s, streamID *start, streamID *end, size_t count, streamConsumer *consumer);


void *addReplyDeferredLen(client *c);

int streamRangeHasTombstones(stream *s, streamID *start, streamID *end) ;

long long streamEstimateDistanceFromFirstEverEntry(stream *s, streamID *id) ;

void streamUpdateCGroupLastId(stream *s, streamCG *cg, streamID *id);


void addReplyArrayLen(client *c, long length);

void addReplyStreamID(client *c, streamID *id) ;

void streamIteratorGetField(streamIterator *si, unsigned char **fieldptr, unsigned char **valueptr, int64_t *fieldlen, int64_t *valuelen) ;


void addReplyBulkCBuffer(client *c, const void *p, size_t len);

void streamFreeNACK(streamNACK *na);


int raxRemove(rax *rax, unsigned char *s, size_t len, void **old);


mstime_t commandTimeSnapshot(void);


int raxInsert(rax *rax, unsigned char *s, size_t len, void *data, void **old);

listNode *streamLinkCGroupToEntry(stream *s, streamCG *cg, unsigned char *key);

void streamPropagateXCLAIM(client *c, robj *key, streamCG *group, robj *groupname, robj *id, streamNACK *nack) ;


void decrRefCount(robj *o);

streamNACK *streamCreateNACK(streamConsumer *consumer);


int raxTryInsert(rax *rax, unsigned char *s, size_t len, void *data, void **old);


int raxFind(rax *rax, unsigned char *s, size_t len, void **value);

void streamPropagateGroupID(client *c, robj *key, streamCG *group, robj *groupname) ;

size_t streamReplyWithRange(client *c, stream *s, streamID *start, streamID *end, size_t count, int rev, streamCG *group, streamConsumer *consumer, int flags, streamPropInfo *spi, unsigned long *propCount) ;


void addReplyNullArray(client *c);


int string2ull(const char *s, unsigned long long *value);

int streamGenericParseIDOrReply(client *c, const robj *o, streamID *id, uint64_t missing_seq, int strict, int *seq_given) ;


int getTimeoutFromObjectOrReply(client *c, robj *object, mstime_t *timeout, int unit);


int getLongLongFromObjectOrReply(client *c, robj *o, long long *target, const char *msg);


void addReplyErrorFormat(client *c, const char *fmt, ...);


void addReplyError(client *c, const char *err);


void addReplyErrorObject(client *c, robj *err);


void *zmalloc(size_t size);


int checkType(client *c, robj *o, int type);

streamCG *streamLookupCG(stream *s, sds groupname);

void streamLastValidID(stream *s, streamID *maxid) ;

int streamDecrID(streamID *id) ;

int streamParseStrictIDOrReply(client *c, robj *o, streamID *id, uint64_t missing_seq, int *seq_given) ;


kvobj *lookupKeyRead(redisDb *db, robj *key);

streamConsumer *streamLookupConsumer(streamCG *cg, sds name);

streamConsumer *streamCreateConsumer(streamCG *cg, sds name, robj *key, int dbid, int flags);

void streamPropagateConsumerCreation(client *c, robj *key, robj *groupname, sds consumername) ;

int streamIncrID(streamID *id) ;


void addReplyBulk(client *c, robj *obj);

extern struct redisServer server;
;

void setDeferredArrayLen(client *c, void *node, long length);


void setDeferredMapLen(client *c, void *node, long length);


void rewriteClientCommandArgument(client *c, int i, robj *newval);


void blockForKeys(client *c, int btype, robj **keys, int numkeys, mstime_t timeout, int unblock_on_nokey);


rax *raxNew(void);


list *listCreate(void);


void zfree(void *ptr);


sds sdsdup(const sds s);

#endif