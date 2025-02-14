#include "index.h"

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
        fprintf(stderr, "[define_primitive_node] expect value of name: %s to be a primitive, instead of: \n", name);
        value_print(value, stderr);
        exit(1);
    }

    primitive_t *primitive = as_primitive(value);
    size_t arity = primitive->input_arity + primitive->output_arity;
    node_ctor_t *node_ctor = node_ctor_new(name, arity);
    for (size_t i = 0; i < arity; i++) {
        node_ctor->port_infos[i] =
            port_info_from_name(string_copy(port_names[i]));
    }

    primitive->node_ctor = node_ctor;
    node_ctor->primitive = primitive;
}
