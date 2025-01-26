#include "index.h"

struct net_pattern_t {
    const list_t *node_pattern_list;
    size_t starting_index;
};

net_pattern_t *
net_pattern_new(const list_t *node_pattern_list, size_t starting_index) {
    net_pattern_t *self = new(net_pattern_t);
    self->node_pattern_list = node_pattern_list;
    self->starting_index = starting_index;
    return self;
}

void
net_pattern_destroy(net_pattern_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        net_pattern_t *self = *self_pointer;
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
