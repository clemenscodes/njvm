#include "include/opcode_test.h"

void test_decode_opcode(void **state) {
    assert_int_equal(HALT, 0);
}

void test_encode_opcode(void **state) {
    assert_int_equal(PUSHC, 1);
}
