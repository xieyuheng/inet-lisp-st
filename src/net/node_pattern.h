#pragma once

struct node_pattern_t {
    const node_ctor_t *ctor;
    port_info_t **port_infos;
};

node_pattern_t *node_pattern_new(const node_ctor_t *ctor);
void node_pattern_destroy(node_pattern_t **self_pointer);

bool node_pattern_has_principle_name(node_pattern_t *self, const char *name);
