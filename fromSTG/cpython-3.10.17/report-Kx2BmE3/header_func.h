#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline void _mpd_mul_words(mpd_uint_t *hi, mpd_uint_t *lo, mpd_uint_t a, mpd_uint_t b) ;

static inline mpd_size_t add_size_t(mpd_size_t a, mpd_size_t b) ;

static inline mpd_size_t mul_size_t(mpd_size_t a, mpd_size_t b) ;

static inline mpd_size_t _kmul_worksize(mpd_size_t n, mpd_size_t lim) ;

static inline int mpd_bsr(mpd_size_t a) ;

static inline mpd_size_t _mpd_get_transform_len(mpd_size_t rsize) ;


void *mpd_calloc(mpd_size_t nmemb, mpd_size_t size);


int fnt_autoconvolute(mpd_uint_t *c1, mpd_size_t n, int modnum);


int fnt_convolute(mpd_uint_t *c1, mpd_uint_t *c2, mpd_size_t n, int modnum);

inline void mpd_uint_zero(mpd_uint_t *dest, mpd_size_t len) ;


void _mpd_basemul(mpd_uint_t *w, const mpd_uint_t *u, const mpd_uint_t *v, mpd_size_t m, mpd_size_t n);

static mpd_uint_t *_mpd_fntmul(const mpd_uint_t *u, const mpd_uint_t *v, mpd_size_t ulen, mpd_size_t vlen, mpd_size_t *rsize) ;

static int _karatsuba_rec_fnt(mpd_uint_t *c, const mpd_uint_t *a, const mpd_uint_t *b, mpd_uint_t *w, mpd_size_t la, mpd_size_t lb) ;


void _mpd_baseaddto(mpd_uint_t *w, const mpd_uint_t *u, mpd_size_t n);

static inline mpd_size_t _kmul_resultsize(mpd_size_t la, mpd_size_t lb) ;

#endif