#include "index.h"

node_pattern_t *
node_pattern_new(const node_ctor_t *ctor) {
    node_pattern_t *self = new(node_pattern_t);
    self->ctor = ctor;
    self->port_info_array = port_info_array_new(ctor->arity);
    return self;
}

void
node_pattern_destroy(node_pattern_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        node_pattern_t *self = *self_pointer;
        array_destroy(&self->port_info_array);
        free(self);
        *self_pointer = NULL;
    }
}
