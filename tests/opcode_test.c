#include "include/opcode_test.h"

void test_halt(void **state) {
    assert_int_equal(HALT, 0);
}

void test_pushc(void **state) {
    assert_int_equal(PUSHC, 1);
}
