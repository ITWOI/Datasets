#include "header_func.h"
static int is_numeric (const char *str){
    for (; *str; str++)
        if (!((*__ctype_b_loc())[(int)((*str))] & (unsigned short)_ISdigit))
            return 0;
    return 1;
}
extern int main (int argc, char *argv[]){
    int mode = 1;
    char *input = ((void *)0), *output = ((void *)0);
    char *f1 = ((void *)0), *f2 = ((void *)0);
    int force = 0;
    int force_stdstreams = 0, workers = 0, batch = 0, verbose = 0;
    u32 block_size = ((16) * 1024 * 1024);
    const char *short_options = "Bb:cdefhj:krtvVz";
    static struct option long_options[] = {{"encode", 0, 0, 'e'}, {"decode", 0, 0, 'd'}, {"test", 0, 0, 't'}, {"stdout", 0, 0, 'c'}, {"force", 0, 0, 'f'}, {"recover", 0, 0, 'r'}, {"help", 0, 0, 'h'}, {"keep", 0, 0, 'k'}, {"version", 0, 0, 'V'}, {"verbose", 0, 0, 'v'}, {"block", 1, 0, 'b'}, {"batch", 0, 0, 'B'}, {"jobs", 1, 0, 'j'}, {0, 0, 0, 0}};
    while (1)
        {
            int option_index = 0;
            int c = getopt_long(argc, argv, short_options, long_options, &option_index);
            if (c == -1)
                break;
            switch (c) {
              case '?':
                ;
                return 1;
              case 'e':
              case 'z':
                mode = 1;
                break;
              case 'd':
                mode = 0;
                break;
              case 'r':
                mode = 3;
                break;
              case 't':
                mode = 2;
                break;
              case 'c':
                force_stdstreams = 1;
                break;
              case 'f':
                force = 1;
                break;
              case 'k':
                break;
              case 'h':
                ;
                return 0;
              case 'V':
                ;
                return 0;
              case 'B':
                batch = 1;
                break;
              case 'v':
                verbose = 1;
                break;
              case 'b':
                if (!is_numeric(optarg)) {
                    ;
                    return 1;
                }
                block_size = ((atoi(optarg)) * 1024 * 1024);
                break;
              case 'j':
                if (!is_numeric(optarg)) {
                    ;
                    return 1;
                }
                workers = atoi(optarg);
                break;
            }
        }
    if (block_size < ((65) * 1024) || block_size > ((511) * 1024 * 1024)) {
        ;
        return 1;
    }
    if (batch) {
        return 0;
    }
    while (optind < argc)
        {
            char *arg = argv[optind++];
            if (f1 != ((void *)0) && f2 != ((void *)0)) {
                ;
                return 1;
            }
            if (f1 == ((void *)0)) {
                f1 = arg;
            } else
                f2 = arg;
        }
    if (f1 == ((void *)0) && f2 == ((void *)0)) {
        ;
    } else if (mode == 2) {
        ;
    } else {
        if (mode == 1) {
        } else if (mode == 0 || mode == 3) {
            if (f2 == ((void *)0)) {
                input = f1;
                if (force_stdstreams) {
                    ;
                } else {
                    output = malloc(strlen(f1) + 1);
                    strcpy(output, f1);
                    if (strlen(output) > 4 && !strcmp(output + strlen(output) - 4, ".bz3")) {
                        ;
                    } else {
                        fprintf(stderr, "Warning: file %s has an unknown extension, skipping.\n", f1);
                        return 1;
                    }
                }
            } else {
                ;
            }
        }
    }
    FILE *input_des, *output_des;
    int r;
    return r;
}
