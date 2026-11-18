#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline int _Py_IS_TYPE(const PyObject *ob, const PyTypeObject *type) ;


int PyType_IsSubtype(PyTypeObject *, PyTypeObject *);


void _Py_Dealloc(PyObject *);

static inline void _Py_DECREF(PyObject *op) ;

static inline void _Py_INCREF(PyObject *op) ;

static inline int PyType_HasFeature(PyTypeObject *type, unsigned long feature) ;

static inline vectorcallfunc PyVectorcall_Function(PyObject *callable) ;


PyObject *_PyObject_MakeTpCall(PyThreadState *tstate, PyObject *callable, PyObject *const *args, Py_ssize_t nargs, PyObject *keywords);

static inline Py_ssize_t PyVectorcall_NARGS(size_t n) ;


PyObject *_Py_CheckFunctionResult(PyThreadState *tstate, PyObject *callable, PyObject *result, const char *where);


PyThreadState *PyThreadState_Get(void);

static inline PyObject *_PyObject_VectorcallTstate(PyThreadState *tstate, PyObject *callable, PyObject *const *args, size_t nargsf, PyObject *kwnames) ;

static inline void *_PyModule_GetState(PyObject *mod) ;


PyObject *const *_PyArg_UnpackKeywords(PyObject *const *args, Py_ssize_t nargs, PyObject *kwargs, PyObject *kwnames, struct _PyArg_Parser *parser, int minpos, int maxpos, int minkw, PyObject **buf);

static int Struct___init___impl(PyStructObject *self, PyObject *format);


int PyObject_GetBuffer(PyObject *obj, Py_buffer *view, int flags);


int PyBuffer_IsContiguous(const Py_buffer *view, char fort);


void _PyArg_BadArgument(const char *, const char *, const char *, PyObject *);

static PyObject *Struct_unpack_impl(PyStructObject *self, Py_buffer *buffer);


void PyBuffer_Release(Py_buffer *view);


Py_ssize_t PyLong_AsSsize_t(PyObject *);


PyObject *PyErr_Occurred(void);


PyObject *_PyNumber_Index(PyObject *o);

static PyObject *Struct_unpack_from_impl(PyStructObject *self, Py_buffer *buffer, Py_ssize_t offset);

static PyObject *_clearcache_impl(PyObject *module);

static int cache_struct_converter(PyObject *, PyObject *, PyStructObject **);

static Py_ssize_t calcsize_impl(PyObject *module, PyStructObject *s_object);


PyObject *PyLong_FromSsize_t(Py_ssize_t);

static inline void _Py_XDECREF(PyObject *op) ;


int _PyArg_CheckPositional(const char *, Py_ssize_t, Py_ssize_t, Py_ssize_t);

static PyObject *unpack_impl(PyObject *module, PyStructObject *s_object, Py_buffer *buffer);

static PyObject *unpack_from_impl(PyObject *module, PyStructObject *s_object, Py_buffer *buffer, Py_ssize_t offset);

static PyObject *iter_unpack_impl(PyObject *module, PyStructObject *s_object, PyObject *buffer);


int PyIndex_Check(PyObject *);


void PyErr_SetString(PyObject *exception, const char *string);

static PyObject *get_pylong(_structmodulestate *state, PyObject *v) ;


long PyLong_AsLong(PyObject *);


int PyErr_ExceptionMatches(PyObject *);

extern PyObject *PyExc_OverflowError;
;

unsigned long PyLong_AsUnsignedLong(PyObject *);


long long PyLong_AsLongLong(PyObject *);


unsigned long long PyLong_AsUnsignedLongLong(PyObject *);


size_t PyLong_AsSize_t(PyObject *);


double _PyFloat_Unpack2(const unsigned char *p, int le);


PyObject *PyFloat_FromDouble(double);


double PyFloat_AsDouble(PyObject *);


int _PyFloat_Pack2(double x, unsigned char *p, int le);


double _PyFloat_Unpack4(const unsigned char *p, int le);


double _PyFloat_Unpack8(const unsigned char *p, int le);


PyObject *PyErr_Format(PyObject *exception, const char *format, ...);


PyObject *PyBytes_FromStringAndSize(const char *, Py_ssize_t);


PyObject *PyLong_FromLong(long);


PyObject *PyLong_FromUnsignedLong(unsigned long);


PyObject *PyLong_FromSize_t(size_t);


PyObject *PyLong_FromLongLong(long long);


PyObject *PyLong_FromUnsignedLongLong(unsigned long long);


PyObject *PyBool_FromLong(long);

static PyObject *unpack_halffloat(const char *p, int le) ;


PyObject *PyLong_FromVoidPtr(void *);

static int get_long(_structmodulestate *state, PyObject *v, long *p) ;


Py_ssize_t PyBytes_Size(PyObject *);

static int _range_error(_structmodulestate *state, const formatdef *f, int is_unsigned) ;

static int get_ulong(_structmodulestate *state, PyObject *v, unsigned long *p) ;

static int get_ssize_t(_structmodulestate *state, PyObject *v, Py_ssize_t *p) ;

static int get_size_t(_structmodulestate *state, PyObject *v, size_t *p) ;

static int get_longlong(_structmodulestate *state, PyObject *v, long long *p) ;

static int get_ulonglong(_structmodulestate *state, PyObject *v, unsigned long long *p) ;


int PyObject_IsTrue(PyObject *);

static int pack_halffloat(_structmodulestate *state, char *p, PyObject *v, int le) ;


void *PyLong_AsVoidPtr(PyObject *);

static PyObject *unpack_float(const char *p, int le) ;

static PyObject *unpack_double(const char *p, int le) ;


int _PyLong_AsByteArray(PyLongObject *v, unsigned char *bytes, size_t n, int little_endian, int is_signed);


int _PyFloat_Pack4(double x, unsigned char *p, int le);


int _PyFloat_Pack8(double x, unsigned char *p, int le);

static PyObject *nu_byte(_structmodulestate *state, const char *p, const formatdef *f) ;

static int np_byte(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *nu_ubyte(_structmodulestate *state, const char *p, const formatdef *f) ;

static int np_ubyte(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *nu_char(_structmodulestate *state, const char *p, const formatdef *f) ;

static int np_char(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *lu_int(_structmodulestate *state, const char *p, const formatdef *f) ;

static int lp_int(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *lu_uint(_structmodulestate *state, const char *p, const formatdef *f) ;

static int lp_uint(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *lu_longlong(_structmodulestate *state, const char *p, const formatdef *f) ;

static int lp_longlong(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *lu_ulonglong(_structmodulestate *state, const char *p, const formatdef *f) ;

static int lp_ulonglong(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *bu_bool(_structmodulestate *state, const char *p, const formatdef *f) ;

static int bp_bool(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *lu_halffloat(_structmodulestate *state, const char *p, const formatdef *f) ;

static int lp_halffloat(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *lu_float(_structmodulestate *state, const char *p, const formatdef *f) ;

static int lp_float(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *lu_double(_structmodulestate *state, const char *p, const formatdef *f) ;

static int lp_double(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static formatdef lilendian_table[] = {{'x', 1, 0, ((void *)0)}, {'b', 1, 0, nu_byte, np_byte}, {'B', 1, 0, nu_ubyte, np_ubyte}, {'c', 1, 0, nu_char, np_char}, {'s', 1, 0, ((void *)0)}, {'p', 1, 0, ((void *)0)}, {'h', 2, 0, lu_int, lp_int}, {'H', 2, 0, lu_uint, lp_uint}, {'i', 4, 0, lu_int, lp_int}, {'I', 4, 0, lu_uint, lp_uint}, {'l', 4, 0, lu_int, lp_int}, {'L', 4, 0, lu_uint, lp_uint}, {'q', 8, 0, lu_longlong, lp_longlong}, {'Q', 8, 0, lu_ulonglong, lp_ulonglong}, {'?', 1, 0, bu_bool, bp_bool}, {'e', 2, 0, lu_halffloat, lp_halffloat}, {'f', 4, 0, lu_float, lp_float}, {'d', 8, 0, lu_double, lp_double}, {0}};
;
static PyObject *bu_int(_structmodulestate *state, const char *p, const formatdef *f) ;

static int bp_int(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *bu_uint(_structmodulestate *state, const char *p, const formatdef *f) ;

static int bp_uint(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *bu_longlong(_structmodulestate *state, const char *p, const formatdef *f) ;

static int bp_longlong(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *bu_ulonglong(_structmodulestate *state, const char *p, const formatdef *f) ;

static int bp_ulonglong(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *bu_halffloat(_structmodulestate *state, const char *p, const formatdef *f) ;

static int bp_halffloat(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *bu_float(_structmodulestate *state, const char *p, const formatdef *f) ;

static int bp_float(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *bu_double(_structmodulestate *state, const char *p, const formatdef *f) ;

static int bp_double(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static formatdef bigendian_table[] = {{'x', 1, 0, ((void *)0)}, {'b', 1, 0, nu_byte, np_byte}, {'B', 1, 0, nu_ubyte, np_ubyte}, {'c', 1, 0, nu_char, np_char}, {'s', 1, 0, ((void *)0)}, {'p', 1, 0, ((void *)0)}, {'h', 2, 0, bu_int, bp_int}, {'H', 2, 0, bu_uint, bp_uint}, {'i', 4, 0, bu_int, bp_int}, {'I', 4, 0, bu_uint, bp_uint}, {'l', 4, 0, bu_int, bp_int}, {'L', 4, 0, bu_uint, bp_uint}, {'q', 8, 0, bu_longlong, bp_longlong}, {'Q', 8, 0, bu_ulonglong, bp_ulonglong}, {'?', 1, 0, bu_bool, bp_bool}, {'e', 2, 0, bu_halffloat, bp_halffloat}, {'f', 4, 0, bu_float, bp_float}, {'d', 8, 0, bu_double, bp_double}, {0}};
;
static PyObject *nu_short(_structmodulestate *state, const char *p, const formatdef *f) ;

static int np_short(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *nu_ushort(_structmodulestate *state, const char *p, const formatdef *f) ;

static int np_ushort(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *nu_int(_structmodulestate *state, const char *p, const formatdef *f) ;

static int np_int(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *nu_uint(_structmodulestate *state, const char *p, const formatdef *f) ;

static int np_uint(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *nu_long(_structmodulestate *state, const char *p, const formatdef *f) ;

static int np_long(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *nu_ulong(_structmodulestate *state, const char *p, const formatdef *f) ;

static int np_ulong(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *nu_ssize_t(_structmodulestate *state, const char *p, const formatdef *f) ;

static int np_ssize_t(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *nu_size_t(_structmodulestate *state, const char *p, const formatdef *f) ;

static int np_size_t(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *nu_longlong(_structmodulestate *state, const char *p, const formatdef *f) ;

static int np_longlong(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *nu_ulonglong(_structmodulestate *state, const char *p, const formatdef *f) ;

static int np_ulonglong(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *nu_bool(_structmodulestate *state, const char *p, const formatdef *f) ;

static int np_bool(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *nu_halffloat(_structmodulestate *state, const char *p, const formatdef *f) ;

static int np_halffloat(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *nu_float(_structmodulestate *state, const char *p, const formatdef *f) ;

static int np_float(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *nu_double(_structmodulestate *state, const char *p, const formatdef *f) ;

static int np_double(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static PyObject *nu_void_p(_structmodulestate *state, const char *p, const formatdef *f) ;

static int np_void_p(_structmodulestate *state, char *p, PyObject *v, const formatdef *f) ;

static const formatdef native_table[] = {{'x', sizeof(char), 0, ((void *)0)}, {'b', sizeof(char), 0, nu_byte, np_byte}, {'B', sizeof(char), 0, nu_ubyte, np_ubyte}, {'c', sizeof(char), 0, nu_char, np_char}, {'s', sizeof(char), 0, ((void *)0)}, {'p', sizeof(char), 0, ((void *)0)}, {'h', sizeof(short), (sizeof(st_short) - sizeof(short)), nu_short, np_short}, {'H', sizeof(short), (sizeof(st_short) - sizeof(short)), nu_ushort, np_ushort}, {'i', sizeof(int), (sizeof(st_int) - sizeof(int)), nu_int, np_int}, {'I', sizeof(int), (sizeof(st_int) - sizeof(int)), nu_uint, np_uint}, {'l', sizeof(long), (sizeof(st_long) - sizeof(long)), nu_long, np_long}, {'L', sizeof(long), (sizeof(st_long) - sizeof(long)), nu_ulong, np_ulong}, {'n', sizeof(size_t), (sizeof(st_size_t) - sizeof(size_t)), nu_ssize_t, np_ssize_t}, {'N', sizeof(size_t), (sizeof(st_size_t) - sizeof(size_t)), nu_size_t, np_size_t}, {'q', sizeof(long long), (sizeof(s_long_long) - sizeof(long long)), nu_longlong, np_longlong}, {'Q', sizeof(long long), (sizeof(s_long_long) - sizeof(long long)), nu_ulonglong, np_ulonglong}, {'?', sizeof(_Bool), (sizeof(st_bool) - sizeof(_Bool)), nu_bool, np_bool}, {'e', sizeof(short), (sizeof(st_short) - sizeof(short)), nu_halffloat, np_halffloat}, {'f', sizeof(float), (sizeof(st_float) - sizeof(float)), nu_float, np_float}, {'d', sizeof(double), (sizeof(st_double) - sizeof(double)), nu_double, np_double}, {'P', sizeof(void *), (sizeof(st_void_p) - sizeof(void *)), nu_void_p, np_void_p}, {0}};
;
static int _structmodule_traverse(PyObject *module, visitproc visit, void *arg) ;

static int _structmodule_clear(PyObject *module) ;

static void _structmodule_free(void *module) ;

static const char module_doc[] = "Functions to convert between Python values and C structs.\nPython bytes objects are used to hold the data representing the C struct\nand also as format strings (explained below) to describe the layout of data\nin the C struct.\n\nThe optional first format char indicates byte order, size and alignment:\n  @: native order, size & alignment (default)\n  =: native order, std. size & alignment\n  <: little-endian, std. size & alignment\n  >: big-endian, std. size & alignment\n  !: same as >\n\nThe remaining chars indicate types of args and must match exactly;\nthese can be preceded by a decimal repeat count:\n  x: pad byte (no data); c:char; b:signed byte; B:unsigned byte;\n  ?: _Bool (requires C99; if not available, char is used instead)\n  h:short; H:unsigned short; i:int; I:unsigned int;\n  l:long; L:unsigned long; f:float; d:double; e:half-float.\nSpecial cases (preceding decimal count indicates length):\n  s:string (array of char); p: pascal string (with count byte).\nSpecial cases (only available in native format):\n  n:ssize_t; N:size_t;\n  P:an integer type that is wide enough to hold a pointer.\nSpecial case (not in native mode unless 'long long' in platform C):\n  q:long long; Q:unsigned long long\nWhitespace between formats is ignored.\n\nThe variable struct.error is an exception raised on errors.\n";
static PyObject *_clearcache(PyObject *module, PyObject *_unused_ignored) ;

static const char _clearcache__doc__[] = "_clearcache($module, /)\n--\n\nClear the internal cache.";
static PyObject *calcsize(PyObject *module, PyObject *arg) ;

static const char calcsize__doc__[] = "calcsize($module, format, /)\n--\n\nReturn size in bytes of the struct described by the format string.";
static PyObject *iter_unpack(PyObject *module, PyObject *const *args, Py_ssize_t nargs) ;

static const char iter_unpack__doc__[] = "iter_unpack($module, format, buffer, /)\n--\n\nReturn an iterator yielding tuples unpacked from the given bytes.\n\nThe bytes are unpacked according to the format string, like\na repeated invocation of unpack_from().\n\nRequires that the bytes length be a multiple of the format struct size.";
static PyObject *pack(PyObject *module, PyObject *const *args, Py_ssize_t nargs) ;

static const char pack_doc[] = "pack(format, v1, v2, ...) -> bytes\n\nReturn a bytes object containing the values v1, v2, ... packed according\nto the format string.  See help(struct) for more on format strings.";
static PyObject *pack_into(PyObject *module, PyObject *const *args, Py_ssize_t nargs) ;

static const char pack_into_doc[] = "pack_into(format, buffer, offset, v1, v2, ...)\n\nPack the values v1, v2, ... according to the format string and write\nthe packed bytes into the writable buffer buf starting at offset.  Note\nthat the offset is a required argument.  See help(struct) for more\non format strings.";
static PyObject *unpack(PyObject *module, PyObject *const *args, Py_ssize_t nargs) ;

static const char unpack__doc__[] = "unpack($module, format, buffer, /)\n--\n\nReturn a tuple containing values unpacked according to the format string.\n\nThe buffer's size in bytes must be calcsize(format).\n\nSee help(struct) for more on format strings.";
static PyObject *unpack_from(PyObject *module, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames) ;

static const char unpack_from__doc__[] = "unpack_from($module, format, /, buffer, offset=0)\n--\n\nReturn a tuple containing values unpacked according to the format string.\n\nThe buffer's size, minus offset, must be at least calcsize(format).\n\nSee help(struct) for more on format strings.";
static struct PyMethodDef module_functions[] = {{"_clearcache", (PyCFunction)_clearcache, 4, _clearcache__doc__}, {"calcsize", (PyCFunction)calcsize, 8, calcsize__doc__}, {"iter_unpack", (PyCFunction)(void (*)(void))iter_unpack, 128, iter_unpack__doc__}, {"pack", (PyCFunction)(void (*)(void))pack, 128, pack_doc}, {"pack_into", (PyCFunction)(void (*)(void))pack_into, 128, pack_into_doc}, {"unpack", (PyCFunction)(void (*)(void))unpack, 128, unpack__doc__}, {"unpack_from", (PyCFunction)(void (*)(void))unpack_from, 128 | 2, unpack_from__doc__}, {((void *)0), ((void *)0)}};
static int _structmodule_exec(PyObject *m) ;

static PyModuleDef_Slot _structmodule_slots[] = {{2, _structmodule_exec}, {0, ((void *)0)}};
static struct PyModuleDef _structmodule = {{{1, ((void *)0)}, ((void *)0), 0, ((void *)0)}, .m_name = "_struct", .m_doc = module_doc, .m_size = sizeof(_structmodulestate), .m_methods = module_functions, .m_slots = _structmodule_slots, .m_traverse = _structmodule_traverse, .m_clear = _structmodule_clear, .m_free = _structmodule_free};
;
static inline _structmodulestate *get_struct_state(PyObject *module) ;


PyObject *_PyType_GetModuleByDef(PyTypeObject *, struct PyModuleDef *);

static const formatdef *whichtable(const char **pfmt) ;

static const formatdef *getentry(_structmodulestate *state, int c, const formatdef *f) ;

static Py_ssize_t align(Py_ssize_t size, char c, const formatdef *e) ;

extern const unsigned int _Py_ctype_table[256];
;

PyObject *PyErr_NoMemory(void);


void *PyMem_Malloc(size_t size);


void PyMem_Free(void *ptr);


void *PyType_GetSlot(PyTypeObject *, int);

static inline PyObject *_Py_NewRef(PyObject *obj) ;

extern PyObject _Py_NoneStruct;
;

PyObject *PyUnicode_AsASCIIString(PyObject *unicode);


const char *_PyType_Name(PyTypeObject *);

extern PyObject *PyExc_TypeError;
;
static int prepare_s(PyStructObject *self) ;


void PyObject_GC_UnTrack(void *);


void PyObject_ClearWeakRefs(PyObject *);


PyObject *PyTuple_New(Py_ssize_t size);

static PyObject *s_unpack_internal(PyStructObject *soself, const char *startfrom, _structmodulestate *state) ;


void PyObject_GC_Del(void *);


PyObject *PyType_GetModule(struct _typeobject *);


PyObject *PyType_GenericAlloc(PyTypeObject *, Py_ssize_t);

static inline int _PyObject_TypeCheck(PyObject *ob, PyTypeObject *type) ;

extern PyTypeObject PyByteArray_Type;
;
extern char _PyByteArray_empty_string[];
;

void _PyBytesWriter_Init(_PyBytesWriter *writer);


void *_PyBytesWriter_Alloc(_PyBytesWriter *writer, Py_ssize_t size);


void _PyBytesWriter_Dealloc(_PyBytesWriter *writer);

static int s_pack_internal(PyStructObject *soself, PyObject *const *args, int offset, char *buf, _structmodulestate *state) ;


PyObject *_PyBytesWriter_Finish(_PyBytesWriter *writer, void *str);


int _PyArg_Parse_SizeT(PyObject *, const char *, ...);


Py_ssize_t PyNumber_AsSsize_t(PyObject *o, PyObject *exc);

extern PyObject *PyExc_IndexError;
;

PyObject *PyUnicode_FromStringAndSize(const char *u, Py_ssize_t size);


PyObject *PyDict_New(void);


PyObject *PyDict_GetItemWithError(PyObject *mp, PyObject *key);

static inline PyObject *PyObject_CallOneArg(PyObject *func, PyObject *arg) ;


void PyDict_Clear(PyObject *mp);


int PyDict_SetItem(PyObject *mp, PyObject *key, PyObject *item);


void PyErr_Clear(void);

static PyObject *s_pack(PyObject *self, PyObject *const *args, Py_ssize_t nargs) ;

static PyObject *s_pack_into(PyObject *self, PyObject *const *args, Py_ssize_t nargs) ;

static PyObject *Struct_iter_unpack(PyStructObject *self, PyObject *buffer) ;


PyObject *PyType_FromModuleAndSpec(PyObject *, PyType_Spec *, PyObject *);

static const char s__doc__[] = "Struct(fmt) --> compiled struct object\n\n";
static PyObject *Struct_unpack(PyStructObject *self, PyObject *arg) ;

static PyObject *Struct_unpack_from(PyStructObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames) ;

static PyObject *s_sizeof(PyStructObject *self, void *unused) ;

static const char Struct_iter_unpack__doc__[] = "iter_unpack($self, buffer, /)\n--\n\nReturn an iterator yielding tuples.\n\nTuples are unpacked from the given bytes source, like a repeated\ninvocation of unpack_from().\n\nRequires that the bytes length be a multiple of the struct size.";
static const char s_pack__doc__[] = "S.pack(v1, v2, ...) -> bytes\n\nReturn a bytes object containing values v1, v2, ... packed according\nto the format string S.format.  See help(struct) for more on format\nstrings.";
static const char s_pack_into__doc__[] = "S.pack_into(buffer, offset, v1, v2, ...)\n\nPack the values v1, v2, ... according to the format string S.format\nand write the packed bytes into the writable buffer buf starting at\noffset.  Note that the offset is a required argument.  See\nhelp(struct) for more on format strings.";
static const char Struct_unpack__doc__[] = "unpack($self, buffer, /)\n--\n\nReturn a tuple containing unpacked values.\n\nUnpack according to the format string Struct.format. The buffer's size\nin bytes must be Struct.size.\n\nSee help(struct) for more on format strings.";
static const char Struct_unpack_from__doc__[] = "unpack_from($self, /, buffer, offset=0)\n--\n\nReturn a tuple containing unpacked values.\n\nValues are unpacked according to the format string Struct.format.\n\nThe buffer's size in bytes, starting at position offset, must be\nat least Struct.size.\n\nSee help(struct) for more on format strings.";
static const char s_sizeof__doc__[] = "S.__sizeof__() -> size of S in memory, in bytes";
static struct PyMethodDef s_methods[] = {{"iter_unpack", (PyCFunction)Struct_iter_unpack, 8, Struct_iter_unpack__doc__}, {"pack", (PyCFunction)(void (*)(void))s_pack, 128, s_pack__doc__}, {"pack_into", (PyCFunction)(void (*)(void))s_pack_into, 128, s_pack_into__doc__}, {"unpack", (PyCFunction)Struct_unpack, 8, Struct_unpack__doc__}, {"unpack_from", (PyCFunction)(void (*)(void))Struct_unpack_from, 128 | 2, Struct_unpack_from__doc__}, {"__sizeof__", (PyCFunction)s_sizeof, 4, s_sizeof__doc__}, {((void *)0), ((void *)0)}};
;
static PyMemberDef s_members[] = {{"__weaklistoffset__", 19, __builtin_offsetof(PyStructObject, weakreflist), 1}, {((void *)0)}};
;
static PyObject *s_get_format(PyStructObject *self, void *unused) ;

static PyObject *s_get_size(PyStructObject *self, void *unused) ;

static PyGetSetDef s_getsetlist[] = {{"format", (getter)s_get_format, (setter)((void *)0), "struct format string", ((void *)0)}, {"size", (getter)s_get_size, (setter)((void *)0), "struct size in bytes", ((void *)0)}, {((void *)0)}};
;
static void s_dealloc(PyStructObject *s) ;


PyObject *PyObject_GenericGetAttr(PyObject *, PyObject *);


int PyObject_GenericSetAttr(PyObject *, PyObject *, PyObject *);

static int s_traverse(PyStructObject *s, visitproc visit, void *arg) ;

static int s_clear(PyStructObject *s) ;

static int Struct___init__(PyObject *self, PyObject *args, PyObject *kwargs) ;

static PyObject *s_new(PyTypeObject *type, PyObject *args, PyObject *kwds) ;

static PyType_Slot PyStructType_slots[] = {{52, s_dealloc}, {58, PyObject_GenericGetAttr}, {69, PyObject_GenericSetAttr}, {56, (void *)s__doc__}, {71, s_traverse}, {51, s_clear}, {64, s_methods}, {72, s_members}, {73, s_getsetlist}, {60, Struct___init__}, {47, PyType_GenericAlloc}, {65, s_new}, {74, PyObject_GC_Del}, {0, 0}};
static PyType_Spec PyStructType_spec = {"_struct.Struct", sizeof(PyStructObject), 0, ((0 | 0) | (1UL << 14) | (1UL << 10) | (1UL << 8)), PyStructType_slots};
;

int PyModule_AddType(PyObject *module, PyTypeObject *type);

static PyObject *unpackiter_len(unpackiterobject *self, PyObject *_unused_ignored) ;

static PyMethodDef unpackiter_methods[] = {{"__length_hint__", (PyCFunction)unpackiter_len, 4, ((void *)0)}, {((void *)0), ((void *)0)}};
;
static void unpackiter_dealloc(unpackiterobject *self) ;

static int unpackiter_traverse(unpackiterobject *self, visitproc visit, void *arg) ;


PyObject *PyObject_SelfIter(PyObject *);

static PyObject *unpackiter_iternext(unpackiterobject *self) ;

PyObject *unpackiter_new(PyTypeObject *type, PyObject *args, PyObject *kwds) ;

static PyType_Slot unpackiter_type_slots[] = {{52, unpackiter_dealloc}, {58, PyObject_GenericGetAttr}, {71, unpackiter_traverse}, {62, PyObject_SelfIter}, {63, unpackiter_iternext}, {64, unpackiter_methods}, {65, unpackiter_new}, {0, 0}};
static PyType_Spec unpackiter_type_spec = {"_struct.unpack_iterator", sizeof(unpackiterobject), 0, ((0 | 0) | (1UL << 14) | (1UL << 8)), unpackiter_type_slots};
;

PyObject *PyErr_NewException(const char *name, PyObject *base, PyObject *dict);


int PyModule_AddObjectRef(PyObject *mod, const char *name, PyObject *value);

#endif