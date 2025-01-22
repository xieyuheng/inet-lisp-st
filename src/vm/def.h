#pragma once

typedef enum {
    DEF_FUNCTION,
    DEF_NODE,
} def_kind_t;

struct def_t {
    def_kind_t kind;
    union {
        function_def_t *function_def;
        node_def_t *node_def;
    };
};

def_t *def_function(function_def_t *function_def);
def_t *def_node(node_def_t *node_def);

void def_destroy(def_t **self_pointer);

const char *def_name(const def_t *self);
const char *def_kind_name(def_kind_t kind);

void def_print(const def_t *self, file_t *file);
