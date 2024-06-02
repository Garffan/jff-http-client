#include <stdio.h>
#include "lib-http/http.h"
#include "lib-http/string-builder.h"

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

    Header headers;
    HeaderValue header_value;
    jff_string str;

    headers_init(&headers);

    jff_string_init(&str);

    // Generate Host line
    jff_string_append(&str, uri.host);
    jff_string_append(&str, ":");
    jff_string_append_int(&str, uri.port);

    // set HOST container
    header_value.entity_type = value_type_string;
    header_value.data = jff_string_clone(str);
    header_value.entity_size = str.len * sizeof(char);

    headers_set(&headers, "Host", header_value);

    jff_string_cleanup(&str);

    jff_string_append(&str, "*/*");

    header_value.entity_type = value_type_string;
    header_value.data = jff_string_clone(str);
    header_value.entity_size = str.len * sizeof(char);

    headers_set(&headers, "accept", header_value);

    char* resp = simple_http_get(uri, &headers);
    printf("GET %s:%d%s response: \n", uri.host, uri.port, uri.path);
    printf("%s\n", resp);
}
