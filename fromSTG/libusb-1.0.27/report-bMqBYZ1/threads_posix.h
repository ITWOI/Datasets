#include "header_func.h"
static inline void usbi_mutex_init (usbi_mutex_t *mutex){
    ((void)sizeof ((pthread_mutex_init(mutex, ((void *)0)) == 0) ? 1 : 0) , __extension__ ({
        if (pthread_mutex_init(mutex, ((void *)0)) == 0)
            ;
        else
            __assert_fail("pthread_mutex_init(mutex, ((void*)0)) == 0", "./os/threads_posix.h", 38, __extension__ __PRETTY_FUNCTION__);
    }));
}
static inline void usbi_mutex_lock (usbi_mutex_t *mutex){
    ((void)sizeof ((pthread_mutex_lock(mutex) == 0) ? 1 : 0) , __extension__ ({
        if (pthread_mutex_lock(mutex) == 0)
            ;
        else
            __assert_fail("pthread_mutex_lock(mutex) == 0", "./os/threads_posix.h", 42, __extension__ __PRETTY_FUNCTION__);
    }));
}
static inline void usbi_mutex_unlock (usbi_mutex_t *mutex){
    ((void)sizeof ((pthread_mutex_unlock(mutex) == 0) ? 1 : 0) , __extension__ ({
        if (pthread_mutex_unlock(mutex) == 0)
            ;
        else
            __assert_fail("pthread_mutex_unlock(mutex) == 0", "./os/threads_posix.h", 46, __extension__ __PRETTY_FUNCTION__);
    }));
}
static inline void usbi_mutex_destroy (usbi_mutex_t *mutex){
    ((void)sizeof ((pthread_mutex_destroy(mutex) == 0) ? 1 : 0) , __extension__ ({
        if (pthread_mutex_destroy(mutex) == 0)
            ;
        else
            __assert_fail("pthread_mutex_destroy(mutex) == 0", "./os/threads_posix.h", 52, __extension__ __PRETTY_FUNCTION__);
    }));
}
