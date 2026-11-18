extern int anetFdToString (int fd, char *ip, size_t ip_len, int *port, int remote){
    struct sockaddr_storage sa;
    socklen_t salen = sizeof (sa);
    if (remote) {
        if (getpeername(fd, (__SOCKADDR_ARG){(struct sockaddr *)&sa}, &salen) == -1)
            goto error;
        ;
    } else {
        if (getsockname(fd, (__SOCKADDR_ARG){(struct sockaddr *)&sa}, &salen) == -1)
            goto error;
        ;
    }
    if (sa.ss_family == 2) {
        struct sockaddr_in *s;
        ;
    } else {
        ;
    }
    return 0;
  error:
    ;
    return -1;
}


