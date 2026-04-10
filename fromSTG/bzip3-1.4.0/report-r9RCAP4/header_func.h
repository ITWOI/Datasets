#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static void help() ;

static void version() ;

static int is_numeric(const char *str) ;

extern FILE *stderr;
;
extern char *optarg;
;
static int process(FILE *input_des, FILE *output_des, int mode, int block_size, int workers, int verbose, char *file_name) ;

static void close_out_file(FILE *des) ;

extern int optind;
;
#endif