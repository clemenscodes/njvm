#include "stack.h"

void initialize_stack(uint32_t bytes) {
    vm.stack.size = vm.stack.sp = vm.stack.fp = 0;
    vm.stack.data = calloc(bytes, sizeof(unsigned char));
    if (!vm.stack.data && vm.stack.size) perror("calloc(vm.stack.data)");
}

void push(Immediate immediate, bool is_obj_ref) {
    if (vm.stack.size >= MAX_ITEMS) fatal_error("Error: stack overflow");
    vm.stack.size++;
    vm.stack.data[vm.stack.sp].is_obj_ref = false;
    vm.stack.data[vm.stack.sp].u.value = immediate;
    vm.stack.sp++;
}

void push_obj_ref(ObjRef obj_ref) {
    if (vm.stack.size >= MAX_ITEMS) fatal_error("Error: stack overflow");
    vm.stack.size++;
    vm.stack.data[vm.stack.sp].is_obj_ref = true;
    vm.stack.data[vm.stack.sp].u.obj_ref = obj_ref;
    vm.stack.sp++;
}

Immediate pop(void) {
    if (!(vm.stack.sp || vm.stack.data[vm.stack.sp])) fatal_error("Stack underflow: popped from empty stack");
    vm.stack.sp--;
    vm.stack.size--;
    if (vm.stack.data[vm.stack.sp].is_obj_ref) fatal_error("Error: slot is obj_ref")
    return vm.stack.data[vm.stack.sp].u.value;
}

ObjRef pop_obj_ref(void) {
    if (!(vm.stack.sp || vm.stack.data[vm.stack.sp])) fatal_error("Stack underflow: popped from empty stack");
    vm.stack.sp--;
    vm.stack.size--;
    if (!vm.stack.data[vm.stack.sp].is_obj_ref) fatal_error("Error: slot is not obj_ref")
    return vm.stack.data[vm.stack.sp].u.obj_ref;
}

void free_stack(void) {
    free(vm.stack.data);
}

void print_stack(void) {
    int i, sp = vm.stack.sp, fp = vm.stack.fp;
    for (i = sp; i >= 0; i--) {
        StackSlot slot = vm.stack.data[i];
        char *type = slot.is_obj_ref ? "objref\0" : "number\0";
        if (!sp && !fp)
            printf("sp, fp --->\t%04d:\txxxx\n", i);
        else if (sp == fp) {
            if (slot.is_obj_ref)
                printf("sp, fp --->\t%04d: (%s) \t%p\n", i, type, vm.stack.data[i].u.obj_ref);
            else
                printf("sp, fp --->\t%04d: (%s) \t%d\n", i, type, vm.stack.data[i].u.value);
        }
        if (i != sp && i != fp) {
            if (slot.is_obj_ref)
                printf("\t\t%04d: (%s) \t%p\n", i, type, vm.stack.data[i].u.obj_ref);
            else
                printf("\t\t%04d: (%s) \t%d\n", i, type, vm.stack.data[i].u.value);
        }
        if (i == sp && i != fp) printf("sp \t --->\t%04d:\txxxx\n", sp);
        if (i == fp && i != sp && fp == 0) {
            if (slot.is_obj_ref)
                printf("fp \t --->\t%04d: (%s) \t%p\n", fp, type, vm.stack.data[fp].u.obj_ref);
            else
                printf("fp \t --->\t%04d: (%s) \t%d\n", fp, type, vm.stack.data[fp].u.value);
        }
        if (i == fp && i != sp && fp != 0) {
            if (slot.is_obj_ref)
                printf("fp \t --->\t%04d: (%s) \t%p\n", fp, type, vm.stack.data[fp].u.obj_ref);
            else
                printf("fp \t --->\t%04d: (%s) \t%d\n", fp, type, vm.stack.data[fp].u.value);
        }
    }
}
