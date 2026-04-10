#ifndef __HEADER_FUNC_H__ 
#define __HEADER_FUNC_H__
#include"header_type.h" 
static inline int connAddr(connection *conn, char *ip, size_t ip_len, int *port, int remote) ;


ConnectionType *connectionTypeTls(void);

static inline int connAddrPeerName(connection *conn, char *ip, size_t ip_len, int *port) ;


client *lookupClientByID(uint64_t id);

int modulePopulateClientInfoStructure(void *ci, client *client, int structver) ;

#endif