#include "include/utils_test.h"

const struct CMUnitTest utils_unit_tests[] = {
    cmocka_unit_test(test_open_file),
    cmocka_unit_test(test_seek_file),
    cmocka_unit_test(test_close_file),
    cmocka_unit_test(test_check_ninja_binary_format),
    cmocka_unit_test(test_check_ninja_version),
    cmocka_unit_test(test_check_ninja_instruction_count),
    cmocka_unit_test(test_check_ninja_variable_count),
    cmocka_unit_test(test_new_composite_object),
    cmocka_unit_test(test_set_broken_heart),
    cmocka_unit_test(test_set_forward_pointer),
    cmocka_unit_test(test_get_obj_ref_from_forward_pointer),
    cmocka_unit_test(test_get_obj_ref_bytes),
    cmocka_unit_test(test_get_obj_ref_size),
};

void test_new_composite_object(void **state) {
    initialize_heap(DEFAULT_HEAP_SIZE);
    int set_size = 4;
    ObjRef obj_ref = new_composite_object(set_size);
    assert_false(IS_PRIMITIVE(obj_ref));
    int get_size = GET_ELEMENT_COUNT(obj_ref);
    assert_int_equal(set_size, get_size);
    for (int i = 0; i < set_size; i++) {
        assert_null(GET_REFS_PTR(obj_ref)[i]);
    }
}

void test_get_obj_ref_bytes(void **state) {
    ObjRef test_obj_ref = new_composite_object(2);
    unsigned bytes = get_obj_ref_bytes(test_obj_ref);
    assert_int_equal(bytes, 20);
    test_obj_ref = new_composite_object(0);
    bytes = get_obj_ref_bytes(test_obj_ref);
    assert_int_equal(bytes, 4);
    test_obj_ref = newPrimObject(8);
    bytes = get_obj_ref_bytes(test_obj_ref);
    assert_int_equal(bytes, 12);
}

void test_get_obj_ref_size(void **state) {
    ObjRef test_obj_ref = new_composite_object(2);
    unsigned size = get_obj_ref_size(test_obj_ref);
    assert_int_equal(size, 2);
    test_obj_ref = new_composite_object(0);
    size = get_obj_ref_size(test_obj_ref);
    assert_int_equal(size, 0);
    test_obj_ref = newPrimObject(8);
    size = get_obj_ref_size(test_obj_ref);
    assert_int_equal(size, 8);
}

void test_set_broken_heart(void **state) {
    ObjRef test_obj_ref = newPrimObject(6);
    print_obj_ref_in_be_bits(test_obj_ref);
    assert_false(IS_COPIED(test_obj_ref));
    set_broken_heart(test_obj_ref);
    print_obj_ref_in_be_bits(test_obj_ref);
    assert_true(IS_COPIED(test_obj_ref));
}

void test_set_forward_pointer(void **state) {
    vm = default_vm();
    print_heap_bytes();
    ObjRef test_obj_ref = new_composite_object(0);
    print_memory_in_be_bits(test_obj_ref, 4);
    unsigned forward_pointer = vm.heap.used;
    print_memory_in_be_bits(&forward_pointer, 4);
    printf("FP: %u\n", forward_pointer);
    set_broken_heart(test_obj_ref);
    set_forward_pointer(test_obj_ref, forward_pointer);
    print_memory_in_be_bits(test_obj_ref, 4);
}

void test_get_obj_ref_from_forward_pointer(void **state) {
    ObjRef test_obj_ref = new_composite_object(2);
    ObjRef new_obj_ref = relocate(test_obj_ref);
    ObjRef forward_pointer_decoded_obj_ref = get_obj_ref_from_forward_pointer(test_obj_ref);
    assert_ptr_not_equal(test_obj_ref, new_obj_ref);
    assert_ptr_equal(forward_pointer_decoded_obj_ref, new_obj_ref);
    print_obj_ref(forward_pointer_decoded_obj_ref);
    print_obj_ref(new_obj_ref);
}

void test_open_file(void **state) {}
void test_seek_file(void **state) {}
void test_close_file(void **state) {}
void test_check_ninja_binary_format(void **state) {}
void test_check_ninja_version(void **state) {}
void test_check_ninja_instruction_count(void **state) {}
void test_check_ninja_variable_count(void **state) {}
