#include "heap.h"

void initialize_heap() {
    vm.heap.bytes = vm.heap.memory * 1024;
    vm.heap.available = vm.heap.bytes / 2;
    vm.heap.used = vm.heap.size = 0;
    vm.heap.active = malloc(vm.heap.bytes);
    if (!vm.heap.active) {
        perror("malloc(vm.heap.active)");
    }
    vm.heap.next = vm.heap.begin = vm.heap.active;
    vm.heap.passive = vm.heap.next + vm.heap.available;
}

void *alloc(size_t size) {
    if ((vm.heap.used + size) > vm.heap.available) {
        printf("GC triggered\n");
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
    vm.heap.used += size;
    vm.heap.size++;
    return p;
}

void free_heap(void) {
    free(vm.heap.begin);
}
