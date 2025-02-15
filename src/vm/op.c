#include "index.h"

op_t *
op_apply(size_t arity) {
    op_t *self = new(op_t);
    self->kind = OP_APPLY;
    self->apply.arity = arity;
    return self;
}

op_t *
op_literal(value_t value) {
    op_t *self = new(op_t);
    self->kind = OP_LITERAL;
    self->literal.value = value;
    return self;
}

op_t *
op_get_variable(size_t index) {
    op_t *self = new(op_t);
    self->kind = OP_GET_VARIABLE;
    self->get_variable.index = index;
    return self;
}

op_t *
op_set_variable(size_t index) {
    op_t *self = new(op_t);
    self->kind = OP_SET_VARIABLE;
    self->set_variable.index = index;
    return self;
}

op_t *
op_get_linear_variable(size_t index) {
    op_t *self = new(op_t);
    self->kind = OP_GET_LINEAR_VARIABLE;
    self->get_linear_variable.index = index;
    return self;
}

op_t *
op_set_linear_variable(size_t index) {
    op_t *self = new(op_t);
    self->kind = OP_SET_LINEAR_VARIABLE;
    self->set_linear_variable.index = index;
    return self;
}

void
op_destroy(op_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        op_t *self = *self_pointer;
        switch (self->kind) {
        case OP_APPLY: {
            break;
        }

        case OP_LITERAL: {
            break;
        }

        case OP_GET_VARIABLE: {
            break;
        }

        case OP_SET_VARIABLE: {
            break;
        }

        case OP_GET_LINEAR_VARIABLE: {
            break;
        }

        case OP_SET_LINEAR_VARIABLE: {
            break;
        }
        }

        free(self);
        *self_pointer = NULL;
        return;
    }
}

void
op_print(const op_t *op, file_t *file) {
    switch (op->kind) {
    case OP_APPLY: {
        fprintf(file, "(apply %lu)", op->apply.arity);
        return;
    }

    case OP_LITERAL: {
        fprintf(file, "(literal ");
        value_print(op->literal.value, file);
        fprintf(file, ")");
        return;
    }

    case OP_GET_VARIABLE: {
        fprintf(file, "(get-variable %ld)", op->get_variable.index);
        return;
    }

    case OP_SET_VARIABLE: {
        fprintf(file, "(set-variable %ld)", op->set_variable.index);
        return;
    }

    case OP_GET_LINEAR_VARIABLE: {
        fprintf(file, "(get-linear-variable %ld)", op->get_linear_variable.index);
        return;
    }

    case OP_SET_LINEAR_VARIABLE: {
        fprintf(file, "(set-linear-variable %ld)", op->set_linear_variable.index);
        return;
    }
    }
}
