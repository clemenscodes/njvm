#include "heap.h"

void initialize_heap(unsigned memory) {
    vm.heap.memory = memory;
    vm.heap.bytes = vm.heap.memory * KiB;
    vm.heap.available = vm.heap.bytes / 2;
    if (vm.heap.available > FORWARD_PTR_MASK) {
        fatalError("Error: heap cannot address more than 2^30 bytes");
    }
    vm.heap.active = calloc(vm.heap.bytes, sizeof(unsigned char*));
    if (!vm.heap.active) {
        perror("calloc(vm.heap.active)");
    }
    vm.heap.next = vm.heap.begin = vm.heap.active;
    vm.heap.passive = vm.heap.next + vm.heap.available;
}

ObjRef alloc(unsigned bytes) {
    if ((vm.heap.used + bytes) > vm.heap.available) {
        if (!vm.gc.is_running) {
            run_gc();
        }
        if (((vm.heap.used + bytes) > vm.heap.available) && !vm.gc.is_running) {
            fatalError("Error: heap overflow");
        }
    }
    unsigned char *p = vm.heap.next;
    if (!p) {
        fatalError("Error: could not determine free memory");
    }
    vm.heap.next += bytes;
    if (!vm.heap.next) {
        fatalError("Error: failed calculating pointer to available memory");
    }
    vm.heap.used += bytes;
    vm.heap.size++;
    return (ObjRef)p;
}

void free_heap(void) {
    free(vm.heap.begin);
}

void purge_heap_half(void *half) {
    memset(half, 0, (size_t)vm.heap.available);
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
