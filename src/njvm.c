#include "njvm.h"

NinjaVM vm;

int njvm(int argc, char *argv[]) {
    int i, code_file_specified = 0, debug_mode_activated = 0;
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
            printf("  --debug \tstart virtual machine in debug mode\n");
            printf("  --version \tshow version and exit\n");
            printf("  --help \tshow this help and exit\n");
            exit(0);
        }
        if (!strcmp(argv[i], "--version")) {
            printf("Ninja Virtual Machine version %d (compiled Sep 23 2015, 10:36:53)\n", NINJA_BINARY_VERSION);
            exit(0);
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
