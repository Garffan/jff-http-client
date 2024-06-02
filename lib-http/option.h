#ifndef HTTP_CLIENT_OPTION_H
#define HTTP_CLIENT_OPTION_H
#include "stdio.h"
#include <stdlib.h>

#define DEFINE_OPTION(type)                         \
    typedef enum {                                  \
        NONE,                                       \
        SOME                                        \
    } Option##type##Type;                           \
                                                    \
    typedef struct {                                \
        Option##type##Type type;                    \
        union {                                     \
            type value;                             \
        };                                          \
    } Option##type;                                 \
                                                    \
    static inline Option##type some_##type(type value) {          \
        Option##type opt;                           \
        opt.type = SOME;                            \
        opt.value = value;                          \
        return opt;                                 \
    }                                               \
                                                    \
    static inline Option##type none_##type() {                    \
        Option##type opt;                           \
        opt.type = NONE;                            \
        return opt;                                 \
    }                                               \
                                                    \
    static inline bool is_some_##type(Option##type opt) {         \
        return opt.type == SOME;                    \
    }                                               \
                                                    \
    static inline type unwrap_##type(Option##type opt) {          \
        if (opt.type == SOME) {                     \
            return opt.value;                       \
        } else {                                    \
            fprintf(stderr, "Called unwrap on a none value\n"); \
            exit(1);                                \
        }                                           \
    }

#endif //HTTP_CLIENT_OPTION_H
