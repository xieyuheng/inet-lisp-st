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

void
define_primitive_vm_fn(mod_t *mod, const char *name, size_t input_arity, size_t output_arity, primitive_vm_fn_t *primitive_vm_fn) {
    define(mod, name, primitive_from_vm_fn(name, input_arity, output_arity, primitive_vm_fn));
}

void
define_primitive_0_fn(mod_t *mod, const char *name, primitive_0_fn_t *primitive_0_fn) {
    define(mod, name, primitive_from_0_fn(name, primitive_0_fn));
}

void
define_primitive_1_fn(mod_t *mod, const char *name, primitive_1_fn_t *primitive_1_fn) {
    define(mod, name, primitive_from_1_fn(name, primitive_1_fn));
}

void
define_primitive_2_fn(mod_t *mod, const char *name, primitive_2_fn_t *primitive_2_fn) {
    define(mod, name, primitive_from_2_fn(name, primitive_2_fn));
}

void
define_primitive_3_fn(mod_t *mod, const char *name, primitive_3_fn_t *primitive_3_fn) {
    define(mod, name, primitive_from_3_fn(name, primitive_3_fn));
}

void
define_primitive_4_fn(mod_t *mod, const char *name, primitive_4_fn_t *primitive_4_fn)  {
    define(mod, name, primitive_from_4_fn(name, primitive_4_fn));
}

void
define_primitive_node(mod_t *mod, const char *name, const char *port_names[]) {
    value_t value = mod_find(mod, name);
    if (!is_primitive(value)) {
        fprintf(stderr, "[define_primitive_node] expect value of %s to be a primitive: \n", name);
        value_print(value, stderr);
        exit(1);
    }

    (void) port_names;
}
