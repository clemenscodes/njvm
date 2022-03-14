#include "include/gc_test.h"

const struct CMUnitTest gc_unit_tests[] = {
    cmocka_unit_test(test_run_gc),
    cmocka_unit_test(test_copy_obj_ref),
    cmocka_unit_test(test_copy_obj_ref_returns_null),
    cmocka_unit_test(test_nullify_heap_stats),
    cmocka_unit_test(test_swap_heaps),
    cmocka_unit_test(test_relocate_registers),
    cmocka_unit_test(test_relocate_stack_objects),
    cmocka_unit_test(test_relocate_sda_objects),
};

void test_nullify_heap_stats(void **state) {
    nullify_heap_stats();
    assert_int_equal(vm.heap.used, 0);
    assert_int_equal(vm.heap.size, 0);
    assert_int_equal(vm.gc.copied_objects, 0);
    assert_int_equal(vm.gc.copied_bytes, 0);
}

void test_swap_heaps(void **state) {
    unsigned char *old_begin = vm.heap.begin;
    unsigned char *old_active = vm.heap.active;
    unsigned char *old_passive = vm.heap.passive;
    unsigned char *old_next = vm.heap.next;
    swap_heaps();
    assert_ptr_equal(old_begin, vm.heap.passive);
    assert_ptr_equal(old_active, vm.heap.passive);
    assert_ptr_equal(old_next, vm.heap.passive);
    assert_ptr_equal(old_passive, vm.heap.active);
}

void test_relocate_registers(void **state) {
    relocate_registers();
}

void test_relocate_stack_objects(void **state) {
    relocate_stack_objects();
}

void test_relocate_sda_objects(void **state) {
    relocate_sda_objects();
}

void test_copy_obj_ref(void **state) {
    // size_t size = 4;
    // ObjRef test_obj_ref = newPrimObject(size);
    // ObjRef copied_obj_ref = copy_obj_ref(test_obj_ref);
}

void test_copy_obj_ref_returns_null(void **state) {
    assert_null(copy_obj_ref(NULL));
}

void test_run_gc(void **state) {}
