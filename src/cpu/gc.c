#include "gc.h"

void run_gc(void) {
    vm.gc.copied_objects = 0;
    vm.gc.copied_bytes = 0;
    if (vm.heap.active == vm.heap.begin) {
        vm.heap.next = vm.heap.active = vm.heap.passive;
        vm.heap.passive = vm.heap.begin;
    } else {
        vm.heap.passive = vm.heap.active;
        vm.heap.next = vm.heap.active = vm.heap.begin;
    }
}

void print_gc_stats(void) {
    printf("Garbage Collector:\n");
    printf("\t%ld objects (%ld bytes) allocated since last collection\n", vm.heap.size, vm.heap.used);
    printf("\t%ld objects (%ld bytes) copied during this collection\n", vm.gc.copied_objects, vm.gc.copied_bytes);
    printf("\t%ld of %ld bytes free after this collection\n", vm.heap.available - vm.heap.used, vm.heap.available);
}