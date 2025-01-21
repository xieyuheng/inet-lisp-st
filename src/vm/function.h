#pragma once

extern object_spec_t function_object_spec;

function_t *function_new(size_t arity);
void function_destroy(function_t **self_pointer);

bool is_function(value_t value);
function_t *as_function(value_t value);

size_t function_length(const function_t *self);
void function_add_op(function_t *self, op_t *op);
void function_build(function_t *self);
op_t *function_get_op(const function_t *self, size_t index);

void function_print(const function_t *self, file_t *file);
void function_print_with_cursor(const function_t *self, file_t *file, size_t cursor);
