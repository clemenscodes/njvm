#include "stack.h"

void initialize_stack(void) {
    vm.stack.size = 0;
    vm.stack.sp = 0;
    vm.stack.fp = 0;
}

void push(int immediate) {
    vm.stack.size++;
    vm.stack.data = realloc(vm.stack.data, (vm.stack.size + 1) * sizeof(int));
    vm.stack.data[vm.stack.sp] = immediate;
    vm.stack.sp++;
    vm.stack.data[vm.stack.sp] = 0;
}

int pop(void) {
    if (!(vm.stack.sp || vm.stack.data[vm.stack.sp])) {
        printf("Stack underflow: popped from empty stack\n");
        exit(1);
    }
    vm.stack.sp--;
    vm.stack.size--;
    int tmp = vm.stack.data[vm.stack.sp];
    vm.stack.data = realloc(vm.stack.data, vm.stack.size * sizeof(int));
    return tmp;
}

void print_stack(void) {
    printf("\n\tStack\n");
    printf(".-------+-------.\n");
    for (int i = vm.stack.sp; i >= 0; i--) {
        if (i == vm.stack.sp) {
            printf("|sp->%3d|%7d|\n", i, 0);
        } else {
            printf("|%7d|%7d|\n", i, vm.stack.data[i]);
        }
    }
    printf("'-------+-------'\n\n");
}
