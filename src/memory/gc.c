#include "gc.h"

void nullify_heap_stats(void) {
    vm.gc.total_copied_objects += vm.gc.copied_objects;
    vm.gc.total_copied_bytes += vm.gc.copied_bytes;
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
    // ObjRef *registers[5] = {&vm.rv, &bip.op1, &bip.op2, &bip.res, &bip.rem};
    // for (int i = 0; i < 5; i++) {
    //     registers[i] = relocate(registers[i]);
    // }
    vm.rv = relocate(vm.rv);
    bip.op1 = relocate(bip.op1);
    bip.op2 = relocate(bip.op2);
    bip.res = relocate(bip.res);
    bip.rem = relocate(bip.rem);
}

void relocate_sda_objects(void) {
    for (int i = 0; i < vm.sda.size; i++) {
        vm.sda.data[i] = relocate(vm.sda.data[i]);
    }
}

void relocate_stack_objects(void) {
    for (int i = 0; i < vm.stack.size; i++) {
        StackSlot slot = vm.stack.data[i];
        if (slot.is_obj_ref) {
            slot.u.obj_ref = relocate(slot.u.obj_ref);
        }
    }
}

ObjRef relocate(ObjRef obj_ref) {
    if (obj_ref == NULL) {
        return (ObjRef)NULL;
    }
    if (IS_COPIED(obj_ref)) {
        return get_obj_ref_from_forward_pointer(obj_ref);
    }
    unsigned bytes = get_obj_ref_bytes(obj_ref),
             size = get_obj_ref_size(obj_ref);
    ObjRef new_obj_ref = copy_obj_ref_to_free_memory(obj_ref, bytes, size);
    if (!new_obj_ref) {
        fatalError("Error: failed relocating object");
    }
    return new_obj_ref;
}

ObjRef copy_obj_ref_to_free_memory(ObjRef obj_ref, unsigned bytes, unsigned size) {
    if ((void *)obj_ref == NULL) {
        return NULL;
    }
    unsigned forward_pointer = vm.heap.used;
    ObjRef new_obj_ref = IS_PRIMITIVE(obj_ref) ? newPrimObject(size) : new_composite_object(size);
    if (!memcpy(new_obj_ref, obj_ref, bytes)) {
        fatalError("Error: failed copying memory");
    }
    set_broken_heart(obj_ref);
    set_forward_pointer(obj_ref, forward_pointer);
    collect_stats(bytes);
    return new_obj_ref;
}

void collect_stats(unsigned bytes) {
    vm.gc.copied_objects++;
    vm.gc.copied_bytes += bytes;
}

void scan(void) {
    unsigned char *scan = vm.heap.active;
    while (scan < vm.heap.next) {
        ObjRef obj_ref = (ObjRef)scan;
        unsigned bytes = get_obj_ref_bytes(obj_ref);
        if (!IS_PRIMITIVE(obj_ref)) {
            unsigned elements = GET_ELEMENT_COUNT(obj_ref);
            ObjRef *obj_refs = GET_REFS_PTR(obj_ref);
            for (int i = 0; i < elements; i++) {
                obj_refs[i] = relocate(obj_refs[i]);
            }
        }
        scan += bytes;
    }
}

void purge_heap(void) {
    if (vm.gc.purge_flag) {
        vm.heap.passive = calloc(vm.heap.available, sizeof(unsigned char));
    }
}

void print_gc_stats(void) {
    if (vm.gc.stats_flag) {
        printf("Garbage Collector:\n");
        printf("\t%u objects (%u bytes) allocated since last collection\n", vm.heap.size, vm.heap.used);
        printf("\t%u objects (%u bytes) copied during this collection\n", vm.gc.copied_objects, vm.gc.copied_bytes);
        printf("\t%u of %u  bytes free after this collection\n", vm.heap.available - vm.heap.used, vm.heap.available);
    }
}

void run_gc(void) {
    vm.gc.collections++;
    vm.gc.is_running = true;
    nullify_heap_stats();
    swap_heaps();
    relocate_registers();
    relocate_sda_objects();
    relocate_stack_objects();
    scan();
    purge_heap();
    print_gc_stats();
    vm.gc.is_running = false;
}
