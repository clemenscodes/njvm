#include "gc.h"

void nullify_heap_stats(void) {
    vm.gc.copied_objects = vm.gc.copied_bytes = vm.heap.used = vm.heap.size = 0;
}

void swap_heaps(void) {
    if (vm.heap.active == vm.heap.begin) {
        vm.heap.next = vm.heap.active = vm.heap.passive;
        vm.heap.passive = vm.heap.begin;
    } else {
        vm.heap.passive = vm.heap.active;
        vm.heap.next = vm.heap.active = vm.heap.begin;
    }
}

void relocate_registers(void) {
    ObjRef registers[5] = {vm.rv, bip.op1, bip.op2, bip.res, bip.rem};
    for (int i = 0; i < 5; i++) {
        registers[i] = copy_obj_ref(registers[i]);
    }
}

void relocate_stack_objects(void) {
    for (int i = 0; i < vm.stack.size; i++) {
        StackSlot slot = vm.stack.data[i];
        if (slot.is_obj_ref) {
            slot.u.obj_ref = copy_obj_ref(slot.u.obj_ref);
        }
    }
}

void relocate_sda_objects(void) {
    for (int i = 0; i < vm.sda.size; i++) {
        vm.sda.data[i] = copy_obj_ref(vm.sda.data[i]);
    }
}

void collect_stats(unsigned bytes) {
    vm.gc.copied_objects++;
    vm.gc.copied_bytes += bytes;
}

void run_gc(void) {
    nullify_heap_stats();
    swap_heaps();
    relocate_registers();
    relocate_stack_objects();
    relocate_sda_objects();
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

ObjRef copy_obj_ref(ObjRef obj_ref) {
    if (!obj_ref || !*(ObjRef *)obj_ref) {
        return NULL;
    }
    unsigned bytes = get_obj_ref_bytes(obj_ref),
           size = get_obj_ref_size(obj_ref),
           forward_pointer = vm.heap.used;
    ObjRef new_obj_ref = memcpy_obj_ref(obj_ref, bytes, size);
    collect_stats(bytes);
    // set_broken_heart(obj_ref);
    // set_forward_pointer(obj_ref, forward_pointer);
    return new_obj_ref;
}

ObjRef memcpy_obj_ref(ObjRef obj_ref, unsigned bytes, unsigned size) {
    ObjRef new_obj_ref;
    if (IS_PRIMITIVE(obj_ref)) {
        new_obj_ref = newPrimObject(size);
    } else {
        new_obj_ref = new_composite_object(size);
    }
    if (!memcpy(new_obj_ref, obj_ref, bytes)) {
        fatalError("Error: failed copying memory");
    }
    return new_obj_ref;
}

void print_gc_stats(void) {
    printf("Garbage Collector:\n");
    printf("\t%u objects (%u bytes) allocated since last collection\n", vm.heap.size, vm.heap.used);
    printf("\t%u objects (%u bytes) copied during this collection\n", vm.gc.copied_objects, vm.gc.copied_bytes);
    printf("\t%u of %u  bytes free after this collection\n", vm.heap.available - vm.heap.used, vm.heap.available);
}
