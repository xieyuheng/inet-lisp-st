#pragma once

path_t *path_new(const char *string);
void path_destroy(path_t **self_pointer);

void path_join(path_t *self, const char *string);
const char *path_string(path_t *self);
