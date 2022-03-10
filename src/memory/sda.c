#include "sda.h"

void initialize_sda(void) {
    vm.sda.data = alloc(vm.sda.size * sizeof(ObjRef));
    if (!vm.sda.data) {
        perror("malloc(vm.sda.data)");
    }
}

void push_global(Immediate immediate) {
    if (immediate >= vm.sda.size || immediate < 0)  {
        fatalError("Error: sda index out of bound");
    }
    push_obj_ref(vm.sda.data[immediate]);
}

void pop_global(Immediate immediate) {
    if (immediate >= vm.sda.size || immediate < 0)  {
        fatalError("Error: sda index out of bound");
    }
    vm.sda.data[immediate] = pop_obj_ref();
}

void print_sda(void) {
    if (!vm.sda.size) {
        printf("data[%04u]:\t[empty]\n", 0);
    }
    for (int i = 0; i < vm.sda.size; i++) {
        printf("data[%04u]:\t[%p]\n", i, (void *)vm.sda.data[i]);
    }
}
