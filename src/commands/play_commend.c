#include "index.h"

static int run(commander_t *commander);

void
play_command(commander_t *runner) {
    command_t *command = command_new("play");
    command->description = "play files";
    command->run = run;
    commander_add(runner, command);
}

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
            core_player_flag = true;
            mod_t *mod = load_mod(path);
            player_start(mod->loader_worker);
        } else  {
            test_printf("[debug] file name must ends with .lisp, given file name: %s\n", src);
            exit(1);
        }
    }

    return 0;
}
