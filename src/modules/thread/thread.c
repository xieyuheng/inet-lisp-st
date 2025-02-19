#include "index.h"

thread_id_t
thread_start(thread_fn_t *thread_fn, void *arg) {
    thread_id_t thread_id;
    int ok = pthread_create(&thread_id, NULL, thread_fn, arg);
    assert(ok == 0);
    return thread_id;
}
