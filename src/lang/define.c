#include "index.h"

void
define(mod_t *self, const char *name, value_t value) {
    assert(hash_set(self->value_hash, string_copy(name), value));
}

void
define_rule(mod_t *self, const char *name, rule_t *rule) {
    value_t value = mod_find(self, name);
    node_ctor_t *node_ctor = as_node_ctor(value);
    list_push(node_ctor->rule_list, rule);
}
