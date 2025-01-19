#pragma once

typedef enum {
    STMT_DEFINE_FUNCTION,
    STMT_DEFINE_NODE,
    STMT_DEFINE_RULE,
} stmt_kind_t;


struct stmt_t {
    stmt_kind_t kind;
    union {
        struct { char *name; list_t *arg_name_list; list_t *exp_list; } define_function;
        struct { char *name; list_t *port_name_list; } define_node;
    };
};

stmt_t *stmt_define_function(char *name, list_t *arg_name_list, list_t *exp_list);
stmt_t *stmt_define_node(char *name, list_t *port_name_list);

void stmt_destroy(stmt_t **self_pointer);
