#include "index.h"

list_t *
string_list_new(void) {
    return list_new_with((destroy_fn_t *) string_destroy);
}

list_t *
string_list_copy(list_t *list) {
    list_set_copy_fn(list, (copy_fn_t *) string_copy);
    return list_copy(list);
}
