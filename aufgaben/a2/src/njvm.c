#include <stdio.h>
#include <string.h>
#include "cpu/control_unit.h"
#include "boot/boot.h"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        check_args(argc, argv);
    } else {
        printf("Error: no code file specified\n");
    }
    return 0;
}
