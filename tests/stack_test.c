#include "include/stack_test.h"

const struct CMUnitTest stack_unit_tests[] = {
    cmocka_unit_test(test_default_stack),
    cmocka_unit_test(test_initialize_stack),
};

void test_default_stack(void **state) {
    assert_int_equal(vm.stack.size, 0);
    assert_int_equal(vm.stack.sp, 0);
    assert_int_equal(vm.stack.fp, 0);
    assert_int_equal(vm.stack.memory, DEFAULT_STACK_SIZE);
    assert_int_equal(vm.stack.bytes, vm.stack.memory * KiB);
    assert_int_equal(vm.stack.max_items, vm.stack.bytes / sizeof(StackSlot));
    assert_non_null(vm.stack.data);
}

void test_initialize_stack(void **state) {
    size_t factor = 2;
    size_t init_size = DEFAULT_STACK_SIZE * factor;
    initialize_stack(init_size);
    assert_int_equal(vm.stack.size, 0);
    assert_int_equal(vm.stack.sp, 0);
    assert_int_equal(vm.stack.fp, 0);
    assert_int_equal(vm.stack.memory, init_size);
    assert_int_equal(vm.stack.bytes, init_size * KiB);
    assert_int_equal(vm.stack.max_items, vm.stack.bytes / sizeof(StackSlot));
    assert_non_null(vm.stack.data);
}
