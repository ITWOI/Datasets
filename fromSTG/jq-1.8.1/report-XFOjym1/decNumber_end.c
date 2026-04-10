#include "header_func.h"
extern decNumber * decNumberCopy (decNumber *dest, const decNumber *src){
    if (dest == src)
        return dest;
    dest->bits = src->bits;
    dest->exponent = src->exponent;
    dest->digits = src->digits;
    dest->lsu[0] = src->lsu[0];
    if (src->digits > 3) {
        const uint16_t *smsup, *s;
        uint16_t *d;
        d = dest->lsu + 1;
        smsup = src->lsu + ((src->digits) <= 49 ? d2utable[src->digits] : ((src->digits) + 3 - 1) / 3);
        for (s = src->lsu + 1; s < smsup; s++ , d++)
            *d = *s;
    }
    return dest;
}
extern decNumber * decNumberZero (decNumber *dn){
    dn->bits = 0;
    dn->exponent = 0;
    dn->digits = 1;
    dn->lsu[0] = 0;
    return dn;
}
static decNumber * decDivideOp (decNumber *res, const decNumber *lhs, const decNumber *rhs, decContext *set, uint8_t op, uint32_t *status){
    uint16_t accbuff[17];
    uint16_t *acc = accbuff;
    uint16_t *allocacc = ((void *)0);
    uint16_t *accnext;
    int32_t acclength;
    int32_t accunits;
    int32_t accdigits;
    uint16_t varbuff[25];
    uint16_t *var1 = varbuff;
    uint16_t *varalloc = ((void *)0);
    uint16_t *msu1;
    const uint16_t *var2;
    const uint16_t *msu2;
    int32_t msu2plus;
    int32_t msu2pair;
    int32_t var1units, var2units;
    int32_t var2ulen;
    int32_t var1initpad = 0;
    int32_t maxdigits;
    int32_t mult;
    uint16_t thisunit;
    int32_t residue;
    int32_t reqdigits = set->digits;
    int32_t exponent;
    int32_t maxexponent = 0;
    uint8_t bits;
    uint16_t *target;
    const uint16_t *source;
    const uint32_t *pow;
    int32_t shift, cut;
    do {
        bits = (lhs->bits ^ rhs->bits) & 128;
        if (((lhs->bits | rhs->bits) & (64 | 32 | 16))) {
            if (((lhs->bits | rhs->bits) & (64 | 32 | 16)) & (16 | 32)) {
                decNaNs(res, lhs, rhs, set, status);
                break;
            }
            if ((((lhs)->bits & 64) != 0)) {
                if ((((rhs)->bits & 64) != 0) || op & (64 | 16)) {
                    ;
                    break;
                }
                decNumberZero(res);
                break;
            } else {
                residue = 0;
                if (op & (64 | 16)) {
                    decCopyFit(res, lhs, set, &residue, status);
                } else {
                    decNumberZero(res);
                    res->bits = bits;
                    if (op & 128) {
                        res->exponent = set->emin - set->digits + 1;
                        *status |= 1024;
                    }
                }
                decFinalize(res, set, &residue, status);
                break;
            }
        }
        if ((*(rhs)->lsu == 0 && (rhs)->digits == 1 && (((rhs)->bits & (64 | 32 | 16)) == 0))) {
            if ((*(lhs)->lsu == 0 && (lhs)->digits == 1 && (((lhs)->bits & (64 | 32 | 16)) == 0))) {
                decNumberZero(res);
            } else {
                decNumberZero(res);
            }
            break;
        }
        if ((*(lhs)->lsu == 0 && (lhs)->digits == 1 && (((lhs)->bits & (64 | 32 | 16)) == 0))) {
            if (op & 128) {
                residue = 0;
                exponent = lhs->exponent - rhs->exponent;
                decNumberCopy(res, lhs);
                res->bits = bits;
                res->exponent = exponent;
                decFinalize(res, set, &residue, status);
            } else if (op & 32) {
                decNumberZero(res);
            } else {
                ;
                decNumberCopy(res, lhs);
            }
            break;
        }
        exponent = (lhs->exponent + lhs->digits) - (rhs->exponent + rhs->digits);
        if (exponent < 0 && !(op == 128)) {
            if (op & 32) {
                decNumberZero(res);
                break;
            }
            if (lhs->exponent <= rhs->exponent) {
                if (op & 64 || exponent < -1) {
                    residue = 0;
                    decCopyFit(res, lhs, set, &residue, status);
                    decFinalize(res, set, &residue, status);
                    break;
                }
            }
        }
        acclength = ((reqdigits + 3) <= 49 ? d2utable[reqdigits + 3] : ((reqdigits + 3) + 3 - 1) / 3);
        if (acclength * sizeof(uint16_t) > sizeof (accbuff)) {
            allocacc = (uint16_t *)malloc(acclength * sizeof(uint16_t));
            if (allocacc == ((void *)0)) {
                ;
                break;
            }
            acc = allocacc;
        }
        maxdigits = rhs->digits + reqdigits - 1;
        if (lhs->digits > maxdigits)
            maxdigits = lhs->digits;
        var1units = ((maxdigits) <= 49 ? d2utable[maxdigits] : ((maxdigits) + 3 - 1) / 3) + 2;
        if (!(op & 128))
            var1units++;
        if ((var1units + 1) * sizeof(uint16_t) > sizeof (varbuff)) {
            varalloc = (uint16_t *)malloc((var1units + 1) * sizeof(uint16_t));
            if (varalloc == ((void *)0)) {
                ;
                break;
            }
            var1 = varalloc;
        }
        msu1 = var1 + var1units - 1;
        source = lhs->lsu + ((lhs->digits) <= 49 ? d2utable[lhs->digits] : ((lhs->digits) + 3 - 1) / 3) - 1;
        for (target = msu1; source >= lhs->lsu; source-- , target--)
            *target = *source;
        for (; target >= var1; target--)
            *target = 0;
        var2ulen = var1units;
        var2units = ((rhs->digits) <= 49 ? d2utable[rhs->digits] : ((rhs->digits) + 3 - 1) / 3);
        var2 = rhs->lsu;
        msu2 = var2 + var2units - 1;
        msu2plus = *msu2;
        if (var2units > 1)
            msu2plus++;
        msu2pair = (int32_t)*msu2 * (999 + 1);
        if (var2units > 1) {
            msu2pair += *(msu2 - 1);
            if (var2units > 2)
                msu2pair++;
        }
        for (pow = &DECPOWERS[1]; *msu1 >= *pow; pow++)
            exponent--;
        for (pow = &DECPOWERS[1]; *msu2 >= *pow; pow++)
            exponent++;
        if (!(op & 128)) {
            uint16_t *u;
            var1initpad = (var1units - ((lhs->digits) <= 49 ? d2utable[lhs->digits] : ((lhs->digits) + 3 - 1) / 3)) * 3;
            if (exponent < 0)
                cut = -exponent;
            else
                cut = 3 - exponent % 3;
            decShiftToLeast(var1, var1units, cut);
            exponent += cut;
            var1initpad -= cut;
            for (u = msu1; cut >= 3; cut -= 3 , u--)
                *u = 0;
        } else {
            maxexponent = lhs->exponent - rhs->exponent;
            if (*msu1 < *msu2) {
                var2ulen--;
                exponent -= 3;
            }
        }
        accunits = 0;
        accdigits = 0;
        accnext = acc + acclength - 1;
        for (;;) {
            thisunit = 0;
            for (;;) {
                for (; *msu1 == 0 && msu1 > var1; msu1--)
                    var1units--;
                if (var1units < var2ulen)
                    break;
                if (var1units == var2ulen) {
                    const uint16_t *pv1, *pv2;
                    uint16_t v2;
                    pv2 = msu2;
                    for (pv1 = msu1; ; pv1-- , pv2--) {
                        v2 = 0;
                        if (pv2 >= var2)
                            v2 = *pv2;
                        if (*pv1 != v2)
                            break;
                        if (pv1 == var1)
                            break;
                    }
                    if (*pv1 < v2)
                        break;
                    if (*pv1 == v2) {
                        thisunit++;
                        *var1 = 0;
                        var1units = 1;
                        break;
                    }
                    mult = (int32_t)(((int32_t)*msu1 * (999 + 1) + *(msu1 - 1)) / msu2pair);
                } else {
                    mult = (int32_t)(((int32_t)*msu1 * (999 + 1) + *(msu1 - 1)) / msu2plus);
                }
                if (mult == 0)
                    mult = 1;
                thisunit = (uint16_t)(thisunit + mult);
                shift = var2ulen - var2units;
                decUnitAddSub(&var1[shift], var1units - shift, var2, var2units, 0, &var1[shift], -mult);
            }
            if (accunits != 0 || thisunit != 0) {
                *accnext = thisunit;
                if (accunits == 0) {
                    accdigits++;
                    for (pow = &DECPOWERS[1]; thisunit >= *pow; pow++)
                        accdigits++;
                } else
                    accdigits += 3;
                accunits++;
                accnext--;
                if (accdigits > reqdigits)
                    break;
            }
            if (*var1 == 0 && var1units == 1) {
                if (op & (64 | 16))
                    break;
                if ((op & 128) && (exponent <= maxexponent))
                    break;
            }
            if (exponent == 0 && !(op & 128))
                break;
            var2ulen--;
            exponent -= 3;
        }
        if (accunits == 0) {
            accunits = 1;
            accdigits = 1;
            *accnext = 0;
        } else
            accnext++;
        residue = 0;
        if (op & 128) {
            if (*var1 != 0 || var1units > 1) {
                residue = 1;
            } else {
                uint16_t lsu = *accnext;
                if (!(lsu & 1) && (lsu != 0)) {
                    int32_t drop = 0;
                    for (;; drop++) {
                        if (exponent >= maxexponent)
                            break;
                        if ((lsu - ((((uint32_t)(lsu) >> (drop + 1)) * multies[drop + 1]) >> 17) * DECPOWERS[drop + 1]) != 0)
                            break;
                        exponent++;
                    }
                    if (drop > 0) {
                        accunits = decShiftToLeast(accnext, accunits, drop);
                        accdigits = decGetDigits(accnext, accunits);
                    }
                }
            }
        } else {
            if (accdigits + exponent > reqdigits) {
                ;
                break;
            }
            if (op & (64 | 16)) {
                int32_t postshift;
                uint8_t wasodd = 0;
                uint16_t *quotlsu;
                int32_t quotdigits;
                bits = lhs->bits;
                if (*var1 == 0 && var1units == 1) {
                    int32_t exp = lhs->exponent;
                    if (rhs->exponent < exp)
                        exp = rhs->exponent;
                    decNumberZero(res);
                    res->exponent = exp;
                    res->bits = (uint8_t)(bits & 128);
                    decFinalize(res, set, &residue, status);
                    break;
                }
                if (*accnext & 1)
                    wasodd = 1;
                quotlsu = accnext;
                quotdigits = accdigits;
                postshift = var1initpad + exponent - lhs->exponent + rhs->exponent;
                if (var1initpad < postshift)
                    postshift = var1initpad;
                var1units = decShiftToLeast(var1, var1units, postshift);
                accnext = var1;
                accdigits = decGetDigits(var1, var1units);
                accunits = ((accdigits) <= 49 ? d2utable[accdigits] : ((accdigits) + 3 - 1) / 3);
                exponent = lhs->exponent;
                if (rhs->exponent < exponent)
                    exponent = rhs->exponent;
                if (op & 16) {
                    int32_t compare, tarunits;
                    uint16_t *up;
                    tarunits = decUnitAddSub(accnext, accunits, accnext, accunits, 0, accnext, 1);
                    compare = decUnitCompare(accnext, tarunits, rhs->lsu, ((rhs->digits) <= 49 ? d2utable[rhs->digits] : ((rhs->digits) + 3 - 1) / 3), rhs->exponent - exponent);
                    if (compare == (int32_t)2147483648U) {
                        ;
                        break;
                    }
                    for (up = accnext; up < accnext + tarunits; up++) {
                        int32_t half;
                        half = *up & 1;
                        *up /= 2;
                        if (!half)
                            continue;
                        *(up - 1) += (999 + 1) / 2;
                    }
                    if (compare > 0 || (compare == 0 && wasodd)) {
                        int32_t exp, expunits, exprem;
                        uint8_t allnines = 0;
                        if (quotdigits == reqdigits) {
                            for (up = quotlsu; ; up++) {
                                if (quotdigits > 3) {
                                    if (*up != 999)
                                        break;
                                } else {
                                    if (*up == DECPOWERS[quotdigits] - 1)
                                        allnines = 1;
                                    break;
                                }
                                quotdigits -= 3;
                            }
                        }
                        if (allnines) {
                            ;
                            break;
                        }
                        exp = rhs->exponent - exponent;
                        expunits = exp / 3;
                        exprem = exp % 3;
                        accunits = -decUnitAddSub(accnext, accunits, rhs->lsu, ((rhs->digits) <= 49 ? d2utable[rhs->digits] : ((rhs->digits) + 3 - 1) / 3), expunits, accnext, -(int32_t)DECPOWERS[exprem]);
                        accdigits = decGetDigits(accnext, accunits);
                        bits ^= 128;
                    }
                }
            }
        }
        res->exponent = exponent;
        res->bits = (uint8_t)(bits & 128);
        decSetCoeff(res, set, accnext, accdigits, &residue, status);
        decFinalize(res, set, &residue, status);
    } while (0);
    return res;
}
static int32_t decCompare (const decNumber *lhs, const decNumber *rhs, uint8_t abs){
    int32_t result;
    int32_t sigr;
    int32_t compare;
    result = 1;
    if ((*(lhs)->lsu == 0 && (lhs)->digits == 1 && (((lhs)->bits & (64 | 32 | 16)) == 0)))
        result = 0;
    if (abs) {
        if ((*(rhs)->lsu == 0 && (rhs)->digits == 1 && (((rhs)->bits & (64 | 32 | 16)) == 0)))
            return result;
        if (result == 0)
            return -1;
    } else {
        if (result && (((lhs)->bits & 128) != 0))
            result = -1;
        sigr = 1;
        if ((*(rhs)->lsu == 0 && (rhs)->digits == 1 && (((rhs)->bits & (64 | 32 | 16)) == 0))) {
            sigr = 0;
        } else if ((((rhs)->bits & 128) != 0))
            sigr = -1;
        if (result > sigr)
            return +1;
        if (result < sigr)
            return -1;
        if (result == 0)
            return 0;
    }
    if ((lhs->bits | rhs->bits) & 64) {
        if ((((rhs)->bits & 64) != 0)) {
            if ((((lhs)->bits & 64) != 0)) {
                result = 0;
            } else
                result = -result;
        }
        return result;
    }
    if (lhs->exponent > rhs->exponent) {
        const decNumber *temp = lhs;
        lhs = rhs;
        rhs = temp;
        result = -result;
    }
    compare = decUnitCompare(lhs->lsu, ((lhs->digits) <= 49 ? d2utable[lhs->digits] : ((lhs->digits) + 3 - 1) / 3), rhs->lsu, ((rhs->digits) <= 49 ? d2utable[rhs->digits] : ((rhs->digits) + 3 - 1) / 3), rhs->exponent - lhs->exponent);
    if (compare != (int32_t)2147483648U)
        compare *= result;
    return compare;
}
static int32_t decUnitCompare (const uint16_t *a, int32_t alength, const uint16_t *b, int32_t blength, int32_t exp){
    uint16_t *acc;
    uint16_t accbuff[25];
    uint16_t *allocacc = ((void *)0);
    int32_t accunits, need;
    const uint16_t *l, *r, *u;
    int32_t expunits, exprem, result;
    if (exp == 0) {
        if (alength > blength)
            return 1;
        if (alength < blength)
            return -1;
        l = a + alength - 1;
        r = b + alength - 1;
        for (; l >= a; l-- , r--) {
            if (*l > *r)
                return 1;
            if (*l < *r)
                return -1;
        }
        return 0;
    }
    if (alength > blength + (int32_t)((exp) <= 49 ? d2utable[exp] : ((exp) + 3 - 1) / 3))
        return 1;
    if (alength + 1 < blength + (int32_t)((exp) <= 49 ? d2utable[exp] : ((exp) + 3 - 1) / 3))
        return -1;
    need = blength + ((exp) <= 49 ? d2utable[exp] : ((exp) + 3 - 1) / 3);
    if (need < alength)
        need = alength;
    need += 2;
    acc = accbuff;
    if (need * sizeof(uint16_t) > sizeof (accbuff)) {
        allocacc = (uint16_t *)malloc(need * sizeof(uint16_t));
        if (allocacc == ((void *)0))
            return (int32_t)2147483648U;
        acc = allocacc;
    }
    expunits = exp / 3;
    exprem = exp % 3;
    accunits = decUnitAddSub(a, alength, b, blength, expunits, acc, -(int32_t)DECPOWERS[exprem]);
    if (accunits < 0) {
        result = -1;
    } else {
        for (u = acc; u < acc + accunits - 1 && *u == 0;)
            u++;
        result = (*u == 0 ? 0 : +1);
    }
    ;
    return result;
}
static int32_t decUnitAddSub (const uint16_t *a, int32_t alength, const uint16_t *b, int32_t blength, int32_t bshift, uint16_t *c, int32_t m){
    const uint16_t *alsu = a;
    uint16_t *clsu = c;
    uint16_t *minC;
    uint16_t *maxC;
    int32_t carry = 0;
    int32_t add;
    int32_t est;
    maxC = c + alength;
    minC = c + blength;
    if (bshift != 0) {
        minC += bshift;
        if (a == c && bshift <= alength) {
            c += bshift;
            a += bshift;
        } else
            for (; c < clsu + bshift; a++ , c++) {
                if (a < alsu + alength) {
                    *c = *a;
                } else
                    *c = 0;
            }
    }
    if (minC > maxC) {
        uint16_t *hold = minC;
        minC = maxC;
        maxC = hold;
    }
    for (; c < minC; c++) {
        carry += *a;
        a++;
        carry += ((int32_t)*b) * m;
        b++;
        if ((uint32_t)carry <= 999) {
            *c = (uint16_t)carry;
            carry = 0;
            continue;
        }
        if (carry >= 0) {
            est = (((uint32_t)carry >> 3) * 16777) >> 21;
            *c = (uint16_t)(carry - est * (999 + 1));
            carry = est;
            if (*c < 999 + 1)
                continue;
            carry++;
            *c -= 999 + 1;
            continue;
        }
        carry = carry + (int32_t)(999 + 1) * (999 + 1);
        est = (((uint32_t)carry >> 3) * 16777) >> 21;
        *c = (uint16_t)(carry - est * (999 + 1));
        carry = est - (999 + 1);
        if (*c < 999 + 1)
            continue;
        carry++;
        *c -= 999 + 1;
    }
    if (c < maxC)
        for (; c < maxC; c++) {
            if (a < alsu + alength) {
                carry += *a;
                a++;
            } else {
                carry += ((int32_t)*b) * m;
                b++;
            }
            if ((uint32_t)carry <= 999) {
                *c = (uint16_t)carry;
                carry = 0;
                continue;
            }
            if (carry >= 0) {
                est = (((uint32_t)carry >> 3) * 16777) >> 21;
                *c = (uint16_t)(carry - est * (999 + 1));
                carry = est;
                if (*c < 999 + 1)
                    continue;
                carry++;
                *c -= 999 + 1;
                continue;
            }
            carry = carry + (int32_t)(999 + 1) * (999 + 1);
            est = (((uint32_t)carry >> 3) * 16777) >> 21;
            *c = (uint16_t)(carry - est * (999 + 1));
            carry = est - (999 + 1);
            if (*c < 999 + 1)
                continue;
            carry++;
            *c -= 999 + 1;
        }
    if (carry == 0)
        return c - clsu;
    if (carry > 0) {
        *c = (uint16_t)carry;
        c++;
        return c - clsu;
    }
    add = 1;
    for (c = clsu; c < maxC; c++) {
        add = 999 + add - *c;
        if (add <= 999) {
            *c = (uint16_t)add;
            add = 0;
        } else {
            *c = 0;
            add = 1;
        }
    }
    if ((add - carry - 1) != 0) {
        *c = (uint16_t)(add - carry - 1);
        c++;
    }
    return clsu - c;
}
static int32_t decShiftToLeast (uint16_t *uar, int32_t units, int32_t shift){
    uint16_t *target, *up;
    int32_t cut, count;
    int32_t quot, rem;
    if (shift == 0)
        return units;
    if (shift == units * 3) {
        *uar = 0;
        return 1;
    }
    target = uar;
    cut = ((shift) - (((shift) <= 49 ? d2utable[shift] : ((shift) + 3 - 1) / 3) - 1) * 3);
    if (cut == 3) {
        up = uar + ((shift) <= 49 ? d2utable[shift] : ((shift) + 3 - 1) / 3);
        for (; up < uar + units; target++ , up++)
            *target = *up;
        return target - uar;
    }
    up = uar + ((shift - cut) <= 49 ? d2utable[shift - cut] : ((shift - cut) + 3 - 1) / 3);
    count = units * 3 - shift;
    quot = ((((uint32_t)(*up) >> (cut)) * multies[cut]) >> 17);
    for (;; target++) {
        *target = (uint16_t)quot;
        count -= (3 - cut);
        if (count <= 0)
            break;
        up++;
        quot = *up;
        quot = ((((uint32_t)(quot) >> (cut)) * multies[cut]) >> 17);
        rem = *up - quot * DECPOWERS[cut];
        *target = (uint16_t)(*target + rem * DECPOWERS[3 - cut]);
        count -= cut;
        if (count <= 0)
            break;
    }
    return target - uar + 1;
}
static void decCopyFit (decNumber *dest, const decNumber *src, decContext *set, int32_t *residue, uint32_t *status){
    dest->bits = src->bits;
    dest->exponent = src->exponent;
    decSetCoeff(dest, set, src->lsu, src->digits, residue, status);
}
static void decSetCoeff (decNumber *dn, decContext *set, const uint16_t *lsu, int32_t len, int32_t *residue, uint32_t *status){
    int32_t discard;
    uint32_t cut;
    const uint16_t *up;
    uint16_t *target;
    int32_t count;
    uint32_t temp;
    discard = len - set->digits;
    if (discard <= 0) {
        if (dn->lsu != lsu) {
            count = len;
            up = lsu;
            for (target = dn->lsu; count > 0; target++ , up++ , count -= 3)
                *target = *up;
            dn->digits = len;
        }
        if (*residue != 0)
            *status |= (32 | 2048);
        return;
    }
    dn->exponent += discard;
    *status |= 2048;
    if (*residue > 1)
        *residue = 1;
    if (discard > len) {
        if (*residue <= 0) {
            count = len;
            for (up = lsu; count > 0; up++ , count -= 3)
                if (*up != 0) {
                    *residue = 1;
                    break;
                }
        }
        if (*residue != 0)
            *status |= 32;
        *dn->lsu = 0;
        dn->digits = 1;
        return;
    }
    count = 0;
    for (up = lsu; ; up++) {
        count += 3;
        if (count >= discard)
            break;
        if (*up != 0)
            *residue = 1;
    }
    cut = discard - (count - 3) - 1;
    if (cut == 3 - 1) {
        uint16_t half = (uint16_t)DECPOWERS[3] >> 1;
        if (*up >= half) {
            if (*up > half) {
                *residue = 7;
            } else
                *residue += 5;
        } else {
            if (*up != 0)
                *residue = 3;
        }
        if (set->digits <= 0) {
            *dn->lsu = 0;
            dn->digits = 1;
        } else {
            count = set->digits;
            dn->digits = count;
            up++;
            for (target = dn->lsu; count > 0; target++ , up++ , count -= 3)
                *target = *up;
        }
    } else {
        uint32_t discard1;
        uint32_t quot, rem;
        if (cut == 0) {
            quot = *up;
        } else {
            quot = ((((uint32_t)(*up) >> (cut)) * multies[cut]) >> 17);
            rem = *up - quot * DECPOWERS[cut];
            if (rem != 0)
                *residue = 1;
        }
        temp = (quot * 6554) >> 16;
        discard1 = quot - (((temp) << 1) + ((temp) << 3));
        quot = temp;
        *residue += resmap[discard1];
        cut++;
        if (set->digits <= 0) {
            *dn->lsu = 0;
            dn->digits = 1;
        } else {
            count = set->digits;
            dn->digits = count;
            for (target = dn->lsu; ; target++) {
                *target = (uint16_t)quot;
                count -= (3 - cut);
                if (count <= 0)
                    break;
                up++;
                quot = *up;
                quot = ((((uint32_t)(quot) >> (cut)) * multies[cut]) >> 17);
                rem = *up - quot * DECPOWERS[cut];
                *target = (uint16_t)(*target + rem * DECPOWERS[3 - cut]);
                count -= cut;
                if (count <= 0)
                    break;
            }
        }
    }
    if (*residue != 0)
        *status |= 32;
    return;
}
static void decApplyRound (decNumber *dn, decContext *set, int32_t residue, uint32_t *status){
    int32_t bump;
    if (residue == 0)
        return;
    bump = 0;
    switch (set->round) {
      case DEC_ROUND_05UP:
        {
            int32_t lsd5 = *dn->lsu % 5;
            if (residue < 0 && lsd5 != 1) {
                bump = -1;
            } else if (residue > 0 && lsd5 == 0)
                bump = 1;
            break;
        }
      case DEC_ROUND_DOWN:
        {
            if (residue < 0)
                bump = -1;
            break;
        }
      case DEC_ROUND_HALF_DOWN:
        {
            if (residue > 5)
                bump = 1;
            break;
        }
      case DEC_ROUND_HALF_EVEN:
        {
            if (residue > 5) {
                bump = 1;
            } else if (residue == 5) {
                if (*dn->lsu & 1)
                    bump = 1;
            }
            break;
        }
      case DEC_ROUND_HALF_UP:
        {
            if (residue >= 5)
                bump = 1;
            break;
        }
      case DEC_ROUND_UP:
        {
            if (residue > 0)
                bump = 1;
            break;
        }
      case DEC_ROUND_CEILING:
        {
            if ((((dn)->bits & 128) != 0)) {
                if (residue < 0)
                    bump = -1;
            } else {
                if (residue > 0)
                    bump = 1;
            }
            break;
        }
      case DEC_ROUND_FLOOR:
        {
            if (!(((dn)->bits & 128) != 0)) {
                if (residue < 0)
                    bump = -1;
            } else {
                if (residue > 0)
                    bump = 1;
            }
            break;
        }
      default:
        {
            *status |= 64;
            break;
        }
    }
    if (bump == 0)
        return;
    if (bump > 0) {
        uint16_t *up;
        uint32_t count = dn->digits;
        for (up = dn->lsu; ; up++) {
            if (count <= 3) {
                if (*up != DECPOWERS[count] - 1)
                    break;
                *up = (uint16_t)DECPOWERS[count - 1];
                for (up = up - 1; up >= dn->lsu; up--)
                    *up = 0;
                dn->exponent++;
                if ((dn->exponent + dn->digits) > set->emax + 1) {
                    decSetOverflow(dn, set, status);
                }
                return;
            }
            if (*up != 999)
                break;
            count -= 3;
        }
    } else {
        uint16_t *up, *sup;
        uint32_t count = dn->digits;
        for (up = dn->lsu; ; up++) {
            if (count <= 3) {
                if (*up != DECPOWERS[count - 1])
                    break;
                sup = up;
                *up = (uint16_t)DECPOWERS[count] - 1;
                for (up = up - 1; up >= dn->lsu; up--)
                    *up = (uint16_t)DECPOWERS[3] - 1;
                dn->exponent--;
                if (dn->exponent + 1 == set->emin - set->digits + 1) {
                    if (count == 1 && dn->digits == 1) {
                        *sup = 0;
                    } else {
                        *sup = (uint16_t)DECPOWERS[count - 1] - 1;
                        dn->digits--;
                    }
                    dn->exponent++;
                    *status |= 8192 | 4096 | 32 | 2048;
                }
                return;
            }
            if (*up != 0)
                break;
            count -= 3;
        }
    }
    decUnitAddSub(dn->lsu, ((dn->digits) <= 49 ? d2utable[dn->digits] : ((dn->digits) + 3 - 1) / 3), uarrone, 1, 0, dn->lsu, bump);
}
static void decFinalize (decNumber *dn, decContext *set, int32_t *residue, uint32_t *status){
    int32_t shift;
    int32_t tinyexp = set->emin - dn->digits + 1;
    if (dn->exponent <= tinyexp) {
        int32_t comp;
        decNumber nmin;
        if (dn->exponent < tinyexp) {
            decSetSubnormal(dn, set, residue, status);
            return;
        }
        decNumberZero(&nmin);
        nmin.lsu[0] = 1;
        nmin.exponent = set->emin;
        comp = decCompare(dn, &nmin, 1);
        if (comp == (int32_t)2147483648U) {
            ;
            return;
        }
        if (*residue < 0 && comp == 0) {
            decApplyRound(dn, set, *residue, status);
            decSetSubnormal(dn, set, residue, status);
            return;
        }
    }
    if (*residue != 0)
        decApplyRound(dn, set, *residue, status);
    if (dn->exponent <= set->emax - set->digits + 1)
        return;
    if (dn->exponent > set->emax - dn->digits + 1) {
        decSetOverflow(dn, set, status);
        return;
    }
    ;
    return;
}
static void decSetOverflow (decNumber *dn, decContext *set, uint32_t *status){
    uint8_t needmax = 0;
    uint8_t sign = dn->bits & 128;
    if ((*(dn)->lsu == 0 && (dn)->digits == 1 && (((dn)->bits & (64 | 32 | 16)) == 0))) {
        int32_t emax = set->emax;
        if (set->clamp)
            emax -= set->digits - 1;
        if (dn->exponent > emax) {
            dn->exponent = emax;
            *status |= 1024;
        }
        return;
    }
    decNumberZero(dn);
    switch (set->round) {
      case DEC_ROUND_DOWN:
        {
            needmax = 1;
            break;
        }
      case DEC_ROUND_05UP:
        {
            needmax = 1;
            break;
        }
      case DEC_ROUND_CEILING:
        {
            if (sign)
                needmax = 1;
            break;
        }
      case DEC_ROUND_FLOOR:
        {
            if (!sign)
                needmax = 1;
            break;
        }
        ;
    }
    if (needmax) {
        decSetMaxValue(dn, set);
        dn->bits = sign;
    } else
        dn->bits = sign | 64;
    *status |= 512 | 32 | 2048;
}
static void decSetMaxValue (decNumber *dn, decContext *set){
    uint16_t *up;
    int32_t count = set->digits;
    dn->digits = count;
    for (up = dn->lsu; ; up++) {
        if (count > 3) {
            *up = 999;
        } else {
            *up = (uint16_t)(DECPOWERS[count] - 1);
            break;
        }
        count -= 3;
    }
    dn->bits = 0;
    dn->exponent = set->emax - set->digits + 1;
}
static void decSetSubnormal (decNumber *dn, decContext *set, int32_t *residue, uint32_t *status){
    decContext workset;
    int32_t etiny, adjust;
    etiny = set->emin - (set->digits - 1);
    if (*(dn)->lsu == 0 && (dn)->digits == 1 && (((dn)->bits & (64 | 32 | 16)) == 0)) {
        return;
    }
    *status |= 4096;
    adjust = etiny - dn->exponent;
    if (adjust <= 0) {
        ;
        return;
    }
    workset = *set;
    workset.digits = dn->digits - adjust;
    workset.emin -= adjust;
    decSetCoeff(dn, &workset, dn->lsu, dn->digits, residue, status);
    decApplyRound(dn, &workset, *residue, status);
}
static decNumber * decDecap (decNumber *dn, int32_t drop){
    uint16_t *msu;
    int32_t cut;
    if (drop >= dn->digits) {
        ;
        return dn;
    }
    msu = dn->lsu + ((dn->digits - drop) <= 49 ? d2utable[dn->digits - drop] : ((dn->digits - drop) + 3 - 1) / 3) - 1;
    cut = ((dn->digits - drop) - (((dn->digits - drop) <= 49 ? d2utable[dn->digits - drop] : ((dn->digits - drop) + 3 - 1) / 3) - 1) * 3);
    if (cut != 3)
        *msu %= DECPOWERS[cut];
    dn->digits = decGetDigits(dn->lsu, msu - dn->lsu + 1);
    return dn;
}
static decNumber * decNaNs (decNumber *res, const decNumber *lhs, const decNumber *rhs, decContext *set, uint32_t *status){
    if (lhs->bits & 16) {
        *status |= 128 | 1073741824;
    } else if (rhs == ((void *)0)) {
        ;
    } else if (rhs->bits & 16) {
        lhs = rhs;
        *status |= 128 | 1073741824;
    } else if (lhs->bits & 32) {
        ;
    } else
        lhs = rhs;
    if (lhs->digits <= set->digits) {
        decNumberCopy(res, lhs);
    } else {
        const uint16_t *ul;
        uint16_t *ur, *uresp1;
        res->bits = lhs->bits;
        uresp1 = res->lsu + ((set->digits) <= 49 ? d2utable[set->digits] : ((set->digits) + 3 - 1) / 3);
        for (ur = res->lsu , ul = lhs->lsu; ur < uresp1; ur++ , ul++)
            *ur = *ul;
        res->digits = ((set->digits) <= 49 ? d2utable[set->digits] : ((set->digits) + 3 - 1) / 3) * 3;
        if (res->digits > set->digits)
            decDecap(res, res->digits - set->digits);
    }
    ;
    return res;
}
static int32_t decGetDigits (uint16_t *uar, int32_t len){
    uint16_t *up = uar + (len - 1);
    int32_t digits = (len - 1) * 3 + 1;
    for (; up >= uar; up--) {
        if (*up == 0) {
            if (digits == 1)
                break;
            digits -= 3;
            continue;
        }
        if (*up < 10)
            break;
        digits++;
        if (*up < 100)
            break;
        digits++;
    }
    return digits;
}
