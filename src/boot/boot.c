#include "boot.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cpu/control_unit.h"
#include "../memory/program_memory.h"

void print_usage(void) {
    printf("usage: ./njvm [option] [option] ...\n");
    printf("  --version        show version and exit\n");
    printf("  --help           show this help and exit\n");
    exit(0);
}

void print_version(void) {
    printf("Ninja Virtual Machine version 3 (compiled Sep 23 2015, 10:36:53)\n");
    exit(0);
}

int check_args(int argc, char *argv[]) {
    int help_result = strcmp(argv[1], "--help");
    int version_result = strcmp(argv[1], "--version");
    if (help_result == 0) {
        print_usage();
    } else if (version_result == 0) {
        print_version();
    } else {
        if (strncmp("-", argv[1], strlen("-")) == 0) {
            printf("unknown command line argument '%s', try '%s --help'\n", argv[1], argv[0]);
            exit(1);
        }
        if (argc > 2) {
            printf("Error: more than one code file specified\n");
            exit(1);
        }
        execute_binary(argv[1]);
    }
    return 0;
}