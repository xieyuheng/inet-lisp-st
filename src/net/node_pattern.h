#pragma once

struct node_pattern_t {
    const node_ctor_t *ctor;
    array_t *port_info_array;
};

node_pattern_t *node_pattern_new(const node_ctor_t *ctor);
