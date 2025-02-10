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

typedef struct {
    const char *string;
    char *segment;
}  entry_t;

static entry_t *
first_segment(const char *string) {
    (void) string;
    return NULL;
}

static entry_t *
next_segment(const char *string) {
    (void) string;
    return NULL;
}

void
path_add(path_t *self, const char *string) {
    entry_t *entry = first_segment(string);
    while (entry) {
        string = entry->string;
        stack_push(self->segment_stack, entry->segment);
        free(entry);
        entry = next_segment(string);
    }
}
