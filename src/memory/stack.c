#include "stack.h"

void initialize_stack(void) {
    vm.stack.size = 0;
    vm.stack.sp = 0;
    vm.stack.fp = 0;
}

void push(Immediate immediate) {
    vm.stack.size++;
    vm.stack.data = realloc(vm.stack.data, (vm.stack.size) * sizeof(int));
    vm.stack.data[vm.stack.sp] = immediate;
    vm.stack.sp++;
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
    int sp = vm.stack.sp;
    int fp = vm.stack.fp;
    for (int slot = sp; slot >= 0; slot--) {
        if (!sp && !fp) {
            printf("sp, fp --->\t%04d:\txxxx\n", slot);
        } else if (sp == fp) {
            printf("sp, fp --->\t%04d:\t%d\n", slot, vm.stack.data[slot]);
        }
        if (slot != sp && slot != fp) {
            printf("\t\t%04d:\t%d\n", slot, vm.stack.data[slot]);
        }
        if (slot == sp && slot != fp) {
            printf("sp \t --->\t%04d:\txxxx\n", sp);
        }
        if (slot == fp && slot != sp && fp == 0) {
            printf("fp \t --->\t%04d:\t%d\n", fp, vm.stack.data[fp]);
        }
        if (slot == fp && slot != sp && fp != 0) {
            printf("fp \t --->\t%04d:\t%d\n", fp, vm.stack.data[fp]);
        }
    }
}
