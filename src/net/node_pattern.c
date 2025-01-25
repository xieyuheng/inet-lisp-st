#include "index.h"

node_pattern_t *
node_pattern_new(const node_ctor_t *ctor) {
    node_pattern_t *self = new(node_pattern_t);
    self->ctor = ctor;
    self->port_info_array = port_info_array_new(ctor->arity);
    return self;
}
