#ifndef _INSTRUCTION_TEST_H
#define _INSTRUCTION_TEST_H

#include "cmocka.h"
#include "instruction.h"

void test_instruction(void **state);
void test_encode_instruction(void **state);
void test_decode_instruction(void **state);
void test_immediate_macro(void **state);
void test_sign_extend_macro(void **state);

#endif
