#include <stdio.h>
#include <string.h>
#include "stack.c"
#include "init.c"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        check_args(argv);
    } else {
        print_start();
        print_stop();
    }
    return 0;
}
