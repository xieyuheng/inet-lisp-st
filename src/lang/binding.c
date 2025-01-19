#include "index.h"

binding_t *
binding_new(list_t *name_list, exp_t *exp) {
    binding_t *self = new(binding_t);
    self->name_list = name_list;
    self->exp = exp;
    return self;
}

void
binding_destroy(binding_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        binding_t *self = *self_pointer;
        list_destroy(&self->name_list);
        exp_destroy(&self->exp);
        free(self);
        *self_pointer = NULL;
    }
}

list_t *
binding_list_new(void) {
    return list_new_with((destroy_fn_t *) binding_destroy);
}
