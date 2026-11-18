#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline void _mpd_mul_words(mpd_uint_t *hi, mpd_uint_t *lo, mpd_uint_t a, mpd_uint_t b) ;

extern const mpd_uint_t mprime_rdx;
;
static inline void _mpd_div_words_r(mpd_uint_t *q, mpd_uint_t *r, mpd_uint_t hi, mpd_uint_t lo) ;

static inline void _mpd_div_words(mpd_uint_t *q, mpd_uint_t *r, mpd_uint_t hi, mpd_uint_t lo, mpd_uint_t d) ;

static inline mpd_size_t sub_size_t(mpd_size_t a, mpd_size_t b) ;


void *mpd_alloc(mpd_size_t nmemb, mpd_size_t size);

void _mpd_shortmul(mpd_uint_t *w, const mpd_uint_t *u, mpd_size_t n, mpd_uint_t v) ;

mpd_uint_t _mpd_shortdiv(mpd_uint_t *w, const mpd_uint_t *u, mpd_size_t n, mpd_uint_t v) ;

static inline void _mpd_singlemul(mpd_uint_t w[2], mpd_uint_t u, mpd_uint_t v) ;

mpd_uint_t _mpd_baseadd(mpd_uint_t *w, const mpd_uint_t *u, const mpd_uint_t *v, mpd_size_t m, mpd_size_t n) ;

static inline int _mpd_isallzero(const mpd_uint_t *data, mpd_ssize_t len) ;

#endif