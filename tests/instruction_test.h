#ifndef _INSTRUCTION_TEST_H
#define _INSTRUCTION_TEST_H

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>

#include "instruction.h"

void test_encode_instruction(void **state);
void test_decode_instruction(void **state);

#endif
