#pragma once

struct net_pattern_t {
    const array_t *node_pattern_array;
};

net_pattern_t *net_pattern_new(const array_t *node_pattern_array);
void net_pattern_destroy(net_pattern_t **self_pointer);
