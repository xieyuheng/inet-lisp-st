#pragma once

extern object_spec_t node_ctor_object_spec;

struct node_ctor_t {
    object_spec_t *spec;
    char *name;
    size_t arity;
    port_info_t **port_infos;
};

node_ctor_t *node_ctor_new(const char *name, size_t arity);
void node_ctor_destroy(node_ctor_t **self_pointer);

size_t node_ctor_find_port_index(const node_ctor_t *node_ctor, const char *port_name);
