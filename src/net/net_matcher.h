#pragma once

struct net_matcher_t {
    const net_pattern_t *net_pattern;
    hash_t *wire_hash;
    set_t *node_set;
    list_t *principle_name_list;
    list_t *matched_principle_name_list;
};

net_matcher_t *net_matcher_new(const net_pattern_t *net_pattern);
void net_matcher_destroy(net_matcher_t **self_pointer);

void matcher_start(net_matcher_t *self, const node_t *node);
