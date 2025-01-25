#include "index.h"

def_t *
def_function(function_def_t *function_def) {
    def_t *self = new(def_t);
    self->kind = DEF_FUNCTION;
    self->function_def = function_def;
    return self;
}

def_t *
def_node(node_ctor_t *node_ctor) {
    def_t *self = new(def_t);
    self->kind = DEF_NODE;
    self->node_ctor = node_ctor;
    return self;
}

void
def_destroy(def_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        def_t *self = *self_pointer;

        switch (self->kind) {
        case DEF_FUNCTION: {
            function_def_destroy(&self->function_def);
            break;
        }

        case DEF_NODE: {
            node_ctor_destroy(&self->node_ctor);
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
        return def->function_def->function->name;
    }

    case DEF_NODE: {
        return def->node_ctor->name;
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
        fprintf(file, "define %s ", def->function_def->function->name);
        function_print(def->function_def->function, file);
        return;
    }

    case DEF_NODE: {
        fprintf(file, "define-node %s ", def->node_ctor->name);
        for (size_t i = 0; i < def->node_ctor->arity; i++) {
            port_info_t *port_info = def->node_ctor->port_infos[i];
            if (port_info->is_principal) {
                fprintf(file, "%s! ", port_info->name);
            } else {
                fprintf(file, "%s ", port_info->name);
            }
        }

        return;
    }
    }
}
