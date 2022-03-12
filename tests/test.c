#include "include/test.h"

int main() {
    const struct CMUnitTest opcode[] = {
        cmocka_unit_test(test_encode_opcode),
        cmocka_unit_test(test_decode_opcode),
    };
    const struct CMUnitTest instruction[] = {
        cmocka_unit_test(test_instruction),
        cmocka_unit_test(test_encode_instruction),
        cmocka_unit_test(test_decode_instruction),
    };
    const struct CMUnitTest ir[] = {
        cmocka_unit_test(test_default_ir),
    };
     const struct CMUnitTest utils[] = {
        cmocka_unit_test(test_utils),
    };
    const struct CMUnitTest stack[] = {
        cmocka_unit_test(test_default_stack),
        cmocka_unit_test(test_initialize_stack),
    };
    const struct CMUnitTest heap[] = {
        cmocka_unit_test(test_default_heap),
        cmocka_unit_test(test_initialize_heap),
        cmocka_unit_test(test_alloc),
    };
    const struct CMUnitTest sda[] = {
        cmocka_unit_test(test_default_sda),
    };
    const struct CMUnitTest processor[] = {
        cmocka_unit_test(test_processor),
    };
    const struct CMUnitTest gc[] = {
        cmocka_unit_test(test_run_gc),
        cmocka_unit_test(test_copy_obj_ref),
        cmocka_unit_test(test_copy_obj_ref_returns_null),
    };
    int result = 0;
    result += cmocka_run_group_tests(opcode, NULL, NULL);
    result += cmocka_run_group_tests(instruction, NULL, NULL);
    result += cmocka_run_group_tests(ir, setup, teardown);
    result += cmocka_run_group_tests(utils, setup, teardown);
    result += cmocka_run_group_tests(stack, setup, teardown);
    result += cmocka_run_group_tests(heap, setup, teardown);
    result += cmocka_run_group_tests(sda, setup, teardown);
    result += cmocka_run_group_tests(processor, setup, teardown);
    result += cmocka_run_group_tests(gc, setup, teardown);
    return result;
}

static int setup(void **state) {
    vm = default_vm();
    return 0;
}

static int teardown(void **state) {
    bip.op1 = bip.op2 = bip.res = bip.rem = NULL;
    if (vm.heap.begin) {
        free(vm.heap.begin);
    }
    if (vm.stack.data) {
        free(vm.stack.data);
    }
    if (vm.rv) {
        free(vm.rv);
    }
    if (vm.bp) {
        free(vm.bp);
    }
    if (vm.ir.data) {
        free(vm.ir.data);
    }
    if (vm.sda.data) {
        free(vm.sda.data);
    }
    return 0;
}
