#include "gc.h"

void run_gc(void) {
    vm.gc.copied_objects = vm.gc.copied_bytes = vm.heap.used = vm.heap.size = 0;
    if (vm.heap.active == vm.heap.begin) {
        vm.heap.next = vm.heap.active = vm.heap.passive;
        vm.heap.passive = vm.heap.begin;
    } else {
        vm.heap.passive = vm.heap.active;
        vm.heap.next = vm.heap.active = vm.heap.begin;
    }
    ObjRef *registers[5] = {&vm.rv, &bip.op1, &bip.op2, &bip.res, &bip.rem};
    for (int i = 0; i < 5; i++) {
        copy_obj_ref(*registers[i]);
    }
    for (int i = 0; i < vm.stack.size; i++) {
        StackSlot slot = vm.stack.data[i];
        if (slot.is_obj_ref) {
            copy_obj_ref(slot.u.obj_ref);
        }
    }
    for (int i = 0; i < vm.sda.size; i++) {
        copy_obj_ref(vm.sda.data[i]);
    }
    // Scan phase
    // Check active heap for objects
    // Skip copied primitive objects
    // Check references of compound objects
    // If broken heart flag set, use forward pointer and update the reference
    // Else copy_obj_ref()
    // Set reference in object to forward pointer of copied object
    // Inspect newly copied object for further references and repeat
    if (vm.gc.purge_flag) {
        // Purge passive heap
    }
    if (vm.gc.stats_flag) {
        print_gc_stats();
    }
}

void copy_obj_ref(ObjRef obj_ref) {
    collect_obj_ref_stats(obj_ref);
    // Set broken heart flag in root object
    // Set forward pointer to current next pointer in root object
    // Copy root object to current next pointer using memcpy
    // Increment next pointer with calculated root object size
}

void collect_obj_ref_stats(ObjRef obj_ref) {
    vm.gc.copied_objects++;
    vm.gc.copied_bytes += get_obj_ref_bytes(obj_ref);
}

void print_gc_stats(void) {
    printf("Garbage Collector:\n");
    printf("\t%ld objects (%ld bytes) allocated since last collection\n", vm.heap.size, vm.heap.used);
    printf("\t%ld objects (%ld bytes) copied during this collection\n", vm.gc.copied_objects, vm.gc.copied_bytes);
    printf("\t%ld of %ld bytes free after this collection\n", vm.heap.available - vm.heap.used, vm.heap.available);
}
