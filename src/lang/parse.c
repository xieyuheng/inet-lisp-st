#include "index.h"

stmt_t *
parse_stmt(sexp_t *sexp) {
    (void) sexp;
    return NULL;
    // if (sexp_starts_with(sexp, "define-node"))
    //     return parse_define_node(sexp);
    // else if (sexp_starts_with(sexp, "define"))
    //     return parse_define_function(sexp);
    // else assert(false && "[parse_stmt] unknown sexp");
}

list_t *
parse_stmt_list(list_t *sexp_list) {
    list_t *stmt_list = list_new_with((destroy_fn_t *) stmt_destroy);
    sexp_t *sexp = list_first(sexp_list);
    while (sexp) {
        list_push(stmt_list, parse_stmt(sexp));
        sexp = list_next(sexp_list);
    }

    return stmt_list;
}
