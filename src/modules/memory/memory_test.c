#include "index.h"

void
memory_test(void) {
    printf("<memory_test>\n");

    {
        void *pointer = allocate(10);
        assert(pointer_is_8_bytes_aligned(pointer));
        destroy(&pointer);
        destroy(&pointer);
    }

    {
        void *pointer = allocate_shared(10);
        assert(pointer_is_8_bytes_aligned(pointer));
        assert(pointer_is_cache_line_aligned(pointer));
        destroy(&pointer);
        destroy(&pointer);
    }

    printf("</memory_test>\n");
}
