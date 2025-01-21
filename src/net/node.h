#pragma once

extern object_spec_t node_object_spec;

struct node_t {
    object_spec_t *spec;
    const node_def_t *def;
    size_t id;
    wire_t **wires;
};

node_t *node_new(const node_def_t *def, size_t id);
void node_destroy(node_t **self_pointer);

bool is_node(value_t value);
node_t *as_node(value_t value);

void node_print(const node_t *self, file_t *file);
