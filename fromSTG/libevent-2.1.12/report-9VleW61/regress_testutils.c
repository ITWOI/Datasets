extern int regress_get_socket_port (int fd){
    struct sockaddr_storage ss;
    socklen_t socklen = sizeof (ss);
    if (getsockname(fd, (__SOCKADDR_ARG){(struct sockaddr *)&ss}, &socklen) != 0)
        return -1;
    if (ss.ss_family == 2) {
        return ntohs(((struct sockaddr_in *)&ss)->sin_port);
    } else {
        ;
    }
}


extern struct evdns_server_port * regress_get_dnsserver (struct event_base *base, uint16_t *portnum, int *psock, evdns_request_callback_fn_type cb, void *arg){
    struct evdns_server_port *port = ((void *)0);
    int sock;
    struct sockaddr_in my_addr;
    sock = socket(2, SOCK_DGRAM, 0);
    if (sock < 0) {
        ;
    }
    ;
    memset(&my_addr, 0, sizeof (my_addr));
    my_addr.sin_family = 2;
    my_addr.sin_port = htons(*portnum);
    my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (bind(sock, (__CONST_SOCKADDR_ARG){(struct sockaddr *)&my_addr}, sizeof (my_addr)) < 0) {
        ;
        ;
    }
    port = evdns_add_server_port_with_base(base, sock, 0, cb, arg);
    if (!*portnum)
        *portnum = regress_get_socket_port(sock);
    ;
    return port;
  end:
    ;
}


extern int regress_dnsserver (struct event_base *base, uint16_t *port, struct regress_dns_server_table *search_table){
    dns_port = regress_get_dnsserver(base, port, &dns_sock, regress_dns_server_cb, search_table);
    return dns_port != ((void *)0);
}


