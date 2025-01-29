#include "index.h"

object_spec_t primitive_object_spec = {
    .name = "primitive",
    .print_fn = (print_fn_t *) primitive_print,
};

static primitive_t *
primitive_new(const char *name) {
    primitive_t *self = new(primitive_t);
    self->name = string_copy(name);
    return self;
}

primitive_t *
primitive_from_vm_fn(const char *name, size_t arity, primitive_vm_fn_t *primitive_vm_fn) {
    primitive_t *self = primitive_new(name);
    self->fn_kind = PRIMITIVE_VM_FN;
    self->arity = arity;
    self->primitive_vm_fn = primitive_vm_fn;
    return self;
}

primitive_t *
primitive_from_0_fn(const char *name, primitive_0_fn_t *primitive_0_fn) {
    primitive_t *self = primitive_new(name);
    self->fn_kind = PRIMITIVE_0_FN;
    self->arity = 0;
    self->primitive_0_fn = primitive_0_fn;
    return self;
}

primitive_t *
primitive_from_1_fn(const char *name, primitive_1_fn_t *primitive_1_fn) {
    primitive_t *self = primitive_new(name);
    self->fn_kind = PRIMITIVE_1_FN;
    self->arity = 1;
    self->primitive_1_fn = primitive_1_fn;
    return self;
}

primitive_t *
primitive_from_2_fn(const char *name, primitive_2_fn_t *primitive_2_fn) {
    primitive_t *self = primitive_new(name);
    self->fn_kind = PRIMITIVE_2_FN;
    self->arity = 2;
    self->primitive_2_fn = primitive_2_fn;
    return self;
}

primitive_t *
primitive_from_3_fn(const char *name, primitive_3_fn_t *primitive_3_fn) {
    primitive_t *self = primitive_new(name);
    self->fn_kind = PRIMITIVE_3_FN;
    self->arity = 3;
    self->primitive_3_fn = primitive_3_fn;
    return self;
}

primitive_t *
primitive_from_4_fn(const char *name, primitive_4_fn_t *primitive_4_fn) {
    primitive_t *self = primitive_new(name);
    self->fn_kind = PRIMITIVE_4_FN;
    self->arity = 4;
    self->primitive_4_fn = primitive_4_fn;
    return self;
}

void
primitive_destroy(primitive_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        primitive_t *self = *self_pointer;
        string_destroy(&self->name);
        free(self);
        *self_pointer = NULL;
    }
}

bool
is_primitive(value_t value) {
    if (!is_xobject(value)) return false;
    return as_object(value)->spec == &primitive_object_spec;
}

primitive_t *
as_primitive(value_t value) {
    assert(is_primitive(value));
    return (primitive_t *) value;
}

void
primitive_print(primitive_t *self, file_t *file) {
    fprintf(file, "#<%s>", self->name);
}
