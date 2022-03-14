#include "include/macros_test.h"

const struct CMUnitTest macros_unit_tests[] = {
    cmocka_unit_test(test_immediate_macro),
    cmocka_unit_test(test_sign_extend_macro),
    cmocka_unit_test(test_msb_macro),
    cmocka_unit_test(test_broken_heart_macro),
    cmocka_unit_test(test_is_primitive_macro),
    cmocka_unit_test(test_get_element_count_macro),
    cmocka_unit_test(test_get_refs_ptr_macro),
    cmocka_unit_test(test_copied_mask_macro),
    cmocka_unit_test(test_is_copied_macro),
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
    print_memory_in_le_bytes(&test, sizeof(int));
    test |= MSB;
    assert_int_equal(test, msb + 1);
    print_memory_in_le_bytes(&test, sizeof(int));
}

void test_broken_heart_macro(void **state) {
    int test = 1 | MSB;
    int broken_heart = BROKEN_HEART;
    assert_int_not_equal(test, broken_heart);
    assert_int_equal(broken_heart, 0x40000000);
    print_memory_in_le_bytes(&broken_heart, sizeof(int));
    print_memory_in_le_bytes(&test, sizeof(int));
    test |= BROKEN_HEART;
    assert_int_equal(test, (broken_heart | MSB) + 1);
    print_memory_in_le_bytes(&test, sizeof(int));
}

void test_is_primitive_macro(void **state) {
    ObjRef test_primitive_obj_ref = newPrimObject(4);
    ObjRef test_composite_obj_ref = new_composite_object(4);
    assert_true(IS_PRIMITIVE(test_primitive_obj_ref));
    assert_false(IS_PRIMITIVE(test_composite_obj_ref));
}

void test_is_copied_macro(void **state) {
    ObjRef test_primitive_obj_ref = newPrimObject(4);
    print_memory_in_be_bits(test_primitive_obj_ref, 4);
    print_memory_in_be_bytes(test_primitive_obj_ref, 4);
    unsigned copied_mask = COPIED_MASK;
    print_memory_in_be_bits(&copied_mask, 4);
    print_memory_in_be_bytes(&copied_mask, 4);
    assert_false(IS_COPIED(test_primitive_obj_ref));
    test_primitive_obj_ref->size = COPIED_MASK;
    print_memory_in_be_bits(test_primitive_obj_ref, 4);
    print_memory_in_be_bytes(test_primitive_obj_ref, 4);
    assert_true(IS_COPIED(test_primitive_obj_ref));
}

void test_get_element_count_macro(void **state) {
    size_t elements = 4;
    ObjRef test_obj_ref = new_composite_object(elements);
    assert_int_equal(elements, GET_ELEMENT_COUNT(test_obj_ref));
}

void test_get_refs_ptr_macro(void **state) {
    ObjRef test_obj_ref = new_composite_object(2);
    ObjRef *test_obj_ref_refs = GET_REFS_PTR(test_obj_ref);
    assert_ptr_equal((ObjRef *)test_obj_ref->data, test_obj_ref_refs);
}

void test_copied_mask_macro(void **state) {
    unsigned int forward_pointer_mask = COPIED_MASK;
    print_memory_in_be_bytes(&forward_pointer_mask, 4);
    ObjRef test_obj_ref = new_composite_object(1);
    ObjRef test_primitive = newPrimObject(4);
    print_memory_in_be_bytes(&test_obj_ref, 8);
    print_memory_in_be_bytes(&test_primitive, 8);
    print_obj_ref_in_be_bytes(test_obj_ref);
    GET_REFS_PTR(test_obj_ref)[0] = test_primitive;
    print_obj_ref_in_be_bytes(test_obj_ref);
    print_obj_ref_in_be_bytes(test_primitive);
}
