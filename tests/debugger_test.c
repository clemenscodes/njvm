#include "include/debugger_test.h"

const struct CMUnitTest debugger_unit_tests[] = {
    cmocka_unit_test(test_debug),
    cmocka_unit_test(test_prompt),
    cmocka_unit_test(test_inspect),
    cmocka_unit_test(test_step),
    cmocka_unit_test(test_next),
    cmocka_unit_test(test_run),
    cmocka_unit_test(test_set_breakpoint),
    cmocka_unit_test(test_print_obj_ref),
    cmocka_unit_test(test_print_memory_in_be_bytes),
    cmocka_unit_test(test_print_memory_in_le_bytes),
    cmocka_unit_test(test_print_obj_ref_in_be_bytes),
    cmocka_unit_test(test_print_obj_ref_in_le_bytes),
};

void test_debug(void **state) {}
void test_prompt(void **state) {}
void test_inspect(void **state) {}
void test_step(void **state) {}
void test_next(void **state) {}
void test_run(void **state) {}
void test_set_breakpoint(void **state) {}
void test_print_obj_ref(void **state) {}

void test_print_memory_in_be_bytes(void **state) {
    ObjRef test_obj_ref = new_composite_object(1);
    size_t bytes = get_obj_ref_bytes(test_obj_ref);
    print_memory_in_be_bytes(test_obj_ref, bytes);
}

void test_print_memory_in_le_bytes(void **state) {
    ObjRef test_obj_ref = new_composite_object(1);
    size_t bytes = get_obj_ref_bytes(test_obj_ref);
    print_memory_in_le_bytes(test_obj_ref, bytes);
}

void test_print_obj_ref_in_be_bytes(void **state) {
    ObjRef test_obj_ref = new_composite_object(1);
    print_obj_ref_in_be_bytes(test_obj_ref);
}

void test_print_obj_ref_in_le_bytes(void **state) {
    ObjRef test_obj_ref = new_composite_object(1);
    print_obj_ref_in_le_bytes(test_obj_ref);
}
