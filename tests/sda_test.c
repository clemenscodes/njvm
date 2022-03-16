#include "include/sda_test.h"

const struct CMUnitTest sda_unit_tests[] = {
    cmocka_unit_test(test_default_sda),
};

void test_default_sda(void **state) {
    assert_int_equal(vm.sda.size, 0);
    assert_null(vm.sda.data);
}
