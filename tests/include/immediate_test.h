#ifndef _IMMEDIATE_TEST_H
#define _IMMEDIATE_TEST_H

#include "cmocka/cmocka.h"
#include "immediate.h"

const struct CMUnitTest immediate_unit_tests[2];

void test_decode_immediate(void **state);
void test_encode_immediate(void **state);

#endif
