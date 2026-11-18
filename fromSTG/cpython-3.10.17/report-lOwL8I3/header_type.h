#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct _object;//insertRecordDeclare 

/*TD*/typedef struct _object PyObject;


/*Ano*/typedef struct {
    const char *name;
    const char *fqname;
    uint32_t flag;
    PyObject *ex;
} DecCondMap;

/*TD*/typedef ssize_t Py_ssize_t;

struct _typeobject;//insertRecordDeclare 

/*TD*/typedef struct _typeobject PyTypeObject;


struct _object {
    Py_ssize_t ob_refcnt;
    PyTypeObject *ob_type;
};


/*Ano*/typedef struct {
    PyObject ob_base;
    uint32_t *flags;
} PyDecSignalDictObject;

#endif