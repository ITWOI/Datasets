#include "header_func.h"
static inline void _mpd_mul_words (mpd_uint_t *hi, mpd_uint_t *lo, mpd_uint_t a, mpd_uint_t b){
    mpd_uint_t h, l;
    asm ("mulq %3\n\t" : "=d" (h), "=a" (l) : "%a" (a), "rm" (b) : "cc");
    *hi = h;
    *lo = l;
}
static inline void _mpd_div_words (mpd_uint_t *q, mpd_uint_t *r, mpd_uint_t hi, mpd_uint_t lo, mpd_uint_t d){
    mpd_uint_t qq, rr;
    asm ("divq %4\n\t" : "=a" (qq), "=d" (rr) : "a" (lo), "d" (hi), "rm" (d) : "cc");
    *q = qq;
    *r = rr;
}
static inline mpd_size_t sub_size_t (mpd_size_t a, mpd_size_t b){
    if (b > a) {
        ;
    }
    return a - b;
}
