#include "string-builder.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

void jff_string_init(jff_string *str) {
    if (str == NULL) {
        return;
    }

    str->buffer = (char*) malloc(JFF_STRING_INITIAL_LEN * sizeof(char));
    str->cap = JFF_STRING_INITIAL_LEN;
    str->len = 0;
}

void jff_string_append(jff_string *str, const char* s) {
    if (str == NULL) {
        return;
    }

    size_t len = strlen(s);
    if (str->len + len >= str->cap) {
        str->cap *= 2;
        str->buffer = (char *) realloc(str->buffer, str->cap * sizeof(char));
    }

    strncpy(&str->buffer[str->len], s, len);
    str->len += len;
}

void jff_string_append_int(jff_string *str, uint32_t num) {
    if (str == NULL) {
        return;
    }

    char* buf = (char*)malloc(32 * sizeof(char));
    snprintf(buf, 32, "%d", num);
    jff_string_append(str, buf);
    free(buf);
}

void jff_string_cleanup(jff_string *str) {
    str->len = 0;
    memset(str->buffer, 0, str->cap);
}

char* jff_string_clone(jff_string str) {
    char* new_buf = (char*) malloc(sizeof(char) * str.len);
    strncpy(new_buf, str.buffer, str.len);
    return new_buf;
};

void jff_string_destroy(jff_string *str) {
    if (str == NULL) {
        return;
    }

    free(str->buffer);
    str->buffer = NULL;
}