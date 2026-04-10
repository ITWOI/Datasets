#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline unsigned char sdsType(const sds s) ;

static inline size_t sdslen(const sds s) ;


int string2ull(const char *s, unsigned long long *value);

int streamGenericParseIDOrReply(client *c, const robj *o, streamID *id, uint64_t missing_seq, int strict, int *seq_given) ;

int streamCompareID(streamID *a, streamID *b) ;


rax *raxNew(void);


int raxFind(rax *rax, unsigned char *s, size_t len, void **value);


void *zmalloc(size_t size);

void streamUpdateCGroupLastId(stream *s, streamCG *cg, streamID *id) ;


int raxTryInsert(rax *rax, unsigned char *s, size_t len, void *data, void **old);


int raxRemove(rax *rax, unsigned char *s, size_t len, void **old);


int getLongLongFromObjectOrReply(client *c, robj *o, long long *target, const char *msg);


void addReplyError(client *c, const char *err);


void addReplySubcommandSyntaxError(client *c);


kvobj *lookupKeyWrite(redisDb *db, robj *key);


int checkType(client *c, robj *o, int type);

streamCG *streamLookupCG(stream *s, sds groupname) ;


void addReplyErrorFormat(client *c, const char *fmt, ...);


void addReplyHelp(client *c, const char **help);

int streamParseStrictIDOrReply(client *c, robj *o, streamID *id, uint64_t missing_seq, int *seq_given) ;


void _serverAssert(const char *estr, const char *file, int line);


robj *createStreamObject(void);


kvobj *dbAdd(redisDb *db, robj *key, robj **valref);


void signalModifiedKey(client *c, redisDb *db, robj *key);


void addReply(client *c, robj *obj);


void notifyKeyspaceEvent(int type, const char *event, robj *key, int dbid);

int streamParseIDOrReply(client *c, robj *o, streamID *id, uint64_t missing_seq) ;

void streamDestroyCG(stream *s, streamCG *cg) ;


void signalKeyAsReady(redisDb *db, robj *key, int type);


void addReplyLongLong(client *c, long long ll);


uint64_t raxSize(rax *rax);

void streamDelConsumer(stream *s, streamCG *cg, streamConsumer *consumer) ;

streamCG *streamCreateCG(stream *s, char *name, size_t namelen, streamID *id, long long entries_read) ;

streamConsumer *streamCreateConsumer(streamCG *cg, sds name, robj *key, int dbid, int flags) ;

streamConsumer *streamLookupConsumer(streamCG *cg, sds name) ;

#endif