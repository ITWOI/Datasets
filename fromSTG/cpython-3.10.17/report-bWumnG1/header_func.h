#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
void _PyWideStringList_Clear(PyWideStringList *list) ;


void *PyMem_RawMalloc(size_t size);


wchar_t *_PyMem_RawWcsdup(const wchar_t *str);


void *PyMem_RawRealloc(void *ptr, size_t new_size);


void PyMem_RawFree(void *ptr);

PyStatus PyWideStringList_Insert(PyWideStringList *list, Py_ssize_t index, const wchar_t *item) ;

PyStatus PyWideStringList_Append(PyWideStringList *list, const wchar_t *item) ;


PyStatus _Py_PreInitializeFromConfig(const PyConfig *config, const struct _PyArgv *args);


wchar_t *Py_DecodeLocale(const char *arg, size_t *size);


const char *_Py_GetEnv(int use_environment, const char *name);

static PyStatus config_set_bytes_string(PyConfig *config, wchar_t **config_str, const char *str, const char *decode_err_msg) ;

int Py_IsolatedFlag = 0;
;
int Py_IgnoreEnvironmentFlag = 0;
;
int Py_BytesWarningFlag = 0;
;
int Py_InspectFlag = 0;
;
int Py_InteractiveFlag = 0;
;
int Py_OptimizeFlag = 0;
;
int Py_DebugFlag = 0;
;
int Py_VerboseFlag = 0;
;
int Py_QuietFlag = 0;
;
int Py_FrozenFlag = 0;
;
int Py_UnbufferedStdioFlag = 0;
;
int Py_NoSiteFlag = 0;
;
int Py_DontWriteBytecodeFlag = 0;
;
int Py_NoUserSiteDirectory = 0;
;
extern _PyPathConfig _Py_path_config;
;
PyStatus PyConfig_SetString(PyConfig *config, wchar_t **config_str, const wchar_t *str) ;


const wchar_t *_Py_get_xoption(const PyWideStringList *xoptions, const wchar_t *name);

static PyStatus config_get_env_dup(PyConfig *config, wchar_t **dest, wchar_t *wname, char *name, const char *decode_err_msg) ;

static const char *config_get_env(const PyConfig *config, const char *name) ;

static PyStatus config_init_hash_seed(PyConfig *config) ;


int _Py_str_to_int(const char *str, int *result);

static const wchar_t *config_get_xoption(const PyConfig *config, wchar_t *name) ;

static int config_wstr_to_int(const wchar_t *wstr, int *result) ;

int _Py_global_config_int_max_str_digits = -1;
;
static PyStatus config_init_tracemalloc(PyConfig *config) ;

static PyStatus config_init_int_max_str_digits(PyConfig *config) ;

static PyStatus config_init_pycache_prefix(PyConfig *config) ;


int _Py_IsLocaleCoercionTarget(const char *ctype_loc);


wchar_t *_Py_GetLocaleEncoding(void);

static char *_Py_StandardStreamEncoding = ((void *)0);
;
static char *_Py_StandardStreamErrors = ((void *)0);
;

char *_PyMem_RawStrdup(const char *str);

static PyStatus config_get_locale_encoding(PyConfig *config, const PyPreConfig *preconfig, wchar_t **locale_encoding) ;

static const wchar_t *config_get_stdio_errors(const PyPreConfig *preconfig) ;


int _Py_GetForceASCII(void);

static PyStatus config_get_fs_encoding(PyConfig *config, const PyPreConfig *preconfig, wchar_t **fs_encoding) ;

extern _PyRuntimeState _PyRuntime;
;
static PyStatus config_read_env_vars(PyConfig *config) ;

static PyStatus config_read_complex_options(PyConfig *config) ;

static PyStatus config_init_home(PyConfig *config) ;

static PyStatus config_init_executable(PyConfig *config) ;


extern PyStatus _PyConfig_InitPathConfig(PyConfig *config, int compute_path_config);

static PyStatus config_init_fs_encoding(PyConfig *config, const PyPreConfig *preconfig) ;

static PyStatus config_init_stdio_encoding(PyConfig *config, const PyPreConfig *preconfig) ;

static void config_usage(int error, const wchar_t *program) ;


extern int _PyOS_GetOpt(Py_ssize_t argc, wchar_t *const *argv, int *longindex);

extern const wchar_t *_PyOS_optarg;
;

const char *Py_GetVersion(void);

extern Py_ssize_t _PyOS_optind;
;
static int _PyWideStringList_Find(PyWideStringList *list, const wchar_t *item) ;

static PyStatus warnoptions_append(PyConfig *config, PyWideStringList *options, const wchar_t *option) ;

static PyStatus warnoptions_extend(PyConfig *config, PyWideStringList *options, const PyWideStringList *options2) ;

PyStatus _PyWideStringList_Extend(PyWideStringList *list, const PyWideStringList *list2) ;

int _PyWideStringList_Copy(PyWideStringList *list, const PyWideStringList *list2) ;


extern PyStatus _PyPreConfig_InitFromPreConfig(PyPreConfig *preconfig, const PyPreConfig *config2);


extern PyStatus _PyPreCmdline_Read(_PyPreCmdline *cmdline, const PyPreConfig *preconfig);


extern PyStatus _PyPreCmdline_SetConfig(const _PyPreCmdline *cmdline, PyConfig *config);


int _Py_isabs(const wchar_t *path);


int _Py_abspath(const wchar_t *path, wchar_t **abspath_p);

static PyStatus config_init_program_name(PyConfig *config) ;

static PyStatus config_parse_cmdline(PyConfig *config, PyWideStringList *warnoptions, Py_ssize_t *opt_index) ;

static PyStatus config_run_filename_abspath(PyConfig *config) ;

static PyStatus config_update_argv(PyConfig *config, Py_ssize_t opt_index) ;

static PyStatus config_init_env_warnoptions(PyConfig *config, PyWideStringList *warnoptions) ;


extern PyStatus _PySys_ReadPreinitWarnOptions(PyWideStringList *options);

static PyStatus config_init_warnoptions(PyConfig *config, const PyWideStringList *cmdline_warnoptions, const PyWideStringList *env_warnoptions, const PyWideStringList *sys_warnoptions) ;

static void config_get_global_vars(PyConfig *config) ;

static PyStatus core_read_precmdline(PyConfig *config, _PyPreCmdline *precmdline) ;

static PyStatus config_read_cmdline(PyConfig *config) ;


extern PyStatus _PySys_ReadPreinitXOptions(PyConfig *config);

static PyStatus config_read(PyConfig *config, int compute_path_config) ;

PyStatus _PyConfig_Read(PyConfig *config, int compute_path_config) ;

#endif