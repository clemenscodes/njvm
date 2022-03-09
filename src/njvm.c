#include "njvm.h"

NinjaVM vm;

int njvm(int argc, char *argv[]) {
    vm.stack.memory = 64, vm.heap.memory = 8192;
    vm.debugger.activated = false;
    bool code_flag = false;
    char *code_file = NULL;
    for (int i = 1; i <= argc; i++) {
        if (i == argc) {
            if (!code_flag) {
                fatalError("Error: no code file specified");
            }
            init(code_file);
        }
        if (!strcmp(argv[i], "--debug")) {
            vm.debugger.activated = true;
            continue;
        }
        if (!strcmp(argv[i], "--help")) {
            printf("usage: ./njvm [options] <code file>\n");
            printf("Options:\n");
            printf("  --stack <n>\t   set stack size to n KBytes (default: n = 64)\n");
            printf("  --heap <n>\t   set heap size to n KBytes (default: n = 8192)\n");
            printf("  --gcstats\t   show garbage collection stats\n");
            printf("  --gcpurge\t   purge old objects after collection\n");
            printf("  --debug\t   start virtual machine in debug mode\n");
            printf("  --version\t   show version and exit\n");
            printf("  --help\t   show this help and exit\n");
            exit(0);
        }
        if (!strcmp(argv[i], "--version")) {
            printf("Ninja Virtual Machine version %d (compiled %s, %s)\n", NINJA_BINARY_VERSION, __DATE__, __TIME__);
            exit(0);
        }
        if (!strcmp(argv[i], "--stack")) {
            if (i >= argc - 1) {
                continue;
            }
            int memory = strtol(argv[++i], (char **)NULL, 10);
            if (memory <= 0) {
                continue;
            }
            vm.stack.memory = memory;
            continue;
        }
        if (!strcmp(argv[i], "--heap")) {
            if (i >= argc - 1) {
                continue;
            }
            int memory = strtol(argv[++i], (char **)NULL, 10);
            if (memory <= 0) {
                continue;
            }
            vm.heap.memory = memory;
            continue;
        }
        if (!strcmp(argv[i], "--gcstats")) {
            vm.gc.stats_flag = true;
            continue;
        }
        if (!strcmp(argv[i], "--gcpurge")) {
            vm.gc.purge_flag = true;
            continue;
        }
        if (!strncmp("-", argv[i], strlen("-"))) {
            printf("unknown command line argument '%s', try '%s --help'\n", argv[i], argv[0]);
            exit(1);
        }
        if (code_flag) {
            fatalError("Error: more than one code file specified");
        }
        code_file = argv[i];
        code_flag = true;
        if (i < argc - 1) {
            continue;
        }
        init(code_file);
    }
    return 0;
}
