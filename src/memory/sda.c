#include "sda.h"

void initialize_sda(uint32_t variable_count) {
    vm.sda.size = variable_count;
    vm.sda.data = calloc(vm.sda.size, sizeof(int));
    if (!vm.sda.data) {
        perror("malloc(sda.data)");
        exit(1);
    }
}

void push_global(int n) {
    push(vm.sda.data[n]);
}

void pop_global(int n) {
    vm.sda.data[n] = pop();
}

void free_sda(void) {
    free(vm.sda.data);
}

void print_sda(void) {
    for (int i = 0; i < vm.sda.size; i++) {
        printf("data[%04u]:\t[%d]\n", i, vm.sda.data[i]);
    }
}
