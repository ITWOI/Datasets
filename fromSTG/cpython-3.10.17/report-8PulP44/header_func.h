#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 

void _Py_Dealloc(PyObject *);

static inline void _Py_DECREF(PyObject *op) ;

static inline int PyType_HasFeature(PyTypeObject *type, unsigned long feature) ;

static inline vectorcallfunc PyVectorcall_Function(PyObject *callable) ;


PyObject *_PyObject_MakeTpCall(PyThreadState *tstate, PyObject *callable, PyObject *const *args, Py_ssize_t nargs, PyObject *keywords);

static inline Py_ssize_t PyVectorcall_NARGS(size_t n) ;


PyObject *_Py_CheckFunctionResult(PyThreadState *tstate, PyObject *callable, PyObject *result, const char *where);


PyThreadState *PyThreadState_Get(void);

static inline PyObject *_PyObject_VectorcallTstate(PyThreadState *tstate, PyObject *callable, PyObject *const *args, size_t nargsf, PyObject *kwnames) ;

static inline PyThreadState *_PyRuntimeState_GetThreadState(_PyRuntimeState *runtime) ;

extern _PyRuntimeState _PyRuntime;
;
static inline PyThreadState *_PyThreadState_GET(void) ;

static inline void _Py_SET_TYPE(PyObject *ob, PyTypeObject *type) ;

static inline int _PyType_HasFeature(PyTypeObject *type, unsigned long feature) ;

static inline void _Py_INCREF(PyObject *op) ;

static inline PyInterpreterState *_PyInterpreterState_GET(void) ;

static struct _Py_unicode_state *get_unicode_state(void) ;

static inline PyObject *unicode_get_empty(void) ;


const PyConfig *_PyInterpreterState_GetConfig(PyInterpreterState *interp);


PyObject *_PyCodec_Lookup(const char *encoding);


PyObject *PyCodec_LookupError(const char *name);

static inline PyObject *unicode_new_empty(void) ;

static PyObject *get_latin1_char(unsigned char ch);

int _PyUnicode_Ready(PyObject *unicode);

static PyObject *unicode_result_ready(PyObject *unicode) ;

static PyObject *unicode_result_wchar(PyObject *unicode) ;

static inline Py_ssize_t ucs1lib_find_char(const Py_UCS1 *s, Py_ssize_t n, Py_UCS1 ch) ;

static inline Py_ssize_t ucs1lib_rfind_char(const Py_UCS1 *s, Py_ssize_t n, Py_UCS1 ch) ;

static inline Py_ssize_t ucs2lib_find_char(const Py_UCS2 *s, Py_ssize_t n, Py_UCS2 ch) ;

static inline Py_ssize_t ucs2lib_rfind_char(const Py_UCS2 *s, Py_ssize_t n, Py_UCS2 ch) ;

static inline Py_ssize_t ucs4lib_find_char(const Py_UCS4 *s, Py_ssize_t n, Py_UCS4 ch) ;

static inline Py_ssize_t ucs4lib_rfind_char(const Py_UCS4 *s, Py_ssize_t n, Py_UCS4 ch) ;


PyObject *PyErr_NoMemory(void);


void PyObject_Free(void *ptr);


void *PyObject_Realloc(void *ptr, size_t new_size);


void _Py_NewReference(PyObject *op);


void PyErr_SetString(PyObject *exception, const char *string);


void *PyObject_Malloc(size_t size);

static inline void _PyObject_Init(PyObject *op, PyTypeObject *typeobj) ;

static void unicode_dealloc(PyObject *unicode) ;

static PyObject *unicode_repr(PyObject *unicode) ;

static Py_hash_t unicode_hash(PyObject *self) ;

static PyObject *unicode_str(PyObject *self) ;


PyObject *PyObject_GenericGetAttr(PyObject *, PyObject *);

PyObject *PyUnicode_RichCompare(PyObject *left, PyObject *right, int op) ;

static PyObject *unicode_iter(PyObject *seq);

static PyObject *unicode_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) ;

extern PyTypeObject PyType_Type;
static PyObject *unicode_mod(PyObject *v, PyObject *w) ;

static PyNumberMethods unicode_as_number = {0, 0, 0, unicode_mod};
static Py_ssize_t unicode_length(PyObject *self) ;

PyObject *PyUnicode_Concat(PyObject *left, PyObject *right) ;

static PyObject *unicode_repeat(PyObject *str, Py_ssize_t len) ;

static PyObject *unicode_getitem(PyObject *self, Py_ssize_t index) ;

int PyUnicode_Contains(PyObject *str, PyObject *substr) ;

static PySequenceMethods unicode_as_sequence = {(lenfunc)unicode_length, PyUnicode_Concat, (ssizeargfunc)unicode_repeat, (ssizeargfunc)unicode_getitem, 0, 0, 0, PyUnicode_Contains};
static PyObject *unicode_subscript(PyObject *self, PyObject *item) ;

static PyMappingMethods unicode_as_mapping = {(lenfunc)unicode_length, (binaryfunc)unicode_subscript, (objobjargproc)0};
static const char unicode_doc[] = "str(object='') -> str\nstr(bytes_or_buffer[, encoding[, errors]]) -> str\n\nCreate a new string object from the given object. If encoding or\nerrors is specified, then the object must expose a data buffer\nthat will be decoded using the given encoding and error handler.\nOtherwise, returns the result of object.__str__() (if defined)\nor repr(object).\nencoding defaults to sys.getdefaultencoding().\nerrors defaults to 'strict'.";
static PyObject *unicode_encode(PyObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames) ;

static const char unicode_encode__doc__[] = "encode($self, /, encoding='utf-8', errors='strict')\n--\n\nEncode the string using the codec registered for encoding.\n\n  encoding\n    The encoding in which to encode the string.\n  errors\n    The error handling scheme to use for encoding errors.\n    The default is 'strict' meaning that encoding errors raise a\n    UnicodeEncodeError.  Other possible values are 'ignore', 'replace' and\n    'xmlcharrefreplace' as well as any other name registered with\n    codecs.register_error that can handle UnicodeEncodeErrors.";
static PyObject *unicode_replace(PyObject *self, PyObject *const *args, Py_ssize_t nargs) ;

static const char unicode_replace__doc__[] = "replace($self, old, new, count=-1, /)\n--\n\nReturn a copy with all occurrences of substring old replaced by new.\n\n  count\n    Maximum number of occurrences to replace.\n    -1 (the default value) means replace all occurrences.\n\nIf the optional argument count is given, only the first count occurrences are\nreplaced.";
static PyObject *unicode_split(PyObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames) ;

static const char unicode_split__doc__[] = "split($self, /, sep=None, maxsplit=-1)\n--\n\nReturn a list of the substrings in the string, using sep as the separator string.\n\n  sep\n    The separator used to split the string.\n\n    When set to None (the default value), will split on any whitespace\n    character (including \\\\n \\\\r \\\\t \\\\f and spaces) and will discard\n    empty strings from the result.\n  maxsplit\n    Maximum number of splits (starting from the left).\n    -1 (the default value) means no limit.\n\nNote, str.split() is mainly useful for data that has been intentionally\ndelimited.  With natural text that includes punctuation, consider using\nthe regular expression module.";
static PyObject *unicode_rsplit(PyObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames) ;

static const char unicode_rsplit__doc__[] = "rsplit($self, /, sep=None, maxsplit=-1)\n--\n\nReturn a list of the substrings in the string, using sep as the separator string.\n\n  sep\n    The separator used to split the string.\n\n    When set to None (the default value), will split on any whitespace\n    character (including \\\\n \\\\r \\\\t \\\\f and spaces) and will discard\n    empty strings from the result.\n  maxsplit\n    Maximum number of splits (starting from the left).\n    -1 (the default value) means no limit.\n\nSplitting starts at the end of the string and works to the front.";
static PyObject *unicode_join(PyObject *self, PyObject *iterable) ;

static const char unicode_join__doc__[] = "join($self, iterable, /)\n--\n\nConcatenate any number of strings.\n\nThe string whose method is called is inserted in between each given string.\nThe result is returned as a new string.\n\nExample: '.'.join(['ab', 'pq', 'rs']) -> 'ab.pq.rs'";
static PyObject *unicode_capitalize(PyObject *self, PyObject *_unused_ignored) ;

static const char unicode_capitalize__doc__[] = "capitalize($self, /)\n--\n\nReturn a capitalized version of the string.\n\nMore specifically, make the first character have upper case and the rest lower\ncase.";
static PyObject *unicode_casefold(PyObject *self, PyObject *_unused_ignored) ;

static const char unicode_casefold__doc__[] = "casefold($self, /)\n--\n\nReturn a version of the string suitable for caseless comparisons.";
static PyObject *unicode_title(PyObject *self, PyObject *_unused_ignored) ;

static const char unicode_title__doc__[] = "title($self, /)\n--\n\nReturn a version of the string where each word is titlecased.\n\nMore specifically, words start with uppercased characters and all remaining\ncased characters have lower case.";
static PyObject *unicode_center(PyObject *self, PyObject *const *args, Py_ssize_t nargs) ;

static const char unicode_center__doc__[] = "center($self, width, fillchar=' ', /)\n--\n\nReturn a centered string of length width.\n\nPadding is done using the specified fill character (default is a space).";
static PyObject *unicode_count(PyObject *self, PyObject *args) ;

static const char count__doc__[] = "S.count(sub[, start[, end]]) -> int\n\nReturn the number of non-overlapping occurrences of substring sub in\nstring S[start:end].  Optional arguments start and end are\ninterpreted as in slice notation.";
static PyObject *unicode_expandtabs(PyObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames) ;

static const char unicode_expandtabs__doc__[] = "expandtabs($self, /, tabsize=8)\n--\n\nReturn a copy where all tab characters are expanded using spaces.\n\nIf tabsize is not given, a tab size of 8 characters is assumed.";
static PyObject *unicode_find(PyObject *self, PyObject *args) ;

static const char find__doc__[] = "S.find(sub[, start[, end]]) -> int\n\nReturn the lowest index in S where substring sub is found,\nsuch that sub is contained within S[start:end].  Optional\narguments start and end are interpreted as in slice notation.\n\nReturn -1 on failure.";
static PyObject *unicode_partition(PyObject *self, PyObject *sep) ;

static const char unicode_partition__doc__[] = "partition($self, sep, /)\n--\n\nPartition the string into three parts using the given separator.\n\nThis will search for the separator in the string.  If the separator is found,\nreturns a 3-tuple containing the part before the separator, the separator\nitself, and the part after it.\n\nIf the separator is not found, returns a 3-tuple containing the original string\nand two empty strings.";
static PyObject *unicode_index(PyObject *self, PyObject *args) ;

static const char index__doc__[] = "S.index(sub[, start[, end]]) -> int\n\nReturn the lowest index in S where substring sub is found,\nsuch that sub is contained within S[start:end].  Optional\narguments start and end are interpreted as in slice notation.\n\nRaises ValueError when the substring is not found.";
static PyObject *unicode_ljust(PyObject *self, PyObject *const *args, Py_ssize_t nargs) ;

static const char unicode_ljust__doc__[] = "ljust($self, width, fillchar=' ', /)\n--\n\nReturn a left-justified string of length width.\n\nPadding is done using the specified fill character (default is a space).";
static PyObject *unicode_lower(PyObject *self, PyObject *_unused_ignored) ;

static const char unicode_lower__doc__[] = "lower($self, /)\n--\n\nReturn a copy of the string converted to lowercase.";
static PyObject *unicode_lstrip(PyObject *self, PyObject *const *args, Py_ssize_t nargs) ;

static const char unicode_lstrip__doc__[] = "lstrip($self, chars=None, /)\n--\n\nReturn a copy of the string with leading whitespace removed.\n\nIf chars is given and not None, remove characters in chars instead.";
static PyObject *unicode_rfind(PyObject *self, PyObject *args) ;

static const char rfind__doc__[] = "S.rfind(sub[, start[, end]]) -> int\n\nReturn the highest index in S where substring sub is found,\nsuch that sub is contained within S[start:end].  Optional\narguments start and end are interpreted as in slice notation.\n\nReturn -1 on failure.";
static PyObject *unicode_rindex(PyObject *self, PyObject *args) ;

static const char rindex__doc__[] = "S.rindex(sub[, start[, end]]) -> int\n\nReturn the highest index in S where substring sub is found,\nsuch that sub is contained within S[start:end].  Optional\narguments start and end are interpreted as in slice notation.\n\nRaises ValueError when the substring is not found.";
static PyObject *unicode_rjust(PyObject *self, PyObject *const *args, Py_ssize_t nargs) ;

static const char unicode_rjust__doc__[] = "rjust($self, width, fillchar=' ', /)\n--\n\nReturn a right-justified string of length width.\n\nPadding is done using the specified fill character (default is a space).";
static PyObject *unicode_rstrip(PyObject *self, PyObject *const *args, Py_ssize_t nargs) ;

static const char unicode_rstrip__doc__[] = "rstrip($self, chars=None, /)\n--\n\nReturn a copy of the string with trailing whitespace removed.\n\nIf chars is given and not None, remove characters in chars instead.";
static PyObject *unicode_rpartition(PyObject *self, PyObject *sep) ;

static const char unicode_rpartition__doc__[] = "rpartition($self, sep, /)\n--\n\nPartition the string into three parts using the given separator.\n\nThis will search for the separator in the string, starting at the end. If\nthe separator is found, returns a 3-tuple containing the part before the\nseparator, the separator itself, and the part after it.\n\nIf the separator is not found, returns a 3-tuple containing two empty strings\nand the original string.";
static PyObject *unicode_splitlines(PyObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames) ;

static const char unicode_splitlines__doc__[] = "splitlines($self, /, keepends=False)\n--\n\nReturn a list of the lines in the string, breaking at line boundaries.\n\nLine breaks are not included in the resulting list unless keepends is given and\ntrue.";
static PyObject *unicode_strip(PyObject *self, PyObject *const *args, Py_ssize_t nargs) ;

static const char unicode_strip__doc__[] = "strip($self, chars=None, /)\n--\n\nReturn a copy of the string with leading and trailing whitespace removed.\n\nIf chars is given and not None, remove characters in chars instead.";
static PyObject *unicode_swapcase(PyObject *self, PyObject *_unused_ignored) ;

static const char unicode_swapcase__doc__[] = "swapcase($self, /)\n--\n\nConvert uppercase characters to lowercase and lowercase characters to uppercase.";
static PyObject *unicode_translate(PyObject *self, PyObject *table) ;

static const char unicode_translate__doc__[] = "translate($self, table, /)\n--\n\nReplace each character in the string using the given translation table.\n\n  table\n    Translation table, which must be a mapping of Unicode ordinals to\n    Unicode ordinals, strings, or None.\n\nThe table must implement lookup/indexing via __getitem__, for instance a\ndictionary or list.  If this operation raises LookupError, the character is\nleft untouched.  Characters mapped to None are deleted.";
static PyObject *unicode_upper(PyObject *self, PyObject *_unused_ignored) ;

static const char unicode_upper__doc__[] = "upper($self, /)\n--\n\nReturn a copy of the string converted to uppercase.";
static PyObject *unicode_startswith(PyObject *self, PyObject *args) ;

static const char startswith__doc__[] = "S.startswith(prefix[, start[, end]]) -> bool\n\nReturn True if S starts with the specified prefix, False otherwise.\nWith optional start, test S beginning at that position.\nWith optional end, stop comparing S at that position.\nprefix can also be a tuple of strings to try.";
static PyObject *unicode_endswith(PyObject *self, PyObject *args) ;

static const char endswith__doc__[] = "S.endswith(suffix[, start[, end]]) -> bool\n\nReturn True if S ends with the specified suffix, False otherwise.\nWith optional start, test S beginning at that position.\nWith optional end, stop comparing S at that position.\nsuffix can also be a tuple of strings to try.";
static PyObject *unicode_removeprefix(PyObject *self, PyObject *arg) ;

static const char unicode_removeprefix__doc__[] = "removeprefix($self, prefix, /)\n--\n\nReturn a str with the given prefix string removed if present.\n\nIf the string starts with the prefix string, return string[len(prefix):].\nOtherwise, return a copy of the original string.";
static PyObject *unicode_removesuffix(PyObject *self, PyObject *arg) ;

static const char unicode_removesuffix__doc__[] = "removesuffix($self, suffix, /)\n--\n\nReturn a str with the given suffix string removed if present.\n\nIf the string ends with the suffix string and that suffix is not empty,\nreturn string[:-len(suffix)]. Otherwise, return a copy of the original\nstring.";
static PyObject *unicode_isascii(PyObject *self, PyObject *_unused_ignored) ;

static const char unicode_isascii__doc__[] = "isascii($self, /)\n--\n\nReturn True if all characters in the string are ASCII, False otherwise.\n\nASCII characters have code points in the range U+0000-U+007F.\nEmpty string is ASCII too.";
static PyObject *unicode_islower(PyObject *self, PyObject *_unused_ignored) ;

static const char unicode_islower__doc__[] = "islower($self, /)\n--\n\nReturn True if the string is a lowercase string, False otherwise.\n\nA string is lowercase if all cased characters in the string are lowercase and\nthere is at least one cased character in the string.";
static PyObject *unicode_isupper(PyObject *self, PyObject *_unused_ignored) ;

static const char unicode_isupper__doc__[] = "isupper($self, /)\n--\n\nReturn True if the string is an uppercase string, False otherwise.\n\nA string is uppercase if all cased characters in the string are uppercase and\nthere is at least one cased character in the string.";
static PyObject *unicode_istitle(PyObject *self, PyObject *_unused_ignored) ;

static const char unicode_istitle__doc__[] = "istitle($self, /)\n--\n\nReturn True if the string is a title-cased string, False otherwise.\n\nIn a title-cased string, upper- and title-case characters may only\nfollow uncased characters and lowercase characters only cased ones.";
static PyObject *unicode_isspace(PyObject *self, PyObject *_unused_ignored) ;

static const char unicode_isspace__doc__[] = "isspace($self, /)\n--\n\nReturn True if the string is a whitespace string, False otherwise.\n\nA string is whitespace if all characters in the string are whitespace and there\nis at least one character in the string.";
static PyObject *unicode_isdecimal(PyObject *self, PyObject *_unused_ignored) ;

static const char unicode_isdecimal__doc__[] = "isdecimal($self, /)\n--\n\nReturn True if the string is a decimal string, False otherwise.\n\nA string is a decimal string if all characters in the string are decimal and\nthere is at least one character in the string.";
static PyObject *unicode_isdigit(PyObject *self, PyObject *_unused_ignored) ;

static const char unicode_isdigit__doc__[] = "isdigit($self, /)\n--\n\nReturn True if the string is a digit string, False otherwise.\n\nA string is a digit string if all characters in the string are digits and there\nis at least one character in the string.";
static PyObject *unicode_isnumeric(PyObject *self, PyObject *_unused_ignored) ;

static const char unicode_isnumeric__doc__[] = "isnumeric($self, /)\n--\n\nReturn True if the string is a numeric string, False otherwise.\n\nA string is numeric if all characters in the string are numeric and there is at\nleast one character in the string.";
static PyObject *unicode_isalpha(PyObject *self, PyObject *_unused_ignored) ;

static const char unicode_isalpha__doc__[] = "isalpha($self, /)\n--\n\nReturn True if the string is an alphabetic string, False otherwise.\n\nA string is alphabetic if all characters in the string are alphabetic and there\nis at least one character in the string.";
static PyObject *unicode_isalnum(PyObject *self, PyObject *_unused_ignored) ;

static const char unicode_isalnum__doc__[] = "isalnum($self, /)\n--\n\nReturn True if the string is an alpha-numeric string, False otherwise.\n\nA string is alpha-numeric if all characters in the string are alpha-numeric and\nthere is at least one character in the string.";
static PyObject *unicode_isidentifier(PyObject *self, PyObject *_unused_ignored) ;

static const char unicode_isidentifier__doc__[] = "isidentifier($self, /)\n--\n\nReturn True if the string is a valid Python identifier, False otherwise.\n\nCall keyword.iskeyword(s) to test whether string s is a reserved identifier,\nsuch as \"def\" or \"class\".";
static PyObject *unicode_isprintable(PyObject *self, PyObject *_unused_ignored) ;

static const char unicode_isprintable__doc__[] = "isprintable($self, /)\n--\n\nReturn True if the string is printable, False otherwise.\n\nA string is printable if all of its characters are considered printable in\nrepr() or if it is empty.";
static PyObject *unicode_zfill(PyObject *self, PyObject *arg) ;

static const char unicode_zfill__doc__[] = "zfill($self, width, /)\n--\n\nPad a numeric string with zeros on the left, to fill a field of the given width.\n\nThe string is never truncated.";
static PyObject *do_string_format(PyObject *self, PyObject *args, PyObject *kwargs) ;

static const char format__doc__[] = "S.format(*args, **kwargs) -> str\n\nReturn a formatted version of S, using substitutions from args and kwargs.\nThe substitutions are identified by braces ('{' and '}').";
static PyObject *do_string_format_map(PyObject *self, PyObject *obj) ;

static const char format_map__doc__[] = "S.format_map(mapping) -> str\n\nReturn a formatted version of S, using substitutions from mapping.\nThe substitutions are identified by braces ('{' and '}').";
static PyObject *unicode___format__(PyObject *self, PyObject *arg) ;

static const char unicode___format____doc__[] = "__format__($self, format_spec, /)\n--\n\nReturn a formatted version of the string as described by format_spec.";
static PyObject *unicode_maketrans(void *null, PyObject *const *args, Py_ssize_t nargs) ;

static const char unicode_maketrans__doc__[] = "maketrans(x, y=<unrepresentable>, z=<unrepresentable>, /)\n--\n\nReturn a translation table usable for str.translate().\n\nIf there is only one argument, it must be a dictionary mapping Unicode\nordinals (integers) or characters to Unicode ordinals, strings or None.\nCharacter keys will be then converted to ordinals.\nIf there are two arguments, they must be strings of equal length, and\nin the resulting dictionary, each character in x will be mapped to the\ncharacter at the same position in y. If there is a third argument, it\nmust be a string, whose characters will be mapped to None in the result.";
static PyObject *unicode_sizeof(PyObject *self, PyObject *_unused_ignored) ;

static const char unicode_sizeof__doc__[] = "__sizeof__($self, /)\n--\n\nReturn the size of the string in memory, in bytes.";
static PyObject *unicode_getnewargs(PyObject *v, PyObject *_unused_ignored) ;

static PyMethodDef unicode_methods[] = {{"encode", (PyCFunction)(void (*)(void))unicode_encode, 128 | 2, unicode_encode__doc__}, {"replace", (PyCFunction)(void (*)(void))unicode_replace, 128, unicode_replace__doc__}, {"split", (PyCFunction)(void (*)(void))unicode_split, 128 | 2, unicode_split__doc__}, {"rsplit", (PyCFunction)(void (*)(void))unicode_rsplit, 128 | 2, unicode_rsplit__doc__}, {"join", (PyCFunction)unicode_join, 8, unicode_join__doc__}, {"capitalize", (PyCFunction)unicode_capitalize, 4, unicode_capitalize__doc__}, {"casefold", (PyCFunction)unicode_casefold, 4, unicode_casefold__doc__}, {"title", (PyCFunction)unicode_title, 4, unicode_title__doc__}, {"center", (PyCFunction)(void (*)(void))unicode_center, 128, unicode_center__doc__}, {"count", (PyCFunction)unicode_count, 1, count__doc__}, {"expandtabs", (PyCFunction)(void (*)(void))unicode_expandtabs, 128 | 2, unicode_expandtabs__doc__}, {"find", (PyCFunction)unicode_find, 1, find__doc__}, {"partition", (PyCFunction)unicode_partition, 8, unicode_partition__doc__}, {"index", (PyCFunction)unicode_index, 1, index__doc__}, {"ljust", (PyCFunction)(void (*)(void))unicode_ljust, 128, unicode_ljust__doc__}, {"lower", (PyCFunction)unicode_lower, 4, unicode_lower__doc__}, {"lstrip", (PyCFunction)(void (*)(void))unicode_lstrip, 128, unicode_lstrip__doc__}, {"rfind", (PyCFunction)unicode_rfind, 1, rfind__doc__}, {"rindex", (PyCFunction)unicode_rindex, 1, rindex__doc__}, {"rjust", (PyCFunction)(void (*)(void))unicode_rjust, 128, unicode_rjust__doc__}, {"rstrip", (PyCFunction)(void (*)(void))unicode_rstrip, 128, unicode_rstrip__doc__}, {"rpartition", (PyCFunction)unicode_rpartition, 8, unicode_rpartition__doc__}, {"splitlines", (PyCFunction)(void (*)(void))unicode_splitlines, 128 | 2, unicode_splitlines__doc__}, {"strip", (PyCFunction)(void (*)(void))unicode_strip, 128, unicode_strip__doc__}, {"swapcase", (PyCFunction)unicode_swapcase, 4, unicode_swapcase__doc__}, {"translate", (PyCFunction)unicode_translate, 8, unicode_translate__doc__}, {"upper", (PyCFunction)unicode_upper, 4, unicode_upper__doc__}, {"startswith", (PyCFunction)unicode_startswith, 1, startswith__doc__}, {"endswith", (PyCFunction)unicode_endswith, 1, endswith__doc__}, {"removeprefix", (PyCFunction)unicode_removeprefix, 8, unicode_removeprefix__doc__}, {"removesuffix", (PyCFunction)unicode_removesuffix, 8, unicode_removesuffix__doc__}, {"isascii", (PyCFunction)unicode_isascii, 4, unicode_isascii__doc__}, {"islower", (PyCFunction)unicode_islower, 4, unicode_islower__doc__}, {"isupper", (PyCFunction)unicode_isupper, 4, unicode_isupper__doc__}, {"istitle", (PyCFunction)unicode_istitle, 4, unicode_istitle__doc__}, {"isspace", (PyCFunction)unicode_isspace, 4, unicode_isspace__doc__}, {"isdecimal", (PyCFunction)unicode_isdecimal, 4, unicode_isdecimal__doc__}, {"isdigit", (PyCFunction)unicode_isdigit, 4, unicode_isdigit__doc__}, {"isnumeric", (PyCFunction)unicode_isnumeric, 4, unicode_isnumeric__doc__}, {"isalpha", (PyCFunction)unicode_isalpha, 4, unicode_isalpha__doc__}, {"isalnum", (PyCFunction)unicode_isalnum, 4, unicode_isalnum__doc__}, {"isidentifier", (PyCFunction)unicode_isidentifier, 4, unicode_isidentifier__doc__}, {"isprintable", (PyCFunction)unicode_isprintable, 4, unicode_isprintable__doc__}, {"zfill", (PyCFunction)unicode_zfill, 8, unicode_zfill__doc__}, {"format", (PyCFunction)(void (*)(void))do_string_format, 1 | 2, format__doc__}, {"format_map", (PyCFunction)do_string_format_map, 8, format_map__doc__}, {"__format__", (PyCFunction)unicode___format__, 8, unicode___format____doc__}, {"maketrans", (PyCFunction)(void (*)(void))unicode_maketrans, 128 | 32, unicode_maketrans__doc__}, {"__sizeof__", (PyCFunction)unicode_sizeof, 4, unicode_sizeof__doc__}, {"__getnewargs__", unicode_getnewargs, 4}, {((void *)0), ((void *)0)}};
extern PyTypeObject PyBaseObject_Type;
PyTypeObject PyUnicode_Type = {{{1, &PyType_Type}, 0}, "str", sizeof(PyUnicodeObject), 0, (destructor)unicode_dealloc, 0, 0, 0, 0, unicode_repr, &unicode_as_number, &unicode_as_sequence, &unicode_as_mapping, (hashfunc)unicode_hash, 0, (reprfunc)unicode_str, PyObject_GenericGetAttr, 0, 0, (0 | 0) | (1UL << 10) | (1UL << 28) | (1UL << 22), unicode_doc, 0, 0, PyUnicode_RichCompare, 0, unicode_iter, 0, unicode_methods, 0, 0, &PyBaseObject_Type, 0, 0, 0, 0, 0, 0, unicode_new, PyObject_Free};
;
static inline Py_UCS4 ucs1lib_find_max_char(const Py_UCS1 *begin, const Py_UCS1 *end) ;

static int _copy_characters(PyObject *to, Py_ssize_t to_start, PyObject *from, Py_ssize_t from_start, Py_ssize_t how_many, int check_maxchar) ;


PyObject *PyErr_Format(PyObject *exception, const char *format, ...);

static int find_maxchar_surrogates(const wchar_t *begin, const wchar_t *end, Py_UCS4 *maxchar, Py_ssize_t *num_surrogates) ;

PyObject *PyUnicode_New(Py_ssize_t size, Py_UCS4 maxchar) ;


void _PyErr_BadInternalCall(const char *filename, int lineno);

static PyObject *unicode_result(PyObject *unicode) ;

extern const unsigned int _Py_ctype_table[256];
;
extern const unsigned char _Py_ctype_tolower[256];
;
static inline int unicode_check_encoding_errors(const char *encoding, const char *errors) ;

PyObject *PyUnicode_DecodeUTF8Stateful(const char *string, Py_ssize_t length, const char *errors, Py_ssize_t *consumed);

int _Py_normalize_encoding(const char *encoding, char *lower, size_t lower_len) ;

PyObject *PyUnicode_DecodeUTF16(const char *string, Py_ssize_t length, const char *errors, int *byteorder);

PyObject *PyUnicode_DecodeUTF32(const char *string, Py_ssize_t length, const char *errors, int *byteorder);

PyObject *PyUnicode_DecodeASCII(const char *string, Py_ssize_t length, const char *errors);

PyObject *PyUnicode_DecodeLatin1(const char *string, Py_ssize_t length, const char *errors);


int PyBuffer_FillInfo(Py_buffer *view, PyObject *o, void *buf, Py_ssize_t len, int readonly, int flags);


PyObject *PyMemoryView_FromBuffer(Py_buffer *info);


PyObject *_PyCodec_DecodeText(PyObject *object, const char *encoding, const char *errors);

static inline void _Py_XDECREF(PyObject *op) ;


int _Py_DecodeLocaleEx(const char *arg, wchar_t **wstr, size_t *wlen, const char **reason, int current_locale, _Py_error_handler errors);


PyObject *_PyObject_CallFunction_SizeT(PyObject *callable, const char *format, ...);


PyObject *PyCodec_StrictErrors(PyObject *exc);

extern PyObject *PyExc_UnicodeDecodeError;
;
PyObject *PyUnicode_FromWideChar(const wchar_t *u, Py_ssize_t size) ;

static PyObject *unicode_decode_utf8(const char *s, Py_ssize_t size, _Py_error_handler error_handler, const char *errors, Py_ssize_t *consumed);

PyObject *PyUnicode_Decode(const char *s, Py_ssize_t size, const char *encoding, const char *errors) ;

static PyObject *unicode_decode_locale(const char *str, Py_ssize_t len, _Py_error_handler errors, int current_locale) ;

static _Py_error_handler get_error_handler_wide(const wchar_t *errors) ;


int PyObject_CheckBuffer(PyObject *obj);


PyObject *PyOS_FSPath(PyObject *path);


int PyErr_WarnFormat(PyObject *category, Py_ssize_t stack_level, const char *format, ...);


PyObject *PyBytes_FromObject(PyObject *);

PyObject *PyUnicode_DecodeFSDefaultAndSize(const char *s, Py_ssize_t size) ;

extern PyObject *PyExc_DeprecationWarning;
;
static inline Py_ssize_t findchar(const void *s, int kind, Py_ssize_t size, Py_UCS4 ch, int direction) ;


PyObject *PyUnicodeDecodeError_Create(const char *encoding, const char *object, Py_ssize_t length, Py_ssize_t start, Py_ssize_t end, const char *reason);


int PyUnicodeDecodeError_SetStart(PyObject *, Py_ssize_t);


int PyUnicodeDecodeError_SetEnd(PyObject *, Py_ssize_t);


int PyUnicodeDecodeError_SetReason(PyObject *exc, const char *reason);

static void make_decode_exception(PyObject **exceptionObject, const char *encoding, const char *input, Py_ssize_t length, Py_ssize_t startpos, Py_ssize_t endpos, const char *reason) ;

static inline PyObject *PyObject_CallOneArg(PyObject *func, PyObject *arg) ;


int _PyArg_ParseTuple_SizeT(PyObject *, const char *, ...);


PyObject *PyUnicodeDecodeError_GetObject(PyObject *);

int _PyUnicodeWriter_PrepareInternal(_PyUnicodeWriter *writer, Py_ssize_t length, Py_UCS4 maxchar);

int _PyUnicodeWriter_WriteStr(_PyUnicodeWriter *writer, PyObject *str);

static Py_ssize_t ascii_decode(const char *start, const char *end, Py_UCS1 *dest) ;

static inline void _PyUnicodeWriter_InitWithBuffer(_PyUnicodeWriter *writer, PyObject *buffer);

static inline Py_UCS4 asciilib_utf8_decode(const char **inptr, const char *end, Py_UCS1 *dest, Py_ssize_t *outpos) ;

static inline Py_UCS4 ucs1lib_utf8_decode(const char **inptr, const char *end, Py_UCS1 *dest, Py_ssize_t *outpos) ;

static inline Py_UCS4 ucs2lib_utf8_decode(const char **inptr, const char *end, Py_UCS2 *dest, Py_ssize_t *outpos) ;

static inline Py_UCS4 ucs4lib_utf8_decode(const char **inptr, const char *end, Py_UCS4 *dest, Py_ssize_t *outpos) ;

static inline int _PyUnicodeWriter_WriteCharInline(_PyUnicodeWriter *writer, Py_UCS4 ch);

_Py_error_handler _Py_GetErrorHandler(const char *errors) ;

int _PyUnicodeWriter_PrepareKindInternal(_PyUnicodeWriter *writer, enum PyUnicode_Kind kind);

static int unicode_decode_call_errorhandler_writer(const char *errors, PyObject **errorHandler, const char *encoding, const char *reason, const char **input, const char **inend, Py_ssize_t *startinpos, Py_ssize_t *endinpos, PyObject **exceptionObject, const char **inptr, _PyUnicodeWriter *writer) ;

PyObject *_PyUnicodeWriter_Finish(_PyUnicodeWriter *writer);

void _PyUnicodeWriter_Dealloc(_PyUnicodeWriter *writer);

PyObject *PyUnicode_DecodeUTF32Stateful(const char *string, Py_ssize_t length, const char *errors, int *byteorder, Py_ssize_t *consumed);

void _PyUnicodeWriter_Init(_PyUnicodeWriter *writer);

PyObject *PyUnicode_DecodeUTF16Stateful(const char *string, Py_ssize_t length, const char *errors, int *byteorder, Py_ssize_t *consumed);

static inline Py_UCS4 asciilib_utf16_decode(const unsigned char **inptr, const unsigned char *e, Py_UCS1 *dest, Py_ssize_t *outpos, int native_ordering) ;

static inline Py_UCS4 ucs1lib_utf16_decode(const unsigned char **inptr, const unsigned char *e, Py_UCS1 *dest, Py_ssize_t *outpos, int native_ordering) ;

static inline Py_UCS4 ucs2lib_utf16_decode(const unsigned char **inptr, const unsigned char *e, Py_UCS2 *dest, Py_ssize_t *outpos, int native_ordering) ;

static inline Py_UCS4 ucs4lib_utf16_decode(const unsigned char **inptr, const unsigned char *e, Py_UCS4 *dest, Py_ssize_t *outpos, int native_ordering) ;

static PyObject *_PyUnicode_FromUCS1(const Py_UCS1 *u, Py_ssize_t size) ;

static inline void _PyUnicodeWriter_Update(_PyUnicodeWriter *writer) ;

void _PyUnicode_FastCopyCharacters(PyObject *to, Py_ssize_t to_start, PyObject *from, Py_ssize_t from_start, Py_ssize_t how_many) ;

static PyObject *resize_compact(PyObject *unicode, Py_ssize_t length) ;

#endif