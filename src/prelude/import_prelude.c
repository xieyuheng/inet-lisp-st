#include "index.h"

void
import_prelude(mod_t *mod) {
    // // bool

    // define_constant(mod, "false", xfalse);
    // define_constant(mod, "true", xtrue);
    // define_primitive_1_fn(mod, "not", xbool_not);
    // define_primitive_2_fn(mod, "and", xbool_and);
    // define_primitive_2_fn(mod, "or", xbool_or);

    // // value

    // define_primitive_2_fn(mod, "eq?", x_eq);

    // // testing

    // define_primitive_vm_fn(mod, "ok", x_ok);

    // int

    define_primitive_2_fn(mod, "iadd", xint_add);
    define_primitive_2_fn(mod, "isub", xint_sub);
    define_primitive_2_fn(mod, "imul", xint_mul);
    define_primitive_2_fn(mod, "idiv", xint_div);
    define_primitive_2_fn(mod, "imod", xint_mod);
    define_primitive_1_fn(mod, "int-to-float", xint_to_xfloat);

    // float

    define_primitive_2_fn(mod, "fadd", xfloat_add);
    define_primitive_2_fn(mod, "fsub", xfloat_sub);
    define_primitive_2_fn(mod, "fmul", xfloat_mul);
    define_primitive_2_fn(mod, "fdiv", xfloat_div);
    define_primitive_2_fn(mod, "fmod", xfloat_mod);
    define_primitive_1_fn(mod, "float-to-int", xfloat_to_xint);

    // net

    define_primitive_vm_fn(mod, "connect", 2, 0, x_connect);
    define_primitive_vm_fn(mod, "wire-print-net", 1, 1, x_wire_print_net);
    define_primitive_vm_fn(mod, "link", 0, 2, x_link);
    define_primitive_vm_fn(mod, "run", 0, 0, x_run);
    define_primitive_vm_fn(mod, "inspect-run", 1, 1, x_inspect_run);
    define_primitive_vm_fn(mod, "debug", 0, 0, x_debug);

    // console

    define_primitive_1_fn(mod, "print", x_print);
    define_primitive_0_fn(mod, "newline", x_newline);
    define_primitive_1_fn(mod, "println", x_println);
}
