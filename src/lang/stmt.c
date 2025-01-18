#include "index.h"

stmt_t *
stmt_define_function(char *name) {
    stmt_t *self = new(stmt_t);
    self->kind = STMT_DEFINE_FUNCTION;
    self->define_function.name = name;
    self->define_function.arg_name_list =
        list_new_with((destroy_fn_t *) string_destroy);
    self->define_function.body = exp_list_new();
    return self;
}

stmt_t *
stmt_define_node(char *name) {
    stmt_t *self = new(stmt_t);
    self->kind = STMT_DEFINE_NODE;
    self->define_node.name = name;
    self->define_node.port_name_list =
        list_new_with((destroy_fn_t *) string_destroy);
    return self;
}

void
stmt_destroy(stmt_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        stmt_t *self = *self_pointer;
        switch (self->kind) {
        case STMT_DEFINE_FUNCTION: {
            string_destroy(&self->define_function.name);
            list_destroy(&self->define_function.arg_name_list);
            list_destroy(&self->define_function.body);            
            break;
        }

        case STMT_DEFINE_NODE: {
            string_destroy(&self->define_node.name);
            list_destroy(&self->define_node.port_name_list);
            break;
        }

        case STMT_DEFINE_RULE: {
            // TODO
            break;
        }
        }

        free(self);
        *self_pointer = NULL;
        return;
    }
}
