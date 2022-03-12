#include "include/heap_test.h"

void test_initialize_heap(void **state) {
    test_setup();
    assert_int_equal(vm.heap.memory, 8192);
    assert_int_equal(vm.heap.bytes, vm.heap.memory * 1024);
    assert_int_equal(vm.heap.available, vm.heap.bytes / 2);
    assert_int_equal(vm.heap.used, 0);
    assert_int_equal(vm.heap.size, 0);
    assert_ptr_equal(vm.heap.next, vm.heap.begin);
    assert_ptr_equal(vm.heap.begin, vm.heap.active);
    assert_ptr_equal(vm.heap.passive, vm.heap.next + vm.heap.available);
}

void test_alloc(void **state) {
    test_setup();
    assert_int_equal(0, 0);
}
