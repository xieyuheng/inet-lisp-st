#include "index.h"

stmt_t *
parse_stmt(list_t *sexp_list) {
    (void) sexp_list;
    return NULL;
}

list_t *
parse_stmt_list(list_t *sexp_list) {
    list_t *stmt_list = list_new_with((destroy_fn_t *) stmt_destroy);
    while (!list_is_empty(sexp_list)) {
        list_push(stmt_list, parse_stmt(sexp_list));
    }

    return stmt_list;
}
