#include "index.h"

mod_t *
mod_new(path_t *path, char *code) {
    mod_t *self = new(mod_t);
    self->path = path;
    self->code = code;
    self->def_hash = hash_of_string_key();
    hash_set_destroy_fn(self->def_hash, (destroy_fn_t *) def_destroy);
    return self;
}

void
mod_destroy(mod_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        mod_t *self = *self_pointer;
        path_destroy(&self->path);
        string_destroy(&self->code);
        hash_destroy(&self->def_hash);
        free(self);
        *self_pointer = NULL;
    }
}

def_t *
mod_find_def(const mod_t *self, const char *name) {
    return hash_get(self->def_hash, name);
}

void
mod_define(mod_t *self, def_t *def) {
    assert(hash_set(self->def_hash, string_copy(def_name(def)), def));
}

void
mod_define_rule(mod_t *self, const char *name, rule_t *rule) {
    const def_t *def = mod_find_def(self, name);
    assert(def->kind == DEF_NODE);
    list_push(def->node.rule_list, rule);
}

void
mod_print(const mod_t *self, file_t *file) {
    fprintf(file, "<mod def-count=\"%lu\">\n", hash_length(self->def_hash));

    def_t *def = hash_first(self->def_hash);
    while (def) {
        def_print(def, file);
        fprintf(file, "\n");
        def = hash_next(self->def_hash);
    }

    fprintf(file, "</mod>\n");
}
