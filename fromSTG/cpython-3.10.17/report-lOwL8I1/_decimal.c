static PyObject * signaldict_repr (PyObject *self){
    DecCondMap *cm;
    const char *n[9];
    const char *b[9];
    int i;
    ;
    for (cm = signal_map , i = 0; cm->name != ((void *)0); cm++ , i++) {
        n[i] = cm->fqname;
        b[i] = (*((PyDecSignalDictObject *)self)->flags) & cm->flag ? "True" : "False";
    }
    return PyUnicode_FromFormat("{<class '%s'>:%s, <class '%s'>:%s, <class '%s'>:%s, <class '%s'>:%s, <class '%s'>:%s, <class '%s'>:%s, <class '%s'>:%s, <class '%s'>:%s, <class '%s'>:%s}", n[0], b[0], n[1], b[1], n[2], b[2], n[3], b[3], n[4], b[4], n[5], b[5], n[6], b[6], n[7], b[7], n[8], b[8]);
}


