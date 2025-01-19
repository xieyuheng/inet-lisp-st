#include "index.h"

static stmt_t *
parse_define_node(sexp_t *sexp) {
    list_sexp_t *list_sexp = as_list_sexp(sexp);
    list_t *sexp_list = list_sexp->sexp_list;
    sexp_t *first_sexp = list_first(sexp_list);
    assert(string_equal(sexp_string(first_sexp), "define-node"));
    sexp_t *name_sexp = list_next(sexp_list);
    char *name = string_copy(sexp_string(name_sexp));
    (void) name;
    // TODO
    return NULL;
}

static stmt_t *
parse_define_function(sexp_t *sexp) {
    (void) sexp;
    return NULL;
}

stmt_t *
parse_stmt(sexp_t *sexp) {
    if (sexp_starts_with(sexp, "define-node"))
        return parse_define_node(sexp);
    else if (sexp_starts_with(sexp, "define"))
        return parse_define_function(sexp);
    else assert(false && "[parse_stmt] unknown sexp");
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
