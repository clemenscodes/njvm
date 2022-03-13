#ifndef _IR_TEST_H
#define _IR_TEST_H

#include "cmocka.h"
#include "ir.h"

const struct CMUnitTest ir_unit_tests[2];

void test_default_ir(void **state);
void test_initialize_ir(void **state);

#endif
