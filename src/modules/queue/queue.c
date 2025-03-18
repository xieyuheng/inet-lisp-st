#include "index.h"

// a thread safe queue

typedef _Atomic uint64_t cursor_t;

struct queue_t {
    size_t size;
    cursor_t start_cursor;
    cursor_t end_cursor;
};
