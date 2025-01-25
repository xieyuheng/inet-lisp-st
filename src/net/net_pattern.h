#pragma once

struct net_pattern_t {
    const array_t *node_pattern_array;
    size_t starting_index;
};

net_pattern_t *net_pattern_new(const array_t *node_pattern_array, size_t starting_index);
void net_pattern_destroy(net_pattern_t **self_pointer);

node_pattern_t *net_pattern_first(const net_pattern_t *self);
