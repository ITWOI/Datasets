#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

void _Py_Dealloc(PyObject *);

static inline void _Py_DECREF(PyObject *op) ;

static inline void _Py_INCREF(PyObject *op) ;

static inline PyThreadState *_PyRuntimeState_GetThreadState(_PyRuntimeState *runtime) ;

extern _PyRuntimeState _PyRuntime;
;
static inline PyThreadState *_PyThreadState_GET(void) ;

static inline PyInterpreterState *_PyInterpreterState_GET(void) ;

static inline PyObject *__PyLong_GetSmallInt_internal(int value) ;

static inline void _Py_SET_TYPE(PyObject *ob, PyTypeObject *type) ;

static inline int _PyType_HasFeature(PyTypeObject *type, unsigned long feature) ;


void _Py_NewReference(PyObject *op);

static inline void _Py_SET_SIZE(PyVarObject *ob, Py_ssize_t size) ;

static inline void _PyObject_Init(PyObject *op, PyTypeObject *typeobj) ;

static PyObject *get_small_int(sdigit ival) ;

static inline Py_ssize_t _Py_REFCNT(const PyObject *ob) ;

PyObject *PyLong_FromLong(long);


void PyErr_SetString(PyObject *exception, const char *string);

extern PyObject *PyExc_OverflowError;
;

void *PyObject_Malloc(size_t size);


PyObject *PyErr_NoMemory(void);

static inline void _PyObject_InitVar(PyVarObject *op, PyTypeObject *typeobj, Py_ssize_t size) ;

static PyObject *long_to_decimal_string(PyObject *aa) ;

static Py_hash_t long_hash(PyLongObject *v) ;


PyObject *PyObject_GenericGetAttr(PyObject *, PyObject *);

static PyObject *long_richcompare(PyObject *self, PyObject *other, int op) ;

static PyObject *long_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) ;


void PyObject_Free(void *ptr);

extern PyTypeObject PyType_Type;
static PyObject *long_add(PyLongObject *a, PyLongObject *b) ;

static PyObject *long_sub(PyLongObject *a, PyLongObject *b) ;

static PyObject *long_mul(PyLongObject *a, PyLongObject *b) ;

static PyObject *long_mod(PyObject *a, PyObject *b) ;

static PyObject *long_divmod(PyObject *a, PyObject *b) ;

static PyObject *long_pow(PyObject *v, PyObject *w, PyObject *x) ;

static PyObject *long_neg(PyLongObject *v) ;

static PyObject *long_long(PyObject *v) ;

static PyObject *long_abs(PyLongObject *v) ;

static int long_bool(PyLongObject *v) ;

static PyObject *long_invert(PyLongObject *v) ;

static PyObject *long_lshift(PyObject *a, PyObject *b) ;

static PyObject *long_rshift(PyObject *a, PyObject *b) ;

static PyObject *long_and(PyObject *a, PyObject *b) ;

static PyObject *long_xor(PyObject *a, PyObject *b) ;

static PyObject *long_or(PyObject *a, PyObject *b) ;

static PyObject *long_float(PyObject *v) ;

static PyObject *long_div(PyObject *a, PyObject *b) ;

static PyObject *long_true_divide(PyObject *v, PyObject *w) ;

static PyNumberMethods long_as_number = {(binaryfunc)long_add, (binaryfunc)long_sub, (binaryfunc)long_mul, long_mod, long_divmod, long_pow, (unaryfunc)long_neg, long_long, (unaryfunc)long_abs, (inquiry)long_bool, (unaryfunc)long_invert, long_lshift, long_rshift, long_and, long_xor, long_or, long_long, 0, long_float, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, long_div, long_true_divide, 0, 0, long_long};
static const char long_doc[] = "int([x]) -> integer\nint(x, base=10) -> integer\n\nConvert a number or string to an integer, or return 0 if no arguments\nare given.  If x is a number, return x.__int__().  For floating point\nnumbers, this truncates towards zero.\n\nIf x is not a number or if base is given, then x must be a string,\nbytes, or bytearray instance representing an integer literal in the\ngiven base.  The literal can be preceded by '+' or '-' and be surrounded\nby whitespace.  The base defaults to 10.  Valid bases are 0 and 2-36.\nBase 0 means to interpret the base from the string as an integer literal.\n>>> int('0b100', base=0)\n4";
static PyObject *long_long_meth(PyObject *self, PyObject *_unused_ignored) ;

static PyObject *int_bit_length(PyObject *self, PyObject *_unused_ignored) ;

static const char int_bit_length__doc__[] = "bit_length($self, /)\n--\n\nNumber of bits necessary to represent self in binary.\n\n>>> bin(37)\n'0b100101'\n>>> (37).bit_length()\n6";
static PyObject *int_bit_count(PyObject *self, PyObject *_unused_ignored) ;

static const char int_bit_count__doc__[] = "bit_count($self, /)\n--\n\nNumber of ones in the binary representation of the absolute value of self.\n\nAlso known as the population count.\n\n>>> bin(13)\n'0b1101'\n>>> (13).bit_count()\n3";
static PyObject *int_to_bytes(PyObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames) ;

static const char int_to_bytes__doc__[] = "to_bytes($self, /, length, byteorder, *, signed=False)\n--\n\nReturn an array of bytes representing an integer.\n\n  length\n    Length of bytes object to use.  An OverflowError is raised if the\n    integer is not representable with the given number of bytes.\n  byteorder\n    The byte order used to represent the integer.  If byteorder is 'big',\n    the most significant byte is at the beginning of the byte array.  If\n    byteorder is 'little', the most significant byte is at the end of the\n    byte array.  To request the native byte order of the host system, use\n    `sys.byteorder' as the byte order value.\n  signed\n    Determines whether two's complement is used to represent the integer.\n    If signed is False and a negative integer is given, an OverflowError\n    is raised.";
static PyObject *int_from_bytes(PyTypeObject *type, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames) ;

static const char int_from_bytes__doc__[] = "from_bytes($type, /, bytes, byteorder, *, signed=False)\n--\n\nReturn the integer represented by the given array of bytes.\n\n  bytes\n    Holds the array of bytes to convert.  The argument must either\n    support the buffer protocol or be an iterable object producing bytes.\n    Bytes and bytearray are examples of built-in objects that support the\n    buffer protocol.\n  byteorder\n    The byte order used to represent the integer.  If byteorder is 'big',\n    the most significant byte is at the beginning of the byte array.  If\n    byteorder is 'little', the most significant byte is at the end of the\n    byte array.  To request the native byte order of the host system, use\n    `sys.byteorder' as the byte order value.\n  signed\n    Indicates whether two's complement is used to represent the integer.";
static PyObject *int_as_integer_ratio(PyObject *self, PyObject *_unused_ignored) ;

static const char int_as_integer_ratio__doc__[] = "as_integer_ratio($self, /)\n--\n\nReturn integer ratio.\n\nReturn a pair of integers, whose ratio is exactly equal to the original int\nand with a positive denominator.\n\n>>> (10).as_integer_ratio()\n(10, 1)\n>>> (-10).as_integer_ratio()\n(-10, 1)\n>>> (0).as_integer_ratio()\n(0, 1)";
static PyObject *int___round__(PyObject *self, PyObject *const *args, Py_ssize_t nargs) ;

static const char int___round____doc__[] = "__round__($self, ndigits=<unrepresentable>, /)\n--\n\nRounding an Integral returns itself.\n\nRounding with an ndigits argument also returns an integer.";
static PyObject *int___getnewargs__(PyObject *self, PyObject *_unused_ignored) ;

static const char int___getnewargs____doc__[] = "__getnewargs__($self, /)\n--\n\n";
static PyObject *int___format__(PyObject *self, PyObject *arg) ;

static const char int___format____doc__[] = "__format__($self, format_spec, /)\n--\n\n";
static PyObject *int___sizeof__(PyObject *self, PyObject *_unused_ignored) ;

static const char int___sizeof____doc__[] = "__sizeof__($self, /)\n--\n\nReturns size in memory, in bytes.";
static PyMethodDef long_methods[] = {{"conjugate", long_long_meth, 4, "Returns self, the complex conjugate of any int."}, {"bit_length", (PyCFunction)int_bit_length, 4, int_bit_length__doc__}, {"bit_count", (PyCFunction)int_bit_count, 4, int_bit_count__doc__}, {"to_bytes", (PyCFunction)(void (*)(void))int_to_bytes, 128 | 2, int_to_bytes__doc__}, {"from_bytes", (PyCFunction)(void (*)(void))int_from_bytes, 128 | 2 | 16, int_from_bytes__doc__}, {"as_integer_ratio", (PyCFunction)int_as_integer_ratio, 4, int_as_integer_ratio__doc__}, {"__trunc__", long_long_meth, 4, "Truncating an Integral returns itself."}, {"__floor__", long_long_meth, 4, "Flooring an Integral returns itself."}, {"__ceil__", long_long_meth, 4, "Ceiling of an Integral returns itself."}, {"__round__", (PyCFunction)(void (*)(void))int___round__, 128, int___round____doc__}, {"__getnewargs__", (PyCFunction)int___getnewargs__, 4, int___getnewargs____doc__}, {"__format__", (PyCFunction)int___format__, 8, int___format____doc__}, {"__sizeof__", (PyCFunction)int___sizeof__, 4, int___sizeof____doc__}, {((void *)0), ((void *)0)}};
static PyObject *long_get0(PyObject *_unused_self, void *_unused_context) ;

static PyObject *long_get1(PyObject *_unused_self, void *_unused_ignored) ;

static PyGetSetDef long_getset[] = {{"real", (getter)long_long_meth, (setter)((void *)0), "the real part of a complex number", ((void *)0)}, {"imag", long_get0, (setter)((void *)0), "the imaginary part of a complex number", ((void *)0)}, {"numerator", (getter)long_long_meth, (setter)((void *)0), "the numerator of a rational number in lowest terms", ((void *)0)}, {"denominator", long_get1, (setter)((void *)0), "the denominator of a rational number in lowest terms", ((void *)0)}, {((void *)0)}};
PyTypeObject PyLong_Type = {{{1, &PyType_Type}, 0}, "int", __builtin_offsetof(PyLongObject, ob_digit), sizeof(digit), 0, 0, 0, 0, 0, long_to_decimal_string, &long_as_number, 0, 0, (hashfunc)long_hash, 0, 0, PyObject_GenericGetAttr, 0, 0, (0 | 0) | (1UL << 10) | (1UL << 24) | (1UL << 22), long_doc, 0, 0, long_richcompare, 0, 0, 0, long_methods, 0, long_getset, 0, 0, 0, 0, 0, 0, 0, long_new, PyObject_Free};
;
PyLongObject *_PyLong_New(Py_ssize_t size) ;

static inline int _Py_bit_length(unsigned long x) ;

static digit inplace_divrem1(digit *pout, digit *pin, Py_ssize_t size, digit n) ;

static PyLongObject *long_normalize(PyLongObject *v) ;

extern PyObject *PyExc_ZeroDivisionError;
;
static inline PyObject *_PyLong_GetZero(void) ;

static PyLongObject *divrem1(PyLongObject *a, digit n, digit *prem) ;

static PyLongObject *x_divrem(PyLongObject *, PyLongObject *, PyLongObject **);

static inline void _PyLong_Negate(PyLongObject **x_p) ;

static PyLongObject *maybe_small_long(PyLongObject *v) ;

static int bit_length_digit(digit x) ;

static digit v_lshift(digit *z, digit *a, Py_ssize_t m, int d) ;


int PyErr_CheckSignals(void);

static digit v_rshift(digit *z, digit *a, Py_ssize_t m, int d) ;

extern PyObject _Py_NotImplementedStruct;
;
static inline int PyType_HasFeature(PyTypeObject *type, unsigned long feature) ;

static inline PyObject *_Py_NewRef(PyObject *obj) ;

static PyLongObject *x_add(PyLongObject *a, PyLongObject *b) ;

static PyLongObject *x_sub(PyLongObject *a, PyLongObject *b) ;

static PyLongObject *x_mul(PyLongObject *a, PyLongObject *b) ;

static PyLongObject *k_lopsided_mul(PyLongObject *a, PyLongObject *b);

static int kmul_split(PyLongObject *n, Py_ssize_t size, PyLongObject **high, PyLongObject **low) ;

static PyLongObject *k_mul(PyLongObject *a, PyLongObject *b) ;

static digit v_isub(digit *x, Py_ssize_t m, digit *y, Py_ssize_t n) ;

static digit v_iadd(digit *x, Py_ssize_t m, digit *y, Py_ssize_t n) ;

static inline void _Py_XDECREF(PyObject *op) ;

PyObject *PyLong_FromLongLong(long long ival) ;

static PyObject *fast_floor_div(PyLongObject *a, PyLongObject *b) ;

static PyObject *fast_mod(PyLongObject *a, PyLongObject *b) ;

static int long_divrem(PyLongObject *a, PyLongObject *b, PyLongObject **pdiv, PyLongObject **prem) ;

static inline PyObject *_PyLong_GetOne(void) ;

static int l_divmod(PyLongObject *v, PyLongObject *w, PyLongObject **pdiv, PyLongObject **pmod) ;

static Py_ssize_t long_compare(PyLongObject *a, PyLongObject *b) ;

extern PyObject *PyExc_ValueError;
;
extern PyObject _Py_NoneStruct;
;
extern PyTypeObject PyFloat_Type;
;
PyObject *_PyLong_Copy(PyLongObject *src) ;

static PyLongObject *long_invmod(PyLongObject *a, PyLongObject *n) ;

static inline int _Py_IS_TYPE(const PyObject *ob, const PyTypeObject *type) ;

#endif