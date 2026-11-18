static inline char * word_to_string (char *s, mpd_uint_t x, int n, char *dot){
    switch (n) {
      case 20:
        if (s == dot)
            *s++ = '.';
        *s++ = '0' + (char)(x / 10000000000000000000ULL);
        x %= 10000000000000000000ULL;
      case 19:
        if (s == dot)
            *s++ = '.';
        *s++ = '0' + (char)(x / 1000000000000000000ULL);
        x %= 1000000000000000000ULL;
      case 18:
        if (s == dot)
            *s++ = '.';
        *s++ = '0' + (char)(x / 100000000000000000ULL);
        x %= 100000000000000000ULL;
      case 17:
        if (s == dot)
            *s++ = '.';
        *s++ = '0' + (char)(x / 10000000000000000ULL);
        x %= 10000000000000000ULL;
      case 16:
        if (s == dot)
            *s++ = '.';
        *s++ = '0' + (char)(x / 1000000000000000ULL);
        x %= 1000000000000000ULL;
      case 15:
        if (s == dot)
            *s++ = '.';
        *s++ = '0' + (char)(x / 100000000000000ULL);
        x %= 100000000000000ULL;
      case 14:
        if (s == dot)
            *s++ = '.';
        *s++ = '0' + (char)(x / 10000000000000ULL);
        x %= 10000000000000ULL;
      case 13:
        if (s == dot)
            *s++ = '.';
        *s++ = '0' + (char)(x / 1000000000000ULL);
        x %= 1000000000000ULL;
      case 12:
        if (s == dot)
            *s++ = '.';
        *s++ = '0' + (char)(x / 100000000000ULL);
        x %= 100000000000ULL;
      case 11:
        if (s == dot)
            *s++ = '.';
        *s++ = '0' + (char)(x / 10000000000ULL);
        x %= 10000000000ULL;
      case 10:
        if (s == dot)
            *s++ = '.';
        *s++ = '0' + (char)(x / 1000000000UL);
        x %= 1000000000UL;
      case 9:
        if (s == dot)
            *s++ = '.';
        *s++ = '0' + (char)(x / 100000000UL);
        x %= 100000000UL;
      case 8:
        if (s == dot)
            *s++ = '.';
        *s++ = '0' + (char)(x / 10000000UL);
        x %= 10000000UL;
      case 7:
        if (s == dot)
            *s++ = '.';
        *s++ = '0' + (char)(x / 1000000UL);
        x %= 1000000UL;
      case 6:
        if (s == dot)
            *s++ = '.';
        *s++ = '0' + (char)(x / 100000UL);
        x %= 100000UL;
      case 5:
        if (s == dot)
            *s++ = '.';
        *s++ = '0' + (char)(x / 10000UL);
        x %= 10000UL;
      case 4:
        if (s == dot)
            *s++ = '.';
        *s++ = '0' + (char)(x / 1000UL);
        x %= 1000UL;
      case 3:
        if (s == dot)
            *s++ = '.';
        *s++ = '0' + (char)(x / 100UL);
        x %= 100UL;
      case 2:
        if (s == dot)
            *s++ = '.';
        *s++ = '0' + (char)(x / 10UL);
        x %= 10UL;
      default:
        if (s == dot)
            *s++ = '.';
        *s++ = '0' + (char)x;
    }
    *s = '\x00';
    return s;
}


static inline char * exp_to_string (char *s, mpd_ssize_t x){
    char sign = '+';
    if (x < 0) {
        sign = '-';
        x = -x;
    }
    *s++ = sign;
    return word_to_string(s, x, mpd_word_digits(x), ((void *)0));
}


static inline char * coeff_to_string (char *s, const mpd_t *dec){
    mpd_uint_t x;
    mpd_ssize_t i;
    x = mpd_msword(dec);
    s = word_to_string(s, x, mpd_word_digits(x), ((void *)0));
    for (i = dec->len - 2; i >= 0; --i) {
        x = dec->data[i];
        s = word_to_string(s, x, 19, ((void *)0));
    }
    return s;
}


static inline char * coeff_to_string_dot (char *s, char *dot, const mpd_t *dec){
    mpd_uint_t x;
    mpd_ssize_t i;
    x = mpd_msword(dec);
    s = word_to_string(s, x, mpd_word_digits(x), dot);
    for (i = dec->len - 2; i >= 0; --i) {
        x = dec->data[i];
        s = word_to_string(s, x, 19, dot);
    }
    return s;
}


static mpd_ssize_t _mpd_to_string (char **result, const mpd_t *dec, int flags, mpd_ssize_t dplace){
    char *decstring = ((void *)0), *cp = ((void *)0);
    mpd_ssize_t ldigits;
    mpd_ssize_t mem = 0, k;
    if (mpd_isspecial(dec)) {
        mem = sizeof "-Infinity%";
        if (mpd_isnan(dec) && dec->len > 0) {
            mem += dec->digits;
        }
        cp = decstring = mpd_alloc(mem, sizeof *decstring);
        if (cp == ((void *)0)) {
            *result = ((void *)0);
            return -1;
        }
        if (mpd_isnegative(dec)) {
            *cp++ = '-';
        } else if (flags & 64) {
            *cp++ = ' ';
        } else if (flags & 128) {
            *cp++ = '+';
        }
        if (mpd_isnan(dec)) {
            if (mpd_isqnan(dec)) {
                ;
                cp += 3;
            } else {
                ;
                cp += 4;
            }
            if (dec->len > 0) {
                cp = coeff_to_string(cp, dec);
            }
        } else if (mpd_isinfinite(dec)) {
            ;
            cp += 8;
        } else {
            ;
        }
    } else {
        ;
        ldigits = dec->digits + dec->exp;
        if (flags & 8) {
            ;
        } else if (flags & 16 || (dec->exp <= 0 && ldigits > -6)) {
            dplace = ldigits;
        } else if (flags & 4) {
            if (mpd_iszero(dec)) {
                dplace = -1 + mod_mpd_ssize_t(dec->exp + 2, 3);
            } else {
                dplace += mod_mpd_ssize_t(ldigits - 1, 3);
            }
        }
        if (dplace <= 0) {
            mem = -dplace + dec->digits + 2;
        } else if (dplace >= dec->digits) {
            mem = dplace;
        } else {
            mem = dec->digits;
        }
        mem += (19 + 1 + 6);
        cp = decstring = mpd_alloc(mem, sizeof *decstring);
        if (cp == ((void *)0)) {
            *result = ((void *)0);
            return -1;
        }
        if (mpd_isnegative(dec)) {
            *cp++ = '-';
        } else if (flags & 64) {
            *cp++ = ' ';
        } else if (flags & 128) {
            *cp++ = '+';
        }
        if (dplace <= 0) {
            *cp++ = '0';
            *cp++ = '.';
            for (k = 0; k < -dplace; k++) {
                *cp++ = '0';
            }
            cp = coeff_to_string(cp, dec);
        } else if (dplace >= dec->digits) {
            cp = coeff_to_string(cp, dec);
            for (k = 0; k < dplace - dec->digits; k++) {
                *cp++ = '0';
            }
        } else {
            cp = coeff_to_string_dot(cp, cp + dplace, dec);
        }
        if (ldigits != dplace || flags & 8) {
            *cp++ = (flags & 1) ? 'E' : 'e';
            cp = exp_to_string(cp, ldigits - dplace);
        }
    }
    if (flags & 32) {
        *cp++ = '%';
    }
    ;
    ;
    *cp = '\x00';
    *result = decstring;
    return (mpd_ssize_t)(cp - decstring);
}


static int _mpd_copy_utf8 (char dest[5], const char *s){
    const unsigned char *cp = (const unsigned char *)s;
    unsigned char lb, ub;
    int count, i;
    if (*cp == 0) {
        dest[0] = '\x00';
        return 0;
    } else if (*cp <= 127) {
        dest[0] = *cp;
        dest[1] = '\x00';
        return 1;
    } else if (194 <= *cp && *cp <= 223) {
        lb = 128;
        ub = 191;
        count = 2;
    } else if (*cp == 224) {
        lb = 160;
        ub = 191;
        count = 3;
    } else if (*cp <= 236) {
        lb = 128;
        ub = 191;
        count = 3;
    } else if (*cp == 237) {
        lb = 128;
        ub = 159;
        count = 3;
    } else if (*cp <= 239) {
        lb = 128;
        ub = 191;
        count = 3;
    } else if (*cp == 240) {
        lb = 144;
        ub = 191;
        count = 4;
    } else if (*cp <= 243) {
        lb = 128;
        ub = 191;
        count = 4;
    } else if (*cp == 244) {
        lb = 128;
        ub = 143;
        count = 4;
    } else {
        ;
    }
    dest[0] = *cp++;
    if (*cp < lb || ub < *cp) {
        goto error;
    }
    dest[1] = *cp++;
    for (i = 2; i < count; i++) {
        if (*cp < 128 || 191 < *cp) {
            goto error;
        }
        dest[i] = *cp++;
    }
    dest[i] = '\x00';
    return count;
  error:
    dest[0] = '\x00';
    return -1;
}


extern  __attribute__((visibility("hidden"))) int mpd_validate_lconv (mpd_spec_t *spec){
    size_t n;
    const char *cp = spec->grouping;
    while (*cp != '\x00')
        {
            if (*cp++ < 0) {
                return -1;
            }
        }
    n = strlen(spec->dot);
    if (n == 0 || n > 4) {
        return -1;
    }
    if (strlen(spec->sep) > 4) {
        return -1;
    }
    return 0;
}


extern  __attribute__((visibility("hidden"))) int mpd_parse_fmt_str (mpd_spec_t *spec, const char *fmt, int caps){
    char *cp = (char *)fmt;
    int have_align = 0, n;
    spec->min_width = 0;
    spec->prec = -1;
    spec->type = caps ? 'G' : 'g';
    spec->align = '>';
    spec->sign = '-';
    spec->dot = "";
    spec->sep = "";
    spec->grouping = "";
    if ((n = _mpd_copy_utf8(spec->fill, cp)) < 0) {
        return 0;
    }
    if (*cp && (*(cp + n) == '<' || *(cp + n) == '>' || *(cp + n) == '=' || *(cp + n) == '^')) {
        cp += n;
        spec->align = *cp++;
        have_align = 1;
    } else {
        spec->fill[0] = ' ';
        spec->fill[1] = '\x00';
        if (*cp == '<' || *cp == '>' || *cp == '=' || *cp == '^') {
            spec->align = *cp++;
            have_align = 1;
        }
    }
    if (*cp == '+' || *cp == '-' || *cp == ' ') {
        spec->sign = *cp++;
    }
    if (*cp == '0') {
        if (have_align) {
            return 0;
        }
        spec->align = 'z';
        spec->fill[0] = *cp++;
        spec->fill[1] = '\x00';
    }
    if (((*__ctype_b_loc())[(int)(((unsigned char)*cp))] & (unsigned short)_ISdigit)) {
        if (*cp == '0') {
            return 0;
        }
        (*__errno_location()) = 0;
        spec->min_width = strtoll(cp, &cp, 10);
        if ((*__errno_location()) == 34 || (*__errno_location()) == 22) {
            return 0;
        }
    }
    if (*cp == ',') {
        spec->dot = ".";
        spec->sep = ",";
        spec->grouping = "\003\003";
        cp++;
    }
    if (*cp == '.') {
        cp++;
        if (!((*__ctype_b_loc())[(int)(((unsigned char)*cp))] & (unsigned short)_ISdigit)) {
            return 0;
        }
        (*__errno_location()) = 0;
        spec->prec = strtoll(cp, &cp, 10);
        if ((*__errno_location()) == 34 || (*__errno_location()) == 22) {
            return 0;
        }
    }
    if (*cp == 'E' || *cp == 'e' || *cp == 'F' || *cp == 'f' || *cp == 'G' || *cp == 'g' || *cp == '%') {
        spec->type = *cp++;
    } else if (*cp == 'N' || *cp == 'n') {
        struct lconv *lc;
        if (*spec->sep) {
            return 0;
        }
        spec->type = *cp++;
        spec->type = (spec->type == 'N') ? 'G' : 'g';
        lc = localeconv();
        spec->dot = lc->decimal_point;
        spec->sep = lc->thousands_sep;
        spec->grouping = lc->grouping;
        if (mpd_validate_lconv(spec) < 0) {
            return 0;
        }
    }
    if (*cp != '\x00') {
        return 0;
    }
    return 1;
}


static inline void _mpd_bcopy (char *dest, const char *src, mpd_ssize_t n){
    while (--n >= 0)
        {
            dest[n] = src[n];
        }
}


static inline void _mbstr_copy_char (mpd_mbstr_t *dest, const char *src, mpd_ssize_t n){
    dest->nbytes += n;
    dest->nchars += (n > 0 ? 1 : 0);
    dest->cur -= n;
    if (dest->data != ((void *)0)) {
        _mpd_bcopy(dest->data + dest->cur, src, n);
    }
}


static inline void _mbstr_copy_ascii (mpd_mbstr_t *dest, const char *src, mpd_ssize_t n){
    dest->nbytes += n;
    dest->nchars += n;
    dest->cur -= n;
    if (dest->data != ((void *)0)) {
        _mpd_bcopy(dest->data + dest->cur, src, n);
    }
}


static inline void _mbstr_copy_pad (mpd_mbstr_t *dest, mpd_ssize_t n){
    dest->nbytes += n;
    dest->nchars += n;
    dest->cur -= n;
    if (dest->data != ((void *)0)) {
        char *cp = dest->data + dest->cur;
        while (--n >= 0)
            {
                cp[n] = '0';
            }
    }
}


static void _mpd_add_sep_dot (mpd_mbstr_t *dest, const char *sign, const char *src, mpd_ssize_t n_src, const char *dot, const char *rest, mpd_ssize_t n_rest, const mpd_spec_t *spec){
    mpd_ssize_t n_sep, n_sign, consume;
    const char *g;
    int pad = 0;
    n_sign = sign ? 1 : 0;
    n_sep = (mpd_ssize_t)strlen(spec->sep);
    dest->cur = dest->nbytes;
    dest->nbytes = dest->nchars = 0;
    _mbstr_copy_ascii(dest, rest, n_rest);
    if (dot) {
        _mbstr_copy_char(dest, dot, (mpd_ssize_t)strlen(dot));
    }
    g = spec->grouping;
    consume = *g;
    while (1)
        {
            if (*g == 0 || *g == 127 || consume > n_src) {
                consume = n_src;
            }
            n_src -= consume;
            if (pad) {
                _mbstr_copy_pad(dest, consume);
            } else {
                _mbstr_copy_ascii(dest, src + n_src, consume);
            }
            if (n_src == 0) {
                if (spec->align == 'z' && dest->nchars + n_sign < spec->min_width) {
                    n_src = spec->min_width - (dest->nchars + n_sign);
                    consume = *g - consume;
                    pad = 1;
                    continue;
                }
                break;
            }
            if (n_sep > 0) {
                if (pad && n_src > 1)
                    n_src -= 1;
                _mbstr_copy_char(dest, spec->sep, n_sep);
            }
            if (*g && *(g + 1))
                g++;
            consume = *g;
        }
    if (sign) {
        _mbstr_copy_ascii(dest, sign, 1);
    }
    if (dest->data) {
        dest->data[dest->nbytes] = '\x00';
    }
}


static int _mpd_apply_lconv (mpd_mbstr_t *result, const mpd_spec_t *spec, uint32_t *status){
    const char *sign = ((void *)0), *intpart = ((void *)0), *dot = ((void *)0);
    const char *rest, *dp;
    char *decstring;
    mpd_ssize_t n_int, n_rest;
    dp = result->data;
    if (*dp == '+' || *dp == '-' || *dp == ' ') {
        sign = dp++;
    }
    ;
    intpart = dp++;
    while (((*__ctype_b_loc())[(int)(((unsigned char)*dp))] & (unsigned short)_ISdigit))
        {
            dp++;
        }
    n_int = (mpd_ssize_t)(dp - intpart);
    if (*dp == '.') {
        dp++;
        dot = spec->dot;
    }
    rest = dp;
    n_rest = result->nbytes - (mpd_ssize_t)(dp - result->data);
    if (dot == ((void *)0) && (*spec->sep == '\x00' || *spec->grouping == '\x00')) {
        return 1;
    }
    ;
    result->data = ((void *)0);
    _mpd_add_sep_dot(result, sign, intpart, n_int, dot, rest, n_rest, spec);
    result->data = mpd_alloc(result->nbytes + 1, 1);
    if (result->data == ((void *)0)) {
        *status |= 512U;
        ;
        return 0;
    }
    _mpd_add_sep_dot(result, sign, intpart, n_int, dot, rest, n_rest, spec);
    ;
    return 1;
}


static int _mpd_add_pad (mpd_mbstr_t *result, const mpd_spec_t *spec, uint32_t *status){
    if (result->nchars < spec->min_width) {
        mpd_ssize_t add_chars, add_bytes;
        size_t lpad = 0, rpad = 0;
        size_t n_fill, len, i, j;
        char align = spec->align;
        uint8_t err = 0;
        char *cp;
        n_fill = strlen(spec->fill);
        add_chars = (spec->min_width - result->nchars);
        add_bytes = add_chars * (mpd_ssize_t)n_fill;
        cp = result->data = mpd_realloc(result->data, result->nbytes + add_bytes + 1, sizeof *result->data, &err);
        if (err) {
            ;
            ;
            return 0;
        }
        if (align == 'z') {
            align = '=';
        }
        if (align == '<') {
            rpad = add_chars;
        } else if (align == '>' || align == '=') {
            lpad = add_chars;
        } else {
            lpad = add_chars / 2;
            rpad = add_chars - lpad;
        }
        len = result->nbytes;
        if (align == '=' && (*cp == '-' || *cp == '+' || *cp == ' ')) {
            cp++;
            len--;
        }
        ;
        for (i = 0; i < lpad; i++) {
            for (j = 0; j < n_fill; j++) {
                cp[i * n_fill + j] = spec->fill[j];
            }
        }
        ;
        ;
        ;
        ;
    }
    return 1;
}


extern  __attribute__((visibility("hidden"))) char * mpd_qformat_spec (const mpd_t *dec, const mpd_spec_t *spec, const mpd_context_t *ctx, uint32_t *status){
    mpd_uint_t dt[64];
    mpd_t tmp = {((uint8_t)16) | ((uint8_t)32), 0, 0, 0, 64, dt};
    mpd_ssize_t dplace = 1;
    mpd_mbstr_t result;
    mpd_spec_t stackspec;
    char type = spec->type;
    int flags = 0;
    if (spec->min_width > 999999999999999999LL) {
        ;
        return ((void *)0);
    }
    if (((*__ctype_b_loc())[(int)(((unsigned char)type))] & (unsigned short)_ISupper)) {
        type = (char)tolower((unsigned char)type);
        flags |= 1;
    }
    if (spec->sign == ' ') {
        flags |= 64;
    } else if (spec->sign == '+') {
        flags |= 128;
    }
    if (mpd_isspecial(dec)) {
        if (spec->align == 'z') {
            stackspec = *spec;
            stackspec.fill[0] = ' ';
            stackspec.fill[1] = '\x00';
            stackspec.align = '>';
            spec = &stackspec;
        }
        ;
        if (type == '%') {
            flags |= 32;
        }
    } else {
        uint32_t workstatus = 0;
        mpd_ssize_t prec;
        switch (type) {
          case 'g':
            flags |= 2;
            break;
            ;
          case 'e':
            flags |= 8;
            break;
            ;
          case '%':
            flags |= 32;
            if (!mpd_qcopy(&tmp, dec, status)) {
                return ((void *)0);
            }
            tmp.exp += 2;
            dec = &tmp;
            type = 'f';
          case 'f':
            flags |= 16;
            break;
            ;
            ;
        }
        if (spec->prec >= 0) {
            if (spec->prec > 999999999999999999LL) {
                ;
                goto error;
            }
            switch (type) {
              case 'g':
                prec = (spec->prec == 0) ? 1 : spec->prec;
                if (dec->digits > prec) {
                    ;
                    dec = &tmp;
                }
                break;
              case 'e':
                if (mpd_iszero(dec)) {
                    dplace = 1 - spec->prec;
                } else {
                    ;
                    dec = &tmp;
                }
                break;
              case 'f':
                ;
                dec = &tmp;
                break;
            }
        }
        if (type == 'f') {
            if (mpd_iszero(dec) && dec->exp > 0) {
                ;
                dec = &tmp;
            }
        }
        if (workstatus & ((2U | 8U | 16U | 32U | 128U | 256U | 512U) | 4U)) {
            ;
            goto error;
        }
    }
    result.nbytes = _mpd_to_string(&result.data, dec, flags, dplace);
    result.nchars = result.nbytes;
    if (result.nbytes < 0) {
        ;
        goto error;
    }
    if (*spec->dot != '\x00' && !mpd_isspecial(dec)) {
        if (result.nchars > 999999999999999999LL + 36) {
            ;
            ;
            goto error;
        }
        if (!_mpd_apply_lconv(&result, spec, status)) {
            goto error;
        }
    }
    if (spec->min_width) {
        if (!_mpd_add_pad(&result, spec, status)) {
            goto error;
        }
    }
    ;
    return result.data;
  error:
    ;
    return ((void *)0);
}


extern  __attribute__((visibility("hidden"))) char * mpd_qformat (const mpd_t *dec, const char *fmt, const mpd_context_t *ctx, uint32_t *status){
    mpd_spec_t spec;
    if (!mpd_parse_fmt_str(&spec, fmt, 1)) {
        ;
        return ((void *)0);
    }
    return mpd_qformat_spec(dec, &spec, ctx, status);
}


