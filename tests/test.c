#include "include/test.h"

int main() {
    vm.stack.memory = 64;
    vm.heap.memory = 8192;
    initialize_heap();
    initialize_stack();
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_encode_opcode),
        cmocka_unit_test(test_decode_opcode),
        cmocka_unit_test(test_instruction),
        cmocka_unit_test(test_encode_instruction),
        cmocka_unit_test(test_decode_instruction),
        cmocka_unit_test(test_ir),
        cmocka_unit_test(test_stack),
        cmocka_unit_test(test_sda),
        cmocka_unit_test(test_processor),
        cmocka_unit_test(test_utils),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
