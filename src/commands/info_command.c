#include "index.h"

static int run(commander_t *commander);

void
info_command(commander_t *commander) {
    command_t *command = command_new("info");
    command->description = "print system info";
    command->run = run;
    commander_add(commander, command);
}

int
run(commander_t *commander) {
    (void) commander;

    printf("hi\n");

    return 0;
}
