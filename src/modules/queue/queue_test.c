#include "index.h"

void
queue_test(void) {
    printf("<queue_test>\n");

    queue_t *queue = queue_new(3);
    assert(queue_size(queue) == 3);
    assert(queue_length(queue) == 0);

    queue_destroy(&queue);

    printf("</queue_test>\n");
}
