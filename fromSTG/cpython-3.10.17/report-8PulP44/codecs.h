#include "header_func.h"
static inline Py_UCS4 asciilib_utf8_decode (const char **inptr, const char *end, Py_UCS1 *dest, Py_ssize_t *outpos){
    Py_UCS4 ch;
    const char *s = *inptr;
    Py_UCS1 *p = dest + *outpos;
    while (s < end)
        {
            ch = (unsigned char)*s;
            if (ch < 128) {
                if ((!((uintptr_t)(s) & (uintptr_t)((8) - 1)))) {
                    const char *_s = s;
                    Py_UCS1 *_p = p;
                    while (_s + 8 <= end)
                        {
                            size_t value = *(const size_t *)_s;
                            if (value & 9259542123273814144ULL)
                                break;
                            _p[0] = (Py_UCS1)(value & 255U);
                            _p[1] = (Py_UCS1)((value >> 8) & 255U);
                            _p[2] = (Py_UCS1)((value >> 16) & 255U);
                            _p[3] = (Py_UCS1)((value >> 24) & 255U);
                            _p[4] = (Py_UCS1)((value >> 32) & 255U);
                            _p[5] = (Py_UCS1)((value >> 40) & 255U);
                            _p[6] = (Py_UCS1)((value >> 48) & 255U);
                            _p[7] = (Py_UCS1)((value >> 56) & 255U);
                            _s += 8;
                            _p += 8;
                        }
                    s = _s;
                    p = _p;
                    if (s == end)
                        break;
                    ch = (unsigned char)*s;
                }
                if (ch < 128) {
                    s++;
                    *p++ = ch;
                    continue;
                }
            }
            if (ch < 224) {
                Py_UCS4 ch2;
                if (ch < 194) {
                    goto InvalidStart;
                }
                if (end - s < 2) {
                    break;
                }
                ch2 = (unsigned char)s[1];
                if (!((ch2) >= 128 && (ch2) < 192))
                    goto InvalidContinuation1;
                ch = (ch << 6) + ch2 - ((192 << 6) + 128);
                s += 2;
                continue;
            }
            if (ch < 240) {
                Py_UCS4 ch2, ch3;
                if (end - s < 3) {
                    if (end - s < 2)
                        break;
                    ch2 = (unsigned char)s[1];
                    if (!((ch2) >= 128 && (ch2) < 192) || (ch2 < 160 ? ch == 224 : ch == 237))
                        goto InvalidContinuation1;
                    break;
                }
                ch2 = (unsigned char)s[1];
                ch3 = (unsigned char)s[2];
                if (!((ch2) >= 128 && (ch2) < 192)) {
                    goto InvalidContinuation1;
                }
                if (ch == 224) {
                    if (ch2 < 160)
                        goto InvalidContinuation1;
                } else if (ch == 237 && ch2 >= 160) {
                    goto InvalidContinuation1;
                }
                if (!((ch3) >= 128 && (ch3) < 192)) {
                    goto InvalidContinuation2;
                }
                ch = (ch << 12) + (ch2 << 6) + ch3 - ((224 << 12) + (128 << 6) + 128);
                s += 3;
                continue;
            }
            if (ch < 245) {
                Py_UCS4 ch2, ch3, ch4;
                if (end - s < 4) {
                    if (end - s < 2)
                        break;
                    ch2 = (unsigned char)s[1];
                    if (!((ch2) >= 128 && (ch2) < 192) || (ch2 < 144 ? ch == 240 : ch == 244))
                        goto InvalidContinuation1;
                    if (end - s < 3)
                        break;
                    ch3 = (unsigned char)s[2];
                    if (!((ch3) >= 128 && (ch3) < 192))
                        goto InvalidContinuation2;
                    break;
                }
                ch2 = (unsigned char)s[1];
                ch3 = (unsigned char)s[2];
                ch4 = (unsigned char)s[3];
                if (!((ch2) >= 128 && (ch2) < 192)) {
                    goto InvalidContinuation1;
                }
                if (ch == 240) {
                    if (ch2 < 144)
                        goto InvalidContinuation1;
                } else if (ch == 244 && ch2 >= 144) {
                    goto InvalidContinuation1;
                }
                if (!((ch3) >= 128 && (ch3) < 192)) {
                    goto InvalidContinuation2;
                }
                if (!((ch4) >= 128 && (ch4) < 192)) {
                    goto InvalidContinuation3;
                }
                ch = (ch << 18) + (ch2 << 12) + (ch3 << 6) + ch4 - ((240 << 18) + (128 << 12) + (128 << 6) + 128);
                s += 4;
                continue;
            }
            goto InvalidStart;
        }
    ch = 0;
  Return:
    *inptr = s;
    *outpos = p - dest;
    return ch;
  InvalidStart:
    ch = 1;
    goto Return;
  InvalidContinuation1:
    ch = 2;
    goto Return;
  InvalidContinuation2:
    ch = 3;
    goto Return;
  InvalidContinuation3:
    ch = 4;
    goto Return;
}
static inline Py_UCS4 asciilib_utf16_decode (const unsigned char **inptr, const unsigned char *e, Py_UCS1 *dest, Py_ssize_t *outpos, int native_ordering){
    Py_UCS4 ch;
    const unsigned char *q = *inptr;
    Py_UCS1 *p = dest + *outpos;
    int ihi = !!native_ordering, ilo = !native_ordering;
    --e;
    while (q < e)
        {
            Py_UCS4 ch2;
            if ((!((uintptr_t)(q) & (uintptr_t)((8) - 1)))) {
                const unsigned char *_q = q;
                while (_q + 8 <= e)
                    {
                        unsigned long block = *(const unsigned long *)_q;
                        if (native_ordering) {
                            if (block & (281479271743489UL * (65535U & ~127U)))
                                break;
                        } else {
                            if (block & (((((281479271743489UL * (65535U & ~127U))) >> 8) & (281479271743489UL * 255U)) | ((((281479271743489UL * (65535U & ~127U))) & (281479271743489UL * 255U)) << 8)))
                                break;
                            block >>= 8;
                        }
                        p[0] = (Py_UCS1)(block & 65535U);
                        p[1] = (Py_UCS1)((block >> 16) & 65535U);
                        p[2] = (Py_UCS1)((block >> 32) & 65535U);
                        p[3] = (Py_UCS1)(block >> 48);
                        _q += 8;
                        p += 8 / 2;
                    }
                q = _q;
                if (q >= e)
                    break;
            }
            ch = (q[ihi] << 8) | q[ilo];
            q += 2;
            if (!(55296 <= (ch) && (ch) <= 57343)) {
                if (ch > 127U)
                    goto Return;
                *p++ = (Py_UCS1)ch;
                continue;
            }
            if (!(55296 <= (ch) && (ch) <= 56319))
                goto IllegalEncoding;
            if (q >= e)
                goto UnexpectedEnd;
            ch2 = (q[ihi] << 8) | q[ilo];
            q += 2;
            if (!(56320 <= (ch2) && (ch2) <= 57343))
                goto IllegalSurrogate;
            ch = (((((Py_UCS4)(ch) & 1023) << 10) | ((Py_UCS4)(ch2) & 1023)) + 65536);
            goto Return;
        }
    ch = 0;
  Return:
    *inptr = q;
    *outpos = p - dest;
    return ch;
  UnexpectedEnd:
    ch = 1;
    goto Return;
  IllegalEncoding:
    ch = 2;
    goto Return;
  IllegalSurrogate:
    ch = 3;
    goto Return;
}
static inline Py_UCS4 ucs1lib_utf8_decode (const char **inptr, const char *end, Py_UCS1 *dest, Py_ssize_t *outpos){
    Py_UCS4 ch;
    const char *s = *inptr;
    Py_UCS1 *p = dest + *outpos;
    while (s < end)
        {
            ch = (unsigned char)*s;
            if (ch < 128) {
                if ((!((uintptr_t)(s) & (uintptr_t)((8) - 1)))) {
                    const char *_s = s;
                    Py_UCS1 *_p = p;
                    while (_s + 8 <= end)
                        {
                            size_t value = *(const size_t *)_s;
                            if (value & 9259542123273814144ULL)
                                break;
                            _p[0] = (Py_UCS1)(value & 255U);
                            _p[1] = (Py_UCS1)((value >> 8) & 255U);
                            _p[2] = (Py_UCS1)((value >> 16) & 255U);
                            _p[3] = (Py_UCS1)((value >> 24) & 255U);
                            _p[4] = (Py_UCS1)((value >> 32) & 255U);
                            _p[5] = (Py_UCS1)((value >> 40) & 255U);
                            _p[6] = (Py_UCS1)((value >> 48) & 255U);
                            _p[7] = (Py_UCS1)((value >> 56) & 255U);
                            _s += 8;
                            _p += 8;
                        }
                    s = _s;
                    p = _p;
                    if (s == end)
                        break;
                    ch = (unsigned char)*s;
                }
                if (ch < 128) {
                    s++;
                    *p++ = ch;
                    continue;
                }
            }
            if (ch < 224) {
                Py_UCS4 ch2;
                if (ch < 194) {
                    goto InvalidStart;
                }
                if (end - s < 2) {
                    break;
                }
                ch2 = (unsigned char)s[1];
                if (!((ch2) >= 128 && (ch2) < 192))
                    goto InvalidContinuation1;
                ch = (ch << 6) + ch2 - ((192 << 6) + 128);
                s += 2;
                continue;
            }
            if (ch < 240) {
                Py_UCS4 ch2, ch3;
                if (end - s < 3) {
                    if (end - s < 2)
                        break;
                    ch2 = (unsigned char)s[1];
                    if (!((ch2) >= 128 && (ch2) < 192) || (ch2 < 160 ? ch == 224 : ch == 237))
                        goto InvalidContinuation1;
                    break;
                }
                ch2 = (unsigned char)s[1];
                ch3 = (unsigned char)s[2];
                if (!((ch2) >= 128 && (ch2) < 192)) {
                    goto InvalidContinuation1;
                }
                if (ch == 224) {
                    if (ch2 < 160)
                        goto InvalidContinuation1;
                } else if (ch == 237 && ch2 >= 160) {
                    goto InvalidContinuation1;
                }
                if (!((ch3) >= 128 && (ch3) < 192)) {
                    goto InvalidContinuation2;
                }
                ch = (ch << 12) + (ch2 << 6) + ch3 - ((224 << 12) + (128 << 6) + 128);
                s += 3;
                continue;
            }
            if (ch < 245) {
                Py_UCS4 ch2, ch3, ch4;
                if (end - s < 4) {
                    if (end - s < 2)
                        break;
                    ch2 = (unsigned char)s[1];
                    if (!((ch2) >= 128 && (ch2) < 192) || (ch2 < 144 ? ch == 240 : ch == 244))
                        goto InvalidContinuation1;
                    if (end - s < 3)
                        break;
                    ch3 = (unsigned char)s[2];
                    if (!((ch3) >= 128 && (ch3) < 192))
                        goto InvalidContinuation2;
                    break;
                }
                ch2 = (unsigned char)s[1];
                ch3 = (unsigned char)s[2];
                ch4 = (unsigned char)s[3];
                if (!((ch2) >= 128 && (ch2) < 192)) {
                    goto InvalidContinuation1;
                }
                if (ch == 240) {
                    if (ch2 < 144)
                        goto InvalidContinuation1;
                } else if (ch == 244 && ch2 >= 144) {
                    goto InvalidContinuation1;
                }
                if (!((ch3) >= 128 && (ch3) < 192)) {
                    goto InvalidContinuation2;
                }
                if (!((ch4) >= 128 && (ch4) < 192)) {
                    goto InvalidContinuation3;
                }
                ch = (ch << 18) + (ch2 << 12) + (ch3 << 6) + ch4 - ((240 << 18) + (128 << 12) + (128 << 6) + 128);
                s += 4;
                continue;
            }
            goto InvalidStart;
        }
    ch = 0;
  Return:
    *inptr = s;
    *outpos = p - dest;
    return ch;
  InvalidStart:
    ch = 1;
    goto Return;
  InvalidContinuation1:
    ch = 2;
    goto Return;
  InvalidContinuation2:
    ch = 3;
    goto Return;
  InvalidContinuation3:
    ch = 4;
    goto Return;
}
static inline Py_UCS4 ucs1lib_utf16_decode (const unsigned char **inptr, const unsigned char *e, Py_UCS1 *dest, Py_ssize_t *outpos, int native_ordering){
    Py_UCS4 ch;
    const unsigned char *q = *inptr;
    Py_UCS1 *p = dest + *outpos;
    int ihi = !!native_ordering, ilo = !native_ordering;
    --e;
    while (q < e)
        {
            Py_UCS4 ch2;
            if ((!((uintptr_t)(q) & (uintptr_t)((8) - 1)))) {
                const unsigned char *_q = q;
                while (_q + 8 <= e)
                    {
                        unsigned long block = *(const unsigned long *)_q;
                        if (native_ordering) {
                            if (block & (281479271743489UL * (65535U & ~127U)))
                                break;
                        } else {
                            if (block & (((((281479271743489UL * (65535U & ~255U))) >> 8) & (281479271743489UL * 255U)) | ((((281479271743489UL * (65535U & ~255U))) & (281479271743489UL * 255U)) << 8)))
                                break;
                            block >>= 8;
                        }
                        p[0] = (Py_UCS1)(block & 65535U);
                        p[1] = (Py_UCS1)((block >> 16) & 65535U);
                        p[2] = (Py_UCS1)((block >> 32) & 65535U);
                        p[3] = (Py_UCS1)(block >> 48);
                        _q += 8;
                        p += 8 / 2;
                    }
                q = _q;
                if (q >= e)
                    break;
            }
            ch = (q[ihi] << 8) | q[ilo];
            q += 2;
            if (!(55296 <= (ch) && (ch) <= 57343)) {
                if (ch > 127U)
                    goto Return;
                *p++ = (Py_UCS1)ch;
                continue;
            }
            if (!(55296 <= (ch) && (ch) <= 56319))
                goto IllegalEncoding;
            if (q >= e)
                goto UnexpectedEnd;
            ch2 = (q[ihi] << 8) | q[ilo];
            q += 2;
            if (!(56320 <= (ch2) && (ch2) <= 57343))
                goto IllegalSurrogate;
            ch = (((((Py_UCS4)(ch) & 1023) << 10) | ((Py_UCS4)(ch2) & 1023)) + 65536);
            goto Return;
        }
    ch = 0;
  Return:
    *inptr = q;
    *outpos = p - dest;
    return ch;
  UnexpectedEnd:
    ch = 1;
    goto Return;
  IllegalEncoding:
    ch = 2;
    goto Return;
  IllegalSurrogate:
    ch = 3;
    goto Return;
}
static inline Py_UCS4 ucs2lib_utf8_decode (const char **inptr, const char *end, Py_UCS2 *dest, Py_ssize_t *outpos){
    Py_UCS4 ch;
    const char *s = *inptr;
    Py_UCS2 *p = dest + *outpos;
    while (s < end)
        {
            ch = (unsigned char)*s;
            if (ch < 128) {
                if ((!((uintptr_t)(s) & (uintptr_t)((8) - 1)))) {
                    const char *_s = s;
                    Py_UCS2 *_p = p;
                    while (_s + 8 <= end)
                        {
                            size_t value = *(const size_t *)_s;
                            if (value & 9259542123273814144ULL)
                                break;
                            _p[0] = (Py_UCS1)(value & 255U);
                            _p[1] = (Py_UCS1)((value >> 8) & 255U);
                            _p[2] = (Py_UCS1)((value >> 16) & 255U);
                            _p[3] = (Py_UCS1)((value >> 24) & 255U);
                            _p[4] = (Py_UCS1)((value >> 32) & 255U);
                            _p[5] = (Py_UCS1)((value >> 40) & 255U);
                            _p[6] = (Py_UCS1)((value >> 48) & 255U);
                            _p[7] = (Py_UCS1)((value >> 56) & 255U);
                            _s += 8;
                            _p += 8;
                        }
                    s = _s;
                    p = _p;
                    if (s == end)
                        break;
                    ch = (unsigned char)*s;
                }
                if (ch < 128) {
                    s++;
                    *p++ = ch;
                    continue;
                }
            }
            if (ch < 224) {
                Py_UCS4 ch2;
                if (ch < 194) {
                    goto InvalidStart;
                }
                if (end - s < 2) {
                    break;
                }
                ch2 = (unsigned char)s[1];
                if (!((ch2) >= 128 && (ch2) < 192))
                    goto InvalidContinuation1;
                ch = (ch << 6) + ch2 - ((192 << 6) + 128);
                s += 2;
                continue;
            }
            if (ch < 240) {
                Py_UCS4 ch2, ch3;
                if (end - s < 3) {
                    if (end - s < 2)
                        break;
                    ch2 = (unsigned char)s[1];
                    if (!((ch2) >= 128 && (ch2) < 192) || (ch2 < 160 ? ch == 224 : ch == 237))
                        goto InvalidContinuation1;
                    break;
                }
                ch2 = (unsigned char)s[1];
                ch3 = (unsigned char)s[2];
                if (!((ch2) >= 128 && (ch2) < 192)) {
                    goto InvalidContinuation1;
                }
                if (ch == 224) {
                    if (ch2 < 160)
                        goto InvalidContinuation1;
                } else if (ch == 237 && ch2 >= 160) {
                    goto InvalidContinuation1;
                }
                if (!((ch3) >= 128 && (ch3) < 192)) {
                    goto InvalidContinuation2;
                }
                ch = (ch << 12) + (ch2 << 6) + ch3 - ((224 << 12) + (128 << 6) + 128);
                s += 3;
                continue;
            }
            if (ch < 245) {
                Py_UCS4 ch2, ch3, ch4;
                if (end - s < 4) {
                    if (end - s < 2)
                        break;
                    ch2 = (unsigned char)s[1];
                    if (!((ch2) >= 128 && (ch2) < 192) || (ch2 < 144 ? ch == 240 : ch == 244))
                        goto InvalidContinuation1;
                    if (end - s < 3)
                        break;
                    ch3 = (unsigned char)s[2];
                    if (!((ch3) >= 128 && (ch3) < 192))
                        goto InvalidContinuation2;
                    break;
                }
                ch2 = (unsigned char)s[1];
                ch3 = (unsigned char)s[2];
                ch4 = (unsigned char)s[3];
                if (!((ch2) >= 128 && (ch2) < 192)) {
                    goto InvalidContinuation1;
                }
                if (ch == 240) {
                    if (ch2 < 144)
                        goto InvalidContinuation1;
                } else if (ch == 244 && ch2 >= 144) {
                    goto InvalidContinuation1;
                }
                if (!((ch3) >= 128 && (ch3) < 192)) {
                    goto InvalidContinuation2;
                }
                if (!((ch4) >= 128 && (ch4) < 192)) {
                    goto InvalidContinuation3;
                }
                ch = (ch << 18) + (ch2 << 12) + (ch3 << 6) + ch4 - ((240 << 18) + (128 << 12) + (128 << 6) + 128);
                s += 4;
                continue;
            }
            goto InvalidStart;
        }
    ch = 0;
  Return:
    *inptr = s;
    *outpos = p - dest;
    return ch;
  InvalidStart:
    ch = 1;
    goto Return;
  InvalidContinuation1:
    ch = 2;
    goto Return;
  InvalidContinuation2:
    ch = 3;
    goto Return;
  InvalidContinuation3:
    ch = 4;
    goto Return;
}
static inline Py_UCS4 ucs2lib_utf16_decode (const unsigned char **inptr, const unsigned char *e, Py_UCS2 *dest, Py_ssize_t *outpos, int native_ordering){
    Py_UCS4 ch;
    const unsigned char *q = *inptr;
    Py_UCS2 *p = dest + *outpos;
    int ihi = !!native_ordering, ilo = !native_ordering;
    --e;
    while (q < e)
        {
            Py_UCS4 ch2;
            if ((!((uintptr_t)(q) & (uintptr_t)((8) - 1)))) {
                const unsigned char *_q = q;
                while (_q + 8 <= e)
                    {
                        unsigned long block = *(const unsigned long *)_q;
                        if (native_ordering) {
                            if (block & (281479271743489UL * (65535U & ~127U)))
                                break;
                        } else {
                            if (block & (((((281479271743489UL * 32768U)) >> 8) & (281479271743489UL * 255U)) | ((((281479271743489UL * 32768U)) & (281479271743489UL * 255U)) << 8)))
                                break;
                            block = ((((block) >> 8) & (281479271743489UL * 255U)) | (((block) & (281479271743489UL * 255U)) << 8));
                        }
                        p[0] = (Py_UCS1)(block & 65535U);
                        p[1] = (Py_UCS1)((block >> 16) & 65535U);
                        p[2] = (Py_UCS1)((block >> 32) & 65535U);
                        p[3] = (Py_UCS1)(block >> 48);
                        _q += 8;
                        p += 8 / 2;
                    }
                q = _q;
                if (q >= e)
                    break;
            }
            ch = (q[ihi] << 8) | q[ilo];
            q += 2;
            if (!(55296 <= (ch) && (ch) <= 57343)) {
                *p++ = (Py_UCS1)ch;
                continue;
            }
            if (!(55296 <= (ch) && (ch) <= 56319))
                goto IllegalEncoding;
            if (q >= e)
                goto UnexpectedEnd;
            ch2 = (q[ihi] << 8) | q[ilo];
            q += 2;
            if (!(56320 <= (ch2) && (ch2) <= 57343))
                goto IllegalSurrogate;
            ch = (((((Py_UCS4)(ch) & 1023) << 10) | ((Py_UCS4)(ch2) & 1023)) + 65536);
            goto Return;
        }
    ch = 0;
  Return:
    *inptr = q;
    *outpos = p - dest;
    return ch;
  UnexpectedEnd:
    ch = 1;
    goto Return;
  IllegalEncoding:
    ch = 2;
    goto Return;
  IllegalSurrogate:
    ch = 3;
    goto Return;
}
static inline Py_UCS4 ucs4lib_utf8_decode (const char **inptr, const char *end, Py_UCS4 *dest, Py_ssize_t *outpos){
    Py_UCS4 ch;
    const char *s = *inptr;
    Py_UCS4 *p = dest + *outpos;
    while (s < end)
        {
            ch = (unsigned char)*s;
            if (ch < 128) {
                if ((!((uintptr_t)(s) & (uintptr_t)((8) - 1)))) {
                    const char *_s = s;
                    Py_UCS4 *_p = p;
                    while (_s + 8 <= end)
                        {
                            size_t value = *(const size_t *)_s;
                            if (value & 9259542123273814144ULL)
                                break;
                            _p[0] = (Py_UCS1)(value & 255U);
                            _p[1] = (Py_UCS1)((value >> 8) & 255U);
                            _p[2] = (Py_UCS1)((value >> 16) & 255U);
                            _p[3] = (Py_UCS1)((value >> 24) & 255U);
                            _p[4] = (Py_UCS1)((value >> 32) & 255U);
                            _p[5] = (Py_UCS1)((value >> 40) & 255U);
                            _p[6] = (Py_UCS1)((value >> 48) & 255U);
                            _p[7] = (Py_UCS1)((value >> 56) & 255U);
                            _s += 8;
                            _p += 8;
                        }
                    s = _s;
                    p = _p;
                    if (s == end)
                        break;
                    ch = (unsigned char)*s;
                }
                if (ch < 128) {
                    s++;
                    *p++ = ch;
                    continue;
                }
            }
            if (ch < 224) {
                Py_UCS4 ch2;
                if (ch < 194) {
                    goto InvalidStart;
                }
                if (end - s < 2) {
                    break;
                }
                ch2 = (unsigned char)s[1];
                if (!((ch2) >= 128 && (ch2) < 192))
                    goto InvalidContinuation1;
                ch = (ch << 6) + ch2 - ((192 << 6) + 128);
                s += 2;
                continue;
            }
            if (ch < 240) {
                Py_UCS4 ch2, ch3;
                if (end - s < 3) {
                    if (end - s < 2)
                        break;
                    ch2 = (unsigned char)s[1];
                    if (!((ch2) >= 128 && (ch2) < 192) || (ch2 < 160 ? ch == 224 : ch == 237))
                        goto InvalidContinuation1;
                    break;
                }
                ch2 = (unsigned char)s[1];
                ch3 = (unsigned char)s[2];
                if (!((ch2) >= 128 && (ch2) < 192)) {
                    goto InvalidContinuation1;
                }
                if (ch == 224) {
                    if (ch2 < 160)
                        goto InvalidContinuation1;
                } else if (ch == 237 && ch2 >= 160) {
                    goto InvalidContinuation1;
                }
                if (!((ch3) >= 128 && (ch3) < 192)) {
                    goto InvalidContinuation2;
                }
                ch = (ch << 12) + (ch2 << 6) + ch3 - ((224 << 12) + (128 << 6) + 128);
                s += 3;
                continue;
            }
            if (ch < 245) {
                Py_UCS4 ch2, ch3, ch4;
                if (end - s < 4) {
                    if (end - s < 2)
                        break;
                    ch2 = (unsigned char)s[1];
                    if (!((ch2) >= 128 && (ch2) < 192) || (ch2 < 144 ? ch == 240 : ch == 244))
                        goto InvalidContinuation1;
                    if (end - s < 3)
                        break;
                    ch3 = (unsigned char)s[2];
                    if (!((ch3) >= 128 && (ch3) < 192))
                        goto InvalidContinuation2;
                    break;
                }
                ch2 = (unsigned char)s[1];
                ch3 = (unsigned char)s[2];
                ch4 = (unsigned char)s[3];
                if (!((ch2) >= 128 && (ch2) < 192)) {
                    goto InvalidContinuation1;
                }
                if (ch == 240) {
                    if (ch2 < 144)
                        goto InvalidContinuation1;
                } else if (ch == 244 && ch2 >= 144) {
                    goto InvalidContinuation1;
                }
                if (!((ch3) >= 128 && (ch3) < 192)) {
                    goto InvalidContinuation2;
                }
                if (!((ch4) >= 128 && (ch4) < 192)) {
                    goto InvalidContinuation3;
                }
                ch = (ch << 18) + (ch2 << 12) + (ch3 << 6) + ch4 - ((240 << 18) + (128 << 12) + (128 << 6) + 128);
                s += 4;
                continue;
            }
            goto InvalidStart;
        }
    ch = 0;
  Return:
    *inptr = s;
    *outpos = p - dest;
    return ch;
  InvalidStart:
    ch = 1;
    goto Return;
  InvalidContinuation1:
    ch = 2;
    goto Return;
  InvalidContinuation2:
    ch = 3;
    goto Return;
  InvalidContinuation3:
    ch = 4;
    goto Return;
}
static inline Py_UCS4 ucs4lib_utf16_decode (const unsigned char **inptr, const unsigned char *e, Py_UCS4 *dest, Py_ssize_t *outpos, int native_ordering){
    Py_UCS4 ch;
    const unsigned char *q = *inptr;
    Py_UCS4 *p = dest + *outpos;
    int ihi = !!native_ordering, ilo = !native_ordering;
    --e;
    while (q < e)
        {
            Py_UCS4 ch2;
            if ((!((uintptr_t)(q) & (uintptr_t)((8) - 1)))) {
                const unsigned char *_q = q;
                while (_q + 8 <= e)
                    {
                        unsigned long block = *(const unsigned long *)_q;
                        if (native_ordering) {
                            if (block & (281479271743489UL * (65535U & ~127U)))
                                break;
                        } else {
                            if (block & (((((281479271743489UL * 32768U)) >> 8) & (281479271743489UL * 255U)) | ((((281479271743489UL * 32768U)) & (281479271743489UL * 255U)) << 8)))
                                break;
                            block = ((((block) >> 8) & (281479271743489UL * 255U)) | (((block) & (281479271743489UL * 255U)) << 8));
                        }
                        p[0] = (Py_UCS1)(block & 65535U);
                        p[1] = (Py_UCS1)((block >> 16) & 65535U);
                        p[2] = (Py_UCS1)((block >> 32) & 65535U);
                        p[3] = (Py_UCS1)(block >> 48);
                        _q += 8;
                        p += 8 / 2;
                    }
                q = _q;
                if (q >= e)
                    break;
            }
            ch = (q[ihi] << 8) | q[ilo];
            q += 2;
            if (!(55296 <= (ch) && (ch) <= 57343)) {
                *p++ = (Py_UCS1)ch;
                continue;
            }
            if (!(55296 <= (ch) && (ch) <= 56319))
                goto IllegalEncoding;
            if (q >= e)
                goto UnexpectedEnd;
            ch2 = (q[ihi] << 8) | q[ilo];
            q += 2;
            if (!(56320 <= (ch2) && (ch2) <= 57343))
                goto IllegalSurrogate;
            ch = (((((Py_UCS4)(ch) & 1023) << 10) | ((Py_UCS4)(ch2) & 1023)) + 65536);
            *p++ = (Py_UCS4)ch;
        }
    ch = 0;
  Return:
    *inptr = q;
    *outpos = p - dest;
    return ch;
  UnexpectedEnd:
    ch = 1;
    goto Return;
  IllegalEncoding:
    ch = 2;
    goto Return;
  IllegalSurrogate:
    ch = 3;
    goto Return;
}
