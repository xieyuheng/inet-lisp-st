#include "index.h"

struct net_pattern_t {
    list_t *node_pattern_list;
    size_t starting_index;
    set_t *local_name_set;
};

static void
init_local_name_set(set_t *local_name_set, list_t *node_pattern_list) {
    node_pattern_t *node_pattern = list_first(node_pattern_list);
    while (node_pattern) {
        for (size_t i = 0; i < node_pattern->ctor->arity; i++) {
            port_info_t *port_info = node_pattern->port_infos[i];
            if (!port_info->is_principal) {
                set_put(local_name_set, port_info->name);
            }
        }

        node_pattern = list_next(node_pattern_list);
    }
}

net_pattern_t *
net_pattern_new(list_t *node_pattern_list, size_t starting_index) {
    net_pattern_t *self = new(net_pattern_t);
    self->node_pattern_list = node_pattern_list;
    self->starting_index = starting_index;
    self->local_name_set = string_set_new();
    init_local_name_set(self->local_name_set, node_pattern_list);
    return self;
}

void
net_pattern_destroy(net_pattern_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        net_pattern_t *self = *self_pointer;
        set_destroy(&self->local_name_set);
        free(self);
        *self_pointer = NULL;
    }
}

size_t
net_pattern_length(const net_pattern_t *self) {
    return list_length(self->node_pattern_list);
}

size_t
net_pattern_starting_index(const net_pattern_t *self) {
    return self->starting_index;
}

node_pattern_t *
net_pattern_get(const net_pattern_t *self, size_t index) {
    return list_get(self->node_pattern_list, index);
}
