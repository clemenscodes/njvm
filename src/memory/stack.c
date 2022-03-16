#include "stack.h"

void initialize_stack(unsigned memory) {
    vm.stack.memory = memory;
    vm.stack.bytes = vm.stack.memory * Ki;
    vm.stack.max_items = vm.stack.bytes / sizeof(StackSlot);
    vm.stack.data = malloc(vm.stack.bytes);
    if (!vm.stack.data && vm.stack.size) {
        perror("malloc(vm.stack.data)");
    }
}

void push(Immediate immediate) {
    if (vm.stack.size >= vm.stack.max_items) {
        fatalError("stack overflow");
    }
    vm.stack.size++;
    vm.stack.data[vm.stack.sp].is_obj_ref = false;
    vm.stack.data[vm.stack.sp].u.value = immediate;
    vm.stack.sp++;
}

void push_obj_ref(ObjRef obj_ref) {
    if (vm.stack.size >= vm.stack.max_items) {
        fatalError("stack overflow");
    }
    vm.stack.size++;
    vm.stack.data[vm.stack.sp].is_obj_ref = true;
    vm.stack.data[vm.stack.sp].u.obj_ref = obj_ref;
    vm.stack.sp++;
}

Immediate pop(void) {
    if (!vm.stack.sp) {
        fatalError("Stack underflow: popped from empty stack");
    }
    vm.stack.sp--;
    vm.stack.size--;
    if (vm.stack.data[vm.stack.sp].is_obj_ref) {
        fatalError("slot is object, but shouldn't be");
    }
    return vm.stack.data[vm.stack.sp].u.value;
}

ObjRef pop_obj_ref(void) {
    if (!vm.stack.sp) {
        fatalError("Stack underflow: popped from empty stack");
    }
    vm.stack.sp--;
    vm.stack.size--;
    if (!vm.stack.data[vm.stack.sp].is_obj_ref) {
        fatalError("slot is object, but shouldn't be");
    }
    return vm.stack.data[vm.stack.sp].u.obj_ref;
}

void free_stack(void) {
    free(vm.stack.data);
}

void print_stack(void) {
    int sp = vm.stack.sp, fp = vm.stack.fp;
    for (int i = sp; i >= 0; i--) {
        StackSlot slot = vm.stack.data[i];
        ObjRef obj_ref;
        Immediate value;
        char *type = slot.is_obj_ref ? "objref\0" : "number\0";
        if (!sp && !fp) {
            printf("sp, fp --->\t%04d: (xxxxxx) \txxxxxxx\n", i);
        } else if (i == sp && i == fp) {
            if (slot.is_obj_ref) {
                obj_ref = slot.u.obj_ref;
                if (slot.u.obj_ref) {
                    if (IS_PRIMITIVE(obj_ref)) {
                        printf("sp, fp --->\t%04d: (%s) \t%p ---> [", i, type,
                               (void *)obj_ref);
                        bip.op1 = obj_ref;
                        bigPrint(stdout);
                        printf("]\n");
                    } else {
                        printf("sp, fp --->\t%04d: (%s) \t%p ---> (objref) -> "
                               "size: [%u]\n",
                               i, type, (void *)obj_ref,
                               GET_ELEMENT_COUNT(obj_ref));
                    }
                } else {
                    printf("sp, fp --->\t%04d: (%s) \t%p\n", i, type,
                           (void *)obj_ref);
                }
            } else {
                value = slot.u.value;
                printf("sp, fp --->\t%04d: (%s) \t%d\n", i, type, value);
            }
        }
        if (i != sp && i != fp) {
            if (slot.is_obj_ref) {
                obj_ref = slot.u.obj_ref;
                if (slot.u.obj_ref) {
                    if (IS_PRIMITIVE(obj_ref)) {
                        printf("\t\t%04d: (%s) \t%p ---> [", i, type,
                               (void *)obj_ref);
                        bip.op1 = obj_ref;
                        bigPrint(stdout);
                        printf("]\n");
                    } else {
                        printf(
                            "\t\t%04d: (%s) \t%p ---> (objref) -> size: [%u]\n",
                            i, type, (void *)obj_ref,
                            GET_ELEMENT_COUNT(obj_ref));
                    }
                } else {
                    printf("\t\t%04d: (%s) \t%p\n", i, type, (void *)obj_ref);
                }
            } else {
                value = slot.u.value;
                printf("\t\t%04d: (%s) \t%d\n", i, type, value);
            }
        }
        if (i == sp && i != fp) {
            printf("sp \t --->\t%04d: (xxxxxx) \txxxxxx\n", sp);
        }
        if (i == fp && i != sp && fp != 0) {
            if (slot.is_obj_ref) {
                obj_ref = vm.stack.data[fp].u.obj_ref;
                if (slot.u.obj_ref) {
                    if (IS_PRIMITIVE(obj_ref)) {
                        printf("fp \t --->\t%04d: (%s) \t%p ---> [", fp, type,
                               (void *)obj_ref);
                        bip.op1 = obj_ref;
                        bigPrint(stdout);
                        printf("]\n");
                    } else {
                        printf("fp \t --->\t%04d: (%s) \t%p ---> (objref) -> "
                               "size: [%u]\n",
                               i, type, (void *)obj_ref,
                               GET_ELEMENT_COUNT(obj_ref));
                    }
                } else {
                    printf("fp \t --->\t%04d: (%s) \t%p\n", fp, type,
                           (void *)obj_ref);
                }
            } else {
                value = vm.stack.data[fp].u.value;
                printf("fp \t --->\t%04d: (%s) \t%d\n", fp, type, value);
            }
        }
    }
}
