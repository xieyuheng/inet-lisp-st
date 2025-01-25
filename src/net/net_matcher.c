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
    (void) self;
    (void) node_pattern;
    (void) node;
}

static const char *
matcher_next_principle_name(net_matcher_t *self) {
    (void) self;
    return NULL;
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

void
matcher_start(net_matcher_t *self, const node_t *node) {
    const node_pattern_t *node_pattern = net_pattern_first(self->net_pattern);
    matcher_match_node(self, node_pattern, node);
    const char *name = matcher_next_principle_name(self);
    while (name) {
        node_pattern = matcher_next_node_pattern(self, name);
        node = matcher_next_node(self, name);
        matcher_match_node(self, node_pattern, node);
    }
}
