extern  __attribute__((visibility("default"))) void _PyWideStringList_Clear (PyWideStringList *list){
    ;
    ;
    list->length = 0;
    list->items = ((void *)0);
}


extern  __attribute__((visibility("default"))) int _PyWideStringList_Copy (PyWideStringList *list, const PyWideStringList *list2){
    ;
    ;
    if (list2->length == 0) {
        _PyWideStringList_Clear(list);
        return 0;
    }
    PyWideStringList copy = (PyWideStringList){.length = 0, .items = ((void *)0)};
    size_t size = list2->length * sizeof (list2->items[0]);
    copy.items = PyMem_RawMalloc(size);
    if (copy.items == ((void *)0)) {
        return -1;
    }
    for (Py_ssize_t i = 0; i < list2->length; i++) {
        wchar_t *item = _PyMem_RawWcsdup(list2->items[i]);
        if (item == ((void *)0)) {
            _PyWideStringList_Clear(&copy);
            return -1;
        }
        copy.items[i] = item;
        copy.length = i + 1;
    }
    _PyWideStringList_Clear(list);
    *list = copy;
    return 0;
}


extern  __attribute__((visibility("default"))) PyStatus PyWideStringList_Insert (PyWideStringList *list, Py_ssize_t index, const wchar_t *item){
    Py_ssize_t len = list->length;
    if (len == ((Py_ssize_t)(((size_t)-1) >> 1))) {
        return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("memory allocation failed")};
    }
    if (index < 0) {
        return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("PyWideStringList_Insert index must be >= 0")};
    }
    if (index > len) {
        index = len;
    }
    wchar_t *item2 = _PyMem_RawWcsdup(item);
    if (item2 == ((void *)0)) {
        return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("memory allocation failed")};
    }
    size_t size = (len + 1) * sizeof (list->items[0]);
    wchar_t **items2 = (wchar_t **)PyMem_RawRealloc(list->items, size);
    if (items2 == ((void *)0)) {
        ;
        return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("memory allocation failed")};
    }
    items2[index] = item2;
    list->items = items2;
    list->length++;
    return (PyStatus){._type = _PyStatus_TYPE_OK};
}


extern  __attribute__((visibility("default"))) PyStatus PyWideStringList_Append (PyWideStringList *list, const wchar_t *item){
    return PyWideStringList_Insert(list, list->length, item);
}


extern  __attribute__((visibility("default"))) PyStatus _PyWideStringList_Extend (PyWideStringList *list, const PyWideStringList *list2){
    for (Py_ssize_t i = 0; i < list2->length; i++) {
        PyStatus status = PyWideStringList_Append(list, list2->items[i]);
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
    }
    return (PyStatus){._type = _PyStatus_TYPE_OK};
}


static int _PyWideStringList_Find (PyWideStringList *list, const wchar_t *item){
    for (Py_ssize_t i = 0; i < list->length; i++) {
        if (wcscmp(list->items[i], item) == 0) {
            return 1;
        }
    }
    return 0;
}


extern  __attribute__((visibility("default"))) PyStatus PyConfig_SetString (PyConfig *config, wchar_t **config_str, const wchar_t *str){
    PyStatus status = _Py_PreInitializeFromConfig(config, ((void *)0));
    if ((status._type != _PyStatus_TYPE_OK)) {
        return status;
    }
    wchar_t *str2;
    if (str != ((void *)0)) {
        str2 = _PyMem_RawWcsdup(str);
        if (str2 == ((void *)0)) {
            return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("memory allocation failed")};
        }
    } else {
        str2 = ((void *)0);
    }
    ;
    *config_str = str2;
    return (PyStatus){._type = _PyStatus_TYPE_OK};
}


static PyStatus config_set_bytes_string (PyConfig *config, wchar_t **config_str, const char *str, const char *decode_err_msg){
    PyStatus status = _Py_PreInitializeFromConfig(config, ((void *)0));
    if ((status._type != _PyStatus_TYPE_OK)) {
        return status;
    }
    wchar_t *str2;
    if (str != ((void *)0)) {
        size_t len;
        str2 = Py_DecodeLocale(str, &len);
        if (str2 == ((void *)0)) {
            if (len == (size_t)-2) {
                return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = (decode_err_msg)};
            } else {
                return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("memory allocation failed")};
            }
        }
    } else {
        str2 = ((void *)0);
    }
    ;
    *config_str = str2;
    return (PyStatus){._type = _PyStatus_TYPE_OK};
}


static const char * config_get_env (const PyConfig *config, const char *name){
    return _Py_GetEnv(config->use_environment, name);
}


static PyStatus config_get_env_dup (PyConfig *config, wchar_t **dest, wchar_t *wname, char *name, const char *decode_err_msg){
    ;
    ;
    if (!config->use_environment) {
        *dest = ((void *)0);
        return (PyStatus){._type = _PyStatus_TYPE_OK};
    }
    const char *var = getenv(name);
    if (!var || var[0] == '\x00') {
        *dest = ((void *)0);
        return (PyStatus){._type = _PyStatus_TYPE_OK};
    }
    return config_set_bytes_string(config, dest, var, decode_err_msg);
}


static void config_get_global_vars (PyConfig *config){
    if (config->_config_init != _PyConfig_INIT_COMPAT) {
        return;
    }
    if (config->isolated == -1) {
        config->isolated = Py_IsolatedFlag;
    }
    ;
    ;
    if (config->use_environment == -1) {
        config->use_environment = !(Py_IgnoreEnvironmentFlag);
    }
    ;
    ;
    if (config->bytes_warning == -1) {
        config->bytes_warning = Py_BytesWarningFlag;
    }
    ;
    ;
    if (config->inspect == -1) {
        config->inspect = Py_InspectFlag;
    }
    ;
    ;
    if (config->interactive == -1) {
        config->interactive = Py_InteractiveFlag;
    }
    ;
    ;
    if (config->optimization_level == -1) {
        config->optimization_level = Py_OptimizeFlag;
    }
    ;
    ;
    if (config->parser_debug == -1) {
        config->parser_debug = Py_DebugFlag;
    }
    ;
    ;
    if (config->verbose == -1) {
        config->verbose = Py_VerboseFlag;
    }
    ;
    ;
    if (config->quiet == -1) {
        config->quiet = Py_QuietFlag;
    }
    ;
    ;
    if (config->pathconfig_warnings == -1) {
        config->pathconfig_warnings = !(Py_FrozenFlag);
    }
    ;
    ;
    if (config->buffered_stdio == -1) {
        config->buffered_stdio = !(Py_UnbufferedStdioFlag);
    }
    ;
    ;
    if (config->site_import == -1) {
        config->site_import = !(Py_NoSiteFlag);
    }
    ;
    ;
    if (config->write_bytecode == -1) {
        config->write_bytecode = !(Py_DontWriteBytecodeFlag);
    }
    ;
    ;
    if (config->user_site_directory == -1) {
        config->user_site_directory = !(Py_NoUserSiteDirectory);
    }
    ;
    ;
}


static PyStatus config_init_program_name (PyConfig *config){
    PyStatus status;
    const wchar_t *program_name = _Py_path_config.program_name;
    if (program_name != ((void *)0)) {
        config->program_name = _PyMem_RawWcsdup(program_name);
        if (config->program_name == ((void *)0)) {
            return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("memory allocation failed")};
        }
        return (PyStatus){._type = _PyStatus_TYPE_OK};
    }
    const PyWideStringList *argv = &config->argv;
    if (argv->length >= 1 && argv->items[0][0] != L'\x00') {
        config->program_name = _PyMem_RawWcsdup(argv->items[0]);
        if (config->program_name == ((void *)0)) {
            return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("memory allocation failed")};
        }
        return (PyStatus){._type = _PyStatus_TYPE_OK};
    }
    const wchar_t *default_program_name = L"python3";
    status = PyConfig_SetString(config, &config->program_name, default_program_name);
    if ((status._type != _PyStatus_TYPE_OK)) {
        return status;
    }
    return (PyStatus){._type = _PyStatus_TYPE_OK};
}


static PyStatus config_init_executable (PyConfig *config){
    ;
    const wchar_t *program_full_path = _Py_path_config.program_full_path;
    if (program_full_path != ((void *)0)) {
        PyStatus status = PyConfig_SetString(config, &config->executable, program_full_path);
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
        return (PyStatus){._type = _PyStatus_TYPE_OK};
    }
    return (PyStatus){._type = _PyStatus_TYPE_OK};
}


static const wchar_t * config_get_xoption (const PyConfig *config, wchar_t *name){
    return _Py_get_xoption(&config->xoptions, name);
}


static PyStatus config_init_home (PyConfig *config){
    ;
    wchar_t *home = _Py_path_config.home;
    if (home) {
        PyStatus status = PyConfig_SetString(config, &config->home, home);
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
        return (PyStatus){._type = _PyStatus_TYPE_OK};
    }
    return config_get_env_dup(config, &config->home, L"PYTHONHOME", "PYTHONHOME", "cannot decode PYTHONHOME");
}


static PyStatus config_init_hash_seed (PyConfig *config){
    const char *seed_text = config_get_env(config, "PYTHONHASHSEED");
    ;
    if (seed_text && strcmp(seed_text, "random") != 0) {
        const char *endptr = seed_text;
        unsigned long seed;
        (*__errno_location()) = 0;
        seed = strtoul(seed_text, (char **)&endptr, 10);
        if (*endptr != '\x00' || seed > 4294967295UL || ((*__errno_location()) == 34 && seed == (9223372036854775807L * 2UL + 1UL))) {
            return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("PYTHONHASHSEED must be \"random\" or an integer in range [0; 4294967295]")};
        }
        config->use_hash_seed = 1;
        config->hash_seed = seed;
    } else {
        config->use_hash_seed = 0;
        config->hash_seed = 0;
    }
    return (PyStatus){._type = _PyStatus_TYPE_OK};
}


static int config_wstr_to_int (const wchar_t *wstr, int *result){
    const wchar_t *endptr = wstr;
    (*__errno_location()) = 0;
    long value = wcstol(wstr, (wchar_t **)&endptr, 10);
    if (*endptr != '\x00' || (*__errno_location()) == 34) {
        return -1;
    }
    if (value < (-2147483647 - 1) || value > 2147483647) {
        return -1;
    }
    *result = (int)value;
    return 0;
}


static PyStatus config_read_env_vars (PyConfig *config){
    PyStatus status;
    int use_env = config->use_environment;
    ;
    ;
    ;
    ;
    int dont_write_bytecode = 0;
    ;
    if (dont_write_bytecode) {
        config->write_bytecode = 0;
    }
    int no_user_site_directory = 0;
    ;
    if (no_user_site_directory) {
        config->user_site_directory = 0;
    }
    int unbuffered_stdio = 0;
    ;
    if (unbuffered_stdio) {
        config->buffered_stdio = 0;
    }
    if (config_get_env(config, "PYTHONDUMPREFS")) {
        config->dump_refs = 1;
    }
    if (config_get_env(config, "PYTHONMALLOCSTATS")) {
        config->malloc_stats = 1;
    }
    if (config->pythonpath_env == ((void *)0)) {
        status = config_get_env_dup(config, &config->pythonpath_env, L"PYTHONPATH", "PYTHONPATH", "cannot decode PYTHONPATH");
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
    }
    if (config->platlibdir == ((void *)0)) {
        status = config_get_env_dup(config, &config->platlibdir, L"PYTHONPLATLIBDIR", "PYTHONPLATLIBDIR", "cannot decode PYTHONPLATLIBDIR");
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
    }
    if (config->use_hash_seed < 0) {
        status = config_init_hash_seed(config);
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
    }
    return (PyStatus){._type = _PyStatus_TYPE_OK};
}


static PyStatus config_init_tracemalloc (PyConfig *config){
    int nframe;
    int valid;
    const char *env = config_get_env(config, "PYTHONTRACEMALLOC");
    if (env) {
        if (!_Py_str_to_int(env, &nframe)) {
            valid = (nframe >= 0);
        } else {
            valid = 0;
        }
        if (!valid) {
            return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("PYTHONTRACEMALLOC: invalid number of frames")};
        }
        config->tracemalloc = nframe;
    }
    const wchar_t *xoption = config_get_xoption(config, L"tracemalloc");
    if (xoption) {
        const wchar_t *sep = wcschr(xoption, L'=');
        if (sep) {
            if (!config_wstr_to_int(sep + 1, &nframe)) {
                valid = (nframe >= 0);
            } else {
                valid = 0;
            }
            if (!valid) {
                return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("-X tracemalloc=NFRAME: invalid number of frames")};
            }
        } else {
            nframe = 1;
        }
        config->tracemalloc = nframe;
    }
    return (PyStatus){._type = _PyStatus_TYPE_OK};
}


static PyStatus config_init_int_max_str_digits (PyConfig *config){
    int maxdigits;
    const char *env = config_get_env(config, "PYTHONINTMAXSTRDIGITS");
    if (env) {
        int valid = 0;
        if (!_Py_str_to_int(env, &maxdigits)) {
            valid = ((maxdigits == 0) || (maxdigits >= 640));
        }
        if (!valid) {
            return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("PYTHONINTMAXSTRDIGITS: invalid limit; must be >= 640 or 0 for unlimited.")};
        }
        _Py_global_config_int_max_str_digits = maxdigits;
    }
    const wchar_t *xoption = config_get_xoption(config, L"int_max_str_digits");
    if (xoption) {
        const wchar_t *sep = wcschr(xoption, L'=');
        int valid = 0;
        if (sep) {
            if (!config_wstr_to_int(sep + 1, &maxdigits)) {
                valid = ((maxdigits == 0) || (maxdigits >= 640));
            }
        }
        if (!valid) {
            return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("-X int_max_str_digits: invalid limit; must be >= 640 or 0 for unlimited.")};
        }
        _Py_global_config_int_max_str_digits = maxdigits;
    }
    return (PyStatus){._type = _PyStatus_TYPE_OK};
}


static PyStatus config_init_pycache_prefix (PyConfig *config){
    ;
    const wchar_t *xoption = config_get_xoption(config, L"pycache_prefix");
    if (xoption) {
        const wchar_t *sep = wcschr(xoption, L'=');
        if (sep && wcslen(sep) > 1) {
            config->pycache_prefix = _PyMem_RawWcsdup(sep + 1);
            if (config->pycache_prefix == ((void *)0)) {
                return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("memory allocation failed")};
            }
        } else {
            config->pycache_prefix = ((void *)0);
        }
        return (PyStatus){._type = _PyStatus_TYPE_OK};
    }
    return config_get_env_dup(config, &config->pycache_prefix, L"PYTHONPYCACHEPREFIX", "PYTHONPYCACHEPREFIX", "cannot decode PYTHONPYCACHEPREFIX");
}


static PyStatus config_read_complex_options (PyConfig *config){
    if (config->faulthandler < 0) {
        if (config_get_env(config, "PYTHONFAULTHANDLER") || config_get_xoption(config, L"faulthandler")) {
            config->faulthandler = 1;
        }
    }
    if (config_get_env(config, "PYTHONPROFILEIMPORTTIME") || config_get_xoption(config, L"importtime")) {
        config->import_time = 1;
    }
    PyStatus status;
    if (config->tracemalloc < 0) {
        status = config_init_tracemalloc(config);
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
    }
    if (_Py_global_config_int_max_str_digits < 0) {
        status = config_init_int_max_str_digits(config);
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
    }
    if (config->pycache_prefix == ((void *)0)) {
        status = config_init_pycache_prefix(config);
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
    }
    return (PyStatus){._type = _PyStatus_TYPE_OK};
}


static const wchar_t * config_get_stdio_errors (const PyPreConfig *preconfig){
    if (preconfig->utf8_mode) {
        return L"surrogateescape";
    }
    const char *loc = setlocale(0, ((void *)0));
    if (loc != ((void *)0)) {
        if (strcmp(loc, "C") == 0 || strcmp(loc, "POSIX") == 0) {
            return L"surrogateescape";
        }
        if (_Py_IsLocaleCoercionTarget(loc)) {
            return L"surrogateescape";
        }
    }
    return L"strict";
}


static PyStatus config_get_locale_encoding (PyConfig *config, const PyPreConfig *preconfig, wchar_t **locale_encoding){
    wchar_t *encoding = _Py_GetLocaleEncoding();
    if (encoding == ((void *)0)) {
        return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("memory allocation failed")};
    }
    PyStatus status = PyConfig_SetString(config, locale_encoding, encoding);
    ;
    return status;
}


static PyStatus config_init_stdio_encoding (PyConfig *config, const PyPreConfig *preconfig){
    PyStatus status;
    if (config->stdio_encoding == ((void *)0) && _Py_StandardStreamEncoding != ((void *)0)) {
        status = config_set_bytes_string(config, &config->stdio_encoding, _Py_StandardStreamEncoding, "cannot decode _Py_StandardStreamEncoding");
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
    }
    if (config->stdio_errors == ((void *)0) && _Py_StandardStreamErrors != ((void *)0)) {
        status = config_set_bytes_string(config, &config->stdio_errors, _Py_StandardStreamErrors, "cannot decode _Py_StandardStreamErrors");
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
    }
    if (config->stdio_encoding != ((void *)0) && config->stdio_errors != ((void *)0)) {
        return (PyStatus){._type = _PyStatus_TYPE_OK};
    }
    const char *opt = config_get_env(config, "PYTHONIOENCODING");
    if (opt) {
        char *pythonioencoding = _PyMem_RawStrdup(opt);
        if (pythonioencoding == ((void *)0)) {
            return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("memory allocation failed")};
        }
        char *errors = strchr(pythonioencoding, ':');
        if (errors) {
            *errors = '\x00';
            errors++;
            if (!errors[0]) {
                errors = ((void *)0);
            }
        }
        if (pythonioencoding[0]) {
            if (config->stdio_encoding == ((void *)0)) {
                status = config_set_bytes_string(config, &config->stdio_encoding, pythonioencoding, "cannot decode PYTHONIOENCODING environment variable");
                if ((status._type != _PyStatus_TYPE_OK)) {
                    ;
                    return status;
                }
            }
            if (!errors) {
                errors = "strict";
            }
        }
        if (config->stdio_errors == ((void *)0) && errors != ((void *)0)) {
            status = config_set_bytes_string(config, &config->stdio_errors, errors, "cannot decode PYTHONIOENCODING environment variable");
            if ((status._type != _PyStatus_TYPE_OK)) {
                ;
                return status;
            }
        }
        ;
    }
    if (config->stdio_encoding == ((void *)0)) {
        status = config_get_locale_encoding(config, preconfig, &config->stdio_encoding);
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
    }
    if (config->stdio_errors == ((void *)0)) {
        const wchar_t *errors = config_get_stdio_errors(preconfig);
        ;
        status = PyConfig_SetString(config, &config->stdio_errors, errors);
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
    }
    return (PyStatus){._type = _PyStatus_TYPE_OK};
}


static PyStatus config_get_fs_encoding (PyConfig *config, const PyPreConfig *preconfig, wchar_t **fs_encoding){
    if (preconfig->utf8_mode) {
        return PyConfig_SetString(config, fs_encoding, L"utf-8");
    }
    if (_Py_GetForceASCII()) {
        return PyConfig_SetString(config, fs_encoding, L"ascii");
    }
    return config_get_locale_encoding(config, preconfig, fs_encoding);
}


static PyStatus config_init_fs_encoding (PyConfig *config, const PyPreConfig *preconfig){
    PyStatus status;
    if (config->filesystem_encoding == ((void *)0)) {
        status = config_get_fs_encoding(config, preconfig, &config->filesystem_encoding);
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
    }
    if (config->filesystem_errors == ((void *)0)) {
        const wchar_t *errors;
        errors = L"surrogateescape";
        status = PyConfig_SetString(config, &config->filesystem_errors, errors);
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
    }
    return (PyStatus){._type = _PyStatus_TYPE_OK};
}


static PyStatus config_read (PyConfig *config, int compute_path_config){
    PyStatus status;
    const PyPreConfig *preconfig = &_PyRuntime.preconfig;
    if (config->use_environment) {
        status = config_read_env_vars(config);
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
    }
    if (config_get_xoption(config, L"showrefcount")) {
        config->show_ref_count = 1;
    }
    status = config_read_complex_options(config);
    if ((status._type != _PyStatus_TYPE_OK)) {
        return status;
    }
    if (config->home == ((void *)0)) {
        status = config_init_home(config);
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
    }
    if (config->executable == ((void *)0)) {
        status = config_init_executable(config);
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
    }
    if (config->platlibdir == ((void *)0)) {
        status = config_set_bytes_string(config, &config->platlibdir, "lib", "cannot decode PLATLIBDIR macro");
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
    }
    if (config->_install_importlib) {
        status = _PyConfig_InitPathConfig(config, compute_path_config);
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
    }
    if (config->dev_mode) {
        if (config->faulthandler < 0) {
            config->faulthandler = 1;
        }
    }
    if (config->faulthandler < 0) {
        config->faulthandler = 0;
    }
    if (config->tracemalloc < 0) {
        config->tracemalloc = 0;
    }
    if (config->use_hash_seed < 0) {
        config->use_hash_seed = 0;
        config->hash_seed = 0;
    }
    if (config->filesystem_encoding == ((void *)0) || config->filesystem_errors == ((void *)0)) {
        status = config_init_fs_encoding(config, preconfig);
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
    }
    status = config_init_stdio_encoding(config, preconfig);
    if ((status._type != _PyStatus_TYPE_OK)) {
        return status;
    }
    if (config->argv.length < 1) {
        status = PyWideStringList_Append(&config->argv, L"");
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
    }
    if (config->check_hash_pycs_mode == ((void *)0)) {
        status = PyConfig_SetString(config, &config->check_hash_pycs_mode, L"default");
    }
    return (PyStatus){._type = _PyStatus_TYPE_OK};
}


static PyStatus config_parse_cmdline (PyConfig *config, PyWideStringList *warnoptions, Py_ssize_t *opt_index){
    PyStatus status;
    const PyWideStringList *argv = &config->argv;
    int print_version = 0;
    const wchar_t *program = config->program_name;
    ;
    do {
        int longindex = -1;
        int c = _PyOS_GetOpt(argv->length, argv->items, &longindex);
        if (c == (-1)) {
            break;
        }
        if (c == 'c') {
            if (config->run_command == ((void *)0)) {
                size_t len = wcslen(_PyOS_optarg) + 1 + 1;
                wchar_t *command = PyMem_RawMalloc(sizeof(wchar_t) * len);
                if (command == ((void *)0)) {
                    return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("memory allocation failed")};
                }
                ;
                command[len - 2] = '\n';
                command[len - 1] = 0;
                config->run_command = command;
            }
            break;
        }
        if (c == 'm') {
            if (config->run_module == ((void *)0)) {
                config->run_module = _PyMem_RawWcsdup(_PyOS_optarg);
                if (config->run_module == ((void *)0)) {
                    return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("memory allocation failed")};
                }
            }
            break;
        }
        switch (c) {
          case 0:
            ((void)(0));
            if (wcscmp(_PyOS_optarg, L"always") == 0 || wcscmp(_PyOS_optarg, L"never") == 0 || wcscmp(_PyOS_optarg, L"default") == 0) {
                status = PyConfig_SetString(config, &config->check_hash_pycs_mode, _PyOS_optarg);
                if ((status._type != _PyStatus_TYPE_OK)) {
                    return status;
                }
            } else {
                ;
                ;
                return (PyStatus){._type = _PyStatus_TYPE_EXIT, .exitcode = (2)};
            }
            break;
          case 'b':
            config->bytes_warning++;
            break;
          case 'd':
            config->parser_debug++;
            break;
          case 'i':
            config->inspect++;
            config->interactive++;
            break;
            ;
          case 'O':
            config->optimization_level++;
            break;
          case 'B':
            config->write_bytecode = 0;
            break;
          case 's':
            config->user_site_directory = 0;
            break;
          case 'S':
            config->site_import = 0;
            break;
            ;
          case 'u':
            config->buffered_stdio = 0;
            break;
          case 'v':
            config->verbose++;
            break;
          case 'x':
            config->skip_source_first_line = 1;
            break;
          case 'h':
            ;
            return (PyStatus){._type = _PyStatus_TYPE_EXIT, .exitcode = (0)};
          case 'V':
            print_version++;
            break;
          case 'W':
            status = PyWideStringList_Append(warnoptions, _PyOS_optarg);
            if ((status._type != _PyStatus_TYPE_OK)) {
                return status;
            }
            break;
          case 'q':
            config->quiet++;
            break;
          case 'R':
            config->use_hash_seed = 0;
            break;
          default:
            ;
            return (PyStatus){._type = _PyStatus_TYPE_EXIT, .exitcode = (2)};
        }
    } while (1);
    if (print_version) {
        ;
        return (PyStatus){._type = _PyStatus_TYPE_EXIT, .exitcode = (0)};
    }
    if (config->run_command == ((void *)0) && config->run_module == ((void *)0) && _PyOS_optind < argv->length && wcscmp(argv->items[_PyOS_optind], L"-") != 0 && config->run_filename == ((void *)0)) {
        config->run_filename = _PyMem_RawWcsdup(argv->items[_PyOS_optind]);
        if (config->run_filename == ((void *)0)) {
            return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("memory allocation failed")};
        }
    }
    if (config->run_command != ((void *)0) || config->run_module != ((void *)0)) {
        _PyOS_optind--;
    }
    *opt_index = _PyOS_optind;
    return (PyStatus){._type = _PyStatus_TYPE_OK};
}


static PyStatus config_init_env_warnoptions (PyConfig *config, PyWideStringList *warnoptions){
    PyStatus status;
    wchar_t *env = ((void *)0);
    status = config_get_env_dup(config, &env, L"PYTHONWARNINGS", "PYTHONWARNINGS", "cannot decode PYTHONWARNINGS");
    if ((status._type != _PyStatus_TYPE_OK)) {
        return status;
    }
    if (env == ((void *)0)) {
        return (PyStatus){._type = _PyStatus_TYPE_OK};
    }
    wchar_t *warning, *context = ((void *)0);
    for (warning = wcstok(env, L",", &context); warning != ((void *)0); warning = wcstok(((void *)0), L",", &context)) {
        status = PyWideStringList_Append(warnoptions, warning);
        if ((status._type != _PyStatus_TYPE_OK)) {
            ;
            return status;
        }
    }
    ;
    return (PyStatus){._type = _PyStatus_TYPE_OK};
}


static PyStatus warnoptions_append (PyConfig *config, PyWideStringList *options, const wchar_t *option){
    if (_PyWideStringList_Find(&config->warnoptions, option)) {
        return (PyStatus){._type = _PyStatus_TYPE_OK};
    }
    if (_PyWideStringList_Find(options, option)) {
        return (PyStatus){._type = _PyStatus_TYPE_OK};
    }
    return PyWideStringList_Append(options, option);
}


static PyStatus warnoptions_extend (PyConfig *config, PyWideStringList *options, const PyWideStringList *options2){
    const Py_ssize_t len = options2->length;
    wchar_t *const *items = options2->items;
    for (Py_ssize_t i = 0; i < len; i++) {
        PyStatus status = warnoptions_append(config, options, items[i]);
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
    }
    return (PyStatus){._type = _PyStatus_TYPE_OK};
}


static PyStatus config_init_warnoptions (PyConfig *config, const PyWideStringList *cmdline_warnoptions, const PyWideStringList *env_warnoptions, const PyWideStringList *sys_warnoptions){
    PyStatus status;
    PyWideStringList options = (PyWideStringList){.length = 0, .items = ((void *)0)};
    if (config->dev_mode) {
        status = warnoptions_append(config, &options, L"default");
        if ((status._type != _PyStatus_TYPE_OK)) {
            goto error;
        }
    }
    status = warnoptions_extend(config, &options, env_warnoptions);
    if ((status._type != _PyStatus_TYPE_OK)) {
        goto error;
    }
    status = warnoptions_extend(config, &options, cmdline_warnoptions);
    if ((status._type != _PyStatus_TYPE_OK)) {
        goto error;
    }
    if (config->bytes_warning) {
        const wchar_t *filter;
        if (config->bytes_warning > 1) {
            filter = L"error::BytesWarning";
        } else {
            filter = L"default::BytesWarning";
        }
        status = warnoptions_append(config, &options, filter);
        if ((status._type != _PyStatus_TYPE_OK)) {
            goto error;
        }
    }
    status = warnoptions_extend(config, &options, sys_warnoptions);
    if ((status._type != _PyStatus_TYPE_OK)) {
        goto error;
    }
    status = _PyWideStringList_Extend(&options, &config->warnoptions);
    if ((status._type != _PyStatus_TYPE_OK)) {
        goto error;
    }
    _PyWideStringList_Clear(&config->warnoptions);
    ;
    return (PyStatus){._type = _PyStatus_TYPE_OK};
  error:
    _PyWideStringList_Clear(&options);
    return status;
}


static PyStatus config_update_argv (PyConfig *config, Py_ssize_t opt_index){
    const PyWideStringList *cmdline_argv = &config->argv;
    PyWideStringList config_argv = (PyWideStringList){.length = 0, .items = ((void *)0)};
    if (cmdline_argv->length <= opt_index) {
        PyStatus status = PyWideStringList_Append(&config_argv, L"");
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
    } else {
        PyWideStringList slice;
        slice.length = cmdline_argv->length - opt_index;
        slice.items = &cmdline_argv->items[opt_index];
        if (_PyWideStringList_Copy(&config_argv, &slice) < 0) {
            return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("memory allocation failed")};
        }
    }
    ;
    wchar_t *arg0 = ((void *)0);
    if (config->run_command != ((void *)0)) {
        arg0 = L"-c";
    } else if (config->run_module != ((void *)0)) {
        arg0 = L"-m";
    }
    if (arg0 != ((void *)0)) {
        arg0 = _PyMem_RawWcsdup(arg0);
        if (arg0 == ((void *)0)) {
            _PyWideStringList_Clear(&config_argv);
            return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("memory allocation failed")};
        }
        PyMem_RawFree(config_argv.items[0]);
        config_argv.items[0] = arg0;
    }
    _PyWideStringList_Clear(&config->argv);
    ;
    return (PyStatus){._type = _PyStatus_TYPE_OK};
}


static PyStatus core_read_precmdline (PyConfig *config, _PyPreCmdline *precmdline){
    PyStatus status;
    if (config->parse_argv == 1) {
        if (_PyWideStringList_Copy(&precmdline->argv, &config->argv) < 0) {
            return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("memory allocation failed")};
        }
    }
    PyPreConfig preconfig;
    status = _PyPreConfig_InitFromPreConfig(&preconfig, &_PyRuntime.preconfig);
    if ((status._type != _PyStatus_TYPE_OK)) {
        return status;
    }
    ;
    status = _PyPreCmdline_Read(precmdline, &preconfig);
    if ((status._type != _PyStatus_TYPE_OK)) {
        return status;
    }
    status = _PyPreCmdline_SetConfig(precmdline, config);
    if ((status._type != _PyStatus_TYPE_OK)) {
        return status;
    }
    return (PyStatus){._type = _PyStatus_TYPE_OK};
}


static PyStatus config_run_filename_abspath (PyConfig *config){
    if (!config->run_filename) {
        return (PyStatus){._type = _PyStatus_TYPE_OK};
    }
    if (_Py_isabs(config->run_filename)) {
        return (PyStatus){._type = _PyStatus_TYPE_OK};
    }
    wchar_t *abs_filename;
    if (_Py_abspath(config->run_filename, &abs_filename) < 0) {
        return (PyStatus){._type = _PyStatus_TYPE_OK};
    }
    if (abs_filename == ((void *)0)) {
        return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("memory allocation failed")};
    }
    ;
    config->run_filename = abs_filename;
    return (PyStatus){._type = _PyStatus_TYPE_OK};
}


static PyStatus config_read_cmdline (PyConfig *config){
    PyStatus status;
    PyWideStringList cmdline_warnoptions = (PyWideStringList){.length = 0, .items = ((void *)0)};
    PyWideStringList env_warnoptions = (PyWideStringList){.length = 0, .items = ((void *)0)};
    PyWideStringList sys_warnoptions = (PyWideStringList){.length = 0, .items = ((void *)0)};
    if (config->parse_argv < 0) {
        config->parse_argv = 1;
    }
    if (config->program_name == ((void *)0)) {
        status = config_init_program_name(config);
        if ((status._type != _PyStatus_TYPE_OK)) {
            return status;
        }
    }
    if (config->parse_argv == 1) {
        Py_ssize_t opt_index;
        status = config_parse_cmdline(config, &cmdline_warnoptions, &opt_index);
        if ((status._type != _PyStatus_TYPE_OK)) {
            goto done;
        }
        status = config_run_filename_abspath(config);
        if ((status._type != _PyStatus_TYPE_OK)) {
            goto done;
        }
        status = config_update_argv(config, opt_index);
        if ((status._type != _PyStatus_TYPE_OK)) {
            goto done;
        }
    } else {
        status = config_run_filename_abspath(config);
        if ((status._type != _PyStatus_TYPE_OK)) {
            goto done;
        }
    }
    if (config->use_environment) {
        status = config_init_env_warnoptions(config, &env_warnoptions);
        if ((status._type != _PyStatus_TYPE_OK)) {
            goto done;
        }
    }
    status = _PySys_ReadPreinitWarnOptions(&sys_warnoptions);
    if ((status._type != _PyStatus_TYPE_OK)) {
        goto done;
    }
    status = config_init_warnoptions(config, &cmdline_warnoptions, &env_warnoptions, &sys_warnoptions);
    if ((status._type != _PyStatus_TYPE_OK)) {
        goto done;
    }
    status = (PyStatus){._type = _PyStatus_TYPE_OK};
  done:
    _PyWideStringList_Clear(&cmdline_warnoptions);
    _PyWideStringList_Clear(&env_warnoptions);
    _PyWideStringList_Clear(&sys_warnoptions);
    return status;
}


extern PyStatus _PyConfig_Read (PyConfig *config, int compute_path_config){
    PyStatus status;
    status = _Py_PreInitializeFromConfig(config, ((void *)0));
    if ((status._type != _PyStatus_TYPE_OK)) {
        return status;
    }
    config_get_global_vars(config);
    if (config->orig_argv.length == 0 && !(config->argv.length == 1 && wcscmp(config->argv.items[0], L"") == 0)) {
        if (_PyWideStringList_Copy(&config->orig_argv, &config->argv) < 0) {
            return (PyStatus){._type = _PyStatus_TYPE_ERROR, .func = __func__, .err_msg = ("memory allocation failed")};
        }
    }
    _PyPreCmdline precmdline = (_PyPreCmdline){.use_environment = -1, .isolated = -1, .dev_mode = -1};
    status = core_read_precmdline(config, &precmdline);
    if ((status._type != _PyStatus_TYPE_OK)) {
        goto done;
    }
    ;
    if (config->isolated) {
        config->use_environment = 0;
        config->user_site_directory = 0;
    }
    status = config_read_cmdline(config);
    if ((status._type != _PyStatus_TYPE_OK)) {
        goto done;
    }
    status = _PySys_ReadPreinitXOptions(config);
    if ((status._type != _PyStatus_TYPE_OK)) {
        goto done;
    }
    status = config_read(config, compute_path_config);
    ;
    ;
  done:
    ;
    return status;
}


extern  __attribute__((visibility("default"))) PyStatus PyConfig_Read (PyConfig *config){
    return _PyConfig_Read(config, 1);
}


