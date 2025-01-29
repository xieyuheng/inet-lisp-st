#pragma once

struct function_t {
    object_spec_t *spec;
    char *name;
    size_t arity;
    hash_t *local_index_hash;
    list_t *op_list;
    size_t length;
    op_t **ops;
};

extern object_spec_t function_object_spec;

function_t *function_new(size_t arity);
void function_destroy(function_t **self_pointer);

bool is_function(value_t value);
function_t *as_function(value_t value);

void function_add_op(function_t *self, op_t *op);
void function_build(function_t *self);
op_t *function_get_op(const function_t *self, size_t index);

void function_print(const function_t *self, file_t *file);
void function_print_with_cursor(const function_t *self, file_t *file, size_t cursor);
