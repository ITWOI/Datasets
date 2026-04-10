#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

extern void *jv_mem_alloc(size_t);


void jv_mem_free(void *);

static Bigint *Balloc(struct dtoa_context *C, int k) ;

static void Bfree(struct dtoa_context *C, Bigint *v) ;

static Bigint *multadd(struct dtoa_context *C, Bigint *b, int m, int a) ;

static Bigint *i2b(struct dtoa_context *C, int i) ;

static Bigint *mult(struct dtoa_context *C, Bigint *a, Bigint *b) ;

static int cmp(struct dtoa_context *C, Bigint *a, Bigint *b) ;

static int lo0bits(struct dtoa_context *C, ULong *y) ;

static int hi0bits(struct dtoa_context *C, ULong x) ;

static char *rv_alloc(struct dtoa_context *C, int i) ;

static char *nrv_alloc(struct dtoa_context *C, const char *s, char **rve, int n) ;

static Bigint *d2b(struct dtoa_context *C, U *d, int *e, int *bits) ;

static const double tens[] = {1., 10., 100., 1000., 1.0E+4, 1.0E+5, 1.0E+6, 1.0E+7, 1.0E+8, 1.0E+9, 1.0E+10, 1.0E+11, 1.0E+12, 1.0E+13, 1.0E+14, 1.0E+15, 1.0E+16, 1.0E+17, 1.0E+18, 1.0E+19, 1.0E+20, 1.0E+21, 1.0E+22};
;
static const double bigtens[] = {1.0E+16, 1.0000000000000001E+32, 1.0E+64, 1.0000000000000001E+128, 1.0E+256};
;
static Bigint *pow5mult(struct dtoa_context *C, Bigint *b, int k) ;

static int dshift(struct dtoa_context *C, Bigint *b, int p2) ;

static Bigint *lshift(struct dtoa_context *C, Bigint *b, int k) ;

static int quorem(struct dtoa_context *C, Bigint *b, Bigint *S) ;

static Bigint *diff(struct dtoa_context *C, Bigint *a, Bigint *b) ;

#endif