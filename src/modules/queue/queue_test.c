#include "index.h"

void
queue_test(void) {
    printf("<queue_test>\n");

    queue_test_thread_safe();
    queue_test_throughput();

    queue_t *queue = queue_new(3);
    assert(queue_size(queue) == 3);
    assert(queue_length(queue) == 0);

    {
        queue_enqueue(queue, (void *) 1);
        queue_enqueue(queue, (void *) 2);
        queue_enqueue(queue, (void *) 3);

        assert(queue_length(queue) == 3);
        assert(queue_is_full(queue));

        assert(((uint64_t) queue_dequeue(queue)) == 1);
        assert(((uint64_t) queue_dequeue(queue)) == 2);
        assert(((uint64_t) queue_dequeue(queue)) == 3);
        assert(queue_dequeue(queue) == NULL);

        assert(queue_length(queue) == 0);
    }

    {
        queue_enqueue(queue, (void *) 1);
        queue_enqueue(queue, (void *) 2);
        queue_enqueue(queue, (void *) 3);

        assert(queue_length(queue) == 3);
        assert(queue_is_full(queue));

        assert(((uint64_t) queue_dequeue(queue)) == 1);
        assert(((uint64_t) queue_dequeue(queue)) == 2);
        assert(((uint64_t) queue_dequeue(queue)) == 3);
        assert(queue_dequeue(queue) == NULL);

        assert(queue_length(queue) == 0);
    }

    queue_destroy(&queue);

    printf("</queue_test>\n");
}
