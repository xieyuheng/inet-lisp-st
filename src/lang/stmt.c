#include "index.h"

stmt_t *
stmt_define_function(char *name, list_t *arg_name_list, list_t *exp_list) {
    stmt_t *self = new(stmt_t);
    self->kind = STMT_DEFINE_FUNCTION;
    self->define_function.name = name;
    self->define_function.arg_name_list = arg_name_list;
    self->define_function.exp_list = exp_list;
    return self;
}

stmt_t *
stmt_define_node(char *name, list_t *port_name_list) {
    stmt_t *self = new(stmt_t);
    self->kind = STMT_DEFINE_NODE;
    self->define_node.name = name;
    self->define_node.port_name_list = port_name_list;
    return self;
}

stmt_t *
stmt_compute_exp(exp_t *exp) {
    stmt_t *self = new(stmt_t);
    self->kind = STMT_COMPUTE_EXP;
    self->compute_exp.exp = exp;
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
            list_destroy(&self->define_function.exp_list);
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

        case STMT_COMPUTE_EXP: {
            // TODO
            break;
        }
        }

        free(self);
        *self_pointer = NULL;
        return;
    }
}
