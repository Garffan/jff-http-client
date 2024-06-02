#include "connection.h"
#include <stdio.h>
#include "stdlib.h"
#include <sys/socket.h>
#include <netdb.h>
#include "netinet/in.h"
#include "arpa/inet.h"
#include "string.h"
#include "unistd.h"

void net_connect(net_connection_info *con, const char* server_host, uint32_t port) {
    struct addrinfo hints, *res;
    con->socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (con->socket_fd < 0) {
        printf("Can't create socket\n");
        return;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    int rc = inet_pton(AF_INET, server_host, &server_addr.sin_addr.s_addr);
    if (rc != -1) {
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_flags = AI_ALL;
        rc = getaddrinfo(server_host, NULL, &hints, &res);
        if (rc != 0) {
            printf("Host not found %s\n", server_host);
            perror("getaddrinfo() failed \n");
            return;
        }

        memcpy(&server_addr.sin_addr.s_addr, (&((struct sockaddr_in *)(res->ai_addr))->sin_addr), sizeof (server_addr.sin_addr));
        freeaddrinfo(res);
    }

    rc = connect(con->socket_fd, (struct sockaddr *)&server_addr, sizeof (server_addr));
    if (rc < 0) {
        perror("connect() failed\n");
        return;
    }
}

void net_wrtie(net_connection_info con, const char* msg) {
    size_t len = strlen(msg);
    int rc = send(con.socket_fd, msg, len, 0);
    if (rc < 0) {
        perror("::NET send() failed\n");
        return;
    }

    printf("::NET sent %d\n", rc);
}

char* net_read(net_connection_info con) {
    ssize_t BUFFER_LENGTH = 1024, bytesRecv = 0;
    char* buf = (char*)malloc(BUFFER_LENGTH * sizeof(char));
    while (1) {
        printf("trying recv() ...\n");
        ssize_t rc = recvfrom(con.socket_fd, &buf[bytesRecv], BUFFER_LENGTH - bytesRecv, 0, NULL, NULL);

        if (rc < 0) {
            printf("recv() failed %ld\n", rc);
            free(buf);
            return NULL;
        }

        if (rc == 0) {
            printf("::NET server closed conenction\n");
            return buf;
        }

        if (bytesRecv + rc > BUFFER_LENGTH - 100) {
            BUFFER_LENGTH *= 2;
            char* p_buf = buf;
            buf = (char *)realloc(buf, BUFFER_LENGTH * sizeof(char));
            if (buf == NULL) {
                printf("not enough memory\n");
                free(p_buf);
                return NULL;
            }
        }

        bytesRecv += rc;

    }


    return buf;
}

void net_close(net_connection_info con) {
    close(con.socket_fd);
}