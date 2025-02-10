#include "index.h"

static int run(commander_t *commander);

void
run_command(commander_t *runner) {
    command_t *command = command_new("run");
    command->description = "run files";
    command->run = run;
    commander_add(runner, command);
}

int
run(commander_t *commander) {
    char **paths = commander_rest_argv(commander);
    paths = commander_rest_argv(commander);
    while (*paths) {
        char *path = *paths++;
        if (string_starts_with(path, "--"))
            continue;

        if (string_ends_with(path, ".lisp")) {
            mod_t *mod = load_mod(path);
            mod_destroy(&mod);
        } else  {
            fprintf(stderr, "[run] file name must ends with .lisp, given file name: %s\n", path);
            exit(1);
        }
    }

    return 0;
}
