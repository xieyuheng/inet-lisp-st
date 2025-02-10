#pragma once

path_t *path_new(void);
void path_destroy(path_t **self_pointer);

void path_add(path_t *self, const char *string);
