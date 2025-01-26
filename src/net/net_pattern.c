#include "index.h"

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

list_t *
net_pattern_list_new(void) {
    return list_new_with((destroy_fn_t *) net_pattern_destroy);
}
