#include "index.h"

static int run(commander_t *commander);

void
debug_command(commander_t *runner) {
    command_t *command = command_new("debug");
    command->description = "debug files";
    command->run = run;
    commander_add(runner, command);
}

extern bool global_debug_flag;

int
run(commander_t *commander) {
    char **argv = commander_rest_argv(commander);
    argv = commander_rest_argv(commander);
    while (*argv) {
        char *src = *argv++;
        if (string_ends_with(src, ".lisp")) {
            char *cwd = getcwd(NULL, 0);
            path_t *path = path_new(cwd);
            path_join(path, src);
            global_debug_flag = true;
            mod_t *mod = load_mod(path);
            debug_start(mod->loader_worker);
        } else  {
            fprintf(stderr, "[debug] file name must ends with .lisp, given file name: %s\n", src);
            exit(1);
        }
    }

    return 0;
}
