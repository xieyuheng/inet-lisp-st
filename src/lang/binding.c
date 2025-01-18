#include "index.h"

binding_t *
binding_new(void) {
    binding_t *self = new(binding_t);
    self->name_list = list_new_with((destroy_fn_t *) string_destroy);
    self->body = list_new(); // TODO
    return self;
}

void
binding_destroy(binding_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        binding_t *self = *self_pointer;
        list_destroy(&self->name_list);
        list_destroy(&self->body);
        free(self);
        *self_pointer = NULL;
    }
}

list_t *
binding_list_new(void) {
    return list_new_with((destroy_fn_t *) binding_destroy);
}
