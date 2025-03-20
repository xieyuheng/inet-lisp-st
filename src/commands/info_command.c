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

    printf("page size: %ld bytes\n", sysconf(_SC_PAGE_SIZE));

    printf("l1 data cache size: %ld bytes\n", sysconf(_SC_LEVEL1_DCACHE_SIZE));
    printf("l1 data cache associativity: %ld lines\n", sysconf(_SC_LEVEL1_DCACHE_ASSOC));
    printf("l1 data cache line size: %ld bytes\n", sysconf(_SC_LEVEL1_DCACHE_LINESIZE));

    printf("l2 data cache size: %ld bytes\n", sysconf(_SC_LEVEL2_CACHE_SIZE));
    printf("l2 data cache associativity: %ld lines\n", sysconf(_SC_LEVEL2_CACHE_ASSOC));
    printf("l2 data cache line size: %ld bytes\n", sysconf(_SC_LEVEL2_CACHE_LINESIZE));

    printf("l3 data cache size: %ld bytes\n", sysconf(_SC_LEVEL3_CACHE_SIZE));
    printf("l3 data cache associativity: %ld lines\n", sysconf(_SC_LEVEL3_CACHE_ASSOC));
    printf("l3 data cache line size: %ld bytes\n", sysconf(_SC_LEVEL3_CACHE_LINESIZE));

    return 0;
}
