#include "index.h"

static void *
thread_fn(char *message) {
    printf("[thread_fn] %s\n", message);
    return (void *) strlen(message);
}

void
thread_test(void) {
    printf("<thread_test>\n");

    thread_id_t thread_id = thread_start(
        (thread_fn_t *) thread_fn,
        string_copy("hello world"));

    printf("[thread_test]thread created: %lu\n", thread_id);

    void *result;
    pthread_join(thread_id, &result);

    printf("[thread_test] thread returned: %lu\n", (size_t) result);

    printf("</thread_test>\n");
}
