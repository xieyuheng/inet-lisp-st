#pragma once

// A mod is a compilation unit,
// like the dictionary of forth.

struct mod_t {
    path_t *path;
    char *code;
    hash_t *def_hash;
};

mod_t *mod_new(path_t *path, char *code);
void mod_destroy(mod_t **self_pointer);

def_t *mod_find_def(const mod_t *self, const char *name);
void mod_define(mod_t *self, def_t *def);
void mod_define_rule(mod_t *self, const char *name, rule_t *rule);

void mod_print(const mod_t *self, file_t *file);
