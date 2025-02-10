#include "index.h"

struct path_t {
    stack_t *segment_stack;
};

path_t *
path_new(void) {
    path_t *self = new(path_t);
    self->segment_stack = stack_new(); // TODO string_stack_new();
    return self;
}
