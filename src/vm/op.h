#pragma once

typedef enum {
    OP_APPLY,
    OP_LITERAL,
    OP_GET_VARIABLE,
    OP_SET_VARIABLE,
} op_kind_t;

struct op_t {
    op_kind_t kind;
    union {
        struct { size_t arity; } apply;
        struct { value_t value; } literal;
        struct { size_t index; } get_variable;
        struct { size_t index; } set_variable;
    };
};

op_t *op_apply(size_t arity);
op_t *op_literal(value_t value);
op_t *op_get_variable(size_t index);
op_t *op_set_variable(size_t index);

void op_destroy(op_t **self_pointer);

void op_print(const op_t *self, file_t *file);
