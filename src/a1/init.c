#ifndef _INIT_C
#define _INIT_C

#include <stdio.h>
#include <string.h>

#include "program_memory.c"

void print_start() {
    printf("Ninja Virtual Machine started\n");
}

void print_stop() {
    printf("Ninja Virtual Machine stopped\n");
}

void print_usage() {
    printf("usage: ./njvm [option] [option] ...\n");
    printf("  --prog1          select program 1 to execute\n");
    printf("  --prog2          select program 2 to execute\n");
    printf("  --prog2          select program 3 to execute\n");
    printf("  --version        show version and exit\n");
    printf("  --help           show this help and exit\n");
}

void print_version() {
    printf("Ninja Virtual Machine version 0 (compiled Sep 23 2015, 10:36:52\n");
}

void print_err(char *arg) {
    printf("unknown command line argument '%s', try './njvm --help'\n", arg);
}

void program_1() {
    printf("Executing program 1\n");
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
}

void program_2() {
    printf("Executing program 2\n");
}

void program_3() {
    printf("Executing program 3\n");
}

int check_args(char *argv[]) {
    int help_result = strcmp(argv[1], "--help");
    int version_result = strcmp(argv[1], "--version");
    int prog1 = strcmp(argv[1], "--prog1");
    int prog2 = strcmp(argv[1], "--prog2");
    int prog3 = strcmp(argv[1], "--prog3");
    if (help_result == 0) {
        print_usage();
    } else if (version_result == 0) {
        print_version();
    } else if (prog1 == 0) {
        program_1();
    } else if (prog2 == 0) {
        program_2();
    } else if (prog3 == 0) { 
        program_3();
    } else {
        print_err(argv[1]);
    }
    return 0;
}

#endif
