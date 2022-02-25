#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "njvm.h"

void print_usage(void) {
    printf("usage: ./njvm [option] [option] ...\n");
    printf("  --version        show version and exit\n");
    printf("  --help           show this help and exit\n");
    exit(0);
}

void print_version(void) {
    printf("Ninja Virtual Machine version %d (compiled Sep 23 2015, 10:36:53)\n", NINJA_BINARY_VERSION);
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error: no code file specified\n");
        exit(1);
    }
    char *arg = argv[1];
    int help_result = strcmp(arg, "--help");
    int version_result = strcmp(arg, "--version");
    if (!help_result) {
        print_usage();
    }
    if (!version_result) {
        print_version();
    }
    if (!strncmp("-", arg, strlen("-"))) {
        printf("unknown command line argument '%s', try '%s --help'\n", arg, argv[0]);
        exit(1);
    }
    if (argc > 2) {
        printf("Error: more than one code file specified\n");
        exit(1);
    }
    execute_binary(arg);
    return 0;
}
