#include "index.h"

net_matcher_t *
net_matcher_new(const net_pattern_t *net_pattern) {
    net_matcher_t *self = new(net_matcher_t);
    self->net_pattern = net_pattern;
    self->wire_hash = hash_of_string_key();
    self->node_set = set_new();
    self->principle_name_list = string_list_new();
    return self;
}
