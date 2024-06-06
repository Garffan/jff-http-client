#ifndef HTTP_CLIENT_HEADERS_H
#define HTTP_CLIENT_HEADERS_H
#include "stddef.h"
#include "option.h"

typedef enum {
    value_type_int = 1,
    value_type_string = 2
} value_type;

typedef struct {
    void* data;
    size_t entity_size;
    value_type entity_type;
} HeaderValue;

void header_value_update(HeaderValue* hv, void* data, value_type type, size_t entity_size);

typedef struct {
    char* key;
    HeaderValue value;
    struct Header *next;
} Header;

#ifndef CG_HEADER_VALUE
#define CG_HEADER_VALUE 1
DEFINE_OPTION(HeaderValue);
#endif

void headers_init(Header *lst);
OptionHeaderValue headers_get(Header *lst, const char* key);
void headers_set(Header *lst, const char* key, HeaderValue val);
char* headers_format_rfc(Header* lst);


#endif //HTTP_CLIENT_HEADERS_H
