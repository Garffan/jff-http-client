#ifndef HTTP_CLIENT_CONNECTION_H
#define HTTP_CLIENT_CONNECTION_H
#include "stdint.h"

typedef struct {
    int socket_fd;
} net_connection_info;

void net_connect(net_connection_info *con, const char* server_host, uint32_t port);
void net_wrtie(net_connection_info con, const char* msg);

char* net_read(net_connection_info con);

void net_close(net_connection_info con);

#endif //HTTP_CLIENT_CONNECTION_H
