#include "index.h"

stmt_t *
stmt_define_function(char *name) {
    stmt_t *self = new(stmt_t);
    self->kind = STMT_DEFINE_FUNCTION;
    self->define_function.name = name;
    self->define_function.arg_name_list = list_new_with((destroy_fn_t *) string_destroy);
    self->define_function.body = exp_list_new();
    return self;
}
