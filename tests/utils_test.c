#include "include/utils_test.h"

const struct CMUnitTest utils_unit_tests[] = {
    cmocka_unit_test(test_read_file),
    cmocka_unit_test(test_read_instructions_into_ir),
    cmocka_unit_test(test_open_file),
    cmocka_unit_test(test_seek_file),
    cmocka_unit_test(test_check_ninja_binary_format),
    cmocka_unit_test(test_close_file),
    cmocka_unit_test(test_check_ninja_instruction_count),
    cmocka_unit_test(test_check_ninja_variable_count),
    cmocka_unit_test(test_new_composite_object),
    cmocka_unit_test(test_get_obj_ref_bytes),
    cmocka_unit_test(test_get_obj_ref_size),
};

void test_read_file(void **state) {}
void test_read_instructions_into_ir(void **state) {}
void test_open_file(void **state) {}
void test_seek_file(void **state) {}
void test_check_ninja_binary_format(void **state) {}
void test_close_file(void **state) {}
void test_check_ninja_instruction_count(void **state) {}
void test_check_ninja_variable_count(void **state) {}
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
void test_get_obj_ref_bytes(void **state) {}
void test_get_obj_ref_size(void **state) {}
