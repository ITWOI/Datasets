static Bigint * Balloc (int k){
    int x;
    Bigint *rv;
    unsigned int len;
    if (k <= 7 && (rv = freelist[k])) {
        freelist[k] = rv->next;
    } else {
        x = 1 << k;
        len = (sizeof(Bigint) + (x - 1) * sizeof(ULong) + sizeof(double) - 1) / sizeof(double);
        if (k <= 7 && pmem_next - private_mem + len <= (Py_ssize_t)((2304 + sizeof(double) - 1) / sizeof(double))) {
            rv = (Bigint *)pmem_next;
            pmem_next += len;
        } else {
            rv = (Bigint *)PyMem_Malloc(len * sizeof(double));
            if (rv == ((void *)0))
                return ((void *)0);
        }
        rv->k = k;
        rv->maxwds = x;
    }
    rv->sign = rv->wds = 0;
    return rv;
}


static void Bfree (Bigint *v){
    if (v) {
        if (v->k > 7) {
            ;
        } else {
            v->next = freelist[v->k];
            freelist[v->k] = v;
        }
    }
}


static Bigint * multadd (Bigint *b, int m, int a){
    int i, wds;
    ULong *x;
    ULLong carry, y;
    Bigint *b1;
    wds = b->wds;
    x = b->x;
    i = 0;
    carry = a;
    do {
        y = *x * (ULLong)m + carry;
        carry = y >> 32;
        *x++ = (ULong)(y & 4294967295UL);
    } while (++i < wds);
    if (carry) {
        if (wds >= b->maxwds) {
            b1 = Balloc(b->k + 1);
            if (b1 == ((void *)0)) {
                Bfree(b);
                return ((void *)0);
            }
            memcpy((char *)&b1->sign, (char *)&b->sign, b->wds * sizeof(Long) + 2 * sizeof(int));
            Bfree(b);
            b = b1;
        }
        b->x[wds++] = (ULong)carry;
        b->wds = wds;
    }
    return b;
}


static int hi0bits (ULong x){
    int k = 0;
    if (!(x & 4294901760U)) {
        k = 16;
        x <<= 16;
    }
    if (!(x & 4278190080U)) {
        k += 8;
        x <<= 8;
    }
    if (!(x & 4026531840U)) {
        k += 4;
        x <<= 4;
    }
    if (!(x & 3221225472U)) {
        k += 2;
        x <<= 2;
    }
    if (!(x & 2147483648U)) {
        k++;
        if (!(x & 1073741824))
            return 32;
    }
    return k;
}


static int lo0bits (ULong *y){
    int k;
    ULong x = *y;
    if (x & 7) {
        if (x & 1)
            return 0;
        if (x & 2) {
            *y = x >> 1;
            return 1;
        }
        *y = x >> 2;
        return 2;
    }
    k = 0;
    if (!(x & 65535)) {
        k = 16;
        x >>= 16;
    }
    if (!(x & 255)) {
        k += 8;
        x >>= 8;
    }
    if (!(x & 15)) {
        k += 4;
        x >>= 4;
    }
    if (!(x & 3)) {
        k += 2;
        x >>= 2;
    }
    if (!(x & 1)) {
        k++;
        x >>= 1;
        if (!x)
            return 32;
    }
    *y = x;
    return k;
}


static Bigint * i2b (int i){
    Bigint *b;
    b = Balloc(1);
    if (b == ((void *)0))
        return ((void *)0);
    b->x[0] = i;
    b->wds = 1;
    return b;
}


static Bigint * mult (Bigint *a, Bigint *b){
    Bigint *c;
    int k, wa, wb, wc;
    ULong *x, *xa, *xae, *xb, *xbe, *xc, *xc0;
    ULong y;
    ULLong carry, z;
    if ((!a->x[0] && a->wds == 1) || (!b->x[0] && b->wds == 1)) {
        c = Balloc(0);
        if (c == ((void *)0))
            return ((void *)0);
        c->wds = 1;
        c->x[0] = 0;
        return c;
    }
    if (a->wds < b->wds) {
        c = a;
        a = b;
        b = c;
    }
    k = a->k;
    wa = a->wds;
    wb = b->wds;
    wc = wa + wb;
    if (wc > a->maxwds)
        k++;
    c = Balloc(k);
    if (c == ((void *)0))
        return ((void *)0);
    for (x = c->x , xa = x + wc; x < xa; x++)
        *x = 0;
    xa = a->x;
    xae = xa + wa;
    xb = b->x;
    xbe = xb + wb;
    xc0 = c->x;
    for (; xb < xbe; xc0++) {
        if ((y = *xb++)) {
            x = xa;
            xc = xc0;
            carry = 0;
            do {
                z = *x++ * (ULLong)y + *xc + carry;
                carry = z >> 32;
                *xc++ = (ULong)(z & 4294967295UL);
            } while (x < xae);
            *xc = (ULong)carry;
        }
    }
    for (xc0 = c->x , xc = xc0 + wc; wc > 0 && !*--xc; --wc)
        ;
    ;
    c->wds = wc;
    return c;
}


static Bigint * pow5mult (Bigint *b, int k){
    Bigint *b1, *p5, *p51;
    int i;
    static const int p05[3] = {5, 25, 125};
    if ((i = k & 3)) {
        b = multadd(b, p05[i - 1], 0);
        if (b == ((void *)0))
            return ((void *)0);
    }
    if (!(k >>= 2))
        return b;
    p5 = p5s;
    if (!p5) {
        p5 = i2b(625);
        if (p5 == ((void *)0)) {
            Bfree(b);
            return ((void *)0);
        }
        p5s = p5;
        p5->next = 0;
    }
    for (;;) {
        if (k & 1) {
            b1 = mult(b, p5);
            Bfree(b);
            b = b1;
            if (b == ((void *)0))
                return ((void *)0);
        }
        if (!(k >>= 1))
            break;
        p51 = p5->next;
        if (!p51) {
            p51 = mult(p5, p5);
            if (p51 == ((void *)0)) {
                Bfree(b);
                return ((void *)0);
            }
            p51->next = 0;
            p5->next = p51;
        }
        p5 = p51;
    }
    return b;
}


static Bigint * lshift (Bigint *b, int k){
    int i, k1, n, n1;
    Bigint *b1;
    ULong *x, *x1, *xe, z;
    if (!k || (!b->x[0] && b->wds == 1))
        return b;
    n = k >> 5;
    k1 = b->k;
    n1 = n + b->wds + 1;
    for (i = b->maxwds; n1 > i; i <<= 1)
        k1++;
    b1 = Balloc(k1);
    if (b1 == ((void *)0)) {
        Bfree(b);
        return ((void *)0);
    }
    x1 = b1->x;
    for (i = 0; i < n; i++)
        *x1++ = 0;
    x = b->x;
    xe = x + b->wds;
    if (k &= 31) {
        k1 = 32 - k;
        z = 0;
        do {
            *x1++ = *x << k | z;
            z = *x++ >> k1;
        } while (x < xe);
        if ((*x1 = z))
            ++n1;
    } else
        do 
            *x1++ = *x++;
        while (x < xe);
    b1->wds = n1 - 1;
    Bfree(b);
    return b1;
}


static int cmp (Bigint *a, Bigint *b){
    ULong *xa, *xa0, *xb, *xb0;
    int i, j;
    i = a->wds;
    j = b->wds;
    if (i -= j)
        return i;
    xa0 = a->x;
    xa = xa0 + j;
    xb0 = b->x;
    xb = xb0 + j;
    for (;;) {
        if (*--xa != *--xb)
            return *xa < *xb ? -1 : 1;
        if (xa <= xa0)
            break;
    }
    return 0;
}


static Bigint * diff (Bigint *a, Bigint *b){
    Bigint *c;
    int i, wa, wb;
    ULong *xa, *xae, *xb, *xbe, *xc;
    ULLong borrow, y;
    i = cmp(a, b);
    if (!i) {
        c = Balloc(0);
        if (c == ((void *)0))
            return ((void *)0);
        c->wds = 1;
        c->x[0] = 0;
        return c;
    }
    if (i < 0) {
        c = a;
        a = b;
        b = c;
        i = 1;
    } else
        i = 0;
    c = Balloc(a->k);
    if (c == ((void *)0))
        return ((void *)0);
    c->sign = i;
    wa = a->wds;
    xa = a->x;
    xae = xa + wa;
    wb = b->wds;
    xb = b->x;
    xbe = xb + wb;
    xc = c->x;
    borrow = 0;
    do {
        y = (ULLong)*xa++ - *xb++ - borrow;
        borrow = y >> 32 & (ULong)1;
        *xc++ = (ULong)(y & 4294967295UL);
    } while (xb < xbe);
    while (xa < xae)
        {
            y = *xa++ - borrow;
            borrow = y >> 32 & (ULong)1;
            *xc++ = (ULong)(y & 4294967295UL);
        }
    while (!*--xc)
        wa--;
    c->wds = wa;
    return c;
}


static Bigint * d2b (U *d, int *e, int *bits){
    Bigint *b;
    int de, k;
    ULong *x, y, z;
    int i;
    b = Balloc(1);
    if (b == ((void *)0))
        return ((void *)0);
    x = b->x;
    z = (d)->L[1] & 1048575;
    (d)->L[1] &= 2147483647;
    if ((de = (int)((d)->L[1] >> 20)))
        z |= 1048576;
    if ((y = (d)->L[0])) {
        if ((k = lo0bits(&y))) {
            x[0] = y | z << (32 - k);
            z >>= k;
        } else
            x[0] = y;
        i = b->wds = (x[1] = z) ? 2 : 1;
    } else {
        k = lo0bits(&z);
        x[0] = z;
        i = b->wds = 1;
        k += 32;
    }
    if (de) {
        *e = de - 1023 - (53 - 1) + k;
        *bits = 53 - k;
    } else {
        *e = de - 1023 - (53 - 1) + 1 + k;
        *bits = 32 * i - hi0bits(x[i - 1]);
    }
    return b;
}


static int dshift (Bigint *b, int p2){
    int rv = hi0bits(b->x[b->wds - 1]) - 4;
    if (p2 > 0)
        rv -= p2;
    return rv & 31;
}


static int quorem (Bigint *b, Bigint *S){
    int n;
    ULong *bx, *bxe, q, *sx, *sxe;
    ULLong borrow, carry, y, ys;
    n = S->wds;
    if (b->wds < n)
        return 0;
    sx = S->x;
    sxe = sx + --n;
    bx = b->x;
    bxe = bx + n;
    q = *bxe / (*sxe + 1);
    if (q) {
        borrow = 0;
        carry = 0;
        do {
            ys = *sx++ * (ULLong)q + carry;
            carry = ys >> 32;
            y = *bx - (ys & 4294967295UL) - borrow;
            borrow = y >> 32 & (ULong)1;
            *bx++ = (ULong)(y & 4294967295UL);
        } while (sx <= sxe);
        if (!*bxe) {
            bx = b->x;
            while (--bxe > bx && !*bxe)
                --n;
            b->wds = n;
        }
    }
    if (cmp(b, S) >= 0) {
        q++;
        borrow = 0;
        carry = 0;
        bx = b->x;
        sx = S->x;
        do {
            ys = *sx++ + carry;
            carry = ys >> 32;
            y = *bx - (ys & 4294967295UL) - borrow;
            borrow = y >> 32 & (ULong)1;
            *bx++ = (ULong)(y & 4294967295UL);
        } while (sx <= sxe);
        bx = b->x;
        bxe = bx + n;
        if (!*bxe) {
            while (--bxe > bx && !*bxe)
                --n;
            b->wds = n;
        }
    }
    return q;
}


static char * rv_alloc (int i){
    int j, k, *r;
    j = sizeof(ULong);
    for (k = 0; sizeof(Bigint) - sizeof(ULong) - sizeof(int) + j <= (unsigned int)i; j <<= 1)
        k++;
    r = (int *)Balloc(k);
    if (r == ((void *)0))
        return ((void *)0);
    *r = k;
    return (char *)(r + 1);
}


static char * nrv_alloc (const char *s, char **rve, int n){
    char *rv, *t;
    rv = rv_alloc(n);
    ;
    ;
    ;
    ;
    return rv;
}


extern  __attribute__((visibility("default"))) void _Py_dg_freedtoa (char *s){
    Bigint *b = (Bigint *)((int *)s - 1);
    b->maxwds = 1 << (b->k = *(int *)b);
    Bfree(b);
}


extern  __attribute__((visibility("default"))) char * _Py_dg_dtoa (double dd, int mode, int ndigits, int *decpt, int *sign, char **rve){
    int bbits, b2, b5, be, dig, i, ieps, ilim, ilim0, ilim1, j, j1, k, k0, k_check, leftright, m2, m5, s2, s5, spec_case, try_quick;
    Long L;
    int denorm;
    ULong x;
    Bigint *b, *b1, *delta, *mlo, *mhi, *S;
    U d2, eps, u;
    double ds;
    char *s, *s0;
    mlo = mhi = S = 0;
    s0 = 0;
    u.d = dd;
    if ((&u)->L[1] & 2147483648U) {
        *sign = 1;
        (&u)->L[1] &= ~2147483648U;
    } else
        *sign = 0;
    if (((&u)->L[1] & 2146435072) == 2146435072) {
        *decpt = 9999;
        if (!(&u)->L[0] && !((&u)->L[1] & 1048575))
            return nrv_alloc("Infinity", rve, 8);
        return nrv_alloc("NaN", rve, 3);
    }
    if (!(&u)->d) {
        *decpt = 1;
        return nrv_alloc("0", rve, 1);
    }
    b = d2b(&u, &be, &bbits);
    if (b == ((void *)0))
        goto failed_malloc;
    if ((i = (int)((&u)->L[1] >> 20 & (2146435072 >> 20)))) {
        (&d2)->d = (&u)->d;
        (&d2)->L[1] &= 1048575;
        (&d2)->L[1] |= 1072693248;
        i -= 1023;
        denorm = 0;
    } else {
        i = bbits + be + (1023 + (53 - 1) - 1);
        x = i > 32 ? (&u)->L[1] << (64 - i) | (&u)->L[0] >> (i - 32) : (&u)->L[0] << (32 - i);
        (&d2)->d = x;
        (&d2)->L[1] -= 31 * 1048576;
        i -= (1023 + (53 - 1) - 1) + 1;
        denorm = 1;
    }
    ds = ((&d2)->d - 1.5) * 0.28952965460216801 + 0.1760912590558 + i * 0.30102999566398098;
    k = (int)ds;
    if (ds < 0. && ds != k)
        k--;
    k_check = 1;
    if (k >= 0 && k <= 22) {
        if ((&u)->d < tens[k])
            k--;
        k_check = 0;
    }
    j = bbits - i - 1;
    if (j >= 0) {
        b2 = 0;
        s2 = j;
    } else {
        b2 = -j;
        s2 = 0;
    }
    if (k >= 0) {
        b5 = 0;
        s5 = k;
        s2 += k;
    } else {
        b2 -= k;
        b5 = -k;
        s5 = 0;
    }
    if (mode < 0 || mode > 9)
        mode = 0;
    try_quick = 1;
    if (mode > 5) {
        mode -= 4;
        try_quick = 0;
    }
    leftright = 1;
    ilim = ilim1 = -1;
    switch (mode) {
      case 0:
      case 1:
        i = 18;
        ndigits = 0;
        break;
      case 2:
        leftright = 0;
      case 4:
        if (ndigits <= 0)
            ndigits = 1;
        ilim = ilim1 = i = ndigits;
        break;
      case 3:
        leftright = 0;
      case 5:
        i = ndigits + k + 1;
        ilim = i;
        ilim1 = i - 1;
        if (i <= 0)
            i = 1;
    }
    s0 = rv_alloc(i);
    if (s0 == ((void *)0))
        goto failed_malloc;
    s = s0;
    if (ilim >= 0 && ilim <= 14 && try_quick) {
        i = 0;
        (&d2)->d = (&u)->d;
        k0 = k;
        ilim0 = ilim;
        ieps = 2;
        if (k > 0) {
            ds = tens[k & 15];
            j = k >> 4;
            if (j & 16) {
                j &= 16 - 1;
                (&u)->d /= bigtens[5 - 1];
                ieps++;
            }
            for (; j; j >>= 1 , i++)
                if (j & 1) {
                    ieps++;
                    ds *= bigtens[i];
                }
            (&u)->d /= ds;
        } else if ((j1 = -k)) {
            (&u)->d *= tens[j1 & 15];
            for (j = j1 >> 4; j; j >>= 1 , i++)
                if (j & 1) {
                    ieps++;
                    (&u)->d *= bigtens[i];
                }
        }
        if (k_check && (&u)->d < 1. && ilim > 0) {
            if (ilim1 <= 0)
                goto fast_failed;
            ilim = ilim1;
            k--;
            (&u)->d *= 10.;
            ieps++;
        }
        (&eps)->d = ieps * (&u)->d + 7.;
        (&eps)->L[1] -= (53 - 1) * 1048576;
        if (ilim == 0) {
            S = mhi = 0;
            (&u)->d -= 5.;
            if ((&u)->d > (&eps)->d)
                goto one_digit;
            if ((&u)->d < -(&eps)->d)
                goto no_digits;
            goto fast_failed;
        }
        if (leftright) {
            (&eps)->d = 0.5 / tens[ilim - 1] - (&eps)->d;
            for (i = 0; ;) {
                L = (Long)(&u)->d;
                (&u)->d -= L;
                *s++ = '0' + (int)L;
                if ((&u)->d < (&eps)->d)
                    goto ret1;
                if (1. - (&u)->d < (&eps)->d)
                    goto bump_up;
                if (++i >= ilim)
                    break;
                (&eps)->d *= 10.;
                (&u)->d *= 10.;
            }
        } else {
            (&eps)->d *= tens[ilim - 1];
            for (i = 1; ; i++ , (&u)->d *= 10.) {
                L = (Long)((&u)->d);
                if (!((&u)->d -= L))
                    ilim = i;
                *s++ = '0' + (int)L;
                if (i == ilim) {
                    if ((&u)->d > 0.5 + (&eps)->d) {
                        goto bump_up;
                    } else if ((&u)->d < 0.5 - (&eps)->d) {
                        ;
                        goto ret1;
                    }
                    break;
                }
            }
        }
      fast_failed:
        s = s0;
        (&u)->d = (&d2)->d;
        k = k0;
        ilim = ilim0;
    }
    if (be >= 0 && k <= 14) {
        ds = tens[k];
        if (ndigits < 0 && ilim <= 0) {
            S = mhi = 0;
            if (ilim < 0 || (&u)->d <= 5 * ds)
                goto no_digits;
            goto one_digit;
        }
        for (i = 1; ; i++ , (&u)->d *= 10.) {
            L = (Long)((&u)->d / ds);
            (&u)->d -= L * ds;
            *s++ = '0' + (int)L;
            if (!(&u)->d) {
                break;
            }
            if (i == ilim) {
                (&u)->d += (&u)->d;
                if ((&u)->d > ds || ((&u)->d == ds && L & 1)) {
                  bump_up:
                    while (*--s == '9')
                        if (s == s0) {
                            k++;
                            *s = '0';
                            break;
                        }
                    ++*s++;
                } else {
                    ;
                }
                break;
            }
        }
        goto ret1;
    }
    m2 = b2;
    m5 = b5;
    if (leftright) {
        ;
        ;
        ;
        mhi = i2b(1);
        if (mhi == ((void *)0))
            goto failed_malloc;
    }
    if (m2 > 0 && s2 > 0) {
        i = m2 < s2 ? m2 : s2;
        b2 -= i;
        ;
        s2 -= i;
    }
    if (b5 > 0) {
        if (leftright) {
            if (m5 > 0) {
                mhi = pow5mult(mhi, m5);
                if (mhi == ((void *)0))
                    goto failed_malloc;
                b1 = mult(mhi, b);
                Bfree(b);
                b = b1;
                if (b == ((void *)0))
                    goto failed_malloc;
            }
            if ((j = b5 - m5)) {
                b = pow5mult(b, j);
                if (b == ((void *)0))
                    goto failed_malloc;
            }
        } else {
            b = pow5mult(b, b5);
            if (b == ((void *)0))
                goto failed_malloc;
        }
    }
    S = i2b(1);
    if (S == ((void *)0))
        goto failed_malloc;
    if (s5 > 0) {
        S = pow5mult(S, s5);
        if (S == ((void *)0))
            goto failed_malloc;
    }
    spec_case = 0;
    if ((mode < 2 || leftright)) {
        if (!(&u)->L[0] && !((&u)->L[1] & 1048575) && (&u)->L[1] & (2146435072 & ~1048576)) {
            b2 += 1;
            s2 += 1;
            spec_case = 1;
        }
    }
    i = dshift(S, s2);
    b2 += i;
    m2 += i;
    s2 += i;
    if (b2 > 0) {
        b = lshift(b, b2);
        if (b == ((void *)0))
            goto failed_malloc;
    }
    if (s2 > 0) {
        S = lshift(S, s2);
        if (S == ((void *)0))
            goto failed_malloc;
    }
    if (k_check) {
        if (cmp(b, S) < 0) {
            k--;
            b = multadd(b, 10, 0);
            if (b == ((void *)0))
                goto failed_malloc;
            if (leftright) {
                mhi = multadd(mhi, 10, 0);
                if (mhi == ((void *)0))
                    goto failed_malloc;
            }
            ilim = ilim1;
        }
    }
    if (ilim <= 0 && (mode == 3 || mode == 5)) {
        if (ilim < 0) {
          no_digits:
            ;
            goto ret;
        } else {
            S = multadd(S, 5, 0);
            if (S == ((void *)0))
                goto failed_malloc;
            if (cmp(b, S) <= 0)
                goto no_digits;
        }
      one_digit:
        *s++ = '1';
        ;
        goto ret;
    }
    if (leftright) {
        if (m2 > 0) {
            mhi = lshift(mhi, m2);
            if (mhi == ((void *)0))
                goto failed_malloc;
        }
        mlo = mhi;
        if (spec_case) {
            mhi = Balloc(mhi->k);
            if (mhi == ((void *)0))
                goto failed_malloc;
            memcpy((char *)&mhi->sign, (char *)&mlo->sign, mlo->wds * sizeof(Long) + 2 * sizeof(int));
            mhi = lshift(mhi, 1);
            if (mhi == ((void *)0))
                goto failed_malloc;
        }
        for (i = 1; ; i++) {
            dig = quorem(b, S) + '0';
            j = cmp(b, mlo);
            delta = diff(S, mhi);
            if (delta == ((void *)0))
                goto failed_malloc;
            j1 = delta->sign ? 1 : cmp(b, delta);
            Bfree(delta);
            if (j1 == 0 && mode != 1 && !((&u)->L[0] & 1)) {
                if (dig == '9')
                    goto round_9_up;
                if (j > 0)
                    dig++;
                *s++ = dig;
                goto ret;
            }
            if (j < 0 || (j == 0 && mode != 1 && !((&u)->L[0] & 1))) {
                if (!b->x[0] && b->wds <= 1) {
                    goto accept_dig;
                }
                if (j1 > 0) {
                    b = lshift(b, 1);
                    if (b == ((void *)0))
                        goto failed_malloc;
                    j1 = cmp(b, S);
                    if ((j1 > 0 || (j1 == 0 && dig & 1)) && dig++ == '9')
                        goto round_9_up;
                }
              accept_dig:
                *s++ = dig;
                goto ret;
            }
            if (j1 > 0) {
                if (dig == '9') {
                  round_9_up:
                    *s++ = '9';
                    goto roundoff;
                }
                *s++ = dig + 1;
                goto ret;
            }
            *s++ = dig;
            if (i == ilim)
                break;
            b = multadd(b, 10, 0);
            if (b == ((void *)0))
                goto failed_malloc;
            if (mlo == mhi) {
                mlo = mhi = multadd(mhi, 10, 0);
                if (mlo == ((void *)0))
                    goto failed_malloc;
            } else {
                mlo = multadd(mlo, 10, 0);
                if (mlo == ((void *)0))
                    goto failed_malloc;
                mhi = multadd(mhi, 10, 0);
                if (mhi == ((void *)0))
                    goto failed_malloc;
            }
        }
    } else
        for (i = 1; ; i++) {
            *s++ = dig = quorem(b, S) + '0';
            if (!b->x[0] && b->wds <= 1) {
                goto ret;
            }
            if (i >= ilim)
                break;
            b = multadd(b, 10, 0);
            if (b == ((void *)0))
                goto failed_malloc;
        }
    b = lshift(b, 1);
    if (b == ((void *)0))
        goto failed_malloc;
    j = cmp(b, S);
    if (j > 0 || (j == 0 && dig & 1)) {
      roundoff:
        while (*--s == '9')
            if (s == s0) {
                ;
                *s++ = '1';
                goto ret;
            }
        ++*s++;
    } else {
        ;
    }
  ret:
    Bfree(S);
    if (mhi) {
        if (mlo && mlo != mhi)
            Bfree(mlo);
        Bfree(mhi);
    }
  ret1:
    Bfree(b);
    ;
    ;
    ;
    return s0;
  failed_malloc:
    if (S)
        Bfree(S);
    if (mlo && mlo != mhi)
        Bfree(mlo);
    if (mhi)
        Bfree(mhi);
    if (b)
        Bfree(b);
    if (s0)
        _Py_dg_freedtoa(s0);
    return ((void *)0);
}


