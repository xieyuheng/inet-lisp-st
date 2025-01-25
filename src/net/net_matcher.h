#pragma once

struct net_matcher_t {
    const net_pattern_t *net_pattern;
    hash_t *wire_hash;
    set_t *node_set;
    list_t *principle_name_list;
};

net_matcher_t *net_matcher_new(const net_pattern_t *net_pattern);
