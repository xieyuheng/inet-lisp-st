#include "index.h"

static exp_t *
parse_var(sexp_t *sexp) {
    return exp_var(string_copy(sexp_string(sexp)));
}

static exp_t *
parse_ap(sexp_t *sexp) {
    (void) sexp;
    return NULL;
}

static exp_t *
parse_assign(sexp_t *sexp) {
    (void) sexp;
    return NULL;
}

static exp_t *
parse_exp(sexp_t *sexp) {
    if (sexp_starts_with(sexp, "="))
        return parse_assign(sexp);
    else if (is_list_sexp(sexp))
        return parse_ap(sexp);
    else
        return parse_var(sexp);
}

static stmt_t *
parse_define_node(sexp_t *sexp) {
    list_t *sexp_list = sexp_sexp_list(sexp);
    (void) list_first(sexp_list);
    sexp_t *name_sexp = list_next(sexp_list);
    char *name = string_copy(sexp_string(name_sexp));
    list_t *port_name_list = string_list_new();
    sexp_t *port_name_sexp = list_next(sexp_list);
    while (port_name_sexp) {
        list_push(port_name_list, string_copy(sexp_string(port_name_sexp)));
        port_name_sexp = list_next(sexp_list);
    }

    return stmt_define_node(name, port_name_list);
}

static stmt_t *
parse_define_function(sexp_t *sexp) {
    list_t *sexp_list = sexp_sexp_list(sexp);
    (void) list_first(sexp_list);

    list_t *name_sexp_list = sexp_sexp_list(list_next(sexp_list));
    sexp_t *first_name_sexp = list_first(name_sexp_list);
    char *name = string_copy(sexp_string(first_name_sexp));
    (void) name;
    list_t *arg_name_list = string_list_new();
    sexp_t *name_sexp = list_next(name_sexp_list);
    while (name_sexp) {
        list_push(arg_name_list, string_copy(sexp_string(name_sexp)));
        name_sexp = list_next(name_sexp_list);
    }

    list_t *exp_list = exp_list_new();
    sexp_t *exp_sexp = list_next(sexp_list);
    while (exp_sexp) {
        list_push(exp_list, parse_exp(exp_sexp));
        exp_sexp = list_next(sexp_list);
    }

    return stmt_define_function(name, arg_name_list, exp_list);
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
