#include "header_func.h"
static inline void _mpd_div_words_r (mpd_uint_t *q, mpd_uint_t *r, mpd_uint_t hi, mpd_uint_t lo){
    mpd_uint_t n_adj, h, l, t;
    mpd_uint_t n1_neg;
    n1_neg = (lo & (1ULL << 63)) ? (18446744073709551615UL) : 0;
    n_adj = lo + (n1_neg & 10000000000000000000ULL);
    _mpd_mul_words(&h, &l, mprime_rdx, hi - n1_neg);
    l = l + n_adj;
    if (l < n_adj)
        h++;
    t = h + hi;
    t = (18446744073709551615UL) - t;
    _mpd_mul_words(&h, &l, t, 10000000000000000000ULL);
    l = l + lo;
    if (l < lo)
        h++;
    h += hi;
    h -= 10000000000000000000ULL;
    *q = (h - t);
    *r = l + (10000000000000000000ULL & h);
}
static inline void _mpd_singlemul (mpd_uint_t w[2], mpd_uint_t u, mpd_uint_t v){
    mpd_uint_t hi, lo;
    _mpd_mul_words(&hi, &lo, u, v);
    _mpd_div_words_r(&w[1], &w[0], hi, lo);
}
