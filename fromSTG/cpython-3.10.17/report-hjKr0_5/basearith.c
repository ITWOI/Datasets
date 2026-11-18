extern  __attribute__((visibility("hidden"))) mpd_uint_t _mpd_baseshiftr (mpd_uint_t *dest, mpd_uint_t *src, mpd_size_t slen, mpd_size_t shift){
    mpd_uint_t l, h, hprev;
    mpd_uint_t rnd, rest;
    mpd_uint_t q, r;
    mpd_size_t i, j;
    mpd_uint_t ph;
    ;
    _mpd_div_word(&q, &r, (mpd_uint_t)shift, 19);
    rnd = rest = 0;
    if (r != 0) {
        ph = mpd_pow10[19 - r];
        _mpd_divmod_pow10(&hprev, &rest, src[q], r);
        _mpd_divmod_pow10(&rnd, &rest, rest, r - 1);
        if (rest == 0 && q > 0) {
            rest = !_mpd_isallzero(src, q);
        }
        for (j = 0 , i = q + 1; i < slen; i++ , j++) {
            _mpd_divmod_pow10(&h, &l, src[i], r);
            dest[j] = ph * l + hprev;
            hprev = h;
        }
        if (hprev != 0) {
            ;
        }
    } else {
        if (q > 0) {
            _mpd_divmod_pow10(&rnd, &rest, src[q - 1], 19 - 1);
            if (rest == 0)
                rest = !_mpd_isallzero(src, q - 1);
        }
    }
    return (rnd == 0 || rnd == 5) ? rnd + !!rest : rnd;
}


