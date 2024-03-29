#ifndef _INSTRUCTION_TEST_H
#define _INSTRUCTION_TEST_H

#include "cmocka/cmocka.h"
#include "instruction.h"

const struct CMUnitTest instruction_unit_tests[3];

void test_instruction(void **state);
void test_encode_instruction(void **state);
void test_decode_instruction(void **state);

#endif
