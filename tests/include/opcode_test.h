#ifndef _OPCODE_TEST_H
#define _OPCODE_TEST_H

#include "cmocka/cmocka.h"
#include "opcode.h"

const struct CMUnitTest opcode_unit_tests[2];

void test_encode_opcode(void **state);
void test_decode_opcode(void **state);

#endif
