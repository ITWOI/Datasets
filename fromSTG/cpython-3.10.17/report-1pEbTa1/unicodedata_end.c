#include "header_func.h"
static unsigned long _gethash (const char *s, int len, int scale){
    int i;
    unsigned long h = 0;
    unsigned long ix;
    for (i = 0; i < len; i++) {
        h = (h * scale) + (unsigned char)(_Py_ctype_toupper[((unsigned char)((s[i]) & 255))]);
        ix = h & 4278190080U;
        if (ix)
            h = (h ^ ((ix >> 24) & 255)) & 16777215;
    }
    return h;
}
static int is_unified_ideograph (Py_UCS4 code){
    return (13312 <= code && code <= 19903) || (19968 <= code && code <= 40956) || (131072 <= code && code <= 173789) || (173824 <= code && code <= 177972) || (177984 <= code && code <= 178205) || (178208 <= code && code <= 183969) || (183984 <= code && code <= 191456) || (196608 <= code && code <= 201546);
}
static int _getucname (PyObject *self, Py_UCS4 code, char *buffer, int buflen, int with_alias_and_seq){
    int offset;
    int i;
    int word;
    const unsigned char *w;
    if (code >= 1114112)
        return 0;
    if (!with_alias_and_seq && (((code >= aliases_start) && (code < aliases_end)) || ((code >= named_sequences_start) && (code < named_sequences_end))))
        return 0;
    if ((self != ((void *)0) && !_PyObject_TypeCheck(((PyObject *)(self)), &PyModule_Type))) {
        const change_record *old;
        if (((code >= aliases_start) && (code < aliases_end)) || ((code >= named_sequences_start) && (code < named_sequences_end)))
            return 0;
        old = ((((PreviousDBVersion *)self)->getrecord)(code));
        if (old->category_changed == 0) {
            return 0;
        }
    }
    if (44032 <= code && code < 44032 + (19 * (21 * 28))) {
        int SIndex = code - 44032;
        int L = SIndex / (21 * 28);
        int V = (SIndex % (21 * 28)) / 28;
        int T = SIndex % 28;
        if (buflen < 27)
            return 0;
        strcpy(buffer, "HANGUL SYLLABLE ");
        buffer += 16;
        strcpy(buffer, hangul_syllables[L][0]);
        buffer += strlen(hangul_syllables[L][0]);
        strcpy(buffer, hangul_syllables[V][1]);
        buffer += strlen(hangul_syllables[V][1]);
        strcpy(buffer, hangul_syllables[T][2]);
        buffer += strlen(hangul_syllables[T][2]);
        *buffer = '\x00';
        return 1;
    }
    if (is_unified_ideograph(code)) {
        if (buflen < 28)
            return 0;
        return 1;
    }
    offset = phrasebook_offset1[(code >> 8)];
    offset = phrasebook_offset2[(offset << 8) + (code & ((1 << 8) - 1))];
    if (!offset)
        return 0;
    i = 0;
    for (;;) {
        word = phrasebook[offset] - 191;
        if (word >= 0) {
            word = (word << 8) + phrasebook[offset + 1];
            offset += 2;
        } else
            word = phrasebook[offset++];
        if (i) {
            if (i > buflen)
                return 0;
            buffer[i++] = ' ';
        }
        w = lexicon + lexicon_offset[word];
        while (*w < 128)
            {
                if (i >= buflen)
                    return 0;
                buffer[i++] = *w++;
            }
        if (i >= buflen)
            return 0;
        buffer[i++] = *w & 127;
        if (*w == 128)
            break;
    }
    return 1;
}
static int _cmpname (PyObject *self, int code, const char *name, int namelen){
    int i;
    char buffer[257];
    if (!_getucname(self, code, buffer, 256, 1))
        return 0;
    for (i = 0; i < namelen; i++) {
        if ((_Py_ctype_toupper[((unsigned char)((name[i]) & 255))]) != buffer[i])
            return 0;
    }
    return buffer[namelen] == '\x00';
}
static int _getcode (PyObject *self, const char *name, int namelen, Py_UCS4 *code, int with_named_seq){
    unsigned int h, v;
    unsigned int mask = 65536 - 1;
    unsigned int i, incr;
    if (strncmp(name, "HANGUL SYLLABLE ", 16) == 0) {
        int len, L = -1, V = -1, T = -1;
        const char *pos = name + 16;
        return 0;
    }
    if (strncmp(name, "CJK UNIFIED IDEOGRAPH-", 22) == 0) {
        v = 0;
        name += 22;
        namelen -= 22;
        if (namelen != 4 && namelen != 5)
            return 0;
        while (namelen--)
            {
                v *= 16;
                if (*name >= '0' && *name <= '9') {
                    v += *name - '0';
                } else if (*name >= 'A' && *name <= 'F') {
                    v += *name - 'A' + 10;
                } else {
                    ;
                }
                name++;
            }
        if (!is_unified_ideograph(v))
            return 0;
        return 1;
    }
    h = (unsigned int)_gethash(name, namelen, 47);
    i = (~h) & mask;
    v = code_hash[i];
    if (!v)
        return 0;
    if (_cmpname(self, v, name, namelen)) {
        return _check_alias_and_seq(v, code, with_named_seq);
    }
    incr = (h ^ (h >> 3)) & mask;
    if (!incr)
        incr = mask;
    for (;;) {
        i = (i + incr) & mask;
        v = code_hash[i];
        if (!v)
            return 0;
        if (_cmpname(self, v, name, namelen)) {
            return _check_alias_and_seq(v, code, with_named_seq);
        }
        incr = incr << 1;
        if (incr > mask)
            incr = incr ^ 65581;
    }
}
static int capi_getcode (const char *name, int namelen, Py_UCS4 *code, int with_named_seq){
    return _getcode(((void *)0), name, namelen, code, with_named_seq);
}
