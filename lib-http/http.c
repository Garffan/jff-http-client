#include "http.h"
#include "stdio.h"
#include "connection.h"
#include "string.h"

char* simple_http_get(Uri uri) {
    // подключаемся к серверу
    net_connection_info con;
    net_connect(&con, uri.host, uri.port);

    // формируем пакет по стандарту http
    char package[256];
    sprintf(package, "GET %s HTTP/1.1\r\nHost: %s:%d\r\nAccept: */*\r\n\r\n", uri.path, uri.host, uri.port);
    printf("::HTTP package len: %zu, content: \n%s\n", strlen(package), package);

    // отправляем пакет по сети серверу
    net_wrtie(con, package);

    // ждём ответ от сервера
    printf("::HTTP reading package...\n");
    char *resp = net_read(con);

    // отключаемся
    net_close(con);
    return resp;
}



