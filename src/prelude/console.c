#include "index.h"

value_t x_print(value_t x) {
    value_print(x, stdout);
    return x;
}

void x_newline(vm_t *vm) {
    (void) vm;
    printf("\n");
}

value_t x_println(value_t x) {
    x_print(x);
    printf("\n");
    return x;
}
