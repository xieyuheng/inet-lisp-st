#include "index.h"

net_pattern_t *
net_pattern_new(void) {
    net_pattern_t *self = new(net_pattern_t);
    self->node_pattern_list = node_pattern_list_new();
    return self;
}
