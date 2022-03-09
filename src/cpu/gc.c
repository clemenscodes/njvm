#include "gc.h"

void run_gc(void) {
    vm.gc.copied_objects = 0;
    vm.gc.copied_bytes = 0;
}

void print_gc_stats(void) {
    printf("Garbage Collector:\n");
    printf("\t%ld objects (%ld bytes) allocated since last collection\n", vm.heap.size, vm.heap.used);
    printf("\t%ld objects (%ld bytes) copied during this collection\n", vm.gc.copied_objects, vm.gc.copied_bytes);
    printf("\t%ld of %ld bytes free after this collection\n", vm.heap.available - vm.heap.used, vm.heap.available);
}