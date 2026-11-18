#include "header_func.h"
#include "typearith.h"
inline extern  __attribute__((visibility("hidden")))  __attribute__((always_inline)) void mpd_uint_zero (mpd_uint_t *dest, mpd_size_t len){
    mpd_size_t i;
    for (i = 0; i < len; i++) {
        dest[i] = 0;
    }
}
static inline mpd_size_t _kmul_resultsize (mpd_size_t la, mpd_size_t lb){
    mpd_size_t n, m;
    n = add_size_t(la, lb);
    n = add_size_t(n, 1);
    m = (la + 1) / 2 + 1;
    m = mul_size_t(m, 3);
    return (m > n) ? m : n;
}
static inline mpd_size_t _kmul_worksize (mpd_size_t n, mpd_size_t lim){
    mpd_size_t m;
    if (n <= lim) {
        return 0;
    }
    m = (n + 1) / 2 + 1;
    return add_size_t(mul_size_t(m, 2), _kmul_worksize(m, lim));
}
static inline mpd_size_t _mpd_get_transform_len (mpd_size_t rsize){
    mpd_size_t log2rsize;
    mpd_size_t x, step;
    log2rsize = mpd_bsr(rsize);
    if (rsize <= 1024) {
        x = ((mpd_size_t)1) << log2rsize;
        return (rsize == x) ? x : x << 1;
    } else if (rsize <= 4294967296ULL) {
        x = ((mpd_size_t)1) << log2rsize;
        if (rsize == x)
            return x;
        step = x >> 1;
        x += step;
        return (rsize <= x) ? x : x + step;
    } else if (rsize <= 4294967296ULL + 4294967296ULL / 2) {
        return 4294967296ULL + 4294967296ULL / 2;
    } else if (rsize <= 3 * 4294967296ULL) {
        return 3 * 4294967296ULL;
    } else {
        return (18446744073709551615UL);
    }
}
static mpd_uint_t * _mpd_fntmul (const mpd_uint_t *u, const mpd_uint_t *v, mpd_size_t ulen, mpd_size_t vlen, mpd_size_t *rsize){
    mpd_uint_t *c1 = ((void *)0), *c2 = ((void *)0), *c3 = ((void *)0), *vtmp = ((void *)0);
    mpd_size_t n;
    *rsize = add_size_t(ulen, vlen);
    if ((n = _mpd_get_transform_len(*rsize)) == (18446744073709551615UL)) {
        goto malloc_error;
    }
    if ((c1 = mpd_calloc(n, sizeof *c1)) == ((void *)0)) {
        goto malloc_error;
    }
    if ((c2 = mpd_calloc(n, sizeof *c2)) == ((void *)0)) {
        goto malloc_error;
    }
    if ((c3 = mpd_calloc(n, sizeof *c3)) == ((void *)0)) {
        goto malloc_error;
    }
    ;
    if (u == v) {
        if (!fnt_autoconvolute(c1, n, P1) || !fnt_autoconvolute(c2, n, P2) || !fnt_autoconvolute(c3, n, P3)) {
            goto malloc_error;
        }
    } else {
        if ((vtmp = mpd_calloc(n, sizeof *vtmp)) == ((void *)0)) {
            goto malloc_error;
        }
        ;
        if (!fnt_convolute(c1, vtmp, n, P1)) {
            ;
            goto malloc_error;
        }
        ;
        mpd_uint_zero(vtmp + vlen, n - vlen);
        if (!fnt_convolute(c2, vtmp, n, P2)) {
            ;
            goto malloc_error;
        }
        ;
        mpd_uint_zero(vtmp + vlen, n - vlen);
        if (!fnt_convolute(c3, vtmp, n, P3)) {
            ;
            goto malloc_error;
        }
        ;
    }
    ;
  out:
    ;
    return c1;
  malloc_error:
    ;
    c1 = ((void *)0);
    goto out;
}
static int _karatsuba_rec_fnt (mpd_uint_t *c, const mpd_uint_t *a, const mpd_uint_t *b, mpd_uint_t *w, mpd_size_t la, mpd_size_t lb){
    mpd_size_t m, lt;
    if (la <= 3 * (4294967296ULL / 2)) {
        if (lb <= 192) {
            ;
        } else {
            mpd_uint_t *result;
            mpd_size_t dummy;
            if ((result = _mpd_fntmul(a, b, la, lb, &dummy)) == ((void *)0)) {
                return 0;
            }
            memcpy(c, result, (la + lb) * (sizeof *result));
        }
        return 1;
    }
    m = (la + 1) / 2;
    if (lb <= m) {
        if (lb > la - m) {
            lt = lb + lb + 1;
            mpd_uint_zero(w, lt);
            if (!_karatsuba_rec_fnt(w, b, a + m, w + lt, lb, la - m)) {
                return 0;
            }
        } else {
            lt = (la - m) + (la - m) + 1;
            mpd_uint_zero(w, lt);
            if (!_karatsuba_rec_fnt(w, a + m, b, w + lt, la - m, lb)) {
                return 0;
            }
        }
        ;
        lt = m + m + 1;
        mpd_uint_zero(w, lt);
        if (!_karatsuba_rec_fnt(w, a, b, w + lt, m, lb)) {
            return 0;
        }
        ;
        return 1;
    }
    ;
    w[m] = 0;
    w[m + 1 + m] = 0;
    if (!_karatsuba_rec_fnt(c + m, w, w + (m + 1), w + 2 * (m + 1), m + 1, m + 1)) {
        return 0;
    }
    lt = (la - m) + (la - m) + 1;
    mpd_uint_zero(w, lt);
    if (!_karatsuba_rec_fnt(w, a + m, b + m, w + lt, la - m, lb - m)) {
        return 0;
    }
    ;
    lt = m + m + 1;
    mpd_uint_zero(w, lt);
    if (!_karatsuba_rec_fnt(w, a, b, w + lt, m, m)) {
        return 0;
    }
    ;
    return 1;
}
static mpd_uint_t * _mpd_kmul_fnt (const mpd_uint_t *u, const mpd_uint_t *v, mpd_size_t ulen, mpd_size_t vlen, mpd_size_t *rsize){
    mpd_uint_t *result = ((void *)0), *w = ((void *)0);
    mpd_size_t m;
    *rsize = _kmul_resultsize(ulen, vlen);
    if ((result = mpd_calloc(*rsize, sizeof *result)) == ((void *)0)) {
        return ((void *)0);
    }
    m = _kmul_worksize(ulen, 3 * (4294967296ULL / 2));
    if (m && ((w = mpd_calloc(m, sizeof *w)) == ((void *)0))) {
        ;
        return ((void *)0);
    }
    if (!_karatsuba_rec_fnt(result, u, v, w, ulen, vlen)) {
        ;
    }
    ;
    return result;
}
