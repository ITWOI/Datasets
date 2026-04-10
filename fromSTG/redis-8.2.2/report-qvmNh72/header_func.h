#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline unsigned char sdsType(const sds s) ;

dict *configs = ((void *)0);
;

dictEntry *dictFind(dict *d, const void *key);


void *dictGetVal(const dictEntry *de);


void *zmalloc(size_t size);


dict *dictCreate(dictType *type);


uint64_t dictSdsCaseHash(const void *key);


int dictSdsKeyCaseCompare(dictCmpCache *cache, const void *key1, const void *key2);


void dictSdsDestructor(dict *d, void *val);


void dictListDestructor(dict *d, void *val);

dictType optionToLineDictType = {dictSdsCaseHash, ((void *)0), ((void *)0), dictSdsKeyCaseCompare, dictSdsDestructor, dictListDestructor, ((void *)0)};
;
dictType optionSetDictType = {dictSdsCaseHash, ((void *)0), ((void *)0), dictSdsKeyCaseCompare, dictSdsDestructor, ((void *)0), ((void *)0)};
;

void *zrealloc(void *ptr, size_t size);

struct rewriteConfigState *rewriteConfigCreateState(void) ;

extern const char *SDS_NOINIT;
;

sds sdsnewlen(const void *init, size_t initlen);


void sdsfree(sds s);

void rewriteConfigReleaseState(struct rewriteConfigState *state) ;


sds *sdssplitlen(const char *s, ssize_t len, const char *sep, int seplen, int *count);

static inline size_t sdslen(const sds s) ;

void rewriteConfigAppendLine(struct rewriteConfigState *state, sds line) ;


sds *sdssplitargs(const char *line, int *argc);

static standardConfig *lookupConfig(const sds name) ;


sds sdscatsds(sds s, const sds t);


void sdsfreesplitres(sds *tokens, int count);


void sdstolower(sds s);


sds sdsnew(const char *init);


sds sdscatfmt(sds s, const char *fmt, ...);

void rewriteConfigAddLineNumberToOption(struct rewriteConfigState *state, sds option, int linenum) ;


sds sdstrim(sds s, const char *cset);

extern struct redisServer server;
;

sds sdsempty(void);


void *dictFetchValue(dict *d, const void *key);


void listDelNode(list *list, listNode *node);


int dictDelete(dict *d, const void *key);

void rewriteConfigMarkAsProcessed(struct rewriteConfigState *state, const char *option) ;


int raxNext(raxIterator *it);


sds sdscatlen(sds s, const void *t, size_t len);


void decrRefCount(robj *o);

int rewriteConfigRewriteLine(struct rewriteConfigState *state, const char *option, sds line, int force) ;


robj *ACLDescribeUser(user *u);


dictEntry *dictNext(dictIterator *iter);


void _serverLog(int level, const char *fmt, ...);


void *dictGetKey(const dictEntry *de);

struct rewriteConfigState *rewriteConfigReadOldFile(char *path) ;

void rewriteConfigUserOption(struct rewriteConfigState *state) ;

void rewriteConfigLoadmoduleOption(struct rewriteConfigState *state) ;

void rewriteConfigRemoveOrphaned(struct rewriteConfigState *state) ;

sds rewriteConfigGetContentFromState(struct rewriteConfigState *state) ;

int rewriteConfigOverwriteFile(char *configfile, sds content) ;


void addReplyError(client *c, const char *err);

int rewriteConfig(char *path, int force_write) ;


void addReplyErrorFormat(client *c, const char *fmt, ...);


void addReply(client *c, robj *obj);

#endif