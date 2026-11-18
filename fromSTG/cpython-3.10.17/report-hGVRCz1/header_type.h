#ifndef __HEADER_TYPE_H__ 
#define __HEADER_TYPE_H__
#include"../common.h" 
/*TD*/typedef int64_t mpd_ssize_t;

/*TD*/typedef uint64_t mpd_uint_t;

struct mpd_t;//insertRecordDeclare 

/*TD*/typedef struct mpd_t mpd_t;


struct mpd_t {
    uint8_t flags;
    mpd_ssize_t exp;
    mpd_ssize_t digits;
    mpd_ssize_t len;
    mpd_ssize_t alloc;
    mpd_uint_t *data;
};

/*TD*/typedef size_t mpd_size_t;

struct mpd_spec_t;//insertRecordDeclare 

/*TD*/typedef struct mpd_spec_t mpd_spec_t;


struct mpd_spec_t {
    mpd_ssize_t min_width;
    mpd_ssize_t prec;
    char type;
    char align;
    char sign;
    char fill[5];
    const char *dot;
    const char *sep;
    const char *grouping;
};

struct lconv;//insertRecordDeclare 


/*Ano*/typedef struct {
    mpd_ssize_t nbytes;
    mpd_ssize_t nchars;
    mpd_ssize_t cur;
    char *data;
} mpd_mbstr_t;

struct mpd_context_t;//insertRecordDeclare 

/*TD*/typedef struct mpd_context_t mpd_context_t;

#endif