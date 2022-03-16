#include "heap.h"

void initialize_heap(unsigned memory) {
    vm.heap.memory = memory;
    vm.heap.bytes = vm.heap.memory * KiB;
    vm.heap.available = vm.heap.bytes / 2;
    if (vm.heap.available > FORWARD_PTR_MASK) {
        fatalError("heap cannot address more than 2^30 bytes");
    }
    vm.heap.active = malloc(vm.heap.bytes);
    if (!vm.heap.active) {
        perror("malloc(vm.heap.active)");
    }
    vm.heap.next = vm.heap.begin = vm.heap.active;
    vm.heap.passive = vm.heap.next + vm.heap.available;
}

void *alloc(unsigned bytes) {
    if ((vm.heap.used + bytes) > vm.heap.available) {
        if (!vm.gc.is_running) {
            run_gc();
        }
        if ((vm.heap.used + bytes) > vm.heap.available) {
            fatalError("heap overflow");
        }
    }
    void *p = vm.heap.next;
    if (!p) {
        fatalError("could not determine free memory");
    }
    vm.heap.next += bytes;
    if (!vm.heap.next) {
        fatalError("failed calculating pointer to available memory");
    }
    vm.heap.used += bytes;
    vm.heap.size++;
    return p;
}

void free_heap(void) {
    free(vm.heap.begin);
}

void print_heap_objects(void) {
    int i = 0;
    unsigned char *p = vm.heap.active;
    unsigned bytes = get_obj_ref_bytes((ObjRef)p);
    while (i < vm.heap.used) {
        print_obj_ref((ObjRef)p);
        p += bytes;
        i += bytes;
        bytes = get_obj_ref_bytes((ObjRef)p);
    }
}

void print_heap_bytes(void) {
    int i = 0;
    unsigned char *p = vm.heap.active;
    while (i < vm.heap.used) {
        print_memory_in_be_bytes(p, 4);
        p += 4;
        i += 4;
    }
}
