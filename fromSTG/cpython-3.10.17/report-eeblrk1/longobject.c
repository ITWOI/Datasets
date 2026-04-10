static PyObject * get_small_int (sdigit ival){
    ;
    PyObject *v = __PyLong_GetSmallInt_internal(ival);
    _Py_INCREF(((PyObject *)(v)));
    return v;
}


static PyLongObject * maybe_small_long (PyLongObject *v){
    if (v && (((((PyVarObject *)(v))->ob_size)) < 0 ? -((((PyVarObject *)(v))->ob_size)) : ((((PyVarObject *)(v))->ob_size))) <= 1) {
        sdigit ival = (((void)(0)) , (((PyVarObject *)(v))->ob_size) < 0 ? -(sdigit)(v)->ob_digit[0] : ((((PyVarObject *)(v))->ob_size) == 0 ? (sdigit)0 : (sdigit)(v)->ob_digit[0]));
        if ((-5 <= (ival) && (ival) < 257)) {
            _Py_DECREF(((PyObject *)(v)));
            return (PyLongObject *)get_small_int(ival);
        }
    }
    return v;
}


static inline void _PyLong_Negate (PyLongObject **x_p){
    PyLongObject *x;
    x = (PyLongObject *)*x_p;
    if (_Py_REFCNT(((const PyObject *)(x))) == 1) {
        _Py_SET_SIZE(((PyVarObject *)(x)), -(((PyVarObject *)(x))->ob_size));
        return;
    }
    *x_p = (PyLongObject *)PyLong_FromLong(-(((void)(0)) , (((PyVarObject *)(x))->ob_size) < 0 ? -(sdigit)(x)->ob_digit[0] : ((((PyVarObject *)(x))->ob_size) == 0 ? (sdigit)0 : (sdigit)(x)->ob_digit[0])));
    _Py_DECREF(((PyObject *)(x)));
}


static PyLongObject * long_normalize (PyLongObject *v){
    Py_ssize_t j = (((((PyVarObject *)(v))->ob_size)) < 0 ? -((((PyVarObject *)(v))->ob_size)) : ((((PyVarObject *)(v))->ob_size)));
    Py_ssize_t i = j;
    while (i > 0 && v->ob_digit[i - 1] == 0)
        --i;
    if (i != j) {
        _Py_SET_SIZE(((PyVarObject *)(v)), ((((PyVarObject *)(v))->ob_size) < 0) ? -(i) : i);
    }
    return v;
}


extern  __attribute__((visibility("default"))) PyLongObject * _PyLong_New (Py_ssize_t size){
    PyLongObject *result;
    if (size > (Py_ssize_t)((((Py_ssize_t)(((size_t)-1) >> 1)) - __builtin_offsetof(PyLongObject, ob_digit)) / sizeof(digit))) {
        PyErr_SetString(PyExc_OverflowError, "too many digits in integer");
        return ((void *)0);
    }
    result = PyObject_Malloc(__builtin_offsetof(PyLongObject, ob_digit) + size * sizeof(digit));
    if (!result) {
        PyErr_NoMemory();
        return ((void *)0);
    }
    _PyObject_InitVar((PyVarObject *)result, &PyLong_Type, size);
    return result;
}


extern  __attribute__((visibility("default"))) PyObject * _PyLong_Copy (PyLongObject *src){
    PyLongObject *result;
    Py_ssize_t i;
    ;
    i = (((PyVarObject *)(src))->ob_size);
    if (i < 0)
        i = -(i);
    if (i < 2) {
        sdigit ival = (((void)(0)) , (((PyVarObject *)(src))->ob_size) < 0 ? -(sdigit)(src)->ob_digit[0] : ((((PyVarObject *)(src))->ob_size) == 0 ? (sdigit)0 : (sdigit)(src)->ob_digit[0]));
        if ((-5 <= (ival) && (ival) < 257)) {
            return get_small_int(ival);
        }
    }
    result = _PyLong_New(i);
    if (result != ((void *)0)) {
        _Py_SET_SIZE(((PyVarObject *)(result)), (((PyVarObject *)(src))->ob_size));
        while (--i >= 0)
            {
                result->ob_digit[i] = src->ob_digit[i];
            }
    }
    return (PyObject *)result;
}


extern  __attribute__((visibility("default"))) PyObject * PyLong_FromLong (long ival){
    PyLongObject *v;
    unsigned long abs_ival;
    unsigned long t;
    int ndigits = 0;
    int sign;
    if ((-5 <= (ival) && (ival) < 257)) {
        return get_small_int((sdigit)ival);
    }
    if (ival < 0) {
        abs_ival = 0U - (unsigned long)ival;
        sign = -1;
    } else {
        abs_ival = (unsigned long)ival;
        sign = ival == 0 ? 0 : 1;
    }
    if (!(abs_ival >> 30)) {
        v = _PyLong_New(1);
        if (v) {
            _Py_SET_SIZE(((PyVarObject *)(v)), sign);
            v->ob_digit[0] = (digit)(abs_ival);
        }
        return (PyObject *)v;
    }
    t = abs_ival;
    while (t)
        {
            ++ndigits;
            t >>= 30;
        }
    v = _PyLong_New(ndigits);
    if (v != ((void *)0)) {
        digit *p = v->ob_digit;
        _Py_SET_SIZE(((PyVarObject *)(v)), ndigits * sign);
        t = abs_ival;
        while (t)
            {
                *p++ = (digit)(t & ((digit)(((digit)1 << 30) - 1)));
                t >>= 30;
            }
    }
    return (PyObject *)v;
}


static int bit_length_digit (digit x){
    ;
    return _Py_bit_length((unsigned long)x);
}


extern  __attribute__((visibility("default"))) PyObject * PyLong_FromLongLong (long long ival){
    PyLongObject *v;
    unsigned long long abs_ival;
    unsigned long long t;
    int ndigits = 0;
    int negative = 0;
    if ((-5 <= (ival) && (ival) < 257)) {
        return get_small_int((sdigit)ival);
    }
    if (ival < 0) {
        abs_ival = (unsigned long long)(-1 - ival) + 1;
        negative = 1;
    } else {
        abs_ival = (unsigned long long)ival;
    }
    t = abs_ival;
    while (t)
        {
            ++ndigits;
            t >>= 30;
        }
    v = _PyLong_New(ndigits);
    if (v != ((void *)0)) {
        digit *p = v->ob_digit;
        _Py_SET_SIZE(((PyVarObject *)(v)), negative ? -ndigits : ndigits);
        t = abs_ival;
        while (t)
            {
                *p++ = (digit)(t & ((digit)(((digit)1 << 30) - 1)));
                t >>= 30;
            }
    }
    return (PyObject *)v;
}


static digit v_iadd (digit *x, Py_ssize_t m, digit *y, Py_ssize_t n){
    Py_ssize_t i;
    digit carry = 0;
    ;
    for (i = 0; i < n; ++i) {
        carry += x[i] + y[i];
        x[i] = carry & ((digit)(((digit)1 << 30) - 1));
        carry >>= 30;
        ;
    }
    for (; carry && i < m; ++i) {
        carry += x[i];
        x[i] = carry & ((digit)(((digit)1 << 30) - 1));
        carry >>= 30;
        ;
    }
    return carry;
}


static digit v_isub (digit *x, Py_ssize_t m, digit *y, Py_ssize_t n){
    Py_ssize_t i;
    digit borrow = 0;
    ;
    for (i = 0; i < n; ++i) {
        borrow = x[i] - y[i] - borrow;
        x[i] = borrow & ((digit)(((digit)1 << 30) - 1));
        borrow >>= 30;
        borrow &= 1;
    }
    for (; borrow && i < m; ++i) {
        borrow = x[i] - borrow;
        x[i] = borrow & ((digit)(((digit)1 << 30) - 1));
        borrow >>= 30;
        borrow &= 1;
    }
    return borrow;
}


static digit v_lshift (digit *z, digit *a, Py_ssize_t m, int d){
    Py_ssize_t i;
    digit carry = 0;
    ;
    for (i = 0; i < m; i++) {
        twodigits acc = (twodigits)a[i] << d | carry;
        z[i] = (digit)acc & ((digit)(((digit)1 << 30) - 1));
        carry = (digit)(acc >> 30);
    }
    return carry;
}


static digit v_rshift (digit *z, digit *a, Py_ssize_t m, int d){
    Py_ssize_t i;
    digit carry = 0;
    digit mask = ((digit)1 << d) - 1U;
    ;
    for (i = m; i-- > 0;) {
        twodigits acc = (twodigits)carry << 30 | a[i];
        carry = (digit)acc & mask;
        z[i] = (digit)(acc >> d);
    }
    return carry;
}


static digit inplace_divrem1 (digit *pout, digit *pin, Py_ssize_t size, digit n){
    twodigits rem = 0;
    ;
    pin += size;
    pout += size;
    while (--size >= 0)
        {
            digit hi;
            rem = (rem << 30) | *--pin;
            *--pout = hi = (digit)(rem / n);
            rem -= (twodigits)hi * n;
        }
    return (digit)rem;
}


static PyLongObject * divrem1 (PyLongObject *a, digit n, digit *prem){
    const Py_ssize_t size = (((((PyVarObject *)(a))->ob_size)) < 0 ? -((((PyVarObject *)(a))->ob_size)) : ((((PyVarObject *)(a))->ob_size)));
    PyLongObject *z;
    ;
    z = _PyLong_New(size);
    if (z == ((void *)0))
        return ((void *)0);
    *prem = inplace_divrem1(z->ob_digit, a->ob_digit, size, n);
    return long_normalize(z);
}


static int long_divrem (PyLongObject *a, PyLongObject *b, PyLongObject **pdiv, PyLongObject **prem){
    Py_ssize_t size_a = (((((PyVarObject *)(a))->ob_size)) < 0 ? -((((PyVarObject *)(a))->ob_size)) : ((((PyVarObject *)(a))->ob_size))), size_b = (((((PyVarObject *)(b))->ob_size)) < 0 ? -((((PyVarObject *)(b))->ob_size)) : ((((PyVarObject *)(b))->ob_size)));
    PyLongObject *z;
    if (size_b == 0) {
        PyErr_SetString(PyExc_ZeroDivisionError, "integer division or modulo by zero");
        return -1;
    }
    if (size_a < size_b || (size_a == size_b && a->ob_digit[size_a - 1] < b->ob_digit[size_b - 1])) {
        *prem = (PyLongObject *)long_long((PyObject *)a);
        if (*prem == ((void *)0)) {
            return -1;
        }
        PyObject *zero = _PyLong_GetZero();
        _Py_INCREF(((PyObject *)(zero)));
        *pdiv = (PyLongObject *)zero;
        return 0;
    }
    if (size_b == 1) {
        digit rem = 0;
        z = divrem1(a, b->ob_digit[0], &rem);
        if (z == ((void *)0))
            return -1;
        *prem = (PyLongObject *)PyLong_FromLong((long)rem);
        if (*prem == ((void *)0)) {
            _Py_DECREF(((PyObject *)(z)));
            return -1;
        }
    } else {
        z = x_divrem(a, b, prem);
        if (z == ((void *)0))
            return -1;
    }
    if (((((PyVarObject *)(a))->ob_size) < 0) != ((((PyVarObject *)(b))->ob_size) < 0)) {
        _PyLong_Negate(&z);
        if (z == ((void *)0)) {
            do {
                PyObject *_py_tmp = ((PyObject *)(*prem));
                if (_py_tmp != ((void *)0)) {
                    (*prem) = ((void *)0);
                    _Py_DECREF(((PyObject *)(_py_tmp)));
                }
            } while (0);
            return -1;
        }
    }
    if ((((PyVarObject *)(a))->ob_size) < 0 && (((PyVarObject *)(*prem))->ob_size) != 0) {
        _PyLong_Negate(prem);
        if (*prem == ((void *)0)) {
            _Py_DECREF(((PyObject *)(z)));
            do {
                PyObject *_py_tmp = ((PyObject *)(*prem));
                if (_py_tmp != ((void *)0)) {
                    (*prem) = ((void *)0);
                    _Py_DECREF(((PyObject *)(_py_tmp)));
                }
            } while (0);
            return -1;
        }
    }
    *pdiv = maybe_small_long(z);
    return 0;
}


static PyLongObject * x_divrem (PyLongObject *v1, PyLongObject *w1, PyLongObject **prem){
    PyLongObject *v, *w, *a;
    Py_ssize_t i, k, size_v, size_w;
    int d;
    digit wm1, wm2, carry, q, r, vtop, *v0, *vk, *w0, *ak;
    twodigits vv;
    sdigit zhi;
    stwodigits z;
    size_v = (((((PyVarObject *)(v1))->ob_size)) < 0 ? -((((PyVarObject *)(v1))->ob_size)) : ((((PyVarObject *)(v1))->ob_size)));
    size_w = (((((PyVarObject *)(w1))->ob_size)) < 0 ? -((((PyVarObject *)(w1))->ob_size)) : ((((PyVarObject *)(w1))->ob_size)));
    ;
    v = _PyLong_New(size_v + 1);
    if (v == ((void *)0)) {
        *prem = ((void *)0);
        return ((void *)0);
    }
    w = _PyLong_New(size_w);
    if (w == ((void *)0)) {
        _Py_DECREF(((PyObject *)(v)));
        *prem = ((void *)0);
        return ((void *)0);
    }
    d = 30 - bit_length_digit(w1->ob_digit[size_w - 1]);
    carry = v_lshift(w->ob_digit, w1->ob_digit, size_w, d);
    ;
    carry = v_lshift(v->ob_digit, v1->ob_digit, size_v, d);
    if (carry != 0 || v->ob_digit[size_v - 1] >= w->ob_digit[size_w - 1]) {
        v->ob_digit[size_v] = carry;
        size_v++;
    }
    k = size_v - size_w;
    ;
    a = _PyLong_New(k);
    if (a == ((void *)0)) {
        _Py_DECREF(((PyObject *)(w)));
        _Py_DECREF(((PyObject *)(v)));
        *prem = ((void *)0);
        return ((void *)0);
    }
    v0 = v->ob_digit;
    w0 = w->ob_digit;
    wm1 = w0[size_w - 1];
    wm2 = w0[size_w - 2];
    for (vk = v0 + k , ak = a->ob_digit + k; vk-- > v0;) {
        do {
            if (PyErr_CheckSignals()) {
                _Py_DECREF(((PyObject *)(a)));
                _Py_DECREF(((PyObject *)(w)));
                _Py_DECREF(((PyObject *)(v)));
                *prem = ((void *)0);
                return ((void *)0);
            }
        } while (0);
        vtop = vk[size_w];
        ;
        vv = ((twodigits)vtop << 30) | vk[size_w - 1];
        q = (digit)(vv / wm1);
        r = (digit)(vv - (twodigits)wm1 * q);
        while ((twodigits)wm2 * q > (((twodigits)r << 30) | vk[size_w - 2]))
            {
                --q;
                r += wm1;
                if (r >= ((digit)1 << 30))
                    break;
                ;
            }
        ;
        zhi = 0;
        for (i = 0; i < size_w; ++i) {
            z = (sdigit)vk[i] + zhi - (stwodigits)q * (stwodigits)w0[i];
            vk[i] = (digit)z & ((digit)(((digit)1 << 30) - 1));
            zhi = (sdigit)((z) >> (30));
        }
        ;
        if ((sdigit)vtop + zhi < 0) {
            carry = 0;
            for (i = 0; i < size_w; ++i) {
                carry += vk[i] + w0[i];
                vk[i] = carry & ((digit)(((digit)1 << 30) - 1));
                carry >>= 30;
            }
            --q;
        }
        ;
        *--ak = q;
    }
    carry = v_rshift(w0, v0, size_w, d);
    ;
    _Py_DECREF(((PyObject *)(v)));
    *prem = long_normalize(w);
    return long_normalize(a);
}


static Py_ssize_t long_compare (PyLongObject *a, PyLongObject *b){
    Py_ssize_t sign = (((PyVarObject *)(a))->ob_size) - (((PyVarObject *)(b))->ob_size);
    if (sign == 0) {
        Py_ssize_t i = (((((PyVarObject *)(a))->ob_size)) < 0 ? -((((PyVarObject *)(a))->ob_size)) : ((((PyVarObject *)(a))->ob_size)));
        sdigit diff = 0;
        while (--i >= 0)
            {
                diff = (sdigit)a->ob_digit[i] - (sdigit)b->ob_digit[i];
                if (diff) {
                    break;
                    ;
                }
            }
        sign = (((PyVarObject *)(a))->ob_size) < 0 ? -diff : diff;
    }
    return sign;
}


static PyLongObject * x_add (PyLongObject *a, PyLongObject *b){
    Py_ssize_t size_a = (((((PyVarObject *)(a))->ob_size)) < 0 ? -((((PyVarObject *)(a))->ob_size)) : ((((PyVarObject *)(a))->ob_size))), size_b = (((((PyVarObject *)(b))->ob_size)) < 0 ? -((((PyVarObject *)(b))->ob_size)) : ((((PyVarObject *)(b))->ob_size)));
    PyLongObject *z;
    Py_ssize_t i;
    digit carry = 0;
    if (size_a < size_b) {
        {
            PyLongObject *temp = a;
            a = b;
            b = temp;
        }
        {
            Py_ssize_t size_temp = size_a;
            size_a = size_b;
            size_b = size_temp;
        }
    }
    z = _PyLong_New(size_a + 1);
    if (z == ((void *)0))
        return ((void *)0);
    for (i = 0; i < size_b; ++i) {
        carry += a->ob_digit[i] + b->ob_digit[i];
        z->ob_digit[i] = carry & ((digit)(((digit)1 << 30) - 1));
        carry >>= 30;
    }
    for (; i < size_a; ++i) {
        carry += a->ob_digit[i];
        z->ob_digit[i] = carry & ((digit)(((digit)1 << 30) - 1));
        carry >>= 30;
    }
    z->ob_digit[i] = carry;
    return long_normalize(z);
}


static PyLongObject * x_sub (PyLongObject *a, PyLongObject *b){
    Py_ssize_t size_a = (((((PyVarObject *)(a))->ob_size)) < 0 ? -((((PyVarObject *)(a))->ob_size)) : ((((PyVarObject *)(a))->ob_size))), size_b = (((((PyVarObject *)(b))->ob_size)) < 0 ? -((((PyVarObject *)(b))->ob_size)) : ((((PyVarObject *)(b))->ob_size)));
    PyLongObject *z;
    Py_ssize_t i;
    int sign = 1;
    digit borrow = 0;
    if (size_a < size_b) {
        sign = -1;
        {
            PyLongObject *temp = a;
            a = b;
            b = temp;
        }
        {
            Py_ssize_t size_temp = size_a;
            size_a = size_b;
            size_b = size_temp;
        }
    } else if (size_a == size_b) {
        i = size_a;
        while (--i >= 0 && a->ob_digit[i] == b->ob_digit[i])
            ;
        if (i < 0)
            return (PyLongObject *)PyLong_FromLong(0);
        if (a->ob_digit[i] < b->ob_digit[i]) {
            sign = -1;
            {
                PyLongObject *temp = a;
                a = b;
                b = temp;
            }
        }
        size_a = size_b = i + 1;
    }
    z = _PyLong_New(size_a);
    if (z == ((void *)0))
        return ((void *)0);
    for (i = 0; i < size_b; ++i) {
        borrow = a->ob_digit[i] - b->ob_digit[i] - borrow;
        z->ob_digit[i] = borrow & ((digit)(((digit)1 << 30) - 1));
        borrow >>= 30;
        borrow &= 1;
    }
    for (; i < size_a; ++i) {
        borrow = a->ob_digit[i] - borrow;
        z->ob_digit[i] = borrow & ((digit)(((digit)1 << 30) - 1));
        borrow >>= 30;
        borrow &= 1;
    }
    ;
    if (sign < 0) {
        _Py_SET_SIZE(((PyVarObject *)(z)), -(((PyVarObject *)(z))->ob_size));
    }
    return maybe_small_long(long_normalize(z));
}


static PyObject * long_add (PyLongObject *a, PyLongObject *b){
    PyLongObject *z;
    do {
        if (!PyType_HasFeature((((PyObject *)(a))->ob_type), (1UL << 24)) || !PyType_HasFeature((((PyObject *)(b))->ob_type), (1UL << 24)))
            return _Py_NewRef(((PyObject *)((&_Py_NotImplementedStruct))));
    } while (0);
    if ((((((PyVarObject *)(a))->ob_size)) < 0 ? -((((PyVarObject *)(a))->ob_size)) : ((((PyVarObject *)(a))->ob_size))) <= 1 && (((((PyVarObject *)(b))->ob_size)) < 0 ? -((((PyVarObject *)(b))->ob_size)) : ((((PyVarObject *)(b))->ob_size))) <= 1) {
        return PyLong_FromLong((((void)(0)) , (((PyVarObject *)(a))->ob_size) < 0 ? -(sdigit)(a)->ob_digit[0] : ((((PyVarObject *)(a))->ob_size) == 0 ? (sdigit)0 : (sdigit)(a)->ob_digit[0])) + (((void)(0)) , (((PyVarObject *)(b))->ob_size) < 0 ? -(sdigit)(b)->ob_digit[0] : ((((PyVarObject *)(b))->ob_size) == 0 ? (sdigit)0 : (sdigit)(b)->ob_digit[0])));
    }
    if ((((PyVarObject *)(a))->ob_size) < 0) {
        if ((((PyVarObject *)(b))->ob_size) < 0) {
            z = x_add(a, b);
            if (z != ((void *)0)) {
                ;
                _Py_SET_SIZE(((PyVarObject *)(z)), -((((PyVarObject *)(z))->ob_size)));
            }
        } else
            z = x_sub(b, a);
    } else {
        if ((((PyVarObject *)(b))->ob_size) < 0) {
            z = x_sub(a, b);
        } else
            z = x_add(a, b);
    }
    return (PyObject *)z;
}


static PyObject * long_sub (PyLongObject *a, PyLongObject *b){
    PyLongObject *z;
    do {
        if (!PyType_HasFeature((((PyObject *)(a))->ob_type), (1UL << 24)) || !PyType_HasFeature((((PyObject *)(b))->ob_type), (1UL << 24)))
            return _Py_NewRef(((PyObject *)((&_Py_NotImplementedStruct))));
    } while (0);
    if ((((((PyVarObject *)(a))->ob_size)) < 0 ? -((((PyVarObject *)(a))->ob_size)) : ((((PyVarObject *)(a))->ob_size))) <= 1 && (((((PyVarObject *)(b))->ob_size)) < 0 ? -((((PyVarObject *)(b))->ob_size)) : ((((PyVarObject *)(b))->ob_size))) <= 1) {
        return PyLong_FromLong((((void)(0)) , (((PyVarObject *)(a))->ob_size) < 0 ? -(sdigit)(a)->ob_digit[0] : ((((PyVarObject *)(a))->ob_size) == 0 ? (sdigit)0 : (sdigit)(a)->ob_digit[0])) - (((void)(0)) , (((PyVarObject *)(b))->ob_size) < 0 ? -(sdigit)(b)->ob_digit[0] : ((((PyVarObject *)(b))->ob_size) == 0 ? (sdigit)0 : (sdigit)(b)->ob_digit[0])));
    }
    if ((((PyVarObject *)(a))->ob_size) < 0) {
        if ((((PyVarObject *)(b))->ob_size) < 0) {
            z = x_sub(b, a);
        } else {
            z = x_add(a, b);
            if (z != ((void *)0)) {
                ;
                _Py_SET_SIZE(((PyVarObject *)(z)), -((((PyVarObject *)(z))->ob_size)));
            }
        }
    } else {
        if ((((PyVarObject *)(b))->ob_size) < 0) {
            z = x_add(a, b);
        } else
            z = x_sub(a, b);
    }
    return (PyObject *)z;
}


static PyLongObject * x_mul (PyLongObject *a, PyLongObject *b){
    PyLongObject *z;
    Py_ssize_t size_a = (((((PyVarObject *)(a))->ob_size)) < 0 ? -((((PyVarObject *)(a))->ob_size)) : ((((PyVarObject *)(a))->ob_size)));
    Py_ssize_t size_b = (((((PyVarObject *)(b))->ob_size)) < 0 ? -((((PyVarObject *)(b))->ob_size)) : ((((PyVarObject *)(b))->ob_size)));
    Py_ssize_t i;
    z = _PyLong_New(size_a + size_b);
    if (z == ((void *)0))
        return ((void *)0);
    memset(z->ob_digit, 0, (((PyVarObject *)(z))->ob_size) * sizeof(digit));
    if (a == b) {
        for (i = 0; i < size_a; ++i) {
            twodigits carry;
            twodigits f = a->ob_digit[i];
            digit *pz = z->ob_digit + (i << 1);
            digit *pa = a->ob_digit + i + 1;
            digit *paend = a->ob_digit + size_a;
            do {
                if (PyErr_CheckSignals()) {
                    _Py_DECREF(((PyObject *)(z)));
                    return ((void *)0);
                }
            } while (0);
            carry = *pz + f * f;
            *pz++ = (digit)(carry & ((digit)(((digit)1 << 30) - 1)));
            carry >>= 30;
            ;
            f <<= 1;
            while (pa < paend)
                {
                    carry += *pz + *pa++ * f;
                    *pz++ = (digit)(carry & ((digit)(((digit)1 << 30) - 1)));
                    carry >>= 30;
                    ;
                }
            if (carry) {
                carry += *pz;
                *pz++ = (digit)(carry & ((digit)(((digit)1 << 30) - 1)));
                carry >>= 30;
            }
            if (carry)
                *pz += (digit)(carry & ((digit)(((digit)1 << 30) - 1)));
            ;
        }
    } else {
        for (i = 0; i < size_a; ++i) {
            twodigits carry = 0;
            twodigits f = a->ob_digit[i];
            digit *pz = z->ob_digit + i;
            digit *pb = b->ob_digit;
            digit *pbend = b->ob_digit + size_b;
            do {
                if (PyErr_CheckSignals()) {
                    _Py_DECREF(((PyObject *)(z)));
                    return ((void *)0);
                }
            } while (0);
            while (pb < pbend)
                {
                    carry += *pz + *pb++ * f;
                    *pz++ = (digit)(carry & ((digit)(((digit)1 << 30) - 1)));
                    carry >>= 30;
                    ;
                }
            if (carry)
                *pz += (digit)(carry & ((digit)(((digit)1 << 30) - 1)));
            ;
        }
    }
    return long_normalize(z);
}


static int kmul_split (PyLongObject *n, Py_ssize_t size, PyLongObject **high, PyLongObject **low){
    PyLongObject *hi, *lo;
    Py_ssize_t size_lo, size_hi;
    const Py_ssize_t size_n = (((((PyVarObject *)(n))->ob_size)) < 0 ? -((((PyVarObject *)(n))->ob_size)) : ((((PyVarObject *)(n))->ob_size)));
    size_lo = (((size_n) > (size)) ? (size) : (size_n));
    size_hi = size_n - size_lo;
    if ((hi = _PyLong_New(size_hi)) == ((void *)0))
        return -1;
    if ((lo = _PyLong_New(size_lo)) == ((void *)0)) {
        _Py_DECREF(((PyObject *)(hi)));
        return -1;
    }
    memcpy(lo->ob_digit, n->ob_digit, size_lo * sizeof(digit));
    memcpy(hi->ob_digit, n->ob_digit + size_lo, size_hi * sizeof(digit));
    *high = long_normalize(hi);
    *low = long_normalize(lo);
    return 0;
}


static PyLongObject * k_mul (PyLongObject *a, PyLongObject *b){
    Py_ssize_t asize = (((((PyVarObject *)(a))->ob_size)) < 0 ? -((((PyVarObject *)(a))->ob_size)) : ((((PyVarObject *)(a))->ob_size)));
    Py_ssize_t bsize = (((((PyVarObject *)(b))->ob_size)) < 0 ? -((((PyVarObject *)(b))->ob_size)) : ((((PyVarObject *)(b))->ob_size)));
    PyLongObject *ah = ((void *)0);
    PyLongObject *al = ((void *)0);
    PyLongObject *bh = ((void *)0);
    PyLongObject *bl = ((void *)0);
    PyLongObject *ret = ((void *)0);
    PyLongObject *t1, *t2, *t3;
    Py_ssize_t shift;
    Py_ssize_t i;
    if (asize > bsize) {
        t1 = a;
        a = b;
        b = t1;
        i = asize;
        asize = bsize;
        bsize = i;
    }
    i = a == b ? (2 * 70) : 70;
    if (asize <= i) {
        if (asize == 0) {
            return (PyLongObject *)PyLong_FromLong(0);
        } else
            return x_mul(a, b);
    }
    if (2 * asize <= bsize)
        return k_lopsided_mul(a, b);
    shift = bsize >> 1;
    if (kmul_split(a, shift, &ah, &al) < 0)
        goto fail;
    ;
    ;
    if (a == b) {
        bh = ah;
        bl = al;
        _Py_INCREF(((PyObject *)(bh)));
        _Py_INCREF(((PyObject *)(bl)));
    } else if (kmul_split(b, shift, &bh, &bl) < 0)
        goto fail;
    ;
    ret = _PyLong_New(asize + bsize);
    if (ret == ((void *)0))
        goto fail;
    ;
    if ((t1 = k_mul(ah, bh)) == ((void *)0))
        goto fail;
    ;
    ;
    ;
    memcpy(ret->ob_digit + 2 * shift, t1->ob_digit, (((PyVarObject *)(t1))->ob_size) * sizeof(digit));
    i = (((PyVarObject *)(ret))->ob_size) - 2 * shift - (((PyVarObject *)(t1))->ob_size);
    if (i)
        memset(ret->ob_digit + 2 * shift + (((PyVarObject *)(t1))->ob_size), 0, i * sizeof(digit));
    if ((t2 = k_mul(al, bl)) == ((void *)0)) {
        _Py_DECREF(((PyObject *)(t1)));
        goto fail;
        ;
    }
    ;
    ;
    memcpy(ret->ob_digit, t2->ob_digit, (((PyVarObject *)(t2))->ob_size) * sizeof(digit));
    i = 2 * shift - (((PyVarObject *)(t2))->ob_size);
    if (i)
        memset(ret->ob_digit + (((PyVarObject *)(t2))->ob_size), 0, i * sizeof(digit));
    i = (((PyVarObject *)(ret))->ob_size) - shift;
    (void)v_isub(ret->ob_digit + shift, i, t2->ob_digit, (((PyVarObject *)(t2))->ob_size));
    _Py_DECREF(((PyObject *)(t2)));
    (void)v_isub(ret->ob_digit + shift, i, t1->ob_digit, (((PyVarObject *)(t1))->ob_size));
    _Py_DECREF(((PyObject *)(t1)));
    if ((t1 = x_add(ah, al)) == ((void *)0))
        goto fail;
    ;
    _Py_DECREF(((PyObject *)(ah)));
    _Py_DECREF(((PyObject *)(al)));
    ah = al = ((void *)0);
    if (a == b) {
        t2 = t1;
        _Py_INCREF(((PyObject *)(t2)));
    } else if ((t2 = x_add(bh, bl)) == ((void *)0)) {
        _Py_DECREF(((PyObject *)(t1)));
        goto fail;
        ;
    }
    _Py_DECREF(((PyObject *)(bh)));
    _Py_DECREF(((PyObject *)(bl)));
    bh = bl = ((void *)0);
    t3 = k_mul(t1, t2);
    _Py_DECREF(((PyObject *)(t1)));
    _Py_DECREF(((PyObject *)(t2)));
    if (t3 == ((void *)0))
        goto fail;
    ;
    ;
    (void)v_iadd(ret->ob_digit + shift, i, t3->ob_digit, (((PyVarObject *)(t3))->ob_size));
    _Py_DECREF(((PyObject *)(t3)));
    return long_normalize(ret);
  fail:
    _Py_XDECREF(((PyObject *)(ret)));
    _Py_XDECREF(((PyObject *)(ah)));
    _Py_XDECREF(((PyObject *)(al)));
    _Py_XDECREF(((PyObject *)(bh)));
    _Py_XDECREF(((PyObject *)(bl)));
    return ((void *)0);
}


static PyLongObject * k_lopsided_mul (PyLongObject *a, PyLongObject *b){
    const Py_ssize_t asize = (((((PyVarObject *)(a))->ob_size)) < 0 ? -((((PyVarObject *)(a))->ob_size)) : ((((PyVarObject *)(a))->ob_size)));
    Py_ssize_t bsize = (((((PyVarObject *)(b))->ob_size)) < 0 ? -((((PyVarObject *)(b))->ob_size)) : ((((PyVarObject *)(b))->ob_size)));
    Py_ssize_t nbdone;
    PyLongObject *ret;
    PyLongObject *bslice = ((void *)0);
    ;
    ;
    ret = _PyLong_New(asize + bsize);
    if (ret == ((void *)0))
        return ((void *)0);
    memset(ret->ob_digit, 0, (((PyVarObject *)(ret))->ob_size) * sizeof(digit));
    bslice = _PyLong_New(asize);
    if (bslice == ((void *)0))
        goto fail;
    ;
    nbdone = 0;
    while (bsize > 0)
        {
            PyLongObject *product;
            const Py_ssize_t nbtouse = (((bsize) > (asize)) ? (asize) : (bsize));
            memcpy(bslice->ob_digit, b->ob_digit + nbdone, nbtouse * sizeof(digit));
            _Py_SET_SIZE(((PyVarObject *)(bslice)), nbtouse);
            product = k_mul(a, bslice);
            if (product == ((void *)0))
                goto fail;
            ;
            (void)v_iadd(ret->ob_digit + nbdone, (((PyVarObject *)(ret))->ob_size) - nbdone, product->ob_digit, (((PyVarObject *)(product))->ob_size));
            _Py_DECREF(((PyObject *)(product)));
            bsize -= nbtouse;
            nbdone += nbtouse;
        }
    _Py_DECREF(((PyObject *)(bslice)));
    return long_normalize(ret);
  fail:
    _Py_DECREF(((PyObject *)(ret)));
    _Py_XDECREF(((PyObject *)(bslice)));
    return ((void *)0);
}


static PyObject * long_mul (PyLongObject *a, PyLongObject *b){
    PyLongObject *z;
    do {
        if (!PyType_HasFeature((((PyObject *)(a))->ob_type), (1UL << 24)) || !PyType_HasFeature((((PyObject *)(b))->ob_type), (1UL << 24)))
            return _Py_NewRef(((PyObject *)((&_Py_NotImplementedStruct))));
    } while (0);
    if ((((((PyVarObject *)(a))->ob_size)) < 0 ? -((((PyVarObject *)(a))->ob_size)) : ((((PyVarObject *)(a))->ob_size))) <= 1 && (((((PyVarObject *)(b))->ob_size)) < 0 ? -((((PyVarObject *)(b))->ob_size)) : ((((PyVarObject *)(b))->ob_size))) <= 1) {
        stwodigits v = (stwodigits)((((void)(0)) , (((PyVarObject *)(a))->ob_size) < 0 ? -(sdigit)(a)->ob_digit[0] : ((((PyVarObject *)(a))->ob_size) == 0 ? (sdigit)0 : (sdigit)(a)->ob_digit[0]))) * (((void)(0)) , (((PyVarObject *)(b))->ob_size) < 0 ? -(sdigit)(b)->ob_digit[0] : ((((PyVarObject *)(b))->ob_size) == 0 ? (sdigit)0 : (sdigit)(b)->ob_digit[0]));
        return PyLong_FromLongLong((long long)v);
    }
    z = k_mul(a, b);
    if ((((((PyVarObject *)(a))->ob_size) ^ (((PyVarObject *)(b))->ob_size)) < 0) && z) {
        _PyLong_Negate(&z);
        if (z == ((void *)0))
            return ((void *)0);
    }
    return (PyObject *)z;
}


static PyObject * fast_mod (PyLongObject *a, PyLongObject *b){
    sdigit left = a->ob_digit[0];
    sdigit right = b->ob_digit[0];
    sdigit mod;
    ;
    ;
    if ((((PyVarObject *)(a))->ob_size) == (((PyVarObject *)(b))->ob_size)) {
        mod = left % right;
    } else {
        mod = right - 1 - (left - 1) % right;
    }
    return PyLong_FromLong(mod * (sdigit)(((PyVarObject *)(b))->ob_size));
}


static PyObject * fast_floor_div (PyLongObject *a, PyLongObject *b){
    sdigit left = a->ob_digit[0];
    sdigit right = b->ob_digit[0];
    sdigit div;
    ;
    ;
    if ((((PyVarObject *)(a))->ob_size) == (((PyVarObject *)(b))->ob_size)) {
        div = left / right;
    } else {
        div = -1 - (left - 1) / right;
    }
    return PyLong_FromLong(div);
}


static int l_divmod (PyLongObject *v, PyLongObject *w, PyLongObject **pdiv, PyLongObject **pmod){
    PyLongObject *div, *mod;
    if ((((((PyVarObject *)(v))->ob_size)) < 0 ? -((((PyVarObject *)(v))->ob_size)) : ((((PyVarObject *)(v))->ob_size))) == 1 && (((((PyVarObject *)(w))->ob_size)) < 0 ? -((((PyVarObject *)(w))->ob_size)) : ((((PyVarObject *)(w))->ob_size))) == 1) {
        div = ((void *)0);
        if (pdiv != ((void *)0)) {
            div = (PyLongObject *)fast_floor_div(v, w);
            if (div == ((void *)0)) {
                return -1;
            }
        }
        if (pmod != ((void *)0)) {
            mod = (PyLongObject *)fast_mod(v, w);
            if (mod == ((void *)0)) {
                _Py_XDECREF(((PyObject *)(div)));
                return -1;
            }
            *pmod = mod;
        }
        if (pdiv != ((void *)0)) {
            *pdiv = div;
        }
        return 0;
    }
    if (long_divrem(v, w, &div, &mod) < 0)
        return -1;
    if (((((PyVarObject *)(mod))->ob_size) < 0 && (((PyVarObject *)(w))->ob_size) > 0) || ((((PyVarObject *)(mod))->ob_size) > 0 && (((PyVarObject *)(w))->ob_size) < 0)) {
        PyLongObject *temp;
        temp = (PyLongObject *)long_add(mod, w);
        _Py_DECREF(((PyObject *)(mod)));
        mod = temp;
        if (mod == ((void *)0)) {
            _Py_DECREF(((PyObject *)(div)));
            return -1;
        }
        temp = (PyLongObject *)long_sub(div, (PyLongObject *)_PyLong_GetOne());
        if (temp == ((void *)0)) {
            _Py_DECREF(((PyObject *)(mod)));
            _Py_DECREF(((PyObject *)(div)));
            return -1;
        }
        _Py_DECREF(((PyObject *)(div)));
        div = temp;
    }
    if (pdiv != ((void *)0))
        *pdiv = div;
    else
        _Py_DECREF(((PyObject *)(div)));
    if (pmod != ((void *)0))
        *pmod = mod;
    else
        _Py_DECREF(((PyObject *)(mod)));
    return 0;
}


static PyLongObject * long_invmod (PyLongObject *a, PyLongObject *n){
    PyLongObject *b, *c;
    ;
    b = (PyLongObject *)PyLong_FromLong(1L);
    if (b == ((void *)0)) {
        return ((void *)0);
    }
    c = (PyLongObject *)PyLong_FromLong(0L);
    if (c == ((void *)0)) {
        _Py_DECREF(((PyObject *)(b)));
        return ((void *)0);
    }
    _Py_INCREF(((PyObject *)(a)));
    _Py_INCREF(((PyObject *)(n)));
    while ((((PyVarObject *)(n))->ob_size) != 0)
        {
            PyLongObject *q, *r, *s, *t;
            if (l_divmod(a, n, &q, &r) == -1) {
                goto Error;
                ;
            }
            _Py_DECREF(((PyObject *)(a)));
            a = n;
            n = r;
            t = (PyLongObject *)long_mul(q, c);
            _Py_DECREF(((PyObject *)(q)));
            if (t == ((void *)0)) {
                goto Error;
                ;
            }
            s = (PyLongObject *)long_sub(b, t);
            _Py_DECREF(((PyObject *)(t)));
            if (s == ((void *)0)) {
                goto Error;
                ;
            }
            _Py_DECREF(((PyObject *)(b)));
            b = c;
            c = s;
        }
    _Py_DECREF(((PyObject *)(c)));
    _Py_DECREF(((PyObject *)(n)));
    if (long_compare(a, (PyLongObject *)_PyLong_GetOne())) {
        _Py_DECREF(((PyObject *)(a)));
        _Py_DECREF(((PyObject *)(b)));
        PyErr_SetString(PyExc_ValueError, "base is not invertible for the given modulus");
        return ((void *)0);
    } else {
        _Py_DECREF(((PyObject *)(a)));
        return b;
    }
  Error:
    _Py_DECREF(((PyObject *)(a)));
    _Py_DECREF(((PyObject *)(b)));
    _Py_DECREF(((PyObject *)(c)));
    _Py_DECREF(((PyObject *)(n)));
    return ((void *)0);
}


static PyObject * long_pow (PyObject *v, PyObject *w, PyObject *x){
    PyLongObject *a, *b, *c;
    int negativeOutput = 0;
    PyLongObject *z = ((void *)0);
    Py_ssize_t i, j, k;
    PyLongObject *temp = ((void *)0);
    PyLongObject *table[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    do {
        if (!PyType_HasFeature((((PyObject *)(v))->ob_type), (1UL << 24)) || !PyType_HasFeature((((PyObject *)(w))->ob_type), (1UL << 24)))
            return _Py_NewRef(((PyObject *)((&_Py_NotImplementedStruct))));
    } while (0);
    a = (PyLongObject *)v;
    _Py_INCREF(((PyObject *)(a)));
    b = (PyLongObject *)w;
    _Py_INCREF(((PyObject *)(b)));
    if (PyType_HasFeature((((PyObject *)(x))->ob_type), (1UL << 24))) {
        c = (PyLongObject *)x;
        _Py_INCREF(((PyObject *)(x)));
    } else if (x == (&_Py_NoneStruct)) {
        c = ((void *)0);
    } else {
        _Py_DECREF(((PyObject *)(a)));
        _Py_DECREF(((PyObject *)(b)));
        return _Py_NewRef(((PyObject *)((&_Py_NotImplementedStruct))));
    }
    if ((((PyVarObject *)(b))->ob_size) < 0 && c == ((void *)0)) {
        _Py_DECREF(((PyObject *)(a)));
        _Py_DECREF(((PyObject *)(b)));
        return PyFloat_Type.tp_as_number->nb_power(v, w, x);
    }
    if (c) {
        if ((((PyVarObject *)(c))->ob_size) == 0) {
            PyErr_SetString(PyExc_ValueError, "pow() 3rd argument cannot be 0");
            goto Error;
            ;
        }
        if ((((PyVarObject *)(c))->ob_size) < 0) {
            negativeOutput = 1;
            temp = (PyLongObject *)_PyLong_Copy(c);
            if (temp == ((void *)0))
                goto Error;
            ;
            _Py_DECREF(((PyObject *)(c)));
            c = temp;
            temp = ((void *)0);
            _PyLong_Negate(&c);
            if (c == ((void *)0))
                goto Error;
            ;
        }
        if (((((PyVarObject *)(c))->ob_size) == 1) && (c->ob_digit[0] == 1)) {
            z = (PyLongObject *)PyLong_FromLong(0L);
            goto Done;
            ;
        }
        if ((((PyVarObject *)(b))->ob_size) < 0) {
            temp = (PyLongObject *)_PyLong_Copy(b);
            if (temp == ((void *)0))
                goto Error;
            ;
            _Py_DECREF(((PyObject *)(b)));
            b = temp;
            temp = ((void *)0);
            _PyLong_Negate(&b);
            if (b == ((void *)0))
                goto Error;
            ;
            temp = long_invmod(a, c);
            if (temp == ((void *)0))
                goto Error;
            ;
            _Py_DECREF(((PyObject *)(a)));
            a = temp;
            temp = ((void *)0);
        }
        if ((((PyVarObject *)(a))->ob_size) < 0 || (((PyVarObject *)(a))->ob_size) > (((PyVarObject *)(c))->ob_size)) {
            if (l_divmod(a, c, ((void *)0), &temp) < 0)
                goto Error;
            ;
            _Py_DECREF(((PyObject *)(a)));
            a = temp;
            temp = ((void *)0);
        }
    }
    z = (PyLongObject *)PyLong_FromLong(1L);
    if (z == ((void *)0))
        goto Error;
    ;
    if ((((PyVarObject *)(b))->ob_size) <= 8) {
        for (i = (((PyVarObject *)(b))->ob_size) - 1; i >= 0; --i) {
            digit bi = b->ob_digit[i];
            for (j = (digit)1 << (30 - 1); j != 0; j >>= 1) {
                do {
                    temp = (PyLongObject *)long_mul(z, z);
                    if (temp == ((void *)0))
                        goto Error;
                    _Py_XDECREF(((PyObject *)(z)));
                    z = temp;
                    temp = ((void *)0);
                    do {
                        if (c != ((void *)0)) {
                            if (l_divmod(z, c, ((void *)0), &temp) < 0)
                                goto Error;
                            _Py_XDECREF(((PyObject *)(z)));
                            z = temp;
                            temp = ((void *)0);
                        }
                    } while (0);
                } while (0);
                if (bi & j)
                    do {
                        temp = (PyLongObject *)long_mul(z, a);
                        if (temp == ((void *)0))
                            goto Error;
                        _Py_XDECREF(((PyObject *)(z)));
                        z = temp;
                        temp = ((void *)0);
                        do {
                            if (c != ((void *)0)) {
                                if (l_divmod(z, c, ((void *)0), &temp) < 0)
                                    goto Error;
                                _Py_XDECREF(((PyObject *)(z)));
                                z = temp;
                                temp = ((void *)0);
                            }
                        } while (0);
                    } while (0);
            }
        }
    } else {
        _Py_INCREF(((PyObject *)(z)));
        table[0] = z;
        for (i = 1; i < 32; ++i)
            do {
                temp = (PyLongObject *)long_mul(table[i - 1], a);
                if (temp == ((void *)0))
                    goto Error;
                _Py_XDECREF(((PyObject *)(table[i])));
                table[i] = temp;
                temp = ((void *)0);
                do {
                    if (c != ((void *)0)) {
                        if (l_divmod(table[i], c, ((void *)0), &temp) < 0)
                            goto Error;
                        _Py_XDECREF(((PyObject *)(table[i])));
                        table[i] = temp;
                        temp = ((void *)0);
                    }
                } while (0);
            } while (0);
        for (i = (((PyVarObject *)(b))->ob_size) - 1; i >= 0; --i) {
            const digit bi = b->ob_digit[i];
            for (j = 30 - 5; j >= 0; j -= 5) {
                const int index = (bi >> j) & 31;
                for (k = 0; k < 5; ++k)
                    do {
                        temp = (PyLongObject *)long_mul(z, z);
                        if (temp == ((void *)0))
                            goto Error;
                        _Py_XDECREF(((PyObject *)(z)));
                        z = temp;
                        temp = ((void *)0);
                        do {
                            if (c != ((void *)0)) {
                                if (l_divmod(z, c, ((void *)0), &temp) < 0)
                                    goto Error;
                                _Py_XDECREF(((PyObject *)(z)));
                                z = temp;
                                temp = ((void *)0);
                            }
                        } while (0);
                    } while (0);
                if (index)
                    do {
                        temp = (PyLongObject *)long_mul(z, table[index]);
                        if (temp == ((void *)0))
                            goto Error;
                        _Py_XDECREF(((PyObject *)(z)));
                        z = temp;
                        temp = ((void *)0);
                        do {
                            if (c != ((void *)0)) {
                                if (l_divmod(z, c, ((void *)0), &temp) < 0)
                                    goto Error;
                                _Py_XDECREF(((PyObject *)(z)));
                                z = temp;
                                temp = ((void *)0);
                            }
                        } while (0);
                    } while (0);
            }
        }
    }
    if (negativeOutput && ((((PyVarObject *)(z))->ob_size) != 0)) {
        temp = (PyLongObject *)long_sub(z, c);
        if (temp == ((void *)0))
            goto Error;
        ;
        _Py_DECREF(((PyObject *)(z)));
        z = temp;
        temp = ((void *)0);
    }
    goto Done;
    ;
  Error:
    do {
        PyObject *_py_tmp = ((PyObject *)(z));
        if (_py_tmp != ((void *)0)) {
            (z) = ((void *)0);
            _Py_DECREF(((PyObject *)(_py_tmp)));
        }
    } while (0);
  Done:
    if ((((PyVarObject *)(b))->ob_size) > 8) {
        for (i = 0; i < 32; ++i)
            _Py_XDECREF(((PyObject *)(table[i])));
    }
    _Py_DECREF(((PyObject *)(a)));
    _Py_DECREF(((PyObject *)(b)));
    _Py_XDECREF(((PyObject *)(c)));
    _Py_XDECREF(((PyObject *)(temp)));
    return (PyObject *)z;
}


static PyObject * long_long (PyObject *v){
    if (_Py_IS_TYPE(((const PyObject *)(v)), &PyLong_Type)) {
        _Py_INCREF(((PyObject *)(v)));
    } else
        v = _PyLong_Copy((PyLongObject *)v);
    return v;
}


