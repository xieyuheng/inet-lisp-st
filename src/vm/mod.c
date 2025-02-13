#include "index.h"

mod_t *
mod_new(path_t *path, char *code) {
    mod_t *self = new(mod_t);
    self->path = path;
    self->code = code;
    self->value_hash = hash_of_string_key();
    // TODO we do not have `value_destroy` for now
    // hash_set_destroy_fn(self->value_hash, (destroy_fn_t *) value_destroy);
    return self;
}

void
mod_destroy(mod_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        mod_t *self = *self_pointer;
        path_destroy(&self->path);
        string_destroy(&self->code);
        hash_destroy(&self->value_hash);
        free(self);
        *self_pointer = NULL;
    }
}

value_t
mod_find(const mod_t *self, const char *name) {
    return hash_get(self->value_hash, name);
}

void
mod_define(mod_t *self, const char *name, value_t value) {
    assert(hash_set(self->value_hash, string_copy(name), value));
}

void
mod_define_rule(mod_t *self, const char *name, rule_t *rule) {
    value_t value = mod_find(self, name);
    node_ctor_t *node_ctor = as_node_ctor(value);
    list_push(node_ctor->rule_list, rule);
}

void
mod_print(const mod_t *self, file_t *file) {
    fprintf(file, "<mod value-count=\"%lu\">\n", hash_length(self->value_hash));

    value_t value = hash_first(self->value_hash);
    while (value) {
        value_print(value, file);
        fprintf(file, "\n");
        value = hash_next(self->value_hash);
    }

    fprintf(file, "</mod>\n");
}
