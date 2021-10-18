#ifndef _NJVM_C
#define _NJVM_C

#include <stdio.h>
#include <string.h>
#include "control_unit.c"
#include "init.c"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        check_args(argv);
    } else {
        init();
        shutdown();
    }
    return 0;
}

#endif
