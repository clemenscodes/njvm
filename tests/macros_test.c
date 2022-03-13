#include "include/macros_test.h"

const struct CMUnitTest macros_unit_tests[] = {
    cmocka_unit_test(test_immediate_macro),
    cmocka_unit_test(test_sign_extend_macro),
    cmocka_unit_test(test_msb_macro),
    cmocka_unit_test(test_broken_heart_macro),
    cmocka_unit_test(test_is_primitive_macro),
    cmocka_unit_test(test_get_element_count_macro),
    cmocka_unit_test(test_get_refs_ptr_macro),
    cmocka_unit_test(test_forward_ptr_mask_macro),
    cmocka_unit_test(test_msb_and_bh_mask_macro),
    cmocka_unit_test(test_get_forward_ptr_macro),
};

void test_immediate_macro(void **state) {}
void test_sign_extend_macro(void **state) {}
void test_msb_macro(void **state) {}
void test_broken_heart_macro(void **state) {}
void test_is_primitive_macro(void **state) {}
void test_get_element_count_macro(void **state) {}
void test_get_refs_ptr_macro(void **state) {}
void test_forward_ptr_mask_macro(void **state) {}
void test_msb_and_bh_mask_macro(void **state) {}
void test_get_forward_ptr_macro(void **state) {}
