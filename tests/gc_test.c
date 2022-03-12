#include "include/gc_test.h"

void test_run_gc(void **state) {
    assert_int_equal(0, 0);
}

void test_copy_obj_ref(void **state) {
    initialize_heap(DEFAULT_HEAP_SIZE);
    initialize_stack(DEFAULT_STACK_SIZE);
    size_t size = 4;
    ObjRef test_obj_ref = newPrimObject(size);
    ObjRef copied_obj_ref = copy_obj_ref(test_obj_ref);
}

void test_copy_obj_ref_returns_null(void **state) {
    initialize_heap(DEFAULT_HEAP_SIZE);
    initialize_stack(DEFAULT_STACK_SIZE);
    assert_null(copy_obj_ref(NULL));
}
