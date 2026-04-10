#include "header_func.h"
static inline int connConnect (connection *conn, const char *addr, int port, const char *src_addr, ConnectionCallbackFunc connect_handler){
    return conn->type->connect(conn, addr, port, src_addr, connect_handler);
}
static inline void connClose (connection *conn){
    conn->type->close(conn);
}
static inline int connAddr (connection *conn, char *ip, size_t ip_len, int *port, int remote){
    if (conn && conn->type->addr) {
        return conn->type->addr(conn, ip, ip_len, port, remote);
    }
    return -1;
}
static inline int connAddrPeerName (connection *conn, char *ip, size_t ip_len, int *port){
    return connAddr(conn, ip, ip_len, port, 1);
}
static inline connection * connCreate (struct aeEventLoop *el, ConnectionType *ct){
    return ct->conn_create(el);
}
