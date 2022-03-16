#include "include/gc_test.h"

const struct CMUnitTest gc_unit_tests[] = {
    cmocka_unit_test(test_nullify_heap_stats),
    cmocka_unit_test(test_swap_heaps),
    cmocka_unit_test(test_relocate_registers),
    cmocka_unit_test(test_relocate_stack_objects),
    cmocka_unit_test(test_relocate_sda_objects),
    cmocka_unit_test(test_relocate),
    cmocka_unit_test(test_relocate_returns_null),
    cmocka_unit_test(test_collect_stats),
    cmocka_unit_test(test_print_gc_stats),
    cmocka_unit_test(test_purge_heap),
    cmocka_unit_test(test_run_gc),
    cmocka_unit_test(test_scan),
};

void test_nullify_heap_stats(void **state) {
    new_composite_object(2);
    new_composite_object(3);
    new_composite_object(4);
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
    swap_heaps();
    assert_ptr_equal(old_begin, vm.heap.passive);
    assert_ptr_equal(old_active, vm.heap.passive);
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

void test_relocate(void **state) {
    // size_t size = 4;
    // ObjRef test_obj_ref = newPrimObject(size);
    // ObjRef copied_obj_ref = relocate(test_obj_ref);
}

void test_relocate_returns_null(void **state) {
    assert_null(relocate(NULL));
}

void test_copy_obj_ref_to_free_memory(void **state) {
    ObjRef test_obj_ref = new_composite_object(4);
    ObjRef new_obj_ref = copy_obj_ref_to_free_memory(test_obj_ref);
    unsigned bytes = get_obj_ref_bytes(test_obj_ref);
    assert_memory_equal(test_obj_ref, new_obj_ref, bytes);
}

void test_collect_stats(void **state) {}
void test_scan(void **state) {}
void test_print_gc_stats(void **state) {}
void test_purge_heap(void **state) {}
void test_run_gc(void **state) {}
