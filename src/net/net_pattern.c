#include "index.h"

net_pattern_t *
net_pattern_new(void) {
    net_pattern_t *self = new(net_pattern_t);
    self->node_pattern_list = node_pattern_list_new();
    return self;
}

void
net_pattern_destroy(net_pattern_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        net_pattern_t *self = *self_pointer;
        list_destroy(&self->node_pattern_list);
        free(self);
        *self_pointer = NULL;
    }
}
