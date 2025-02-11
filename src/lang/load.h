#pragma once

extern hash_t *global_mod_hash;

extern void import_all_primitives(mod_t *mod);

mod_t *load_mod(path_t *path);
