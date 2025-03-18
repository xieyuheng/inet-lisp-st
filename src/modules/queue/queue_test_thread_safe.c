#include "index.h"

static void *
producer(queue_t *queue) {
    (void) queue;

    return NULL;
}

static void *
consumer(queue_t *queue) {
    (void) queue;

    return NULL;
}

void
queue_test_thread_safe(void) {
    printf("<queue_test_thread_safe>\n");

    queue_t *queue = queue_new(3);

    thread_id_t producer_id = thread_start((thread_fn_t *) producer, queue);
    thread_id_t consumer_id = thread_start((thread_fn_t *) consumer, queue);

    thread_wait(producer_id);
    thread_wait(consumer_id);

    queue_destroy(&queue);

    printf("</queue_test_thread_safe>\n");
}
