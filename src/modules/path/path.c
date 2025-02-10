#include "index.h"

struct path_t {
    stack_t *segment_stack;
    char *string;
};

path_t *
path_new(const char *string) {
    path_t *self = new(path_t);
    self->segment_stack = string_stack_new();
    path_add(self, string);
    return self;
}

void
path_destroy(path_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        path_t *self = *self_pointer;
        stack_destroy(&self->segment_stack);
        string_destroy(&self->string);
        free(self);
        *self_pointer = NULL;
    }
}

typedef struct {
    const char *string;
    char *segment;
}  entry_t;

static entry_t *
next_segment(const char *string) {
    if (string_is_empty(string))
        return NULL;

    int index = string_find_index(string, '/');
    if (index == -1) {
        entry_t *entry = new(entry_t);
        entry->string = string + string_length(string);
        entry->segment = string_copy(string);
        return entry;
    }

    entry_t *entry = new(entry_t);
    entry->string = string + index;
    if (string_length(entry->string) > 0)
        entry->string++;

    entry->segment = string_slice(string, 0, index);
    return entry;
}

static void
path_update_string(path_t *self) {
    size_t length = stack_length(self->segment_stack);
    size_t size = 0;
    for (size_t i = 0; i < length; i++) {
        char *segment = stack_get(self->segment_stack, i);
        size += string_length(segment);
        size += 1;
    }

    string_destroy(&self->string);
    self->string = allocate(size);
    char *string = self->string;
    for (size_t i = 0; i < length; i++) {
        char *segment = stack_get(self->segment_stack, i);
        strcat(string, segment);
        string += string_length(segment);
        if (i == length - 1) {
            string[0] = '\0';
        } else {
            string[0] = '/';
            string++;
        }
    }
}

void
path_add(path_t *self, const char *string) {
    entry_t *entry = next_segment(string);
    while (entry) {
        string = entry->string;
        stack_push(self->segment_stack, entry->segment);
        free(entry);
        entry = next_segment(string);
    }

    path_update_string(self);
}

const char *
path_string(path_t *self) {
    if (self->string)
        return self->string;

    path_update_string(self);
    return self->string;
}
