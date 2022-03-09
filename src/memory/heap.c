#include "heap.h"

void initialize_heap() {
    vm.heap.bytes = vm.heap.memory * 1024;
    vm.heap.available = vm.heap.bytes / 2;
    vm.heap.used = 0;
    vm.heap.active = malloc(vm.heap.available);
    if (!vm.heap.active) {
        perror("malloc(vm.heap.active)");
    }
    vm.heap.passive = malloc(vm.heap.available);
    if (!vm.heap.passive) {
        perror("malloc(vm.heap.passive)");
    }
    vm.heap.next = vm.heap.active;
}

void *alloc(unsigned int bytes) {
    if ((vm.heap.used + bytes) > vm.heap.available) {
        fatalError("Error: heap is out of memory");
    }
    void *p = vm.heap.next;
    vm.heap.next += bytes;
    if (!vm.heap.next) {
        fatalError("Error: failed calculating pointer to available memory");
    }
    vm.heap.used += bytes;
    return p;
}

void free_heap(void) {
    free(vm.heap.active);
    free(vm.heap.passive);
}
