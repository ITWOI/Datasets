#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static long long line = 1;
;
static off_t epos;
;
int consumeNewline(char *buf) ;

int readLong(FILE *fp, char prefix, long *target) ;


void *zmalloc(size_t size);

int readBytes(FILE *fp, char *target, long length) ;


void zfree(void *ptr);

int readArgc(FILE *fp, long *target) ;

int readString(FILE *fp, char **target) ;

static time_t to_timestamp = 0;
;

int redis_check_rdb_main(int argc, char **argv, FILE *fp);

int processAnnotations(FILE *fp, char *filename, int last_file) ;

int processRESP(FILE *fp, char *filename, int *out_multi) ;

extern FILE *stdin;
;
int fileIsManifest(char *filepath) ;

int fileIsRDB(char *filepath) ;


aofManifest *aofLoadManifestFromFile(sds am_filepath);

int checkSingleAof(char *aof_filename, char *aof_filepath, int last_file, int fix, int preamble) ;

void printAofStyle(int ret, char *aofFileName, char *aofType) ;


void sdsfree(sds s);


sds makePath(char *path, char *filename);


void listRewind(list *list, listIter *li);


listNode *listNext(listIter *iter);

input_file_type getInputFileType(char *filepath) ;

void checkMultiPartAof(char *dirpath, char *manifest_filepath, int fix) ;

void checkOldStyleAof(char *filepath, int fix, int preamble) ;

#endif