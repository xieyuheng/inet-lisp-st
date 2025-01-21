#include "index.h"

op_t *
op_apply(const def_t *def, size_t arity) {
    op_t *self = new(op_t);
    self->kind = OP_APPLY;
    self->apply.def = def;
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
op_local_get(size_t index) {
    op_t *self = new(op_t);
    self->kind = OP_LOCAL_GET;
    self->local_get.index = index;
    return self;
}

op_t *
op_local_set(size_t index) {
    op_t *self = new(op_t);
    self->kind = OP_LOCAL_SET;
    self->local_set.index = index;
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

        case OP_LOCAL_GET: {
            break;
        }

        case OP_LOCAL_SET: {
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
        fprintf(file, "APPLY %s", def_name(op->apply.def));
        return;
    }

    case OP_LITERAL: {
        fprintf(file, "LITERAL ");
        value_print(op->literal.value, file);
        return;
    }

    case OP_LOCAL_GET: {
        fprintf(file, "LOCAL-GET %ld", op->local_get.index);
        return;
    }

    case OP_LOCAL_SET: {
        fprintf(file, "LOCAL-SET %ld", op->local_set.index);
        return;
    }
    }
}
