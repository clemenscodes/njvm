#include <stdio.h>
#include <string.h>
#include "control_unit.h"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        check_args(argc, argv);
    } else {
        printf("Error: no code file specified\n");
    }
    return 0;
}
