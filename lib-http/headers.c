#include "headers.h"
#include "string.h"
#include "string-builder.h"

char* int_to_str(uint32_t num);

Header* find_by_key(Header* lst, const char* key) {
    Header *p = lst;

    while(p != NULL) {
        if (strcmp(key, p->key) == 0)  {
            return p;
        }
        p = p->next;
    }

    return NULL;
}

Header* find_last(Header *lst) {
    Header *cur = lst;
    Header *prev = lst;
    while (cur != NULL) {
        prev = cur;
        cur = cur->next;
    }

    return prev;
}

void headers_init(Header *lst) {
    lst->key = NULL;
    lst->next = NULL;
}

OptionHeaderValue headers_get(Header *lst, const char* key) {
    Header *el = find_by_key(lst, key);
    if (el == NULL) {
        return none_HeaderValue();
    }

    return some_HeaderValue(el->value);
}

void headers_set(Header *lst, const char* key, HeaderValue val) {
    Header *el;
    if (lst->key == NULL) {
        el = lst;
        el->key = (char*) malloc(strlen(key) * sizeof(char));
        strcpy(el->key, key);
    } else {
        el = find_by_key(lst, key);
    }
    if (el == NULL) {
        Header *new = (Header *)malloc(sizeof(Header));
        new->next = NULL;
        new->key = (char*) malloc(strlen(key) * sizeof(char));
        strcpy(new->key, key);
        new->value = val;
        Header *last = find_last(lst);
        last->next = new;
        return;
    }

    el->value = val;
}

char* headers_format_rfc(Header* lst) {
    Header *p = lst;
    jff_string headers, line;

    jff_string_init(&headers);
    jff_string_init(&line);

    while (p != NULL) {
        jff_string_append(&line, p->key);
        jff_string_append(&line, ": ");
        if (p->value.entity_type == value_type_string) {
            jff_string_append(&line, (const char*)p->value.data);
        } else if (p->value.entity_type == value_type_int) {
            char* num = int_to_str(*((int32_t*)p->value.data));
            jff_string_append(&line, num);
            free(num);
        }
        jff_string_append(&line, "\r\n");

        jff_string_append(&headers, jff_string_clone(line));

        jff_string_cleanup(&line);
        p = p->next;
    }

    jff_string_destroy(&line);

    return headers.buffer;
}

void header_value_update(HeaderValue* hv, void* data, value_type type, size_t entity_size) {
    if (hv == NULL) {
        return;
    }

    hv->data = data;
    hv->entity_type = type;
    hv->entity_size = entity_size;
}


char* int_to_str(uint32_t num) {
    char *buf = (char *)malloc(32 * sizeof(char));
    snprintf(buf, 32, "%d", num);
    return buf;
}