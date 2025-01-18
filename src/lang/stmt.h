#pragma once

typedef enum {
    STMT_DEFINE_FUNCTION,
    STMT_DEFINE_NODE,
    STMT_DEFINE_RULE,
} stmt_kind_t;


struct stmt_t {
    stmt_kind_t kind;
    union {
        struct { char *name; list_t *arg_name_list; list_t *body; } define_function;
    };
};

stmt_t *stmt_define_function(char *name);
