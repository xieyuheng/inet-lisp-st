#include "index.h"

object_spec_t node_object_spec = {
    .name = "node",
    .print_fn = (print_fn_t *) node_print,
};

node_t *
node_new(const node_ctor_t *ctor, size_t id) {
    node_t *self = new(node_t);
    self->spec = &node_object_spec;
    self->ctor = ctor;
    self->id = id;
    self->wires = allocate_pointers(ctor->arity);
    return self;
}

void
node_destroy(node_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        node_t *self = *self_pointer;
        free(self->wires);
        // Does NOT own wires in `wires`.
        free(self);
        *self_pointer = NULL;
    }
}

bool
is_node(value_t value) {
    if (!is_xobject(value)) return false;
    return as_object(value)->spec == &node_object_spec;
}

node_t *
as_node(value_t value) {
    assert(is_node(value));
    return (node_t *) value;
}

void
node_print(const node_t *self, file_t *file) {
    char *id_string = uint_to_subscript(self->id);
    fprintf(file, "(%s%s)", self->ctor->name, id_string);
    free(id_string);
}
