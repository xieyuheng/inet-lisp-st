#include "index.h"

mod_t *
load_mod(const char *path) {
    file_t *file = file_open_or_fail(path, "r");
    const char *code = file_read_string(file);
    fclose(file);

    mod_t *mod = mod_new(path, code);
    import_all_primitives(mod);
    vm_t *vm = vm_new(mod);

    list_t *sexp_list = sexp_parse_list(code) ;
    list_t *stmt_list = parse_stmt_list(sexp_list);
    stmt_t *stmt = list_first(stmt_list);
    while (stmt) {
        execute(vm, stmt);
        stmt = list_next(stmt_list);
    }

    list_destroy(&sexp_list);
    list_destroy(&stmt_list);
    vm_destroy(&vm);

    return mod;
}
