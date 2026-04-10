#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static decNumber *decNaNs(decNumber *, const decNumber *, const decNumber *, decContext *, uint32_t *);

decNumber *decNumberZero(decNumber *dn) ;

static int32_t decUnitAddSub(const uint16_t *, int32_t, const uint16_t *, int32_t, int32_t, uint16_t *, int32_t);

static int32_t decGetDigits(uint16_t *, int32_t);

static void decSetCoeff(decNumber *, decContext *, const uint16_t *, int32_t, int32_t *, uint32_t *);

static void decFinalize(decNumber *, decContext *, int32_t *, uint32_t *);

extern const uint32_t DECPOWERS[10];
;
#endif