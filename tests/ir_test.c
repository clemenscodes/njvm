#include "include/ir_test.h"

void test_default_ir(void **state) {
    assert_int_equal(vm.ir.size, 0);
    assert_int_equal(vm.ir.pc, 0);
    assert_null(vm.ir.data);
}
