#ifndef HTTP_CLIENT_HTTP_H
#define HTTP_CLIENT_HTTP_H
#include "stdint.h"
#include "headers.h"

typedef struct {
    char* host;
    char* path;
    uint16_t port;
} Uri;

char* simple_http_get(Uri uri, Header* headers);

#endif //HTTP_CLIENT_HTTP_H
