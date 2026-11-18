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


static void _karatsuba_rec (mpd_uint_t *c, const mpd_uint_t *a, const mpd_uint_t *b, mpd_uint_t *w, mpd_size_t la, mpd_size_t lb){
    mpd_size_t m, lt;
    ;
    ;
    if (la <= 16) {
        ;
        return;
    }
    m = (la + 1) / 2;
    if (lb <= m) {
        if (lb > la - m) {
            lt = lb + lb + 1;
            mpd_uint_zero(w, lt);
            _karatsuba_rec(w, b, a + m, w + lt, lb, la - m);
        } else {
            lt = (la - m) + (la - m) + 1;
            mpd_uint_zero(w, lt);
            _karatsuba_rec(w, a + m, b, w + lt, la - m, lb);
        }
        ;
        lt = m + m + 1;
        mpd_uint_zero(w, lt);
        _karatsuba_rec(w, a, b, w + lt, m, lb);
        ;
        return;
    }
    memcpy(w, a, m * sizeof *w);
    w[m] = 0;
    ;
    ;
    w[m + 1 + m] = 0;
    ;
    _karatsuba_rec(c + m, w, w + (m + 1), w + 2 * (m + 1), m + 1, m + 1);
    lt = (la - m) + (la - m) + 1;
    mpd_uint_zero(w, lt);
    _karatsuba_rec(w, a + m, b + m, w + lt, la - m, lb - m);
    ;
    ;
    lt = m + m + 1;
    mpd_uint_zero(w, lt);
    _karatsuba_rec(w, a, b, w + lt, m, m);
    ;
    ;
    return;
}


static mpd_uint_t * _mpd_kmul (const mpd_uint_t *u, const mpd_uint_t *v, mpd_size_t ulen, mpd_size_t vlen, mpd_size_t *rsize){
    mpd_uint_t *result = ((void *)0), *w = ((void *)0);
    mpd_size_t m;
    ;
    ;
    *rsize = _kmul_resultsize(ulen, vlen);
    if ((result = mpd_calloc(*rsize, sizeof *result)) == ((void *)0)) {
        return ((void *)0);
    }
    m = _kmul_worksize(ulen, 16);
    if (m && ((w = mpd_calloc(m, sizeof *w)) == ((void *)0))) {
        ;
        return ((void *)0);
    }
    _karatsuba_rec(result, u, v, w, ulen, vlen);
    ;
    return result;
}


