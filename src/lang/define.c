#include "index.h"

void
define(mod_t *self, const char *name, value_t value) {
    assert(hash_set(self->value_hash, string_copy(name), value));
}
