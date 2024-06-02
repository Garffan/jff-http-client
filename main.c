#include <stdio.h>
#include "lib-http/http.h"

void test(const char* host, const char* path, uint16_t port);

int main(int argc, char **argv) {
    if (argc < 4) {
        perror("not enough params, pass host, path and port\n");
        return 1;
    }


    char host[256], path[256];
    uint16_t port;

    sscanf(argv[1], "%s", host);
    sscanf(argv[2], "%s", path);
    sscanf(argv[3], "%du", &port);

    printf("passed %s %s %d\n", host, path, port);

    test(host, path, port);

    return 0;
}

void test(const char* host, const char* path, uint16_t port) {
    Uri uri = {
        .host = host,
        .path = path,
        .port = port
    };

    printf("GET %s:%d%s... \n", uri.host, uri.port, uri.path);
    char* resp = simple_http_get(uri);
    printf("GET %s:%d%s response: \n", uri.host, uri.port, uri.path);
    printf("%s\n", resp);
}
