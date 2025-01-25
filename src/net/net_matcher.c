#include "index.h"

net_matcher_t *
net_matcher_new(const net_pattern_t *net_pattern) {
    net_matcher_t *self = new(net_matcher_t);
    self->net_pattern = net_pattern;
    self->wire_hash = hash_of_string_key();
    self->node_set = set_new();
    self->principle_name_list = string_list_new();
    self->matched_principle_name_list = string_list_new();
    return self;
}

void
net_matcher_destroy(net_matcher_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        net_matcher_t *self = *self_pointer;
        hash_destroy(&self->wire_hash);
        set_destroy(&self->node_set);
        list_destroy(&self->principle_name_list);
        list_destroy(&self->matched_principle_name_list);
        free(self);
        *self_pointer = NULL;
    }
}

static void
matcher_match_node(net_matcher_t *self, const node_pattern_t *node_pattern, const node_t *node) {
    if (node_pattern->ctor != node->ctor) return;

    for (size_t i = 0; i < node->ctor->arity; i++) {
        // port_info_t *port_info = array_get(node_pattern->port_info_array, i);
        // port_info_t *port_info = node_pattern->port_infos[i];
        wire_t *wire = node->wires[i];
        (void) wire;
        // if (port_info->is_principal) {

        // } else {

        // }
    }

    (void) self;
}

static const char *
matcher_next_principle_name(net_matcher_t *self) {
    char *name = list_pop(self->principle_name_list);
    if (!name) return NULL;

    list_push(self->matched_principle_name_list, name);
    return name;
}

static const node_pattern_t *
matcher_next_node_pattern(net_matcher_t *self, const char *name) {
    (void) self;
    (void) name;
    return NULL;
}

static const node_t *
matcher_next_node(net_matcher_t *self, const char *name) {
    (void) self;
    (void) name;
    return NULL;
}

static bool
matcher_is_success(const net_matcher_t *self) {
    return set_length(self->node_set) == array_size(self->net_pattern->node_pattern_array);
}

void
net_matcher_start(net_matcher_t *self, const node_t *node) {
    const node_pattern_t *node_pattern = net_pattern_first(self->net_pattern);
    matcher_match_node(self, node_pattern, node);
    const char *name = matcher_next_principle_name(self);
    while (name) {
        node_pattern = matcher_next_node_pattern(self, name);
        node = matcher_next_node(self, name);
        if (node_pattern && node) {
            matcher_match_node(self, node_pattern, node);
        }
    }
}

net_matcher_t *
match_net(const net_pattern_t *net_pattern, const node_t *node) {
    net_matcher_t *self = net_matcher_new(net_pattern);
    net_matcher_start(self, node);
    if (matcher_is_success(self)) {
        return self;
    } else {
        net_matcher_destroy(&self);
        return NULL;
    }
}
