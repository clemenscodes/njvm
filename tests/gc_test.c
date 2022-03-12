#include "include/gc_test.h"

void test_run_gc(void **state) {
    assert_int_equal(0, 0);
}

void test_copy_obj_ref(void **state) {
    initialize_heap(DEFAULT_HEAP_SIZE);
    size_t size = 4;
    ObjRef test_obj_ref = newPrimObject(size);
    ObjRef copied_obj_ref = copy_obj_ref(test_obj_ref);
}

void test_copy_obj_ref_returns_null(void **state) {
    initialize_heap(DEFAULT_HEAP_SIZE);
    assert_null(copy_obj_ref(NULL));
}

void test_nullify_heap_stats(void **state) {
    initialize_heap(DEFAULT_HEAP_SIZE);
    nullify_heap_stats();
    assert_int_equal(vm.heap.used, 0);
    assert_int_equal(vm.heap.size, 0);
    assert_int_equal(vm.gc.copied_objects, 0);
    assert_int_equal(vm.gc.copied_bytes, 0);
}

void test_swap_heaps(void **state) {
    initialize_heap(DEFAULT_HEAP_SIZE);
    swap_heaps();
}

void test_relocate_registers(void **state) {
    initialize_heap(DEFAULT_HEAP_SIZE);
    relocate_registers();
}

void test_relocate_stack_objects(void **state) {
    initialize_heap(DEFAULT_HEAP_SIZE);
    initialize_stack(DEFAULT_HEAP_SIZE);
    relocate_stack_objects();
}

void test_relocate_sda_objects(void **state) {
    initialize_heap(DEFAULT_HEAP_SIZE);
    initialize_stack(DEFAULT_HEAP_SIZE);
    relocate_sda_objects();
}
