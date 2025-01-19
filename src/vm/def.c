#include "index.h"

def_t *
def_function(function_def_t *function_def) {
    def_t *self = new(def_t);
    self->kind = DEF_FUNCTION;
    self->function = function_def;
    return self;
}

def_t *
def_node(node_def_t *node_def) {
    def_t *self = new(def_t);
    self->kind = DEF_NODE;
    self->node = node_def;
    return self;
}


void
def_destroy(def_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        def_t *self = *self_pointer;

        switch (self->kind) {
        case DEF_FUNCTION: {
            function_def_destroy(&self->function);
            break;
        }

        case DEF_NODE: {
            node_def_destroy(&self->node);
            break;
        }
        }

        free(self);
        *self_pointer = NULL;
    }
}

const char *
def_name(const def_t *def) {
    switch (def->kind) {
    case DEF_FUNCTION: {
        return def->function->name;
    }

    case DEF_NODE: {
        return def->node->name;
    }
    }

    assert(false);
}

const char *
def_kind_name(def_kind_t kind) {
    switch (kind) {
    case DEF_FUNCTION: {
        return "function";
    }

    case DEF_NODE: {
        return "node";
    }
    }

    assert(false);
}

void
def_print(const def_t *def, file_t *file) {
    switch (def->kind) {
    case DEF_FUNCTION: {
        fprintf(file, "define %s ", def->function->name);
        function_print(def->function->function, file);
        return;
    }

    case DEF_NODE: {
        fprintf(file, "define-node %s ", def->node->name);
        for (port_index_t i = 0; i < def->node->arity; i++) {
            port_def_t *port_def = def->node->port_defs[i];
            if (port_def->is_principal) {
                fprintf(file, "%s! ", port_def->name);
            } else {
                fprintf(file, "%s ", port_def->name);
            }
        }

        return;
    }
    }
}
