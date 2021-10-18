#ifndef _NJVM_C
#define _NJVM_C

#include <stdio.h>
#include <string.h>
#include "stack.c"
#include "init.c"
#include "program_memory.c"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        check_args(argv);
    } else {
        print_start();
        print_memory();
        print_stop();
    }
    return 0;
}

#endif
