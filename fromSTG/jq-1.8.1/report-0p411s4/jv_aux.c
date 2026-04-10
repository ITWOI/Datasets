static jv parse_slice (jv j, jv slice, int *pstart, int *pend){
    jv start_jv = jv_object_get(jv_copy(slice), jv_string("start"));
    jv end_jv = jv_object_get(slice, jv_string("end"));
    if (jv_get_kind(start_jv) == JV_KIND_NULL) {
        ;
        start_jv = jv_number(0);
    }
    int len;
    if (jv_get_kind(j) == JV_KIND_ARRAY) {
        len = jv_array_length(j);
    } else if (jv_get_kind(j) == JV_KIND_STRING) {
        len = jv_string_length_codepoints(j);
    } else {
        ;
        ;
        ;
        return jv_invalid_with_msg(jv_string("Only arrays and strings can be sliced"));
    }
    if (jv_get_kind(end_jv) == JV_KIND_NULL) {
        ;
        end_jv = jv_number(len);
    }
    if (jv_get_kind(start_jv) != JV_KIND_NUMBER || jv_get_kind(end_jv) != JV_KIND_NUMBER) {
        ;
        ;
        return jv_invalid_with_msg(jv_string("Array/string slice indices must be integers"));
    }
    double dstart = jv_number_value(start_jv);
    double dend = jv_number_value(end_jv);
    int start, end;
    ;
    ;
    if (__builtin_isnan(dstart))
        dstart = 0;
    if (dstart < 0)
        dstart += len;
    if (dstart < 0)
        dstart = 0;
    if (dstart > len)
        dstart = len;
    start = dstart > 2147483647 ? 2147483647 : (int)dstart;
    if (__builtin_isnan(dend))
        dend = len;
    if (dend < 0)
        dend += len;
    if (dend < 0)
        dend = start;
    end = dend > 2147483647 ? 2147483647 : (int)dend;
    if (end > len)
        end = len;
    if (end < len)
        end += end < dend ? 1 : 0;
    if (end < start)
        end = start;
    ((void)sizeof ((0 <= start && start <= end && end <= len) ? 1 : 0) , __extension__ ({
        if (0 <= start && start <= end && end <= len)
            ;
        else
            __assert_fail("0 <= start && start <= end && end <= len", "src/jv_aux_InstSlice.c", 69, __extension__ __PRETTY_FUNCTION__);
    }));
    *pstart = start;
    *pend = end;
    return jv_true();
}


extern jv jv_get (jv t, jv k){
    jv v;
    if (jv_get_kind(t) == JV_KIND_OBJECT && jv_get_kind(k) == JV_KIND_STRING) {
        v = jv_object_get(t, k);
        if (!jv_is_valid(v)) {
            ;
            v = jv_null();
        }
    } else if (jv_get_kind(t) == JV_KIND_ARRAY && jv_get_kind(k) == JV_KIND_NUMBER) {
        if (jvp_number_is_nan(k)) {
            ;
            v = jv_null();
        } else {
            double didx;
            if (jvp_number_is_nan(k)) {
                v = jv_null();
            } else {
                ;
                ;
                int idx;
                ;
                v = jv_array_get(t, idx);
                if (!jv_is_valid(v)) {
                    ;
                    v = jv_null();
                }
            }
        }
        ;
    } else if (jv_get_kind(t) == JV_KIND_ARRAY && jv_get_kind(k) == JV_KIND_OBJECT) {
        int start, end;
        jv e = parse_slice(jv_copy(t), k, &start, &end);
        if (jv_get_kind(e) == JV_KIND_TRUE) {
            v = jv_array_slice(t, start, end);
        } else {
            ;
            v = e;
        }
    } else if (jv_get_kind(t) == JV_KIND_STRING && jv_get_kind(k) == JV_KIND_OBJECT) {
        int start, end;
        jv e = parse_slice(jv_copy(t), k, &start, &end);
        if (jv_get_kind(e) == JV_KIND_TRUE) {
            v = jv_string_slice(t, start, end);
        } else {
            ;
            v = e;
        }
    } else if (jv_get_kind(t) == JV_KIND_ARRAY && jv_get_kind(k) == JV_KIND_ARRAY) {
        v = jv_array_indexes(t, k);
    } else if (jv_get_kind(t) == JV_KIND_NULL && (jv_get_kind(k) == JV_KIND_STRING || jv_get_kind(k) == JV_KIND_NUMBER || jv_get_kind(k) == JV_KIND_OBJECT)) {
        ;
        ;
        v = jv_null();
    } else {
        if (jv_get_kind(k) == JV_KIND_STRING && jv_string_length_bytes(jv_copy(k)) < 30) {
            v = jv_invalid_with_msg(jv_string_fmt("Cannot index %s with string \"%s\"", jv_kind_name(jv_get_kind(t)), jv_string_value(k)));
        } else {
            v = jv_invalid_with_msg(jv_string_fmt("Cannot index %s with %s", jv_kind_name(jv_get_kind(t)), jv_kind_name(jv_get_kind(k))));
        }
        ;
        ;
    }
    return v;
}


extern jv jv_set (jv t, jv k, jv v){
    if (!jv_is_valid(v)) {
        ;
        ;
        return v;
    }
    int isnull = jv_get_kind(t) == JV_KIND_NULL;
    if (jv_get_kind(k) == JV_KIND_STRING && (jv_get_kind(t) == JV_KIND_OBJECT || isnull)) {
        ;
        ;
    } else if (jv_get_kind(k) == JV_KIND_NUMBER && (jv_get_kind(t) == JV_KIND_ARRAY || isnull)) {
    } else if (jv_get_kind(k) == JV_KIND_OBJECT && (jv_get_kind(t) == JV_KIND_ARRAY || isnull)) {
        if (isnull)
            t = jv_array();
        int start, end;
        jv e = parse_slice(jv_copy(t), k, &start, &end);
        if (jv_get_kind(e) == JV_KIND_TRUE) {
            if (jv_get_kind(v) == JV_KIND_ARRAY) {
                int array_len = jv_array_length(jv_copy(t));
                ((void)sizeof ((0 <= start && start <= end && end <= array_len) ? 1 : 0) , __extension__ ({
                    if (0 <= start && start <= end && end <= array_len)
                        ;
                    else
                        __assert_fail("0 <= start && start <= end && end <= array_len", "src/jv_aux_InstSlice.c", 164, __extension__ __PRETTY_FUNCTION__);
                }));
                int slice_len = end - start;
                int insert_len = jv_array_length(jv_copy(v));
                if (slice_len < insert_len) {
                    int shift;
                    for (int i = array_len - 1; i >= end && jv_is_valid(t); i--) {
                        t = jv_array_set(t, i + shift, jv_array_get(jv_copy(t), i));
                    }
                } else if (slice_len > insert_len) {
                    int shift;
                    for (int i = end; i < array_len && jv_is_valid(t); i++) {
                        t = jv_array_set(t, i - shift, jv_array_get(jv_copy(t), i));
                    }
                    if (jv_is_valid(t))
                        t = jv_array_slice(t, 0, array_len - shift);
                }
                for (int i = 0; i < insert_len && jv_is_valid(t); i++) {
                    t = jv_array_set(t, start + i, jv_array_get(jv_copy(v), i));
                }
                ;
            } else {
                ;
            }
        } else {
            ;
        }
    } else {
        ;
    }
    return t;
}


static jv jv_dels (jv t, jv keys){
    ((void)sizeof ((jv_get_kind(keys) == JV_KIND_ARRAY) ? 1 : 0) , __extension__ ({
        if (jv_get_kind(keys) == JV_KIND_ARRAY)
            ;
        else
            __assert_fail("jv_get_kind(keys) == JV_KIND_ARRAY", "src/jv_aux_InstSlice.c", 196, __extension__ __PRETTY_FUNCTION__);
    }));
    ((void)sizeof ((jv_is_valid(t)) ? 1 : 0) , __extension__ ({
        if (jv_is_valid(t))
            ;
        else
            __assert_fail("jv_is_valid(t)", "src/jv_aux_InstSlice.c", 197, __extension__ __PRETTY_FUNCTION__);
    }));
    if (jv_get_kind(t) == JV_KIND_NULL || jv_array_length(jv_copy(keys)) == 0) {
    } else if (jv_get_kind(t) == JV_KIND_ARRAY) {
        jv neg_keys;
        jv nonneg_keys;
        jv new_array;
        jv starts = jv_array(), ends = jv_array();
        for (int jv_len__ = jv_array_length(jv_copy(keys)), i = 0, jv_j__ = 1; jv_j__; jv_j__ = 0)
            for (jv key; i < jv_len__ ? (key = jv_array_get(jv_copy(keys), i) , 1) : 0; i++) {
                if (jv_get_kind(key) == JV_KIND_NUMBER) {
                    if (jv_number_value(key) < 0) {
                        neg_keys = jv_array_append(neg_keys, key);
                    } else {
                        nonneg_keys = jv_array_append(nonneg_keys, key);
                    }
                } else if (jv_get_kind(key) == JV_KIND_OBJECT) {
                    int start, end;
                    jv e = parse_slice(jv_copy(t), key, &start, &end);
                    if (jv_get_kind(e) == JV_KIND_TRUE) {
                        starts = jv_array_append(starts, jv_number(start));
                        ends = jv_array_append(ends, jv_number(end));
                    } else {
                        jv_free(new_array);
                        jv_free(key);
                        new_array = e;
                        goto arr_out;
                    }
                } else {
                    jv_free(new_array);
                    new_array = jv_invalid_with_msg(jv_string_fmt("Cannot delete %s element of array", jv_kind_name(jv_get_kind(key))));
                    jv_free(key);
                    goto arr_out;
                }
            }
        int neg_idx;
        int nonneg_idx;
        int len;
      arr_out:
        ;
        ;
        ;
        ;
        ;
        ;
    } else if (jv_get_kind(t) == JV_KIND_OBJECT) {
        for (int jv_len__ = jv_array_length(jv_copy(keys)), i = 0, jv_j__ = 1; jv_j__; jv_j__ = 0)
            for (jv k; i < jv_len__ ? (k = jv_array_get(jv_copy(keys), i) , 1) : 0; i++) {
                if (jv_get_kind(k) != JV_KIND_STRING) {
                    jv_free(t);
                    t = jv_invalid_with_msg(jv_string_fmt("Cannot delete %s field of object", jv_kind_name(jv_get_kind(k))));
                    jv_free(k);
                    break;
                }
                t = jv_object_delete(t, k);
            }
    } else {
        ;
    }
    ;
    return t;
}


static jv delpaths_sorted (jv object, jv paths, int start){
    jv delkeys = jv_array();
    for (int i = 0; i < jv_array_length(jv_copy(paths));) {
        int j = i;
        ((void)sizeof ((jv_array_length(jv_array_get(jv_copy(paths), i)) > start) ? 1 : 0) , __extension__ ({
            if (jv_array_length(jv_array_get(jv_copy(paths), i)) > start)
                ;
            else
                __assert_fail("jv_array_length(jv_array_get(jv_copy(paths), i)) > start", "src/jv_aux_InstSlice.c", 271, __extension__ __PRETTY_FUNCTION__);
        }));
        int delkey = jv_array_length(jv_array_get(jv_copy(paths), i)) == start + 1;
        jv key = jv_array_get(jv_array_get(jv_copy(paths), i), start);
        while (j < jv_array_length(jv_copy(paths)) && jv_equal(jv_copy(key), jv_array_get(jv_array_get(jv_copy(paths), j), start)))
            j++;
        if (delkey) {
            delkeys = jv_array_append(delkeys, key);
        } else {
            jv subobject = jv_get(jv_copy(object), jv_copy(key));
            if (!jv_is_valid(subobject)) {
                ;
                ;
                object = subobject;
                break;
            } else if (jv_get_kind(subobject) == JV_KIND_NULL) {
                ;
                ;
            } else {
                jv newsubobject = delpaths_sorted(subobject, jv_array_slice(jv_copy(paths), i, j), start + 1);
                if (!jv_is_valid(newsubobject)) {
                    ;
                    ;
                    object = newsubobject;
                    break;
                }
                object = jv_set(object, key, newsubobject);
            }
            if (!jv_is_valid(object))
                break;
            ;
        }
        i = j;
    }
    ;
    if (jv_is_valid(object)) {
        object = jv_dels(object, delkeys);
    } else {
        ;
    }
    return object;
}


extern jv jv_delpaths (jv object, jv paths){
    if (jv_get_kind(paths) != JV_KIND_ARRAY) {
        ;
        ;
        return jv_invalid_with_msg(jv_string("Paths must be specified as an array"));
    }
    paths = jv_sort(paths, jv_copy(paths));
    for (int jv_len__ = jv_array_length(jv_copy(paths)), i = 0, jv_j__ = 1; jv_j__; jv_j__ = 0)
        for (jv elem; i < jv_len__ ? (elem = jv_array_get(jv_copy(paths), i) , 1) : 0; i++) {
            if (jv_get_kind(elem) != JV_KIND_ARRAY) {
                jv_free(object);
                jv_free(paths);
                jv err = jv_invalid_with_msg(jv_string_fmt("Path must be specified as array, not %s", jv_kind_name(jv_get_kind(elem))));
                jv_free(elem);
                return err;
            }
            jv_free(elem);
        }
    if (jv_array_length(jv_copy(paths)) == 0) {
        ;
        return object;
    }
    if (jv_array_length(jv_array_get(jv_copy(paths), 0)) == 0) {
        ;
        ;
        return jv_null();
    }
    return delpaths_sorted(object, paths, 0);
}


static struct sort_entry * sort_items (jv objects, jv keys){
    ((void)sizeof ((jv_get_kind(objects) == JV_KIND_ARRAY) ? 1 : 0) , __extension__ ({
        if (jv_get_kind(objects) == JV_KIND_ARRAY)
            ;
        else
            __assert_fail("jv_get_kind(objects) == JV_KIND_ARRAY", "src/jv_aux_InstSlice.c", 364, __extension__ __PRETTY_FUNCTION__);
    }));
    ((void)sizeof ((jv_get_kind(keys) == JV_KIND_ARRAY) ? 1 : 0) , __extension__ ({
        if (jv_get_kind(keys) == JV_KIND_ARRAY)
            ;
        else
            __assert_fail("jv_get_kind(keys) == JV_KIND_ARRAY", "src/jv_aux_InstSlice.c", 365, __extension__ __PRETTY_FUNCTION__);
    }));
    ((void)sizeof ((jv_array_length(jv_copy(objects)) == jv_array_length(jv_copy(keys))) ? 1 : 0) , __extension__ ({
        if (jv_array_length(jv_copy(objects)) == jv_array_length(jv_copy(keys)))
            ;
        else
            __assert_fail("jv_array_length(jv_copy(objects)) == jv_array_length(jv_copy(keys))", "src/jv_aux_InstSlice.c", 366, __extension__ __PRETTY_FUNCTION__);
    }));
    int n = jv_array_length(jv_copy(objects));
    if (n == 0) {
        ;
        ;
        return ((void *)0);
    }
    struct sort_entry *entries = jv_mem_calloc(n, sizeof(struct sort_entry));
    for (int i = 0; i < n; i++) {
        ;
        ;
        entries[i].index = i;
    }
    ;
    ;
    ;
    return entries;
}


extern jv jv_sort (jv objects, jv keys){
    ((void)sizeof ((jv_get_kind(objects) == JV_KIND_ARRAY) ? 1 : 0) , __extension__ ({
        if (jv_get_kind(objects) == JV_KIND_ARRAY)
            ;
        else
            __assert_fail("jv_get_kind(objects) == JV_KIND_ARRAY", "src/jv_aux_InstSlice.c", 386, __extension__ __PRETTY_FUNCTION__);
    }));
    ((void)sizeof ((jv_get_kind(keys) == JV_KIND_ARRAY) ? 1 : 0) , __extension__ ({
        if (jv_get_kind(keys) == JV_KIND_ARRAY)
            ;
        else
            __assert_fail("jv_get_kind(keys) == JV_KIND_ARRAY", "src/jv_aux_InstSlice.c", 387, __extension__ __PRETTY_FUNCTION__);
    }));
    ((void)sizeof ((jv_array_length(jv_copy(objects)) == jv_array_length(jv_copy(keys))) ? 1 : 0) , __extension__ ({
        if (jv_array_length(jv_copy(objects)) == jv_array_length(jv_copy(keys)))
            ;
        else
            __assert_fail("jv_array_length(jv_copy(objects)) == jv_array_length(jv_copy(keys))", "src/jv_aux_InstSlice.c", 388, __extension__ __PRETTY_FUNCTION__);
    }));
    int n;
    struct sort_entry *entries = sort_items(objects, keys);
    jv ret;
    ;
    return ret;
}


