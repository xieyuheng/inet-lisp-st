#include "index.h"

void
path_test(void) {
    printf("<path_test>\n");

    {
        path_t *path = path_new("abc");
        assert(string_equal(path_string(path), "abc"));
        path_destroy(&path);
    }

    {
        path_t *path = path_new("");
        assert(string_equal(path_string(path), ""));
        path_destroy(&path);
    }

    {
        path_t *path = path_new("a/b/c");
        assert(string_equal(path_string(path), "a/b/c"));
        path_destroy(&path);
    }

    {
        path_t *path = path_new("aa/bb/cc");
        assert(string_equal(path_string(path), "aa/bb/cc"));
        path_destroy(&path);
    }

    {
        path_t *path = path_new("/aa/bb/cc");
        assert(path_is_absolute(path));
        assert(string_equal(path_string(path), "/aa/bb/cc"));
        path_destroy(&path);
    }

    printf("</path_test>\n");
}
