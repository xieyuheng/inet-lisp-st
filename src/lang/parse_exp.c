#include "index.h"

static exp_t *
parse_var(sexp_t *sexp) {
    return exp_var(string_copy(sexp_string(sexp)));
}

static exp_t *
parse_ap(sexp_t *sexp) {
    list_t *sexp_list = sexp_sexp_list(sexp);
    assert(!list_is_empty(sexp_list));
    exp_t *target = parse_exp(list_first(sexp_list));
    list_t *arg_list = exp_list_new();
    sexp_t *arg_sexp = list_next(sexp_list);
    while (arg_sexp) {
        list_push(arg_list, parse_exp(arg_sexp));
        arg_sexp = list_next(sexp_list);
    }

    return exp_ap(target, arg_list);
}

static exp_t *
parse_bind(sexp_t *sexp) {
    list_t *sexp_list = sexp_sexp_list(sexp);
    (void) list_first(sexp_list);
    list_t *name_list = string_list_new();
    sexp_t *name_sexp = list_next(sexp_list);
    while (name_sexp) {
        list_push(name_list, string_copy(sexp_string(name_sexp)));
        name_sexp = list_next(sexp_list);
    }

    return exp_bind(name_list);
}

exp_t *
parse_exp(sexp_t *sexp) {
    if (sexp_starts_with(sexp, "="))
        return parse_bind(sexp);
    else if (is_atom_sexp(sexp))
        return parse_var(sexp);
    else if (!list_is_empty(sexp_sexp_list(sexp)))
        return parse_ap(sexp);
    else
        assert(false && "[parse_exp] can not handle empty list sexp");
}
