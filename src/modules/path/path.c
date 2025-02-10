#include "index.h"

struct path_t {
    stack_t *segment_stack;
};

path_t *
path_new(void) {
    path_t *self = new(path_t);
    self->segment_stack = string_stack_new();
    return self;
}

void
path_destroy(path_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        path_t *self = *self_pointer;
        stack_destroy(&self->segment_stack);
        free(self);
        *self_pointer = NULL;
    }
}
