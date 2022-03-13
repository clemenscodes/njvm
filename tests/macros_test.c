#include "include/macros_test.h"

const struct CMUnitTest macros_unit_tests[] = {
    cmocka_unit_test(test_immediate_macro),
    cmocka_unit_test(test_sign_extend_macro),
    cmocka_unit_test(test_broken_heart_macro),
    cmocka_unit_test(test_is_primitive_macro),
    cmocka_unit_test(test_get_element_count_macro),
    cmocka_unit_test(test_get_refs_ptr_macro),
    cmocka_unit_test(test_forward_ptr_mask_macro),
    cmocka_unit_test(test_msb_and_bh_mask_macro),
    cmocka_unit_test(test_get_forward_ptr_macro),
    cmocka_unit_test(test_msb_macro),
};

void test_immediate_macro(void **state) {
    Bytecode instruction_with_opcode = 0xFFFFFFFF;
    Bytecode instruction_without_opcode = 0x00000000;
    Bytecode opcode_immediate = IMMEDIATE(instruction_with_opcode);
    Bytecode no_opcode_immediate = IMMEDIATE(instruction_without_opcode);
    assert_int_equal(opcode_immediate, 0x00FFFFFF);
    assert_int_equal(no_opcode_immediate, 0x00000000);
}

void test_sign_extend_macro(void **state) {
    Immediate positive = 0x00000001;
    Immediate negative = 0x00FFFFFF;
    positive = SIGN_EXTEND(positive);
    negative = SIGN_EXTEND(negative);
    assert_int_equal(positive, 1);
    assert_int_equal(negative, -1);
}

void test_msb_macro(void **state) {
    int test = 1;
    int msb = MSB;
    assert_int_not_equal(test, msb);
    print_memory_in_le_bytes(&msb, sizeof(int));
    print_memory_in_le_bits(&msb, sizeof(int));
    print_memory_in_le_bytes(&test, sizeof(int));
    print_memory_in_le_bits(&test, sizeof(int));
    test |= MSB;
    assert_int_equal(test, msb + 1);
    print_memory_in_le_bytes(&test, sizeof(int));
    print_memory_in_le_bits(&test, sizeof(int));
}

void test_broken_heart_macro(void **state) {}
void test_is_primitive_macro(void **state) {}
void test_get_element_count_macro(void **state) {}
void test_get_refs_ptr_macro(void **state) {}
void test_forward_ptr_mask_macro(void **state) {}
void test_msb_and_bh_mask_macro(void **state) {}
void test_get_forward_ptr_macro(void **state) {}
