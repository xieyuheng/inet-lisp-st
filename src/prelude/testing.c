#include "index.h"

void x_assert(vm_t *vm) {
    bool ok = to_bool(stack_pop(vm->value_stack));
    if (!ok) {
        fprintf(stderr, "[assert] fail\n");
        vm_print(vm, stderr);
        exit(1);
    }
}
