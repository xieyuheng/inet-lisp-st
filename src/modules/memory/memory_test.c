#include "index.h"

struct vec2_t {
    double x;
    double y;
};

typedef struct vec2_t vec2_t;

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

    {
        vec2_t *v = new(vec2_t);
        assert(sizeof *v == 16);
        assert(pointer_is_8_bytes_aligned(v));
        v->x = 0.1;
        v->y = 0.1;
        destroy((void **) &v);
        destroy((void **) &v);
    }

    {
        vec2_t *v = new_shared(vec2_t);
        assert(sizeof *v == 16);
        assert(pointer_is_8_bytes_aligned(v));
        assert(pointer_is_cache_line_aligned(v));
        v->x = 0.1;
        v->y = 0.1;
        destroy((void **) &v);
        destroy((void **) &v);
    }

    printf("</memory_test>\n");
}
