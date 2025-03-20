#include "index.h"

#define QUEUE_SIZE 1000
#define LENGTH 10000000

static void *
uint_producer(queue_t *queue) {
    size_t count = 0;
    while (true) {
        if (count == LENGTH) return NULL;

        while (queue_is_full(queue)) {}

        queue_enqueue(queue, (void *) count);
        count++;
    }
}

static void *
uint_consumer(queue_t *queue) {
    size_t count = 0;
    while (true) {
        if (count == LENGTH) return NULL;

        while (queue_is_empty(queue)) {}

        assert(((size_t) queue_dequeue(queue)) == count);
        count++;
    }
}

void
queue_test_throughput(void) {
    printf("<queue_test_throughput>\n");

    queue_t *queue = queue_new(QUEUE_SIZE);

    printf("uint_producer v.s. uint_consumer\n");

    struct timespec time_start;
    timespec_get(&time_start, TIME_UTC);

    thread_id_t producer_id =
        thread_start((thread_fn_t *) uint_producer, queue);
    thread_id_t consumer_id =
        thread_start((thread_fn_t *) uint_consumer, queue);

    thread_wait(producer_id);
    thread_wait(consumer_id);

    struct timespec time_end;
    timespec_get(&time_end, TIME_UTC);

    double time_spent =
        (time_end.tv_sec + time_end.tv_nsec * 1e-9) -
        (time_start.tv_sec + time_start.tv_nsec * 1e-9);

    printf("throughput: %.f k/s\n", LENGTH / time_spent / 1000);

    queue_destroy(&queue);

    printf("</queue_test_throughput>\n");
}
