#include "index.h"

static void *
thread_fn(char *message) {
    printf("[thread_fn] %s\n", message);
    return (void *) strlen(message);
}

void
thread_test(void) {
    printf("<thread_test>\n");

    thread_id_t thread;
    int ok = pthread_create(
        &thread, NULL,
        (thread_fn_t *) thread_fn,
        string_copy("hello world"));
    assert(ok == 0);

    printf("[thread_test]thread created\n");

    void *result;
    pthread_join(thread, &result);

    printf("[thread_test] thread returned: %lu\n", (size_t) result);

    printf("</thread_test>\n");
}
