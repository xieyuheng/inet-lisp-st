#pragma once

void define(mod_t *self, const char *name, value_t value);

void define_rule(mod_t *self, const char *name, rule_t *rule);

void define_primitive_vm_fn(mod_t *mod, const char *name, size_t input_arity, size_t output_arity, primitive_vm_fn_t *primitive_vm_fn);
void define_primitive_0_fn(mod_t *mod, const char *name, primitive_0_fn_t *primitive_0_fn);
void define_primitive_1_fn(mod_t *mod, const char *name, primitive_1_fn_t *primitive_1_fn);
void define_primitive_2_fn(mod_t *mod, const char *name, primitive_2_fn_t *primitive_2_fn);
void define_primitive_3_fn(mod_t *mod, const char *name, primitive_3_fn_t *primitive_3_fn);
void define_primitive_4_fn(mod_t *mod, const char *name, primitive_4_fn_t *primitive_4_fn);

void define_primitive_node(mod_t *mod, const char *name, const char *port_names[]);
