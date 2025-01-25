#pragma once

struct net_pattern_t {
    list_t *node_pattern_list;
};

net_pattern_t *net_pattern_new(void);
