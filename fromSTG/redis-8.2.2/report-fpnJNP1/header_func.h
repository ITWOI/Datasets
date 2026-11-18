#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline unsigned char sdsType(const sds s) ;


void *zcalloc(size_t size);


void _serverAssert(const char *estr, const char *file, int line);


void sdsfree(sds s);


void zfree(void *ptr);


int sdsneedsrepr(const sds s);


sds sdscatrepr(sds s, const char *p, size_t len);


sds sdsempty(void);

static inline size_t sdslen(const sds s) ;


sds sdscatprintf(sds s, const char *fmt, ...);


sds sdscatlen(sds s, const void *t, size_t len);

extern struct redisServer server;
;

void listRewind(list *list, listIter *li);


listNode *listNext(listIter *iter);

sds aofInfoFormat(sds buf, aofInfo *ai) ;

sds appendAofInfoFromList(sds buf, list *aofList) ;

sds getAofManifestFileName(void) ;


sds makePath(char *path, char *filename);

sds getTempAofManifestFileName(void) ;


void _serverLog(int level, const char *fmt, ...);


int fsyncFileDir(const char *filename);

sds getAofManifestAsString(aofManifest *am) ;

int writeAofManifestFile(sds buf) ;

int aofFileExist(char *filename);


int dirCreateIfMissing(char *dname);

void aofInfoFree(aofInfo *ai) ;

aofInfo *aofInfoCreate(void) ;


sds sdsnew(const char *init);

int persistAofManifest(aofManifest *am) ;


int fileExist(char *filename);


client *createClient(connection *conn);

struct client *createAOFClient(void) ;


void rioInitWithFile(rio *r, FILE *fp);


int rdbLoadRio(rio *rdb, int rdbflags, rdbSaveInfo *rsi);


void loadingAbsProgress(off_t pos);


void loadingIncrProgress(off_t size);


void processEventsWhileBlocked(void);


void processModuleLoadingProgressEvent(int is_aof);


void *zmalloc(size_t size);


void freeClientArgv(client *c);


sds sdsnewlen(const void *init, size_t initlen);


robj *createObject(int type, void *ptr);


struct redisCommand *lookupCommand(robj **argv, int argc);


void multiCommand(client *c);


void execCommand(client *c);


void queueMultiCommand(client *c, uint64_t cmd_flags);


void debugDelay(int usec);

extern const char *SDS_NOINIT;
;

void freeClient(client *c);


void bioCreateCloseJob(int fd, int need_fsync, int need_reclaim_cache);


int dirExists(char *dname);

void aofUpgradePrepare(aofManifest *am) ;

int getBaseAndIncrAppendOnlyFilesNum(aofManifest *am);

off_t getBaseAndIncrAppendOnlyFilesSize(aofManifest *am, int *status);


void startLoading(size_t size, int rdbflags, int async);


void updateLoadingFileName(char *filename);

off_t getAppendOnlyFileSize(sds filename, int *status);


long long ustime(void);

int loadSingleAppendOnlyFile(char *filename) ;


void stopLoading(int success);


mstime_t mstime(void);


void latencyAddSample(const char *event, mstime_t latency);

#endif