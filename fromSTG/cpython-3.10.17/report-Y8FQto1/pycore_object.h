#include "header_func.h"
static inline int _PyType_HasFeature (PyTypeObject *type, unsigned long feature){
    return ((type->tp_flags & feature) != 0);
}
