#include "index.h"

list_t *
string_list_new(void) {
    return list_new_with((destroy_fn_t *) string_destroy);
}
