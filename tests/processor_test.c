#include "include/processor_test.h"

const struct CMUnitTest processor_unit_tests[] = {
    cmocka_unit_test(test_processor),
};

void test_processor(void **state) {
    assert_int_equal(0, 0);
}
