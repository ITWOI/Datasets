static void reverse_slice (PyObject **lo, PyObject **hi){
    ;
    --hi;
    while (lo < hi)
        {
            PyObject *t = *lo;
            *lo = *hi;
            *hi = t;
            ++lo;
            --hi;
        }
}


static inline void sortslice_copy (sortslice *s1, Py_ssize_t i, sortslice *s2, Py_ssize_t j){
    s1->keys[i] = s2->keys[j];
    if (s1->values != ((void *)0))
        s1->values[i] = s2->values[j];
}


static inline void sortslice_copy_incr (sortslice *dst, sortslice *src){
    *dst->keys++ = *src->keys++;
    if (dst->values != ((void *)0))
        *dst->values++ = *src->values++;
}


static inline void sortslice_copy_decr (sortslice *dst, sortslice *src){
    *dst->keys-- = *src->keys--;
    if (dst->values != ((void *)0))
        *dst->values-- = *src->values--;
}


static inline void sortslice_memcpy (sortslice *s1, Py_ssize_t i, sortslice *s2, Py_ssize_t j, Py_ssize_t n){
    memcpy(&s1->keys[i], &s2->keys[j], sizeof(PyObject *) * n);
    if (s1->values != ((void *)0))
        memcpy(&s1->values[i], &s2->values[j], sizeof(PyObject *) * n);
}


static inline void sortslice_memmove (sortslice *s1, Py_ssize_t i, sortslice *s2, Py_ssize_t j, Py_ssize_t n){
    memmove(&s1->keys[i], &s2->keys[j], sizeof(PyObject *) * n);
    if (s1->values != ((void *)0))
        memmove(&s1->values[i], &s2->values[j], sizeof(PyObject *) * n);
}


static inline void sortslice_advance (sortslice *slice, Py_ssize_t n){
    slice->keys += n;
    if (slice->values != ((void *)0))
        slice->values += n;
}


static int binarysort (MergeState *ms, sortslice lo, PyObject **hi, PyObject **start){
    Py_ssize_t k;
    PyObject **l, **p, **r;
    PyObject *pivot;
    ;
    if (lo.keys == start)
        ++start;
    for (; start < hi; ++start) {
        l = lo.keys;
        r = start;
        pivot = *r;
        ;
        do {
            p = l + ((r - l) >> 1);
            if ((k = (*(ms->key_compare))(pivot, *p, ms)) < 0)
                goto fail;
            if (k)
                r = p;
            else
                l = p + 1;
        } while (l < r);
        ;
        for (p = start; p > l; --p)
            *p = *(p - 1);
        *l = pivot;
        if (lo.values != ((void *)0)) {
            Py_ssize_t offset = lo.values - lo.keys;
            p = start + offset;
            pivot = *p;
            l += offset;
            for (p = start + offset; p > l; --p)
                *p = *(p - 1);
            *l = pivot;
        }
    }
    return 0;
  fail:
    return -1;
}


static Py_ssize_t count_run (MergeState *ms, PyObject **lo, PyObject **hi, int *descending){
    Py_ssize_t k;
    Py_ssize_t n;
    ;
    *descending = 0;
    ++lo;
    if (lo == hi)
        return 1;
    n = 2;
    if ((k = (*(ms->key_compare))(*lo, *(lo - 1), ms)) < 0)
        goto fail;
    if (k) {
        *descending = 1;
        for (lo = lo + 1; lo < hi; ++lo , ++n) {
            if ((k = (*(ms->key_compare))(*lo, *(lo - 1), ms)) < 0)
                goto fail;
            if (k)
                ;
            else
                break;
        }
    } else {
        for (lo = lo + 1; lo < hi; ++lo , ++n) {
            if ((k = (*(ms->key_compare))(*lo, *(lo - 1), ms)) < 0)
                goto fail;
            if (k)
                break;
        }
    }
    return n;
  fail:
    return -1;
}


static Py_ssize_t gallop_left (MergeState *ms, PyObject *key, PyObject **a, Py_ssize_t n, Py_ssize_t hint){
    Py_ssize_t ofs;
    Py_ssize_t lastofs;
    Py_ssize_t k;
    ;
    a += hint;
    lastofs = 0;
    ofs = 1;
    if ((k = (*(ms->key_compare))(*a, key, ms)) < 0)
        goto fail;
    if (k) {
        const Py_ssize_t maxofs = n - hint;
        while (ofs < maxofs)
            {
                if ((k = (*(ms->key_compare))(a[ofs], key, ms)) < 0)
                    goto fail;
                if (k) {
                    lastofs = ofs;
                    ((void)(0));
                    ofs = (ofs << 1) + 1;
                } else
                    break;
            }
        if (ofs > maxofs)
            ofs = maxofs;
        lastofs += hint;
        ofs += hint;
    } else {
        const Py_ssize_t maxofs = hint + 1;
        while (ofs < maxofs)
            {
                if ((k = (*(ms->key_compare))(*(a - ofs), key, ms)) < 0)
                    goto fail;
                if (k)
                    break;
                lastofs = ofs;
                ((void)(0));
                ofs = (ofs << 1) + 1;
            }
        if (ofs > maxofs)
            ofs = maxofs;
        k = lastofs;
        lastofs = hint - ofs;
        ofs = hint - k;
    }
    a -= hint;
    ;
    ++lastofs;
    while (lastofs < ofs)
        {
            Py_ssize_t m = lastofs + ((ofs - lastofs) >> 1);
            if ((k = (*(ms->key_compare))(a[m], key, ms)) < 0)
                goto fail;
            if (k)
                lastofs = m + 1;
            else
                ofs = m;
        }
    ;
    return ofs;
  fail:
    return -1;
}


static Py_ssize_t gallop_right (MergeState *ms, PyObject *key, PyObject **a, Py_ssize_t n, Py_ssize_t hint){
    Py_ssize_t ofs;
    Py_ssize_t lastofs;
    Py_ssize_t k;
    ;
    a += hint;
    lastofs = 0;
    ofs = 1;
    if ((k = (*(ms->key_compare))(key, *a, ms)) < 0)
        goto fail;
    if (k) {
        const Py_ssize_t maxofs = hint + 1;
        while (ofs < maxofs)
            {
                if ((k = (*(ms->key_compare))(key, *(a - ofs), ms)) < 0)
                    goto fail;
                if (k) {
                    lastofs = ofs;
                    ((void)(0));
                    ofs = (ofs << 1) + 1;
                } else
                    break;
            }
        if (ofs > maxofs)
            ofs = maxofs;
        k = lastofs;
        lastofs = hint - ofs;
        ofs = hint - k;
    } else {
        const Py_ssize_t maxofs = n - hint;
        while (ofs < maxofs)
            {
                if ((k = (*(ms->key_compare))(key, a[ofs], ms)) < 0)
                    goto fail;
                if (k)
                    break;
                lastofs = ofs;
                ((void)(0));
                ofs = (ofs << 1) + 1;
            }
        if (ofs > maxofs)
            ofs = maxofs;
        lastofs += hint;
        ofs += hint;
    }
    a -= hint;
    ;
    ++lastofs;
    while (lastofs < ofs)
        {
            Py_ssize_t m = lastofs + ((ofs - lastofs) >> 1);
            if ((k = (*(ms->key_compare))(key, a[m], ms)) < 0)
                goto fail;
            if (k)
                ofs = m;
            else
                lastofs = m + 1;
        }
    ;
    return ofs;
  fail:
    return -1;
}


static void merge_init (MergeState *ms, Py_ssize_t list_size, int has_keyfunc){
    ;
    if (has_keyfunc) {
        ms->alloced = (list_size + 1) / 2;
        if (256 / 2 < ms->alloced)
            ms->alloced = 256 / 2;
        ms->a.values = &ms->temparray[ms->alloced];
    } else {
        ms->alloced = 256;
        ms->a.values = ((void *)0);
    }
    ms->a.keys = ms->temparray;
    ms->n = 0;
    ms->min_gallop = 7;
}


static void merge_freemem (MergeState *ms){
    ;
    if (ms->a.keys != ms->temparray) {
        ;
        ms->a.keys = ((void *)0);
    }
}


static int merge_getmem (MergeState *ms, Py_ssize_t need){
    int multiplier;
    ;
    if (need <= ms->alloced)
        return 0;
    multiplier = ms->a.values != ((void *)0) ? 2 : 1;
    merge_freemem(ms);
    if ((size_t)need > ((Py_ssize_t)(((size_t)-1) >> 1)) / sizeof(PyObject *) / multiplier) {
        ;
        return -1;
    }
    ms->a.keys = (PyObject **)PyMem_Malloc(multiplier * need * sizeof(PyObject *));
    if (ms->a.keys != ((void *)0)) {
        ms->alloced = need;
        if (ms->a.values != ((void *)0))
            ms->a.values = &ms->a.keys[need];
        return 0;
    }
    ;
    return -1;
}


static Py_ssize_t merge_lo (MergeState *ms, sortslice ssa, Py_ssize_t na, sortslice ssb, Py_ssize_t nb){
    Py_ssize_t k;
    sortslice dest;
    int result = -1;
    Py_ssize_t min_gallop;
    ;
    ;
    if (((na) <= (ms)->alloced ? 0 : merge_getmem(ms, na)) < 0)
        return -1;
    sortslice_memcpy(&ms->a, 0, &ssa, 0, na);
    dest = ssa;
    ssa = ms->a;
    sortslice_copy_incr(&dest, &ssb);
    --nb;
    if (nb == 0)
        goto Succeed;
    if (na == 1)
        goto CopyB;
    min_gallop = ms->min_gallop;
    for (;;) {
        Py_ssize_t acount = 0;
        Py_ssize_t bcount = 0;
        for (;;) {
            ;
            k = (*(ms->key_compare))(ssb.keys[0], ssa.keys[0], ms);
            if (k) {
                if (k < 0)
                    goto Fail;
                sortslice_copy_incr(&dest, &ssb);
                ++bcount;
                acount = 0;
                --nb;
                if (nb == 0)
                    goto Succeed;
                if (bcount >= min_gallop)
                    break;
            } else {
                sortslice_copy_incr(&dest, &ssa);
                ++acount;
                bcount = 0;
                --na;
                if (na == 1)
                    goto CopyB;
                if (acount >= min_gallop)
                    break;
            }
        }
        ++min_gallop;
        do {
            ;
            min_gallop -= min_gallop > 1;
            ms->min_gallop = min_gallop;
            k = gallop_right(ms, ssb.keys[0], ssa.keys, na, 0);
            acount = k;
            if (k) {
                if (k < 0)
                    goto Fail;
                sortslice_memcpy(&dest, 0, &ssa, 0, k);
                sortslice_advance(&dest, k);
                sortslice_advance(&ssa, k);
                na -= k;
                if (na == 1)
                    goto CopyB;
                if (na == 0)
                    goto Succeed;
            }
            sortslice_copy_incr(&dest, &ssb);
            --nb;
            if (nb == 0)
                goto Succeed;
            k = gallop_left(ms, ssa.keys[0], ssb.keys, nb, 0);
            bcount = k;
            if (k) {
                if (k < 0)
                    goto Fail;
                sortslice_memmove(&dest, 0, &ssb, 0, k);
                sortslice_advance(&dest, k);
                sortslice_advance(&ssb, k);
                nb -= k;
                if (nb == 0)
                    goto Succeed;
            }
            sortslice_copy_incr(&dest, &ssa);
            --na;
            if (na == 1)
                goto CopyB;
        } while (acount >= 7 || bcount >= 7);
        ++min_gallop;
        ms->min_gallop = min_gallop;
    }
  Succeed:
    result = 0;
  Fail:
    if (na)
        sortslice_memcpy(&dest, 0, &ssa, 0, na);
    return result;
  CopyB:
    ;
    sortslice_memmove(&dest, 0, &ssb, 0, nb);
    sortslice_copy(&dest, nb, &ssa, 0);
    return 0;
}


static Py_ssize_t merge_hi (MergeState *ms, sortslice ssa, Py_ssize_t na, sortslice ssb, Py_ssize_t nb){
    Py_ssize_t k;
    sortslice dest, basea, baseb;
    int result = -1;
    Py_ssize_t min_gallop;
    ;
    ;
    if (((nb) <= (ms)->alloced ? 0 : merge_getmem(ms, nb)) < 0)
        return -1;
    dest = ssb;
    sortslice_advance(&dest, nb - 1);
    sortslice_memcpy(&ms->a, 0, &ssb, 0, nb);
    basea = ssa;
    baseb = ms->a;
    ssb.keys = ms->a.keys + nb - 1;
    if (ssb.values != ((void *)0))
        ssb.values = ms->a.values + nb - 1;
    sortslice_advance(&ssa, na - 1);
    sortslice_copy_decr(&dest, &ssa);
    --na;
    if (na == 0)
        goto Succeed;
    if (nb == 1)
        goto CopyA;
    min_gallop = ms->min_gallop;
    for (;;) {
        Py_ssize_t acount = 0;
        Py_ssize_t bcount = 0;
        for (;;) {
            ;
            k = (*(ms->key_compare))(ssb.keys[0], ssa.keys[0], ms);
            if (k) {
                if (k < 0)
                    goto Fail;
                sortslice_copy_decr(&dest, &ssa);
                ++acount;
                bcount = 0;
                --na;
                if (na == 0)
                    goto Succeed;
                if (acount >= min_gallop)
                    break;
            } else {
                sortslice_copy_decr(&dest, &ssb);
                ++bcount;
                acount = 0;
                --nb;
                if (nb == 1)
                    goto CopyA;
                if (bcount >= min_gallop)
                    break;
            }
        }
        ++min_gallop;
        do {
            ;
            min_gallop -= min_gallop > 1;
            ms->min_gallop = min_gallop;
            k = gallop_right(ms, ssb.keys[0], basea.keys, na, na - 1);
            if (k < 0)
                goto Fail;
            k = na - k;
            acount = k;
            if (k) {
                sortslice_advance(&dest, -k);
                sortslice_advance(&ssa, -k);
                sortslice_memmove(&dest, 1, &ssa, 1, k);
                na -= k;
                if (na == 0)
                    goto Succeed;
            }
            sortslice_copy_decr(&dest, &ssb);
            --nb;
            if (nb == 1)
                goto CopyA;
            k = gallop_left(ms, ssa.keys[0], baseb.keys, nb, nb - 1);
            if (k < 0)
                goto Fail;
            k = nb - k;
            bcount = k;
            if (k) {
                sortslice_advance(&dest, -k);
                sortslice_advance(&ssb, -k);
                sortslice_memcpy(&dest, 1, &ssb, 1, k);
                nb -= k;
                if (nb == 1)
                    goto CopyA;
                if (nb == 0)
                    goto Succeed;
            }
            sortslice_copy_decr(&dest, &ssa);
            --na;
            if (na == 0)
                goto Succeed;
        } while (acount >= 7 || bcount >= 7);
        ++min_gallop;
        ms->min_gallop = min_gallop;
    }
  Succeed:
    result = 0;
  Fail:
    if (nb)
        sortslice_memcpy(&dest, -(nb - 1), &baseb, 0, nb);
    return result;
  CopyA:
    ;
    sortslice_memmove(&dest, 1 - na, &ssa, 1 - na, na);
    sortslice_advance(&dest, -na);
    sortslice_advance(&ssa, -na);
    sortslice_copy(&dest, 0, &ssb, 0);
    return 0;
}


static Py_ssize_t merge_at (MergeState *ms, Py_ssize_t i){
    sortslice ssa, ssb;
    Py_ssize_t na, nb;
    Py_ssize_t k;
    ;
    ;
    ;
    ;
    ssa = ms->pending[i].base;
    na = ms->pending[i].len;
    ssb = ms->pending[i + 1].base;
    nb = ms->pending[i + 1].len;
    ;
    ;
    ms->pending[i].len = na + nb;
    if (i == ms->n - 3)
        ms->pending[i + 1] = ms->pending[i + 2];
    --ms->n;
    k = gallop_right(ms, *ssb.keys, ssa.keys, na, 0);
    if (k < 0)
        return -1;
    sortslice_advance(&ssa, k);
    na -= k;
    if (na == 0)
        return 0;
    nb = gallop_left(ms, ssa.keys[na - 1], ssb.keys, nb, nb - 1);
    if (nb <= 0)
        return nb;
    if (na <= nb) {
        return merge_lo(ms, ssa, na, ssb, nb);
    } else
        return merge_hi(ms, ssa, na, ssb, nb);
}


static int merge_collapse (MergeState *ms){
    struct s_slice *p = ms->pending;
    ;
    while (ms->n > 1)
        {
            Py_ssize_t n = ms->n - 2;
            if ((n > 0 && p[n - 1].len <= p[n].len + p[n + 1].len) || (n > 1 && p[n - 2].len <= p[n - 1].len + p[n].len)) {
                if (p[n - 1].len < p[n + 1].len)
                    --n;
                if (merge_at(ms, n) < 0)
                    return -1;
            } else if (p[n].len <= p[n + 1].len) {
                if (merge_at(ms, n) < 0)
                    return -1;
            } else {
                ;
            }
            ;
        }
    return 0;
}


static int merge_force_collapse (MergeState *ms){
    struct s_slice *p = ms->pending;
    ;
    while (ms->n > 1)
        {
            Py_ssize_t n = ms->n - 2;
            if (n > 0 && p[n - 1].len < p[n + 1].len)
                --n;
            if (merge_at(ms, n) < 0)
                return -1;
        }
    return 0;
}


static Py_ssize_t merge_compute_minrun (Py_ssize_t n){
    Py_ssize_t r = 0;
    ;
    while (n >= 64)
        {
            r |= n & 1;
            n >>= 1;
        }
    return n + r;
}


static void reverse_sortslice (sortslice *s, Py_ssize_t n){
    reverse_slice(s->keys, &s->keys[n]);
    if (s->values != ((void *)0))
        reverse_slice(s->values, &s->values[n]);
}


static int safe_object_compare (PyObject *v, PyObject *w, MergeState *ms){
    return PyObject_RichCompareBool(v, w, 0);
}


static int unsafe_object_compare (PyObject *v, PyObject *w, MergeState *ms){
    PyObject *res_obj;
    int res;
    if ((((PyObject *)(v))->ob_type)->tp_richcompare != ms->key_richcompare)
        return PyObject_RichCompareBool(v, w, 0);
    ;
    res_obj = (*(ms->key_richcompare))(v, w, 0);
    if (res_obj == (&_Py_NotImplementedStruct)) {
        _Py_DECREF(((PyObject *)(res_obj)));
        return PyObject_RichCompareBool(v, w, 0);
    }
    if (res_obj == ((void *)0))
        return -1;
    if (_Py_IS_TYPE(((const PyObject *)(res_obj)), &PyBool_Type)) {
        res = (res_obj == ((PyObject *)&_Py_TrueStruct));
    } else {
        res = PyObject_IsTrue(res_obj);
    }
    _Py_DECREF(((PyObject *)(res_obj)));
    return res;
}


static int unsafe_latin_compare (PyObject *v, PyObject *w, MergeState *ms){
    Py_ssize_t len;
    int res;
    ;
    ;
    ;
    ;
    len = ((((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(v))->length)) > ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(w))->length))) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(w))->length)) : ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(v))->length)));
    res = memcmp((((void)(0)) , (((PyASCIIObject *)(v))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)v)->state.ascii) ? ((void *)((PyASCIIObject *)(v) + 1)) : ((void *)((PyCompactUnicodeObject *)(v) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(v))->data.any)))), (((void)(0)) , (((PyASCIIObject *)(w))->state.compact) ? ((((void)(0)) , ((void)(0)) , ((PyASCIIObject *)w)->state.ascii) ? ((void *)((PyASCIIObject *)(w) + 1)) : ((void *)((PyCompactUnicodeObject *)(w) + 1))) : (((void)(0)) , ((((PyUnicodeObject *)(w))->data.any)))), len);
    res = (res != 0 ? res < 0 : (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(v))->length) < (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(w))->length));
    ;
    ;
    return res;
}


static int unsafe_long_compare (PyObject *v, PyObject *w, MergeState *ms){
    PyLongObject *vl, *wl;
    sdigit v0, w0;
    int res;
    ;
    ;
    ;
    ;
    vl = (PyLongObject *)v;
    wl = (PyLongObject *)w;
    v0 = (((PyVarObject *)(vl))->ob_size) == 0 ? 0 : (sdigit)vl->ob_digit[0];
    w0 = (((PyVarObject *)(wl))->ob_size) == 0 ? 0 : (sdigit)wl->ob_digit[0];
    if ((((PyVarObject *)(vl))->ob_size) < 0)
        v0 = -v0;
    if ((((PyVarObject *)(wl))->ob_size) < 0)
        w0 = -w0;
    res = v0 < w0;
    ;
    return res;
}


static int unsafe_float_compare (PyObject *v, PyObject *w, MergeState *ms){
    int res;
    ;
    ;
    res = (((PyFloatObject *)(v))->ob_fval) < (((PyFloatObject *)(w))->ob_fval);
    ;
    return res;
}


static int unsafe_tuple_compare (PyObject *v, PyObject *w, MergeState *ms){
    PyTupleObject *vt, *wt;
    Py_ssize_t i, vlen, wlen;
    int k;
    ;
    ;
    ;
    ;
    vt = (PyTupleObject *)v;
    wt = (PyTupleObject *)w;
    vlen = (((PyVarObject *)(vt))->ob_size);
    wlen = (((PyVarObject *)(wt))->ob_size);
    for (i = 0; i < vlen && i < wlen; i++) {
        k = PyObject_RichCompareBool(vt->ob_item[i], wt->ob_item[i], 2);
        if (k < 0)
            return -1;
        if (!k)
            break;
    }
    if (i >= vlen || i >= wlen)
        return vlen < wlen;
    if (i == 0) {
        return ms->tuple_elem_compare(vt->ob_item[i], wt->ob_item[i], ms);
    } else
        return PyObject_RichCompareBool(vt->ob_item[i], wt->ob_item[i], 0);
}


static PyObject * list_sort_impl (PyListObject *self, PyObject *keyfunc, int reverse){
    MergeState ms;
    Py_ssize_t nremaining;
    Py_ssize_t minrun;
    sortslice lo;
    Py_ssize_t saved_ob_size, saved_allocated;
    PyObject **saved_ob_item;
    PyObject **final_ob_item;
    PyObject *result = ((void *)0);
    Py_ssize_t i;
    PyObject **keys;
    ;
    ;
    if (keyfunc == (&_Py_NoneStruct))
        keyfunc = ((void *)0);
    saved_ob_size = (((PyVarObject *)(self))->ob_size);
    saved_ob_item = self->ob_item;
    saved_allocated = self->allocated;
    _Py_SET_SIZE(((PyVarObject *)(self)), 0);
    self->ob_item = ((void *)0);
    self->allocated = -1;
    if (keyfunc == ((void *)0)) {
        keys = ((void *)0);
        lo.keys = saved_ob_item;
        lo.values = ((void *)0);
    } else {
        if (saved_ob_size < 256 / 2) {
            keys = &ms.temparray[saved_ob_size + 1];
        } else {
            keys = PyMem_Malloc(sizeof(PyObject *) * saved_ob_size);
            if (keys == ((void *)0)) {
                ;
                goto keyfunc_fail;
            }
        }
        for (i = 0; i < saved_ob_size; i++) {
            keys[i] = PyObject_CallOneArg(keyfunc, saved_ob_item[i]);
            if (keys[i] == ((void *)0)) {
                for (i = i - 1; i >= 0; i--)
                    _Py_DECREF(((PyObject *)(keys[i])));
                ;
                goto keyfunc_fail;
            }
        }
        lo.keys = keys;
        lo.values = saved_ob_item;
    }
    if (saved_ob_size > 1) {
        int keys_are_in_tuples = (_Py_IS_TYPE(((const PyObject *)(lo.keys[0])), &PyTuple_Type) && (((PyVarObject *)(lo.keys[0]))->ob_size) > 0);
        PyTypeObject *key_type = (keys_are_in_tuples ? (((PyObject *)(((((void)(0)) , (PyTupleObject *)(lo.keys[0]))->ob_item[0])))->ob_type) : (((PyObject *)(lo.keys[0]))->ob_type));
        int keys_are_all_same_type = 1;
        int strings_are_latin = 1;
        int ints_are_bounded = 1;
        for (i = 0; i < saved_ob_size; i++) {
            if (keys_are_in_tuples && !(_Py_IS_TYPE(((const PyObject *)(lo.keys[i])), &PyTuple_Type) && (((PyVarObject *)(lo.keys[i]))->ob_size) != 0)) {
                keys_are_in_tuples = 0;
                keys_are_all_same_type = 0;
                break;
            }
            PyObject *key = (keys_are_in_tuples ? ((((void)(0)) , (PyTupleObject *)(lo.keys[i]))->ob_item[0]) : lo.keys[i]);
            if (!_Py_IS_TYPE(((const PyObject *)(key)), key_type)) {
                keys_are_all_same_type = 0;
                if (!keys_are_in_tuples) {
                    break;
                }
            }
            if (keys_are_all_same_type) {
                if (key_type == &PyLong_Type && ints_are_bounded && (((((PyVarObject *)(key))->ob_size)) < 0 ? -((((PyVarObject *)(key))->ob_size)) : ((((PyVarObject *)(key))->ob_size))) > 1) {
                    ints_are_bounded = 0;
                } else if (key_type == &PyUnicode_Type && strings_are_latin && (((void)(0)) , ((void)(0)) , ((PyASCIIObject *)(key))->state.kind) != PyUnicode_1BYTE_KIND) {
                    strings_are_latin = 0;
                }
            }
        }
        if (keys_are_all_same_type) {
            if (key_type == &PyUnicode_Type && strings_are_latin) {
                ms.key_compare = unsafe_latin_compare;
            } else if (key_type == &PyLong_Type && ints_are_bounded) {
                ms.key_compare = unsafe_long_compare;
            } else if (key_type == &PyFloat_Type) {
                ms.key_compare = unsafe_float_compare;
            } else if ((ms.key_richcompare = key_type->tp_richcompare) != ((void *)0)) {
                ms.key_compare = unsafe_object_compare;
            } else {
                ms.key_compare = safe_object_compare;
            }
        } else {
            ms.key_compare = safe_object_compare;
        }
        if (keys_are_in_tuples) {
            if (key_type == &PyTuple_Type) {
                ms.tuple_elem_compare = safe_object_compare;
            } else {
                ms.tuple_elem_compare = ms.key_compare;
            }
            ms.key_compare = unsafe_tuple_compare;
        }
    }
    merge_init(&ms, saved_ob_size, keys != ((void *)0));
    nremaining = saved_ob_size;
    if (nremaining < 2)
        goto succeed;
    if (reverse) {
        if (keys != ((void *)0))
            reverse_slice(&keys[0], &keys[saved_ob_size]);
        reverse_slice(&saved_ob_item[0], &saved_ob_item[saved_ob_size]);
    }
    minrun = merge_compute_minrun(nremaining);
    do {
        int descending;
        Py_ssize_t n;
        n = count_run(&ms, lo.keys, lo.keys + nremaining, &descending);
        if (n < 0)
            goto fail;
        if (descending)
            reverse_sortslice(&lo, n);
        if (n < minrun) {
            const Py_ssize_t force = nremaining <= minrun ? nremaining : minrun;
            if (binarysort(&ms, lo, lo.keys + force, lo.keys + n) < 0)
                goto fail;
            n = force;
        }
        ;
        ms.pending[ms.n].base = lo;
        ms.pending[ms.n].len = n;
        ++ms.n;
        if (merge_collapse(&ms) < 0)
            goto fail;
        sortslice_advance(&lo, n);
        nremaining -= n;
    } while (nremaining);
    if (merge_force_collapse(&ms) < 0)
        goto fail;
    ;
    ;
    ;
    lo = ms.pending[0].base;
  succeed:
    result = (&_Py_NoneStruct);
  fail:
    if (keys != ((void *)0)) {
        for (i = 0; i < saved_ob_size; i++)
            _Py_DECREF(((PyObject *)(keys[i])));
        ;
    }
    if (self->allocated != -1 && result != ((void *)0)) {
        ;
        result = ((void *)0);
    }
    if (reverse && saved_ob_size > 1)
        reverse_slice(saved_ob_item, saved_ob_item + saved_ob_size);
    merge_freemem(&ms);
  keyfunc_fail:
    final_ob_item = self->ob_item;
    i = (((PyVarObject *)(self))->ob_size);
    _Py_SET_SIZE(((PyVarObject *)(self)), saved_ob_size);
    self->ob_item = saved_ob_item;
    self->allocated = saved_allocated;
    if (final_ob_item != ((void *)0)) {
        while (--i >= 0)
            {
                _Py_XDECREF(((PyObject *)(final_ob_item[i])));
            }
        ;
    }
    ;
    return result;
}


