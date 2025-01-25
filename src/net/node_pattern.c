#include "index.h"

node_pattern_t *
node_pattern_new(const node_ctor_t *ctor) {
    node_pattern_t *self = new(node_pattern_t);
    self->ctor = ctor;
    self->port_infos = allocate_pointers(ctor->arity);
    return self;
}

void
node_pattern_destroy(node_pattern_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        node_pattern_t *self = *self_pointer;
        for (size_t i = 0; i < self->ctor->arity; i++) {
            port_info_t *port_info = self->port_infos[i];
            if (port_info) {
                port_info_destroy(&port_info);
            }
        }

        free(self);
        *self_pointer = NULL;
    }
}
