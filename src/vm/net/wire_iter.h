#pragma once

// For a pair of connected wires,
// only one of them will be traversed.

wire_iter_t *wire_iter_new(wire_t *root);
void wire_iter_destroy(wire_iter_t **self_pointer);

value_t wire_iter_first(wire_iter_t *self);
value_t wire_iter_next(wire_iter_t *self);
