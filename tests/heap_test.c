#include "include/heap_test.h"

const struct CMUnitTest heap_unit_tests[] = {
    cmocka_unit_test(test_default_heap),
    cmocka_unit_test(test_initialize_heap),
    cmocka_unit_test(test_alloc),
    cmocka_unit_test(test_print_heap_objects),
    cmocka_unit_test(test_print_heap_bytes),
};

void test_default_heap(void **state) {
    assert_int_equal(vm.heap.memory, DEFAULT_HEAP_SIZE);
    assert_int_equal(vm.heap.bytes, vm.heap.memory * KiB);
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
    initialize_heap(DEFAULT_HEAP_SIZE);
    unsigned char *old_next_pointer = vm.heap.next;
    unsigned char *old_passive = vm.heap.passive;
    size_t size = 4;
    ObjRef test_obj_ref = (ObjRef)alloc(size);
    assert_int_equal(vm.heap.used, size);
    assert_int_equal(vm.heap.size, 1);
    assert_ptr_equal(old_next_pointer, vm.heap.active);
    assert_ptr_equal(old_next_pointer, test_obj_ref);
    assert_ptr_equal(vm.heap.next, old_next_pointer + size);
    assert_ptr_equal(old_passive, vm.heap.passive);
}

void test_print_heap_objects(void **state) {
    vm = default_vm();
    newPrimObject(4);
    new_composite_object(1);
    newPrimObject(8);
    new_composite_object(7);
    print_heap_objects();
}

void test_print_heap_bytes(void **state) {
    vm = default_vm();
    newPrimObject(4);
    new_composite_object(2);
    newPrimObject(8);
    print_heap_bytes();
}
