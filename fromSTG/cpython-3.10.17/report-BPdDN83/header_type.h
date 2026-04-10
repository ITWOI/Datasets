#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct _object;//insertRecordDeclare 

/*TD*/typedef struct _object PyObject;

/*TD*/typedef ssize_t Py_ssize_t;


/*Ano*/typedef struct {
    const char *function_name;
    const char *argument_name;
    int nullable;
    int allow_fd;
    const wchar_t *wide;
    const char *narrow;
    int fd;
    Py_ssize_t length;
    PyObject *object;
    PyObject *cleanup;
} path_t;

struct _ts;//insertRecordDeclare 

/*TD*/typedef struct _ts PyThreadState;

struct _typeobject;//insertRecordDeclare 

/*TD*/typedef struct _typeobject PyTypeObject;


struct _object {
    Py_ssize_t ob_refcnt;
    PyTypeObject *ob_type;
};

#endif