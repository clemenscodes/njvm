#include "heap.h"

void initialize_heap() {
    vm.heap.bytes = vm.heap.memory * 1024;
    vm.heap.active = malloc(vm.heap.bytes / 2);
    if (!vm.heap.active) {
        perror("malloc(vm.heap.passive)");
    }
    vm.heap.passive = malloc(vm.heap.bytes / 2);
    if (!vm.heap.passive) {
        perror("malloc(vm.heap.passive)");
    }
    vm.heap.available = vm.heap.bytes / 2;
    vm.heap.used = 0;
    vm.heap.next = vm.heap.active;
}

ObjRef alloc(unsigned int bytes) {
    if ((vm.heap.used + bytes) > vm.heap.available) {
        fatalError("Error: heap is out of memory");
    }
    ObjRef next = (ObjRef)vm.heap.next;
    if (!next) {
        fatalError("Error: failed to allocate memory for compound object");
    }
    vm.heap.next += bytes;
    if (!vm.heap.next) {
        fatalError("Error: failed calculating next pointer to free memory");
    }
    vm.heap.used += bytes;
    return next;
}
