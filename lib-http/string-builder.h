#ifndef HTTP_CLIENT_STRING_BUILDER_H
#define HTTP_CLIENT_STRING_BUILDER_H
#include "stddef.h"
#include "stdint.h"

#define JFF_STRING_INITIAL_LEN 100

typedef struct {
    char* buffer;
    size_t len;
    size_t cap;
} jff_string;

void jff_string_init(jff_string *str);
void jff_string_append(jff_string *str, const char* s);
void jff_string_append_int(jff_string *str, uint32_t num);

char* jff_string_clone(jff_string str);
void jff_string_cleanup(jff_string *str);
void jff_string_destroy(jff_string *str);

#endif //HTTP_CLIENT_STRING_BUILDER_H
