#include "sda.h"

void initialize_sda(size_t variable_count) {
    vm.sda.size = variable_count;
    vm.sda.data = calloc(vm.sda.size, sizeof(ObjRef));
    if (!vm.sda.data) {
        perror("malloc(vm.sda.data)");
    }
}

void push_global(Immediate immediate) {
    push_obj_ref(vm.sda.data[immediate]);
}

void pop_global(Immediate immediate) {
    vm.sda.data[immediate] = pop_obj_ref();
}

void free_sda(void) {
    free(vm.sda.data);
}

void print_sda(void) {
    if (!vm.sda.size) {
        printf("data[%04u]:\t[empty]\n", 0);
    }
    for (int i = 0; i < vm.sda.size; i++) {
        printf("data[%04u]:\t[%p]\n", i, (void *)vm.sda.data[i]);
    }
}
