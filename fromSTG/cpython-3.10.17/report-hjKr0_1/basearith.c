extern  __attribute__((visibility("hidden"))) mpd_uint_t _mpd_baseadd (mpd_uint_t *w, const mpd_uint_t *u, const mpd_uint_t *v, mpd_size_t m, mpd_size_t n){
    mpd_uint_t s;
    mpd_uint_t carry = 0;
    mpd_size_t i;
    ;
    for (i = 0; i < n; i++) {
        s = u[i] + (v[i] + carry);
        carry = (s < u[i]) | (s >= 10000000000000000000ULL);
        w[i] = carry ? s - 10000000000000000000ULL : s;
    }
    for (; carry && i < m; i++) {
        s = u[i] + carry;
        carry = (s == 10000000000000000000ULL);
        w[i] = carry ? 0 : s;
    }
    for (; i < m; i++) {
        w[i] = u[i];
    }
    return carry;
}


extern  __attribute__((visibility("hidden"))) void _mpd_shortmul (mpd_uint_t *w, const mpd_uint_t *u, mpd_size_t n, mpd_uint_t v){
    mpd_uint_t hi, lo;
    mpd_uint_t carry = 0;
    mpd_size_t i;
    ;
    for (i = 0; i < n; i++) {
        _mpd_mul_words(&hi, &lo, u[i], v);
        lo = carry + lo;
        if (lo < carry)
            hi++;
        _mpd_div_words_r(&carry, &w[i], hi, lo);
    }
    w[i] = carry;
}


extern  __attribute__((visibility("hidden"))) mpd_uint_t _mpd_shortdiv (mpd_uint_t *w, const mpd_uint_t *u, mpd_size_t n, mpd_uint_t v){
    mpd_uint_t hi, lo;
    mpd_uint_t rem = 0;
    mpd_size_t i;
    ;
    for (i = n - 1; i != (18446744073709551615UL); i--) {
        _mpd_mul_words(&hi, &lo, rem, 10000000000000000000ULL);
        lo = u[i] + lo;
        if (lo < u[i])
            hi++;
        _mpd_div_words(&w[i], &rem, hi, lo, v);
    }
    return rem;
}


extern  __attribute__((visibility("hidden"))) int _mpd_basedivmod (mpd_uint_t *q, mpd_uint_t *r, const mpd_uint_t *uconst, const mpd_uint_t *vconst, mpd_size_t nplusm, mpd_size_t n){
    mpd_uint_t ustatic[64];
    mpd_uint_t vstatic[64];
    mpd_uint_t *u = ustatic;
    mpd_uint_t *v = vstatic;
    mpd_uint_t d, qhat, rhat, w2[2];
    mpd_uint_t hi, lo, x;
    mpd_uint_t carry;
    mpd_size_t i, j, m;
    int retval = 0;
    ;
    m = sub_size_t(nplusm, n);
    d = 10000000000000000000ULL / (vconst[n - 1] + 1);
    if (nplusm >= 64) {
        if ((u = mpd_alloc(nplusm + 1, sizeof *u)) == ((void *)0)) {
            return -1;
        }
    }
    if (n >= 64) {
        if ((v = mpd_alloc(n + 1, sizeof *v)) == ((void *)0)) {
            ;
            return -1;
        }
    }
    _mpd_shortmul(u, uconst, nplusm, d);
    _mpd_shortmul(v, vconst, n, d);
    for (j = m; j != (18446744073709551615UL); j--) {
        ;
        rhat = _mpd_shortdiv(w2, u + j + n - 1, 2, v[n - 1]);
        qhat = w2[1] * 10000000000000000000ULL + w2[0];
        while (1)
            {
                if (qhat < 10000000000000000000ULL) {
                    _mpd_singlemul(w2, qhat, v[n - 2]);
                    if (w2[1] <= rhat) {
                        if (w2[1] != rhat || w2[0] <= u[j + n - 2]) {
                            break;
                        }
                    }
                }
                qhat -= 1;
                rhat += v[n - 1];
                if (rhat < v[n - 1] || rhat >= 10000000000000000000ULL) {
                    break;
                }
            }
        carry = 0;
        for (i = 0; i <= n; i++) {
            _mpd_mul_words(&hi, &lo, qhat, v[i]);
            lo = carry + lo;
            if (lo < carry)
                hi++;
            _mpd_div_words_r(&hi, &lo, hi, lo);
            x = u[i + j] - lo;
            carry = (u[i + j] < x);
            u[i + j] = carry ? x + 10000000000000000000ULL : x;
            carry += hi;
        }
        q[j] = qhat;
        if (carry) {
            q[j] -= 1;
            (void)_mpd_baseadd(u + j, u + j, v, n + 1, n);
        }
    }
    if (r != ((void *)0)) {
        _mpd_shortdiv(r, u, n, d);
        ;
    } else {
        ;
    }
    ;
    ;
    return retval;
}


