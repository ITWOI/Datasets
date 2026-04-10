#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

void *PyMem_Malloc(size_t size);

static Bigint *freelist[8];
;
static double private_mem[288];
;
static double *pmem_next = private_mem;
;

void PyMem_Free(void *ptr);

static Bigint *Balloc(int k) ;

static void Bfree(Bigint *v) ;

static Bigint *multadd(Bigint *b, int m, int a) ;

static Bigint *p5s;
;
static Bigint *i2b(int i) ;

static Bigint *mult(Bigint *a, Bigint *b) ;

static int cmp(Bigint *a, Bigint *b) ;

static int lo0bits(ULong *y) ;

static int hi0bits(ULong x) ;

static char *rv_alloc(int i) ;

static char *nrv_alloc(const char *s, char **rve, int n) ;

static Bigint *d2b(U *d, int *e, int *bits) ;

static const double tens[] = {1., 10., 100., 1000., 1.0E+4, 1.0E+5, 1.0E+6, 1.0E+7, 1.0E+8, 1.0E+9, 1.0E+10, 1.0E+11, 1.0E+12, 1.0E+13, 1.0E+14, 1.0E+15, 1.0E+16, 1.0E+17, 1.0E+18, 1.0E+19, 1.0E+20, 1.0E+21, 1.0E+22};
;
static const double bigtens[] = {1.0E+16, 1.0000000000000001E+32, 1.0E+64, 1.0000000000000001E+128, 1.0E+256};
;
static Bigint *pow5mult(Bigint *b, int k) ;

static int dshift(Bigint *b, int p2) ;

static Bigint *lshift(Bigint *b, int k) ;

static int quorem(Bigint *b, Bigint *S) ;

static Bigint *diff(Bigint *a, Bigint *b) ;

void _Py_dg_freedtoa(char *s) ;

#endif