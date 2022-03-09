#include "gc.h"

void run_gc(void) {
    vm.gc.copied_objects = vm.gc.copied_bytes = 0;
    if (vm.heap.active == vm.heap.begin) {
        vm.heap.next = vm.heap.active = vm.heap.passive;
        vm.heap.passive = vm.heap.begin;
    } else {
        vm.heap.passive = vm.heap.active;
        vm.heap.next = vm.heap.active = vm.heap.begin;
    }
    vm.heap.used = vm.heap.size = 0;
    // Copy phase
    // Check RV, BIP, Stack, SDA for Root objects
    // For root object: copy_obj_ref()
    //
    // copy_obj_ref():
    // Calculate bytes of object
    // Increment copy counter, copied byte counter
    // Set broken heart flag in root object
    // Set forward pointer to current next pointer in root object
    // Copy root object to current next pointer using memcpy
    // Increment next pointer with calculated root object size
    // 
    // End Copy Phase
    //
    // Scan phase
    // Check active heap for objects
    // Skip copied primitive objects
    // Check references of compound objects
    // If broken heart flag set, use forward pointer and update the reference
    // Else copy_obj_ref()
    // Set reference in object to forward pointer of copied object
    // Inspect newly copied object for further references and repeat
    //
    // End Scan phase
    // 
    // Purge passive heap
    // 
    // End GC
}

void print_gc_stats(void) {
    printf("Garbage Collector:\n");
    printf("\t%ld objects (%ld bytes) allocated since last collection\n", vm.heap.size, vm.heap.used);
    printf("\t%ld objects (%ld bytes) copied during this collection\n", vm.gc.copied_objects, vm.gc.copied_bytes);
    printf("\t%ld of %ld bytes free after this collection\n", vm.heap.available - vm.heap.used, vm.heap.available);
}