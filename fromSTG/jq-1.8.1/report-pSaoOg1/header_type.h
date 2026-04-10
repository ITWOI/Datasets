#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 

/*Ano*/typedef struct {
    int32_t digits;
    int32_t exponent;
    uint8_t bits;
    uint16_t lsu[1];
} decNumber;

/*ENUM*/
enum rounding {
    DEC_ROUND_CEILING,
    DEC_ROUND_UP,
    DEC_ROUND_HALF_UP,
    DEC_ROUND_HALF_EVEN,
    DEC_ROUND_HALF_DOWN,
    DEC_ROUND_DOWN,
    DEC_ROUND_FLOOR,
    DEC_ROUND_05UP,
    DEC_ROUND_MAX
};


/*Ano*/typedef struct {
    int32_t digits;
    int32_t emax;
    int32_t emin;
    enum rounding round;
    uint32_t traps;
    uint32_t status;
    uint8_t clamp;
} decContext;

#endif