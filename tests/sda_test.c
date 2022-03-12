#include "include/sda_test.h"

void test_default_sda(void **state) {
    assert_int_equal(vm.sda.size, 0);
    assert_null(vm.sda.data);
}
