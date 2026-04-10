#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static long long ustime(void) ;


hisds hi_sdsnew(const char *init);


hisds hi_sdscatprintf(hisds s, const char *fmt, ...);


hisds hi_sdsempty(void);

static int cliConnect(int flags);

static redisContext *context;
;

void *redisCommand(redisContext *c, const char *format, ...);


void freeReplyObject(void *reply);


void *zrealloc(void *ptr, size_t size);


void *zmalloc(size_t size);


void hi_sdstoupper(hisds s);


hisds hi_sdscat(hisds s, const char *t);

static int helpEntriesLen = 0;
;
static helpEntry *helpEntries = ((void *)0);
;
static void cliAddCommandDocArg(cliCommandArg *cmdArg, redisReply *argMap);


void *zcalloc(size_t size);

static void cliMakeCommandDocArgs(redisReply *arguments, cliCommandArg *result) ;

static void cliFillInCommandHelpEntry(helpEntry *help, char *cmdname, char *subcommandname) ;


int dictAdd(dict *d, void *key, void *val);


void hi_sdsfree(hisds s);

static hisds makeHint(char **inputargv, int inputargc, int cmdlen, struct commandDocs docs);

static helpEntry *cliInitCommandHelpEntry(char *cmdname, char *subcommandname, helpEntry *next, redisReply *specs, dict *groups) ;


hisds hi_sdsdup(const hisds s);


void dictInitIterator(dictIterator *iter, dict *d);


dictEntry *dictNext(dictIterator *iter);


void *dictGetKey(const dictEntry *de);

static int versionIsSupported(hisds version, hisds since) ;

static void removeUnsupportedArgs(struct cliCommandArg *args, int *numargs, hisds version) ;

static helpEntry *cliLegacyInitCommandHelpEntry(char *cmdname, char *subcommandname, helpEntry *next, struct commandDocs *command, dict *groups, hisds version) ;

static size_t cliLegacyCountCommands(struct commandDocs *commands, hisds version) ;

static struct config config;
;

hisds hi_sdsnewlen(const void *init, size_t initlen);

static hisds cliGetServerVersion(void) ;

extern struct commandDocs redisCommandTable[];
;
int cliLegacyInitCommandHelpEntries(struct commandDocs *commands, dict *groups, hisds version) ;

void cliInitGroupHelpEntries(dict *groups) ;

static uint64_t dictSdsHash(const void *key) ;

static int dictSdsKeyCompare(dictCmpCache *cache, const void *key1, const void *key2) ;

static void dictSdsDestructor(dict *d, void *val) ;


dict *dictCreate(dictType *type);

static void cliLegacyInitHelp(dict *groups) ;

static void cliLegacyIntegrateHelp(void) ;

static size_t cliCountCommands(redisReply *commandTable) ;

void cliInitCommandHelpEntries(redisReply *commandTable, dict *groups) ;

static void cliOutputGenericHelp(void) ;

static void cliInitHelp(void) ;

static inline size_t hi_sdslen(const hisds s) ;

static void clearMatchedArgs(cliCommandArg *args, int numargs) ;

static hisds addHintForArgument(hisds hint, cliCommandArg *arg);

static hisds addSeparator(hisds str, size_t *len, char *separator, int is_last) ;

static hisds sdscat_orempty(hisds params, const char *value) ;

static hisds addHintForArguments(hisds hint, cliCommandArg *args, int numargs, char *separator) ;

static hisds addHintForRepeatedArgument(hisds hint, cliCommandArg *arg) ;

static int matchArgs(char **words, int numwords, cliCommandArg *args, int numargs);

static int matchArg(char **nextword, int numwords, cliCommandArg *arg);

static int matchToken(char **nextword, cliCommandArg *arg) ;

static int matchNoTokenArg(char **nextword, int numwords, cliCommandArg *arg) ;

static int matchArgOnce(char **nextword, int numwords, cliCommandArg *arg) ;

static int matchOneOptionalArg(char **words, int numwords, cliCommandArg *args, int numargs, int *matchedarg) ;

static int matchOptionalArgs(char **words, int numwords, cliCommandArg *args, int numargs) ;


hisds *hi_sdssplitargs(const char *line, int *argc);

static helpEntry *findHelpEntry(int argc, char **argv) ;

void cliRestoreTTY(void) ;

static int orig_termios_saved = 0;
;
static struct termios orig_termios;
;
static void cliRefreshPrompt(void) ;


void redisFree(redisContext *c);


redisContext *redisConnectWrapper(const char *ip, int port, const struct timeval tv);


redisContext *redisConnectUnixWrapper(const char *path, const struct timeval tv);


int cliSecureConnection(redisContext *c, cliSSLconfig config, const char **err);


int anetKeepAlive(char *err, int fd, int interval);

static int cliAuth(redisContext *ctx, char *user, char *auth) ;

static int cliSelect(void) ;

static int cliSwitchProto(void) ;

static int cliIsMultilineValueTTY(redisReply *r) ;


hisds hi_sdscatrepr(hisds s, const char *p, size_t len);


hisds hi_sdscatlen(hisds s, const void *t, size_t len);

static hisds cliFormatReplyTTY(redisReply *r, char *prefix) ;


int hi_sdsrange(hisds s, ssize_t start, ssize_t end);

int isColorTerm(void) ;


hisds hi_sdscatfmt(hisds s, const char *fmt, ...);

hisds sdscatcolor(hisds o, char *s, size_t len, char *color) ;

hisds sdsCatColorizedLdbReply(hisds o, char *s, size_t len) ;

static hisds cliFormatReplyRaw(redisReply *r) ;

static hisds cliFormatReplyCSV(redisReply *r) ;


hisds escapeJsonString(hisds s, const char *p, size_t len);

static hisds jsonStringOutput(hisds out, const char *p, int len, int mode) ;

static hisds cliFormatReplyJson(hisds out, redisReply *r, int mode) ;


hisds hi_sdscatsds(hisds s, const hisds t);


int redisGetReply(redisContext *c, void **reply);

static void cliPrintContextError(void) ;

static hisds cliFormatReply(redisReply *reply, int mode, int verbatim) ;

extern FILE *stdout;
;
static void cliPressAnyKeyTTY(void) ;


int redisGetReplyFromReader(redisContext *c, void **reply);

static int cliReadReply(int output_raw_strings) ;


int redisAppendCommandArgv(redisContext *c, int argc, const char **argv, const size_t *argvlen);


void zfree(void *ptr);


redisPushFn *redisSetPushCallback(redisContext *c, redisPushFn *fn);

static void slaveMode(int send_sync);

int isPubsubPush(redisReply *r) ;

static void cliPushHandler(void *privdata, void *reply) ;


void *redisvCommand(redisContext *c, const char *format, va_list ap);

static void usage(int err);


void parseRedisUri(const char *uri, const char *tool_name, cliConnInfo *connInfo, int *tls_flag);


hisds unquoteCString(char *str);

int *spectrum_palette;
;
int spectrum_palette_mono[] = {0, 233, 234, 235, 237, 239, 241, 243, 245, 247, 249, 251, 253};
;
int spectrum_palette_size;
;
int spectrum_palette_mono_size = 13;
;
static int createClusterManagerCommand(char *cmdname, int argc, char **argv);


hisds cliVersion(void);

extern FILE *stdin;
;
static void cliOutputHelp(int argc, char **argv) ;

static int cliSendAsking(void) ;

static int cliSendCommand(int argc, char **argv, long repeat) ;

static int issueCommandRepeat(int argc, char **argv, long repeat) ;


void *hi_sds_malloc(size_t size);

static struct pref pref;
;
static hisds getDotfilePath(char *envoverride, char *dotfilename) ;

void cliSetPreferences(char **argv, int argc, int interactive) ;


void hi_sdsfreesplitres(hisds *tokens, int count);


int linenoiseHistoryLoad(const char *filename);

void cliLoadPreferences(void) ;


char *linenoise(const char *prompt);

static hisds *cliSplitArgs(char *line, int *argc) ;


int linenoiseHistoryAdd(const char *line, int is_sensitive);


int linenoiseHistorySave(const char *filename);


void linenoiseFree(void *ptr);


void linenoiseClearScreen(void);

static long long mstime(void) ;

static void cliWaitForMessagesOrStdin(void) ;

static int isSensitiveCommand(int argc, char **argv) ;


hisds *getSdsArrayFromArgv(int argc, char **argv, int quoted);


void *hi_sds_realloc(void *ptr, size_t size);


hisds readArgFromStdin(void);

static int issueCommand(int argc, char **argv) ;

static void repl(void) ;

static int clusterManagerCommandCreate(int argc, char **argv);

static int clusterManagerCommandCheck(int argc, char **argv);

static int clusterManagerCommandInfo(int argc, char **argv);

static int clusterManagerCommandFix(int argc, char **argv);

static int clusterManagerCommandReshard(int argc, char **argv);

static int clusterManagerCommandRebalance(int argc, char **argv);

static int clusterManagerCommandAddNode(int argc, char **argv);

static int clusterManagerCommandDeleteNode(int argc, char **argv);

static int clusterManagerCommandCall(int argc, char **argv);

static int clusterManagerCommandSetTimeout(int argc, char **argv);

static int clusterManagerCommandImport(int argc, char **argv);

static int clusterManagerCommandBackup(int argc, char **argv);

static int clusterManagerCommandHelp(int argc, char **argv);

clusterManagerCommandDef clusterManagerCommands[] = {{"create", clusterManagerCommandCreate, -1, "host1:port1 ... hostN:portN", "replicas <arg>"}, {"check", clusterManagerCommandCheck, -1, "<host:port> or <host> <port> - separated by either colon or space", "search-multiple-owners"}, {"info", clusterManagerCommandInfo, -1, "<host:port> or <host> <port> - separated by either colon or space", ((void *)0)}, {"fix", clusterManagerCommandFix, -1, "<host:port> or <host> <port> - separated by either colon or space", "search-multiple-owners,fix-with-unreachable-masters"}, {"reshard", clusterManagerCommandReshard, -1, "<host:port> or <host> <port> - separated by either colon or space", "from <arg>,to <arg>,slots <arg>,yes,timeout <arg>,pipeline <arg>,replace"}, {"rebalance", clusterManagerCommandRebalance, -1, "<host:port> or <host> <port> - separated by either colon or space", "weight <node1=w1...nodeN=wN>,use-empty-masters,timeout <arg>,simulate,pipeline <arg>,threshold <arg>,replace"}, {"add-node", clusterManagerCommandAddNode, 2, "new_host:new_port existing_host:existing_port", "slave,master-id <arg>"}, {"del-node", clusterManagerCommandDeleteNode, 2, "host:port node_id", ((void *)0)}, {"call", clusterManagerCommandCall, -2, "host:port command arg arg .. arg", "only-masters,only-replicas"}, {"set-timeout", clusterManagerCommandSetTimeout, 2, "host:port milliseconds", ((void *)0)}, {"import", clusterManagerCommandImport, 1, "host:port", "from <arg>,from-user <arg>,from-pass <arg>,from-askpass,copy,replace"}, {"backup", clusterManagerCommandBackup, 2, "host:port backup_directory", ((void *)0)}, {"help", clusterManagerCommandHelp, 0, ((void *)0), ((void *)0)}};
;
static int parseClusterNodeAddress(char *addr, char **ip_ptr, int *port_ptr, int *bus_port_ptr) ;


void listRewind(list *list, listIter *li);


listNode *listNext(listIter *iter);

static void freeClusterManagerNode(clusterManagerNode *node) ;


void listRelease(list *list);

static void freeClusterManagerNodeFlags(list *flags) ;

static struct clusterManager cluster_manager;
;
static void clusterManagerNodeResetSlots(clusterManagerNode *node);


size_t redis_strlcpy(char *dst, const char *src, size_t dsize);

static void clusterManagerLog(int level, const char *fmt, ...);

static int clusterManagerCheckRedisReply(clusterManagerNode *n, redisReply *r, char **err) ;


hisds hi_sdscpy(hisds s, const char *t);


int hi_sdscmp(const hisds s1, const hisds s2);

static redisReply *clusterManagerGetNodeRedisInfo(clusterManagerNode *node, char **err) ;

static long getLongInfoField(char *info, char *field);


void *dictGetVal(const dictEntry *de);


int dictReplace(dict *d, void *key, void *val);


void dictResetIterator(dictIterator *iter);


void dictRelease(dict *d);

static dictType clusterManagerDictType = {dictSdsHash, ((void *)0), ((void *)0), dictSdsKeyCompare, ((void *)0), dictSdsDestructor, ((void *)0)};
;

dictEntry *dictFind(dict *d, const void *key);

static int clusterManagerGetAntiAffinityScore(clusterManagerNodeArray *ipnodes, int ip_count, clusterManagerNode ***offending, int *offending_len) ;

static hisds clusterManagerNodeSlotsString(clusterManagerNode *node) ;

static hisds clusterManagerNodeFlagString(clusterManagerNode *node) ;


uint16_t crc16(const char *buf, int len);

static hisds clusterManagerNodeInfo(clusterManagerNode *node, int indent) ;


hisds hi_sdsfromlonglong(long long value);

static clusterManagerNode *clusterManagerNodeByName(const char *name) ;


char *zstrdup(const char *s);

static clusterManagerNode *clusterManagerGetSlotOwner(clusterManagerNode *n, int slot, char **err) ;

static int clusterManagerStartTransaction(clusterManagerNode *node) ;

static int clusterManagerDelSlot(clusterManagerNode *node, int slot, int ignore_unassigned_err) ;

static int clusterManagerAddSlot(clusterManagerNode *node, int slot) ;

static int clusterManagerClearSlotStatus(clusterManagerNode *node, int slot) ;

static int clusterManagerBumpEpoch(clusterManagerNode *node) ;

static int clusterManagerExecTransaction(clusterManagerNode *node, clusterManagerOnReplyError onerror) ;

static int clusterManagerOnSetOwnerErr(redisReply *reply, clusterManagerNode *n, int bulk_idx) ;


list *listAddNodeTail(list *list, void *value);

static redisReply *clusterManagerMigrateKeysInReply(clusterManagerNode *source, clusterManagerNode *target, redisReply *reply, int replace, int timeout, char *dots) ;

static int clusterManagerSetSlot(clusterManagerNode *node1, clusterManagerNode *node2, int slot, const char *status, char **err) ;

static int clusterManagerCompareKeysValues(clusterManagerNode *n1, clusterManagerNode *n2, redisReply *keys_reply, list *diffs) ;


list *listCreate(void);

static int clusterManagerMigrateKeysInSlot(clusterManagerNode *source, clusterManagerNode *target, int slot, int timeout, int pipeline, int verbose, char **err) ;

static int clusterManagerAddSlots(clusterManagerNode *node, char **err) ;

static int clusterManagerIsConfigConsistent(void);


void listEmpty(list *list);

static dict *clusterManagerGetLinkStatus(void);

static clusterManagerNode *clusterManagerNewNode(char *ip, int port, int bus_port) ;

static int clusterManagerNodeConnect(clusterManagerNode *node) ;

static int clusterManagerNodeIsCluster(clusterManagerNode *node, char **err) ;

static void clusterManagerPrintNotClusterNodeError(clusterManagerNode *node, char *err);

static int clusterManagerNodeLoadInfo(clusterManagerNode *node, int opts, char **err) ;

int clusterManagerSlotCompare(const void *slot1, const void *slot2) ;

static hisds clusterManagerGetConfigSignature(clusterManagerNode *node) ;

void dictListDestructor(dict *d, void *val) ;

static dictType clusterManagerLinkDictType = {dictSdsHash, ((void *)0), ((void *)0), dictSdsKeyCompare, dictSdsDestructor, dictListDestructor, ((void *)0)};
;
static list *clusterManagerGetDisconnectedLinks(clusterManagerNode *node) ;

static void clusterManagerPrintSlotsList(list *slots) ;

static int confirmWithYes(char *msg, int ignore_force) ;

static int clusterManagerSetSlotOwner(clusterManagerNode *owner, int slot, int do_clear) ;

static clusterManagerNode *clusterManagerNodeMasterRandom(void) ;

dict *clusterManagerUncoveredSlots = ((void *)0);
;
static int clusterManagerMoveSlot(clusterManagerNode *source, clusterManagerNode *target, int slot, int opts, char **err) ;

static clusterManagerNode *clusterManagerGetNodeWithMostKeysInSlot(list *nodes, int slot, char **err) ;

static void clusterManagerRemoveNodeFromList(list *nodelist, clusterManagerNode *node) ;

static int clusterManagerCountKeysInSlot(clusterManagerNode *node, int slot) ;

static void clusterManagerShowNodes(void) ;

static void clusterManagerOnError(hisds err) ;

static int clusterManagerFixOpenSlot(int slot) ;

static int clusterManagerGetCoveredSlots(char *all_slots) ;

static int clusterManagerFixSlotsCoverage(char *all_slots) ;

static int clusterManagerFixMultipleSlotOwners(int slot, list *owners) ;

static void freeClusterManager(void) ;

static int clusterManagerNodeIsEmpty(clusterManagerNode *node, char **err) ;

static void clusterManagerPrintNotEmptyNodeError(clusterManagerNode *node, char *err) ;

static void clusterManagerNodeArrayInit(clusterManagerNodeArray *array, int alloc_len) ;

static void clusterManagerNodeArrayAdd(clusterManagerNodeArray *array, clusterManagerNode *node) ;

static void clusterManagerNodeArrayShift(clusterManagerNodeArray *array, clusterManagerNode **nodeptr) ;

static void clusterManagerNodeArrayReset(clusterManagerNodeArray *array) ;

static void clusterManagerOptimizeAntiAffinity(clusterManagerNodeArray *ipnodes, int ip_count) ;


int anetResolve(char *err, char *host, char *ipbuf, size_t ipbuf_len, int flags);

static void clusterManagerWaitForClusterJoin(void) ;

static int clusterManagerLoadInfoFromNode(clusterManagerNode *node) ;

static int clusterManagerCheckCluster(int quiet) ;

static int clusterManagerFlushNodeConfig(clusterManagerNode *node, char **err) ;

static int getClusterHostFromCmdArgs(int argc, char **argv, char **ip_ptr, int *port_ptr) ;

static clusterManagerNode *clusterManagerNodeWithLeastReplicas(void) ;

static clusterManagerNode *clusterNodeForResharding(char *id, clusterManagerNode *target, int *raise_err) ;

static list *clusterManagerComputeReshardTable(list *sources, int numslots) ;

static clusterManagerNode *clusterManagerNodeByAbbreviatedName(const char *name) ;

static void clusterManagerReleaseReshardTable(list *table) ;

static redisReply *reconnectingRedisCommand(redisContext *c, const char *fmt, ...) ;

static unsigned int clusterManagerKeyHashSlot(char *key, int keylen) ;

static void getRDB(clusterManagerNode *node);

static hisds clusterManagerNodeGetJSON(clusterManagerNode *node, unsigned long error_count) ;

static void latencyModePrint(long long min, long long max, double avg, long long count) ;

void showLatencyDistLegend(void) ;

void showLatencyDistSamples(struct distsamples *samples, long long tot) ;

int sendReplconf(const char *arg1, const char *arg2) ;


ssize_t cliWriteConn(redisContext *c, const char *buf, size_t buf_len);

static ssize_t readConn(redisContext *c, char *buf, size_t len) ;

unsigned long long sendSync(redisContext *c, int send_sync, char *out_eof, int *out_full_mode) ;

static hisds clusterManagerGetNodeRDBFilename(clusterManagerNode *node) ;

static typeinfo *typeinfo_add(dict *types, char *name, typeinfo *type_template) ;

typeinfo type_other = {"other", ((void *)0), "?"};
;
void type_free(dict *d, void *val) ;

static dictType typeinfoDictType = {dictSdsHash, ((void *)0), ((void *)0), dictSdsKeyCompare, ((void *)0), type_free, ((void *)0)};
;
typeinfo type_string = {"string", "STRLEN", "bytes"};
;
typeinfo type_list = {"list", "LLEN", "items"};
;
typeinfo type_set = {"set", "SCARD", "members"};
;
typeinfo type_hash = {"hash", "HLEN", "fields"};
;
typeinfo type_zset = {"zset", "ZCARD", "members"};
;
typeinfo type_stream = {"stream", "XLEN", "entries"};
;
static int getDbSize(void) ;

static void sendReadOnly(void) ;

static redisReply *sendScan(unsigned long long *it) ;

static void getKeyTypes(dict *types_dict, redisReply *keys, typeinfo **types) ;

static void getKeySizes(redisReply *keys, typeinfo **types, unsigned long long *sizes, int memkeys, long long memkeys_samples) ;

static int displayKeyStatsProgressbar(unsigned long long sampled, unsigned long long total_keys);

int cleanPrintfln(char *fmt, ...) ;

static volatile sig_atomic_t force_cancel_loop = 0;
;
static void getKeyFreqs(redisReply *keys, unsigned long long *freqs) ;

static char *getInfoField(char *info, char *field) ;

static int getDatabases(void) ;

char *bytesToHuman(char *s, size_t size, long long n) ;

void LRUTestGenKey(char *buf, size_t buflen) ;


int redisAppendCommand(redisContext *c, const char *format, ...);

extern FILE *stderr;
;
unsigned long compute_something_fast(void) ;

static hisds getHintForInput(const char *charinput) ;


hisds hi_sdstrim(hisds s, const char *cset);

hisds readHintSuiteLine(char buf[], size_t size, FILE *fp) ;

static inline void hi_sdssetlen(hisds s, size_t newlen) ;


_Bool hdr_iter_next(struct hdr_iter *iter);


double hdr_mean(const struct hdr_histogram *h);


double hdr_stddev(const struct hdr_histogram *h);

static key_info *createKeySizeInfo(char *key_name, size_t key_name_len, char *key_type, unsigned long long size) ;

static int displayKeyStatsTopSizes(list *top_key_sizes, unsigned long top_sizes_limit) ;

static int displayKeyStatsSizeType(dict *memkeys_types_dict) ;

static int displayKeyStatsLengthType(dict *bigkeys_types_dict) ;

static void sizeDistInit(size_dist *dist, size_dist_entry *distribution) ;


int hdr_init(int64_t lowest_discernible_value, int64_t highest_trackable_value, int significant_figures, struct hdr_histogram **result);

static int updateTopSizes(char *key_name, size_t key_name_len, unsigned long long key_size, char *type_name, list *topkeys, unsigned long top_sizes_limit) ;

static void updateKeyType(redisReply *element, unsigned long long size, typeinfo *type) ;


_Bool hdr_record_value(struct hdr_histogram *h, int64_t value);

static void addSizeDist(size_dist *dist, unsigned long long size) ;

static void displayKeyStats(unsigned long long sampled, unsigned long long total_keys, unsigned long long total_size, dict *memkeys_types_dict, dict *bigkeys_types_dict, list *top_key_sizes, unsigned long top_sizes_limit, int move_cursor_up) ;

static int displayKeyStatsSizeDist(struct hdr_histogram *keysize_histogram) ;

static int displayKeyStatsLengthDist(size_dist *dist) ;

static int displayKeyStatsType(unsigned long long sampled, dict *memkeys_types_dict, dict *bigkeys_types_dict) ;

int spectrum_palette_color[] = {0, 233, 234, 235, 237, 239, 241, 243, 245, 247, 144, 143, 142, 184, 226, 214, 208, 202, 196};
;
int spectrum_palette_color_size = 19;
;
static int parseOptions(int argc, char **argv) ;

static void parseEnv(void) ;

static hisds askPassword(const char *msg) ;

static void clusterManagerMode(clusterManagerCommandProc *proc) ;

static clusterManagerCommandProc *validateClusterManagerCommand(void) ;

static void latencyMode(void) ;

static void latencyDistMode(void) ;

void sendCapa(void) ;

void sendRdbOnly(void) ;

static void pipeMode(void) ;

static void findBigKeys(int memkeys, long long memkeys_samples) ;

static void keyStats(long long memkeys_samples, unsigned long long cursor, unsigned long top_sizes_limit) ;

static void findHotKeys(void) ;

static void statMode(void) ;

static void scanMode(void) ;

static void LRUTestMode(void) ;

static void intrinsicLatencyMode(void) ;

void testHint(const char *input) ;

void testHintSuite(char *filename) ;

static void sigIntHandler(int s) ;

static int evalMode(int argc, char **argv) ;

static int noninteractive(int argc, char **argv) ;

#endif