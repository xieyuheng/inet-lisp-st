#pragma once

net_pattern_t *net_pattern_new(list_t *node_pattern_list, size_t starting_index);
void net_pattern_destroy(net_pattern_t **self_pointer);

size_t net_pattern_length(const net_pattern_t *self);
size_t net_pattern_starting_index(const net_pattern_t *self);
node_pattern_t *net_pattern_get(const net_pattern_t *self, size_t index);
list_t *net_pattern_local_name_list(const net_pattern_t *self);
