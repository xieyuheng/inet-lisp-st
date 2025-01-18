#include "index.h"

binding_t *
binding_new(void) {
    binding_t *self = new(binding_t);
    self->name_list = list_new();
    self->body = list_new();
    return self;
}
