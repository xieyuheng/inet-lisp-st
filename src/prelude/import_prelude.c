#include "index.h"

void
import_prelude(mod_t *mod) {
    // bool

    define(mod, "false", xfalse);
    define(mod, "true", xtrue);
    define_primitive_fn_1(mod, "not", xbool_not);
    define_primitive_node(mod, "not", (const char*[]) { "x!", "y" });
    define_primitive_fn_2(mod, "and", xbool_and);
    define_primitive_node(mod, "and", (const char*[]) { "x!", "y!", "z" });
    define_primitive_fn_2(mod, "or", xbool_or);
    define_primitive_node(mod, "or", (const char*[]) { "x!", "y!", "z" });

    // value

    define_primitive_fn_2(mod, "eq?", x_eq);

    // testing

    define_primitive_vm_fn(mod, "assert", 1, 0, x_assert);

    // int

    define_primitive_fn_1(mod, "int?", xint_p);
    define_primitive_fn_2(mod, "iadd", xint_add);
    define_primitive_node(mod, "iadd", (const char*[]) { "x!", "y!", "z" });
    define_primitive_fn_2(mod, "isub", xint_sub);
    define_primitive_node(mod, "isub", (const char*[]) { "x!", "y!", "z" });
    define_primitive_fn_2(mod, "imul", xint_mul);
    define_primitive_node(mod, "imul", (const char*[]) { "x!", "y!", "z" });
    define_primitive_fn_2(mod, "idiv", xint_div);
    define_primitive_node(mod, "idiv", (const char*[]) { "x!", "y!", "z" });
    define_primitive_fn_2(mod, "imod", xint_mod);
    define_primitive_node(mod, "imod", (const char*[]) { "x!", "y!", "z" });
    define_primitive_fn_1(mod, "int-to-float", xint_to_xfloat);

    // float

    define_primitive_fn_1(mod, "float?", xfloat_p);
    define_primitive_fn_2(mod, "fadd", xfloat_add);
    define_primitive_fn_2(mod, "fsub", xfloat_sub);
    define_primitive_fn_2(mod, "fmul", xfloat_mul);
    define_primitive_fn_2(mod, "fdiv", xfloat_div);
    define_primitive_fn_2(mod, "fmod", xfloat_mod);
    define_primitive_fn_1(mod, "float-to-int", xfloat_to_xint);

    // net

    define_primitive_vm_fn(mod, "connect", 2, 0, x_connect);
    define_primitive_vm_fn(mod, "wire-print-net", 1, 1, x_wire_print_net);
    define_primitive_vm_fn(mod, "link", 0, 2, x_link);
    define_primitive_vm_fn(mod, "run", 0, 0, x_run);
    define_primitive_vm_fn(mod, "inspect-run", 1, 1, x_inspect_run);
    define_primitive_vm_fn(mod, "debug", 0, 0, x_debug);

    // console

    define_primitive_fn_1(mod, "print", x_print);
    define_primitive_fn_0(mod, "newline", x_newline);
    define_primitive_fn_1(mod, "println", x_println);
}
