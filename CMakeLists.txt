cmake_minimum_required(VERSION 3.28)
project(http_client C)

set(CMAKE_C_STANDARD 23)

add_executable(http_client main.c
        lib-http/connection.c
        lib-http/connection.h
        lib-http/http.c
        lib-http/http.h
        lib-http/headers.c
        lib-http/headers.h
        lib-http/option.h
        lib-http/string-builder.c
        lib-http/string-builder.h
)
