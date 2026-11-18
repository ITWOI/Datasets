#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static DecCondMap signal_map[] = {{"InvalidOperation", "decimal.InvalidOperation", (2U | 8U | 16U | 32U | 128U | 256U | 512U), ((void *)0)}, {"FloatOperation", "decimal.FloatOperation", 1024U, ((void *)0)}, {"DivisionByZero", "decimal.DivisionByZero", 4U, ((void *)0)}, {"Overflow", "decimal.Overflow", 2048U, ((void *)0)}, {"Underflow", "decimal.Underflow", 16384U, ((void *)0)}, {"Subnormal", "decimal.Subnormal", 8192U, ((void *)0)}, {"Inexact", "decimal.Inexact", 64U, ((void *)0)}, {"Rounded", "decimal.Rounded", 4096U, ((void *)0)}, {"Clamped", "decimal.Clamped", 1U, ((void *)0)}, {((void *)0)}};
;

PyObject *PyUnicode_FromFormat(const char *format, ...);

#endif