static decNumber * decMultiplyOp (decNumber *res, const decNumber *lhs, const decNumber *rhs, decContext *set, uint32_t *status){
    int32_t accunits;
    int32_t exponent;
    int32_t residue = 0;
    uint8_t bits;
    uint16_t *acc;
    int32_t needbytes;
    void *allocacc = ((void *)0);
    uint16_t accbuff[49];
    const uint16_t *mer, *mermsup;
    int32_t madlength;
    int32_t shift;
    uint32_t zlhibuff[10];
    uint32_t *zlhi = zlhibuff;
    uint32_t *alloclhi = ((void *)0);
    uint32_t zrhibuff[10];
    uint32_t *zrhi = zrhibuff;
    uint32_t *allocrhi = ((void *)0);
    uint64_t zaccbuff[20];
    uint64_t *zacc = zaccbuff;
    uint32_t *lip, *rip;
    uint32_t *lmsi, *rmsi;
    int32_t ilhs, irhs, iacc;
    int32_t lazy;
    uint64_t lcarry;
    uint32_t carry;
    int32_t count;
    const uint16_t *cup;
    uint16_t *up;
    uint64_t *lp;
    int32_t p;
    bits = (uint8_t)((lhs->bits ^ rhs->bits) & 128);
    if (((lhs->bits | rhs->bits) & (64 | 32 | 16))) {
        ;
        ;
        return res;
    }
    if (lhs->digits < rhs->digits) {
        const decNumber *hold = lhs;
        lhs = rhs;
        rhs = hold;
    }
    do {
        if (rhs->digits > (3 * 2)) {
            ilhs = (lhs->digits + 9 - 1) / 9;
            irhs = (rhs->digits + 9 - 1) / 9;
            iacc = ilhs + irhs;
            needbytes = ilhs * sizeof(uint32_t);
            if (needbytes > (int32_t)sizeof (zlhibuff)) {
                alloclhi = (uint32_t *)malloc(needbytes);
                zlhi = alloclhi;
            }
            needbytes = irhs * sizeof(uint32_t);
            if (needbytes > (int32_t)sizeof (zrhibuff)) {
                allocrhi = (uint32_t *)malloc(needbytes);
                zrhi = allocrhi;
            }
            needbytes = iacc * sizeof(uint64_t);
            if (needbytes > (int32_t)sizeof (zaccbuff)) {
                allocacc = (uint64_t *)malloc(needbytes);
                zacc = (uint64_t *)allocacc;
            }
            if (zlhi == ((void *)0) || zrhi == ((void *)0) || zacc == ((void *)0)) {
                ;
                break;
            }
            acc = (uint16_t *)zacc;
            for (count = lhs->digits , cup = lhs->lsu , lip = zlhi; count > 0; lip++)
                for (p = 0 , *lip = 0; p < 9 && count > 0; p += 3 , cup++ , count -= 3)
                    *lip += *cup * DECPOWERS[p];
            lmsi = lip - 1;
            for (count = rhs->digits , cup = rhs->lsu , rip = zrhi; count > 0; rip++)
                for (p = 0 , *rip = 0; p < 9 && count > 0; p += 3 , cup++ , count -= 3)
                    *rip += *cup * DECPOWERS[p];
            rmsi = rip - 1;
            for (lp = zacc; lp < zacc + iacc; lp++)
                *lp = 0;
            lazy = 18;
            for (rip = zrhi; rip <= rmsi; rip++) {
                lp = zacc + (rip - zrhi);
                for (lip = zlhi; lip <= lmsi; lip++ , lp++) {
                    *lp += (uint64_t)(*lip) * (*rip);
                }
                lazy--;
                if (lazy > 0 && rip != rmsi)
                    continue;
                ;
                lazy = 18;
                for (lp = zacc; lp < zacc + iacc; lp++) {
                    if (*lp < 1000000000)
                        continue;
                    ;
                    lcarry = *lp / 1000000000;
                    if (lcarry < 1000000000) {
                        carry = (uint32_t)lcarry;
                    } else {
                        uint32_t carry2 = (uint32_t)(lcarry / 1000000000);
                        *(lp + 2) += carry2;
                        *lp -= ((uint64_t)1000000000 * 1000000000 * carry2);
                        carry = (uint32_t)(lcarry - ((uint64_t)1000000000 * carry2));
                    }
                    *(lp + 1) += carry;
                    *lp -= ((uint64_t)1000000000 * carry);
                }
            }
            ;
        } else {
            ;
        }
        ;
        ;
        ;
        ;
        ;
        ;
        ;
    } while (0);
    ;
    ;
    ;
    return res;
}


