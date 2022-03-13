#include "include/test.h"

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

int main() {
    int result = 0;
    result += cmocka_run_group_tests(opcode_unit_tests, NULL, NULL);
    result += cmocka_run_group_tests(immediate_unit_tests, NULL, NULL);
    result += cmocka_run_group_tests(instruction_unit_tests, NULL, NULL);
    result += cmocka_run_group_tests(ir_unit_tests, setup, teardown);
    result += cmocka_run_group_tests(utils_unit_tests, setup, teardown);
    result += cmocka_run_group_tests(macros_unit_tests, setup, teardown);
    result += cmocka_run_group_tests(stack_unit_tests, setup, teardown);
    result += cmocka_run_group_tests(heap_unit_tests, setup, teardown);
    result += cmocka_run_group_tests(sda_unit_tests, setup, teardown);
    result += cmocka_run_group_tests(processor_unit_tests, setup, teardown);
    result += cmocka_run_group_tests(gc_unit_tests, setup, teardown);
    result += cmocka_run_group_tests(debugger_unit_tests, setup, teardown);
    return result;
}
