#include "index.h"

void
define_primitive_fn(mod_t *mod, const char *name, size_t input_arity, size_t output_arity, primitive_fn_t *primitive_fn) {
    define(mod, name, primitive_from_fn(name, input_arity, output_arity, primitive_fn));
}

void
define_primitive_fn_0(mod_t *mod, const char *name, primitive_fn_0_t *primitive_fn_0) {
    define(mod, name, primitive_from_fn_0(name, primitive_fn_0));
}

void
define_primitive_fn_1(mod_t *mod, const char *name, primitive_fn_1_t *primitive_fn_1) {
    define(mod, name, primitive_from_fn_1(name, primitive_fn_1));
}

void
define_primitive_fn_2(mod_t *mod, const char *name, primitive_fn_2_t *primitive_fn_2) {
    define(mod, name, primitive_from_fn_2(name, primitive_fn_2));
}

void
define_primitive_fn_3(mod_t *mod, const char *name, primitive_fn_3_t *primitive_fn_3) {
    define(mod, name, primitive_from_fn_3(name, primitive_fn_3));
}

void
define_primitive_fn_4(mod_t *mod, const char *name, primitive_fn_4_t *primitive_fn_4)  {
    define(mod, name, primitive_from_fn_4(name, primitive_fn_4));
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
        assert(port_names[i]);
        node_ctor->port_infos[i] =
            port_info_from_name(string_copy(port_names[i]));
    }

    primitive->node_ctor = node_ctor;
    node_ctor->primitive = primitive;
}

void
define_primitive_fn_node(mod_t *mod, const char *name, size_t input_arity, size_t output_arity, primitive_fn_t *primitive_fn, const char *port_names[]) {
    define_primitive_fn(mod, name, input_arity, output_arity, primitive_fn);
    define_primitive_node(mod, name, port_names);
}

void
define_primitive_fn_node_0(mod_t *mod, const char *name, primitive_fn_0_t *primitive_fn_0, const char *port_names[]) {
    define_primitive_fn_0(mod, name, primitive_fn_0);
    define_primitive_node(mod, name, port_names);
}

void
define_primitive_fn_node_1(mod_t *mod, const char *name, primitive_fn_1_t *primitive_fn_1, const char *port_names[]) {
    define_primitive_fn_1(mod, name, primitive_fn_1);
    define_primitive_node(mod, name, port_names);
}

void
define_primitive_fn_node_2(mod_t *mod, const char *name, primitive_fn_2_t *primitive_fn_2, const char *port_names[]) {
    define_primitive_fn_2(mod, name, primitive_fn_2);
    define_primitive_node(mod, name, port_names);
}

void
define_primitive_fn_node_3(mod_t *mod, const char *name, primitive_fn_3_t *primitive_fn_3, const char *port_names[]) {
    define_primitive_fn_3(mod, name, primitive_fn_3);
    define_primitive_node(mod, name, port_names);
}

void
define_primitive_fn_node_4(mod_t *mod, const char *name, primitive_fn_4_t *primitive_fn_4, const char *port_names[]) {
    define_primitive_fn_4(mod, name, primitive_fn_4);
    define_primitive_node(mod, name, port_names);
}
