#include "include/heap_test.h"

void test_default_heap(void **state) {
    assert_int_equal(vm.heap.memory, DEFAULT_HEAP_SIZE);
    assert_int_equal(vm.heap.bytes, vm.heap.memory * KiB);
    assert_int_equal(vm.heap.available, vm.heap.bytes / 2);
    assert_int_equal(vm.heap.used, 0);
    assert_int_equal(vm.heap.size, 0);
    assert_null(vm.heap.begin);
    assert_null(vm.heap.active);
    assert_null(vm.heap.passive);
    assert_null(vm.heap.next);
}

void test_initialize_heap(void **state) {
    size_t factor = 2;
    size_t init_size = DEFAULT_HEAP_SIZE * factor;
    initialize_heap(init_size);
    assert_int_equal(vm.heap.memory, init_size);
    assert_int_equal(vm.heap.bytes, init_size * KiB);
    assert_int_equal(vm.heap.available, vm.heap.bytes / 2);
    assert_int_equal(vm.heap.used, 0);
    assert_int_equal(vm.heap.size, 0);
    assert_non_null(vm.heap.begin);
    assert_non_null(vm.heap.active);
    assert_non_null(vm.heap.passive);
    assert_non_null(vm.heap.next);
    assert_ptr_equal(vm.heap.begin, vm.heap.active);
    assert_ptr_equal(vm.heap.active, vm.heap.next);
    assert_ptr_equal(vm.heap.passive, vm.heap.next + vm.heap.available);
    assert_ptr_not_equal(vm.heap.active, vm.heap.passive);
    assert_memory_equal(vm.heap.begin, vm.heap.active, vm.heap.available);
}

void test_alloc(void **state) {
    assert_int_equal(0, 0);
}
