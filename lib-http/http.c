#include "http.h"
#include "stdio.h"
#include "connection.h"
#include "string.h"
#include "headers.h"

char* simple_http_get(Uri uri, Header *headers) {
    net_connection_info con;
    net_connect(&con, uri.host, uri.port);

    char package[256];

    sprintf(package, "GET %s HTTP/1.0\r\n%s\r\n", uri.path, headers_format_rfc(headers));
    printf("::HTTP package len: %zu, content: \n%s\n", strlen(package), package);

    net_wrtie(con, package);

    printf("::HTTP reading package...\n");
    char *resp = net_read(con);

    net_close(con);
    return resp;
}



