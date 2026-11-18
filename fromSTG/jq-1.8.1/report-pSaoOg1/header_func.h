#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
const uint8_t d2utable[50] = {0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10, 11, 11, 11, 12, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15, 15, 16, 16, 16, 17};
;
static decNumber *decNaNs(decNumber *, const decNumber *, const decNumber *, decContext *, uint32_t *);

decNumber *decNumberZero(decNumber *dn) ;

static void decCopyFit(decNumber *, const decNumber *, decContext *, int32_t *, uint32_t *);

static void decFinalize(decNumber *, decContext *, int32_t *, uint32_t *);

decNumber *decNumberCopy(decNumber *dest, const decNumber *src) ;

static int32_t decShiftToLeast(uint16_t *, int32_t, int32_t);

static int32_t decUnitAddSub(const uint16_t *, int32_t, const uint16_t *, int32_t, int32_t, uint16_t *, int32_t);

static int32_t decGetDigits(uint16_t *, int32_t);

static int32_t decUnitCompare(const uint16_t *, int32_t, const uint16_t *, int32_t, int32_t);

static void decSetCoeff(decNumber *, decContext *, const uint16_t *, int32_t, int32_t *, uint32_t *);

extern const uint32_t DECPOWERS[10];
;
static const uint32_t multies[] = {131073, 26215, 5243, 1049, 210};
;
static const uint8_t resmap[10] = {0, 3, 3, 3, 3, 5, 7, 7, 7, 7};
;
static void decSetOverflow(decNumber *, decContext *, uint32_t *);

static uint16_t uarrone[1] = {1};
;
static void decSetSubnormal(decNumber *, decContext *, int32_t *, uint32_t *);

static int32_t decCompare(const decNumber *lhs, const decNumber *rhs, uint8_t abs) ;

static void decApplyRound(decNumber *dn, decContext *set, int32_t residue, uint32_t *status) ;

static void decSetMaxValue(decNumber *, decContext *);

static decNumber *decDecap(decNumber *dn, int32_t drop) ;

#endif