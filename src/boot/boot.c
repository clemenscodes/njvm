#include "boot.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../cpu/control_unit.h"
#include "../ram/program_memory.h"

void print_usage(void) {
    printf("usage: ./njvm [option] [option] ...\n");
    printf("  --version        show version and exit\n");
    printf("  --help           show this help and exit\n");
    exit(0);
}

void print_version(void) {
    printf("Ninja Virtual Machine version 0 (compiled Sep 23 2015, 10:36:52)\n");
    exit(0);
}

void program_1(void) {
    init();
    register_instruction(pushc, 3);
    register_instruction(pushc, 4);
    register_instruction(add, 0);
    register_instruction(pushc, 10);
    register_instruction(pushc, 6);
    register_instruction(sub, 0);
    register_instruction(mul, 0);
    register_instruction(wrint, 0);
    register_instruction(pushc, 10);
    register_instruction(wrchr, 0);
    register_instruction(halt, 0);
    print_memory();
    work();
}

void program_2(void) {
    init();
    register_instruction(pushc, -2);
    register_instruction(rdint, 0);
    register_instruction(mul, 0);
    register_instruction(pushc, 3);
    register_instruction(add, 0);
    register_instruction(wrint, 0);
    register_instruction(pushc, '\n');
    register_instruction(wrchr, 0);
    register_instruction(halt, 0);
    print_memory();
    work();
}

void program_3(void) {
    init();
    register_instruction(rdchr, 0);
    register_instruction(wrint, 0);
    register_instruction(pushc, '\n');
    register_instruction(wrchr, 0);
    register_instruction(halt, 0);
    print_memory();
    work();
}

int check_args(int argc, char *argv[]) {
    int help_result = strcmp(argv[1], "--help");
    int version_result = strcmp(argv[1], "--version");
    if (help_result == 0) {
        print_usage();
    } else if (version_result == 0) {
        print_version();
        program_3();
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