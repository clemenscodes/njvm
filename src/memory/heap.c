#include "heap.h"

void initialize_heap(unsigned int memory) {
    vm.heap.memory = memory;
    vm.heap.bytes = vm.heap.memory * KiB;
    vm.heap.available = vm.heap.bytes / 2;
    vm.heap.active = calloc(vm.heap.bytes, 1);
    if (!vm.heap.active) {
        perror("malloc(vm.heap.active)");
    }
    vm.heap.next = vm.heap.begin = vm.heap.active;
    vm.heap.passive = vm.heap.next + vm.heap.available;
}

void *alloc(size_t size) {
    if ((vm.heap.used + size) > vm.heap.available) {
        run_gc();
        if ((vm.heap.used + size) > vm.heap.available) {
            fatalError("Error: heap overflow");
        }
    }
    void *p = vm.heap.next;
    vm.heap.next += size;
    if (!vm.heap.next) {
        fatalError("Error: failed calculating pointer to available memory");
    }
    vm.heap.available -= size;
    vm.heap.used += size;
    vm.heap.size++;
    return p;
}

void free_heap(void) {
    free(vm.heap.begin);
}
