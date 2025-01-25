#include "index.h"

net_pattern_t *
net_pattern_new(const array_t *node_pattern_array) {
    net_pattern_t *self = new(net_pattern_t);
    self->node_pattern_array = node_pattern_array;
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
