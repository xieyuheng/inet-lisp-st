#include "index.h"

void
define_function(mod_t *mod, const char *name, function_t *function) {
    mod_define(mod, name, function);
}

void
define_primitive_vm_fn(mod_t *mod, const char *name, size_t input_arity, size_t output_arity, primitive_vm_fn_t *primitive_vm_fn) {
    mod_define(mod, name, primitive_from_vm_fn(name, input_arity, output_arity, primitive_vm_fn));
}

void
define_primitive_0_fn(mod_t *mod, const char *name, primitive_0_fn_t *primitive_0_fn) {
    mod_define(mod, name, primitive_from_0_fn(name, primitive_0_fn));
}

void
define_primitive_1_fn(mod_t *mod, const char *name, primitive_1_fn_t *primitive_1_fn) {
    mod_define(mod, name, primitive_from_1_fn(name, primitive_1_fn));
}

void
define_primitive_2_fn(mod_t *mod, const char *name, primitive_2_fn_t *primitive_2_fn) {
    mod_define(mod, name, primitive_from_2_fn(name, primitive_2_fn));
}

void
define_primitive_3_fn(mod_t *mod, const char *name, primitive_3_fn_t *primitive_3_fn) {
    mod_define(mod, name, primitive_from_3_fn(name, primitive_3_fn));
}

void
define_primitive_4_fn(mod_t *mod, const char *name, primitive_4_fn_t *primitive_4_fn)  {
    mod_define(mod, name, primitive_from_4_fn(name, primitive_4_fn));
}
