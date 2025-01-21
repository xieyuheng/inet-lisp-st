#include "index.h"

void
apply_function(vm_t *vm, function_t *function, size_t arity) {
    (void) arity; // TODO
    frame_t *frame = frame_new(function);
    stack_push(vm->return_stack, frame);
    return;
}
