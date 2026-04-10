#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
struct _object;//insertRecordDeclare 

/*TD*/typedef struct _object PyObject;

/*TD*/typedef ssize_t Py_ssize_t;

struct _typeobject;//insertRecordDeclare 

/*TD*/typedef struct _typeobject PyTypeObject;


struct _object {
    Py_ssize_t ob_refcnt;
    PyTypeObject *ob_type;
};


/*Ano*/typedef struct {
    PyObject *attrib;
    Py_ssize_t length;
    Py_ssize_t allocated;
    PyObject **children;
    PyObject *_children[4];
} ElementObjectExtra;


/*Ano*/typedef struct {
    PyObject ob_base;
    PyObject *tag;
    PyObject *text;
    PyObject *tail;
    ElementObjectExtra *extra;
    PyObject *weakreflist;
} ElementObject;


/*Ano*/typedef struct {
    PyObject ob_base;
    Py_ssize_t ob_size;
} PyVarObject;


/*Ano*/typedef struct {
    PyVarObject ob_base;
    PyObject **ob_item;
    Py_ssize_t allocated;
} PyListObject;

#endif