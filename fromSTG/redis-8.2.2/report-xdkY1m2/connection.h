#include "header_func.h"
static inline int connAddr (connection *conn, char *ip, size_t ip_len, int *port, int remote){
    if (conn && conn->type->addr) {
        return conn->type->addr(conn, ip, ip_len, port, remote);
    }
    return -1;
}
static inline int connAddrPeerName (connection *conn, char *ip, size_t ip_len, int *port){
    return connAddr(conn, ip, ip_len, port, 1);
}
