#include "index.h"

stmt_t *
parse_stmt(sexp_t *sexp) {
    (void) sexp;
    return NULL;
}

list_t *
parse_stmt_list(list_t *sexp_list) {
    list_t *stmt_list = list_new_with((destroy_fn_t *) stmt_destroy);
    while (!list_is_empty(sexp_list)) {
        list_push(stmt_list, parse_stmt(list_shift(sexp_list)));
    }

    return stmt_list;
}
