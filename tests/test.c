#include "include/test.h"

void test_setup(void) {
    vm = default_vm();
    initialize_heap();
    initialize_stack();
}

int main() {
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
        cmocka_unit_test(test_initialize_heap),
        cmocka_unit_test(test_alloc),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
