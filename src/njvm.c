#include "njvm.h"

NinjaVM vm;

int njvm(int argc, char *argv[]) {
    int i, code_file_specified = 0, debug_mode_activated = 0, stack_size = 1, heap_size = 1;
    char *code_file = NULL;
    for (i = 1; i <= argc; i++) {
        if (i == argc) {
            if (!code_file_specified) fatalError("Error: no code file specified");
            execute(code_file);
            exit(0);
        }
        if (!strcmp(argv[i], "--debug")) {
            if (i < argc - 1) {
                debug_mode_activated = 1;
                continue;
            }
            if (code_file_specified) debug(code_file);
            debug_mode_activated = 1;
            continue;
        }
        if (!strcmp(argv[i], "--help")) {
            printf("usage: ./njvm [options] <code file>\n");
            printf("Options:\n");
            printf("  --stack <n> \tset stack size to n KBytes (default: n = 64)\n");
            printf("  --heap <n> \tset heap size to n KBytes (default: n = 8192)\n");
            printf("  --gcstats \tshow garbage collection stats\n");
            printf("  --gcpurge \tpurge old objects after collection\n");
            printf("  --debug \tstart virtual machine in debug mode\n");
            printf("  --version \tshow version and exit\n");
            printf("  --help \tshow this help and exit\n");
            exit(0);
        }
        if (!strcmp(argv[i], "--version")) {
            printf("Ninja Virtual Machine version %d (compiled %s, %s)\n", NINJA_BINARY_VERSION, __DATE__, __TIME__);
            exit(0);
        }
        if (!strcmp(argv[i], "--stack")) {
            if (i >= argc - 1) continue;
            int size = strtol(argv[++i], (char **)NULL, 10);
            if (stack_size <= 0) continue;
            stack_size = size;
            continue;
        }
        if (!strcmp(argv[i], "--heap")) {
            if (i >= argc - 1) continue;
            int size = strtol(argv[++i], (char **)NULL, 10);
            if (size <= 0) continue;
            heap_size = size;
            continue;
        }
        if (!strcmp(argv[i], "--gcstats")) {
            printf("--gcstats option set\n");
            continue;
        }
        if (!strcmp(argv[i], "--gcpurge")) {
            printf("--gcpurge option set\n");
            continue;
        }
        if (!strncmp("-", argv[i], strlen("-"))) {
            printf("unknown command line argument '%s', try '%s --help'\n", argv[i], argv[0]);
            exit(1);
        }
        if (code_file_specified) fatalError("Error: more than one code file specified");
        code_file = argv[i];
        code_file_specified = 1;
        if (debug_mode_activated) {
            if (i < argc - 1) continue;
            debug(code_file);
        }
    }
    return 0;
}
