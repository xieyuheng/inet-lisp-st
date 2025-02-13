#include "index.h"

void
define_function(mod_t *mod, const char *name, function_t *function) {
    mod_define(mod, name, def_function(function));
}
